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

const Scene starting_scene = {
  .msgs_len = 3,
  .choices_len = 3,
  .msgs = {
    {"It's the start", "of a new day."},
    {"You slowly open", "your eyes as you"},
    {"begin to tiredly", "wake up."}
  },
  .choices = {
    {{"1) Sit up and", "stretch"}, 2},
    {{"2) Go back to", "sleep"}, 3},
    {{"3) Roll over to", "grab phone"}, 4}
  }
};

// Store all scenes into the game
const Scene game[2] PROGMEM = {
  welcome_scene,
  starting_scene
};
