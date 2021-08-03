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

    IDX_CHAR_B,     //Characteristic B index
    IDX_CHAR_VAL_B, //Characteristic B value index

    IDX_CHAR_C,     //Characteristic B index
    IDX_CHAR_VAL_C, //Characteristic B value index

    HRS_IDX_NB, //Table elements
};

void ble_init(void);
#endif