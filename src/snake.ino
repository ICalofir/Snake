// these matrices are used for different messages
bool gameOverMatrix[6][4] = {
  {1, 1, 1, 1},
  {1, 0, 0, 0},
  {1, 0, 0, 0},
  {1, 0, 1, 1},
  {1, 0, 0, 1},
  {1, 1, 1, 1}
};

bool exclamationPoint[6][2] = {
  {1, 1},
  {1, 1},
  {1, 1},
  {1, 1},
  {0, 0},
  {1, 1}
};

bool unu[5][3] = {
  {0, 0, 1},
  {0, 1, 1},
  {1, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
};

bool doi[5][3] = {
  {1, 1, 1},
  {0, 0, 1},
  {1, 1, 1},
  {1, 0, 0},
  {1, 1, 1},
};

bool trei[5][3] = {
  {1, 1, 1},
  {0, 0, 1},
  {1, 1, 1},
  {0, 0, 1},
  {1, 1, 1},
};

bool patru[5][3] = {
  {0, 0, 1},
  {0, 1, 0},
  {1, 1, 1},
  {0, 0, 1},
  {0, 0, 1},
};

bool cinci[5][3] = {
  {1, 1, 1},
  {1, 0, 0},
  {1, 1, 1},
  {0, 0, 1},
  {1, 1, 1},
};

bool sase[5][3] = {
  {1, 1, 1},
  {1, 0, 0},
  {1, 1, 1},
  {1, 0, 1},
  {1, 1, 1},
};

bool sapte[5][3] = {
  {1, 1, 0},
  {0, 1, 0},
  {1, 1, 1},
  {0, 1, 0},
  {0, 1, 0},
};

bool opt[5][3] = {
  {1, 1, 1},
  {1, 0, 1},
  {1, 1, 1},
  {1, 0, 1},
  {1, 1, 1},
};

bool noua[5][3] = {
  {1, 1, 1},
  {1, 0, 1},
  {1, 1, 1},
  {0, 0, 1},
  {0, 0, 1},
};

bool zero[5][3] = {
  {1, 1, 1},
  {1, 0, 1},
  {1, 0, 1},
  {1, 0, 1},
  {1, 1, 1},
};

// nrScene represents the number of scenes
int nrScene, currScene;
// a scene contains a message
bool scene[6][8][8];

// 2-dimensional array of row pin numbers
const int row[8] = {
  2, 7, 19, 5, 13, 18, 12, 16
};

// 2-dimensional array of column pin numbers
const int col[8] = {
  6, 11, 10, 3, 17, 4, 8, 9
};

// 2-dimensional array of pixels:
int pixels[8][8];

int score = 0, lastScore, lvl = 1;
bool gameOver = false;

enum directions {DOWN, LEFT, UP, RIGHT} dir;
// length of the tail
int n;
// the coordinates of the tail
int snakeX[64];
int snakeY[64];

// position of the head
int x, y;
int lastValX, lastValY;

// how much food is inside the snake
int m;
// the coordinates of the food
int snakeFoodX[64];
int snakeFoodY[64];

// position of the food
int foodX, foodY;

// number of obstacles
int t;
// coordinates of the obstacles
int envX[64];
int envY[64];

// speed of the snake
int t_clock = 0;
int t_clock_lim = 400;

// speed of messages
int tm_clock = 0;
int tm_clock_lim = 2000;

// speed of changing the position of the food
int f_clock = 0;
int f_clock_lim = 0;

void setup() { 
  InitLvl();
}

void InitLvl() {
  // initialize the I/O pins as outputs
  // iterate over the pins
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins
    pinMode(col[thisPin], OUTPUT);
    pinMode(row[thisPin], OUTPUT);
    // take the col pins (i.e. the cathodes) high to ensure that
    // the LEDS are off
    digitalWrite(col[thisPin], HIGH);
  }

  // initialize the pixel matrix
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      pixels[x][y] = HIGH;
    }
  }

  // initialize the scene matrix
  for (int t = 0; t <= 5; ++t) {
    for (int x = 0; x < 8; ++x) {
      for (int y = 0; y < 8; ++y) {
        scene[t][x][y] = 0;
      }
    }
  }

  // initialization
  for (int i = 0; i < 64; ++i) {
    snakeX[i] = -1;
    snakeY[i] = -1;
    snakeFoodX[i] = -1;
    snakeFoodY[i] = -1;
    envX[i] = -1;
    envY[i] = -1;
  }

  // start position
  x = -1;
  y = 7;

  // initialize the tail
  snakeX[0] = x;
  snakeY[0] = y;
  n = 1;

  // initialize the direction
  dir = RIGHT;

  // initialize the food
  m = -1;
  randomSeed(analogRead(A0));
  updateFood();

  // initialize the number of obstacles
  t = -1;
}

