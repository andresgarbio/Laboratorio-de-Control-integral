/*
 * File:   oarri.c
 * Author: Andres
 *
 * Created on January 30, 2017, 4:19 PM
 */

#include <htc.h>
#include <pic.h>


#define _XTAL_FREQ 4000000
__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_OFF & BOREN_OFF & LVP_OFF & CPD_OFF & WRT_OFF & CP_OFF);



int main() {
    /*inicializar entradas y salidas*/
    InitPWM();

    SetPWMDutyCycle(1,127);
    SetPWMDutyCycle(2,127);


    while(1) {
        
    }


}

void InitPWM(void)
{
    TRISC1 = 0;
    TRISC2 = 0;
    CCP1CON = 0x0C;
    CCP2CON = 0x0C;

    PR2 = 0xFF;
    T2CON = 0x01;

    SetPWMDutyCycle(1,127);
    SetPWMDutyCycle(2,127);

}

}
