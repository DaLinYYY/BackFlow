/*
 * @Author: YangSL
 * @version:  
 * @Date: 2021-11-19 16:06:32
 * @Last Modified by: YangSL
 * @LastEditTime: 2021-11-30 00:32:45
 * @Description: 
 */

/* Includes ------------------------------------------------------------------*/
#include <BackFlow.h>

/* Global macro  -------------------------------------------------------------*/
OneButton RButton(BUTTON_PIN, true);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C Disp(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 22, /* data=*/21);

/* Private macro  -------------------------------------------------------------*/
static portMUX_TYPE my_mutex = portMUX_INITIALIZER_UNLOCKED;

//系统信息
uint64_t ChipMAC;
char ChipMAC_S[19] = {0};
char CompileTime[20];

/* Private functions ---------------------------------------------------------*/
void showTask( void * parameter )
{
    while(1){
        // TextEditor("测试中", "ASDFGHJK");
        // EnterLogo();
        // Serial.println("dsadsds");
        
        portENTER_CRITICAL(&my_mutex);//启动任务调度器
        {
            // EnterLogo();
            
        }
        portEXIT_CRITICAL(&my_mutex);

        vTaskDelay(500);
    }
}

void Task1( void * parameter )
{
    uint32_t Count = 0;
    while(1){
        
        // TextEditor("测试中", "ASDFGHJK");
        // EnterLogo();
        Serial.print("Count = ");
        Serial.println(Count);

        vTaskDelay(5000);
        Count++;
    }
}


void us_create_task(void)
{

    xTaskCreatePinnedToCore(showTask,      //任务函数
                            "showTask",    /* 任务名字 没啥用，就是描述*/
                            1024,           /*堆栈大小，单位为字节*/
                            NULL,           /*作为任务输入传递的参数*/
                            7,              //任务的优先级  Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
                            NULL, 
                            0);             //指定运行任务的CPU

    xTaskCreatePinnedToCore(Task1,           //任务入口函数名作为函数指针调用
                            "Task1",        //任务名
                            2048,           //任务栈
                            NULL,           //传给任务函数的参数
                            2,              //任务优先级
                            NULL,           //任务回传句柄
                            tskNO_AFFINITY);//这个任务将不会固定在某个核心上执行
}


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

    us_create_task();
    EnterLogo();
    // ShowBootMsg();
}

void loop() {
  // put your main code here, to run repeatedly:
    keyProcess(RButton);
    
    
    vTaskDelay(10);
}