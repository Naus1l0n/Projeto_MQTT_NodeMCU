#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Wi-Fi
const char* ssid = "Fransley";
const char* password = "12345678";

// MQTT
const char* mqtt_server = "192.168.43.87";
const int mqtt_port = 1883;

// Tópicos de inscrição (sub)
const char* sub_topics[] = {
  "casa/sala/led/set",
  "casa/cozinha/led/set",
  "casa/quarto1/led/set",
  "casa/quarto2/led/set",
  "casa/varanda/led/set"
};

// Tópicos de publicação (pub)
const char* pub_topics[] = {
  "casa/sala/led/status",
  "casa/cozinha/led/status",
  "casa/quarto1/led/status",
  "casa/quarto2/led/status",
  "casa/varanda/led/status"
};

// Pinos dos LEDs (de acordo com a ordem dos tópicos)
const uint8_t led_pins[] = {
  D4,  // Sala
  D5,  // Cozinha
  D6,  // Quarto 1
  D7,  // Quarto 2
  D8   // Varanda
};

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  Serial.print("Conectando na rede Wi-Fi: ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Wi-Fi conectado! IP: ");
  Serial.println(WiFi.localIP());
}

// Função chamada ao receber mensagem MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (unsigned int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }
  msg.toUpperCase();

  // Verifica qual índice do tópico recebido
  for (unsigned int i = 0; i < sizeof(sub_topics) / sizeof(sub_topics[0]); i++) {
    if (String(topic) == String(sub_topics[i])) {
      if (msg == "ON") {
        digitalWrite(led_pins[i], HIGH);
        Serial.print("[" + String(topic) + "] → LED ligado\n");
      } else if (msg == "OFF") {
        digitalWrite(led_pins[i], LOW);
        Serial.print("[" + String(topic) + "] → LED desligado\n");
      } else {
        Serial.print("Comando desconhecido: ");
        Serial.println(msg);
      }

      // Publica o status no tópico correspondente
      client.publish(pub_topics[i], msg.c_str(), true);
      break; // não precisa continuar o loop
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    String clientId = "NodeMCU-";
    clientId += String(random(0xffff), HEX);
    Serial.print("Tentando conectar ao broker MQTT... ID = ");
    Serial.println(clientId);

    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado ao broker!");

      // Inscreve em todos os tópicos
      for (unsigned int i = 0; i < sizeof(sub_topics) / sizeof(sub_topics[0]); i++) {
        client.subscribe(sub_topics[i]);
        Serial.print("Inscrito no tópico: ");
        Serial.println(sub_topics[i]);
      }
    } else {
      Serial.print("Falha na conexão. Código de erro: ");
      Serial.print(client.state());
      Serial.println(" – tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  delay(50);
  Serial.println();
  Serial.println("=== Iniciando NodeMCU + MQTT ===");

  // Configura os pinos dos LEDs como saída
  for (unsigned int i = 0; i < sizeof(led_pins) / sizeof(led_pins[0]); i++) {
    pinMode(led_pins[i], OUTPUT);
    digitalWrite(led_pins[i], LOW);  // inicia desligado
  }

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
