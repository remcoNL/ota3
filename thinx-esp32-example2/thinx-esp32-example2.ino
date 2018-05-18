#include <PubSubClient.h>

#include <Arduino.h>
#include <THiNX32Lib.h>

#define __DEBUG__
#define ARDUINO_IDE

const char *apikey = "8101213fcbb336408409c715345c7ce951c13315bd847dfd5e73a33dbe5d8188";
const char *owner_id = "0cdf3006f7b27239256fb084e5a1c34d28e2f9950aec7a2d99ecc480489dfb6d";
const char *ssid = "Schimmeldraad";
const char *pass = "varkentje";

THiNX thx;

/* Called after library gets connected and registered */
void finalizeCallback () {
  Serial.println("*INO: Finalize callback called. Will fall asleep.");
  //ESP.deepSleep(3e9);
}

void setup() {
pinMode(2, OUTPUT);
  Serial.begin(115200);

#ifdef __DEBUG__
  while (!Serial); // wait for debug console connection
  Serial.println("Connecting to predefined WiFi...");
  WiFi.begin(ssid, pass);
#endif

  // Enter API Key and Owner ID (should be faster)
  thx = THiNX(apikey, owner_id);
  thx.setFinalizeCallback(finalizeCallback);
}

/* Loop must call the thx.loop() in order to pickup MQTT messages and advance the state machine. */
void loop()
{
  thx.loop();
  digitalWrite(2, HIGH);
  delay(400);
  digitalWrite(2, LOW);
}
