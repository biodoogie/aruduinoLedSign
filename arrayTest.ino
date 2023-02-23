#include <FastLED.h>

//pin on arduino where led signal pin is plugged
#define LED_PIN     6

//total number leds for whole sign
#define NUM_LEDS    29

//Number of leds that make up each letter - when added together should equal total leds
const int numA = 3;
const int numN = 2;
const int numG = 3;
const int numE = 2;
const int numL= 3;
const int numB = 2;
const int numO = 3;
const int numT = 2;
const int numI = 3;
const int numC = 2;
const int numS = 4;



//number of letters in the sign
const int NUM_LETTERS = 11;

//each row is one letters rgb value 
  int letterColors[NUM_LETTERS][3] = {
    {
      255, 0, 0
    },
    {
      0, 255, 0
    },
    {
      0, 0, 255
    },
    {
      100, 100, 100
    },
    {
      255, 255, 0
    },
    {
      0,255, 255
    },
     {
      255, 0, 255
    },
    {
      255, 255, 255
    },
    {
      200, 200, 100
    },
    {
      255, 50, 100
    },
    {
      100, 200, 100
    } 
  };
  
  //letterOn  - 0 = off , 1 == on
  int letterOn[NUM_LETTERS] = {0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0};
  //letterFade range from 0 to 255 where 0 is brightest
  int letterFade[NUM_LETTERS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  //Number of leds for each letter  - make sure letters are in the order they are stringed together
  int letterLedNum[NUM_LETTERS] = {numA, numN, numG, numE, numL, numB, numO, numT, numI, numC, numS};
  

  int counter = 0;
  int currentLetter = 0;
  //letterChangeTime - ~time in ms for each change in light 
  //letterFadeTime - time to increment fade value in 
  int letterChangeTime = 300;
  int letterFadeTime = 65;
 long int lastTimeLetterChange = 0;
 long int lastFadeTimeChange = 0;

CRGB leds[NUM_LEDS];
int singleFadeValue;



void setup() {

  FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);


  Serial.begin(9600);
}





void loop() {
  
  
    //changes the state of next letter in sequence  as ordered in array 
    //current letter will go to opposite state on/off
    if ((millis()-lastTimeLetterChange)>letterChangeTime){
    
      currentLetter = counter%NUM_LETTERS;
      letterOn[currentLetter] = !letterOn[currentLetter];
      lastTimeLetterChange = millis();
      letterFade[currentLetter] = 0;
      counter++;
    }


//comment out this if-statment if you do not want letters to fade
    if ((millis()-lastFadeTimeChange)>letterFadeTime){
      for(int k = 0; k < NUM_LETTERS; k++){
        // Serial.println(k);
        if(letterFade[k] >= 255) {
          letterFade[k] = 0;
        } else {
          
          letterFade[k]= letterFade[k]+5;
        
        }
        // delay(10);
        // Serial.println(letterFade[k]);
      }
      lastFadeTimeChange = millis();

    }
    
        
    //updates LEDS
     writeByArray(letterLedNum, letterColors, letterFade, letterOn);
  


    
 }



void writeByArray( int ledNum[NUM_LETTERS], int colors[NUM_LETTERS][3], int fadeValue[NUM_LETTERS], int on[NUM_LETTERS]){
     //elemet in arrays represent one letter
    //on[] = set to zero for letter to be off or one for letter to be on
    //ledNum[] = number of leds in letter
    //colors = coller for each letter  r
    //fadeValue = fadvalue for each letter
    int startValue = 0;
    int endValue = 0;

//sets values for each letter based on the number of leds in the letter
    for (int i = 0; i<NUM_LETTERS; i++){
        
       endValue = startValue+ledNum[i];
        for(int j = startValue; j < endValue; j++) {
            
            leds[j] = CRGB(colors[i][0]*on[i], colors[i][1]*on[i], colors[i][2]*on[i]);
            leds[j].fadeLightBy(fadeValue[i]);
            
        }

        startValue = endValue;
    }
    //updates the led string with new values set above
    FastLED.show();  


}

