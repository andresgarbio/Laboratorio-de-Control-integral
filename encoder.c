//se llama al compilador Hi-Tech C
#include<htc.h>

//se da la frecuencia de 4 KHz del cristal
#define _XTAL_FREQ 4000000

//seteo de los bits de configuración
__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_OFF & BOREN_OFF & LVP_OFF & CPD_OFF & WRT_OFF & CP_OFF);

//se define el valor de preescalador para el timer que será usado en las salidas PWM
#define TMR2PRESCALE 4

//Declaración de las variables a utilizar
long freq;
int n; //variable usada para medir canal A del encoder
int n_last;
int m; //variable usada para medir canal B del encoder
/*Valores para la posición angular y la velocidad que se le dará al motor*/
signed long long encoder;
signed long velocidad;


/*Variable susadas en el PID*/
signed long pos_deseada;
signed long error;
unsigned int Kp = 60;
unsigned int Ki = 0.1;
signed long suma_error;


/*función para sacar el valor absoluto d euna variable*/
int abval(int val)
 {
     return (val<0 ? (-val) : val);
 }

/*función que da el ciclo de trabajo máximo apra una señal PWM*/

int PWM_Max_Duty()
{
  return(_XTAL_FREQ/(freq * TMR2PRESCALE) ;
}

/*Inicialización de frecuencia para la salida PWM 1*/
PWM1_Init(long fre)
{
  PR2 = (_XTAL_FREQ/(fre*4*TMR2PRESCALE)) - 1;
  freq = fre;
}

/*Inicialización de frecuencia para la salida PWM 2*/
PWM2_Init(long fre)
{
  PR2 = (_XTAL_FREQ/(fre*4*TMR2PRESCALE)) - 1;
  freq = fre;
}


/*Generación del ciclo de trabajo para una señal PWM*/
PWM1_Duty(unsigned int duty)
{
  if(duty<1024)
  {
    duty = ((float)duty/1023)*PWM_Max_Duty();
    CCP1X = duty & 2;
    CCP1Y = duty & 1;
    CCPR1L = duty>>2;
  }
}

PWM2_Duty(unsigned int duty)
{
  if(duty<1024)
  {
    duty = ((float)duty/1023)*PWM_Max_Duty();
    CCP2X = duty & 2;
    CCP2Y = duty & 1;
    CCPR2L = duty>>2;
  }
}

PWM1_Start()
{
  CCP1M3 = 1;
  CCP1M2 = 1;
  #if TMR2PRESCALAR == 1
    T2CKPS0 = 0;
    T2CKPS1 = 0;
  #elif TMR2PRESCALAR == 4
    T2CKPS0 = 1;
    T2CKPS1 = 0;
  #elif TMR2PRESCALAR == 16
    T2CKPS0 = 1;
    T2CKPS1 = 1;
  #endif
  TMR2ON = 1;
  TRISC2 = 0;
}

PWM1_Stop()
{
  CCP1M3 = 0;
  CCP1M2 = 0;
}

PWM2_Start()
{
  CCP2M3 = 1;
  CCP2M2 = 1;
  #if TMR2PRESCALE == 1
    T2CKPS0 = 0;
    T2CKPS1 = 0;
  #elif TMR2PRESCALE == 4
    T2CKPS0 = 1;
    T2CKPS1 = 0;
  #elif TMR2PRESCALE == 16
    T2CKPS0 = 1;
    T2CKPS1 = 1;
  #endif
    TMR2ON = 1;
    TRISC1 = 0;
}

PWM2_Stop()
{
  CCP2M3 = 0;
  CCP2M2 = 0;
}

void main()
{
  PWM1_Init(1000);
  PWM2_Init(1000);
  TRISD = 0xFF;
  TRISB = 0b00000000;
  PWM1_Duty(0);
  PWM2_Duty(0);
  PWM1_Start();
  PWM2_Start();
  encoder  = 0;
  velocidad = 0;
  pos_deseada = 0;
  suma_error = 0;
          
  do
  {
    error = pos_deseada - encoder ;
    velocidad = error * Kp  ;
            
    if(velocidad < -600){
    velocidad = -600;
    }

   if(velocidad > 600){
    velocidad = 600;
    }

    if(velocidad < 0){
        PORTB = 0b10000000;  
    }
    else{
        PORTB = 0b01000000;
    }



    PWM1_Duty(abval(velocidad));

     n = PORTD & (1 << 0);
     m = PORTD & (1 << 1);

     if ((n_last == 0) && (n == 1)){
         if(m == 0){
         encoder--;
        }else{
         encoder++;
        }

     }
    n_last = n;
    suma_error = error + suma_error;

  }while(1);
}

