#include <Servo.h> 
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN            12
#define NUMPIXELS      16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 500;

const int pResistor = A0; 
int sensorValue;  

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;
Servo myservo7;
Servo myservo8;
String commandArray[30]; 
int count = 0;

SoftwareSerial wifiSerial(0, 1);      // RX, TX for ESP8266

bool DEBUG = true;   //show more logs
int responseTime = 10; //communication timeout

void getUp(){
    myservo1.attach(8);
    myservo2.attach(9);
    myservo3.attach(2);
    myservo4.attach(3);
    myservo5.attach(4);
    myservo6.attach(5);
    myservo7.attach(6);
    myservo8.attach(7);
    myservo1.write(10);
    myservo2.write(170);
    myservo3.write(170);
    myservo4.write(10);
    myservo5.write(45);
    myservo6.write(45);
    myservo7.write(135);
    myservo8.write(45);
    delay(1000);
}

void addCommand(String command){
  if(count<30){
    commandArray[count++] = command;
  }
}

String getCommand(){
  String cmd = "";
  if(count>0){
    cmd = commandArray[--count];
  }
  return cmd;
}

void duck(){
    myservo1.write(60);
    myservo2.write(170);
    myservo3.write(110);
    myservo4.write(10);
    myservo5.write(45);
    myservo6.write(45);
    myservo7.write(135);
    myservo8.write(45);
    delay(500);
}

void wave(){
    duck();
    myservo2.write(10);
    delay(500);
    myservo6.write(45);
    delay(300);
    myservo6.write(135);
    delay(300);
    myservo6.write(45);
    delay(300);
    myservo6.write(135);
    delay(300);
    myservo6.write(45);
    delay(300);
    myservo2.write(170);
    delay(5000);
}

void getDown(){
    myservo1.write(60);
    myservo2.write(120);
    myservo3.write(120);
    myservo4.write(60);
    myservo5.write(45);
    myservo6.write(45);
    myservo7.write(135);
    myservo8.write(45);
    delay(1500);
    getUp();
    
}

void moveForward(){
  delay(1000);
  liftLeg(8);
  delay(100);
  moveLeg(4, "FORWARD");
  delay(100);
  lowerLeg(8);
  delay(100);
  liftLeg(9);
  delay(100);
  moveLeg(5, "FORWARD");
  delay(100);
  lowerLeg(9);
  delay(100);
  liftLeg(3);
  delay(100);
  moveLeg(7, "BACK");
  delay(100);
  lowerLeg(3);
  delay(100);
  liftLeg(2);
  delay(100);
  moveLeg(6, "FORWARD");
  delay(100);
  lowerLeg(2);
  delay(300);
  moveLeg(4, "BACK");
  moveLeg(7, "FORWARD");
  moveLeg(5, "BACK");
  moveLeg(6, "BACK");
  delay(500);
}

void moveBackwords(){
  delay(1000);
  liftLeg(8);
  delay(100);
  moveLeg(4, "BACK");
  delay(100);
  lowerLeg(8);
  delay(100);
  liftLeg(9);
  delay(100);
  moveLeg(5, "BACK");
  delay(100);
  lowerLeg(9);
  delay(100);
  liftLeg(3);
  delay(100);
  moveLeg(7, "FORWARD");
  delay(100);
  lowerLeg(3);
  delay(100);
  liftLeg(2);
  delay(100);
  moveLeg(6, "BACK");
  delay(100);
  lowerLeg(2);
  delay(300);
  moveLeg(4, "FORWARD");
  moveLeg(7, "BACK");
  moveLeg(5, "FORWARD");
  moveLeg(6, "FORWARD");
  delay(500);
}

void moveLeft(){
  delay(1000);
  liftLeg(8);
  delay(100);
  moveLeg(4, "FORWARD");
  delay(100);
  lowerLeg(8);
  delay(100);
  liftLeg(9);
  delay(100);
  moveLeg(5, "FORWARD");
  delay(100);
  lowerLeg(9);
  delay(100);
  liftLeg(3);
  delay(100);
  moveLeg(7, "FORWARD");
  delay(100);
  lowerLeg(3);
  delay(100);
  liftLeg(2);
  delay(100);
  moveLeg(6, "BACK");
  delay(100);
  lowerLeg(2);
  delay(300);
  moveLeg(4, "BACK");
  moveLeg(7, "BACK");
  moveLeg(5, "BACK");
  moveLeg(6, "FORWARD");
  delay(500);
}

