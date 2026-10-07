#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_TinyUSB.h>

// Descritor HID de Gamepad nativo
uint8_t const desc_hid_report[] = {
  TUD_HID_REPORT_DESC_GAMEPAD()
};

Adafruit_USBD_HID usb_hid(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_NONE, 2, false);
hid_gamepad_report_t gp_report;

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

const int pinoAcelerador = 14; // GP14 -> Botão 1
const int pinoFreio      = 15; // GP15 -> Botão 2
const int pinoLED        = LED_BUILTIN; // LED interno da Pico para feedback

void setup() {
  pinMode(pinoAcelerador, INPUT_PULLUP);
  pinMode(pinoFreio, INPUT_PULLUP);
  pinMode(pinoLED, OUTPUT);

  // Inicializa barramento I2C na Pico (GP4 = SDA, GP5 = SCL)
  Wire.setSDA(4);
  Wire.setSCL(5);
  Wire.begin();

  if (!accel.begin()) {
    // Se o sensor não for encontrado, pisca o LED rapidamente
    while (1) {
      digitalWrite(pinoLED, HIGH);
      delay(100);
      digitalWrite(pinoLED, LOW);
      delay(100);
    }
  }
  accel.setRange(ADXL345_RANGE_2_G);

  // Configura a USB
  usb_hid.begin();

  // Aguarda a montagem da USB no sistema
  while (!TinyUSBDevice.mounted()) delay(10);
}

void loop() {
  // Mantém o motor da TinyUSB ativo (crucial para o Linux receber os dados)
  #ifdef TUSB_ADDED_SUBSYSTEMS
  tud_task();
  #endif

  sensors_event_t event;
  accel.getEvent(&event);

  float xVal = event.acceleration.x;

  // Trava os limites para +- 7.0 m/s² (aprox 45 Graus)
  if (xVal > 7.0) xVal = 7.0;
  if (xVal < -7.0) xVal = -7.0;

  // Converte a leitura para a escala do Gamepad HID (-127 a 127)
  int8_t steering = map(xVal * 100, -700, 700, -127, 127);

  // Zera a estrutura antes de enviar
  memset(&gp_report, 0, sizeof(gp_report));

  // Eixo X da direção
  gp_report.x = steering;

  // Botões
  if (digitalRead(pinoAcelerador) == LOW) gp_report.buttons |= GAMEPAD_BUTTON_0;
  if (digitalRead(pinoFreio) == LOW)      gp_report.buttons |= GAMEPAD_BUTTON_1;

  // Envia se a interface HID estiver pronta
  if (usb_hid.ready()) {
    usb_hid.sendReport(0, &gp_report, sizeof(gp_report));
  }

  // Pisca levemente o LED para demonstrar que o programa está rodando normalmente
  digitalWrite(pinoLED, (millis() / 500) % 2);

  delay(10); // 100Hz
}