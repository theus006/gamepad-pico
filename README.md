# 🏎️ Motion Control Steering Wheel (RP2040 + ADXL345)

Um controlador HID (Gamepad/Volante USB) baseado em sensor de movimento e inclinação. O projeto utiliza um microcontrolador Raspberry Pi Pico (RP2040) e um acelerômetro triaxial ADXL345 para converter a inclinação das mãos no Eixo X da direção de um veículo, acompanhado de botões digitais para acelerador e freio.

Reconhecido nativamente como um dispositivo Plug & Play USB HID, não requer drivers adicionais no Windows ou Linux.

---

## 🛠️ Recursos e Destaques

- Nativo USB HID (TinyUSB): Funciona diretamente sem necessidade de pacotes externos de drivers ou softwares de emulação.
- Filtro de Suavização Passa-Baixa (Média Móvel): Suaviza pequenas variações e tremores das mãos, garantindo uma direção firme e precisa.
- Zona Morta Neutra (Deadzone): Evita desvios acidentais em retas e rodovias.
- Sensibilidade Customizável: Escala otimizada para curvas confortáveis sem necessidade de inclinações excessivas dos pulsos (~24° de esterço máximo).
- Testado no Linux (Wine/Proton): Ótimo desempenho em jogos leves e clássicos de corrida e simuladores de caminhão (ex: 18 Wheels of Steel: Haulin', TrackMania, Need for Speed).

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
- CS  -> 3.3V (Obrigatório para forçar o modo I2C)
- SDO -> GND (Define o endereço I2C para 0x53)

### Conexão dos Botões:
- Acelerador (Botão 0): GP14 + GND
- Freio (Botão 1): GP15 + GND

Nota: Os botões utilizam os resistores de pull-up internos (INPUT_PULLUP). O outro lado de cada botão deve ser ligado diretamente ao GND.

---

## 💻 Requisitos e Bibliotecas (Arduino IDE)

Para compilar e carregar o código no Raspberry Pi Pico / RP2040, certifique-se de ter instalado no Arduino IDE:

1. Placa: Pacote de placas Raspberry Pi Pico/RP2040 (Earle F. Philhower ou pacote oficial da Arduino).
2. Bibliotecas Necessárias:
   - Adafruit_ADXL345
   - Adafruit_Sensor
   - Adafruit_TinyUSB

### Configuração na Arduino IDE:
No menu Tools (Ferramentas):
- Board: Raspberry Pi Pico ou Waveshare RP2040-Zero
- USB Stack: Adafruit TinyUSB (Crucial para o suporte HID)

---

## 🚀 Como Executar

1. Clone este repositório:
   git clone https://github.com/theus006/gamepad-pico.git

2. Abra o arquivo .ino na Arduino IDE.
3. Conecte sua placa RP2040 via cabo USB.
4. Selecione a porta correta e clique em Upload.
5. Abra o painel de controles do seu sistema operacional (jstest-gtk no Linux ou joy.cpl no Windows) para testar a movimentação e calibração dos eixos!

---
## 🎮 Compatibilidade com Jogos

Testado e aprovado em:
- 18 Wheels of Steel: Haulin' (via Wine/Linux)
---

## 📜 Licença

Este projeto é de código aberto sob a licença MIT. Sinta-se à vontade para modificar, melhorar e distribuir!