void moveRight(){
  delay(1000);
  liftLeg(8);
  delay(100);
  moveLeg(4, "BACK");
  delay(100);
  lowerLeg(8);
  delay(100);
  liftLeg(9);
  delay(100);
  moveLeg(5, "BACK");
  delay(100);
  lowerLeg(9);
  delay(100);
  liftLeg(3);
  delay(100);
  moveLeg(7, "BACK");
  delay(100);
  lowerLeg(3);
  delay(100);
  liftLeg(2);
  delay(100);
  moveLeg(6, "FORWARD");
  delay(100);
  lowerLeg(2);
  delay(300);
  moveLeg(4, "FORWARD");
  moveLeg(7, "FORWARD");
  moveLeg(5, "FORWARD");
  moveLeg(6, "BACK");
  delay(500);
}

void liftLeg(int pin){
  switch(pin){
    case 8: myservo1.write(45); break;
    case 9: myservo2.write(135); break;
    case 2: myservo3.write(135); break;
    case 3: myservo4.write(45); break;
  }
}

void lowerLeg(int pin){
  if(pin == 8){
    myservo1.write(10);
  }else if(pin == 3) {
    myservo4.write(10);
  }else if(pin ==9){
    myservo2.write(170);
  }else if(pin == 2){
    myservo3.write(170);
  }
}

void moveLeg(int pin, String direction){
  if(direction == "FORWARD"){
    switch(pin){
        case 2: myservo3.write(90);break;
        case 3: myservo4.write(90);break;
        case 4: myservo5.write(90);break;
        case 5: myservo6.write(90);break;
        case 6: myservo7.write(45);break;
        case 7: myservo8.write(90);break;
        case 8: myservo1.write(90);break;
        case 9: myservo2.write(90);break;
      }
  }else if(direction == "BACK"){
    if(pin == 6){
      myservo7.write(180);
    } else {
      switch(pin){
        case 2: myservo3.write(0);break;
        case 3: myservo4.write(45);break;
        case 4: myservo5.write(0);break;
        case 5: myservo6.write(0);break;
        case 7: myservo8.write(0);break;
        case 8: myservo1.write(45);break;
        case 9: myservo2.write(45);break;
      }
    }
  }
}

void returnToStart(){
    for (int i = 0; i < sizeof(commandArray); i++){
      String command = String(getCommand());
      if(command){
        if(command.equals("LEFT")){
          moveRight();
        } else if(command.equals("RIGHT")){
          moveLeft();
        } else if(command.equals("FORWARD")){
          moveBackwords();
        } else if(command.equals("BACK")){
          moveForward();
        } else if(command.equals("WAVE")){
          wave();
        } else if(command.equals("DUCK")){
          duck();
        }
       }
    }
}

void ledOn(){
    for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i, pixels.Color(255,255,255));
      pixels.show();
      delay(delayval);
    }
}

void ledOff(){
    for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i, pixels.Color(0,0,0));
      pixels.show();
      delay(delayval);
    }
}

/*
* Name: sendData
* Description: Function used to send string to tcp client using cipsend
* Params: 
* Returns: void
*/
void sendData(String str){
  String len="";
  len+=str.length();
  sendToWifi("AT+CIPSEND=0,"+len,responseTime,DEBUG);
  delay(100);
  sendToWifi(str,responseTime,DEBUG);
  delay(100);
  sendToWifi("AT+CIPCLOSE=5",responseTime,DEBUG);
 sendToUno(str, responseTime, DEBUG);
}


/*
* Name: find
* Description: Function used to match two string
* Params: 
* Returns: true if match else false
*/
boolean find(String string, String value){
  if(string.indexOf(value)>=0)
    return true;
  return false;
}


/*
* Name: readSerialMessage
* Description: Function used to read data from Arduino Serial.
* Params: 
* Returns: The response from the Arduino (if there is a reponse)
*/
String  readSerialMessage(){
  char value[100]; 
  int index_count =0;
  while(Serial.available()>0){
    value[index_count]=Serial.read();
    index_count++;
    value[index_count] = '\0'; // Null terminate the string
  }
  String str(value);
  str.trim();
  return str;
}



