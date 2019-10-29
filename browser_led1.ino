#include <ESP8266WiFi.h>
#define LED D2
const char* ssid = "fmdx";
const char* password = "fmd12345";
unsigned char status_led=0;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  Serial.println("new client");
  while(!client.available())
  {
    delay(1);
  }
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  if (req.indexOf("/ledoff") != -1)
  {
    status_led=0;   
    digitalWrite(LED,LOW);
    Serial.println("LED OFF");
  }
  else if(req.indexOf("/ledon") != -1)
  {
    status_led=1;
    digitalWrite(LED,HIGH);
    Serial.println("LED ON");
  }

  String web ="<!doctype html> <html lang=\"en\"> <head> <!-- Required meta tags --> <meta charset=\"utf-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\"> <!-- Bootstrap CSS --> <link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\" integrity=\"sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T\" crossorigin=\"anonymous\"> <link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css\"> <title>Web Server Control</title> <style> a { width: 100; } </style> </head> <body> <div class=\"container-fluid\"> <div class=\"row\"> <div class=\"col-md-12 p-0\"> <div class=\"jumbotron jumbotron-fluid\"> <div class=\"container\"> <h1 class=\"display-4\">This is Basic ESP 8266 IOT Dimmer Project</h1> <p class=\"lead\">We are targeted to understand communications between lamps and smart embeded boards.</p> </div> </div> </div> </div> <div class=\"row justify-content-end \"> <div class=\"col-md-6\"> <h4 class=\"d-flex justify-content-end pr-3\">ON</h4> <div class=\"d-flex justify-content-end\"> <a href=\"ledon\" class=\"btn btn-success justify-content-end \"> <i class=\"fa fa-lightbulb-o fa-5x\" aria-hidden=\"true\"></i> </a> </div> </div> <div class=\"col-md-6\"> <h4 class=\"pl-3\">OFF</h4> <a href=\"ledoff\" class=\"btn btn-danger \"> <i class=\"fa fa-lightbulb-o fa-5x\" aria-hidden=\"true\"></i> </a> </div> </div> </div> <!-- Optional JavaScript --> <!-- jQuery first, then Popper.js, then Bootstrap JS --> <script src=\"https://code.jquery.com/jquery-3.3.1.slim.min.js\" integrity=\"sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo\" crossorigin=\"anonymous\"></script> <script src=\"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js\" integrity=\"sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1\" crossorigin=\"anonymous\"></script> <script src=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js\" integrity=\"sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM\" crossorigin=\"anonymous\"></script> </body> </html>";
  client.print(web);
}
