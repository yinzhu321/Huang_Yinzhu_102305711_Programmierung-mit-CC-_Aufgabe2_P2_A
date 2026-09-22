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
	// 16 MHz clock, 9600 Baudrate
	UBRR0H = 0;
	UBRR0L = 103;
	
	// USART0 receive and transmission
	 UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	 
	 //8 Datenbits
	 UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}


//Ein einzelnes Zeichen über UART0 an den PC senden
void uart0_send_char(char s_data)
{
	//Warten, bis das Senderegister frei ist
	while (!(UCSR0A & (1 << UDRE0)))
	{
		
	}
	// Zeichen in das Datenregister schreiben und senden
	UDR0 = s_data;
}


//Einen vollständigen String über UART0 an den PC senden
void uart0_send_string(const char *text)
{
	while (*text != '\0')
	{
		// Zeichen nacheinander senden, bis das Stringende erreicht ist
		uart0_send_char(*text);
		text++;
	}
}
 
 // Ein einzelnes Zeichen über UART0 vom PC empfangen
 char uart0_rec_Byte(void)
 {
	  // Warten, bis ein Zeichen empfangen wurde
	 while(!(UCSR0A & (1 << RXC0)))
	 {
		
	 }
	 // Empfangenes Zeichen zurückgeben
	 return UDR0;
 }
 
 // Einen vollständigen String vom PC empfangen
 void uart0_rec_string(char *ab)
 {
    int n = 0;
    char c;

    do
    {
		// Zeichen einzeln empfangen
	    c = uart0_rec_Byte();

		// Zeichen speichern, solange das Ende nicht erreicht ist
	    if (c != '\n'&& n < 49)
	    {
		    ab[n] = c;
		    n++;
	    }

    } while (c != '\n');
	
	// String mit Nullzeichen abschließen
    ab[n] = '\0';
    
 }

int main(void)
{
	uart0_init();

	// Puffer für empfangene Daten
    char Dat[50];
	
	while (1)
	{
		uart0_rec_string(Dat);
		
		// Position des Multiplikationszeichens suchen
		char *op = strchr(Dat, '*');
		
		if (op != NULL)
		{
		// Empfangene Zahlen aus dem String auslesen
		int a = atoi(Dat);
		int b = atoi(op + 1);

		// Multiplikation durchführen
		int ergebnis = a * b;

		// Ergebnis in string umwandeln
		char s_ergebnis[20] = {0};
		itoa(ergebnis, s_ergebnis, 10);

		// Ergebnis an den PC senden
		_delay_ms(500);
		uart0_send_string(s_ergebnis);
		}
	}
	
}

