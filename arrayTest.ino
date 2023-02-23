#include <FastLED.h>

#define LED_PIN     6
#define NUM_LEDS    6

const int aNum = 1;
const int bNum = 1;
const int cNum = 1;
const int dNum = 1;
const int eNum = 1;
const int fNum = 1;
unsigned long lastTime;

const int NUM_LETTERS = 6;
  int letters[NUM_LETTERS][3] = {
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
      255, 0, 0
    },
    {
      0, 255, 0
    },
    {
      0, 0, 255
    }  
  };
  
//  int letterOn[NUM_LETTERS] = {1, 1, 1, 1, 1, 1};
  int letterFade[NUM_LETTERS] = {0, 0, 0, 0, 0, 0};
  int letterLedNum[NUM_LETTERS] = {aNum, bNum, cNum, dNum, eNum, fNum};
  


CRGB leds[NUM_LEDS];




void setup() {

  FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);


  Serial.begin(9600);
}





void loop() {
    lastTime = millis();

    for(int i = 0; i < 3; i++){
      if(letterFade[i] >= 255) {
        letterFade[i] = 0;
      } else {
        letterFade[i]= letterFade[i]+1;
      }
    }
    
    delay(100);
    writeByArray(letterLedNum, letters, letterFade);
    
 }


void writeByArray( int ledNum[], int letterColors[NUM_LETTERS][3], int fadeValue[]){
     //elemet in arrays represent one letter
    //on[] = set to zero for letter to be off or one for letter to be on
    //ledNum[] = number of leds in letter
    //rValue  red color value for each letter
    //gValue green color value for each letter
    //bValue blue value for each letter
    //fadeValue = fadvalue for each letter
    int startValue = 0;
    int endValue = 0;

    for (int i = 0; i<NUM_LETTERS; i++){
        
       endValue = startValue+ledNum[i];

        for(int j = startValue; j <= endValue; j++) {
            
            leds[j] = CRGB(letterColors[i][0], letterColors[i][1], letterColors[i][2]);
            leds[j].fadeToBlackBy(fadeValue[i]);
            
        }
        Serial.println(fadeValue[i]);
        startValue = endValue;
    }
    FastLED.show();  

}
