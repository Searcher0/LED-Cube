/*  Date: 2022/03/28
 *   By: Muneeb Zaidi
 *   This code controls an LED Cube, displays animations and allows for individual LED Control.
 *   Each game/animation is controlled through four seperate switches on the arduino due board.
 *   Snake Game: A snake animation is played moving from the bottom to the top, showing a slithering snake.
 *   Pong Game: Control each LED individually through the potentiometer which control the X, Y & Z values.
 *   Diaonal Game: Shows an animation of LED's blinking diagonally and moving through floors.
 *   Letter Game: Displays three letters on the top floor (multiplexing) letters are S, M, and Z.
*/

/*Setup the Global Variables*/

/*Creating the Switch for Each Game*/
boolean game1;
boolean game2;
boolean game3;
boolean game4;

/* Set the switch PINS */
int btnIn[4] = {2, 3, 4, 5};
int btnOut[4] = {8, 9, 10, 11};

/* screenTime sets how long each letter is displayed */
int screenTime = 80;

/*Initializing the Arrays for the Letter Game*/
int letterM[5][3] = {
  
  {41, 40, 30},//0
  {31, 32},//1
  {23, 24},//2
  {28}     //4
};
int letterS[6] = {51, 52, 41, 30, 23, 22};

int letterZ[5][3] = {

  {53, 25, 42},//0
  {51, 23, 31},//1
  {52, 22},//2
  {50, 24},//3
  {28}     //4
};

/* Initializing the Arrays for the Snake Game */
int snake[5][4] = {

  {53, 23, 52, 24},
  {43, 31, 42, 32},
  {33, 41, 30, 40},
  {25, 51, 22, 50},
  {27, 26, 28}
};

int invertedSnake[5][4] = {
  {50, 22, 51, 25},
  {40, 30, 41, 33},
  {32, 42, 31, 43},
  {24, 52, 23, 53},
  {27, 26, 28}
};

/* Initializing the Array for the Diagonal Game*/
int diagonal[5][4] = {

  {25, 31, 30, 32},
  {33, 22, 24, 52},
  {23, 53, 51, 40},
  {43, 41, 42, 50},
  {27, 26, 28 }
};

/* Initializing the Array for the PONG Game*/
int pinMatrix[5][4] = {

  {53, 51, 52, 50},
  {43, 41, 42, 40},
  {33, 31, 30, 32},
  {25, 23, 22, 24},
  {28, 26, 27}
};

int analogVal[3] = {0 , 0, 0};      //store sensed values here.
int analogPins[3] = {A5, A8, A10};  //Set Analog Pins
int zPins[3] = {28, 26, 27};        //Set Floor pins


void setup() {

  /*Initialize the Switch Code*/

//INPUT
  for (int btn = 0; btn < 4; btn++) {
    pinMode(btnIn[btn], INPUT);
  }
//OUTPUT
  for (int btn = 0; btn < 4; btn++) {
    pinMode(btnOut[btn], OUTPUT);
  }

/* Set LED's as OUTPUT. */
  for (int z = 0; z < 3; z++) {
    pinMode(pinMatrix[4][z], OUTPUT);
    for (int y = 0; y < 4; y++) {
      for (int x = 0; x < 4; x++) {
        pinMode(pinMatrix[x][y], OUTPUT);
        digitalWrite(pinMatrix[x][y], HIGH);
      }
    }
  }
  
 //Analog PINS set as INPUT
  for (int i = 0; i < 3; i++) {
    pinMode(analogPins[i], INPUT);
  }
}

/* Create a snake animation, slither from left to right through the floors. */
void Snake()
{
  for (int z = 0; z < 3; z++) {     // Move to next floor once the nested code is complete.

    for (int y = 0; y < 4; y++) {   // Move within the columns of the array increasing by 1, four times.

      for (int x = 0; x < 4; x++) { // Move within the rows of the array increasing by 1, four times.
/* Determine which Array to use depending on which floor the animation is currently on. */
        if (z == 0) {
          digitalWrite(snake[4][z], HIGH);
          digitalWrite(snake[x][y], LOW);
          delay(300);
          digitalWrite(snake[x][y], HIGH);
        } else if (z == 1) {

          digitalWrite(invertedSnake[4][z], HIGH);
          digitalWrite(invertedSnake[x][y], LOW);
          delay(300);
          digitalWrite(invertedSnake[x][y], HIGH);

        } else if (z == 2) {
          digitalWrite(snake[4][z], HIGH);
          digitalWrite(snake[x][y], LOW);
          delay(300);
          digitalWrite(snake[x][y], HIGH);
        }
      }
    }
    digitalWrite(snake[4][z], LOW);
  }
}

