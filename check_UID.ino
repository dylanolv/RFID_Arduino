#include <SPI.h> // On inclut les bibliothèques
#include <RFID.h> // On inclut les bibliothèques
// #include <stdlib.h>

RFID monModuleRFID(10,9); // On déclare l'utilisation de notre module RFID

int UID[5]; // Variable qui contiendra le numéro d'indentification détecté
int MASTERKEY[5]={204,248,170,137,23}; // Variable contenant la suite décimale autorisée

void setup()
{
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  Serial.begin(9600);
  SPI.begin(); // Débute la communication SPI
  monModuleRFID.init();  // On initialise le module RFID

}

void loop()
{
    if (monModuleRFID.isCard()) {  // On vérifie la présence d'un tag
          if (monModuleRFID.readCardSerial()) { // Si il y en a un...
            Serial.print("L'UID est: ");
            for(int i=0;i<=4;i++) // On affiche son UID
            {
              UID[i]=monModuleRFID.serNum[i];
              Serial.print(UID[i],DEC);
              Serial.print(".");
            }
            Serial.println("");
          }

          if (UID[0] == MASTERKEY[0]
           && UID[1] == MASTERKEY[1]
           && UID[2] == MASTERKEY[2]
           && UID[3] == MASTERKEY[3]
           && UID[4] == MASTERKEY[4])
          { // Si l'UID détecté correspond à la suite décimale autorisée, on affiche un message de succès et on allume la diode verte
              
              digitalWrite(6,HIGH);
              Serial.print("Accès autorisé !\n");
              delay(500);
              digitalWrite(6,LOW);    
              // System.Diagnostics.Process.Start("http://www.google.fr");      
          }
          else // Sinon, on affiche un mesage d'erreur et on allume la diode rouge
          {
              digitalWrite(7,HIGH);
              Serial.print("Accès refusé !\n");
              delay(500);
              digitalWrite(7,LOW);
          }          

                    
          monModuleRFID.halt();
    }
    delay(1);    
}
