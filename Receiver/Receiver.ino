/*Include the VirtualWire library */
#include "VirtualWire.h"

/* Digital IO pin that will be used for receiving data from the receiver */
const int RX_DIO_Pin = 12;
 /*Initialize Button Status*/
int buttonState=0;
 
void setup()
{
    pinMode(13, OUTPUT);
    Serial.begin(9600);

    /* Initialises the DIO pin used to receive data from the Rx module */
    vw_set_rx_pin(RX_DIO_Pin);
   
    /* Receive at 2000 bits per second */
    vw_setup(2000);
   
    /* Enable the receiver */
    vw_rx_start();
}

/* Main program */
void loop()
{
  /* Set the receive buffer size to 2 bytes */
  uint8_t Buffer_Size = 5;
 
  /* Holds the recived data */
  unsigned int Data ,Data2;
 
  /* The receive buffer */
  uint8_t RxBuffer[Buffer_Size];

    /* Has a message been received? */
    if (vw_get_message(RxBuffer, &Buffer_Size)) // Non-blocking
    {
        /* If so, then turn on the LED connected to DIO 13
           to indicate this */
        digitalWrite(13, HIGH);
   
        /* Store the received high and low byte data */
        Data = RxBuffer[0] << 8 | RxBuffer[1];
        Data2 = RxBuffer[2] << 8 | RxBuffer[3];
        buttonState = RxBuffer[4];
        /* Output this data to the UART */
        Serial.print("Analogue pin A0: ");
        Serial.print(Data);
        Serial.print("  Analogue pin A1: ");
        Serial.print(Data2);
        Serial.print("  Digital pin State: ");
        Serial.println(buttonState);
        /* Turn off the LED on pin 13 to indicate that the
           data has now been received */
        digitalWrite(13, LOW);
    }
}