/* Navigate the LED Matrix diagonally */
void Diagonal () {

  for (int z = 0; z < 3; z++) {     // Move to next floor once the nested code is complete.

    for (int y = 0; y < 4; y++) {   // Move within the columns of the array increasing by 1, four times.

      for (int x = 0; x < 4; x++) { // Move within the rows of the array increasing by 1, four times.

        digitalWrite(diagonal[4][z], HIGH);
        digitalWrite(diagonal[x][y], LOW);
        delay(300);
        digitalWrite(diagonal[x][y], HIGH);
      }
    }
    digitalWrite(diagonal[4][z], LOW);
  }
}

/* Display 3 Letters on the first Floor of the LED Matrix */

void Letters () {

  for (int z = 0; z < screenTime; z++) { // Display letter (screenTime) times.
    for (int x = 0; x < 6; x++) {        // Move within the array increasing by 1, six times.

      digitalWrite(28, HIGH);            // Turn the first floor ON.
      digitalWrite(letterS[x], LOW);     // Turn the array ON.
      delay(1);
      digitalWrite(letterS[x], HIGH);    //Turn the array OFF.
    }
    digitalWrite(28, LOW);               // Turn the first floor OFF.
  }
  delay(500);

  for (int z = 0; z < screenTime; z++) { // Display letter (screenTime) times.
    for (int y = 0; y < 4; y++) {        // Move within the columns of the array increasing by 1, four times.
      for (int x = 0; x < 4; x++) {      // Move within the rows of the array increasing by 1, four times.

        digitalWrite(letterM[4][0], HIGH); // Turn the first floor ON.
        digitalWrite(letterM[x][y], LOW);  // Turn the Matrix ON.
        delay(1);
        digitalWrite(letterM[x][y], HIGH); // Turn the Matrix OFF.
      }
    }
    digitalWrite(letterM[4][0], LOW);      // Turn the first floor OFF.
  }
  delay(500);

  for (int z = 0; z < screenTime; z++) { // Display letter (screenTime) times.
    for (int y = 0; y < 4; y++) {        // Move within the columns of the array increasing by 1, four times.
      for (int x = 0; x < 4; x++) {      // Move within the rows of the array increasing by 1, four times.

        digitalWrite(letterZ[4][0], HIGH);
        digitalWrite(letterZ[x][y], LOW);
        delay(1);
        digitalWrite(letterZ[x][y], HIGH);
      }
    }
    digitalWrite(letterZ[4][0], LOW);
  }
  delay(500);
}

/* Create grid of the entire LED Matrix */
void Grid (int x, int y, int z, int timeDelay = 5) {
  for (int v = 0; v < 3; v++) {
    digitalWrite(zPins[v], LOW);
    for (int b = 0; b < 4; b++) {
      for (int n = 0; n < 4; n++) {
        digitalWrite(pinMatrix[b][n], HIGH);
        delay(timeDelay);
        digitalWrite(zPins[z], HIGH);
        digitalWrite(pinMatrix[x][y], LOW);
      }
    }
    digitalWrite(pinMatrix[x][y], HIGH);
    digitalWrite(zPins[z], HIGH);
  }
}

/* Use the grid to control each led utilizing the Potentiometers. */

void PONG() {
  
/* Using the map function, map the lowest and max values. Utilize the input recieved from the potentiometers attached to the analog pins
    and store the current value within the analogVal variable for each potentiometer. */
  analogVal[0] = map(analogRead(analogPins[0]), 0, 1023, 0, 3);   //
  analogVal[1] = map(analogRead(analogPins[1]), 0, 1023, 0, 3);
  analogVal[2] = map(analogRead(analogPins[2]), 0, 1023, 0, 2);

/* Utilize void Grid to set the x, y, and z variables as the analogValues read. Determines the X, Y & Z positions based on the values of the potentiometer. */
  Grid(analogVal[0], analogVal[1], analogVal[2]);
}

  /* The code that runs constantly */

void loop () {

  /* Initialize the switches */
 for (int Out = 0; Out < 4; Out++) {
  digitalWrite(btnOut[Out], LOW);
 }
  /* Read the digital pins and store their data into the boolean variables. */
  game1 = digitalRead(2);
  game2 = digitalRead(3);
  game3 = digitalRead(4);
  game4 = digitalRead(5);

/* Determine which wire is out and turn that game on. Detect all the wires that are plugged in and turn those games off.
    One Game Displayed At A Time.*/
    
  if (game1 == HIGH) {
    Snake();
  } else if (game2 == HIGH) {
    Diagonal();
  } else if (game3 == HIGH) {
    PONG();
  } else if (game4 == HIGH) {
    Letters();
  } else {
    digitalWrite(13, HIGH);
  }
}
