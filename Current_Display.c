// 7 segment display x3
// connections
// RC0 - c
// RC1 - d
// RC2 - e
// RC3 - f
// RC4 - a
// RC5 - b
// RC6 - g
// RC7 - decimal point of display 2
// RB4 - Display 2
// RB5 - Display 1
// RB7 - Display 3

#include "Current_Display.h"

const uint8_t	zero    = 0b00010000;
const uint8_t	one     = 0b01111011;
const uint8_t	two     = 0b00001100;
const uint8_t	three   = 0b00001001;
const uint8_t	four    = 0b01000011;
const uint8_t	five    = 0b10000001;
const uint8_t	six     = 0b10000000;
const uint8_t	seven	= 0b00111011;
const uint8_t	eight	= 0b00000000;
const uint8_t	nine	= 0b00000001;
const int       num[10] = {zero,one,two,three,four,five,six,seven,eight,nine};

// voltage going into the microcontroller
// sets the reference voltage for the ADC
// this needs to be accurate
// It might be better to use a proper voltage reference
// But that would multiply error in the resistance measurement
const float     vref = 5.07;    

// Value of the current sense resistor
// This value sets the amount of current flowing through it
// based on the measured voltage across it
// Very senseitive to measurement error 
const float     res = 0.250;    // this needs to be even more accurate

//function prototypes
void disp(int a, int b, int c);
void adc_setup(void);
int adc(void);
void break_display(int read_val);

//start program
void main(void){
	TRISC = 0;
    
	TRISBbits.TRISB4 = 0;
	TRISBbits.TRISB5 = 0;
	TRISBbits.TRISB6 = 0;
	PORTBbits.RB4 = 0;
	PORTBbits.RB5 = 0;
	PORTBbits.RB6 = 0;

	ANSELHbits.ANS10 = 0;
	ANSELHbits.ANS11 = 0;
	adc_setup();
	int read_val;
	int convert;
	while(1){
		read_val = adc();
		convert = (int) ((read_val * 100 * vref) / (res * 1024));
		for (int i=0;i<=2;i++){
			break_display(convert);
		}
	}
}


void disp(int a, int b, int c){
		PORTBbits.RB4 = 1;
		PORTC = num[a];
		__delay_ms(1);
		PORTBbits.RB4 = 0;
		
		PORTBbits.RB5 = 1;
		PORTC = num[b];
		__delay_ms(1);
		PORTBbits.RB5 = 0;
		
		PORTBbits.RB6 = 1;
		PORTC = num[c];
		__delay_ms(1);
		PORTBbits.RB6 = 0;
}
void adc_setup(void){
	ANSELbits.ANS0 = 1;	//disable input buffer for proper ADC function
	TRISAbits.TRISA0 = 1;
	
	ADCON0bits.CHS3 = 0;
	ADCON0bits.CHS2 = 0;
	ADCON0bits.CHS1 = 0;
	ADCON0bits.CHS0 = 0;	//channel select
	
	ADCON0bits.VCFG = 0;	//voltage reference select
				
	ADCON1bits.ADCS2 = 1;	//Prescaler
	ADCON1bits.ADCS1 = 0;
	ADCON1bits.ADCS0 = 1;	//F_osc / 16
	
	ADCON0bits.ADFM = 1;	//RIGHT justify (2 msb on adresh(1-0))
	ADCON0bits.ADON = 1;	//enable adc
	__delay_us(200);
}

int adc(void){
	ADCON0bits.GO_DONE = 1;	//start a conversion
	__delay_us(200);	//acquisition time
	uint16_t value;
	while(1){
		if (ADCON0bits.GO_DONE == 0){
			value = ((uint16_t)ADRESH << 8) | ADRESL;	//move original 2 bits right by 8
			return value;		//return with 16 bit number
		}
	}
}
void break_display(int read_val){
	int a;
	int b;
	int c;
	if (read_val > 999){
		read_val = 999;
	}
	if (read_val < 10){
		read_val = 0;
	}
	c = read_val % 10;
	read_val /= 10;
	b = read_val % 10;
	read_val /= 10;
	a = read_val % 10;
	disp(a,b,c);
}