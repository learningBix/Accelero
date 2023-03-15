/* Accelero Obstacle Avoider - Source Code
   Board - MiniCore 168 or Arduino Uno
*/

#include <modular.h> // include modular library

// bluetooth commands for the mobile app - bixchamp
#define MOVE_BOT_FWD 0xB0
#define MOVE_BOT_BWD 0xB1
#define MOVE_BOT_LT 0xB2
#define MOVE_BOT_RT 0xB3
#define BOT_STOP 0xB4
#define ULTRASONIC_READ 0xD0
#define BUZZER_ON 0xC0
#define BUZZER_OFF 0xC1
#define RED_LED_COLOR 0xC2
#define GREEN_LED_COLOR 0xC3
#define BLUE_LED_COLOR 0xC4

Modular avoider; //create a object to access library functions

// initialise the hardware port connections
void setup() {

  avoider.steerBotBegin(4); //steering motors connected at port 4
  avoider.bluetoothBegin(1); // bluetooth connected at port 1
  avoider.sonarBegin(2); // sonar sensor connected at port 2
  avoider.rgbBegin(3, CA); // rgb led connected at port 3
  avoider.buzzerBegin(3); // buzzer connected at port 3
}

void loop() {
  //check if a command is received from app via bluetooth
  if (avoider.bluetoothCheck() > 0) {
    char message = avoider.bluetoothRead(); //save the command received

    switch (message) { //do action as per the command received
      case MOVE_BOT_FWD :
        avoider.steerBotForward(4);
        break;
      case MOVE_BOT_BWD :
        avoider.steerBotBackward(4);
        break;
      case MOVE_BOT_LT :
        avoider.steerBotLeftAxial(4);
        break;
      case MOVE_BOT_RT :
        avoider.steerBotRightAxial(4);
        break;
      case BOT_STOP :
        avoider.haltBot(4);
        break;
      case ULTRASONIC_READ :
        byte distance = avoider.sonarRead(2); //read distance in centimeter
        avoider.bluetoothWrite(distance); //send distance to app
        break;
      case BUZZER_ON :
        avoider.buzzerSet(3, 1);
        break;
      case BUZZER_OFF :
        avoider.buzzerSet(3, 0);
        break;
      case RED_LED_COLOR :
        while (avoider.bluetoothCheck() <= 0); //wait for the red color value from the app
        message = avoider.bluetoothRead(); //save color value received from bluetooth
        avoider.rgbSetRed(3, 1, message); //switch on the led with intensity as per the message
        break;
      case GREEN_LED_COLOR :
        while (avoider.bluetoothCheck() <= 0); //wait for the green color value from the app
        message = avoider.bluetoothRead(); //save color value received from bluetooth
        avoider.rgbSetGreen(3, 1, message); //switch on the led with intensity as per the message
        break;
      case BLUE_LED_COLOR :
        while (avoider.bluetoothCheck() <= 0); //wait for the blue color value from the app
        message = avoider.bluetoothRead(); //save color value received from bluetooth
        avoider.rgbSetBlue(3, 1, message); //switch on the led with intensity as per the message
        break;
    }
  }
}
