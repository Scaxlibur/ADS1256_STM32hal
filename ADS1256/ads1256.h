#ifndef __ADS1256_H__
#define __ADS1256_H__

#include "main.h"
#include "spi.h"
#include "gpio.h"


typedef enum{
    ADS1256_CMD_WAKEUP   =  0x00, 
    ADS1256_CMD_RDATA    =  0x01, 
    ADS1256_CMD_RDATAC   =  0x03, 
    ADS1256_CMD_SDATAC   =  0x0f, 
    ADS1256_CMD_RREG     =  0x10, 
    ADS1256_CMD_WREG     =  0x50, 
    ADS1256_CMD_SELFCAL  =  0xf0,
    ADS1256_CMD_SELFOCAL =  0xf1, 
    ADS1256_CMD_SELFGCAL =  0xf2,
    ADS1256_CMD_SYSOCAL  =  0xf3, 
    ADS1256_CMD_SYSGCAL  =  0xf4, 
    ADS1256_CMD_SYNC     =  0xfc, 
    ADS1256_CMD_STANDBY  =  0xfd, 
    ADS1256_CMD_REST     =  0xfe, 
}ADS_1256_CMD_t;

typedef enum{// define 多路复用 p为正通道，n为负通道
    ADS1256_MUXP_AIN0   =  0x00, 
    ADS1256_MUXP_AIN1   =  0x10, 
    ADS1256_MUXP_AIN2   =  0x20,
    ADS1256_MUXP_AIN3   =  0x30, 
    ADS1256_MUXP_AIN4   =  0x40, 
    ADS1256_MUXP_AIN5   =  0x50, 
    ADS1256_MUXP_AIN6   =  0x60, 
    ADS1256_MUXP_AIN7   =  0x70, 
    ADS1256_MUXP_AINCOM  = 0x80,
}ADS1256_MUXP_t;

typedef enum{// define 多路复用 p为正通道，n为负通道
    ADS1256_MUXN_AIN0 =  0x00, 
    ADS1256_MUXN_AIN1 =  0x01, 
    ADS1256_MUXN_AIN2 =  0x02, 
    ADS1256_MUXN_AIN3 =  0x03, 
    ADS1256_MUXN_AIN4 =  0x04, 
    ADS1256_MUXN_AIN5 =  0x05, 
    ADS1256_MUXN_AIN6 =  0x06, 
    ADS1256_MUXN_AIN7 =  0x07, 
    ADS1256_MUXN_AINCOM  = 0x08, 
}ADS1256_MUXN_t;

typedef enum{// define gain codes 
    ADS1256_GAIN_1   =   0x00, 
    ADS1256_GAIN_2   =   0x01, 
    ADS1256_GAIN_4   =   0x02, 
    ADS1256_GAIN_8   =   0x03, 
    ADS1256_GAIN_16  =   0x04, 
    ADS1256_GAIN_32  =   0x05, 
    ADS1256_GAIN_64   =  0x06, 
}ADS1256_GAIN_t;

typedef enum{//define drate codes 
    ADS1256_DRATE_30000SPS = 0xF0, 
    ADS1256_DRATE_15000SPS = 0xE0, 
    ADS1256_DRATE_7500SPS =  0xD0,
    ADS1256_DRATE_3750SPS =  0xC0, 
    ADS1256_DRATE_2000SPS =  0xB0, 
    ADS1256_DRATE_1000SPS =  0xA1, 
    ADS1256_DRATE_500SPS  =  0x92, 
    ADS1256_DRATE_100SPS  =  0x82, 
    ADS1256_DRATE_60SPS   =  0x72, 
    ADS1256_DRATE_50SPS   =  0x63, 
    ADS1256_DRATE_30SPS   =  0x53, 
    ADS1256_DRATE_25SPS   =  0x43, 
    ADS1256_DRATE_15SPS   =  0x33, 
    ADS1256_DRATE_10SPS   =  0x23, 
    ADS1256_DRATE_5SPS    =  0x13, 
    ADS1256_DRATE_2_5SPS  =  0x03,
}ADS1256_DRATE_t;

#define ADS1256_STATUS      0x00  
#define ADS1256_MUX         0x01   
#define ADS1256_ADCON       0x02   // A/D控制寄存器
#define ADS1256_DRATE       0x03   // A/D读取速率
#define ADS1256_IO          0x04   
#define ADS1256_OFC0        0x05   
#define ADS1256_OFC1        0x06   
#define ADS1256_OFC2        0x07   
#define ADS1256_FSC0        0x08   
#define ADS1256_FSC1        0x09   
#define ADS1256_FSC2        0x0A

#define CS_0()				HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin,GPIO_PIN_RESET);
#define CS_1()				HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin,GPIO_PIN_SET);
#define ADS1256_DRDY  		(DRDY_GPIO_Port->IDR & DRDY_Pin) //DRDY引脚，
#define ADS1256_MUXN_AINCOM 0x08

void ADS1256WREG(uint8_t regaddr,uint8_t databyte);

void ADS1256_Init(void);

uint32_t ADS1256ReadData(uint8_t channel);

#endif