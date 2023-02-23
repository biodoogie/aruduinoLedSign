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
      255, 0, 0
    },
    {
      0, 255, 0
    },
    {
      0, 0, 255
    }  
  };
  
  //letterOn  - 0 = off , 1 == on
  int letterOn[NUM_LETTERS] = {0, 0, 0, 0, 0, 0};
  //letterFade range from 0 to 255 where 0 is brightest
  int letterFade[NUM_LETTERS] = {0, 0, 0, 0, 0, 0};
  //Number of leds for each letter 
  int letterLedNum[NUM_LETTERS] = {aNum, bNum, cNum, dNum, eNum, fNum};
  

  int counter = 0;
  int currentLetter = 0;

CRGB leds[NUM_LEDS];
int singleFadeValue;



void setup() {

  FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);


  Serial.begin(9600);
}





void loop() {
    lastTime = millis();


  
    // for(int k = 0; k < NUM_LETTERS; k++){
    //   // Serial.println(k);
    //   if(letterFade[k] >= 255) {
    //     letterFade[k] = 0;
    //   } else {
    //     singleFadeValue = letterFade[k];
    //     letterFade[k]= singleFadeValue+1;
      
    //   }
    //   // delay(10);
    //   // Serial.println(letterFade[k]);
    // }


    
    
    
    //currentLetter to turn on or off
    currentLetter = counter%NUM_LETTERS;
    //current letter will go to opposite state on/off
    letterOn[currentLetter] = !letterOn[currentLetter];
        
    
     writeByArray(letterLedNum, letterColors, letterFade, letterOn);
     //Delay determines how quickly move betweent letters
     delay(500);
    counter++;
 }



void writeByArray( int ledNum[NUM_LETTERS], int colors[NUM_LETTERS][3], int fadeValue[NUM_LETTERS], int on[NUM_LETTERS]){
     //elemet in arrays represent one letter
    //on[] = set to zero for letter to be off or one for letter to be on
    //ledNum[] = number of leds in letter
    //colors = coller for each letter  r
    //fadeValue = fadvalue for each letter
    int startValue = 0;
    int endValue = 0;

    for (int i = 0; i<NUM_LETTERS; i++){
        
       endValue = startValue+ledNum[i];

        for(int j = startValue; j < endValue; j++) {
            
            leds[j] = CRGB(colors[i][0]*on[i], colors[i][1]*on[i], colors[i][2]*on[i]);
            singleFadeValue = fadeValue[i];
            leds[j].fadeToBlackBy(singleFadeValue);
            
        }
        if (i==1){
                  
                  // Serial.println(fadeValue[i]);


        }
        startValue = endValue;
    }
    FastLED.show();  


}

