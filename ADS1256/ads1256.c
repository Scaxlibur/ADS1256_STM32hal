#include "ads1256.h"

uint8_t wreg = 0x50;
uint8_t regnumber = 0x00;
uint8_t IO = 0x00;

uint8_t data1=0;
uint8_t data2=0;
uint8_t data3=0;

uint8_t ADS1256_CMD_WAKEUP   =  0x00; 
uint8_t ADS1256_CMD_RDATA    =  0x01; 
uint8_t ADS1256_CMD_RDATAC   =  0x03; 
uint8_t ADS1256_CMD_SDATAC   =  0x0f; 
uint8_t ADS1256_CMD_RREG     =  0x10; 
uint8_t ADS1256_CMD_WREG     =  0x50; 
uint8_t ADS1256_CMD_SELFCAL  =  0xf0;
uint8_t ADS1256_CMD_SELFOCAL =  0xf1; 
uint8_t ADS1256_CMD_SELFGCAL =  0xf2 ;
uint8_t ADS1256_CMD_SYSOCAL  =  0xf3; 
uint8_t ADS1256_CMD_SYSGCAL  =  0xf4; 
uint8_t ADS1256_CMD_SYNC     =  0xfc; 
uint8_t ADS1256_CMD_STANDBY  =  0xfd; 
uint8_t ADS1256_CMD_REST     =  0xfe; 


// define the ADS1256寄存器值
uint8_t ADS1256_STATUS   =    0x00;   
uint8_t ADS1256_MUX      =    0x01;   
uint8_t ADS1256_ADCON    =    0x02;   // A/D控制寄存器
uint8_t ADS1256_DRATE    =    0x03;   // A/D读取速率
uint8_t ADS1256_IO       =    0x04;   
uint8_t ADS1256_OFC0     =    0x05;   
uint8_t ADS1256_OFC1     =    0x06;   
uint8_t ADS1256_OFC2     =    0x07;   
uint8_t ADS1256_FSC0     =    0x08;   
uint8_t ADS1256_FSC1     =    0x09;   
uint8_t ADS1256_FSC2     =    0x0A;
 
 
 // define 多路复用 p为正通道，n为负通道
uint8_t ADS1256_MUXP_AIN0   =  0x00; 
uint8_t ADS1256_MUXP_AIN1   =  0x10; 
uint8_t ADS1256_MUXP_AIN2   =  0x20;
uint8_t ADS1256_MUXP_AIN3   =  0x30; 
uint8_t ADS1256_MUXP_AIN4   =  0x40; 
uint8_t ADS1256_MUXP_AIN5   =  0x50; 
uint8_t ADS1256_MUXP_AIN6   =  0x60; 
uint8_t ADS1256_MUXP_AIN7   =  0x70; 
uint8_t ADS1256_MUXP_AINCOM  = 0x80; 
 
uint8_t ADS1256_MUXN_AIN0 =  0x00; 
uint8_t ADS1256_MUXN_AIN1 =  0x01; 
uint8_t ADS1256_MUXN_AIN2 =  0x02; 
uint8_t ADS1256_MUXN_AIN3 =  0x03; 
uint8_t ADS1256_MUXN_AIN4 =  0x04; 
uint8_t ADS1256_MUXN_AIN5 =  0x05; 
uint8_t ADS1256_MUXN_AIN6 =  0x06; 
uint8_t ADS1256_MUXN_AIN7 =  0x07; 
// uint8_t ADS1256_MUXN_AINCOM  = 0x08;   

 
 
// define gain codes 
uint8_t ADS1256_GAIN_1   =   0x00; 
uint8_t ADS1256_GAIN_2   =   0x01; 
uint8_t ADS1256_GAIN_4   =   0x02; 
uint8_t ADS1256_GAIN_8   =   0x03; 
uint8_t ADS1256_GAIN_16  =   0x04; 
uint8_t ADS1256_GAIN_32  =   0x05; 
uint8_t ADS1256_GAIN_64   =  0x06; 
//#define ADS1256_GAIN_64    0x07 
 
