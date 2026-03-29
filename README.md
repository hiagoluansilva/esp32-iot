# ESP32 IoT — Monitoramento com MQTT/TLS e Tago.io

🇧🇷 **Português** | 🇺🇸 [English](#english)

---

## Português

Dispositivo IoT com ESP32 que lê temperatura/umidade (DHT11) e presença (PIR), envia dados para a plataforma Tago.io via MQTT/TLS, e entra em deep sleep entre leituras.

### O que faz
- Lê **DHT11** (temperatura e umidade) no **GPIO4**
- Detecta presença via sensor PIR no **GPIO15**
- Conecta-se ao **broker MQTT com TLS** na porta **8883**
- Publica dados para a plataforma **Tago.io** usando token de autenticação
- Entra em **deep sleep por 60 segundos** após cada envio para economizar energia

### Parâmetros
| Parâmetro | Valor |
|---|---|
| DHT11 | GPIO4 |
| Sensor PIR | GPIO15 |
| Porta MQTT | 8883 (TLS) |
| Plataforma cloud | Tago.io |
| Deep sleep | 60 segundos |

### Segurança
As credenciais (SSID, senha Wi-Fi, token Tago) devem ser configuradas como constantes no código. **Nunca compartilhe o token real publicamente.**

### Plataforma
ESP32 — Arduino Framework

---

## English

IoT device on ESP32 that reads temperature/humidity (DHT11) and presence (PIR), sends data to Tago.io via MQTT/TLS, and enters deep sleep between readings.

### What it does
- Reads **DHT11** (temperature and humidity) on **GPIO4**
- Detects presence via PIR sensor on **GPIO15**
- Connects to **MQTT broker with TLS** on port **8883**
- Publishes data to **Tago.io** platform using an auth token
- Enters **60-second deep sleep** after each transmission to save energy

### Parameters
| Parameter | Value |
|---|---|
| DHT11 | GPIO4 |
| PIR sensor | GPIO15 |
| MQTT port | 8883 (TLS) |
| Cloud platform | Tago.io |
| Deep sleep | 60 seconds |

### Security
Credentials (SSID, Wi-Fi password, Tago token) must be set as constants in the code. **Never share your real token publicly.**

### Platform
ESP32 — Arduino Framework