// initialize the map for lvl 2
void generateLvl2() {
  x = 1;
  y = 6;
  
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      pixels[x][y] = HIGH;
    }
  }

  for (int i = 0; i < 8; ++i) {
    pixels[i][0] = LOW;
    pixels[0][i] = LOW;
    pixels[i][7] = LOW;
    pixels[7][i] = LOW;
  }

  // initialize obstacles
  t = -1;
  for (int i = 0; i < 8; ++i) {
    ++t;
    envX[t] = i;
    envY[t] = 0;
    ++t;
    envX[t] = i;
    envY[t] = 7;
  }
  for (int i = 1; i < 7; ++i) {
    ++t;
    envX[t] = 0;
    envY[t] = i;
    ++t;
    envX[t] = 7;
    envY[t] = i;
  }
}

// initialize the map for lvl 3
void generateLvl3() {
  x = 1;
  y = 7;
  
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      pixels[x][y] = HIGH;
    }
  }
  t = -1;

  /*
   * 1 0 0 0 0 0 0 0
   * 1 0 0 0 0 0 0 0
   * 1 0 0 0 1 1 1 1
   * 1 0 0 0 0 0 0 0
   * 0 0 0 0 0 0 0 0
   * 0 0 0 0 0 0 0 0
   * 1 1 1 1 1 0 0 0
   * 0 0 0 0 0 0 0 0
   */
   
  for (int y = 7; y >= 4; --y) {
    pixels[0][y] = LOW;
    ++t;
    envX[t] = 0;
    envY[t] = y;
  }

  for (int x = 0; x <= 4; ++x) {
    pixels[x][1] = LOW;
    ++t;
    envX[t] = x;
    envY[t] = 1;
  }

  for (int x = 4; x <= 7; ++x) {
    pixels[x][5] = LOW;
    ++t;
    envX[t] = x;
    envY[t] = 5;
  }
}

// initialize the map for lvl 4
void generateLvl4() {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      pixels[x][y] = HIGH;
    }
  }
  
  t_clock_lim = 200;
  f_clock_lim = 4000;
}

void loop() {
  if (gameOver == true) {
    int valX = analogRead(A0);
    // start a new game
    if (valX == 1023) {
      gameOver = false;
      InitLvl();
    } else {
      // print a message
      gameOverMessage();

      // draw the screen
      refreshScreen();
    }
  } else {
    // move Snake
    moveSnake();

    // draw the screen
    refreshScreen();
  }
}

// iterate over all scenes and print them, one at the time
void gameOverMessage() {
  tm_clock = tm_clock + 1;

  if (tm_clock == 2 * tm_clock_lim) {
    tm_clock = 0;
    ++currScene;
    if (currScene == nrScene + 1) {
      currScene = 0;
    }

    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        if (scene[currScene][x][y] == 1) {
          pixels[x][y] = LOW;
        }
      }
    }
  } else if (tm_clock == tm_clock_lim) {
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        pixels[x][y] = HIGH;
      }
    }
  }
}

