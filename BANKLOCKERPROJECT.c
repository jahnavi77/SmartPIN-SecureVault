#include<reg51.h>
#include<string.h>
void delay(unsigned int i);
void lcd_cmd(unsigned char a);
void lcd_data(unsigned char b);
void lcd_init(void);
void lcd_str(unsigned char *str);
void sendser_char(unsigned char b);
void sendser_str(unsigned char *str);
void sms_send(unsigned char s);
void delay_ms(unsigned int i);
void clear(void);
void gsm_link(void);
void keypad(void);
sbit rs=P3^0;
sbit en=P3^1;
sfr ldata=0x90;//port1 
sbit r1=P2^0;
sbit r2=P2^1;
sbit r3=P2^2;
sbit r4=P2^3;
sbit c1=P2^4;
sbit c2=P2^5;
sbit c3=P2^6;
sbit m1=P3^4;
sbit m2=P3^5;
sbit buzz=P3^6;
unsigned char a[100],mesg_rec,pas[5],p;
unsigned int i;
void ser_int() interrupt 4
{
if(RI==1)
{
RI=0;
a[i]=SBUF;
	i++;
mesg_rec=1;
}

if(TI==1)
{

TI=0;
}


}
void main()

{
	m1 = 0;
	m2 = 0;
	buzz = 0;
	TMOD=0x20;//timer1 mode2 -auto reload mode
	TH1=0xfd;//9600 baud rate
	SCON=0x50;//8bit data ,1start bit,1stop bit
	IE=0x90;//EA=1,ES=1...
	TR1=1;
lcd_init();
	lcd_str("   WELCOME TO   ");
	lcd_cmd(0xc0);
	lcd_str("   MY PROJECT   ");
	
	delay(65000);
		lcd_cmd(0x01);
		lcd_cmd(0x80);
lcd_str("   YT TRAINING   ");
	lcd_cmd(0xc0);
	lcd_str("   INSTITUTE   ");
		delay(65000);
gsm_link();
	//sms_send();
	while(1)

   {
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		 lcd_str("Enter Password: "); 
		 lcd_cmd(0xc0);
	  for(p=0;p<5;p++)
		 {
			 pas[p] = '\0';
			
			}
		 p =0;
			while(p<4)
			{
				keypad();
			}
		pas[5] = '\0';

			if(0 == strcmp(pas,"1234"))
			{
				lcd_cmd(0x01);
		lcd_cmd(0x80);
		 lcd_str("Correct Password");
				m1 = 1;
				m2 = 0;
				delay(65000);
				lcd_cmd(0xc0);
				lcd_str("Door Opened");
				delay(65000);
				m1 = 0;
				m2 = 0;
				delay(65000);
				sms_send(0);//DOOR Opened Succesfully
				delay(65000);
				m1 = 0;
				m2 = 1;
				lcd_cmd(0xc0);
				lcd_str("Door Closed");
				delay(65000);
				m1 = 0;
				m2 = 0;
			}
			else
			{
				lcd_cmd(0x01);
		lcd_cmd(0x80);
		 lcd_str("InCorrect Password");
				delay(65000);
				buzz = 1;
				delay(65000);
				buzz = 0;
				sms_send(1);
			}
			
		}	
}
void keypad(void)
{
	delay(65000);
	c1=c2=c3=1;
		r1=r2=r3=r4=0;
		if(c1==0)
		{
			c1=c2=c3=0;
			r1=r2=r3=r4=1;
			if(r1==0)
			{
			lcd_data('1');pas[p] = '1';p++;
			}
			if(r2==0)
			{
			lcd_data('4');pas[p] = '4';p++;
			}
			if(r3==0)
			{
			lcd_data('7');pas[p] = '7';p++;
			}
			if(r4==0)
			{
			lcd_data('*');pas[p] = '*';p++;
			}
		}
		else if(c2 ==0)
		{
			c1=c2=c3=0;
			r1=r2=r3=r4=1;
			if(r1==0)
			{
			lcd_data('2');pas[p] = '2';p++;
			}
			if(r2==0)
			{
			lcd_data('5');pas[p] = '5';p++;
			}
			if(r3==0)
			{
			lcd_data('8');pas[p] = '8';p++;
			}
			if(r4==0)
			{
			lcd_data('0');pas[p] = '0';p++;
			}
		}
		else if(c3 ==0)
		{
			c1=c2=c3=0;
			r1=r2=r3=r4=1;
			if(r1==0);
			{
			lcd_data('3');pas[p] = '3';p++;
			}
			if(r2==0)
			{
			lcd_data('6');pas[p] = '6';p++;
			}
			if(r3==0)
			{
			lcd_data('9');pas[p] = '9';p++;
			}
			if(r4==0)
			{
			lcd_data('#');pas[p] = '#';p++;
			}
		}
}
	
	
		




void sms_send(unsigned char s)
{
	lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_str(" SMS SENDING");
	delay_ms(650);
sendser_str("AT+CMGS=");
sendser_char(0x22);//"
	sendser_str("+919999999999");
	sendser_char(0x22);// serial char for ''
	sendser_char(0x0d);//serial char for enter
	if(s == 0)
	{
	sendser_str("DOOR OPENED SUCCESSFULLY");
	}
	else
	{
		sendser_str("DOOR NOT OPENED SUCCESSFULLY");
	}
		sendser_char(0x1a);//sms sent
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_str(" SMS SENT");
	delay_ms(650);
	}
void gsm_link(void)
{
	loop:
	i=0;
	sendser_str("AT");
sendser_char(0x0d);
			lcd_cmd(0x01);
		lcd_cmd(0x80);
	if(a[2]=='O'&&a[3]=='K')
	{
	lcd_str(" GSM LINK IS UP");
	
	}
	else
	{
		lcd_str(" GSM CHECKING");
	goto loop;
	}
	 clear();
delay_ms(650);
	
	loop1:
	i=0;
	sendser_str("AT+CMGF=1");
sendser_char(0x0d);
			lcd_cmd(0x01);
		lcd_cmd(0x80);
	if(a[2]=='O'&&a[3]=='K')
	{
	lcd_str(" GSM TEXT MODE");
	
	}
	else
	{
		lcd_str(" GSM NOT IN TEXT");
	goto loop1;
	}
		 clear();
delay_ms(650);

}

void lcd_init()
{
lcd_cmd(0x38);
	lcd_cmd(0x0c);
	lcd_cmd(0x01);
	lcd_cmd(0x80);


}
void delay(unsigned int i)
{
unsigned int j;
	for(j=0;j<i;j++);
}
void delay_ms(unsigned int i)
{
unsigned int j,k;
	for(j=0;j<i;j++)
	for(k=0;k<1275;k++);
}

void lcd_cmd(unsigned char a)
{
  rs=0;//cmd 
	ldata=a;
	en=1;
	delay(5);
	en=0;
	delay(5);
}
void lcd_data(unsigned char b)
{
  rs=1;//data 
	ldata=b;
	en=1;
	delay(5);
	en=0;
	delay(5);
}
void lcd_str(unsigned char *str)
{
while(*str)
{
	lcd_data(*str++);
}

}


void sendser_char(unsigned char b)
{
SBUF=b;
	while(TI==0);
	TI=0;
}


void sendser_str(unsigned char *str)
{
while(*str)
{
	sendser_char(*str++);
}

}
void clear(void)
{
unsigned int i;
	for(i=0;i<100;i++)
	{
	a[i]=0;
	
	}
}