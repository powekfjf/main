#include "My_picture.h"
void My_picture1(void)
{
    OLED_ClearAll();
    
    uint8_t i;
    uint8_t OLED_Chinese_t[]={16,20,19};//我爱你
    uint8_t OLED_Chinese_t2[]={21,22,21,23};//一生一世
    OLED_Show_String(1,1,"5 2 0    1 3 1 4");
    OLED_Show_Chinese(4,1,OLED_Chinese_t,sizeof(OLED_Chinese_t));
    OLED_Show_Chinese(4,5,OLED_Chinese_t2,sizeof(OLED_Chinese_t2));
    for(i=1;i<=2;i++)
    {
        OLED_Show_Love16x16(2,i);
        OLED_Show_Love16x16(3,i);
    }
    OLED_Show_Love32x32(2,2);
    OLED_Show_Love32x32(2,3);
    for(i=7;i<=8;i++)
    {
        OLED_Show_Love16x16(2,i);
        OLED_Show_Love16x16(3,i);
    }
}

void My_picture2(void)
{
    OLED_ClearAll();
    uint8_t i,j;
    for(i=1;i<=4;i++)
    {
        for(j=1;j<=8;j++)
        {
            OLED_Show_Love16x16(i,j);
        }
    }
}

void My_picture3(void)
{
    OLED_ClearAll();
    uint8_t i,j;
    for(i=1;i<=4;i++)
    {
        if(i%2)
        {
            for(j=1;j<=8;j++)
            {
                OLED_Show_Love16x16(i,j);
                HAL_Delay(100);
            }
        }
        else
        {
            for(j=8;j>=1;j--)
            {
                OLED_Show_Love16x16(i,j);
                HAL_Delay(100);
            }
        }
    }
}

void My_picture4(void)
{
    OLED_ClearAll();
    OLED_Show_String(1,4,"I love you");
    OLED_Show_String(2,4,"A lifetime");
    OLED_Show_String(3,4,"Never part");
    OLED_Show_String(4,2,"always for you");
}

void My_picture5(void)
{
    OLED_ClearAll();
    uint8_t buff_chian[]={0,1,2,3,4,5,6,7};//江西环境工程职业
    uint8_t buff_chian2[]={8,9,10,11,12,24,25};//学院钟宝飞制作
    uint8_t buff_chian3[]={26,27,28};//π电子
    OLED_Show_Chinese(1,1,buff_chian,sizeof(buff_chian));
    OLED_Show_Chinese(2,1,buff_chian2,sizeof(buff_chian2));
    OLED_Show_String(3,3,"Zhong");
    OLED_Show_Chinese(3,4,buff_chian3,sizeof(buff_chian3));
}