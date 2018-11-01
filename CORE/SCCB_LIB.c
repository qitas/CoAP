#include "SCCB.h"
#include <string.h>

typedef unsigned char u8;

static void delay_us(unsigned int us)
{
	int len;
	for (;us > 0; us --)
     for (len = 0; len < 20; len++ );
	//
}



#define SDA_PORT GPIOB
#define SCL_PORT GPIOB
#define SDA_PORT_PIN GPIO_Pin_14
#define SCL_PORT_PIN GPIO_Pin_13



//IO方向设置
#define SDA_IN()  SDAPortIN()
#define SDA_OUT() SDAPortOUT();



#define SDA_H  GPIO_SetBits(SDA_PORT, SDA_PORT_PIN)
#define SDA_L  GPIO_ResetBits(SDA_PORT, SDA_PORT_PIN)

#define SCL_H  GPIO_SetBits(SCL_PORT, SCL_PORT_PIN)
#define SCL_L  GPIO_ResetBits(SCL_PORT, SCL_PORT_PIN)

#define READ_SDA GPIO_ReadInputDataBit(SDA_PORT, SDA_PORT_PIN)

unsigned short I2C_Erorr_Count = 0;

/**************************实现函数********************************************
 *函数原型:		void IIC_Init(void)
 *功　　能:		初始化I2C对应的接口引脚。
 *******************************************************************************/
void IOI2C_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	memset(&GPIO_InitStructure,0x0,sizeof(GPIO_InitStructure));
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  SDA_PORT_PIN; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
	GPIO_Init(SDA_PORT, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin =  SCL_PORT_PIN; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
	GPIO_Init(SCL_PORT, &GPIO_InitStructure); 
}

void InitSCCB(void)
{
	IOI2C_Init();
}

