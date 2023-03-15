/* Accelero Soccer - Source Code
   Board - MiniCore 168 or Arduino Uno
*/

#include <modular.h> // include modular library

// bluetooth commands for the mobile app - bixchamp
#define MOVE_BOT_FWD 0xB0
#define MOVE_BOT_BWD 0xB1
#define MOVE_BOT_LT 0xB2
#define MOVE_BOT_RT 0xB3
#define BOT_STOP 0xB4
#define SERVO_1_ANGLE 0xBB

Modular soccer; //create a object to access library functions

// initialise the hardware port connections
void setup() {

  soccer.steerBotBegin(4); //steering motors connected at port 4
  soccer.servoOneBegin(3); //servo motor 1 for kick, connected at port3
  soccer.bluetoothBegin(1); // bluetooth connected at port 1

}

void loop() {
  //check if a command is received from app via bluetooth
  if (soccer.bluetoothCheck() > 0) {
    char message = soccer.bluetoothRead(); //save the command received

    switch (message) { //do action as per the command received
      case MOVE_BOT_FWD :
        soccer.steerBotForward(4);
        break;
      case MOVE_BOT_BWD :
        soccer.steerBotBackward(4);
        break;
      case MOVE_BOT_LT :
        soccer.steerBotLeftAxial(4);
        break;
      case MOVE_BOT_RT :
        soccer.steerBotRightAxial(4);
        break;
      case BOT_STOP :
        soccer.haltBot(4);
        break;
      case SERVO_1_ANGLE :
        while (soccer.bluetoothCheck() <= 0); //wait for the servo angle value from the app
        message = soccer.bluetoothRead(); //save servo angle received from bluetooth
        soccer.servoOneMove(message); //set angle with the value received
        break;
    }
  }
}
