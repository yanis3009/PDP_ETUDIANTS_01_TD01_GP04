#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 33     // Pin numérique connectée au capteur DHT
#define DHTTYPE DHT11 // Type de capteur DHT (peut être DHT11 ou DHT22)

DHT_Unified dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialisation du moniteur série et du capteur DHT
  Serial.begin(9600);
  dht.begin();
  
  // Affichage des détails du capteur de température
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Capteur de température"));
  Serial.print(F("Nom du capteur: ")); Serial.println(sensor.name);
  Serial.print(F("Version du driver: ")); Serial.println(sensor.version);
  Serial.print(F("ID unique: ")); Serial.println(sensor.sensor_id);
  Serial.print(F("Valeur max: ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print(F("Valeur min: ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print(F("Résolution: ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));

  // Affichage des détails du capteur d'humidité
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Capteur d'humidité"));
  Serial.print(F("Nom du capteur: ")); Serial.println(sensor.name);
  Serial.print(F("Version du driver: ")); Serial.println(sensor.version);
  Serial.print(F("ID unique: ")); Serial.println(sensor.sensor_id);
  Serial.print(F("Valeur max: ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print(F("Valeur min: ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print(F("Résolution: ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));

  // Lire la température
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Erreur de lecture de la température!"));
  } else {
    Serial.print(F("Température: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }

  // Lire l'humidité
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Erreur de lecture de l'humidité!"));
  } else {
    Serial.print(F("Humidité: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }

  // Configurer un réveil après 5 secondes
  esp_sleep_enable_timer_wakeup(5000000); // 5 secondes en microsecondes
  Serial.println(F("Entrée en mode Deep Sleep..."));
  delay(100);
  // Passer en mode Deep Sleep
  esp_deep_sleep_start(); // Entrer en Deep Sleep
}

void loop() {
  // La fonction loop est vide car tout se passe dans setup() avec Deep Sleep
}
