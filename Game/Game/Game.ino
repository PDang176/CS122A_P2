#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

// Joystick Pins
const int SW_pin = A0;
const int X_pin = A1;
const int Y_pin = A2;

// Message struct
struct Message{
  char msg[2][16];
};

// Choice struct
struct Choice{
  char choice[2][16];
  int next_scene;
};

// Max number of messages and choices per scene
#define MAX_MSGS 5
#define MAX_CHOICES 4

// Game Over Scene Number
#define GAME_OVER_SCENE 10

// Scene struct
struct Scene{
  int msgs_len;
  int choices_len;
  Message msgs[MAX_MSGS];
  Choice choices[MAX_CHOICES];
};

// All scenes are declared here
const Scene welcome_scene = {
  .msgs_len = 1, 
  .choices_len = 2, 
  .msgs = {
    {"     Hello     ", "     World!     "}
  }, 
  .choices = {
    {{"1) Start Game", ""}, 1},
    {{"2) Return", ""}, 0}
  }
};

const Scene next_scene = {
  .msgs_len = 2,
  .choices_len = 3,
  .msgs = {
    {"Good Bye", "World"},
    {"Something", "Wight"}
  },
  .choices = {
    {{"1) Restart", ""}, 0},
    {{"2) Scene One", ""}, 1},
    {{"3) Something", "Wong"}, 0}
  }
};

// Store all scenes into the game
const Scene game[2] PROGMEM = {
  welcome_scene,
  next_scene
};

// Current Paused
int paused = 0;

// Inputs
int clicked = 0;
int selection = 0; // 0 = Do nothing, 1 == Down, 2 == Up

// Current Scene
int scene_i = 0;

// Current message
Message curr_msg;
int msg_i = 0;
int msgs_len;

// Current Choices
Choice curr_choice;
int choice_i = -1;
int choices_len;

// On What Do You Do
int wdyd = 0;

void setup() {
  Serial.begin(9600);
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Set up joystick
  pinMode(SW_pin, INPUT_PULLUP);
  
  // Print a message to the LCD.
  readMsgsLen();
  readMsg();
  printMsg();
}

void loop() {
  // Check if paused
  if(paused){
    printPaused();
  }
  else{
     click_btn();

    // Check if joystick has been clicked
    if(clicked){
      if(choice_i != -1){ // If selecting choices
        if(wdyd){
          readChoicesLen();
          readChoice();
          printChoice();
          wdyd = 0;
        }
        else{
          scene_i = curr_choice.next_scene;
          choice_i = -1;
          readMsgsLen();
          readMsg();
          printMsg();
        }
      }
      else{ // If reading messages
        if(msg_i >= msgs_len){ // All messages have bene read now read choices
          msg_i = 0;
          choice_i = 0;
          if(scene_i != 0 || scene_i != GAME_OVER_SCENE){
            wdyd = 1;
            printWhatDoYouDo();
          }
          else{
            readChoicesLen();
            readChoice();
            printChoice();
          }
        }
        else{ // Read next message
          readMsg();
          printMsg();
        }
      }
    }
  
    // If selecting choices let user use joystick to choose choices
    if(choice_i != -1){
      select_choice();
      switch(selection){
        case 0:
          break;
        case 1:
          if(choice_i >= choices_len - 1){
            choice_i = 0;
          }
          else{
            choice_i++;
          }
          readChoice();
          printChoice();
          break;
        case 2:
          if(choice_i <= 0){
            choice_i = choices_len - 1;
          }
          else{
            choice_i--;
          }
          readChoice();
          printChoice();
          break;
        default:
          Serial.println(selection);
          break;
      }
    }
  }
  
  // Allow for delay to account for button debouncing
  delay(150);
}

// Read the length of messages from progmem
void readMsgsLen(){
  memcpy_P(&msgs_len, &game[scene_i].msgs_len, sizeof(msgs_len));
}

// Read the length of choices from progmem
void readChoicesLen(){
  memcpy_P(&choices_len, &game[scene_i].choices_len, sizeof(choices_len));
}

// Read the current message from progmem
void readMsg(){
  memcpy_P(&curr_msg, &game[scene_i].msgs[msg_i], sizeof(curr_msg));
  msg_i++;
}

// Print the pause screen
void printPaused(){
  lcd.clear();
  lcd.print("     PAUSED     ");
}

// Print the current message
void printMsg(){
  lcd.clear();
  lcd.print(curr_msg.msg[0]);
  lcd.setCursor(0, 1);
  lcd.print(curr_msg.msg[1]);
}

// Print "What do you do?" message before choices
void printWhatDoYouDo(){
  lcd.clear();
  lcd.print("What do you do?");
}

// Print the current choices
void readChoice(){
  memcpy_P(&curr_choice, &game[scene_i].choices[choice_i], sizeof(curr_choice));
}

// Print all the current choices
void printChoice(){
  lcd.clear();
  lcd.print(curr_choice.choice[0]);
  lcd.setCursor(0, 1);
  lcd.print(curr_choice.choice[1]);
}

// Check if joystick has been clicked
void click_btn(){
  clicked = (digitalRead(SW_pin) == LOW) ? 1 : 0;
}

// Allow for joystick to select choices
void select_choice(){
  if(analogRead(Y_pin) < 256){
    selection = 1;
  }
  else if(analogRead(Y_pin) > 768){
    selection = 2;
  }
  else{
    selection = 0;
  }
}
