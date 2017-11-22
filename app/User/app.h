#ifndef __APP_H

#define __APP_H

#include "stm32f10x.h"
#include "regmap.h"

#define HW_VERSION  "1.0"
#define SW_VERSION  "1.0"

#define MODBUS_PARITY_NONE 	0
#define MODBUS_PARITY_ODD 	1
#define MODBUS_PARITY_EVEN 	2

extern SYS_STATUS_T system_status;

extern COMM_SETTINGS_T comm_settings;

extern MEASURE_SETTINGS_T measure_settings;

extern CALIB_SETTINGS_T calib_settings;

extern FILTER_SETTINGS_T filter_settings;

extern MEASURE_VALUES_T measure_values;

extern SENSOR_PARAM_T sensor_param;

void System_Init(void);
void Parameters_Reset(void);
void LED_TurnOn(void);
void LED_TurnOff(void);
void TIM3_Init(void);

#endif
