/*
 * @Author: YangSL
 * @version:  
 * @Date: 2021-11-19 16:23:44
 * @Last Modified by: YangSL
 * @LastEditTime: 2021-11-22 22:34:07
 * @Description: 
 */
#ifndef ROTARY_H
#define ROTARY_H

#include "RotaryConfig.h"
/* Includes ------------------------------------------------------------------*/

/* Global  functions ---------------------------------------------------------*/
double rotary_counter_Get(void);
void rotaryInit(OneButton& rButton);
uint8_t keyProcess(OneButton& rButton);

#endif /* ROTARY_H */
