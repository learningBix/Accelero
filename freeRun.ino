/* Accelero Free Run - Source Code
   Board - MiniCore 168 or Arduino Uno
*/

#include <modular.h> // include modular library

// bluetooth commands for the mobile app - bixchamp
#define MOVE_BOT_FWD 0xB0
#define MOVE_BOT_BWD 0xB1
#define MOVE_BOT_LT 0xB2
#define MOVE_BOT_RT 0xB3
#define BOT_STOP 0xB4
#define BUZZER_ON 0xC0
#define BUZZER_OFF 0xC1
#define RED_LED_COLOR 0xC2
#define GREEN_LED_COLOR 0xC3
#define BLUE_LED_COLOR 0xC4

Modular accelero; //create a object to access library functions

// initialise the hardware port connections
void setup() {

  accelero.steerBotBegin(4); //steering motors connected at port 4
  accelero.bluetoothBegin(1); // bluetooth connected at port 1
  accelero.rgbBegin(3, CA); // rgb led connected at port 3
  accelero.buzzerBegin(3); // buzzer connected at port 3
}

void loop() {
  //check if a command is received from app via bluetooth
  if (accelero.bluetoothCheck() > 0) {
    char message = accelero.bluetoothRead(); //save the command received

    switch (message) { //do action as per the command received
      case MOVE_BOT_FWD :
        accelero.steerBotForward(4);
        break;
      case MOVE_BOT_BWD :
        accelero.steerBotBackward(4);
        break;
      case MOVE_BOT_LT :
        accelero.steerBotLeftAxial(4);
        break;
      case MOVE_BOT_RT :
        accelero.steerBotRightAxial(4);
        break;
      case BOT_STOP :
        accelero.haltBot(4);
        break;
      case BUZZER_ON :
        accelero.buzzerSet(3, 1);
        break;
      case BUZZER_OFF :
        accelero.buzzerSet(3, 0);
        break;
      case RED_LED_COLOR :
        while (accelero.bluetoothCheck() <= 0); //wait for the red color value from the app
        message = accelero.bluetoothRead(); //save color value received from bluetooth
        accelero.rgbSetRed(3, 1, message); //switch on the led with intensity as per the message
        break;
      case GREEN_LED_COLOR :
        while (accelero.bluetoothCheck() <= 0); //wait for the green color value from the app
        message = accelero.bluetoothRead(); //save color value received from bluetooth
        accelero.rgbSetGreen(3,1, message); //switch on the led with intensity as per the message
        break;
      case BLUE_LED_COLOR :
        while (accelero.bluetoothCheck() <= 0); //wait for the blue color value from the app
        message = accelero.bluetoothRead(); //save color value received from bluetooth
        accelero.rgbSetBlue(3,1, message); //switch on the led with intensity as per the message
        break;
    }
  }
}
