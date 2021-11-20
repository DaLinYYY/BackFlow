/*
 * @Author: YangSL
 * @version:  
 * @Date: 2021-11-19 16:06:32
 * @Last Modified by: YangSL
 * @LastEditTime: 2021-11-21 02:39:15
 * @Description: 
 */

/* Includes ------------------------------------------------------------------*/
#include "BackFlow.h"

/* Global macro  -------------------------------------------------------------*/
OneButton RButton(BUTTON_PIN, true);


/* Private functions ---------------------------------------------------------*/
void setup() {
    Serial.begin(115200);
    rotaryInit(RButton);

    pinMode(4, OUTPUT); 
    pinMode(16, OUTPUT); 
    // rotaryInit();
 
}

void loop() {
  // put your main code here, to run repeatedly:
  keyProcess(RButton);
  delay(10);
  
}