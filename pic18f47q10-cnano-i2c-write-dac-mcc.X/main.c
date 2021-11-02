/*
© [2021] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/i2c_host/i2c_host_types.h"
#include "mcc_generated_files/i2c_host/mssp1.h"


#define I2C_CLIENT_ADDR 0x48 /* 7-bit Address */
#define TC1321_REG_ADDR 0x00
#define DATA_HIGH       0xFF
#define DATALENGTH      3


const struct I2C_HOST_INTERFACE *I2C = &i2c1_host_Interface;

/* Callback function to handle errors */
void I2C_Callback()
{
    if(I2C1_ErrorGet() == I2C_ERROR_NONE)
    {
        /* Transfer is completed successfully */
    }
    else
    {
        /* Error occurred during transfer. */
    }
}


void main(void)
{
    /* Initialize the device */
    SYSTEM_Initialize();
    /* Set callback function */
    I2C->CallbackRegister(I2C_Callback);
    
    uint8_t data[DATALENGTH];
    data[0] = TC1321_REG_ADDR;
    data[1] = DATA_HIGH;
    data[2] = DATA_HIGH;
    
    while (1)
    {
        /* Write to DATA REGISTER in TC1321 */
        I2C->Write(I2C_CLIENT_ADDR, data, DATALENGTH);
        /* Delay 1 second */
        __delay_ms(1000);
        /* Overwrite DATA with its inverse */
        data[1] = ~data[1];
        data[2] = ~data[2];
    }
}