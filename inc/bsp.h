#ifndef __BSP_H__
#define __BSP_H__

#include "stm32f4xx.h"

#ifdef STM32F429_439xx
	#include "STM32F429I-Discovery/stm32f429i_discovery.h"
#else
#ifdef STM32F40_41xxx
	#include "STM32_EVAL/stm32f4_discovery.h"
#else
	#error MCU type not define
#endif
#endif

#endif
