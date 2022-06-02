// Message struct
struct Message {
  char msg[2][16];
};

// Choice struct
struct Choice {
  char choice[2][16];
  int next_scene;
};

// Max number of messages and choices per scene
#define MAX_MSGS 5
#define MAX_CHOICES 4

// Game Over Scene Number
#define GAME_OVER 24

// Win Scene Number
#define WIN 25

// Credits Sceen Number
#define CREDITS 26

const int notwdyd_scenes[] = {
  0, GAME_OVER, WIN, CREDITS, 2, 6, 7, 8, 11, 15, 16
};

// Scene struct
struct Scene {
  int msgs_len;
  int choices_len;
  Message msgs[MAX_MSGS];
  Choice choices[MAX_CHOICES];
};

// All scenes are declared here
const Scene gameover_scene = {
  .msgs_len = 1,
  .choices_len = 1,
  .msgs = {
    {"      Game      ", "      Over      "}
  },
  .choices = {
    {{"1) Restart?"}, 0}
  }
};

const Scene win_scene = {
  .msgs_len = 1,
  .choices_len = 1,
  .msgs = {
    {"Congratulations!", ""}
  },
  .choices = {
    {{"1) Restart?"}, 0}
  }
};

const Scene credits_scene = {
  .msgs_len = 2,
  .choices_len = 1,
  .msgs = {
    {"    Credits     ", ""},
    {"     CS122A     ", "    Project 2    "}
  },
  .choices = {
    {{"    Made By     ", "  Patrick Dang  "}, 0}
  }
};

