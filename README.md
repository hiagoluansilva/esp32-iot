# esp32-iot

Sistema IoT com ESP32 para monitoramento ambiental e envio de dados para a plataforma Tago.io via MQTT/TLS.

## Descrição

Nó IoT que lê temperatura, umidade e presença de pessoas, envia os dados para a nuvem (Tago.io) via MQTT sobre TLS (porta 8883) e entra em deep sleep para economizar energia. Desenvolvido para monitoramento de ambientes.

## Hardware

- Placa: ESP32
- Sensor de temperatura/umidade: DHT11 (GPIO 4)
- Sensor de presença (som): GPIO 15
- LED indicador: GPIO 2

## Variáveis publicadas (MQTT)

| Variável | Descrição |
|----------|-----------|
| `temperatura` | Temperatura em °C |
| `umidade` | Umidade relativa em % |
| `temp_sentida` | Índice de calor (heat index) em °C |
| `pessoas` | `"Habitado"` ou `"Vazio"` |
| `consumo` | Estimativa de consumo energético |

## Consumo de energia

Usa deep sleep entre leituras (60 segundos) para maximizar a autonomia em dispositivos alimentados por bateria.

## Configuração

Antes de gravar, edite `iot.ino` e substitua as variáveis:

```cpp
const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_token = "YOUR_TAGO_TOKEN";  // Token do bucket na Tago.io
```

## Plataforma IoT

[Tago.io](https://tago.io) — servidor MQTT `mqtt.tago.io:8883` com SSL/TLS.

## Dependências (Arduino IDE)

- `PubSubClient`
- `DHT sensor library` (Adafruit)
- `WiFiClientSecure` (built-in ESP32)

## Escola

Centro Tecnológico Liberato — Novo Hamburgo/RS
Autores: Hiago Silva / Vitor Becker — Turma 4422
