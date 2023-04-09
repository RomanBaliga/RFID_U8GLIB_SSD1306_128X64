#include <SPI.h>
#include <RFID.h>
#include "U8glib.h"


#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN); 


U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

unsigned long ActualTime; 
unsigned long LastTime;


// Setup variables:
    int serNum0;
    int serNum1;
    int serNum2;
    int serNum3;
    int serNum4;

String TEXT = "AHOJ";

//*********************************************************************************

void DRAW() {
    u8g.firstPage();  
      do {        
        u8g.setPrintPos(20, 10); 
        u8g.print("ID Card Reader"); 

        u8g.setPrintPos(0, 25); 
        u8g.print("Hex:"); 

        u8g.setPrintPos(0, 37); 
        u8g.print(serNum0,HEX); u8g.print(".");
        u8g.print(serNum1,HEX); u8g.print(".");
        u8g.print(serNum2,HEX); u8g.print(".");
        u8g.print(serNum3,HEX); u8g.print(".");
        u8g.print(serNum4,HEX); 

        u8g.setPrintPos(0, 50); 
        u8g.print("Dec:");

        u8g.setPrintPos(0, 62); 
        u8g.print(serNum0,DEC); u8g.print(".");
        u8g.print(serNum1,DEC); u8g.print(".");
        u8g.print(serNum2,DEC); u8g.print(".");
        u8g.print(serNum3,DEC); u8g.print(".");
        u8g.print(serNum4,DEC); 
        
      } while( u8g.nextPage() );  
}
    
//*********************************************************************************
void setup()
{ 
  Serial.begin(9600);
  SPI.begin(); 
  rfid.init();
  Serial.println("Ready");

  u8g.setFont(u8g_font_helvR08);

      u8g.firstPage();  
      do {        
        u8g.setPrintPos(20, 10); 
        u8g.print("ID Card Reader"); 

       } while( u8g.nextPage() );  
  

}

//*********************************************************************************
void loop()
{
  ActualTime = millis();

  if ( (ActualTime - LastTime) > 10000 ){ 
      u8g.firstPage();  
      do {        
        u8g.setPrintPos(20, 10); 
        u8g.print("ID Card Reader"); 

       } while( u8g.nextPage() );  
    }  

    if (rfid.isCard()) {
        if (rfid.readCardSerial()) {           
          
                LastTime = millis();
                 
                Serial.println(" ");
                Serial.println("Card found");
                serNum0 = rfid.serNum[0];
                serNum1 = rfid.serNum[1];
                serNum2 = rfid.serNum[2];
                serNum3 = rfid.serNum[3];
                serNum4 = rfid.serNum[4];

                DRAW();

                //Serial.println(" ");
                Serial.println("Cardnumber:");
                Serial.print("Dec: ");
                Serial.print(rfid.serNum[0],DEC);
                Serial.print(", ");
                Serial.print(rfid.serNum[1],DEC);
                Serial.print(", ");
                Serial.print(rfid.serNum[2],DEC);
                Serial.print(", ");
                Serial.print(rfid.serNum[3],DEC);
                Serial.print(", ");
                Serial.print(rfid.serNum[4],DEC);
                Serial.println(" ");

                Serial.print("Hex: ");
                Serial.print(rfid.serNum[0],HEX);
                Serial.print(", ");
                Serial.print(rfid.serNum[1],HEX);
                Serial.print(", ");
                Serial.print(rfid.serNum[2],HEX);
                Serial.print(", ");
                Serial.print(rfid.serNum[3],HEX);
                Serial.print(", ");
                Serial.print(rfid.serNum[4],HEX);
                Serial.println(" ");
 
          }
    }

    rfid.halt();
}
