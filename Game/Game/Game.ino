#include <LiquidCrystal.h>
#include <EEPROM.h>
#include "scenes.h"

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

// Joystick Pins
#define SW_pin A0
#define X_pin A1
#define Y_pin A2

// Buttons
#define Pause_pin 7
#define Multi_pin 6

// EEPROM Address
int eeAddress = 0;

// Current Paused
bool paused = false;

// Inputs
bool clicked = false;
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
bool wdyd = false;

void setup() {
  Serial.begin(9600);
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Set up joystick
  pinMode(SW_pin, INPUT_PULLUP);

  // Set up buttons
  pinMode(Pause_pin, INPUT_PULLUP);
  pinMode(Multi_pin, INPUT_PULLUP);
  
  // Print a message to the LCD.
  readMsgsLen();
  readMsg();
  printMsg();
  checkwdyd();
}

void loop() {
  // Check button for pause toggle
  if(valid_scene()){
    pause_btn();
  }

  // Load save state
  if(multi_btn() && scene_i == 0){
    continue_scene();
  }

  // Game is paused
  if(paused){
    if(multi_btn()){ // Check for restart button
      paused = false;
      scene_i = 0;
      msg_i = 0;
      choice_i = -1;
      readMsgsLen();
      readMsg();
      printMsg();
      checkwdyd();
    }
  }
  else{ // Game isn't paused
    // Check for joystick click 
    click_btn();

    if(multi_btn() && valid_scene()){ // Check for save button
      save_scene();
    }

    // Joystick has been clicked
    if(clicked){
      if(choice_i != -1){ // If selecting choices
        scene_i = curr_choice.next_scene;
        choice_i = -1;
        readMsgsLen();
        readMsg();
        printMsg();
        checkwdyd();
      }
      else{ // If reading messages
        if(msg_i >= msgs_len - 1){ // All messages have bene read now read choices
          if(wdyd){
            wdyd = false;
            printWhatDoYouDo();
            msg_i++;
          }
          else{
            msg_i = 0;
            choice_i = 0;
            readChoicesLen();
            readChoice();
            printChoice();
          }
        }
        else{ // Read next message
          msg_i++;
          readMsg();
          printMsg();
        }
      }
    }
  
    // If selecting choices let user use joystick to choose choices
    if(choice_i != -1){
      select_choice();
      switch(selection){
        case 0: // Do nothing
          break;
        case 1: // Scroll down
          if(choice_i >= choices_len - 1){
            choice_i = 0;
          }
          else{
            choice_i++;
          }
          readChoice();
          printChoice();
          break;
        case 2: // Scroll up
          if(choice_i <= 0){
            choice_i = choices_len - 1;
          }
          else{
            choice_i--;
          }
          readChoice();
          printChoice();
          break;
        default: // Error print selection
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

// Save the current scene
void save_scene(){
  // Print "Progress Saved" message
  lcd.clear();
  lcd.print(" Progress Saved ");

  // Save to EEPROM
  eeAddress = 0;
  EEPROM.put(eeAddress, scene_i);
  eeAddress += sizeof(int);
  EEPROM.put(eeAddress, msg_i);
  eeAddress += sizeof(int);
  EEPROM.put(eeAddress, choice_i);
  eeAddress += sizeof(int);
  EEPROM.put(eeAddress, wdyd);
  
  delay(1000);
  if(choice_i != -1){ // Print choice
    printChoice();
  }
  else{
    if(msg_i > msgs_len - 1){ // Print WDYD
      printWhatDoYouDo();
    }
    else{ // Print message
      printMsg();
    }
  }
}

// Continue from saved scene
void continue_scene(){
  // Print "Progress Continued" message
  lcd.clear();
  lcd.print("    Progress    ");
  lcd.setCursor(0, 1);
  lcd.print("    Continued   ");

  // Retrieve scene from EEPROM
  eeAddress = 0;
  EEPROM.get(eeAddress, scene_i);
  eeAddress += sizeof(int);
  EEPROM.get(eeAddress, msg_i);
  eeAddress += sizeof(int);
  EEPROM.get(eeAddress, choice_i);
  eeAddress += sizeof(int);
  EEPROM.get(eeAddress, wdyd);

  delay(1000);
  if(choice_i != -1){ // Print choice
    readChoicesLen();
    readChoice();
    printChoice();
  }
  else{
    readMsgsLen();
    if(msg_i > msgs_len - 1){ // Print WDYD
      printWhatDoYouDo();
    }
    else{ // Print message
      readMsg();
      printMsg(); 
    }
  }
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

// Check if pause button has been clicked
void pause_btn(){
  if(digitalRead(Pause_pin) == LOW){
    paused = !paused;
    if(paused){ // Currently paused
      printPaused();
    }
    else{ // Not paused
      if(choice_i != -1){ // Print choice
        printChoice();
      }
      else{
        if(msg_i > msgs_len - 1){ // Print WDYD
          printWhatDoYouDo();
        }
        else{ // Print message
          printMsg();  
        }
      }
    }
  }
}

bool valid_scene(){
  return (scene_i != 0 && scene_i != GAME_OVER && scene_i != WIN && scene_i != CREDITS);
}

// Check if multi button has been clicked
bool multi_btn(){
  return (digitalRead(Multi_pin) == LOW);
}

// Check if joystick has been clicked
void click_btn(){
  clicked = (digitalRead(SW_pin) == LOW) ? true : false;
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

void checkwdyd(){
  for(int i = 0; i < sizeof(notwdyd_scenes) / sizeof(int); i++){
    if(scene_i == notwdyd_scenes[i]){
      wdyd = false;
      return;
    }
  }
  wdyd = true;
  return;
}
