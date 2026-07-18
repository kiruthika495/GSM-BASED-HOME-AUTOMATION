#include<lpc21xx.h>
#include<string.h>
#include"lcdheader.h"
#include"delay_header.h"
#include"uartheader.h"                                              
#define led1 (1<<23)	   
#define led2 (1<<24)	  
#define mr1 (1<<25)
#define mr2 (1<<26)	   

char rx_buffer[100];

void GSM_INIT(void)
{
UART0_STR("AT\r\n");
delay_millisecond(100);

UART0_STR("AT+CMGF=1\r\n");
delay_millisecond(100);

UART0_STR("AT+CNMI=2,2,0,0,0\r\n");
delay_millisecond(100);

}


void GSM_SEND_SMS(void )
{
UART0_STR("AT+CMGS=\"+918825469141\"\r\n");       //Receivers phone no
delay_millisecond(300);

UART0_STR("GSM TEST");
 delay_millisecond(300);
UART0_Tx(0X1A);

}


int main()
{
unsigned int k;
IODIR0 |=LCD_D|RS|E;
IODIR1 |= led1|led2|mr1|mr2;

LCD_INIT();
UART0_CONFIG();
GSM_INIT();	
GSM_SEND_SMS();

LCD_STR("HOME AUTOMATION");

while(1)
{ 
	     do
		 {
         	k=UART0_Rx();
		 }while(k!='*');
		 k=0;
		 do{
			 rx_buffer[k++]=UART0_Rx();
		 }while(rx_buffer[k-1]!='#');
		 rx_buffer[k-1]='\0';
		 
UART0_STR((unsigned char*)(rx_buffer));
LCD_STR((unsigned char *)(rx_buffer));

LCD_COMMAND(0xc0);
if(strstr(rx_buffer,"FAN ON")!=NULL)
{
IOCLR1=mr1;
IOSET1=mr2;
LCD_COMMAND(0X01);
LCD_STR("FAN ON");
}

else if(strstr(rx_buffer,"FAN OFF")!=NULL)
{
IOCLR1=mr1;
IOCLR1=mr2;
LCD_COMMAND(0X01);
LCD_STR("FAN OFF");
}

else if(strstr(rx_buffer,"LIGHT1 ON")!=NULL)
{
IOCLR1=led1;

LCD_COMMAND(0X01);
LCD_STR("LIGHT1 ON");
}

else if(strstr(rx_buffer,"LIGHT2 ON")!=NULL)
{ 

IOCLR1=led2;

LCD_COMMAND(0X01);
LCD_STR("LIGHT2 ON");
}

else if(strstr(rx_buffer,"LIGHT1 OFF")!=NULL)
{
IOSET1=led1;
LCD_COMMAND(0X01);
LCD_STR("LIGHT1 OFF");
}

else if(strstr(rx_buffer,"LIGHT2 OFF")!=NULL)
{
IOSET1=led2;
LCD_COMMAND(0X01);
LCD_STR("LIGHT2 OFF");
}

else if(strstr(rx_buffer,"ALL ON")!=NULL)
{
IOSET1=mr1;
IOCLR1=mr2;
IOCLR1 |=led1|led2;
LCD_COMMAND(0X01);
LCD_STR("ALL ON");
}

else if(strstr(rx_buffer,"ALL OFF")!=NULL)
{
IOCLR1=mr1;
IOCLR1=mr2;
IOSET1 |=led1|led2;
LCD_COMMAND(0X01);
LCD_STR("ALL OFF");
}

else
{
LCD_STR("Invalid cmd....");
}
}
}

