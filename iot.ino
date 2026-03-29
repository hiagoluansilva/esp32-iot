/**
*@file iot.ino
*@brief Trabalho IOT
*@author HIago Silva / Vitor Becker  Turma 4422
*
**/
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN 4     // Pino do DHT11
#define DHTTYPE DHT11   // Modelo do DHT
#define TEMPO_SLEEP 60000000 //Tempo para sair do deep sleep em uS

const char* ssid = "YOUR_WIFI_SSID";//Parâmetros WIFI
const char* password = "YOUR_WIFI_PASSWORD";
const char* server = "mqtt.tago.io"; //Server da Tago
const int porta = 8883; //Porta com SSL/TLS
const char* mqtt_usuario = "esp32";
const char* mqtt_token = "YOUR_TAGO_TOKEN";//Token do Bucket
String dados;
String dados1;
String dados2;
String dados3;
String dados4;
float temperatura;
float umidade;
float temp_sentida;
float consumo= ((4*143)+(0.130*60))/64;//consumo ligado*tempo ligado + consumo deep sleep*tempo / tempo total
bool som;

//Certificado para autenticação
const char* test_root_ca= \
"-----BEGIN CERTIFICATE-----\n" \ 
"MIIEDzCCAvegAwIBAgIBADANBgkqhkiG9w0BAQUFADBoMQswCQYDVQQGEwJVUzEl\n" \ 
"MCMGA1UEChMcU3RhcmZpZWxkIFRlY2hub2xvZ2llcywgSW5jLjEyMDAGA1UECxMp\n" \ 
"U3RhcmZpZWxkIENsYXNzIDIgQ2VydGlmaWNhdGlvbiBBdXRob3JpdHkwHhcNMDQw\n" \ 
"NjI5MTczOTE2WhcNMzQwNjI5MTczOTE2WjBoMQswCQYDVQQGEwJVUzElMCMGA1UE\n" \ 
"ChMcU3RhcmZpZWxkIFRlY2hub2xvZ2llcywgSW5jLjEyMDAGA1UECxMpU3RhcmZp\n" \ 
"ZWxkIENsYXNzIDIgQ2VydGlmaWNhdGlvbiBBdXRob3JpdHkwggEgMA0GCSqGSIb3\n" \ 
"DQEBAQUAA4IBDQAwggEIAoIBAQC3Msj+6XGmBIWtDBFk385N78gDGIc/oav7PKaf\n" \ 
"8MOh2tTYbitTkPskpD6E8J7oX+zlJ0T1KKY/e97gKvDIr1MvnsoFAZMej2YcOadN\n" \ 
"+lq2cwQlZut3f+dZxkqZJRRU6ybH838Z1TBwj6+wRir/resp7defqgSHo9T5iaU0\n" \ 
"X9tDkYI22WY8sbi5gv2cOj4QyDvvBmVmepsZGD3/cVE8MC5fvj13c7JdBmzDI1aa\n" \ 
"K4UmkhynArPkPw2vCHmCuDY96pzTNbO8acr1zJ3o/WSNF4Azbl5KXZnJHoe0nRrA\n" \ 
"1W4TNSNe35tfPe/W93bC6j67eA0cQmdrBNj41tpvi/JEoAGrAgEDo4HFMIHCMB0G\n" \ 
"A1UdDgQWBBS/X7fRzt0fhvRbVazc1xDCDqmI5zCBkgYDVR0jBIGKMIGHgBS/X7fR\n" \ 
"zt0fhvRbVazc1xDCDqmI56FspGowaDELMAkGA1UEBhMCVVMxJTAjBgNVBAoTHFN0\n" \ 
"YXJmaWVsZCBUZWNobm9sb2dpZXMsIEluYy4xMjAwBgNVBAsTKVN0YXJmaWVsZCBD\n" \ 
"bGFzcyAyIENlcnRpZmljYXRpb24gQXV0aG9yaXR5ggEAMAwGA1UdEwQFMAMBAf8w\n" \ 
"DQYJKoZIhvcNAQEFBQADggEBAAWdP4id0ckaVaGsafPzWdqbAYcaT1epoXkJKtv3\n" \ 
"L7IezMdeatiDh6GX70k1PncGQVhiv45YuApnP+yz3SFmH8lU+nLMPUxA2IGvd56D\n" \ 
"eruix/U0F47ZEUD0/CwqTRV/p2JdLiXTAAsgGh1o+Re49L2L7ShZ3U0WixeDyLJl\n" \ 
"xy16paq8U4Zt3VekyvggQQto8PT7dL5WXXp59fkdheMtlb71cZBDzI0fmgAKhynp\n" \ 
"VSJYACPq4xJDKVtHCN2MQWplBqjlIapBtJUhlbl90TSrE9atvNziPTnNvT51cKEY\n" \ 
"WQPJIrSPnNVeKtelttQKbfi3QBFGmh95DmK/D5fs4C8fF5Q=\n" \ 
"-----END CERTIFICATE-----\n" ;