//define drate codes 
uint8_t ADS1256_DRATE_30000SPS = 0xF0; 
uint8_t ADS1256_DRATE_15000SPS = 0xE0; 
uint8_t ADS1256_DRATE_7500SPS =  0xD0 ;
uint8_t ADS1256_DRATE_3750SPS =  0xC0; 
uint8_t ADS1256_DRATE_2000SPS =  0xB0; 
uint8_t ADS1256_DRATE_1000SPS =  0xA1; 
uint8_t ADS1256_DRATE_500SPS  =  0x92; 
uint8_t ADS1256_DRATE_100SPS  =  0x82; 
uint8_t ADS1256_DRATE_60SPS   =  0x72; 
uint8_t ADS1256_DRATE_50SPS   =  0x63; 
uint8_t ADS1256_DRATE_30SPS   =  0x53; 
uint8_t ADS1256_DRATE_25SPS   =  0x43; 
uint8_t ADS1256_DRATE_15SPS   =  0x33; 
uint8_t ADS1256_DRATE_10SPS   =  0x23; 
uint8_t ADS1256_DRATE_5SPS    =  0x13; 
uint8_t ADS1256_DRATE_2_5SPS  =  0x03;

void ADS1256WREG(uint8_t regaddr,uint8_t databyte)
{
  wreg += (regaddr & 0x0F);    
	//确保前四位为0101，同时后四位为regaddr的值
	
	CS_0();
	while(ADS1256_DRDY);
	
  HAL_SPI_Transmit(&hspi1,(uint8_t*)&wreg,1,100);
	//写入寄存器值时，第一个命令为 0101rrrr,第二个为 0000nnnn
	//同时注意n为需要写入的寄存器减一，写入一个寄存器，所以写入的为0x00
  //printf("%d\r\n",(uint8_t*)(ADS1256_CMD_WREG | (regaddr & 0x0F)));
	 //写入一个寄存器
  HAL_SPI_Transmit(&hspi1,(uint8_t*)&regnumber,1,100);
 
  HAL_SPI_Transmit(&hspi1,(uint8_t*)&databyte,1,100);
	CS_1();
	wreg = 0x50;
}

void ADS1256_Init(void)
{
	//初始化过程参考手册
  while(ADS1256_DRDY);
	CS_0();
	HAL_SPI_Transmit(&hspi1,(uint8_t *)&ADS1256_CMD_SELFCAL,1,100);
	while(ADS1256_DRDY);
	CS_1();
	//**********************************

	ADS1256WREG(ADS1256_STATUS,0x06);               // 启用自校准和模拟输入缓冲区
	// ADS1256WREG(ADS1256_STATUS,0x04);               //
	// ADS1256WREG(ADS1256_MUX,0x08);                  //
	ADS1256WREG(ADS1256_ADCON,ADS1256_GAIN_1);        // 0x00,PGA为1
	ADS1256WREG(ADS1256_DRATE,ADS1256_DRATE_10SPS);  // 10k采样率
	ADS1256WREG(ADS1256_IO,IO);               
	while(ADS1256_DRDY);
	CS_0();
	HAL_SPI_Transmit(&hspi1,(uint8_t *)&ADS1256_CMD_SELFCAL,1,100);
	while(ADS1256_DRDY);
	CS_1(); 
	//**********************************
}

uint32_t ADS1256ReadData(uint8_t channel)  
{
	uint32_t sum=0;
	//uint8_t rdata[3];
	while(ADS1256_DRDY);//
	ADS1256WREG(ADS1256_MUX,channel);
	CS_0();
	//读数据前依次写入SYNC、WAKEUP、RDATA
	HAL_SPI_Transmit(&hspi1,(uint8_t *)&ADS1256_CMD_SYNC,1,100);
	HAL_SPI_Transmit(&hspi1,(uint8_t *)&ADS1256_CMD_WAKEUP,1,100);	               
	HAL_SPI_Transmit(&hspi1,(uint8_t *)&ADS1256_CMD_RDATA,1,100);
	//接收数据依次存入data中
  HAL_SPI_TransmitReceive(&hspi1,(uint8_t *)0xff,(uint8_t *)&data1,1,100);
	HAL_SPI_TransmitReceive(&hspi1,(uint8_t *)0xff,(uint8_t *)&data2,1,100);
	HAL_SPI_TransmitReceive(&hspi1,(uint8_t *)0xff,(uint8_t *)&data3,1,100);
	sum |= (data1 <<16);
	sum |= (data2 <<8);
	sum |= data3;
	CS_1();

	if (sum>0x7FFFFF)           // if MSB=1, 
	{
		sum -= 0x1000000;       // do 2's complement

	}
    return sum;
}