// moves the Snake
void moveSnake() {
  // respawn food in another place
  if (f_clock_lim != 0) {
    f_clock = f_clock + 1;
    if (f_clock == f_clock_lim) {
      f_clock = 0;
      pixels[foodX][foodY] = HIGH;
      updateFood();
    }
  }
  
  t_clock = t_clock + 1;
  if (dir == RIGHT && t_clock == t_clock_lim) {
    t_clock = 0;
    x = x + 1;
    if (x == 8) {
      x = 0;
    }

    // update the game
    moveSnakeTail(x, y);
    checkCollisionWithFood();
    checkCollision();
  }

  if (dir == LEFT && t_clock == t_clock_lim) {
    t_clock = 0;
    x = x - 1;
    if (x == -1) {
      x = 7;
    }
    moveSnakeTail(x, y);
    checkCollisionWithFood();
    checkCollision();
  }

  if (dir == UP && t_clock == t_clock_lim) {
    t_clock = 0;
    y = y + 1;
    if (y == 8) {
      y = 0;
    }
    moveSnakeTail(x, y);
    checkCollisionWithFood();
    checkCollision();
  }

  if (dir == DOWN && t_clock == t_clock_lim) {
    t_clock = 0;
    y = y - 1;
    if (y == -1) {
      y = 7;
    }
    moveSnakeTail(x, y);
    checkCollisionWithFood();
    checkCollision();
  }

  int valX = analogRead(A0);
  int valY = analogRead(A1);

  // snake not going into himself
  if (valX > 1000 && !(valY > 400 && valY < 600)) {
    return;
  }
  if (valX < 10 && !(valY > 400 && valY < 600)) {
    return;
  }
  if (valY > 1000 && !(valX > 400 && valX < 600)) {
    return;
  }
  if (valY < 10 && !(valX > 400 && valX < 600)) {
    return;
  }

  if (valX > 400 && valX < 600)
    lastValX = valX;

  if (valX > 1000 && lastValX < 1000 && (dir != LEFT || (dir == LEFT && n == 1))) {
    lastValX = valX;
    dir = RIGHT;
  } else if (valX < 10 && lastValX > 10  && (dir != RIGHT || (dir == RIGHT && n == 1))) {
    lastValX = valX;
    dir = LEFT;
  }

  if (valY > 400 && valY < 600)
    lastValY = valY;

  if (valY > 1000 && lastValY < 1000  && (dir != UP || (dir == UP && n == 1))) {
    lastValY = valY;
    dir = DOWN;
  } else if (valY < 10 && lastValY > 10  && (dir != DOWN || (dir == DOWN && n == 1))) {
    lastValY = valY;
    dir = UP;
  }
}

void moveSnakeTail(int x, int y) {
  // turn on the pixel
  pixels[x][y] = LOW;

  // don't turn off the last pixel of the tail when the head is exactly near the end of the tail
  bool off = true;
  if (x == snakeX[n - 1] && y == snakeY[n - 1]) {
    off = false;
  }

  // check if the food reached the end of the tail
  if (m >= 0 && snakeX[n - 1] == snakeFoodX[m] && snakeY[n - 1] == snakeFoodY[m]) {
    ++m;
    ++n;
    snakeX[n] = x;
    snakeY[n] = y;
  }

  // update tail
  for (int i = 0; i < n; ++i) {
    int lastX = snakeX[i];
    int lastY = snakeY[i];
    snakeX[i] = x;
    snakeY[i] = y;
    x = lastX;
    y = lastY;
  }

  if (off == true) {
    //turn off the pixel
    pixels[x][y] = HIGH;
  }
}

// spawn food
void updateFood() {
  // check if the food is spawned correctly
  bool collision = true;
  while (collision) {
    foodX = random(0, 8);
    foodY = random(0, 8);

    collision = false;
    for (int i = 0; i < n; ++i) {
      if (foodX == snakeX[i] && foodY == snakeY[i]) {
        collision = true;
      }
    }

    for (int i = 0; i <= t; ++i) {
      if (foodX == envX[i] && foodY == envY[i]) {
        collision = true;
      }
    }
  }

  pixels[foodX][foodY] = LOW;
}

// check if the snake ate the food
void checkCollisionWithFood() {
  if (x == foodX && y == foodY) {
    ++score;
    
    if (score == 4 && lvl == 1) {
      lvl = 2;
      generateLvl2();
      InitLvl();
      generateLvl2();
    } else if (score == 6 && lvl == 2) {
      lvl = 3;
      generateLvl3();
      InitLvl();
      generateLvl3();
    } else if (score == 8 && lvl == 3) {
      lvl = 4;
      generateLvl4();
      InitLvl();
      generateLvl4();
    } else if (score == 50 && lvl == 4) {
      gameOver = true;
      checkCollision();
    }

    ++m;
    snakeFoodX[m] = foodX;
    snakeFoodY[m] = foodY;

    updateFood();
  }
}

