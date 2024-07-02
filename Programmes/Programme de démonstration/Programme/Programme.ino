/*
   "MODULE CHRONOMÈTRE POUR ARDUINO PB300" Pierron référence 33177
   Programme V1.0 : "Programme"
   Rédacteur : M. PAUL Pierre 2024

    L'utilisation d'une carte non officielle nécessite la configuration "Old Booltloader" !
*/

// Déclaration de la bibliothèque.
#include <Pierron_33177.h>

// Initialisation et définition de l'objet écran LCD.
LiquidCrystal_I2C Ecran_LCD(0x20, 20, 4);

// Déclarations des entrées et sorties.
#define DEL_VERTE 4
#define DEL_ROUGE 2
#define BUZZER 6
#define PHOTODIODE_1 A0
#define PHOTODIODE_2 A1

void setup() {
  // Définition de la vitesse de communication de la liaison USB.
  Serial.begin(115200);
  delay(1000);
  // Définition des entées et des sorties de la carte Arduino NANO.
  pinMode(PHOTODIODE_1, INPUT);
  pinMode(PHOTODIODE_2, INPUT);
  pinMode(DEL_VERTE, OUTPUT);
  pinMode(DEL_ROUGE, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Ecran_LCD.init();
  Ecran_LCD.backlight();
  Ecran_LCD.clear();
  Ecran_LCD.setCursor(0, 0);
  Ecran_LCD.print("   CHRONOMETREZ");
  Ecran_LCD.setCursor(0, 1);
  Ecran_LCD.print("  une course avec");
  Ecran_LCD.setCursor(0, 2);
  Ecran_LCD.print(" le microcontroleur");
  Ecran_LCD.setCursor(6, 3);
  Ecran_LCD.print("ARDUINO");
  delay(4000);
  Ecran_LCD.clear();
  Ecran_LCD.setCursor(0, 0);
  Ecran_LCD.print("   Lachez l'objet   ");
  Ecran_LCD.setCursor(0, 1);
  Ecran_LCD.print("    sur la rampe    ");
  Ecran_LCD.setCursor(0, 2);
  Ecran_LCD.print("   de la maquette ");
  Ecran_LCD.setCursor(0, 3);
  Ecran_LCD.print("       PB300    ");
}

void loop() {
  float Pointage_Milliseconde_Demarrage;
  float Durees_Ecoulees;
  if (analogRead(PHOTODIODE_1) < 900) {
    Pointage_Milliseconde_Demarrage = millis();
    digitalWrite(DEL_VERTE, 0);
    digitalWrite(DEL_ROUGE, 1);
    tone(BUZZER, 600, 100);
    while (analogRead(PHOTODIODE_2) > 900) {
    }
    Durees_Ecoulees = (millis() - Pointage_Milliseconde_Demarrage) / 1000.0;
    tone(BUZZER, 600, 100);
    Ecran_LCD.clear();
    Ecran_LCD.setCursor(0, 1);
    Ecran_LCD.print("   duree = " + String(Durees_Ecoulees, 3) + " s");
    Ecran_LCD.setCursor(0, 3);
    Ecran_LCD.print("* Relancez l'objet *");
    Serial.println(String(Durees_Ecoulees, 3));
  }
  else {
    digitalWrite(DEL_VERTE, 1);
    digitalWrite(DEL_ROUGE, 0);
  }
}
