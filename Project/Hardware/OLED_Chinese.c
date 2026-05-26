#include "OLED_includeall.h"
#include "OLED_Chinese.h"

extern void OLED_I2C_Continuous_Write_CommandAndDat(uint8_t *buff,uint16_t count);
extern uint8_t OLED_Set_Display_Coordinates(uint8_t y,uint8_t x);

void OLED_Show_Chinese(uint8_t y,uint8_t x,uint8_t *ch,uint8_t len)
{
    uint8_t i;
    uint8_t buff[17]={OLED_Continuous_Write_Data};
    for(;len>0;len--)
    {
        for(i=1;i<17;i++)
        {
            buff[i]=OLED_Chinese16x16[ch[len-1]][i];
        }
        OLED_Set_Display_Coordinates((y-1)*2,(x+len-2)*16);
        OLED_I2C_Continuous_Write_CommandAndDat(buff,17);
        for(i=1;i<17;i++)
        {
            buff[i]=OLED_Chinese16x16[ch[len-1]][i+16];
        }
        OLED_Set_Display_Coordinates((y-1)*2+1,(x+len-2)*16);
        OLED_I2C_Continuous_Write_CommandAndDat(buff,17);
    }
}