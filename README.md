# 🏎️ Motion Control Steering Wheel (RP2040 + ADXL345)

Um controlador HID de jogo (Gamepad/Volante USB) baseado em sensor de movimento e inclinação. O projeto utiliza um microcontrolador Raspberry Pi Pico (RP2040) e um acelerômetro triaxial ADXL345 para converter a inclinação das mãos no Eixo X da direção de um veículo, acompanhado de botões digitais para acelerador e freio.

Reconhecido nativamente como um dispositivo Plug & Play USB HID, não requer drivers adicionais no Windows ou Linux.

---

## 🛠️ Recursos e Destaques

- Nativo USB HID (TinyUSB): Funciona diretamente sem necessidade de pacotes externos de drivers ou softwares de emulação.
- Leitura Direta e Limite de Esterço: Mapeamento do Eixo X calibrado para limite de +- 7.0 m/s² (~45° de inclinação máxima), convertendo a aceleração para a escala padrão do Gamepad HID (-127 a 127).
- Sinalização de LED: O LED interno pisca durante o funcionamento e entra em modo de alerta caso o sensor ADXL345 não seja identificado na inicialização.
- Compatibilidade com Linux/Wine: Desenvolvido para rodar perfeitamente em jogos de corrida rodando via camada Wine/Proton no Linux sem depender de emuladores de controle.

---

## 🧰 Hardware Utilizado

| Componente | Especificação / Descrição |
| :--- | :--- |
| Microcontrolador | Raspberry Pi Pico ou RP2040-Zero |
| Acelerômetro | Módulo ADXL345 (I2C) |
| Entradas | 2x Botões Táteis (Push-buttons 6x6) |
| Conexão | Cabo USB (Tipo C ou Micro-USB) |

---

## 📌 Esquema de Ligação (Pinout)

### Conexão I2C do ADXL345:
- VCC -> 3.3V (OUT) da Pico
- GND -> GND da Pico
- SDA -> GP4 (SDA)
- SCL -> GP5 (SCL)
- CS  -> 3.3V (Força o modo I2C)
- SDO -> GND (Define o endereço I2C para 0x53)

### Conexão dos Botões:
- Acelerador (Botão 0): GP14 + GND
- Freio (Botão 1): GP15 + GND

Nota: Os botões utilizam os resistores de pull-up internos (INPUT_PULLUP). O outro lado de cada botão deve ser ligado diretamente ao GND.

---

## 💻 Requisitos e Bibliotecas (Arduino IDE)

Para compilar e carregar o código no Raspberry Pi Pico / RP2040, certifique-se de ter instalado na Arduino IDE:

1. Placa: Pacote de placas Raspberry Pi Pico/RP2040 (Earle F. Philhower ou pacote oficial da Arduino).
2. Bibliotecas Necessárias:
   - Adafruit_ADXL345
   - Adafruit_Sensor
   - Adafruit_TinyUSB

### Configuração na Arduino IDE:
No menu Tools (Ferramentas):
- Board: Raspberry Pi Pico ou Waveshare RP2040-Zero
- USB Stack: Adafruit TinyUSB (Obrigatório para o suporte HID)

---

## 🚀 Como Executar

1. Clone este repositório:
   git clone https://github.com/theus006/gamepad-pico.git

2. Abra o arquivo .ino na Arduino IDE.
3. Conecte sua placa RP2040 via cabo USB.
4. Selecione a porta correta e clique em Upload.
5. Abra o painel de controles do seu sistema operacional (jstest-gtk no Linux ou joy.cpl no Windows) para testar a movimentação e os botões.

---

## 🎮 Compatibilidade Testada

- 18 Wheels of Steel: Haulin' (Linux via Wine)

---

## 📜 Licença

Este projeto é de código aberto sob a licença MIT.

## 📜 Esquemático

<img width="1169" height="827" alt="Schematic_controle-pico_2026-10-07 (1)" src="https://github.com/user-attachments/assets/bc778187-1d3f-44c0-a352-0aab5db59ef0" />

