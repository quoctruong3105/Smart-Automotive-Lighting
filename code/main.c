#include <mega328p.h>
#include <delay.h>

#define ADC_VREF_TYPE ((0<<REFS1) | (1<<REFS0) | (0<<ADLAR))
#define sbi(port,bit) (port) |= (1<<(bit))
#define cbi(port,bit) (port) &=~ (1<<(bit))
#define range(i) i


// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | ADC_VREF_TYPE;
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=(1<<ADSC);
// Wait for the AD conversion to complete
while ((ADCSRA & (1<<ADIF))==0);
ADCSRA|=(1<<ADIF);
return ADCW;
}


void lightControl()
{
     unsigned int i, j;

     // High beam
     for(j = 0; j < 4; j++)
     {
          for(i = 0; i < 5; i++)
          {
               if(read_adc(i) < 512)
               {
                    sbi(PORTD,range(i));
               }
               else if(read_adc(i) >= 512)
               {
                    cbi(PORTD,range(i));
               }
          }
          if(PORTD4 == 0 && PORTD3 == 0 && PORTD2 == 0 && PORTD1 == 0 && PORTD0 == 0)
          {
               break;
          }
          cbi(PORTB,j);
          delay_ms(1);
          sbi(PORTB,j);
     }


     // Low beam
     for(j = 4; j < 7; j++)
     {
          for(i = 0; i < 5; i++)
          {
               if(read_adc(i) >= 512)
               {
                    sbi(PORTD,range(i));
               }
               else if(read_adc(i) < 512)
               {
                    cbi(PORTD,range(i));
               }
          }
          if(PORTD4 == 0 && PORTD3 == 0 && PORTD2 == 0 && PORTD1 == 0 && PORTD0 == 0)
          {
               break;
          }
          cbi(PORTB,j);
          delay_ms(1);
          sbi(PORTB,j);
     }
}

void main(void)
{
float steerAngle;

// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=(1<<CLKPCE);
CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

// Set up for Matrix LED
DDRD =(1<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
DDRB =(1<<DDB6) | (1<<DDB5) | (1<<DDB4) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);

// Timer/Counter 0 initialization
TCCR0A=0b00100011;
TCCR0B=0b00000101;
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

// ADC initialization
DIDR0=(1<<ADC5D) | (1<<ADC4D) | (1<<ADC3D) | (1<<ADC2D) | (1<<ADC1D) | (1<<ADC0D);
ADMUX=ADC_VREF_TYPE;
ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
ADCSRB=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);

// Set up for Motors
DDRD.5 = 1;

while (1)
      {
          //ABD
          lightControl();

          //AFS
          steerAngle = 0.0879f*read_adc(5)+45;
          OCR0B = 0.0778f*steerAngle+8.5;
      }
}
