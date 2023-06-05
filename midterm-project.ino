//CONSTANTS
const int MESSAGES_PER_PASSAGE =  20;
const int CHOICES_PER_PASSAGE  =  2;
const int TYPEWRITER_DELAY     = 50;

const int LINES_PER_MESSAGE   =  2; 
const int CHARACTERS_PER_LINE = 16;

int meow = 1;

//STRUCTURES
typedef struct varr{
    char lines[LINES_PER_MESSAGE][CHARACTERS_PER_LINE + 1];
    int action;
} Message;

typedef struct {
    char lines[LINES_PER_MESSAGE][CHARACTERS_PER_LINE + 1];
    int target;
} Choice;

typedef struct{
    Message messages[MESSAGES_PER_PASSAGE];
    Choice choices[CHOICES_PER_PASSAGE];
} Passage;

const Passage story[4] PROGMEM = {
  {
    {
      {
        {"You woke up in a","cold and snowy"},-1},
      {
        {"place, wounded","and alone."},-1},
      {
        {"A mysterious","figure approach"},-1},
      {
        {"-es and starts","healing you up."},-1},
      {
        {"You feel your","strength slowly"},-1},
      {
      	{"returning. As","soon as you're"},-1},
      {
        {"back on your","feet, the figure"},-1},
      {
        {"disappears","without a word."},-1},
      {
        {"You decide to","continue your"},-1},
      {
        {"journey to kill","the bad king,"},-1},
      {
        {"and along the","way, you"},-1},
      {
        {"encounter fights","with his guards."},-1},
      {
        {"You also come","across citizens"},-1},
      {
        {"enslaved inside","the castle, and"},-1},
      {
      	{"you help them","escape in their"},-1},
      {
        {"current state.","After escorting,"},-1},
      {
        {"the citizens out","of the castle,"},-1},
      {
        {"What should you","do next?"},-1}},
    {
      {
        {"1.Proceed with","your journey."},1},
      {
        {"2.Leave the","castle."},3}}},
  {
    {
      {
        {"You successfully","battle the"},3},
      {
        {"guards of the","bad king and"},-1},
      {
        {"find yourself","facing him,"},-1},
      {
        {"begging for.","mercy."},-1},
      {
        {"What will you","do?"},0}},
    {
      {
        {"1.Behead the","king."},2},
      {
        {"2.Spare the king","and arrest him."},2}}},
  {
    {
      {
        {"As a result of","your actions,"},-1},
      {
        {"the kingdom is","finally at peace"},-1},
      {
        {"You return home","as a hero, and"},2},
      {
        {"the people","celebrate your"},-1},
      {
        {"bravery and","heroism."},-1},
      {
        {"You celebrate","with a green LED"},-1},
      {
        {"Thank you for","reading!"},0}},
    {
      {
        {"",""},-1},
      {
        {"",""},-1}}},
  {
    {
      {
        {"You decided to","leave your"},1},
      {
        {"journey.","However, the"},-1},
      {
        {"king's guards","quickly learn of"},-1},
      {
        {"your involvement","in the castle,"},-1},
      {
        {"and you become a","wanted fugitive."},-1},
      {
        {"The slavery and","trafficking in"},-1},
      {
        {"the kingdom","continues. You"},-1},
      {
        {"become a","wanderer and"},-1},
      {
        {"wondered if it","was the right"},-1},
      { 
        {"decision, but","you find solace"},-1},
      {
        {"you had helped","others."},0}},
    {
      {
        {"",""},-1},
      {
        {"",""},-1}}}};

#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int NEXT_BUTTON_PIN = 12;
const int CONFIRM_BUTTON_PIN = 13;


const int RED_LED_PIN   =  9;
const int GREEN_LED_PIN = 10;

LiquidCrystal_I2C lcd(0x27, 16, 2); 

int a=0, b=0, c=0, d=0; //inputted values
int C1=0, C2=0, C3=0, C4=0; //password
int var=0; 

const byte rows = 4; 
const byte columns = 4;
char key[rows][columns] = 
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pinRows[rows] = {A0, A1, A2, A3}; 
byte pinColumns[columns] = {3, 2, 1, 0}; 

Keypad keypad = Keypad( makeKeymap(key), pinRows, pinColumns, rows, columns );