/*
* Name: readWifiSerialMessage
* Description: Function used to read data from ESP8266 Serial.
* Params: 
* Returns: The response from the esp8266 (if there is a reponse)
*/
String  readWifiSerialMessage(){
  char value[100]; 
  int index_count =0;
  while(wifiSerial.available()>0){
    value[index_count]=wifiSerial.read();
    index_count++;
    value[index_count] = '\0'; // Null terminate the string
  }
  String str(value);
  str.trim();
  return str;
}



/*
* Name: sendToWifi
* Description: Function used to send data to ESP8266.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the esp8266 (if there is a reponse)
*/
String sendToWifi(String command, const int timeout, boolean debug){
  String response = "";
  wifiSerial.println(command); // send the read character to the esp8266
  long int time = millis();
  while( (time+timeout) > millis())
  {
    while(wifiSerial.available())
    {
    // The esp has data so display its output to the serial window 
    char c = wifiSerial.read(); // read the next character.
    response+=c;
    }  
  }
  if(debug)
  {
    Serial.println(response);
  }
  return response;
}

/*
* Name: sendToWifi
* Description: Function used to send data to ESP8266.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the esp8266 (if there is a reponse)
*/
String sendToUno(String command, const int timeout, boolean debug){
  String response = "";
  Serial.println(command); // send the read character to the esp8266
  long int time = millis();
  while( (time+timeout) > millis())
  {
    while(Serial.available())
    {
      // The esp has data so display its output to the serial window 
      char c = Serial.read(); // read the next character.
      response+=c;
    }  
  }
  if(debug)
  {
    Serial.println(response);
  }
  return response;
}

void setup()
{
  pinMode(pResistor, INPUT);
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  pixels.begin(); 
  
  getUp();
  delay(2000);
  // Open serial communications and wait for port to open esp8266:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  wifiSerial.begin(115200);
  while (!wifiSerial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  sendToWifi("AT+CWMODE=2",responseTime,DEBUG); // configure as access point
  sendToWifi("AT+CIFSR",responseTime,DEBUG); // get ip address
  sendToWifi("AT+CIPMUX=1",responseTime,DEBUG); // configure for multiple connections
  sendToWifi("AT+CIPSERVER=1,80",responseTime,DEBUG); // turn on server on port 80
 
  sendToUno("Wifi connection is running!",responseTime,DEBUG);
}

void loop()
{
  sensorValue = analogRead(pResistor);
  if (sensorValue > 250){
    ledOff();  
  }
  else{
    ledOn(); 
  } 

  if(Serial.available()>0){
     String message = readSerialMessage();
    if(find(message,"debugEsp8266:")){
      String result = sendToWifi(message.substring(13,message.length()),responseTime,DEBUG);
      if(find(result,"OK"))
        sendData("\nOK");
      else
        sendData("\nEr");
    }
  }
  if(wifiSerial.available()>0){
    
    String message = readWifiSerialMessage();
    
    if(find(message,"esp8266:")){
       String result = sendToWifi(message.substring(8,message.length()),responseTime,DEBUG);
      if(find(result,"OK"))
        sendData("\n"+result);
      else
        sendData("\nErrRead");               //At command ERROR CODE for Failed Executing statement
    }else
    if(find(message,"LEFT")){  //receives LEFT from wifi
        addCommand("LEFT");
        moveLeft(); //Robot moves LEFT
    }else if(find(message,"RIGHT")){
        addCommand("RIGHT");
        moveRight();
    }else if(find(message,"FORWARD")){
        addCommand("FORWARD");
        moveForward();
    }else if(find(message,"BACK")){
        addCommand("BACK");
        moveBackwords();
    }else if(find(message,"WAVE")){
        addCommand("WAVE");
        wave();
    }else if(find(message,"DUCK")){
        addCommand("DUCK");
        duck();
    }else if(find(message,"LEDOFF")){
        ledOff();
    }else if(find(message,"LEDON")){
        ledOn();
    }else if(find(message,"6")){
        returnToStart();
    }else{
      sendData("\nErrRead");                 //Command ERROR CODE for UNABLE TO READ
    }
  }
  delay(responseTime);
}
