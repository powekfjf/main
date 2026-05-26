#include "OLED_includeall.h"
#include "OLED_Image.h"

extern void OLED_I2C_Continuous_Write_CommandAndDat(uint8_t *buff,uint16_t count);
extern uint8_t OLED_Set_Display_Coordinates(uint8_t y,uint8_t x);

void OLED_Show_Love16x16(uint8_t y,uint8_t x)
{
    uint8_t i;
    uint8_t buff_temp[17]={OLED_Continuous_Write_Data};
    for(i=1;i<16;i++)
    {
        buff_temp[i]=OLED_Lmagh16x16[0][i];
    }
    OLED_Set_Display_Coordinates((y-1)*2,(x-1)*16);
    OLED_I2C_Continuous_Write_CommandAndDat(buff_temp,sizeof(buff_temp));
    
    for(i=1;i<16;i++)
    {
        buff_temp[i]=OLED_Lmagh16x16[0][i+16];
    }
    OLED_Set_Display_Coordinates((y-1)*2+1,(x-1)*16);
    OLED_I2C_Continuous_Write_CommandAndDat(buff_temp,sizeof(buff_temp));
}

void OLED_Show_Love32x32(uint8_t y,uint8_t x)
{
    uint8_t buff[33]={OLED_Continuous_Write_Data};
    uint8_t i;
    OLED_Set_Display_Coordinates((y-1)*2,(x-1)*32);
    for(i=1;i<32;i++)
    {
        buff[i]=OLED_Lmagh32x32[0][i];
    }
    OLED_I2C_Continuous_Write_CommandAndDat(buff,sizeof(buff));
    OLED_Set_Display_Coordinates((y-1)*2+1,(x-1)*32);
    for(i=1;i<32;i++)
    {
        buff[i]=OLED_Lmagh32x32[0][i+32];
    }
    OLED_I2C_Continuous_Write_CommandAndDat(buff,sizeof(buff));
    OLED_Set_Display_Coordinates((y-1)*2+2,(x-1)*32);
    for(i=1;i<32;i++)
    {
        buff[i]=OLED_Lmagh32x32[0][i+64];
    }
    OLED_I2C_Continuous_Write_CommandAndDat(buff,sizeof(buff));
    OLED_Set_Display_Coordinates((y-1)*2+3,(x-1)*32);
    for(i=1;i<32;i++)
    {
        buff[i]=OLED_Lmagh32x32[0][i+96];
    }
    OLED_I2C_Continuous_Write_CommandAndDat(buff,sizeof(buff));
}
