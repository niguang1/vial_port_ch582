/********************************** (C) COPYRIGHT *******************************
 * File Name          : hidkbd.h
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/12/10
 * Description        :
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#ifndef HIDKBD_H
#define HIDKBD_H

#include "report.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
 * INCLUDES
 */

/*********************************************************************
 * CONSTANTS
 */

// Task Events
#define START_DEVICE_EVT          0x0001
#define START_REPORT_EVT          0x0002
#define START_PARAM_UPDATE_EVT    0x0004
#define START_PHY_UPDATE_EVT      0x0008
#define BLE_RUN_QMK_TASK_EVT      0x0010
/*********************************************************************
 * MACROS
 */
typedef struct{
    bool isbond;
    UINT8 addr_type;
    UINT8 MacAddr[6];
}Device_ID_;

typedef struct
{
    Device_ID_ ID[16];
    uint8_t bondIdx;        //当前选择的设备的索引
}Device_Info_;

extern Device_Info_ g_device_info;

#define DEVICE_INFO_EEPROM_OFFSET 0

/*********************************************************************
 * FUNCTIONS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */

/*
 * Task Initialization for the BLE Application
 */
extern void HidEmu_Init(void);

/*
 * Task Event Processor for the BLE Application
 */
extern uint16_t HidEmu_ProcessEvent(uint8_t task_id, uint16_t events);

void connectAnotherDevice(uint8_t slot_index);

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
