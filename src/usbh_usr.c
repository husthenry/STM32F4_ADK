// #include "lcd_log.h"
#include "usbh_usr.h"

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "xprintf.h"

extern USB_OTG_CORE_HANDLE	USB_OTG_Core_dev;
/*  Points to the DEVICE_PROP structure of current device */
/*  The purpose of this register is to speed up the execution */

USBH_Usr_cb_TypeDef USR_Callbacks =
{
	USBH_USR_Init,							/* HostLibInitialized */
	USBH_USR_DeInit,						/* HostLibInitialized */  
	USBH_USR_DeviceAttached,				/* DeviceAttached */
	USBH_USR_ResetDevice,	
	USBH_USR_DeviceDisconnected,
	USBH_USR_OverCurrentDetected,
	USBH_USR_DeviceSpeedDetected,			/* DeviceSpeed */
	USBH_USR_Device_DescAvailable,			/* DeviceDescriptor is available */
	USBH_USR_DeviceAddressAssigned,			/* Address is assigned to USB Device */
	USBH_USR_Configuration_DescAvailable,	/* Configuration Descriptor available */
	USBH_USR_Manufacturer_String,			/* ManufacturerString*/
	USBH_USR_Product_String,				/* ProductString*/
	USBH_USR_SerialNum_String,				/* SerialNubString*/
	USBH_USR_EnumerationDone,				/* Enumeration finished */
	USBH_USR_UserInput,
	USBH_USR_ADK_Application,
	USBH_USR_DeviceNotSupported,			/* Device is not supported*/
	USBH_USR_UnrecoveredError
};

/**
* @brief  USBH_USR_Init 
* @param  None
* @retval None
*/
void USBH_USR_Init(void)
{
	static uint8_t startup = 0;  
	if(startup == 0 )
	{
		startup = 1;
		debug_puts("> Host Library Initialized\n");
	}
}

/**
* @brief  USBH_USR_DeviceAttached 
* @param  None
* @retval None
*/
void USBH_USR_DeviceAttached(void)
{
	debug_puts("> Device Attached\n");
}

/**
* @brief  USBH_USR_UnrecoveredError
* @param  None
* @retval None
*/
void USBH_USR_UnrecoveredError (void)
{
	debug_puts("> UNRECOVERED ERROR STATE\n");
}

/**
* @brief  USBH_DisconnectEvent
*         Device disconnect event
* @param  None
* @retval None
*/
void USBH_USR_DeviceDisconnected (void)
{
	debug_puts("> Device Disconnected\n");
}

/**
* @brief  USBH_USR_ResetUSBDevice 
*         Reset USB Device
* @param  None
* @retval None
*/
void USBH_USR_ResetDevice(void)
{
	/* Users can do their application actions here for the USB-Reset */
}

/**
* @brief  USBH_USR_DeviceSpeedDetected 
*         Displays the message on LCD for device speed
* @param  Devicespeed : Device Speed
* @retval None
*/
void USBH_USR_DeviceSpeedDetected(uint8_t DeviceSpeed)
{
#ifdef DEBUG
	if(DeviceSpeed == HPRT0_PRTSPD_HIGH_SPEED)
		debug_puts("> High speed device detected\n");
	else if(DeviceSpeed == HPRT0_PRTSPD_FULL_SPEED)
		debug_puts("> Full speed device detected\n");
	else if(DeviceSpeed == HPRT0_PRTSPD_LOW_SPEED)
		debug_puts("> Low speed device detected\n");
	else
		debug_puts("> Device fault \n");
#endif
}

/**
* @brief  USBH_USR_Device_DescAvailable 
*         Displays the message on LCD for device descriptor
* @param  DeviceDesc : device descriptor
* @retval None
*/
void USBH_USR_Device_DescAvailable(void *DeviceDesc)
{
#ifdef DEBUG
	char temp[20];    
	USBH_DevDesc_TypeDef *hs;
	hs = DeviceDesc;  

	debug_puts("Device Descriptor\n");
	sprintf(temp, "Class : %02Xh\n",	(uint8_t)(*hs).bDeviceClass);
	debug_puts(temp);

	sprintf(temp, "SubClass : %02Xh\n",	(uint8_t)(*hs).bDeviceSubClass);
	debug_puts(temp);

	sprintf(temp, "Protocol : %02Xh\n",	(uint8_t)(*hs).bDeviceProtocol);
	debug_puts(temp);

	sprintf(temp, "VID : %04Xh\n",		(uint32_t)(*hs).idVendor); 
	debug_puts(temp);

	sprintf(temp, "PID : %04Xh\n",		(uint32_t)(*hs).idProduct); 
	debug_puts(temp);
#endif
}

