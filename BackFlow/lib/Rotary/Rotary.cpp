/*
 * @Author: YangSL
 * @version:  
 * @Date: 2021-11-19 16:23:38
 * @Last Modified by: YangSL
 * @LastEditTime: 2021-11-19 18:02:58
 * @Description: 
 */
/* Includes ------------------------------------------------------------------*/
#include "../../src/BackFlow.h"
#include "Rotary.h"

/* Global macro  -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static double Count = 0;
static double CountLast = 0;
static double Count_min = 0;
static double Count_max = 0;
static double Count_step = 0;
static uint8_t CounterChanged = 0;

//按键FIFO循环大小
#define RButton_FIFO_Size 10
//按键FIFO读写指针
static uint8_t RButton_FIFO_pwrite = 0;
static uint8_t RButton_FIFO_pread = 0;
//按键FIFO缓存区
static uint8_t RButton_FIFO[RButton_FIFO_Size];
//按键FIFO缓存区有效数据大小
static uint8_t RButton_FIFO_BufferSize = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
 * @brief: 清空FIFO
 * @param {*}
 * @return {*}
 */
void Clear_RButton_FIFO(void)
{
    RButton_FIFO_pread = RButton_FIFO_pwrite;
    memset(RButton_FIFO, 0, RButton_FIFO_Size);
}

/*** 
 * @description: 写按键FIFO
 * @param uint8_t State 要写入FIFO的按键状态值
 * @return 无
 */
static void Write_RButton_FIFO(uint8_t State)
{
    //重置事件计时器
    // TimerUpdateEvent();

    RButton_FIFO[RButton_FIFO_pwrite] = State;
    printf("FIFO写入[%d]=%d\n", RButton_FIFO_pwrite, State);
    //写指针移位
    RButton_FIFO_pwrite++;
    //按键缓冲区数据大小+1
    if (RButton_FIFO_BufferSize < RButton_FIFO_Size) RButton_FIFO_BufferSize++;
    //循环写
    if (RButton_FIFO_pwrite >= RButton_FIFO_Size) RButton_FIFO_pwrite = 0;
    printf("FIFO缓存区大小:%d\n\n", RButton_FIFO_BufferSize);
}

/*** 
 * @description: 读按键FIFO
 * @param {*}
 * @return 按键State
 */
static uint8_t Read_RButton_FIFO(void)
{
    //判断当前按键缓冲区是否有数据
    if (RButton_FIFO_BufferSize == 0) return 0;

    //从按键FIFO缓存读取数据
    uint8_t res = RButton_FIFO[RButton_FIFO_pread];
    printf("FIFO读取[%d]=%d\n", RButton_FIFO_pread, res);
    //读指针移位
    RButton_FIFO_pread++;
    RButton_FIFO_BufferSize--;
    //循环写
    if (RButton_FIFO_pread >= RButton_FIFO_Size) RButton_FIFO_pread = 0;
    printf("FIFO缓存区大小:%d\n\n", RButton_FIFO_BufferSize);
    return res;
}


/*** 
 * @description: 按键单击回调函数
 * @param {*}
 * @return {*}
 */
void rotary_single_click(void)
{
    printf("触发单击事件\n");
    // SetSound(Beep1);
    Write_RButton_FIFO(1);
}

/*** 
 * @description: 按键双击回调函数
 * @param {*}
 * @return {*}
 */
void rotary_double_click(void)
{
    printf("触发双击事件\n");
    // SetSound(Beep2);
    Write_RButton_FIFO(3);
}

/*** 
 * @description: 按键长按回调函数
 * @param {*}
 * @return {*}
 */
void rotary_long_click(void)
{
    printf("触发长按事件\n");
    // SetSound(Beep2);
    Write_RButton_FIFO(2);
}


/**
 * @brief: 编码器检查改变中断
 * @param {*}
 * @return {*}
 */
void ICACHE_RAM_ATTR rotary_counter_IRQHandler(void)
{

    uint8_t a = digitalRead(ROTARY_PIN1);
    uint8_t b = digitalRead(ROTARY_PIN2);
}


/**
 * @name  sys_Counter_Set
 * @brief 设置计数器参数
 * @param {double} c       计数器初始值
 * @param {double} min     计数器最小值
 * @param {double} max     计数器最大值
 * @param {double} step    计数器增量步进
 * @return {*}
 */
void rotary_set_timer(double min, double max, double step, double c)
{
    delay(100);
    Count_min = min * ROTARY_TYPE;
    Count_max = max * ROTARY_TYPE;
    Count_step = step;
    Count = constrain(c * ROTARY_TYPE, Count_min, Count_max);
    Serial.print("设置编码器 -> 最小值:");
    Serial.print(Count_min);
    Serial.print(" 最大值:");
    Serial.print(Count_max);
    Serial.print(" 步进:");
    Serial.print(Count_step);
    Serial.print(" 传入计数:");
    Serial.print(c);
    Serial.print(" 当前计数:");
    Serial.println(Count);
}

/**
 * @brief: 旋钮初始化
 * @param {*}
 * @return {*}
 */
void rotaryInit(void)
{
    //初始化GPIO
    pinMode(ROTARY_PIN1, INPUT_PULLUP);
    pinMode(ROTARY_PIN2, INPUT_PULLUP);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    //初始化按键事件检测
    RButton.attachClick(rotary_single_click);
    RButton.attachDoubleClick(rotary_double_click);
    RButton.attachLongPressStart(rotary_long_click);
    RButton.setDebounceTicks(25);
    RButton.setClickTicks(30);
    RButton.setPressTicks(500);

    //初始化编码器中断
    attachInterrupt(ROTARY_PIN1, rotary_counter_IRQHandler, CHANGE);

    //初始化编码器设置(测试默认)
    rotary_set_timer(-1.2, 6.6, 0.1, 3.14);
}