// check collision with obstacles
void checkCollision() {
  for (int i = 1; i < n; ++i) {
    if (x == snakeX[i] && y == snakeY[i]) {
      gameOver = true;
    }
  }

  for (int i = 0; i <= t; ++i) {
    if (x == envX[i] && y == envY[i]) {
      gameOver = true;
    }
  }

  if (gameOver == true && score != 0) {
    // initialization
    lastScore = score;
    score = 0;
    lvl = 1;

    f_clock_lim = 0;
    t_clock_lim = 400;
    t_clock = 0;
    tm_clock = 0;

    // generate the message and the score when the game is over
    currScene = -1;
    nrScene = 0;
    for (int x = 2; x <= 5; ++x) {
      for (int y = 6; y >= 1; --y) {
        if (gameOverMatrix[6 - y][x - 2] == 1) {
          scene[nrScene][x][y] = 1;
          scene[nrScene + 1][x][y] = 1;
        }
      }
    }
    nrScene = 2;
    for (int x = 3; x <= 4; ++x) {
      for (int y = 6; y >= 1; --y) {
        if (exclamationPoint[6 - y][x - 3] == 1) {
          scene[nrScene][x][y] = 1;
        }
      }
    }

    int cf = nrCifre(lastScore);
    while (cf >= 1) {
      --cf;
      ++nrScene;

      int z = 1;
      for (int i = 1; i <= cf; ++i) {
        z *= 10;
      }
      int nr = (lastScore / z) % 10;
      for (int x = 3; x <= 5; ++ x) {
        for (int y = 6; y >= 2; --y) {
          appendNumber(nr, 6 - y, x - 3, x, y);
        }
      }
    }

    // prevent premature start of the game
    delay(2000);
  }
}

// returns the number of digits of a number
int nrCifre(int nr) {
  int c = 0;
  while (nr != 0) {
    ++c;
    nr /= 10;
  }

  return c;
}

// generate a message containing a number
void appendNumber(int nr, int nrY, int nrX, int x, int y) {
  if (nr == 0 && zero[nrY][nrX] == 1) {
    scene[nrScene][x][y] = 1;
  } else if (nr == 1 && unu[nrY][nrX] == 1) {
    scene[nrScene][x][y] = 1;
  } else if (nr == 2 && doi[nrY][nrX] == 1) {
    scene[nrScene][x][y] = 1;
  } else if (nr == 3 && trei[nrY][nrX] == 1) {
    scene[nrScene][x][y] = 1;
  } else if (nr == 4 && patru[nrY][nrX] == 1) {
    scene[nrScene][x][y] = 1;
  } else if (nr == 5 && cinci[nrY][nrX] == 1) {
    scene[nrScene][x][y] = 1;
  } else if (nr == 6 && sase[nrY][nrX] == 1) {
    scene[nrScene][x][y] = 1;
  } else if (nr == 7 && sapte[nrY][nrX] == 1) {
    scene[nrScene][x][y] = 1;
  } else if (nr == 8 && opt[nrY][nrX] == 1) {
    scene[nrScene][x][y] = 1;
  } else if (nr == 9 && noua[nrY][nrX] == 1) {
    scene[nrScene][x][y] = 1;
  }
}

void refreshScreen() {
  // iterate over the rows (anodes)
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    // take the row pin (anode) high
    digitalWrite(row[thisRow], HIGH);
    // iterate over the cols (cathodes)
    for (int thisCol = 0; thisCol < 8; thisCol++) {
      // get the state of the current pixel
      int thisPixel = pixels[thisRow][thisCol];
      // when the row is HIGH and the col is LOW,
      // the LED where they meet turns on
      digitalWrite(col[thisCol], thisPixel);
      // turn the pixel off
      if (thisPixel == LOW) {
        digitalWrite(col[thisCol], HIGH);
      }
    }
    // take the row pin low to turn off the whole row
    digitalWrite(row[thisRow], LOW);
  }
}