const Scene welcome_scene = {
  .msgs_len = 1,
  .choices_len = 3,
  .msgs = {
    {"     Hello     ", "     World!     "}
  },
  .choices = {
    {{"1) Start Game", ""}, 1},
    {{"2) Credits", ""}, CREDITS},
    {{"3) Return", ""}, 0}
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

const Scene stretch_scene = {
  .msgs_len = 5,
  .choices_len = 1,
  .msgs = {
    {"Slowly you begin", "to sit up."},
    {"You raise your", "hands up and"},
    {"stretch out your", "limbs. Suddenly"},
    {"your muscles", "cramp up. You"},
    {"start to spaz", "and eventually"}
  },
  .choices = {
    {{"you pass out.", ""}, GAME_OVER}
  }
};

const Scene sleep_scene = {
  .msgs_len = 5,
  .choices_len = 4,
  .msgs = {
    {"You close your", "eyes and try to"},
    {"fall asleep.", "All of a sudden"},
    {"your alarm goes", "off. Annoyed you"},
    {"grab your phone", "and turn it off"},
    {"You sit up now", "somewhat awake."}
  },
  .choices = {
    {{"1) Wash up and", "brush your teeth"}, 5},
    {{"2) Head", "downstairs"}, 6},
    {{"3) Jump out the", "window"}, 7},
    {{"4) Go back to", "sleep again"}, 8}
  }
};

const Scene phone_scene = {
  .msgs_len = 5,
  .choices_len = 4,
  .msgs = {
    {"You roll over", "and grab your"},
    {"phone. You see", "your alarm about"},
    {"to ring so you", "turn it off. Few"},
    {"minutes of", "scrolling later"},
    {"you actually get", "up for the day."}
  },
  .choices = {
    {{"1) Wash up and", "brush your teeth"}, 5},
    {{"2) Head", "downstairs"}, 6},
    {{"3) Jump out the", "window"}, 7},
    {{"4) Go back to", "sleep again"}, 8}
  }
};

const Scene bathroom_scene = {
  .msgs_len = 5,
  .choices_len = 2,
  .msgs = {
    {"You head to the", "bathroom to wash"},
    {"up. After", "brushing your"},
    {"teeth / washing", "your face you're"},
    {"now fully awake", "and ready to"},
    {"start the day.", ""}
  },
  .choices = {
    {{"1) Head", "downstairs"}, 9},
    {{"2) Go back to", "sleep again"}, 8}
  }
};

const Scene downstairs_scene = {
  .msgs_len = 4,
  .choices_len = 1,
  .msgs = {
    {"Tired and groggy", "you stumble to"},
    {"the stairs. You", "start walk down,"},
    {"but because of", "your tiredness"},
    {"you miss a step", "and go crashing"}
  },
  .choices = {
    {{"down the stairs.", ""}, GAME_OVER}
  }
};

const Scene window_scene = {
  .msgs_len = 2,
  .choices_len = 1,
  .msgs = {
    {"You jump out the", "window and"},
    {"perish. There", "was no reason to"}
  },
  .choices = {
    {{"do this. Choose", "a better option."}, GAME_OVER}
  }
};

const Scene sleep2_scene = {
  .msgs_len = 5,
  .choices_len = 1,
  .msgs = {
    {"You're back", "lying down in"},
    {"bed and drift", "off to sleep."},
    {"Later your phone", "rings. It's your"},
    {"boss calling.", "You look at the"},
    {"clock. It's 3PM.", "You're fired."}
  },
  .choices = {
    {{"Don't oversleep", "next time."}, GAME_OVER}
  }
};

const Scene downstairs2_scene = {
  .msgs_len = 4,
  .choices_len = 3,
  .msgs = {
    {"Now awake you", "walk downstairs"},
    {"all ready for", "work. You look"},
    {"at the clock.", "It reads 7AM."},
    {"You still have", "a bit of time."}
  },
  .choices = {
    {{"1) Eat a small", "breakfast" }, 10},
    {{"2) Eat a LARGE", "breakfast"}, 11},
    {{"3) Go to work", "early"}, 12}
  }
};

const Scene breakfast_scene = {
  .msgs_len = 5,
  .choices_len = 1,
  .msgs = {
    {"You decide to", "grab some cereal"},
    {"to eat. Theres", "still a bit of"},
    {"fruity pebbles", "and milk left."},
    {"You eat your", "cereal and wash"},
    {"the dishes.", "Clock reads 8AM."}
  },
  .choices = {
    {{"1) Go to work", ""}, 12}
  }
};

const Scene breakfast2_scene = {
  .msgs_len = 5,
  .choices_len = 1,
  .msgs = {
    {"You decide to", "make a full on"},
    {"feast. Bacon,", "Eggs, Pancakes,"},
    {"the works. So", "much grease and"},
    {"sugar on", "everything. Your"},
    {"body couldn't", "handle it all"}
  },
  .choices = {
    {{"and you go into", "cardiac arrest."}, GAME_OVER}
  }
};

const Scene headtowork_scene = {
  .msgs_len = 4,
  .choices_len = 2,
  .msgs = {
    {"You grab your", "bag and head off"},
    {"to work. It's a", "beautiful day so"},
    {"you decide to", "walk. On the way"},
    {"You pass by a", "random 7-Eleven."},
  },
  .choices = {
    {{"1) Head inside", ""}, 13},
    {{"2) Walk past", ""}, 14}
  }
};

const Scene seleven_scene = {
  .msgs_len = 4,
  .choices_len = 3,
  .msgs = {
    {"You decided to", "walk on inside."},
    {"After walking", "down the aisles"},
    {"for a bit it's", "time to go back"},
    {"to work.", ""}
  },
  .choices = {
    {{"1) Buy a lottery", "ticket"}, 15},
    {{"2) Buy a coffee", ""}, 14},
    {{"3) Buy nothing", "at all"}, 14}
  }
};

const Scene headtowork2_scene = {
  .msgs_len = 5,
  .choices_len = 4,
  .msgs = {
    {"You continue on", "heading towards"},
    {"work. Finally,", "you arrive right"},
    {"on time. As you", "make your way to"},
    {"inside you're", "suddenly stopped"},
    {"by a much hated", "coworker."}
  },
  .choices = {
    {{"1) Punch him in", "the face"}, 17},
    {{"2) Walk right by", "him"}, 18},
    {{"3) Tell him good", "morning"}, 19},
    {{"4) Nod and", "continue walking"}, 18}
  }
};

const Scene lottery_scene = {
  .msgs_len = 5,
  .choices_len = 1,
  .msgs = {
    {"After taking $5", "out of your"},
    {"wallet you head", "to the counter"},
    {"and purchase a", "scratcher. Using"},
    {"your keys you", "start scratching"},
    {"the ticket.", "To your surprise"}
  },
  .choices = {
    {{"you won the", "grand prize! You"}, 16}
  }
};

const Scene lottery2_scene = {
  .msgs_len = 1,
  .choices_len = 1,
  .msgs = {
    {"call your boss", "and quit right"}
  },
  .choices = {
    {{"on the spot.", "You're rich!"}, WIN}
  }
};

const Scene punch_scene = {
  .msgs_len = 5,
  .choices_len = 1,
  .msgs = {
    {"You wind up and", "get ready to"},
    {"swing at him.", "POW! You land a"},
    {"hit right in his", "face. Even if it"},
    {"it was deserved", "you really can't"},
    {"just be hitting", "people. Security"}
  },
  .choices = {
    {{"escorts you off", "the premises."}, GAME_OVER}
  }
}

const Scene passcoworker_scene = {
  .msgs_len = 5,
  .choices_len = 4,
  .msgs = {
    {"As you begin to", "walk by he calls"},
    {"out your name.", "Of course it's"},
    {"not that simple.", "You turn around"},
    {"and to face him.", "He smirks and"},
    {"asks \"No good", "morning?\""}
  },
  .choices = {
    {{"1) Punch him in", "the face"}, 17},
    {{"2) Tell him good", "morning"}, 19},
    {{"3) Turn around", "and keep walking"}, 20},
    {{"4) Say no and", "walk away"}, 20}
  }
}

const Scene goodmorning_scene = {
  .msgs_len = 5,
  .choices_len = 2,
  .msgs = {
    {"You tell him", "good morning and"},
    {"continue on your", "merry way. He"},
    {"was a bit thrown", "back by this,"},
    {"but let you go.", "You head inside"},
    {"and up the", "stairs to work."}
  },
  .choices = {
    {{"1) Head to your", "cubicle"}, 21},
    {{"2) Jump out the", "window"}, 7}
  }
}

const Scene passcoworker2_scene = {
  .msgs_len = 5,
  .choices_len = 4,
  .msgs = {
    {"You continue", "walking, but"},
    {"suddenly a hand", "pulls you to a"},
    {"stop. \"Hey! why", "are you being so"},
    {"rude.\" You brush", "off his hand and"},
    {"face him once", "again."}
  },
  .choices = {
    {{"1) Punch him in", "the face"}, 17},
    {{"2) Turn around", "and keep walking"}, 22},
    {{"3) Tell him it's", "cuz he's an ass"}, 22},
    {{"4) Sigh and say", "good morning"}, 19}
  }
}

const Scene cubicle_scene = {
  .msgs_len = 5,
  .choices_len = 1,
  .msgs = {
    {"You arrive at", "your cubicle."},
    {"Finally you", "begin to work."},
    {"You pull out a", "laptop and open"},
    {"up your favorite", "text editor."},
    {"You're ready to", "start the day."},
  },
  .choices = {
    {{"  Hello World.  ", ""}, WIN}
  }
}

const Scene passcoworker3_scene = {
  .msgs_len = 5,
  .choices_len = 1,
  .msgs = {
    {"He begins to", "become enraged."},
    {"Veins forming", "he starts to"},
    {"clench his fist.", "POW! He smacks"},
    {"you right in the", "face. Security"},
    {"is called and he", "gets escorted"},
  },
  .choices = {
    {{"away. Everyone", "cheers as he's"}, 23}
  }
}

const Scene passcoworker4_scene = {
  .msgs_len = 5,
  .choices_len = 1,
  .msgs = {
    {"dragged away.", "Looks like you"},
    {"weren't the only", "one who hated"},
    {"him. You earn", "the respect of"},
    {"everyone around.", "Bruised but"},
    {"feeling elated", "you walk inside."},
  },
  .choices = {
    {{"Victory is", "finally yours."}, WIN}
  }
}

// Store all scenes into the game
const Scene game[27] PROGMEM = {
  welcome_scene,
  starting_scene,
  stretch_scene,
  sleep_scene,
  phone_scene,
  bathroom_scene,
  downstairs_scene,
  window_scene,
  sleep2_scene,
  downstairs2_scene,
  breakfast_scene,
  breakfast2_scene,
  headtowork_scene,
  seleven_scene,
  headtowork2_scene,
  lottery_scene,
  lottery2_scene,
  punch_scene,
  passcoworker_scene,
  goodmorning_scene,
  passcoworker2_scene,
  cubicle_scene,
  passcoworker3_scene,
  passcoworker4_scene,
  gameover_scene,
  win_scene,
  credits_scene
};
