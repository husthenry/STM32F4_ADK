#include "usb_bsp.h"
#include "usb_hcd_int.h"
#include "usbh_core.h"
#include "stm32f4xx_it.h"

extern USB_OTG_CORE_HANDLE	USB_OTG_Core_dev;
extern USBH_HOST			USB_Host;

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void) { }

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1)
		;
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{	/* Go to infinite loop when Memory Manage exception occurs */
	while (1)
		;
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{	/* Go to infinite loop when Bus Fault exception occurs */
	while (1)
		;
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{	/* Go to infinite loop when Usage Fault exception occurs */
	while (1)
		;
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void) { }

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void) { }

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void) { }

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void);
void SysTick_Handler(void)
{
    TimingDelay_Decrement();
}

/**
  * @brief  TIM2_IRQHandler
  *         This function handles Timer2 Handler.
  * @param  None
  * @retval None
  */
void USB_OTG_BSP_TimerIRQ(void);
void TIM2_IRQHandler(void)
{
	USB_OTG_BSP_TimerIRQ();
}

/**
  * @brief  OTG_FS_IRQHandler
  *          This function handles USB-On-The-Go FS global interrupt request.
  *          requests.
  * @param  None
  * @retval None
  */
#ifdef USE_USB_OTG_FS
void OTG_FS_IRQHandler(void)
#else
void OTG_HS_IRQHandler(void)
#endif
{
	USBH_OTG_ISR_Handler(&USB_OTG_Core_dev);
}
