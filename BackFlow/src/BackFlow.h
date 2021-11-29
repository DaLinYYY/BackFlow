/*
 * @Author: YangSL
 * @version:  
 * @Date: 2021-11-19 16:29:36
 * @Last Modified by: YangSL
 * @LastEditTime: 2021-11-30 00:20:56
 * @Description: 
 */


#ifndef BACKFLOW_H
#define BACKFLOW_H

/* Includes ------------------------------------------------------------------*/
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// #include <OneButton.h>
// #include <Rotary.h>
#include "../lib/OneButton/src/OneButton.h"
#include "../lib/U8g2/src/U8g2lib.h"


#include "Rotary/Rotary.h"
#include "Draw/ExternDraw.h"
#include "Draw/Bitmap.h"

/* Global macro  -------------------------------------------------------------*/
extern OneButton RButton;
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C Disp;
/* Private functions ---------------------------------------------------------*/




#endif /* BACKFLOW_H */

/* Includes ------------------------------------------------------------------*/
/* Global macro  -------------------------------------------------------------*/
#define DEBUG_MODE true

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/