#ifndef BLE_H_INCLUDED
#define BLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Attributes State Machine: Enumerates the services and characteristics */
enum
{
    IDX_SVC,        //Service index
    IDX_CHAR_A,     //Characteristic A index
    IDX_CHAR_VAL_A, //Characteristic A value index
    IDX_CHAR_CFG_A, //Characteristic A configuration index

    HRS_IDX_NB, //Table elements
};
uint16_t handle_table[HRS_IDX_NB];
void ble_init(void);
#endif