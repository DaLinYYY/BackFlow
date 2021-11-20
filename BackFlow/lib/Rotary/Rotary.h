/*
 * @Author: YangSL
 * @version:  
 * @Date: 2021-11-19 16:23:44
 * @Last Modified by: YangSL
 * @LastEditTime: 2021-11-21 02:26:33
 * @Description: 
 */
#ifndef ROTARY_H
#define ROTARY_H

#include "RotaryConfig.h"
/* Includes ------------------------------------------------------------------*/

/* Global  functions ---------------------------------------------------------*/
void rotaryInit(OneButton& rButton);
uint8_t keyProcess(OneButton& rButton);

#endif /* ROTARY_H */
