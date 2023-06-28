#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif

#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#define sensor 14
#define ECHOPIN 13
#define TRIGPIN 12
//int sensorPin = A0;

//Create software serial object to communicate with SIM800L
//SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2

//#include <Adafruit_BME280.h>
WiFiClient wifiClient;
// Replace with your network credentials
const char* ssid     = "Galaxy M30sAF43";
const char* password = "zayn malik";

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://192.168.207.228/sensor_int_data/post-esp-data.php";

// Keep this API Key value to be compatible with the PHP code provided in the project page. 
// If you change the apiKeyValue value, the PHP file /post-esp-data.php also needs to have the same key 
String apiKeyValue = "tPmAT5Ab3j7F9";

String sensorName = "MQ2";
String sensorLocation = "My Room";

int Gas_analog;
int Gas_digital = 0;
#define SEALEVELPRESSURE_HPA (1013.25)
  // I2C
void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  pinMode(sensor, INPUT);
  pinMode(ECHOPIN,INPUT_PULLUP);
  pinMode(TRIGPIN, OUTPUT);
  digitalWrite(ECHOPIN, HIGH);

}
void loop() {
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(wifiClient, serverName);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    float analog = analogRead(Gas_analog);
    int digital = digitalRead(Gas_digital);
    int readings = digitalRead(sensor);
//    int val = analogRead(A0);

    digitalWrite(TRIGPIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGPIN, HIGH);
    delayMicroseconds(15);
    digitalWrite(TRIGPIN, LOW);
    int distance1 = pulseIn(ECHOPIN, HIGH, 26000);
    int distance = distance1/58;
//    
    // Prepare your HTTP POST request data
    String httpRequestData = "api_key=" + apiKeyValue + "&location=" + sensorLocation + "&value1=" + analog
+ "&value2=" + readings + "&value3=" + distance + "";//"&value3=" + distance + 
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    
    // You can comment the httpRequestData variable above
    // then, use the httpRequestData variable below (for testing purposes without the BME280 sensor)
    //String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&location=Office&value1=24.75&value2=49.54&value3=1005.14";
 // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
     
    // If you need an HTTP request with a content type: text/plain
    //http.addHeader("Content-Type", "text/plain");
    //int httpResponseCode = http.POST("Hello, World!");
    
    // If you need an HTTP request with a content type: application/json, use the following:
    //http.addHeader("Content-Type", "application/json");
    //int httpResponseCode = http.POST("{\"value1\":\"19\",\"value2\":\"67\",\"value3\":\"78\"}");
  if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 15 seconds
  delay(60000);  
}
