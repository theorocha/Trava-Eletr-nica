#include <msp430.h> 
#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 100

char received_string[MAX_STRING_LENGTH];
unsigned int string_index = 0;

void config_inicial(void)
{
    P3SEL |= BIT4 | BIT3;
    UCA0CTL1 |= UCSSEL_2;
    UCA0BR0 = 6;
    UCA0BR1 = 0;
    UCA0MCTL = UCBRS_0 + UCBRF_13 + UCOS16;
    UCA0CTL1 &= ~UCSWRST;
    UCA0IE = UCRXIE;
}

void send_char(unsigned char c)
{
    while (!(UCA0IFG & UCTXIFG));
    UCA0TXBUF = c;
}

void send_string(char *str)
{
    int i;
    for (i = 0; str[i] != '\0'; i++)
        send_char(str[i]);
}

void moveMotor(){
    P2DIR |= BIT5;
    P2SEL |= BIT5;

    TA2CTL = TASSEL__SMCLK | MC__UP | TACLR;
    TA2CCR0 = 52429;
    TA2CCTL2 = OUTMOD_7;


    TA2CCR2 = 522;

    TA2CCR2 = 2580;
    __delay_cycles(7000000);
    TA2CCR2 = 522;

}


void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    config_inicial();
    __enable_interrupt();
}

#pragma vector= USCI_A0_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    unsigned char c = UCA0RXBUF;
    if (c == '\r')
    {
        received_string[string_index] = '\0';
        send_string("Recebido: ");
        send_string(received_string);
        send_string("\r\n");
        if (strcmp(received_string, "theo1234") == 0)
        {
            send_string("Senhacorreta!\r\n");
            moveMotor();
        }
        else
        {
            send_string("Senha incorreta!\r\n");
        }

        string_index = 0;
    }
    else
    {
        received_string[string_index++] = c;
    }
}
