//**********************************************************************/
// Universidad del Valle de Guatemala
// BE3029 - Electronica Digital 2
// Luis Rodriguez
// 21/07/2025
// LABORATORIO 3
// MCU: ESP32 dev kit 1.1
//**********************************************************************/


#include <Arduino.h>
#include <stdint.h>
#include <driver/ledc.h>

// Definciones
#define servo 25

#define LED_R 13
#define LED_V 14
#define LED_A 26
#define BTN1 0
#define BTN2 17

#define BTN3 19
#define BTN4 21


#define pwmChannel 0
#define pwmChannel1 1
#define pwmChannel2 2
#define pwmChannel3 3


#define freqPWM 100
#define freqPWMS 50


#define resPWM 16

#define delayBounce 250


// Funciones

void initBoton(void);
void IRAM_ATTR BTN1_ISR (void);

void initBoton2(void);
void IRAM_ATTR BTN2_ISR (void);

void initBoton3(void);
void IRAM_ATTR BTN3_ISR (void);

void initBoton4(void);
void IRAM_ATTR BTN4_ISR (void);

void initPWM(void);


// Variables globales
volatile uint32_t contador;
volatile uint32_t contadorR;
volatile uint32_t contadorV;
volatile uint32_t contadorA;
volatile int32_t contadorS;


volatile bool btn1Pressed;
volatile uint32_t lastISRBtn1 = 0;

volatile bool btn2Pressed;
volatile uint32_t lastISRBtn2 = 0;

volatile bool btn3Pressed;
volatile uint32_t lastISRBtn3 = 0;

volatile bool btn4Pressed;
volatile uint32_t lastISRBtn4 = 0;



//ISRs - Rutinas de interrupcion
void IRAM_ATTR BTN1_ISR (void){
  uint32_t tiempoActual = millis();

  if(tiempoActual - lastISRBtn1 > delayBounce){
    btn1Pressed = true;
    contador++;
    if(contador==5){
      contador=0;
    }
    lastISRBtn1 = tiempoActual;
  }
  
}

void IRAM_ATTR BTN2_ISR (void){
  uint32_t tiempoActual2 = millis();

  if(tiempoActual2 - lastISRBtn2 > delayBounce){
    if (contador == 1){
      btn2Pressed = true;
      contadorR++;
      if(contadorR==4){
      contadorR=0;
    }
    }else if(contador == 2){
      btn2Pressed = true;
      contadorV++;
      if(contadorV==4){
      contadorV=0;
    }
    }else if(contador == 3){
      btn2Pressed = true;
      contadorA++;
      if(contadorA==4){
      contadorA=0;
    }
  }
  lastISRBtn2 = tiempoActual2;
  }
}

void IRAM_ATTR BTN3_ISR (void){
  uint32_t tiempoActual3 = millis();

  if(tiempoActual3 - lastISRBtn3 > delayBounce){
    btn3Pressed = true;
    contadorS++;
    if(contadorS>4){
      contadorS=4;
    }
    lastISRBtn3 = tiempoActual3;
  }
  
}

void IRAM_ATTR BTN4_ISR (void){
  uint32_t tiempoActual4 = millis();

  if(tiempoActual4 - lastISRBtn4 > delayBounce){
    btn4Pressed = true;
    contadorS--;
    if(contadorS<0){
      contadorS=0;
    }
    lastISRBtn4 = tiempoActual4;
  }
  
}

//Rutinas de interrupcion


void setup() {
  // put your setup code here, to run 
  
  Serial.begin(115200);
  initBoton();
  initBoton2();
  initBoton3();
  initBoton4();

  contador=0;

  // Salidas
  pinMode(LED_R, OUTPUT);
  pinMode(LED_V, OUTPUT);
  pinMode(LED_A, OUTPUT);
  
  
  // Entradas
  
  // Inicializar estado de LEDs
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_V, LOW);
  digitalWrite(LED_A, LOW);

  initPWM();
}

void loop() { 
  
  switch (contador){
    case 0:
    break;
    case 1: 
      switch (contadorR){
        case 0:
        ledcWrite(pwmChannel, 0);
        break;

        case 1:
        ledcWrite(pwmChannel, 16383);
        break;

        case 2:
        ledcWrite(pwmChannel, 32767);
        break;

        case 3:
        ledcWrite(pwmChannel, 49151);
        break;
      }
    break;

    case 2:
      switch (contadorV){
        case 0:
        ledcWrite(pwmChannel1, 0);
        break;

        case 1:
        ledcWrite(pwmChannel1, 16383);
        break;

        case 2:
        ledcWrite(pwmChannel1, 32767);
        break;

        case 3:
        ledcWrite(pwmChannel1, 49151);
        break;
      }
      break;
    
    case 3: 
      switch (contadorA){
        case 0:
        ledcWrite(pwmChannel2, 0);
        break;

        case 1:
        ledcWrite(pwmChannel2, 16383);
        break;

        case 2:
        ledcWrite(pwmChannel2, 32767);
        break;

        case 3:
        ledcWrite(pwmChannel2, 49151);
        break;
      }
    break;

    case 4:
      switch (contadorS){
        case 0:
        ledcWrite(pwmChannel, 0);
        ledcWrite(pwmChannel1, 0);
        ledcWrite(pwmChannel2, 0);
        break;

        case 1:
        ledcWrite(pwmChannel, 49151);
        ledcWrite(pwmChannel1, 0);
        ledcWrite(pwmChannel2, 0);
        break;

        case 2:
        ledcWrite(pwmChannel, 0);
        ledcWrite(pwmChannel1, 49151);
        ledcWrite(pwmChannel2, 0);
        break;

        case 3:
        ledcWrite(pwmChannel, 0);
        ledcWrite(pwmChannel1, 0);
        ledcWrite(pwmChannel2, 49151);
        break;

        case 4:
        ledcWrite(pwmChannel, 0);
        ledcWrite(pwmChannel1, 0);
        ledcWrite(pwmChannel2, 0);
        break;
      }
    break;
  }

  switch(contadorS){
    case 0:
    ledcWrite(pwmChannel3, 3277);
    break;

    case 1:
    ledcWrite(pwmChannel3, 4096);
    break;

    case 2:
    ledcWrite(pwmChannel3, 4915);
    break;

    case 3:
    ledcWrite(pwmChannel3, 5734);
    break;

    case 4:
    ledcWrite(pwmChannel3, 6553);
    break;
  }
}


void initBoton(void){
  pinMode(BTN1, INPUT_PULLUP);
  attachInterrupt(BTN1, &BTN1_ISR, FALLING);

}
  void initBoton2(void){
  pinMode(BTN2, INPUT_PULLUP);
  attachInterrupt(BTN2, &BTN2_ISR, FALLING);

}
  void initBoton3(void){
  pinMode(BTN3, INPUT_PULLUP);
  attachInterrupt(BTN3, &BTN3_ISR, FALLING);

}
  void initBoton4(void){
  pinMode(BTN4, INPUT_PULLUP);
  attachInterrupt(BTN4, &BTN4_ISR, FALLING);

}

void initPWM(void) {
    ledcSetup(pwmChannel, freqPWM, resPWM);
    ledcAttachPin(LED_R, pwmChannel);
    
    ledcSetup(pwmChannel1, freqPWM, resPWM);
    ledcAttachPin(LED_V, pwmChannel1);
    
    ledcSetup(pwmChannel2, freqPWM, resPWM);
    ledcAttachPin(LED_A, pwmChannel2);

    ledcSetup(pwmChannel3, freqPWMS, resPWM);
    ledcAttachPin(servo, pwmChannel3);
}
