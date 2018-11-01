#ifndef __adc_h__
#define __adc_h__

void adc_init(void); //初始化 ADC
unsigned short get_adc_val(void); // 获取ADC数值
unsigned short get_bat_vol(void); //获取电池电压

#endif
