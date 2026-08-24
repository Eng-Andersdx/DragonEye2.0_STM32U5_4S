/**
  ******************************************************************************
  * @file    dragoneye_leds.c
  * @author  Anders Engineering Team
  * @version 1.4
  * @brief   This file provides a set of functions needed to manage the Rotary
  *          LEDs on DragonEYE board.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 Anders Electronics plc.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* File Info : -----------------------------------------------------------------
                                   User NOTES
1. Driver description:
----------------------
   - This driver is used to drive the LEDs on the Rotary modules of the DragonEYE
     board. The Leds supported are controllable in pwm mode as much as simple 
	 toggling mode. Display Backlight is treated the same way as all other LEDs

2. How To use this driver:
--------------------------
  + Initialization steps:
     o Initialize the LEDs module using the BSP_LED_Init(Led) function.
	   This function performs hardware resources initialization and set the 
       internal leds off by default.
	   Backlight can be initialised by passing Led = BACK_LIGHT.

  +  Rotary LEDs on the use
     o Any of the available LED defined in the Led_TypeDef state can be changed
	   on or off by calling either one of the BSP_LED_On(Led) or BSP_LED_Off(Led).
	   Backlight status can be changed by passing Led = BACK_LIGHT.
     o Any LED can be simply toggled regardless of the previous state by calling
	   BSP_LED_Toggle(Led). 
	   Backlight can be toggled by passing Led = BACK_LIGHT.

------------------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "assert.h"
#include "../../../Core/Inc/main.h"
#include "dragoneye_leds.h"


#if __DRAGONEYE_LEDS_H != 0104	/* BSP LEDS REVISION v.1.4 */
#error Wrong API version file (dragoneye_leds.h).
#endif


/** @addtogroup BSP
  * @{
  */

/** @addtogroup DragonEYE
  * @{
  */

/** @defgroup DragonEYE_LEDS DragonEYE LEDs
  * @{
  */

/** @defgroup DragonEYE_LEDS_Private_Types_Definitions DragonEYE LEDs Private Types Definitions
  * @{
  */


/**
  * @}
  */

/** @defgroup DragonEYE_LEDS_Private_Defines DragonEYE LEDs Private Types Defines
  * @{
  */




/**
  * @}
  */

/** @defgroup DragonEYE_LEDS_Private_Macros DragonEYE LEDs Private Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup DragonEYE_LEDS_Imported_Variables DragonEYE LEDs Imported Variables
  * @{
  */
  /**
    * @}
    */

/** @defgroup DragonEYE_LEDS_Private_Variables DragonEYE LEDs Private Variables
  * @{
  */
uint32_t GPIO_PIN[LEDn] = {DSI_BL_CTRL_Pin,  //Backlight
						   R_LED_GPIO_Pin,  //Red
						   G_LED_GPIO_Pin,  //Green
						   B_LED_GPIO_Pin}; //Blue

GPIO_TypeDef* GPIO_PORT[LEDn] = {DSI_BL_CTRL_GPIO_Port,
								 R_LED_GPIO_GPIO_Port,
								 G_LED_GPIO_GPIO_Port,
								 B_LED_GPIO_GPIO_Port};

static TIM_HandleTypeDef *tim_handle=NULL, *bl_handle=NULL;  // Static global variable for internal use only
static uint32_t r_channel, g_channel, b_channel, bl_channel;


/**
  * @}
  */

/** @defgroup DragonEYE_LEDS_Private_Function_Prototypes DragonEYE LEDs Private Function Prototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup DragonEYE_LEDS_Public_Functions DragonEYE LEDs Public Functions
  * @{
  */
/**
  * @brief  Initialise PWM Channels for LCD Backlight.
  */
void BSP_BL_PWM_Init(TIM_HandleTypeDef *htim, uint32_t BL_TIM_CH){
	bl_handle = htim;
	bl_channel = BL_TIM_CH;
	HAL_TIM_PWM_Start(bl_handle, bl_channel); //backlight pwm
}

