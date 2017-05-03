/*Include the VirtualWire library */
#include "VirtualWire.h"

/* Digital IO pin that will be used for sending data to the transmitter */
const int TX_DIO_Pin = 2;
int pushButton = A2;

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(12,HIGH);
  /* Initialises the PushButton pin*/
  pinMode(pushButton, INPUT);
  /* Initialises the DIO pin used to send data to the Tx module */
  vw_set_tx_pin(TX_DIO_Pin);
  /* Set the transmit logic level (LOW = transmit for this
     version of module)*/
  vw_set_ptt_inverted(true);
 
  /* Transmit at 2000 bits per second */
  vw_setup(2000);    // Bits per sec
}

/* Main program */
void loop()
{
  /* Temporarily holds the value read from analogue input A0 */
  unsigned int Data;
  unsigned int Data2;
  /* The transmit buffer that will hold the data to be
     transmitted. */
  byte TxBuffer[5];

   /* read the input pin:*/
  int buttonState = digitalRead(pushButton);
  /* Read the analogue input A0... */
  Data = analogRead(A0);
  Data2 = analogRead(A1);
  /* ...and store it as high and low bytes in the transmit
     buffer */
  TxBuffer[0] = Data >> 8;
  TxBuffer[1] = Data;
  TxBuffer[2] = Data2 >> 8;
  TxBuffer[3] = Data2;
  TxBuffer[4] = buttonState;
  /* Turn on the LED on pin 13 to indicate that we are about
    to transmit data */
  digitalWrite(13, HIGH);
  /* Send the data (2 bytes) */
  vw_send((byte *)TxBuffer, 5);
  /* Wait until the data has been sent */
  vw_wait_tx();
 
  /* Turn off the LED on pin 13 to indicate that we have
     now sent the data */
  digitalWrite(13, LOW);
 
  /* Do nothing for a second. Lower this delay to send
     data quicker */
  delay(10);
}
