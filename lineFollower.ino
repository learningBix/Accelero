/* Accelero Line Follower - Source Code
   Board - MiniCore 168 or Arduino Uno
*/

#include <modular.h> // include modular library

// bluetooth commands for the mobile app - bixchamp
#define MOVE_BOT_FWD 0xB0
#define MOVE_BOT_BWD 0xB1
#define MOVE_BOT_LT 0xB2
#define MOVE_BOT_RT 0xB3
#define BOT_STOP 0xB4
#define PROXIMITY_ONE_READ 0xD1
#define PROXIMITY_TWO_READ 0xD2
#define SET_PS_ONE_THRESHOLD 0xD3
#define SET_PS_TWO_THRESHOLD 0xD4
#define PLAY_LINE_FOLLOWER 0xD5
#define STOP_LINE_FOLLOWER 0xD6
#define BUZZER_ON 0xC0
#define BUZZER_OFF 0xC1
#define RED_LED_COLOR 0xC2
#define GREEN_LED_COLOR 0xC3
#define BLUE_LED_COLOR 0xC4

Modular accelero; //create a object to access library functions

//function declaration for play line follower
void play_line_follower();

//value to store black and white threshold value
byte ps1_threshold = 0;
byte ps2_threshold = 0;

byte sense_value = 0; // variable to store proximity senser value

// initialise the hardware port connections
void setup() {

  accelero.steerBotBegin(4); //steering motors connected at port 4
  accelero.proximityOneBegin(2); //proximity sensor 1, connected at port 2
  accelero.proximityTwoBegin(2); //proximity sensor 2, connected at port 2
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
      case PROXIMITY_ONE_READ :
        sense_value = accelero.proximityOneRead(2); // //read proximity 1 sensor
        accelero.bluetoothWrite(sense_value);
        break;
      case PROXIMITY_TWO_READ :
        sense_value = accelero.proximityTwoRead(2); // //read proximity 1 sensor
        accelero.bluetoothWrite(sense_value);
        break;
      case SET_PS_ONE_THRESHOLD :
        while (accelero.bluetoothCheck() <= 0); //wait for the threshold value from the app
        ps1_threshold = accelero.bluetoothRead(); //save threshold value
        break;
      case SET_PS_TWO_THRESHOLD :
        while (accelero.bluetoothCheck() <= 0); //wait for the threshold value from the app
        ps2_threshold = accelero.bluetoothRead(); //save threshold value
        break;
      case PLAY_LINE_FOLLOWER :
        //play line follower until stop command is received from app
        while (accelero.bluetoothCheck() <= 0) {
          play_line_follower();
        }
        break;
      case STOP_LINE_FOLLOWER :
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
        accelero.rgbSetGreen(3, 1, message); //switch on the led with intensity as per the message
        break;
      case BLUE_LED_COLOR :
        while (accelero.bluetoothCheck() <= 0); //wait for the blue color value from the app
        message = accelero.bluetoothRead(); //save color value received from bluetooth
        accelero.rgbSetBlue(3, 1, message); //switch on the led with intensity as per the message
        break;
    }
  }
}

//function definition to play line follower code
void play_line_follower() {
  byte ps1_value = accelero.proximityOneRead(2); // read proximity one sensor
  byte ps2_value = accelero.proximityTwoRead(2); // read proximity one sensor

  //if black line is detected by both sensors then stop the bot
  if ((ps1_value < ps1_threshold) && (ps2_value < ps2_threshold)) {
    accelero.haltBot(4);
  }
  //if white line is detected by both sensors then move the bot forward
  else if ((ps1_value > ps1_threshold) && (ps2_value > ps2_threshold)) {
    accelero.steerBotForward(4);
  }
  //if black line is detected by left sensor then turn left
  else if ((ps1_value < ps1_threshold)) {
    accelero.steerBotLeftAxial(4);
  }
  //if black line is detected by right sensor then turn right
  else {
    accelero.steerBotRightAxial(4);
  }
}
