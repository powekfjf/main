#ifndef __OLED_H
#define __OLED_H

#include "OLED_Define.h"

void OLED_Init(void);
void OLED_ClearAll(void);
void OLED_ClearLine(uint8_t line);
void OLED_Show_Love16x16(uint8_t y,uint8_t x);
void OLED_Show_Love32x32(uint8_t y,uint8_t x);
void OLED_ShowChar(uint8_t y,uint8_t x,char chr);
void OLED_Show_String(uint8_t y,uint8_t x,char *chr);
void OLED_Show_Num(uint8_t y,uint8_t x,uint32_t num,uint8_t len);
void OLED_Show_Chinese(uint8_t y,uint8_t x,uint8_t *ch,uint8_t len);
void OLDE_Show_HexNum(uint8_t y,uint8_t x,uint32_t num,uint8_t len);
void OLED_ClearCoordinates(uint8_t y,uint8_t x,Direction_e Direction);


void OLED_Scroll_Left_ENABLE(void);
void OLED_Scroll_Left_DISABLE(void);
void OLED_Reverse(uint16_t time);

#endif /* __OLED_H */
