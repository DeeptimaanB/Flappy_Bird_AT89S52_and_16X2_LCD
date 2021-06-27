/* -Deeptimaan Banerjee */
#include<reg51.h>
#define display_port P2    
sbit rs = P1^2;  
sbit e =  P1^3;  
sbit i = P3^2;
unsigned int pos=0;
unsigned int temp_pos=10;
unsigned int sema=1;


void msdelay(unsigned int time)  // Delay function milliseconds.
{
    unsigned i,j;
    for(i=0;i<time;i++)    
    for(j=0;j<1275;j++);
}

void ext_int_0 (void) interrupt 0 
{ 	
		
			if(pos==0)
			{
				pos=1;
			}
			else
			{
				pos=0;
			}
		
		msdelay(1);
}

void lcd_cmd(unsigned char command)  
{
    display_port = command;
    rs= 0;
    e=1;
    msdelay(1);
    e=0;
}

void lcd_data(unsigned char disp_data)  
{
    display_port = disp_data;
    rs= 1;
    e=1;
    msdelay(1);
    e=0;
}
void lcd_frist_msg()
{
		unsigned char a[12]="FLAPPY BIRD";    
    int l=0;
    while(a[l] != '\0') 
    {
        lcd_data(a[l]);
        l++;
				msdelay(1);
    }
}

void game_over()
{
		unsigned char a[11]="GAME OVER";    
    int l=0;
		lcd_cmd(0x01); 
		msdelay(1);
		lcd_cmd(0x80);	
		msdelay(1);
    while(a[l] != '\0') 
    {
        lcd_data(a[l]);
        l++;
				msdelay(1);
    }
		msdelay(500);
}

void game_won()
{
		unsigned char a[8]="YOU WON";    
    int l=0;
		lcd_cmd(0x01); 
		msdelay(1);
		lcd_cmd(0x80);	
		msdelay(1);
    while(a[l] != '\0') 
    {
        lcd_data(a[l]);
        l++;
				msdelay(1);
    }
		msdelay(500);
}

 void lcd_init()    
{
    lcd_cmd(0x38);  // for using 2 lines and 5X7 matrix of LCD
    msdelay(1);
    lcd_cmd(0x01);  //clear screen
    msdelay(1);
    lcd_cmd(0x80);  // bring cursor to position 1 of line 1
    msdelay(1);
		lcd_frist_msg();
		lcd_cmd(0x0C);  // turn display ON, cursor off
		msdelay(1);
		msdelay(500);
}

	
void main()
{
	while(1){
	unsigned int i=0;
	unsigned int j=0;
	unsigned int k=0;
	code unsigned char so[50]="       1     1       1     1                      ";  
	code unsigned char st[50]="  1       1     1       1                         ";  
	lcd_cmd(0x01);
	lcd_init();
	pos=0;
	i=1;
	temp_pos=10;
	sema=1;
  EX0 = 1;    
  EA  = 1;
	IT0=1;
	for (i=0;i<=32;i++)
	{
		for (k=0;k<2;k++)
		{
				if(k==0){
						lcd_cmd(0x80); //bring cursor to first line
				}
				if(k==1){
						lcd_cmd(0xC0); //bring cursor to second line
				}
				for(j=i;j<i+16;j++)
				{
					if(k==0)
					{
						if(pos==0 && j==i)
						{
							sema=0;
							lcd_data('0');
						}
						else
						{
							sema=0;
							lcd_data(so[j]);
						}
					}
					if(pos==0 && j==i && so[j]=='1')
					{
						game_over();
						i=100;
						j=100;
						k=100;
						break;
					}
					if(k==1)
					{
						if(pos==1 && j==i)
						{
							lcd_data('0');
						}
						else
						{
							lcd_data(st[j]);
						}
					}
					if(pos==1 && j==i && st[j]=='1')
					{
						game_over();
						i=100;
						j=100;
						k=100;
						break;
					}
					if(k==1 && j>=47)
					{
						game_won();
						i=100;
						j=100;
						k=100;
						break;
					}
					
				}
				
			}
		}
	}
}