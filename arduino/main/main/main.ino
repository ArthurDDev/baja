#include "SoftwareSerial.h"
#include "TinyGPS.h"
#include "WiFiEsp.h" 

SoftwareSerial serial1(10, 11); // RX, TX para ESP8266
TinyGPS gps1;

char ssid[] = "NOME_DA_SUA_REDE_WIFI"; // Nome da rede Wi-Fi
char pass[] = "SENHA_DA_SUA_REDE_WIFI"; // Senha da rede Wi-Fi

int status = WL_IDLE_STATUS; // Status da conexão Wi-Fi

WiFiEspServer server(80); // Inicializa o servidor na porta 80

void setup() {
   serial1.begin(9600); // Inicia a comunicação com ESP8266
   Serial.begin(9600); // Comunicação com o computador
   WiFi.init(&serial1); // Inicializa o Wi-Fi com ESP8266
   WiFi.config(IPAddress(192,168,0,110)); // Configura o IP disponível no roteador

   Serial.println("O GPS aguarda pelo sinal dos satélites...");

   // Conecta o ESP8266 à rede Wi-Fi
   if(WiFi.status() == WL_NO_SHIELD) {
      Serial.println("ESP8266 não conectado.");
      while (true);
   }
   
   while(status != WL_CONNECTED) {
      status = WiFi.begin(ssid, pass);
      Serial.print("Tentando conectar ao Wi-Fi...");
      delay(1000);
   }
   
   Serial.println("Conectado ao Wi-Fi!");
   server.begin(); // Inicia o servidor web
}

void loop() {
   bool recebido = false;

   // Recebe dados do GPS
   while (serial1.available()) {
      char cIn = serial1.read();
      recebido = gps1.encode(cIn);
   }

   if (recebido) {
      Serial.println("----------------------------------------");

      // Latitude e Longitude
      long latitude, longitude;
      unsigned long idadeInfo;
      gps1.get_position(&latitude, &longitude, &idadeInfo);

      if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
         Serial.print("Latitude: ");
         Serial.println(float(latitude) / 100000, 6);
      }

      if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
         Serial.print("Longitude: ");
         Serial.println(float(longitude) / 100000, 6);
      }

      // Exibe data e hora
      int ano;
      byte mes, dia, hora, minuto, segundo, centesimo;
      gps1.crack_datetime(&ano, &mes, &dia, &hora, &minuto, &segundo, &centesimo, &idadeInfo);

      Serial.print("Data (GMT): ");
      Serial.print(dia); Serial.print("/"); Serial.print(mes); Serial.print("/"); Serial.println(ano);
      Serial.print("Horário (GMT): ");
      Serial.print(hora); Serial.print(":"); Serial.print(minuto); Serial.print(":"); Serial.println(segundo);
      
      WiFiEspClient client = server.available(); // Atende as requisições HTTP

      if (client) {
         // Envia os dados de GPS como resposta HTTP
         sendHttpResponse(client, latitude, longitude, dia, mes, ano, hora, minuto, segundo);
         client.stop(); // Finaliza a requisição e desconecta o cliente
      }
   }
}

// Função para enviar resposta HTTP ao cliente
void sendHttpResponse(WiFiEspClient client, long latitude, long longitude, int dia, int mes, int ano, int hora, int minuto, int segundo) {
   client.println("HTTP/1.1 200 OK");
   client.println("Content-Type: text/html");
   client.println("");
   client.println("<!DOCTYPE HTML>");
   client.println("<html>");
   client.println("<head><title>Dados do GPS</title></head>");
   client.println("<body>");
   client.println("<h1>Dados do GPS</h1>");
   client.print("<p>Latitude: "); client.print(float(latitude) / 100000, 6); client.println("</p>");
   client.print("<p>Longitude: "); client.print(float(longitude) / 100000, 6); client.println("</p>");
   client.print("<p>Data (GMT): "); client.print(dia); client.print("/"); client.print(mes); client.print("/"); client.print(ano); client.println("</p>");
   client.print("<p>Horário (GMT): "); client.print(hora); client.print(":"); client.print(minuto); client.print(":"); client.print(segundo); client.println("</p>");
   client.println("</body>");
   client.println("</html>");
}

