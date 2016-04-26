/*************************************************************/
// project    :	221-5059-0918
// driver IC  :	st7565p
// LCD        :	1/65 duty, 1/9bias, 9V vop
// interface  :	SPI
// ver        :	00 
// date       :  -07
// other      :	VDD 3.0v
/**************************************************************/
#include "LCD_LIXIAN.h"
#include "delay.h"
//#include <math.h>

//串口模式下只能写不能读,也不能查忙,因此用户要控制好速度不要太快
void WriteCommand( Uchar CommandByte )
{
	Uchar i;
	CS=0;
	RS=0;		//Command
	for(i=0;i<8;i++)
	{	SCK=1;
		SID=( (CommandByte>>(7-i)) &0x01);
		SCK=0;
//		DelayUs(1);
		SCK=1;
	}
}

void WriteData( Uchar DataByte )
{
	Uchar i;
	CS=0;
	RS=1;		//Data
	for(i=0;i<8;i++)
	{
		SCK=1;
		SID=( (DataByte>>(7-i)) &0x01);
		SCK=0;
//		DelayUs(1);
		SCK=1;
	}
}

void LcmClear( Uchar FillData )
{
	Uint i,j;
	for(i=0;i<8;i++)
	{
		WriteCommand(0xB0|ComTable[i]);	//Set Page Address
		WriteCommand(0x10);	//Set Column Address = 0
		WriteCommand(0x00);	//Colum from S1 -> S128 auto add
		for(j=0;j<128;j++)
		{
			WriteData( FillData );
		}
	}
}

void LcmInit( void )
{
	RES = 1;
	DelayMs(100);
	RES = 0;
	DelayMs(200);
	RES = 1;
	DelayMs(100);

	WriteCommand(0xAE);	//Display OFF
	WriteCommand(0xA2);	//1/64 Duty 1/9 Bias
	WriteCommand(0xA0);	//ADC select S0->S131(玻璃设计用S1-S128)
	WriteCommand(0xC0);	//com1 --> com64
	WriteCommand(0x24);	//对某些模块没用,用的外部Rb/Ra
	WriteCommand(0x81);	//Sets V0
	WriteCommand(48);	//内部电位器调节对比度
	WriteCommand(0x2F);	//voltage follower ON  regulator ON  booster ON
	WriteCommand(0xA6);	//Normal Display (not reverse dispplay)
	WriteCommand(0xA4);	//Entire Display Disable	
	WriteCommand(0x40);	//Set Display Start Line = com0
	WriteCommand(0xB0);	//Set Page Address = 0
	WriteCommand(0x10);	//Set Column Address 4 higher bits = 0
	WriteCommand(0x01);	//Set Column Address 4 lower bits = 1 , from IC SEG1 -> SEG128
	LcmClear(0);
	WriteCommand(0xAF);	//Display ON
}

//显示ASICC字符的函数
void LcmPutChar(Uchar col,Uchar page,Uchar Order)
{
	Uchar i;
	Uint x;
	x = (Order-0x20)*0x10;			//ASICC字符从0x20开始,每个16 byte
	WriteCommand(ComTable[page&0x07]|0xB0);	//Set Page Address
	WriteCommand( ((col+1)>>4) | 0x10);	//Set Column Address High Byte
	WriteCommand( (col+1)&0x0F );		//Low Byte  Colum from S128 -> S1 auto add


	for(i=0;i<8;i++)
	{
		WriteData( ASCIIchardot[x] );
		x++;
	}
	page++;					//下半字符page+1
	
	WriteCommand(ComTable[page&0x07]|0xB0);	//Set Page Address
	WriteCommand( ((col+1)>>4) | 0x10);		//Set Column Address High Byte
	WriteCommand( (col+1)&0x0F );			//Low Byte  Colum from S128 -> S1 auto add
	
	for(i=0;i<8;i++)
	{
		WriteData( ASCIIchardot[x] );
		x++;
	}
	page--;					//写完一个字符page还原
}
//反显ASICC字符的函数
void LcmPutCharInv(Uchar col,Uchar page,Uchar Order)
{
	Uchar i;
	Uint x;
	x = (Order-0x20)*0x10;			//ASICC字符从0x20开始,每个16 byte
	WriteCommand(ComTable[page&0x07]|0xB0);	//Set Page Address
	WriteCommand( ((col+1)>>4) | 0x10);	//Set Column Address High Byte
	WriteCommand( (col+1)&0x0F );		//Low Byte  Colum from S128 -> S1 auto add


	for(i=0;i<8;i++)
	{
		WriteData( ~ASCIIchardot[x] );
		x++;
	}
	page++;					//下半字符page+1
	
	WriteCommand(ComTable[page&0x07]|0xB0);	//Set Page Address
	WriteCommand( ((col+1)>>4) | 0x10);		//Set Column Address High Byte
	WriteCommand( (col+1)&0x0F );			//Low Byte  Colum from S128 -> S1 auto add
	
	for(i=0;i<8;i++)
	{
		WriteData( ~ASCIIchardot[x] );
		x++;
	}
	page--;					//写完一个字符page还原
}

