//Note:  You will need to provide lightMasterConfig.h which contains SSID, SSID Password, and your lifx application secret.
/*TODO:
 * maybe take out all the serial writes.
 * Add error colors for wifi connect.
 *  For error, create second array with only red and pass that to startup look.  Change that to statusLights or something like that.
*/

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "lightMasterConfig.h"
#include <Adafruit_NeoPixel.h>

const int redButtonPin = 12;
const int blueButtonPin = 13;
const int yellowButtonPin = 15;
const int goButtonPin = 14;
const int neoPixelPin = 2;

const int numberOfPixels = 16;

Adafruit_NeoPixel previewRing = Adafruit_NeoPixel(numberOfPixels, neoPixelPin);

const uint32_t red = previewRing.Color(128, 0, 0);
const uint32_t blue = previewRing.Color(0, 0, 128);
const uint32_t yellow = previewRing.Color(128, 128, 0);
const uint32_t green = previewRing.Color(0, 128, 0);
const uint32_t purple = previewRing.Color(128, 0, 128);
const uint32_t orange = previewRing.Color(128, 32, 0);
const uint32_t off = previewRing.Color(0, 0, 0, 0);
const uint32_t white = previewRing.Color(32, 32, 32);

uint32_t colors[] = {red,yellow,green,blue};

String currentColor = "white";

int redButtonState = 0;
int blueButtonState = 0;
int yellowButtonState = 0;
int goButtonState = 0;

void setup()
{
    previewRing.setBrightness(64);
    previewRing.begin();
    startupLook(colors);
    //updatePreview(off);
    //previewRing.show();

    pinMode(redButtonPin, INPUT);
    pinMode(blueButtonPin, INPUT);
    pinMode(yellowButtonPin, INPUT);
    pinMode(goButtonPin, INPUT);

    connectToWifi(SSID, SSID_PASSWORD);

    turnOnLights(LIFXSELECTOR);
    sendColor(LIFXSELECTOR, currentColor);
}

void loop()
{
    redButtonState = digitalRead(redButtonPin);
    blueButtonState = digitalRead(blueButtonPin);
    yellowButtonState = digitalRead(yellowButtonPin);
    goButtonState = digitalRead(goButtonPin);

    if (redButtonState == HIGH) {
        if (currentColor == "white") {
            updatePreview(red);
            currentColor = "red";
        }
        else if (currentColor == "blue"){
            updatePreview(purple);
            currentColor = "purple";
        }
        else if (currentColor == "yellow"){
            updatePreview(orange);
            currentColor = "orange";
        }
        //delay(500);
    }

    if (blueButtonState == HIGH) {
        if (currentColor == "white"){
            updatePreview(blue);
            currentColor = "blue";
        }
        else if (currentColor == "red"){
            updatePreview(purple);
            currentColor = "purple";
        }
        else if (currentColor == "yellow"){
            updatePreview(green);
            currentColor = "green";
        }
        //delay(500);
    }

    if (yellowButtonState == HIGH) {
        if (currentColor == "white"){
            updatePreview(yellow);
            currentColor = "yellow";
        }
        else if (currentColor == "blue"){
            updatePreview(green);
            currentColor = "green";
        }
        else if (currentColor == "red") {
            updatePreview(orange);
            currentColor = "orange";
        }
        //delay(500);
    }

    if (goButtonState == HIGH) {
        sendColor(LIFXSELECTOR, currentColor);
        updatePreview(white);
        currentColor = "white";
        delay(500);
    }
}

//TODO Why doesn't using the passed in variables work?
void connectToWifi(String ssid, String ssid_password)
{
    Serial.begin(115200);
    Serial.println();
    Serial.print("connecting to ");
    Serial.println(ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, SSID_PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    updatePreview(white);
}

void turnOnLights(String selector){
    String body = "{\"power\":\"on\",\"fast\":true}";
    WiFiClientSecure client;
    Serial.print("connecting to ");
    Serial.println(HOST);
    if (!client.connect(HOST, SSL_PORT))
    {
        Serial.println("connection failed");
        return;
    }

    String url = "/v1/lights/" + selector + "/state";
    Serial.print("requesting URL: ");
    Serial.println(url);

    client.print(String("PUT ") + url + " HTTP/1.1\r\n" +
                 "Host: " + HOST + "\r\n" +
                 "Authorization: Bearer " + AUTH_TOKEN + "\r\n" +
                 "Connection: close\r\n" +
                 "Content-Type: application/json\r\n" +
                 "Content-Length: " + body.length() + "\r\n\r\n" +
                 body + "\r\n");

    Serial.println("request sent");

    while (client.connected() || client.available())
    {
        if (client.available())
        {
            String line = client.readStringUntil('\n');
            Serial.println(line);
        }
    }
    client.stop();
    Serial.println("\n[Disconnected]");
}

void sendColor(String selector, String newColor){
    String body = "{\"color\":\"" + newColor + "\",\"fast\":true}";
    WiFiClientSecure client;
    Serial.print("connecting to ");
    Serial.println(HOST);
    if (!client.connect(HOST, SSL_PORT))
    {
        Serial.println("connection failed");
        return;
    }

    String url = "/v1/lights/" + selector + "/state";
    Serial.print("requesting URL: ");
    Serial.println(url);

    client.print(String("PUT ") + url + " HTTP/1.1\r\n" +
                 "Host: " + HOST + "\r\n" +
                 "Authorization: Bearer " + AUTH_TOKEN + "\r\n" +
                 "Connection: close\r\n" +
                 "Content-Type: application/json\r\n" +
                 "Content-Length: " + body.length() + "\r\n\r\n" +
                 body + "\r\n");

    Serial.println("request sent");

    while (client.connected() || client.available())
    {
        if (client.available())
        {
            String line = client.readStringUntil('\n');
            Serial.println(line);
        }
    }
    client.stop();
    Serial.println("\n[Disconnected]");
}

void updatePreview(uint32_t newColor){
    for (int i=0; i<numberOfPixels; i++){
        previewRing.setPixelColor(i, newColor);
        previewRing.show();
        delay(75);
    }
}

void startupLook(uint32_t listOfColors[]){
    for (int i=0; i<sizeof(listOfColors); i++){
        for (int j=i; j<numberOfPixels; j=j+4){
            previewRing.setPixelColor(j, listOfColors[i]);
            previewRing.show();
            delay(75);
        }
    }
}