/**
  * @brief  Set the Custom Intensity for the LCD Backlight.
  * @param  uin8_t: DutyCycle for the Backlight PWM Channel which should be between 0-100.
  *         	@arg dutycycle
  */
void BSP_BL_SetIntensity(uint8_t dutycycle){
	assert(dutycycle>=0 && dutycycle<=100&&"The duty cycle should be between 0-100");
	//__HAL_TIM_SET_COMPARE(bl_handle,bl_channel,dutycycle*255);
	__HAL_TIM_SET_COMPARE(bl_handle, bl_channel, dutycycle*bl_handle->Init.Period/100);
}




/**
  * @brief  Initialise PWM Channels for RGB LEDs.
  */
void BSP_LED_PWM_Init(TIM_HandleTypeDef *htim, uint32_t R_TIM_CH, uint32_t G_TIM_CH, uint32_t B_TIM_CH){
	tim_handle = htim;
	r_channel = R_TIM_CH;
	g_channel = G_TIM_CH;
	b_channel = B_TIM_CH;
	HAL_TIM_PWM_Start(tim_handle, r_channel); //red
	HAL_TIM_PWM_Start(tim_handle, g_channel); //Green
	HAL_TIM_PWM_Start(tim_handle, b_channel); //Blue
}

/**
  * @brief  Set the Intensity for the 3 LED's based on colour.
  * @param  uin32_t: Respective DutyCycles for the 3 PWM Channels which should be between 0-100.
  *         There is only 1 Argument as follows:
  *            @arg 1  color
  *            which has duty cycles of R,G,B respectively
  */
void BSP_LED_SetColor(uint32_t color)
{
    uint8_t red_dutycycle = (color & 0xFF);
    uint8_t green_dutycycle = ((color >> 8) & 0xFF);
    uint8_t blue_dutycycle = ((color >> 16) & 0xFF);
    BSP_LED_SetRGBIntensity(red_dutycycle, green_dutycycle, blue_dutycycle);
}

/**
  * @brief  Set the Custom Intensity for the 3 LED's together.
  * @param  uin8_t: Respective DutyCycle for the 3 PWM Channels which should be between 0-100.
  *         There are 3 Arguments as follows:
  *            @arg 1  red_dutycycle
  *            @arg 2   green_dutycycle
  *            @arg 3   blue_dutycycle
  */
void BSP_LED_SetRGBIntensity(uint8_t red_dutycycle, uint8_t green_dutycycle, uint8_t blue_dutycycle){
	assert(red_dutycycle>=0 && red_dutycycle<=100 && green_dutycycle>=0 && green_dutycycle<=100 && blue_dutycycle>=0 && blue_dutycycle<=100 && "The duty cycle should be between 0-100");
	__HAL_TIM_SET_COMPARE(tim_handle, r_channel, red_dutycycle*tim_handle->Init.Period/100);
	__HAL_TIM_SET_COMPARE(tim_handle, g_channel, (green_dutycycle*tim_handle->Init.Period/100)*0.40);
	__HAL_TIM_SET_COMPARE(tim_handle, b_channel, (blue_dutycycle*tim_handle->Init.Period/100)*0.5);
}

/**
  * @brief  Set the Custom Intensity for the Red LED.
  * @param  uin8_t: DutyCycle for the Red PWM Channel which should be between 0-100.
  *         	@arg dutycycle
  */
void BSP_LED_SetRedIntensity(uint8_t dutycycle){
	assert(dutycycle>=0 && dutycycle<=100&&"The duty cycle should be between 0-100");
	__HAL_TIM_SET_COMPARE(tim_handle, r_channel, dutycycle*tim_handle->Init.Period/100);
}

/**
  * @brief  Set the Custom Intensity for the Green LED.
  * @param  uin8_t: DutyCycle for the Green PWM Channel which should be between 0-100.
  *         	@arg dutycycle
  */
