#include "adc.h"
#include <stm32f0xx.h>

#include "setting.h"
#include "mem.h"
#include "common.h"

void adc_init(void)
{
	__IO uint16_t  ADC1ConvertedValue = 0, ADC1ConvertedVoltage = 0;
	__IO uint32_t ADCmvoltp = 0 ;
	ADC_InitTypeDef          ADC_InitStructure;
	GPIO_InitTypeDef         GPIO_InitStructure;
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef        TIM_OCInitStructure;
	
	  /* GPIOC Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  
  /* ADC1 Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  
  /* Configure ADC Channel11 as analog input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* ADCs DeInit */  
  ADC_DeInit(ADC1);
  
  /* Initialize ADC structure */
  ADC_StructInit(&ADC_InitStructure);
  
  /* Configure the ADC1 in continous mode withe a resolutuion equal to 12 bits  */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(ADC1, &ADC_InitStructure); 
  
  /* Convert the ADC1 Channel 11 with 239.5 Cycles as sampling time */ 
  ADC_ChannelConfig(ADC1, ADC_Channel_1 , ADC_SampleTime_239_5Cycles);   

  /* ADC Calibration */
  ADC_GetCalibrationFactor(ADC1);
  
  /* Enable ADCperipheral[PerIdx] */
  ADC_Cmd(ADC1, ENABLE);     
  
  /* Wait the ADCEN falg */
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN)); 
  
  /* ADC1 regular Software Start Conv */ 
  ADC_StartOfConversion(ADC1);

}

unsigned short get_adc_val()
{
	__IO uint16_t  ADC1ConvertedValue = 0, ADC1ConvertedVoltage = 0;
	__IO uint32_t ADCmvoltp = 0 ;
	
	/* Test EOC flag */
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	
	/* Get ADC1 converted data */
	ADC1ConvertedValue =ADC_GetConversionValue(ADC1);
	
	/* Compute the voltage */
	ADC1ConvertedVoltage = (ADC1ConvertedValue * VOL_REF)/0xFFF;
	
	return ADC1ConvertedVoltage;
}


static void Bubble_Sort_adc(unsigned short *num, int n)
{
    unsigned short i, j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; i + j < n - 1; j++)
        {
            if(num[j] > num[j + 1])
            {
                unsigned short temp = num[j];
                num[j] = num[j + 1];
                num[j + 1] = temp;
            }
            //Print(num, n);
        }
    }
    return;
}

unsigned short get_bat_vol(void)
{
	//return  4321;
	int i=0;
	
  short X;
	for(i=0;i<10;i++)
	{
		mem->adccache[i] = get_adc_val() * 2;
		delayUS(DELAY_ADC);
	}
	
	//ÅÅÐò
	Bubble_Sort_adc(mem->adccache,10);
	
	//È¡¾ùÖµ
	X = 0;
	for(i=3;i<7;i++)
	{
		X += mem->adccache[i];
	}

	
	return X/4;
}