//显示字符串的函数
void LcmPutStr(Uchar col,Uchar page,Uchar *puts)
{
	while(*puts != '\0')		//判断字符串时候显示完毕
	{
		
		if(col>(LcmXPixel-8))		//判断行末空间是否足够放一个字符,自动换行
		{
			page=page+2;
			col=0;
		}
		if(page>(LcmYPixel/8-2))	//到了屏幕最下角,自动返回左上角
		{
			page=0;
			col=0;
		}	
		LcmPutChar(col,page,*puts);
		puts++;
		col=col+8;		//下一个字符8列之后
	}
}
//显示3位数的数值(0-255)
/*void LcmPutNum(Uchar col,Uchar page,Uchar Num)
{
	Uchar a,b,c;
	a=Num/100;
	b=(Num%100)/10;
	c=Num%10;
	if(a==0) ;	//也不写空格,直接跳过去//PutChar(col,page,0x20);
	  else LcmPutChar(col,page,a+0x30);
	  
	if(a==0 && b==0) ;	//也不写空格,直接跳过去//LcmPutChar(col,page,0x20);
	  else LcmPutChar(col+8,page,b+0x30);
	  
	LcmPutChar(col+16,page,c+0x30);
}
*/
void LcmPutNum(unsigned char col,unsigned char page, int Num)
{
    unsigned char a,i,j,k,flag;
    int NumLeft,b;
    k=col;
    flag = 0;
    NumLeft = Num;
    if(Num<0)
    {
        LcmPutChar(k,page,'-');
        k=k+8;
        NumLeft = -Num;
    }
    for(i=4;i>0;i--)
    {
        b=NumLeft;
        for(j=0;j<i;j++)
        {
        b=b/10;
        }
        a=b;
        if(a>0 || flag==1)
        {
            LcmPutChar(k,page,a+0x30);
            k=k+8;   //左对齐
            //NumLeft = NumLeft - a*10^(4-i);
            flag = 1;
        }
        b=a;
        for(j=0;j<i;j++)
        {
        b=b*10;
        }
        NumLeft = NumLeft%b;
        //k=k+8; //右对齐
    }
    LcmPutChar(k,page,NumLeft+0x30);
}

void LcmPutFixDigit(unsigned char page,unsigned char col, int Num, unsigned char nLen, unsigned char nInvIndex)
{
    unsigned char i,j,k;
    int NumLeft,b;
    k=col;

    NumLeft = Num;
    if(Num<0)
    {
        LcmPutChar(k,page,'-');
        k=k+8;
        NumLeft = -Num;
    }
    for(i=nLen;i>0;i--)
    {
        b=NumLeft;
        for(j=1;j<i;j++)
        {
            b=b/10;
        }
        if(i == nInvIndex)
            LcmPutCharInv(k,page,b+0x30);
        else
            LcmPutChar(k,page,b+0x30);
        k=k+8;
        for(j=1;j<i;j++)
        {
        b=b*10;
        }
        NumLeft = NumLeft%b;
        //k=k+8; //右对齐
    }
    //LcmPutChar(k,page,NumLeft+0x30);
}

