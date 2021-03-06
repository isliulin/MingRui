#ifndef	__LCD_LIXIAN_h__
#define	__LCD_LIXIAN_h__
#include <xc.h>
//#include <intrins.h>
#define  CS PORTDbits.RD2
#define  RS PORTDbits.RD0
#define RES PORTDbits.RD1
#define  SCK PORTCbits.RC3
#define SID PORTCbits.RC5

#define	LcmXPixel 128	//横向宽度
#define	LcmYPixel 64	//纵向高度
#define MIN(A,B) ((A)<(B)?(A):(B))
#define Uchar unsigned char
#define Uint  unsigned int
#define code const


//Uchar code ASCIIchardot[];
unsigned char BuffCharDot[8];
//Uchar code bmp1[];
//Uchar code bmp2[];
//Uchar code bmp3[];
Uchar code ComTable[]={7,6,5,4,3,2,1,0,};

void WriteCommand( Uchar CommandByte );
void WriteData( Uchar DataByte );
void LcmClear( Uchar FillData );
void LcmInit( void );
void LcmPutChar(Uchar col,Uchar page,Uchar Order);
void LcmPutStr(Uchar col,Uchar page,Uchar *puts);
//void LcmPutNum(Uchar col,Uchar page,Uchar Num);
void LcmPutNum(unsigned char col,unsigned char page,int Num);
void LcmPutFixDigit(unsigned char page,unsigned char col, int Num, unsigned char nLen, unsigned char nInvIndex);
void LcmPutFloatDigit(unsigned char page,unsigned char col, int Num, unsigned char nLen, unsigned char nInvIndex, unsigned char nDotIndex);
void LcmPutCharInv(Uchar col,Uchar page,Uchar Order);
void LcmPutBmp( Uchar *puts );
void LcmPutCChar(void);
void LcmPutSongStr(unsigned char nLine, unsigned char nCol,unsigned char nCharIndex[],unsigned char nLen, unsigned char nInv);
void LcmSetSongBuff(unsigned char ch1,unsigned char ch2,unsigned char ch3,unsigned char ch4,unsigned char ch5,unsigned char ch6,unsigned char ch7,unsigned char ch8);
/*中文字库*/
unsigned char code SONGchardot[246][16] = {
{0x20,0x24,0x22,0x21,0x26,0x39,0x02,0x0C,0xF0,0x13,0x10,0x10,0x14,0x18,0x00,0x00},
{0x08,0x10,0x60,0x80,0x41,0x32,0x04,0x18,0x60,0x80,0x60,0x18,0x04,0x02,0x01,0x00},/*"欢",0*/
{0x02,0x02,0x42,0x33,0x00,0x00,0x3F,0x20,0x40,0x00,0x3F,0x20,0x20,0x3F,0x00,0x00},
{0x00,0x02,0x04,0xF8,0x04,0x02,0xF2,0x22,0x42,0x02,0xFE,0x42,0x22,0xC2,0x02,0x00},/*"迎",1*/
{0x01,0x06,0x1F,0xE0,0x20,0x27,0x24,0x24,0x24,0xFF,0x24,0x24,0x24,0x27,0x20,0x00},
{0x00,0x00,0xFF,0x00,0x01,0x81,0xA2,0x94,0x88,0xF4,0x82,0x82,0x81,0x81,0x01,0x00},/*"使",2*/
{0x00,0x00,0x7F,0x44,0x44,0x44,0x44,0x7F,0x44,0x44,0x44,0x44,0x7F,0x00,0x00,0x00},
{0x01,0x06,0xF8,0x40,0x40,0x40,0x40,0xFE,0x40,0x40,0x42,0x41,0xFE,0x00,0x00,0x00},/*"用",3*/
{0x00,0x1F,0x10,0xFF,0x10,0x1F,0x00,0x7C,0x55,0x56,0x7C,0x54,0x55,0x7C,0x00,0x00},
{0x04,0xC6,0x84,0xF8,0x88,0x9C,0x12,0x94,0x90,0xB1,0xDF,0x90,0x10,0x34,0x1A,0x00},/*"螺",0*/
{0x08,0x08,0x0B,0xFF,0x09,0x08,0x01,0x41,0x41,0x41,0x7F,0x41,0x41,0x41,0x01,0x00},
{0x20,0xC0,0x00,0xFF,0x00,0xC0,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00},/*"杆",1*/
{0x00,0x00,0x7F,0x40,0x41,0x41,0x41,0x41,0x5F,0x41,0x41,0x41,0x41,0x41,0x40,0x00},
{0x01,0x06,0xF8,0x02,0x02,0x02,0x02,0x02,0xFE,0x02,0x02,0x22,0x1A,0x02,0x02,0x00},/*"压",2*/
{0x04,0x1C,0xE7,0x0C,0x00,0x31,0x23,0x2C,0x24,0xA4,0x65,0x26,0x24,0x24,0x34,0x00},
{0x44,0xE4,0x48,0x48,0x80,0x00,0xFF,0x00,0x00,0xFF,0x92,0x92,0x92,0xFF,0x00,0x00},/*"缩",3*/
{0x08,0x08,0x0B,0xFF,0x09,0x08,0x00,0x7F,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,0x00},
{0x20,0xC0,0x00,0xFF,0x00,0xC1,0x06,0xF8,0x00,0x00,0x00,0xFC,0x02,0x02,0x1E,0x00},/*"机",4*/
{0x08,0x06,0x40,0x31,0x00,0x00,0x7F,0x49,0x49,0x49,0x49,0x49,0x7F,0x00,0x00,0x00},
{0x20,0x20,0x7E,0x80,0x02,0x7E,0x42,0x42,0x7E,0x42,0x7E,0x42,0x42,0x7E,0x02,0x00},/*"温",0*/
{0x00,0x00,0x3F,0x24,0x24,0x24,0x3F,0xA4,0x64,0x24,0x3F,0x24,0x24,0x24,0x20,0x00},
{0x02,0x0C,0xF1,0x01,0x21,0x32,0xAA,0xA4,0xA4,0xA4,0xAA,0x32,0x01,0x01,0x01,0x00},/*"度",1*/
{0x60,0x90,0x90,0x67,0x1F,0x30,0x20,0x40,0x40,0x40,0x40,0x40,0x20,0x78,0x00,0x00},
{0x00,0x00,0x00,0xE0,0xF8,0x0C,0x04,0x02,0x02,0x02,0x02,0x02,0x04,0x08,0x00,0x00},/*"℃",2*/
{0x02,0x02,0x42,0x33,0x00,0x02,0x05,0x79,0x41,0x41,0x41,0x79,0x05,0x04,0x04,0x00},
{0x00,0x00,0x00,0xFC,0x09,0x11,0x02,0xC2,0x34,0x08,0x14,0x62,0x82,0x01,0x01,0x00},/*"设",3*/
{0x01,0x09,0x09,0x12,0x32,0xEA,0x24,0x24,0x24,0x2A,0x32,0x22,0x01,0x01,0x01,0x00},
{0x00,0x00,0x00,0xFF,0x92,0x92,0x92,0xFE,0x92,0x92,0x92,0xFF,0x00,0x00,0x00,0x00},/*"备",4*/
{0x00,0x00,0x47,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x7F,0x00,0x00,0x00,0x00},
{0x00,0x00,0xFC,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x1E,0x00,0x00},/*"已",5*/
{0x04,0x0C,0x35,0xC6,0x04,0x18,0x01,0x41,0x42,0x44,0x48,0x58,0x64,0x42,0x01,0x00},
{0x44,0xE6,0x44,0x48,0x48,0x48,0x02,0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x02,0x00},/*"经",6*/
{0x01,0x06,0x1F,0xE0,0x00,0x20,0x2E,0x2A,0xAA,0x6A,0x2A,0x2A,0x2E,0x20,0x00,0x00},
{0x00,0x00,0xFF,0x00,0xC0,0x80,0xA0,0xA2,0xA1,0xBE,0xA0,0xA0,0xA0,0x80,0xC0,0x00},/*"停",7*/
{0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0xFF,0x02,0x02,0x02,0x02,0x02,0x00,0x00,0x00},
{0x02,0x02,0x02,0xFE,0x02,0x02,0x02,0xFE,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x00},/*"止",8*/
{0x24,0x24,0x25,0x7F,0xC4,0x44,0x00,0x03,0x1C,0x00,0xFF,0x00,0x10,0x08,0x06,0x00},
{0x10,0x60,0x80,0xFF,0x80,0x60,0x81,0x01,0x02,0x02,0xE4,0x08,0x30,0xC0,0x00,0x00},/*"秒",9*/
{0x02,0x02,0x42,0x33,0x00,0x04,0x44,0x44,0x45,0x46,0x44,0x44,0x44,0x04,0x00,0x00},
{0x00,0x02,0x04,0xF8,0x04,0x22,0x72,0xA2,0x22,0x22,0x22,0xA2,0x62,0x32,0x02,0x00},/*"运",10*/
{0x00,0x08,0x11,0x23,0xCC,0x00,0x02,0x42,0x42,0x42,0x43,0x42,0x42,0x42,0x02,0x00},
{0x40,0x80,0x00,0xFF,0x00,0x00,0x00,0x00,0x02,0x01,0xFE,0x00,0x00,0x00,0x00,0x00},/*"行",11*/
{0x00,0x04,0x04,0x15,0x36,0x54,0x9C,0x14,0x15,0x54,0x36,0x15,0x04,0x04,0x00,0x00},
{0x40,0x41,0x81,0x09,0x49,0x52,0x92,0xA2,0x24,0x44,0x08,0x10,0x80,0x40,0x40,0x00},/*"参",12*/
{0x09,0x4A,0x2C,0x08,0xFF,0x08,0x2C,0x4A,0x01,0x0E,0xF1,0x10,0x10,0x1F,0x10,0x00},
{0x41,0x59,0x6A,0xC6,0x44,0x4A,0x71,0x00,0x01,0x02,0xCC,0x30,0xCC,0x02,0x01,0x00},/*"数",13*/
{0x00,0x00,0x00,0x1F,0x10,0x10,0x90,0x70,0x10,0x10,0x10,0x10,0x1F,0x00,0x00,0x00},
{0x00,0x01,0x06,0xF8,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xC0,0x00,0x00,0x00},/*"户",14*/
{0x00,0x00,0x7F,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00},
{0x01,0x06,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"厂",15*/
{0x08,0x34,0x24,0x24,0x25,0x25,0xA6,0x65,0x24,0x24,0x24,0x24,0x25,0x2C,0x30,0x00},
{0x02,0x92,0x92,0x94,0x24,0x28,0x4A,0x91,0xFE,0x20,0x50,0x88,0x08,0x04,0x04,0x00},/*"家",16*/
{0x02,0x42,0x33,0x00,0x00,0x7F,0x41,0x49,0x49,0x7F,0x49,0x49,0x41,0x7F,0x00,0x00},
{0x00,0x00,0xFC,0x08,0x11,0xFE,0x00,0x78,0x48,0x48,0x48,0x7A,0x01,0xFE,0x00,0x00},/*"调",17*/
{0x20,0x2E,0x2B,0x2A,0xFF,0x2A,0x2B,0x2E,0x28,0x10,0xEE,0x21,0x22,0x3C,0x20,0x00},
{0x41,0x91,0x11,0x17,0xD1,0x11,0x11,0x9F,0x15,0x55,0x95,0x15,0x95,0x51,0x41,0x00},/*"整",18*/
{0x00,0x10,0x10,0x10,0x10,0x10,0x90,0x5F,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00},
{0x02,0x02,0x82,0x82,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x82,0x82,0x02,0x02,0x00},/*"主",19*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x6C,0x6C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"：",20*/
{0x00,0x00,0x00,0x3F,0x22,0x22,0x22,0xA2,0x62,0x22,0x22,0x22,0x22,0x3E,0x00,0x00},
{0x02,0x04,0x18,0xE0,0x00,0x3F,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x3F,0x00,0x00},/*"启",21*/
{0x02,0x22,0x23,0x22,0x22,0x22,0x02,0x08,0x08,0xFF,0x08,0x08,0x08,0x0F,0x00,0x00},
{0x08,0x3C,0xC8,0x08,0x28,0x1D,0x02,0x0C,0x70,0x80,0x02,0x01,0x02,0xFC,0x00,0x00},/*"动",22*/
{0x00,0x3F,0x21,0x21,0x21,0x3F,0x00,0x08,0x08,0x08,0x08,0x08,0xFF,0x08,0x08,0x00},
{0x00,0xFC,0x08,0x08,0x08,0xFC,0x00,0x00,0x80,0x60,0x02,0x01,0xFE,0x00,0x00,0x00},/*"时",23*/
{0x00,0x1F,0x80,0x60,0x00,0x0F,0x48,0x48,0x48,0x4F,0x40,0x40,0x40,0x7F,0x00,0x00},
{0x00,0xFF,0x00,0x00,0x00,0xF8,0x88,0x88,0x88,0xF8,0x00,0x02,0x01,0xFE,0x00,0x00},/*"间",24*/
{0x08,0x08,0x08,0xFF,0x08,0x08,0x0F,0x00,0x00,0x1F,0x10,0x10,0x10,0x1F,0x00,0x00},
{0x01,0x02,0x0C,0xF0,0x02,0x01,0xFE,0x00,0x00,0xFE,0x04,0x04,0x04,0xFE,0x00,0x00},/*"加",25*/
{0x09,0x29,0x29,0x2F,0xF9,0x29,0x29,0x29,0x08,0x08,0xFF,0x08,0x48,0x2B,0x08,0x00},
{0x04,0x64,0xA4,0x24,0x7F,0x28,0x28,0x28,0x01,0x02,0xE4,0x18,0x64,0x82,0x0F,0x00},/*"载",26*/
{0x20,0x21,0x23,0x2D,0x31,0x00,0x00,0x27,0x20,0x20,0x7F,0x42,0xC2,0x42,0x00,0x00},
{0x01,0x22,0x14,0x18,0xE4,0x04,0x02,0xF2,0x12,0x12,0xF2,0x12,0x12,0x12,0x02,0x00},/*"延",27*/
{0x11,0x16,0xF8,0x13,0x10,0x08,0x13,0x2A,0x4A,0x8B,0x48,0x29,0x10,0x0B,0x08,0x00},
{0x90,0x98,0x90,0xFF,0xA0,0x00,0xFF,0x48,0x49,0xFF,0x00,0xFA,0x01,0xFE,0x00,0x00},/*"输",28*/
{0x00,0x00,0x00,0x00,0x00,0x80,0x47,0x38,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x01,0x02,0x04,0x08,0x30,0xC0,0x00,0x00,0x00,0xC0,0x30,0x0C,0x02,0x01,0x01,0x00},/*"入",29*/
{0x08,0x31,0x22,0x20,0x27,0x20,0xA9,0x65,0x22,0x24,0x28,0x21,0x22,0x29,0x30,0x00},
{0x40,0x40,0x5E,0x82,0x82,0xC2,0x42,0x7E,0x42,0x42,0x42,0xC2,0x1F,0x00,0x00,0x00},/*"密",30*/
{0x20,0x21,0x27,0x3A,0x22,0x23,0x00,0x40,0x4F,0x41,0x41,0x41,0x7F,0x01,0x01,0x00},
{0x40,0x80,0xFE,0x08,0x08,0xFC,0x00,0x10,0x10,0x10,0x10,0x12,0x11,0x02,0xFC,0x00},/*"码",31*/
{0x00,0x00,0x7F,0x40,0x48,0x44,0x43,0x40,0x43,0x4C,0x40,0x7F,0x00,0x00,0x00,0x00},
{0x01,0x06,0xF8,0x00,0x04,0x08,0x30,0xC0,0x30,0x0C,0x00,0xF0,0x0C,0x02,0x1F,0x00},/*"风",32*/
{0x08,0x30,0x22,0x24,0x28,0x20,0xA0,0x60,0x20,0x20,0x28,0x24,0x22,0x28,0x30,0x00},
{0x00,0x02,0x02,0x82,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x82,0x02,0x02,0x00,0x00},/*"空",33*/
{0x08,0x08,0x28,0x2B,0x2A,0x2A,0x2A,0x3F,0x4A,0x4A,0x4A,0xCB,0x48,0x08,0x08,0x00},
{0x02,0x02,0x0A,0xEA,0xAA,0xAA,0xAA,0xFE,0xAA,0xAA,0xAA,0xEA,0x0A,0x02,0x02,0x00},/*"重",34*/
{0x10,0x10,0x10,0x10,0x10,0x1F,0x91,0x71,0x11,0x11,0x11,0x11,0x10,0x10,0x10,0x00},
{0x00,0x01,0x02,0x04,0x18,0xE0,0x00,0x00,0x02,0x01,0x02,0xFC,0x00,0x00,0x00,0x00},/*"方",35*/
{0x08,0x08,0x09,0x09,0x09,0x09,0x09,0x08,0x08,0xFF,0x08,0x08,0x88,0x68,0x08,0x00},
{0x00,0x04,0x06,0x04,0xFC,0x08,0x08,0x08,0x00,0xC0,0x30,0x08,0x04,0x02,0x1F,0x00},/*"式",36*/
{0x02,0x42,0x33,0x00,0x00,0x47,0x44,0x54,0x54,0x4F,0x54,0x64,0x44,0x07,0x00,0x00},
{0x01,0x02,0xFC,0x02,0x01,0xFF,0x91,0x91,0x91,0xFD,0x91,0x95,0x93,0xFD,0x01,0x00},/*"通",37*/
{0x02,0x02,0x42,0x33,0x00,0x41,0x41,0x7F,0x41,0x41,0x40,0x7F,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0xFE,0x04,0x08,0x00,0xFF,0x00,0x00,0x00,0xF0,0x0C,0x02,0x1F,0x00},/*"讯",38*/
{0x04,0x0C,0x35,0xC6,0x0C,0x00,0x3F,0x24,0xA4,0x64,0x24,0x24,0x24,0x3C,0x00,0x00},
{0x44,0xE6,0x44,0x48,0x4A,0x1C,0xE0,0xFF,0x90,0xFE,0x90,0xFC,0x91,0xFF,0x00,0x00},/*"编",39*/
{0x20,0x21,0x27,0x3A,0x22,0x23,0x00,0x40,0x4F,0x41,0x41,0x41,0x7F,0x01,0x01,0x00},
{0x40,0x80,0xFE,0x08,0x08,0xFC,0x00,0x10,0x10,0x10,0x10,0x12,0x11,0x02,0xFC,0x00},/*"码",40*/
{0x40,0x7F,0x49,0x49,0x7F,0x40,0x00,0x08,0x88,0x68,0x0F,0x28,0xC8,0x08,0x00,0x00},
{0x08,0xF8,0x10,0x10,0xFF,0x20,0x81,0x82,0x8C,0xB0,0xC0,0xB0,0x8C,0x82,0x81,0x00},/*"联",0*/
{0x00,0x10,0x0C,0x00,0xFF,0x04,0x04,0x04,0x04,0xFF,0x04,0x04,0x44,0x34,0x04,0x00},
{0x20,0x20,0x40,0x80,0xFF,0x01,0x02,0x0C,0x70,0x80,0x60,0x18,0x04,0x02,0x01,0x00},/*"状",1*/
{0x00,0x20,0x21,0x21,0x22,0x24,0x2A,0xF1,0x28,0x24,0x22,0x21,0x21,0x20,0x00,0x00},
{0x82,0x9C,0x00,0x00,0x3C,0x02,0x02,0x42,0x32,0x02,0x02,0x0E,0x20,0x90,0x8C,0x00},/*"态",2*/
{0x13,0x1D,0xF1,0x17,0x11,0x13,0x04,0x09,0x30,0xC0,0x30,0x09,0x04,0x02,0x02,0x00},
{0x10,0x18,0x10,0xFF,0x20,0x20,0x00,0xFC,0x22,0x42,0x82,0x02,0x02,0x0E,0x00,0x00},/*"轮",3*/
{0x08,0x08,0x08,0xFF,0x09,0x04,0x08,0x17,0xE4,0x24,0x27,0x2C,0x34,0x07,0x00,0x00},
{0x40,0x42,0x81,0xFE,0x00,0x21,0x21,0xE2,0x24,0x38,0xE0,0x38,0x24,0xE2,0x21,0x00},/*"换",4*/
{0x00,0x08,0x08,0x08,0x08,0x08,0xFF,0x08,0x08,0x08,0x08,0x08,0x0F,0x00,0x00,0x00},
{0x00,0x01,0x02,0x04,0x18,0x60,0x80,0x00,0x04,0x02,0x01,0x02,0xFC,0x00,0x00,0x00},/*"力",5*/
{0x08,0x12,0xE2,0x22,0x3F,0x22,0x22,0x22,0x00,0x3F,0x20,0x20,0x20,0x3F,0x00,0x00},
{0x04,0x06,0x7C,0x04,0xF8,0x48,0x48,0x08,0x00,0xFF,0x00,0x10,0x08,0xF0,0x00,0x00},/*"卸",6*/
{0x08,0x06,0x40,0x31,0x00,0x0F,0x08,0x08,0x08,0xFF,0x08,0x08,0x08,0x0F,0x00,0x00},
{0x20,0x20,0x7E,0x80,0x00,0xFF,0x42,0x42,0x42,0xFE,0x42,0x42,0x42,0xFF,0x00,0x00},/*"油",7*/
{0x08,0x06,0x40,0x31,0x00,0x1F,0x12,0x12,0x12,0xFF,0x54,0x54,0x50,0x53,0x18,0x00},
{0x20,0x20,0x7E,0x81,0x06,0xF8,0x01,0x0E,0x00,0x1E,0xC1,0xB1,0x83,0x90,0x0E,0x00},/*"滤",8*/
{0x01,0x01,0x79,0x49,0x49,0x49,0x79,0x07,0x01,0x79,0x4D,0x4B,0x49,0x79,0x01,0x00},
{0x10,0x10,0x2F,0x29,0x49,0x49,0x8F,0x00,0x80,0x4F,0x49,0x29,0x29,0x1F,0x10,0x00},/*"器",9*/
{0x04,0x08,0x10,0xEF,0x2A,0x2A,0x2A,0x2A,0x2A,0x2A,0x2A,0x2F,0x20,0x20,0x00,0x00},
{0x01,0x09,0x09,0x92,0xB2,0xEA,0xA4,0xA4,0xA4,0xAA,0xB2,0xA2,0x01,0x01,0x01,0x00},/*"复",10*/
{0x00,0x01,0x06,0x1F,0xE0,0x08,0x09,0x08,0x88,0x68,0x08,0x08,0x0B,0x08,0x00,0x00},
{0x80,0x00,0x00,0xFF,0x02,0x02,0x82,0x7A,0x02,0x02,0x0E,0x72,0x82,0x02,0x02,0x00},/*"位",11*/
{0x01,0x02,0x04,0x09,0x11,0x61,0x01,0x01,0x01,0xC1,0x31,0x08,0x04,0x02,0x01,0x00},
{0x00,0x01,0x02,0x04,0x18,0xE0,0x00,0x02,0x01,0x02,0xFC,0x00,0x00,0x00,0x00,0x00},/*"分",12*/
{0x08,0x06,0x40,0x31,0x00,0x3F,0x80,0x68,0x08,0x4F,0x48,0x48,0x40,0x7F,0x00,0x00},
{0x20,0x20,0x7E,0x80,0x00,0xFF,0x00,0x88,0x88,0xF8,0x88,0x8A,0x01,0xFE,0x00,0x00},/*"润",13*/
{0x08,0x06,0x40,0x31,0x06,0x04,0x7D,0x55,0x55,0x5D,0x45,0x45,0x7D,0x04,0x06,0x00},
{0x20,0x20,0x7E,0x80,0x00,0x00,0xFF,0x50,0x50,0x50,0x52,0x51,0xFE,0x00,0x00,0x00},/*"滑",14*/
{0x00,0x00,0x7F,0x44,0x44,0x7F,0x00,0xFC,0x12,0x12,0x22,0x22,0x22,0x42,0x0E,0x00},
{0x01,0x06,0xF8,0x42,0x41,0xFE,0x00,0xFF,0x92,0x92,0x92,0x92,0x92,0xFF,0x00,0x00},/*"脂",15*/
{0x00,0x00,0x1F,0x10,0x11,0x11,0x11,0x11,0xFF,0x11,0x11,0x11,0x14,0x18,0x00,0x00},
{0x01,0x06,0xF8,0x01,0x01,0xC2,0x22,0x14,0x08,0x14,0x22,0xC2,0x01,0x01,0x01,0x00},/*"皮",16*/
{0x00,0x23,0x22,0x22,0xFA,0x22,0x22,0xFB,0x22,0x22,0xFA,0x22,0x22,0x22,0x03,0x00},
{0x80,0x00,0x00,0x7C,0x40,0x40,0x40,0xFF,0x40,0x48,0x44,0x78,0x00,0x80,0x00,0x00},/*"带",17*/
{0x42,0x52,0x4B,0x56,0x62,0x03,0x00,0x4F,0x48,0x58,0x6B,0x48,0x48,0x4F,0x40,0x00},
{0x02,0x01,0xFE,0x00,0x80,0x00,0x01,0xF2,0x04,0x18,0xE0,0x08,0x04,0xF2,0x01,0x00},/*"预",18*/
{0x00,0xE8,0xA8,0xAB,0xAA,0xEA,0xAA,0xBE,0xAA,0xEA,0xAA,0xAB,0xA8,0xE8,0x00,0x00},
{0x02,0x02,0x02,0xFE,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xFE,0x02,0x02,0x02,0x00},/*"置",19*/
{0x00,0x00,0x0F,0x08,0x08,0x08,0x08,0xFF,0x08,0x08,0x08,0x08,0x0F,0x00,0x00,0x00},
{0x00,0x00,0xF0,0x20,0x20,0x20,0x20,0xFF,0x20,0x20,0x20,0x20,0xF0,0x00,0x00,0x00},/*"中",20*/
{0x20,0x20,0x20,0x23,0xF2,0x22,0x22,0x2F,0x22,0x22,0xF2,0x23,0x20,0x20,0x20,0x00},
{0x21,0x21,0x22,0xE2,0x24,0x28,0x30,0xE0,0x30,0x28,0x24,0xE2,0x22,0x21,0x21,0x00},/*"英",21*/
{0x00,0x00,0x00,0x00,0x03,0x1C,0x20,0x00,0x00,0x06,0x18,0xE0,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x03,0x1C,0x20,0x00,0x00,0x06,0x18,0xE0,0x00,0x00,0x00,0x00},/*"/",22*/
{0x10,0x10,0x10,0x1C,0x13,0x10,0x90,0x70,0x10,0x10,0x13,0x1C,0x10,0x10,0x10,0x00},
{0x01,0x01,0x02,0x02,0x04,0x88,0x50,0x20,0x50,0x88,0x04,0x02,0x02,0x01,0x01,0x00},/*"文",23*/
{0x02,0x04,0x1F,0xE0,0x0F,0x05,0x09,0x32,0xEA,0x24,0x25,0x2A,0x32,0x01,0x01,0x00},
{0x00,0x00,0xFF,0x00,0xF8,0x01,0x49,0x4A,0x92,0x94,0x24,0x48,0x10,0x00,0x00,0x00},/*"修",24*/
{0x20,0x21,0x21,0x21,0x21,0x3F,0x02,0x0C,0x33,0xD0,0x10,0x10,0x1F,0x10,0x10,0x00},
{0x00,0xFE,0x04,0x08,0x08,0x10,0x01,0x02,0x84,0x68,0x10,0x68,0x84,0x02,0x01,0x00},/*"改",25*/
{0x00,0x31,0x22,0xAD,0x64,0x25,0x26,0x30,0x40,0x4F,0x58,0x6B,0x48,0x4F,0x40,0x00},
{0x08,0x10,0x3F,0x52,0x92,0x52,0x3F,0x10,0x01,0xF2,0x0C,0xF0,0x08,0xF4,0x03,0x00},/*"额",26*/
{0x08,0x30,0x22,0x22,0x22,0x22,0xA2,0x63,0x22,0x22,0x22,0x22,0x22,0x28,0x30,0x00},
{0x01,0x02,0x04,0x78,0x04,0x02,0x02,0xFE,0x22,0x22,0x22,0x22,0x22,0x02,0x02,0x00},/*"定",27*/
{0x00,0x00,0x1F,0x11,0x11,0x11,0x11,0xFF,0x11,0x11,0x11,0x11,0x1F,0x00,0x00,0x00},
{0x00,0x00,0xF8,0x10,0x10,0x10,0x10,0xFE,0x11,0x11,0x11,0x11,0xF9,0x01,0x0F,0x00},/*"电",28*/
{0x08,0x06,0x40,0x31,0x00,0x22,0x26,0x2A,0xB2,0x62,0x22,0x2A,0x26,0x23,0x20,0x00},
{0x20,0x20,0x7E,0x80,0x01,0x02,0x7C,0x00,0x00,0x7F,0x00,0x00,0x7E,0x01,0x07,0x00},/*"流",29*/
{0x08,0x08,0x08,0xFF,0x09,0x10,0x11,0x11,0xFF,0x00,0x00,0xFF,0x11,0x11,0x10,0x00},
{0x40,0x42,0x81,0xFE,0x00,0x10,0x10,0x10,0xFF,0x00,0x00,0xFF,0x10,0x10,0x10,0x00},/*"排",30*/
{0x48,0x57,0xF5,0x55,0x57,0xF0,0x5F,0x40,0x11,0x31,0xEA,0x24,0x2A,0x31,0x21,0x00},
{0x40,0x40,0x57,0x55,0x55,0xD5,0x55,0xD5,0x55,0x55,0x55,0x55,0x57,0x40,0x40,0x00},/*"警",31*/
{0x00,0x01,0x06,0x1F,0xE0,0x00,0x08,0xFF,0x08,0x08,0x08,0xFF,0x08,0x08,0x00,0x00},
{0x80,0x00,0x00,0xFF,0x01,0x42,0x44,0xD8,0x40,0x40,0x40,0xD0,0x4C,0x43,0x40,0x00},/*"供",32*/
{0x04,0x08,0x32,0xE2,0x2A,0x2A,0x2A,0x2A,0x2A,0x2A,0x2A,0x2B,0x20,0x20,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x0C,0x02,0x0F,0x00},/*"气",33*/
{0x20,0x20,0x20,0x20,0x2F,0x29,0xA9,0x69,0x29,0x29,0x2F,0x20,0x20,0x20,0x20,0x00},
{0x00,0x7F,0x40,0x40,0x5E,0x52,0x52,0x52,0x52,0x52,0x5E,0x40,0x41,0x7F,0x00,0x00},/*"高",34*/
{0x00,0x7F,0x44,0x5A,0x61,0x00,0x7F,0x49,0x49,0x49,0x49,0x49,0x7F,0x00,0x00,0x00},
{0x00,0xFF,0x20,0x10,0xE0,0x00,0xFF,0x02,0x04,0xC0,0x30,0x28,0x44,0x82,0x02,0x00},/*"限",35*/
{0x00,0x00,0x00,0x8F,0x48,0x28,0x08,0x08,0x08,0x28,0x48,0x8F,0x00,0x00,0x00,0x00},
{0x02,0x0C,0x00,0xC0,0x9C,0x82,0x82,0xA2,0x9A,0x82,0x82,0xCE,0x00,0x10,0x0C,0x00},/*"总",0*/
{0x00,0x04,0x08,0x17,0x24,0xE4,0x24,0x25,0x24,0x2C,0x34,0x07,0x00,0x00,0x00,0x00},
{0x00,0x01,0x01,0xF2,0x02,0x04,0x18,0xE0,0x08,0x08,0x04,0xF2,0x01,0x00,0x00,0x00},/*"负",1*/
{0x00,0x00,0x7F,0x40,0x42,0x42,0x42,0x42,0x5F,0x42,0x42,0x42,0x42,0x43,0x40,0x00},
{0x01,0x06,0xF8,0x01,0x02,0x04,0x18,0x60,0x80,0x00,0x02,0x01,0x02,0xFC,0x00,0x00},/*"历",2*/
{0x00,0x00,0x1F,0x11,0x11,0x11,0x11,0xFF,0x11,0x11,0x11,0x11,0x1F,0x00,0x00,0x00},
{0x01,0x01,0x81,0x22,0x12,0x0C,0x08,0xF4,0x04,0x02,0x02,0x02,0x81,0x01,0x01,0x00},/*"史",3*/
{0x08,0x08,0x08,0xFF,0x08,0x08,0x0A,0x04,0x1B,0xE8,0x08,0x08,0x0F,0x08,0x08,0x00},
{0x00,0xFE,0x84,0x84,0x84,0xFE,0x01,0x02,0x84,0x68,0x10,0x68,0x84,0x02,0x01,0x00},/*"故",4*/
{0x00,0x7F,0x40,0x44,0x5B,0x60,0x08,0x4B,0x6A,0x5A,0xCA,0x5A,0x6A,0x4B,0x08,0x00},
{0x00,0xFF,0x10,0x08,0x10,0xE0,0x08,0xE8,0xA8,0xA8,0xBF,0xA8,0xA8,0xE8,0x08,0x00},/*"障",5*/
{0x00,0x40,0x40,0x40,0x40,0x41,0x42,0x4F,0x70,0x42,0x41,0x40,0x40,0x40,0x00,0x00},
{0x08,0x10,0x20,0x40,0x80,0x00,0x00,0xFF,0x00,0x00,0x00,0x80,0x40,0x30,0x00,0x00},/*"不",6*/
{0x00,0x40,0x40,0x48,0x46,0x40,0x40,0x7F,0x40,0x40,0x42,0x4C,0x40,0x40,0x00,0x00},
{0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00},/*"平",7*/
{0x08,0x11,0x23,0xC4,0x10,0x2F,0xC9,0x4F,0x59,0x6F,0x00,0x02,0x22,0x23,0x22,0x00},
{0x80,0x00,0xFF,0x00,0x08,0xE9,0x2A,0xFC,0x2A,0xE9,0x08,0x02,0x01,0xFE,0x00,0x00},/*"衡",8*/
{0x00,0x3F,0x04,0x24,0x15,0xFF,0x15,0x24,0x00,0x3F,0x22,0x22,0x23,0x42,0x02,0x00},
{0x00,0xFC,0x44,0x84,0x04,0xF4,0x04,0xC5,0x06,0xF8,0x00,0x00,0xFF,0x00,0x00,0x00},/*"断",9*/
{0x08,0x08,0x08,0x0B,0xFF,0x09,0x08,0x00,0x7F,0x44,0x44,0x44,0x44,0x7F,0x00,0x00},
{0x10,0x20,0xC0,0x00,0xFF,0x00,0xC0,0x00,0xFF,0x42,0x42,0x42,0x42,0xFF,0x00,0x00},/*"相",10*/
{0x00,0x01,0x06,0x1F,0xE0,0x00,0x7C,0x44,0x44,0x47,0x44,0x44,0x7C,0x00,0x00,0x00},
{0x80,0x00,0x00,0xFF,0x04,0x88,0x90,0xA0,0xC0,0xFF,0xC0,0xA0,0x90,0x88,0x04,0x00},/*"保",11*/
{0x08,0x08,0x08,0xFF,0x08,0x09,0x00,0x1F,0x11,0x91,0x71,0x11,0x11,0x11,0x1F,0x00},
{0x20,0x22,0x41,0xFE,0x81,0x02,0x0C,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00},/*"护",12*/
{0x00,0x00,0x3E,0x02,0x02,0x02,0x02,0xFF,0x02,0x02,0x02,0x02,0x3F,0x00,0x00,0x00},
{0x00,0x3E,0x02,0x02,0x02,0x02,0x02,0xFE,0x02,0x02,0x02,0x02,0x02,0x3F,0x00,0x00},/*"出",13*/
{0x00,0x00,0x00,0x7F,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x7F,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0xFF,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0xFF,0x00,0x00,0x00,0x00},/*"日",14*/
{0x00,0x20,0xFF,0x24,0x24,0x24,0xFF,0x20,0x00,0x7F,0x44,0x44,0x44,0x7F,0x00,0x00},
{0x11,0x12,0xF4,0x90,0x90,0x98,0xF5,0x12,0x0C,0xF0,0x40,0x42,0x41,0xFE,0x00,0x00},/*"期",15*/
{0x01,0x01,0x01,0x7D,0x45,0x45,0x45,0x45,0x45,0x45,0x45,0x7D,0x01,0x01,0x01,0x00},
{0x00,0x00,0x00,0x60,0xA0,0x20,0x20,0x20,0x22,0x21,0x22,0x3C,0x00,0x00,0x00,0x00},/*"号",16*/
{0x02,0x3E,0x02,0xFE,0x12,0x12,0x02,0x4F,0x48,0x58,0x6B,0x48,0x48,0x4F,0x40,0x00},
{0x09,0x71,0x02,0xF2,0x04,0x78,0x01,0xF2,0x04,0x18,0xE0,0x08,0x04,0xF2,0x01,0x00},/*"频",17*/
{0x00,0x28,0x25,0x22,0x24,0x2C,0xB5,0x66,0x24,0x29,0x20,0x22,0x25,0x28,0x00,0x00},
{0x10,0x90,0x10,0x10,0x90,0x90,0x90,0xBF,0x90,0x90,0xD0,0x10,0x10,0x90,0x10,0x00},/*"率",18*/
{0x02,0x02,0x42,0x33,0x00,0x0A,0x72,0x13,0x12,0xFE,0x13,0x12,0x12,0x02,0x00,0x00},
{0x00,0x02,0x04,0xF8,0x04,0x0A,0x32,0xC2,0x02,0x02,0xF2,0x0A,0x0A,0x3A,0x02,0x00},/*"选",19*/
{0x08,0x08,0xFF,0x08,0x00,0x41,0x61,0x52,0x4A,0x45,0x4A,0x52,0x61,0x01,0x01,0x00},
{0x42,0x41,0xFE,0x80,0x00,0x08,0x48,0x48,0x48,0xFF,0x48,0x48,0x48,0x08,0x00,0x00},/*"择",20*/
{0x00,0x00,0x3F,0x20,0x20,0x20,0x28,0xA8,0x6A,0x29,0x2A,0x2C,0x28,0x20,0x20,0x00},
{0x02,0x0C,0xF0,0x00,0x80,0x80,0x80,0x82,0x81,0xFE,0x80,0x80,0x80,0xA0,0xC0,0x00},/*"序",21*/
{0x00,0x01,0x06,0x1F,0xE0,0x00,0x3F,0x21,0x21,0x21,0x7F,0x41,0xC1,0x41,0x01,0x00},
{0x80,0x00,0x00,0xFF,0x00,0x00,0xFF,0x02,0x04,0x00,0x82,0x71,0x0C,0x02,0x1F,0x00},/*"低",22*/
{0x02,0x02,0x42,0x33,0x00,0x10,0x12,0x11,0x10,0x10,0x10,0xFF,0x10,0x10,0x10,0x00},
{0x00,0x02,0x04,0xF8,0x04,0x02,0x02,0x82,0x02,0x12,0x0A,0xF2,0x02,0x02,0x02,0x00},/*"过",23*/
{0x00,0x00,0x01,0x02,0x0C,0xF0,0x10,0x10,0x10,0x13,0x1C,0x00,0x00,0x00,0x00,0x00},
{0x01,0x81,0x02,0x02,0x04,0x08,0x10,0x20,0xC0,0x30,0x08,0x04,0x02,0x01,0x01,0x00},/*"久",24*/
{0x00,0x01,0x06,0x1F,0xE0,0x00,0x20,0x24,0x24,0xA4,0x64,0x24,0x24,0x24,0x20,0x00},
{0x80,0x00,0x00,0xFF,0x00,0x00,0x00,0x9F,0x92,0x92,0x92,0x92,0x92,0x9F,0x00,0x00},/*"信",25*/
{0x08,0x08,0x0B,0xFF,0x09,0x08,0x04,0x44,0x44,0x44,0x47,0x44,0x44,0x44,0x04,0x00},
{0x20,0xC0,0x00,0xFF,0x00,0xC8,0x30,0xC0,0x02,0x01,0xFE,0x00,0x80,0x60,0x18,0x00},/*"标",26*/
{0x00,0x40,0x30,0x07,0x02,0x04,0x1F,0xF2,0x12,0x92,0x7F,0x12,0x12,0x12,0x10,0x00},
{0x20,0x20,0xFE,0x00,0x00,0x00,0xFF,0x44,0x44,0x44,0xFC,0x44,0x44,0x44,0x04,0x00},/*"准",27*/
{0x00,0x00,0x44,0x4C,0x54,0x65,0x45,0x46,0x84,0x88,0x90,0x81,0x80,0x00,0x00,0x00},
{0x00,0x42,0x44,0xC8,0xD0,0x42,0x41,0x7E,0x40,0x40,0x50,0x48,0xC4,0x62,0x00,0x00},/*"系",28*/
{0x20,0x21,0x21,0x3F,0x21,0x21,0x00,0x7F,0x40,0x40,0x4F,0x40,0x40,0x7F,0x00,0x00},
{0x04,0x06,0x04,0xF8,0x08,0x09,0x02,0xC4,0x18,0x60,0x80,0x7E,0x01,0xC1,0x07,0x00},/*"现",29*/
{0x08,0x30,0xA0,0xAA,0xAA,0xAA,0xA1,0xFE,0xA1,0xAA,0xAA,0xAA,0xA0,0x28,0x30,0x00},
{0x20,0x20,0x40,0x50,0x90,0x94,0x54,0x32,0x12,0x95,0x98,0x40,0x40,0x20,0x20,0x00},/*"零",30*/
{0x00,0x00,0x03,0x02,0x02,0x02,0xFE,0x12,0x12,0x12,0x12,0x13,0x10,0x10,0x00,0x00},
{0x01,0x02,0xEC,0x20,0x20,0x28,0x26,0x20,0x28,0x26,0x20,0xE0,0x08,0x07,0x00,0x00},/*"点",31*/
{0x00,0x00,0x00,0x07,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x04,0x02,0x01,0x00,0x00},
{0x10,0x20,0xC0,0x00,0x00,0x02,0x01,0xFE,0x00,0x00,0x00,0x00,0x00,0x80,0x70,0x00},/*"小",0*/
{0x00,0x00,0x00,0x7D,0x54,0x54,0x54,0x57,0x54,0x54,0x54,0x7C,0x00,0x00,0x00,0x00},
{0x00,0x22,0x42,0x92,0x92,0x92,0x92,0xFE,0x92,0x92,0x92,0x92,0x82,0x02,0x00,0x00},/*"星",0*/
{0x04,0x08,0x17,0x24,0xE4,0x24,0x24,0x27,0x24,0x2C,0x34,0x04,0x07,0x00,0x00,0x00},
{0x01,0x06,0xF8,0x90,0x90,0x90,0x90,0xFE,0x90,0x90,0x92,0x91,0xFE,0x00,0x00,0x00},/*"角",1*/
{0x00,0x20,0x20,0x2F,0x29,0x29,0x29,0xF9,0x29,0x29,0x29,0x2F,0x20,0x20,0x00,0x00},
{0x02,0x02,0x02,0xFE,0x52,0x52,0x52,0x52,0x52,0x52,0x52,0xFE,0x02,0x02,0x02,0x00},/*"直",0*/
{0x08,0x08,0x08,0xFF,0x08,0x0A,0x22,0x2A,0xA6,0x63,0x22,0x26,0x2A,0x22,0x02,0x00},
{0x20,0x22,0x41,0xFE,0x80,0x41,0x41,0x52,0x6A,0xC4,0x44,0x4A,0x72,0x41,0x40,0x00}/*"接",1*/
};

/* ASICC字库代码 8x16点阵 */
unsigned char code ASCIIchardot[16*96] = {
/*--  文字:     --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  !  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x0E,0x1F,0x1F,0x0E,0x00,0x00,0x00,0x00,0x00,0xB0,0xB0,0x00,0x00,0x00,

/*--  文字:  "  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x1C,0x1C,0x00,0x00,0x1C,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  #  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x04,0x1F,0x1F,0x04,0x1F,0x1F,0x04,0x00,0x40,0xF0,0xF0,0x40,0xF0,0xF0,0x40,

/*--  文字:  $  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x0C,0x1E,0x73,0x71,0x18,0x08,0x00,0x00,0x20,0x30,0x1C,0x9C,0xF0,0x60,0x00,

/*--  文字:  %  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x18,0x3C,0x24,0x3D,0x1B,0x06,0x0C,0x00,0x00,0x60,0xC0,0xB0,0x78,0x48,0x78,0x30,

/*--  文字:  &  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x0D,0x1F,0x12,0x1E,0x0C,0x00,0x00,0x00,0xE0,0xF0,0x10,0x90,0xE0,0xF0,0x90,

/*--  文字:  '  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x1C,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  (  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x03,0x0F,0x1C,0x10,0x00,0x00,0x00,0x00,0xE0,0xF8,0x1C,0x04,0x00,0x00,

/*--  文字:  )  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x10,0x1C,0x0F,0x03,0x00,0x00,0x00,0x00,0x04,0x1C,0xF8,0xE0,0x00,0x00,

/*--  文字:  *  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x01,0x05,0x07,0x03,0x07,0x05,0x01,0x00,0x00,0x40,0xC0,0x80,0xC0,0x40,0x00,

/*--  文字:  +  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x01,0x01,0x07,0x07,0x01,0x01,0x00,0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,

/*--  文字:  ,  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x34,0x3C,0x38,0x00,0x00,

/*--  文字:  -  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  .  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x30,0x00,0x00,

/*--  文字:  /  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x01,0x07,0x1E,0x18,0x00,0x00,0x18,0x78,0xE0,0x80,0x00,0x00,0x00,

/*--  文字:  0  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x0F,0x1F,0x10,0x16,0x1F,0x0F,0x00,0x00,0xE0,0xF0,0xD0,0x10,0xF0,0xE0,

/*--  文字:  1  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x04,0x04,0x0C,0x1F,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0,0x00,0x00,

/*--  文字:  2  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x0C,0x1C,0x10,0x11,0x1F,0x0E,0x00,0x00,0x30,0x70,0xD0,0x90,0x10,0x10,0x00,

/*--  文字:  3  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x0C,0x1C,0x11,0x11,0x1F,0x0E,0x00,0x00,0x60,0x70,0x10,0x10,0xF0,0xE0,0x00,

/*--  文字:  4  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x1F,0x1F,0x00,0x07,0x07,0x00,0x00,0xC0,0xC0,0x40,0x40,0xF0,0xF0,0x40,

/*--  文字:  5  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x1F,0x1F,0x11,0x11,0x11,0x10,0x00,0x00,0x10,0x10,0x10,0x30,0xE0,0xC0,0x00,

/*--  文字:  6  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x03,0x07,0x1E,0x1A,0x13,0x01,0x00,0x00,0xE0,0xF0,0x10,0x10,0xF0,0xE0,0x00,

/*--  文字:  7  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x10,0x10,0x11,0x17,0x1E,0x18,0x00,0x00,0x00,0x70,0xF0,0x80,0x00,0x00,0x00,

/*--  文字:  8  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x0E,0x1F,0x13,0x11,0x1F,0x0E,0x00,0x00,0xE0,0xF0,0x10,0x90,0xF0,0xE0,0x00,

/*--  文字:  9  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x0F,0x1F,0x10,0x10,0x1F,0x0F,0x00,0x00,0x00,0x90,0xB0,0xF0,0xC0,0x80,0x00,

/*--  文字:  :  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x06,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x30,0x00,0x00,

/*--  文字:  ;  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x06,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x34,0x3C,0x38,0x00,0x00,

/*--  文字:  <  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x01,0x03,0x06,0x0C,0x18,0x10,0x00,0x00,0x00,0x80,0xC0,0x60,0x30,0x10,0x00,

/*--  文字:  =  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,

/*--  文字:  >  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x10,0x18,0x0C,0x06,0x03,0x01,0x00,0x00,0x10,0x30,0x60,0xC0,0x80,0x00,0x00,

/*--  文字:  ?  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x0C,0x1C,0x11,0x13,0x1E,0x0C,0x00,0x00,0x00,0x00,0xB0,0xB0,0x00,0x00,0x00,

/*--  文字:  @  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x0F,0x1F,0x10,0x11,0x13,0x12,0x1F,0x0F,0xE0,0xF0,0x10,0x90,0xD0,0x50,0xD0,0xD0,

/*--  文字:  A  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x07,0x0F,0x18,0x18,0x0F,0x07,0x00,0x00,0xF0,0xF0,0x80,0x80,0xF0,0xF0,0x00,

/*--  文字:  B  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x1F,0x1F,0x11,0x11,0x1F,0x0E,0x00,0x00,0xF0,0xF0,0x10,0x10,0xF0,0xE0,0x00,

/*--  文字:  C  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x0F,0x1F,0x10,0x10,0x1C,0x0C,0x00,0x00,0xE0,0xF0,0x10,0x10,0x70,0x60,0x00,

/*--  文字:  D  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x1F,0x1F,0x10,0x18,0x0F,0x07,0x00,0x00,0xF0,0xF0,0x10,0x30,0xE0,0xC0,0x00,

/*--  文字:  E  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x1F,0x1F,0x11,0x11,0x11,0x10,0x00,0x00,0xF0,0xF0,0x10,0x10,0x10,0x10,0x00,

/*--  文字:  F  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x1F,0x1F,0x11,0x11,0x11,0x10,0x00,0x00,0xF0,0xF0,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  G  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x0F,0x1F,0x10,0x10,0x1C,0x0C,0x00,0x00,0xE0,0xF0,0x10,0x90,0xF0,0xF0,0x00,

/*--  文字:  H  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x1F,0x1F,0x01,0x01,0x1F,0x1F,0x00,0x00,0xF0,0xF0,0x00,0x00,0xF0,0xF0,0x00,

/*--  文字:  I  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x10,0x1F,0x1F,0x10,0x00,0x00,0x00,0x00,0x10,0xF0,0xF0,0x10,0x00,0x00,

/*--  文字:  J  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x00,0x00,0x60,0x70,0x10,0x10,0xF0,0xE0,0x00,

/*--  文字:  K  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x1F,0x1F,0x01,0x07,0x1E,0x18,0x00,0x00,0xF0,0xF0,0x00,0xC0,0xF0,0x30,0x00,

/*--  文字:  L  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x1F,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0,0x10,0x10,0x10,0x10,0x00,

/*--  文字:  M  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x1F,0x1F,0x04,0x03,0x04,0x1F,0x1F,0x00,0xF0,0xF0,0x00,0x80,0x00,0xF0,0xF0,

/*--  文字:  N  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x1F,0x1F,0x06,0x03,0x01,0x1F,0x1F,0x00,0xF0,0xF0,0x00,0x00,0x80,0xF0,0xF0,

/*--  文字:  O  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x0F,0x1F,0x10,0x10,0x1F,0x0F,0x00,0x00,0xE0,0xF0,0x10,0x10,0xF0,0xE0,0x00,

/*--  文字:  P  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x1F,0x1F,0x11,0x11,0x1F,0x0E,0x00,0x00,0xF0,0xF0,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  Q  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x0F,0x1F,0x10,0x10,0x1F,0x0F,0x00,0x00,0xE0,0xF0,0x10,0x18,0xFC,0xE4,0x00,

/*--  文字:  R  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x1F,0x1F,0x11,0x11,0x1F,0x0E,0x00,0x00,0xF0,0xF0,0x00,0x80,0xF0,0x70,0x00,

/*--  文字:  S  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x0C,0x1E,0x13,0x11,0x18,0x08,0x00,0x00,0x20,0x30,0x10,0x90,0xF0,0x60,0x00,

/*--  文字:  T  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x10,0x10,0x1F,0x1F,0x10,0x10,0x00,0x00,0x00,0x00,0xF0,0xF0,0x00,0x00,0x00,

/*--  文字:  U  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x1F,0x1F,0x00,0x00,0x1F,0x1F,0x00,0x00,0xE0,0xF0,0x10,0x10,0xF0,0xE0,0x00,

/*--  文字:  V  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x1F,0x1F,0x00,0x00,0x1F,0x1F,0x00,0x00,0xC0,0xE0,0x30,0x30,0xE0,0xC0,0x00,

/*--  文字:  W  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x1F,0x1F,0x00,0x03,0x00,0x1F,0x1F,0x00,0x80,0xF0,0x70,0x80,0x70,0xF0,0x80,

/*--  文字:  X  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x18,0x1C,0x07,0x03,0x1C,0x18,0x00,0x00,0x70,0xF0,0x00,0x80,0xF0,0x70,0x00,

/*--  文字:  Y  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x1E,0x1F,0x01,0x01,0x1F,0x1E,0x00,0x00,0x00,0x00,0xF0,0xF0,0x00,0x00,0x00,

/*--  文字:  Z  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x10,0x10,0x11,0x13,0x1E,0x1C,0x00,0x00,0x70,0xF0,0x90,0x10,0x10,0x10,0x00,

/*--  文字:  [  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x1F,0x1F,0x10,0x10,0x00,0x00,0x00,0x00,0xFE,0xFE,0x02,0x02,0x00,0x00,

/*--  文字:  \  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x18,0x1E,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xE0,0x78,0x18,0x00,

/*--  文字:  ]  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x10,0x10,0x1F,0x1F,0x00,0x00,0x00,0x00,0x02,0x02,0xFE,0xFE,0x00,0x00,

/*--  文字:  ^  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x10,0x30,0x60,0x60,0x30,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  _  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,

/*--  文字:  `  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x40,0x60,0x70,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  a  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x04,0x04,0x04,0x07,0x03,0x00,0x00,0x60,0xF0,0x90,0x90,0xF0,0xF0,0x00,

/*--  文字:  b  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x1F,0x1F,0x04,0x04,0x07,0x03,0x00,0x00,0xF0,0xF0,0x10,0x10,0xF0,0xE0,0x00,

/*--  文字:  c  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x03,0x07,0x04,0x04,0x06,0x02,0x00,0x00,0xE0,0xF0,0x10,0x10,0x30,0x20,0x00,

/*--  文字:  d  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x03,0x07,0x04,0x04,0x1F,0x1F,0x00,0x00,0xE0,0xF0,0x10,0x10,0xF0,0xF0,0x00,

/*--  文字:  e  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x03,0x07,0x04,0x04,0x07,0x03,0x00,0x00,0xE0,0xF0,0x90,0x90,0x90,0x80,0x00,

/*--  文字:  f  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x01,0x0F,0x1F,0x11,0x11,0x11,0x00,0x00,0x00,0xF0,0xF0,0x00,0x00,0x00,0x00,

/*--  文字:  g  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x03,0x07,0x04,0x04,0x07,0x07,0x00,0x00,0xE2,0xF2,0x12,0x12,0xFE,0xFC,0x00,

/*--  文字:  h  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x1F,0x1F,0x04,0x04,0x07,0x03,0x00,0x00,0xF0,0xF0,0x00,0x00,0xF0,0xF0,0x00,

/*--  文字:  i  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x04,0x04,0x37,0x37,0x00,0x00,0x00,0x00,0x10,0x10,0xF0,0xF0,0x10,0x10,0x00,

/*--  文字:  j  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x04,0x04,0x37,0x37,0x00,0x00,0x00,0x02,0x02,0x02,0xFE,0xFC,0x00,0x00,

/*--  文字:  k  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x1F,0x1F,0x00,0x01,0x07,0x06,0x00,0x00,0xF0,0xF0,0x80,0xC0,0x70,0x30,0x00,

/*--  文字:  l  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x10,0x10,0x1F,0x1F,0x00,0x00,0x00,0x00,0x10,0x10,0xF0,0xF0,0x10,0x10,0x00,

/*--  文字:  m  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x07,0x07,0x04,0x07,0x04,0x07,0x03,0x00,0xF0,0xF0,0x00,0xE0,0x00,0xF0,0xF0,

/*--  文字:  n  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x07,0x07,0x04,0x04,0x07,0x03,0x00,0x00,0xF0,0xF0,0x00,0x00,0xF0,0xF0,0x00,

/*--  文字:  o  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x03,0x07,0x04,0x04,0x07,0x03,0x00,0x00,0xE0,0xF0,0x10,0x10,0xF0,0xE0,0x00,

/*--  文字:  p  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x07,0x07,0x04,0x04,0x07,0x03,0x00,0x00,0xFE,0xFE,0x10,0x10,0xF0,0xE0,0x00,

/*--  文字:  q  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x03,0x07,0x04,0x04,0x07,0x07,0x00,0x00,0xE0,0xF0,0x10,0x10,0xFE,0xFE,0x00,

/*--  文字:  r  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x07,0x07,0x01,0x02,0x06,0x06,0x00,0x00,0xF0,0xF0,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  s  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x03,0x07,0x04,0x04,0x04,0x04,0x00,0x00,0x10,0x90,0x90,0x90,0xF0,0x60,0x00,

/*--  文字:  t  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x04,0x1F,0x1F,0x04,0x04,0x04,0x00,0x00,0x00,0xE0,0xF0,0x10,0x10,0x10,0x00,

/*--  文字:  u  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x07,0x07,0x00,0x00,0x07,0x07,0x00,0x00,0xE0,0xF0,0x10,0x10,0xF0,0xF0,0x00,

/*--  文字:  v  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x07,0x07,0x00,0x00,0x07,0x07,0x00,0x00,0xC0,0xE0,0x30,0x30,0xE0,0xC0,0x00,

/*--  文字:  w  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x07,0x07,0x00,0x03,0x00,0x07,0x07,0x00,0xC0,0xF0,0x30,0xC0,0x30,0xF0,0xC0,

/*--  文字:  x  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x06,0x07,0x01,0x01,0x07,0x06,0x00,0x00,0x30,0x70,0xC0,0xC0,0x70,0x30,0x00,

/*--  文字:  y  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x07,0x07,0x00,0x00,0x07,0x07,0x00,0x02,0xE2,0xF2,0x16,0x1C,0xF8,0xE0,0x00,

/*--  文字:  z  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x04,0x04,0x04,0x05,0x07,0x06,0x00,0x00,0x30,0x70,0xD0,0x90,0x10,0x10,0x00,

/*--  文字:  {  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x01,0x0F,0x1E,0x10,0x00,0x00,0x00,0x80,0xC0,0x78,0x3C,0x04,0x00,0x00,

/*--  文字:  |  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x1F,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xFE,0x00,0x00,0x00,

/*--  文字:  }  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x10,0x1E,0x0F,0x01,0x00,0x00,0x00,0x00,0x04,0x3C,0x78,0xC0,0x80,0x00,

/*--  文字:  ~  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x0C,0x18,0x10,0x18,0x0C,0x04,0x0C,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:    --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x00,0x00,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0x00
};


#endif