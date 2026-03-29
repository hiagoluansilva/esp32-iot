🇧🇷 Português | 🇺🇸 [English](#english)

# esp32-iot

Sistema IoT com ESP32: temperatura/umidade (DHT11), presença, MQTT/TLS para Tago.io e deep sleep.

## Variáveis publicadas

| Variável | Descrição |
|----------|-----------|
| `temperatura` | °C via DHT11 |
| `umidade` | % via DHT11 |
| `temp_sentida` | Heat index |
| `pessoas` | `"Habitado"` / `"Vazio"` |
| `consumo` | Estimativa de consumo |

## Configuração

```cpp
const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_token = "YOUR_TAGO_TOKEN";
```

## Dependências

`PubSubClient` · `DHT sensor library` · `WiFiClientSecure`

Autores: Hiago Silva / Vitor Becker — Turma 4422
Centro Tecnológico Liberato — Novo Hamburgo/RS

---

<a name="english"></a>
🇧🇷 [Português](#) | 🇺🇸 English

# esp32-iot

ESP32 IoT system: temperature/humidity (DHT11), presence detection, MQTT/TLS to Tago.io, deep sleep.

## Published variables

| Variable | Description |
|----------|-------------|
| `temperatura` | °C via DHT11 |
| `umidade` | % via DHT11 |
| `temp_sentida` | Heat index |
| `pessoas` | `"Habitado"` / `"Vazio"` |
| `consumo` | Power consumption estimate |

## Configuration

```cpp
const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_token = "YOUR_TAGO_TOKEN";
```

## Dependencies

`PubSubClient` · `DHT sensor library` · `WiFiClientSecure`

Authors: Hiago Silva / Vitor Becker — Class 4422
Centro Tecnológico Liberato — Novo Hamburgo/RS, Brazil
