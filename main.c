#include "Peripheral_Setup.h"

//DECLARAÇÃO DAS VARIÁVEIS AUXILIARES


int main(void){

    //SETANDO OS REGISTRADORES
    InitSysCtrl();      //INICIALIZA O SISTEMA DO MICROCONTROLADOR (CLOCKS, MEMÓRIA...)

    DINT; //DESABILITA INTERRUPÇÕES
    InitPieCtrl(); //RESETA TODOS OS REGISTRADORES DA TABELA DE INTERRUPÇÕES (COLUNAS)
    //DESABLITANDO AS INTERRUPÇÕES
    IER = 0x0000; //RESETA O REGISTRADOR DE INTERRUPÇÕES (LINHAS)
    IFR = 0x0000; //RESETA O FLAG DAS INTERRUPÇÕES
    InitPieVectTable(); //PREENCHE OS REGISTRADORES DE INTERRUPÇÃO COM O ENDEREÇO DAS FUNÇÕES DOS PERIFÉRICOS

    //CONFIGURA ENTRADAS E SAÍDAS
    Setup_GPIO();
    //CONFIGURA PWM
    Setup_ePWM();
    

    EALLOW;
    
       CpuSysRegs.PCLKCR13.bit.ADC_A = 1;
       AdcaRegs.ADCCTL2.bit.PRESCALE = 6;          // set ADCCLK divider to /4
       AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
       AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;       // Set pulse um ciclo antes do resultado
       AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;          // power up the ADC
       DELAY_US(1000);                             // delay for 1ms to allow ADC time to power up

       AdcaRegs.ADCSOC0CTL.bit.CHSEL = 3;
       AdcaRegs.ADCSOC0CTL.bit.ACQPS = acqps;          //sample window is 15 SYSCLK cycles
       AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 0x05; //trigger on ePWM2 SOCA

       AdcaRegs.ADCSOC1CTL.bit.CHSEL = 4;
       AdcaRegs.ADCSOC1CTL.bit.ACQPS = acqps;
       AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 0x05;

       AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0x01;       // end of SOC1 will set INT1 flag
       AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;            // enable INT1 flag
       AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;          // make sure INT1 flag is cleared

       EDIS;
    



    EINT; //INTERRUPÇÃO GLOBAL
    ERTM; //INTERRUPÇÃO EM TEMPO REAL

    //DESLIGA OS DOIS LED'S


    while(1){//LOOP INFINITO

    }
    return 0;
}


