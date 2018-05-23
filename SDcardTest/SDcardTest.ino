#include <SD.h>

File myFile;

void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.print("Initializing SD card...");

   pinMode(10, OUTPUT);

    while (!SD.begin(4)) {
    Serial.println("ERROR: Can't open the SD card - retrying in 10 seconds");
    delay(5000);
  }
//  if (!SD.begin(4)) {
//    Serial.println("initialization failed!");
//    return;
//  }
//  Serial.println("initialization done.");
  

  myFile = SD.open("test.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("Hello world");
    myFile.println("Im Bob");
   // close the file:
    myFile.close();
    Serial.println("done.");
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
  

void loop()
{
   // nothing happens after setup
}
