#include "MeMegaPi.h"

#include "Controlrobot.h"
#include "LineFollower.h"
#include "UltraSonicSensor.h"
#include "AutomaticBehavior.h"
#include "DetectColorSensor.h"
#include "ControlFork.h"
#include "TrueLineFollower.h"
#include "DetectColorPieceSensor.h"


#include <Wire.h>

#include "Config.h"






MeMegaPiDCMotor motor_left (PORT2B) ;
MeMegaPiDCMotor motor_right (PORT1B);
MeMegaPiDCMotor motorFork (PORT3B);
MeLineFollower lineFinder(PORT_5);
MeColorSensor colorsensor1(PORT_7);

MeColorSensor colorsensor0(PORT_8);
MeGyro gyro(PORT_6, 0x68);



Controlrobot robot(motor_left, motor_right);
LineFollower lf(lineFinder);
UltraSonicSensor ultraSonicSensor(&robot);

DetectColorSensor sensorColor(colorsensor0, &robot);
DetectColorPieceSensor sensorColorPiece(colorsensor1, &robot);
ControlFork fork(motorFork, &gyro, &robot);
TrueLineFollower trueLineFollower(lineFinder, &robot);
AutomaticBehavior automaticBehavior(&gyro,&robot, &trueLineFollower, &ultraSonicSensor, &fork, &sensorColorPiece);

unsigned long time1=0;
unsigned long time2=0;

uint8_t mode=0; //2=auto, 1=manuel


int tabCommandes[80];
int numberCommandes;
int indexCommandes=0;
bool commandValid=false;






int tourne=0;

bool state=false;

void clearTabCommandes(){
  for (int i=0; i<50;i++){
    tabCommandes[i]=0;
  }
}



void setup(){

  Serial3.begin(115200);
  Serial.begin(9600);

  gyro.begin();
  //colorsensor0.SensorInit();

  delay(2000);
  //robot.forward(80);
  //time1=millis();
  //fork.downFork();
  //delay(1000);
  fork.upFork();
  fork.middleFork();
  fork.upFork();
}


/********************start of the loop************************/
void loop(){

  /*
  //-------------------------Read serial-------------------

  if(Serial3.available()){
    Serial.println("données reçues");
    String dataRecieved=Serial3.readString();

   Serial.println(dataRecieved);

   if(dataRecieved.toInt()==AUTOMATIC){
     mode=0;
     clearTabCommandes();

   }else if(dataRecieved.toInt()==MANUEL){
     mode=1;
     clearTabCommandes();

     //si on recoit une commande
   }else{
     clearTabCommandes();
     int r=0, t=0;
     numberCommandes=1;
     for (uint8_t i=0; i<dataRecieved.length();i++){
       if(dataRecieved.charAt(i)=='/'){ //split au slash
         tabCommandes[t]=dataRecieved.substring(r,i).toInt();
         r=i+1;
         t++;
         numberCommandes+=1;
       }
     }
     indexCommandes=0;
     Serial.println("traitement terminé");
   }
 }



 //-----------------------end read serial---------------------------/

commandValid=false;

switch (mode){
  //automatic
  case 2:
    switch(tabCommandes[indexCommandes]){
      case 3:
       automaticBehavior.turnLeft90();
       commandValid=true;
       break;

      case 4:
       automaticBehavior.turnRight90();
       commandValid=true;
       break;

      default:
        break;
    }
  //manuel
  case 1:
    switch (tabCommandes[indexCommandes]){
      case FORWARD :
        Serial.println("forward");

        indexCommandes+=1;
        Serial.println(tabCommandes[indexCommandes]);
        robot.forward(tabCommandes[indexCommandes]);
        commandValid=true;
        delay(DELAY_FORWARD);

        break;

      case LEFT :
        robot.left(45);
        commandValid=true;
        delay(DELAY_ROTATION);
        break;

      case RIGHT :
        robot.right(45);
        commandValid=true;
        delay(DELAY_ROTATION);
        break;

      case STOP :
        robot.forward(0);
        commandValid=true;
      default:
        break;
    }

    // no value in array
  default :
    break;

}


 if(commandValid==true){
   indexCommandes+=1;
   // if end of tab
   if(tabCommandes[indexCommandes]==0){
     clearTabCommandes();

   }
 }

 delay(10);
 */
 automaticBehavior.takePiecesSameColor();
 delay(20000);

}
