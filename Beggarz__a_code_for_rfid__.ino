// WELCOME TO THE BEGGARZ <SMR.Robotics>
//SUBSCRIBE LIKE SHARE 


#include <SPI.h>//DESCRIBE THE LIBRARY
#include <MFRC522.h>//DESCRIBE THE LIBRARY FOR RFID MODULE  
#include <Servo.h>//DESCRIBE THE LIBRARY FOR SERVO MOTOR 
 
#define SS_PIN 9// SDA
#define RST_PIN 10//RESET
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo S1; //WRITE A NAME FOR SERVO
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  S1.attach(8); //servo pin
  S1.write(0); //SERVO INITIAL POSITION
  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop() 
{
  // LOOK FOR CARD  WHICH YOU HAVE
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // SELECT ONE CARD AND SHOW ON RFID MODULE DETECTOR PART
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //SEE THE UID DISPLAYED ON SERIAL MONITOR AND COPY IT 
  Serial.print("YOUR UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "03 A4 8A FB") //REMOVE THE UID HIGHLITED AND REPLACE THE COPIED UID
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(500);
    S1.write(90);//OPEN THE TOLL
    delay(5000);
    S1.write(0);//CLOSE THE TOLL
  }
 
 else   {
    Serial.println(" Access denied");
       S1.write(0);//CLOSE THE TOLL
  }
}
