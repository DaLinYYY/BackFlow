/*
 * @Author: YangSL
 * @version:  
 * @Date: 2021-11-19 16:06:32
 * @Last Modified by: YangSL
 * @LastEditTime: 2021-11-21 23:59:00
 * @Description: 
 */

/* Includes ------------------------------------------------------------------*/
#include <BackFlow.h>

/* Global macro  -------------------------------------------------------------*/
OneButton RButton(BUTTON_PIN, true);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C Disp(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 22, /* data=*/21);

/* Private macro  -------------------------------------------------------------*/
//系统信息
uint64_t ChipMAC;
char ChipMAC_S[19] = {0};
char CompileTime[20];

/* Private functions ---------------------------------------------------------*/
void setup() {

    //获取系统信息
    ChipMAC = ESP.getEfuseMac();
    sprintf(CompileTime, "%s %s", __DATE__, __TIME__);
    for (uint8_t i = 0; i < 6; i++)
        sprintf(ChipMAC_S + i * 3, "%02X%s", ((uint8_t*) &ChipMAC)[i], (i != 5) ? ":" : "");


    Serial.begin(115200);
    rotaryInit(RButton);

    //初始化OLED
    Disp.begin();
    Disp.setBusClock(921600);
    Disp.enableUTF8Print();
    Disp.setFontDirection(0);
    Disp.setFontPosTop();
    Disp.setFont(u8g2_font_wqy12_t_gb2312);
    Disp.setDrawColor(1);
    Disp.setFontMode(1);

    pinMode(4, OUTPUT); 
    pinMode(16, OUTPUT); 
    // rotaryInit();

    
 
}

void loop() {
  // put your main code here, to run repeatedly:
  keyProcess(RButton);
  delay(10);
  EnterLogo();
  
}