/*
 * GccApplication1.c
 *
 * Created: 27.08.2026 09:03:55
 * Author : yinzhu.Huang
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void uart0_init(void)
{
	// 16 MHz clock, 9600 Baud
	UBRR0H = 0;
	UBRR0L = 103;
	
	// USART0 receive and transmission
	 UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	 
	 //8?????????1?????8N1
	 UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}



void uart0_send_char(char s_data)
{
	//?????????
	while (!(UCSR0A & (1 << UDRE0)))
	{
		
	}
	
	UDR0 = s_data;
}



void uart0_send_string(const char *text)
{
	while (*text != '\0')
	{
		uart0_send_char(*text);
		text++;
	}
}
 
 char uart0_rec_Byte(void)
 {
	 while(!(UCSR0A & (1 << RXC0)))
	 {
		 //warten
	 }
	 return UDR0;
 }
 
 
 void uart0_rec_string(char *ab)
 {
    int n = 0;
    char c;

    do
    {
	    c = uart0_rec_Byte();

	    if (c != '\n'&& n < 49)
	    {
		    ab[n] = c;
		    n++;
	    }

    } while (c != '\n');

    ab[n] = '\0';
    
 }

int main(void)
{
	uart0_init();

    char Dat[50];
	
	while (1)
	{
		uart0_rec_string(Dat);
		char *op = strchr(Dat, '*');
		
		if (op != NULL)
		{
		// String zu int
		int a = atoi(Dat);
		int b = atoi(op + 1);

		// Berechnen
		int ergebnis = a * b;

		// int zu String
		char s_ergebnis[20] = {0};
		itoa(ergebnis, s_ergebnis, 10);

		// Ergebnis an PC senden
		_delay_ms(500);
		uart0_send_string(s_ergebnis);
		}
	}
	
}