void setup()
{
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  lcd.begin(CHARACTERS_PER_LINE, LINES_PER_MESSAGE);
  Serial.begin(9600);
  
  
  
  pinMode(NEXT_BUTTON_PIN,    OUTPUT);
  pinMode(CONFIRM_BUTTON_PIN, OUTPUT);

  pinMode(RED_LED_PIN,   OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
}

// State of each button (HIGH or LOW).
int nextPressed;
int confirmPressed;

// Current index of our position in the story.
int currentPassage =  0;
int currentMessage = -1;
int currentChoice  = -1;

// Containers used to hold each message/choice as we load them from memory.
Message message;
Choice choice;

// Prints a message or choice with a stylish delay between characters.
void printLines(char lines[LINES_PER_MESSAGE][CHARACTERS_PER_LINE + 1])
{
    lcd.clear();
    for (int row = 0; row < LINES_PER_MESSAGE; row++)
    {
        for (int column = 0; column < CHARACTERS_PER_LINE; column++)
        {
            char letter = lines[row][column];

            if (letter != NULL)
            {
                lcd.setCursor(column, row);
                lcd.print(lines[row][column]);
                delay(TYPEWRITER_DELAY);
            }
        }
    }
}


void loop()
{
  
  char key = keypad.getKey();
  if (key)
  {
   
   lcd.setCursor(6+var,1);// value of var is used to increment the
                          //column position of the cursor with each keypress
   lcd.print(key),lcd.setCursor(6+var,1);
   key=key-48;//ASCII values of the characters need to be converted to their corresponding decimal values. 
              //In the ASCII table, the character "0" has an ASCII value of 48, "1" has an ASCII value of 49, and so on.
  }   
  if(key == 1 && meow == 1)
  {
    lcd.setCursor(0, 1);
    lcd.print("OPENED");
    meow += 1;
    key += 1;
  }
  if (key != 1 && meow == 1)
  {
    lcd.setCursor(0,0),lcd.print("'1' to play !");
    lcd.setCursor(0, 1);
    lcd.print("CLOSED");
    key += 1;
  }

  readButtons();

  // If we've pressed the next button...
  if (nextPressed)
  {
    // If we haven't read all messages, advance to the next message in the passage.
    if (currentMessage < MESSAGES_PER_PASSAGE - 1)
    {
      advancePassage();
    }
    // Otherwise, cycle to the next available choice.
    else
    {
      cycleChoice();
    }
  }

  if (confirmPressed && currentMessage == MESSAGES_PER_PASSAGE - 1)
  {
    currentPassage = choice.target;

    currentMessage = -1;
    currentChoice = -1;

    advancePassage();
  }
}

// Reads the state of two buttons that are connected to our project.
void readButtons()
{
    nextPressed = digitalRead(NEXT_BUTTON_PIN);
    confirmPressed = digitalRead(CONFIRM_BUTTON_PIN);
}

// Prints the next message in the current passage and executes and action if there's any.
void advancePassage()
{
    currentMessage++;

    readMessageFromPROGMEM(); 

    if (message.action != -1)
    {
        activateAction(message.action);
    }

    printLines(message.lines);
}

// Reads the current message from PROGMEM and saves it to 'message'.
void readMessageFromPROGMEM()
{
    memcpy_P(&message, &story[currentPassage].messages[currentMessage], sizeof message);
}

// Cycles and prints the next choice in the current passage, or jumps to the end if the passage is terminal.
void cycleChoice()
{
    incrementCurrentChoice();
            
    readChoiceFromPROGMEM();

    if (choice.target != -1)   
    {
        printLines(choice.lines);
    }
    else
    {
        printEnding();
    }
    
}

// Prints our ending screen.
void printEnding()
{
    lcd.setCursor(0, 0);
    lcd.print(F("      THE      "));
    lcd.setCursor(0, 1);
    lcd.print(F("      END      "));
}

// Selects the next choice, returning to the first one once we've seen them all.
void incrementCurrentChoice()
{
    if (currentChoice < CHOICES_PER_PASSAGE - 1)
    {
        currentChoice++;
    }
    else
    {
        currentChoice = 0;
    }
}

// Reads the current choice from PROGMEM and saves it to 'choice'. */
void readChoiceFromPROGMEM()
{
    memcpy_P(&choice, &story[currentPassage].choices[currentChoice], sizeof choice);
}

// Calls an action corresponding to the number you put in the message.
void activateAction(int action)
{
    switch(action)
    {
    case 0:
        colorLED(0, 0);
        break;    
    case 1:
        colorLED(255, 0);
        break;
    case 2:
        colorLED(0, 255);
        break;
    }
}

void colorLED(int r, int g)
{
    analogWrite(RED_LED_PIN,   r);
    analogWrite(GREEN_LED_PIN, g);

}