void BSP_LED_SetGreenIntensity(uint8_t dutycycle){
	assert(dutycycle>=0 && dutycycle<=100&&"The duty cycle should be between 0-100");
	__HAL_TIM_SET_COMPARE(tim_handle, g_channel, dutycycle*tim_handle->Init.Period/100);
}

/**
  * @brief  Set the Custom Intensity for the Blue LED.
  * @param  uin8_t: DutyCycle for the Blue PWM Channel which should be between 0-100.
  *         	@arg dutycycle
  */
void BSP_LED_SetBlueIntensity(uint8_t dutycycle){
	assert(dutycycle>=0 && dutycycle<=100&&"The duty cycle should be between 0-100");
	__HAL_TIM_SET_COMPARE(tim_handle, b_channel, dutycycle*tim_handle->Init.Period/100);
}







//--------------- BASIC LEDs Switching Function if no PWM available -------------------//







/**
  * @brief  Configures LED GPIO.
  * @param  Led: LED to be configured.
  *          This parameter can be one of the following values:
  *            @arg  BACK_LIGHT
  *            @arg  LED_RED
  *            @arg  LED_GREEN
  *            @arg  LED_BLUE
  */
void BSP_LED_Init(Led_TypeDef Led)
{
  GPIO_InitTypeDef  gpio_init_structure;

  if (Led <= LEDn)
  {
    /* Configure the GPIO_LED pin */
    gpio_init_structure.Pin   = GPIO_PIN[Led];
    gpio_init_structure.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_init_structure.Pull  = GPIO_PULLUP;
    gpio_init_structure.Speed = GPIO_SPEED_HIGH;

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();

    HAL_GPIO_Init(GPIO_PORT[Led], &gpio_init_structure);

    /* By default, turn off LED by setting a high level on corresponding GPIO */
    HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_RESET);

  } /* of if (Led <= LED_BLUE) */

}

/**
  * @brief  DeInit LEDs.
  * @param  Led: LED to be configured.
  *          This parameter can be one of the following values:
  *            @arg  BACK_LIGHT
  *            @arg  LED_RED
  *            @arg  LED_GREEN
  *            @arg  LED_BLUE
  * @note Led DeInit does not disable the GPIO clock nor disable the Mfx
  */
void BSP_LED_DeInit(Led_TypeDef Led)
{
  GPIO_InitTypeDef  gpio_init_structure;

  if (Led <= LEDn)
  {
    /* DeInit the GPIO_LED pin */
    gpio_init_structure.Pin = GPIO_PIN[Led];

    /* Turn off LED */
    HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_RESET);
    HAL_GPIO_DeInit(GPIO_PORT[Led], gpio_init_structure.Pin);
  }

}

/**
  * @brief  Turns selected LED On.
  * @param  Led: LED to be set on
  *          This parameter can be one of the following values:
  *            @arg  BACK_LIGHT
  *            @arg  LED_RED
  *            @arg  LED_GREEN
  *            @arg  LED_BLUE
  */
void BSP_LED_On(Led_TypeDef Led)
{
  if (Led <= LEDn)
  {
     HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_SET);
  }

}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: LED to be set off
  *          This parameter can be one of the following values:
  *            @arg  BACK_LIGHT
  *            @arg  LED_RED
  *            @arg  LED_GREEN
  *            @arg  LED_BLUE
  */
void BSP_LED_Off(Led_TypeDef Led)
{
  if (Led <= LEDn)
  {
    HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_RESET);
  }
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: LED to be toggled
  *          This parameter can be one of the following values:
  *            @arg  BACK_LIGHT
  *            @arg  LED_RED
  *            @arg  LED_GREEN
  *            @arg  LED_BLUE
  */
void BSP_LED_Toggle(Led_TypeDef Led)
{
  if (Led <= LEDn)
  {
     HAL_GPIO_TogglePin(GPIO_PORT[Led], GPIO_PIN[Led]);
  }
}



/**
  * @}
  */


/** @defgroup DragonEYE_LEDS_Private_Functions DragonEYE LEDs Private Functions
  * @{
  */



/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