/**
* @brief  USBH_USR_DeviceAddressAssigned 
*         USB device is successfully assigned the Address 
* @param  None
* @retval None
*/
void USBH_USR_DeviceAddressAssigned(void)
{
}

/**
* @brief  USBH_USR_Conf_Desc 
*         Displays the message on LCD for configuration descriptor
* @param  ConfDesc : Configuration descriptor
* @retval None
*/
void USBH_USR_Configuration_DescAvailable(
	USBH_CfgDesc_TypeDef * cfgDesc,
	USBH_InterfaceDesc_TypeDef *itfDesc,
	USBH_EpDesc_TypeDef *epDesc
	)
{
#ifdef DEBUG
	char temp[100];
	USBH_InterfaceDesc_TypeDef *id;
	id = itfDesc;  

	sprintf(temp, "Interface : %02X %02X\n", (uint8_t)(*id).bInterfaceClass, (uint8_t)(*id).bInterfaceSubClass);
	debug_puts(temp);
	sprintf((char *)temp , "Power info: bmAttributes:0x%02X, bMaxPower:%d\n",cfgDesc->bmAttributes, cfgDesc->bMaxPower );
	debug_puts(temp);
#endif
}

/**
* @brief  USBH_USR_Manufacturer_String 
*         Displays the message on LCD for Manufacturer String 
* @param  ManufacturerString : Manufacturer String of Device
* @retval None
*/
void USBH_USR_Manufacturer_String(void *ManufacturerString)
{
#ifdef DEBUG
	char temp[100];
	sprintf(temp, "Manufacturer : %s\n", (char *)ManufacturerString);
	debug_puts(temp);
#endif
}

/**
* @brief  USBH_USR_Product_String 
*         Displays the message on LCD for Product String
* @param  ProductString : Product String of Device
* @retval None
*/
void USBH_USR_Product_String(void *ProductString)
{
#ifdef DEBUG
	char temp[100];
	sprintf(temp, "Product : %s\n", (char *)ProductString);  
	debug_puts(temp);
#endif
}

/**
* @brief  USBH_USR_SerialNum_String 
*         Displays the message on LCD for SerialNum_String 
* @param  SerialNumString : SerialNum_String of device
* @retval None
*/
void USBH_USR_SerialNum_String(void *SerialNumString)
{
#ifdef DEBUG
	char temp[100];
	sprintf(temp, "Serial Number : %s\n", (char *)SerialNumString);    
	debug_puts(temp);
#endif
} 

/**
* @brief  EnumerationDone 
*         User response request is displayed to ask for
*         application jump to class
* @param  None
* @retval None
*/
void USBH_USR_EnumerationDone(void)
{
	debug_puts("> Enumeration completed\n");
} 

/**
* @brief  USBH_USR_DeviceNotSupported
*         Device is not supported
* @param  None
* @retval None
*/
void USBH_USR_DeviceNotSupported(void)
{
	debug_puts("> Device not supported.\n");
}  


/**
* @brief  USBH_USR_UserInput
*         User Action for application state entry
* @param  None
* @retval USBH_USR_Status : User response for key button
*/
USBH_USR_Status USBH_USR_UserInput(void)
{
	USBH_USR_Status usbh_usr_status;
  
//  usbh_usr_status = USBH_USR_NO_RESP;
	usbh_usr_status = USBH_USR_RESP_OK;
  
  /*Key B3 is in polling mode to detect user action */
//  if(STM_EVAL_PBGetState(Button_KEY) == RESET)
//  {
//
//    usbh_usr_status = USBH_USR_RESP_OK;
//
//  }
  
	return usbh_usr_status;
} 

/**
* @brief  USBH_USR_OverCurrentDetected
*         Device Overcurrent detection event
* @param  None
* @retval None
*/
void USBH_USR_OverCurrentDetected (void)
{
	debug_puts("Overcurrent detected.\n");
}


/**
* @brief  USBH_USR_DeInit
*         Deint User state and associated variables
* @param  None
* @retval None
*/
void USBH_USR_DeInit(void)
{
}

/**
* @brief  USBH_USR_ADK_Application
*         Application for ADK
* @param  None
* @retval Staus
*/
int USBH_USR_ADK_Application(void)
{
	debug_puts("> USBH_USR_ADK_Application\n");
	return(0);
}