void LcmPutFloatDigit(unsigned char page,unsigned char col, int Num, unsigned char nLen, unsigned char nInvIndex, unsigned char nDotIndex)
{
    unsigned char i,k;
    int NumLeft,b;
    k=col;

    NumLeft = Num;
    if(Num<0)
    {
        LcmPutChar(k,page,'-');
        k=k+8;
        NumLeft = -Num;
    }
    for(i=0;i<nDotIndex;i++)
    {
        b=NumLeft%10;
        if((i+1) == nInvIndex)
            LcmPutCharInv(k+8*(nLen-i),page,b+0x30);
        else
            LcmPutChar(k+8*(nLen-i),page,b+0x30);
        NumLeft = NumLeft/10;
    }
    if(nDotIndex>0)  //显示小数点
    {
        LcmPutChar(k+8*(nLen-nDotIndex),page,'.');
    }
    for(i=nDotIndex;i<nLen;i++)
    {
        b=NumLeft%10;
        if((i+1) == nInvIndex)
            LcmPutCharInv(k+8*(nLen-1-i),page,b+0x30);
        else
            LcmPutChar(k+8*(nLen-1-i),page,b+0x30);
        NumLeft = NumLeft/10;
    }
}

void LcmPutBmp( Uchar *puts )
{
	Uchar i,j;
	Uint X=0;
	for(i=0;i<(LcmYPixel/8);i++)
	{
		WriteCommand(0xB0|ComTable[i]);	//Set Page Address
		WriteCommand(0x10);	//Set Column Address = 0
		WriteCommand(0x00);	//Colum from S1 -> S128 auto add
		for(j=0;j<LcmXPixel;j++)
		{
			WriteData( puts[X] );
			X++;
		}
	}
}

void LcmPutCChar()
{
    unsigned char CChar[2][16] = {
        {0x08,0x06,0x40,0x31,0x00,0x00,0x7F,0x49,0x49,0x49,0x49,0x49,0x7F,0x00,0x00,0x00},
        {0x20,0x20,0x7E,0x80,0x02,0x7E,0x42,0x42,0x7E,0x42,0x7E,0x42,0x42,0x7E,0x02,0x00}/*"温",0*/
    };
    Uchar i,j;
	for(i=0;i<2;i++)
	{
		WriteCommand(0xB0|ComTable[i]);	//Set Page Address
		WriteCommand(0x10);	//Set Column Address = 0
		WriteCommand(0x00);	//Colum from S1 -> S128 auto add
		for(j=0;j<16;j++)
		{
			WriteData( SONGchardot[i][j] );
		}
	}
}
void LcmPutSongStr(unsigned char nLine, unsigned char nCol,unsigned char nCharIndex[],unsigned char nLen, unsigned char nInv)
{
    unsigned char i,j,k;
    for(k=0;k<nLen;k++)
    {
        for(i=0;i<2;i++)
        {
            WriteCommand(0xB0|ComTable[i+nLine]);	//Set Page Address
            WriteCommand(0x10|(nCol+k*16)>>4);	//Set Column Address = 0
            WriteCommand(0x0F&(nCol+k*16));	//Colum from S1 -> S128 auto add
            for(j=0;j<16;j++)
            {
                if(nInv==0)
                    WriteData( SONGchardot[(nCharIndex[k]-1)*2+i][j] );
                else
                    WriteData( ~SONGchardot[(nCharIndex[k]-1)*2+i][j] );
            }
        }
    }
    
}

void LcmSetSongBuff(unsigned char ch1,unsigned char ch2,unsigned char ch3,unsigned char ch4,unsigned char ch5,unsigned char ch6,unsigned char ch7,unsigned char ch8)
{
                BuffCharDot[0]=ch1;
                BuffCharDot[1]=ch2;
                BuffCharDot[2]=ch3;
                BuffCharDot[3]=ch4;
                BuffCharDot[4]=ch5;
                BuffCharDot[5]=ch6;
                BuffCharDot[6]=ch7;
                BuffCharDot[7]=ch8;
}
