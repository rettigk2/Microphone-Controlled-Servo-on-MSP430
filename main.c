#include <msp430.h>

void configurePWM();
void ConfigureAdc_mic();
void configureClocks();

#define BUTTON BIT3;

volatile long rawMic;
int i;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P2DIR = 0b01101010; //set the outputs for LED r + g + b
    P2OUT = BIT3; //Blue LED on

    configureClocks();
    ConfigureAdc_mic();
    configurePWM();

    P1IE = BIT3; //Enable button to start interrupt
    P1IES = BIT3; //Edge select from high to low for button
    P1IFG = 0x00; //Clear interrupt flag

    _bis_SR_register(GIE);
    _enable_interrupts(); //Enable all interrupts

    while (1)
    {
        ADC10CTL0 |= ADC10SC; //Sample Conversion enabled
        while (ADC10CTL1 & ADC10BUSY); //Wait for ADC10 to not be busy
        rawMic = ADC10MEM; //store ADC10 in rawMic

        TACCR0 = 20000;  //PWM period
        if (rawMic < 450)
        {
            P2OUT = BIT5; //blue led on
            for (i = 350; i <= 2350; i++) //0 to 180 degrees on servo
            {
                TACCR1 = i;
                TACCTL1 = OUTMOD_7;  //CCR1 selection reset-set
                TACTL = TASSEL_2 | MC_1;   //SMCLK submain clock,upmode
                __delay_cycles(3000);
            }
            __delay_cycles(1000000);
        }
        if (rawMic >= 450 && rawMic <= 900)
        {
            P2OUT = BIT3; //green led on
            for (i = 350; i <= 2350; i = i + 4)
            {
                TACCR1 = i;
                TACCTL1 = OUTMOD_7;  //CCR1 selection reset-set
                TACTL = TASSEL_2 | MC_1;   //SMCLK submain clock,upmode
                __delay_cycles(2000);
            }
            __delay_cycles(500000);
        }
        if (rawMic > 900)
        {
            P2OUT = BIT1; //red led on
            for (i = 350; i <= 2350; i = i + 4)
            {
                TACCR1 = i;
                TACCTL1 = OUTMOD_7;  //CCR1 selection reset-set
                TACTL = TASSEL_2 | MC_1;   //SMCLK submain clock,upmode
                __delay_cycles(1000);
            }
            __delay_cycles(200000);
        }
    }
}
#pragma vector=PORT1_VECTOR 
__interrupt void PORT1_ISR(void)
{
    P2OUT = 0b00101010; //Turn on all LEDs
    while ((P1IN & 0x08) != 0x08) //While button is held
    {
        for (i = 350; i <= 2350; i++)
        {
            TACCR1 = i;
            TACCTL1 = OUTMOD_7;  //CCR1 selection reset-set
            TACTL = TASSEL_2 | MC_1;   //SMCLK submain clock,upmode
            __delay_cycles(1000);
        }
        __delay_cycles(250000);
    }
    P1IFG = 0x00; //Clear interrupt flags
}

void configureClocks()
{
    BCSCTL1 = CALBC1_1MHZ;                                         // ACLK range
    DCOCTL = CALDCO_1MHZ;                           // Set DCO step + modulation

    //BCSCTL2 |= SELS; //This would set smclk to use VLO 12KHz, but it breaks my servo right now

    BCSCTL3 |= LFXT1S_2; //this breaks the servo if i change it, not sure why, external clock == VLO
    IFG1 &= ~OFIFG;                            // Clear OSCFault flag
}

void ConfigureAdc_mic()
{
    ADC10CTL0 = SREF_0 | ADC10SHT_1 | REFON | ADC10ON; //Vref+ VCC | Sample Hold Time 8 x ADC10CLKs | Ref turn on | ADC10 on
    ADC10CTL1 = INCH_4 | ADC10DIV_7 | CONSEQ_0 | ADC10SSEL_1 | SHS_0; //1.4 output | ADC10 Clk Divider | Single Ch. Single Conversion | ACLK source| Sample Hold bit ADC10SC
    ADC10AE0 = BIT4; //1.4 output port
    __delay_cycles(5);                      //wait for adc Ref to settle
    ADC10CTL0 |= ENC /*| MSC*/; //Enable Conversion
}

void configurePWM()     //Set 2.6 as output PWM port
{
    P2DIR |= BIT6;
    P2SEL |= BIT6;
    P2SEL &= ~BIT7;
    P2SEL2 &= ~(BIT6 | BIT7);
}
