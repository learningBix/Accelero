/* Accelero Hammer - Source Code
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

Modular hammer; //create a object to access library functions

// initialise the hardware port connections
void setup() {

  hammer.steerBotBegin(4); //steering motors connected at port 4
  hammer.servoOneBegin(3); //servo motor 1 for hammer strike, connected at port3
  hammer.bluetoothBegin(1); // bluetooth connected at port 1

}

void loop() {
  //check if a command is received from app via bluetooth
  if (hammer.bluetoothCheck() > 0) {
    char message = hammer.bluetoothRead(); //save the command received

    switch (message) { //do action as per the command received
      case MOVE_BOT_FWD :
        hammer.steerBotForward(4);
        break;
      case MOVE_BOT_BWD :
        hammer.steerBotBackward(4);
        break;
      case MOVE_BOT_LT :
        hammer.steerBotLeftAxial(4);
        break;
      case MOVE_BOT_RT :
        hammer.steerBotRightAxial(4);
        break;
      case BOT_STOP :
        hammer.haltBot(4);
        break;
      case SERVO_1_ANGLE :
        while (hammer.bluetoothCheck() <= 0); //wait for the servo angle value from the app
        message = hammer.bluetoothRead(); //save servo angle received from bluetooth
        hammer.servoOneMove(message); //set angle with the value received
        break;
    }
  }
}