WiFiClientSecure rede;
PubSubClient client(rede);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  delay(500);//Bug wakeup
   esp_sleep_enable_timer_wakeup(TEMPO_SLEEP);//hablita deep sleep por timer
   pinMode(2,OUTPUT);
   pinMode(15,INPUT);
   dht.begin();
   conecta_wifi();//COnexão do WiFi
}
void loop() {
  dht_11();//Leitura e atribuição a variável
  detecta_pessoas();//Leitura e atribuição a variável
  conecta_tago_envia();//Envia para o Tago
  esp_deep_sleep_start();//Dorme
}

void dht_11(void)
{
  /**
  *@brief Função para Leitura do sensor DHT11
  *@param none
  **/
  delay(1000);
  
  umidade = dht.readHumidity();// Umidade
  temperatura = dht.readTemperature();// Temperatura em ºC

  if (isnan(umidade) || isnan(temperatura))
  {
    umidade = dht.readHumidity();
    temperatura = dht.readTemperature();
  }

  temp_sentida = dht.computeHeatIndex(temperatura, umidade, false);//Índice térmico em ºC
};

void conecta_tago_envia(void)
{
  /**
  *@brief Função para Conectar com o servidor da Tago
  *@param none
  *
  **/
   rede.setCACert(test_root_ca); //Autentica Server
   client.setServer(server, porta); // Conecta Servidor da Tago

   while (!client.connected()) 
   {
     client.connect("ESP32", mqtt_usuario, mqtt_token);
   }

  dados = "{\"variable\":\"temperatura\",\"value\":" + String(temperatura) + String("}");
  client.publish("tago/data/post", (char*) dados.c_str());

  dados1 = "{\"variable\":\"umidade\",\"value\":" + String(umidade) + String("}");
  client.publish("tago/data/post", (char*) dados1.c_str());

  dados2 = "{\"variable\":\"temp_sentida\",\"value\":" + String(temp_sentida) + String("}"); 
  client.publish("tago/data/post", (char*) dados2.c_str());

  client.publish("tago/data/post", (char*) dados3.c_str());

  dados4 = "{\"variable\":\"consumo\",\"value\":" + String(consumo) + String("}"); 
  client.publish("tago/data/post", (char*) dados4.c_str());
  rede.stop();//Encerra conexão
};

void detecta_pessoas(void)
{
  /**
  *@brief Função para Leitura de presença de pessoas
  *@param none
  **/
  som = digitalRead(15);
  if(!som)
  {
    dados3 = "{\"variable\":\"pessoas\",\"value\":\"Habitado\"}";
  }
  else if(som)
  {
    dados3 = "{\"variable\":\"pessoas\",\"value\":\"Vazio\"}";
  };
};

void conecta_wifi(void)
{ 
  /**
  *@brief Função para Conectar a rede WiFi local
  *@param none
  **/
   WiFi.mode(WIFI_AP_STA);
   WiFi.begin(ssid, password);
   
   while(WiFi.status() != WL_CONNECTED)//Espera conectar
   {
    delay(500); 
   }
};
