#include "OLED_includeall.h"
#include "OLED_Font.h"
/**
  * @brief  硬件层I2C连续写命令和数据函数        
  * @note          
  * @param  buf要写入的数据缓冲区
  * @param  count要写入的数据长度
  * @retval None
**/
void OLED_I2C_Continuous_Write_CommandAndDat(uint8_t *buff,uint16_t count)
{
    HAL_I2C_Master_Transmit(&hi2c1,OLED_Write_ID,buff,count,1000);
}

/**
  * @brief  OLED屏幕设置显示坐标函数        
  * @param  y显示行数
  * @param  x显示列数
  * @retval 1成功，0失败
**/
uint8_t OLED_Set_Display_Coordinates(uint8_t y,uint8_t x)
{
    if(y>7||x>127) return 0;
    uint8_t buff[]={OLED_Continuous_Write_Command,OLED_CMD_SET_PAGE_START|y,OLED_CMD_SET_COLUMN_LOW|(x&0x0F),OLED_CMD_SET_COLUMN_HIGH|(x>>4)};
    OLED_I2C_Continuous_Write_CommandAndDat(buff,sizeof(buff));
    return 1;
}

/**
  * @brief  OLED清空屏幕函数       
  * @param  None
  * @retval None
**/
void OLED_ClearAll(void)
{
    uint8_t i;
    uint8_t buff[129]={OLED_Continuous_Write_Data};
    memset(buff+1,0,sizeof(buff)-1);
    for(i=0;i<=7;i++)
    {
        OLED_Set_Display_Coordinates(i,0);
        OLED_I2C_Continuous_Write_CommandAndDat(buff,sizeof(buff));
    }
}

/**
  * @brief  OLED清除指定行函数        
  * @param  line要清除的行号
  * @retval None
**/
void OLED_ClearLine(uint8_t line)
{
    if(!OLED_Set_Display_Coordinates((line-1)*2,0)) return;
    uint8_t buff[129]={OLED_Continuous_Write_Data};
    memset(buff+1,0,sizeof(buff)-1);
    OLED_I2C_Continuous_Write_CommandAndDat(buff,sizeof(buff));
    OLED_Set_Display_Coordinates((line-1)*2+1,0);
    OLED_I2C_Continuous_Write_CommandAndDat(buff,sizeof(buff));
}

/**
  * @brief  按指定坐标指定反向清除函数        
  * @param  y行坐标
  * @param  x列坐标
  * @param  Direction清除方向
  *             @arg    Direction_Up
  *             @arg    Direction_Down
  *             @arg    Direction_Left
  *             @arg    Direction_Right
  * @retval None
**/
void OLED_ClearCoordinates(uint8_t y,uint8_t x,Direction_e Direction)
{
    uint8_t i;
    if(Direction==Direction_Up)
    {
        uint8_t buff[9]={OLED_Continuous_Write_Data};
        memset(buff+1,0,sizeof(buff)-1);
        for(i=(y-1)*2+1;i<=7;i--)
        {
            OLED_Set_Display_Coordinates(i,(x-1)*8);
            OLED_I2C_Continuous_Write_CommandAndDat(buff,sizeof(buff));
        }
    }
    else if(Direction==Direction_Down)
    {
        uint8_t buff[9]={OLED_Continuous_Write_Data};
        memset(buff+1,0,sizeof(buff)-1);
        for(i=(y-1)*2;i<=7;i++)
        {
            OLED_Set_Display_Coordinates(i,(x-1)*8);
            OLED_I2C_Continuous_Write_CommandAndDat(buff,sizeof(buff));
        }
    }
    else if(Direction==Direction_Left)
    {
        if(x==16)
        {
            OLED_ClearLine(y);
            return;
        }
        uint8_t buff[129]={OLED_Continuous_Write_Data};
        memset(buff+1,0,sizeof(buff)-1);
        OLED_Set_Display_Coordinates((y-1)*2,0);
        OLED_I2C_Continuous_Write_CommandAndDat(buff,x*8+1);
        OLED_Set_Display_Coordinates((y-1)*2+1,0);
        OLED_I2C_Continuous_Write_CommandAndDat(buff,x*8+1);
    }
    else if(Direction==Direction_Right)
    {
        if(x==1)
        {
            OLED_ClearLine(y);
            return;
        }
        uint8_t buff[129]={OLED_Continuous_Write_Data};
        memset(buff+1,0,sizeof(buff)-1);
        OLED_Set_Display_Coordinates((y-1)*2,(x-1)*8);
        OLED_I2C_Continuous_Write_CommandAndDat(buff,137-x*8);
        OLED_Set_Display_Coordinates((y-1)*2+1,(x-1)*8);
        OLED_I2C_Continuous_Write_CommandAndDat(buff,137-x*8);
    }
}

/**
  * @brief  计算x的y次方函数       
  * @param  x底数
  * @param  y指数
  * @retval x的y次方
**/
uint32_t xPowy(uint8_t x,uint8_t y)
{
    if(y==0) return 1;
    uint32_t rset;
    for(rset=1;y>0;y--)
    {
        rset*=x;
    }
    return rset;
}

/**
  * @brief  OLED显示字符函数        
  * @param  y显示行数
  * @param  x显示列数
  * @param  chr显示字符
  * @retval None
**/  
void OLED_ShowChar(uint8_t y,uint8_t x,char chr)
{
    if(!OLED_Set_Display_Coordinates((y-1)*2,(x-1)*8)) return;
    uint8_t i;
    uint8_t buff[9]={OLED_Continuous_Write_Data};
    for(i=1;i<=8;i++)
    {
        buff[i]=OLED_F8x16[chr-' '][i-1];
    }
    OLED_I2C_Continuous_Write_CommandAndDat(buff,sizeof(buff));

    for(i=1;i<=8;i++)
    {
        buff[i]=OLED_F8x16[chr-' '][i+7];
    }
    OLED_Set_Display_Coordinates((y-1)*2+1,(x-1)*8);
    OLED_I2C_Continuous_Write_CommandAndDat(buff,sizeof(buff));
}

/**
  * @brief  OLED显示字符串函数        
  * @param  y显示行数
  * @param  x显示列数
  * @param  chr显示字符串
  * @retval None
**/
void OLED_Show_String(uint8_t y,uint8_t x,char *chr)
{ 
    uint8_t i;
    for(i=0;chr[i]!='\0';i++)
    {
        OLED_ShowChar(y,x+i,chr[i]);
    }
}

/**
  * @brief  OLED显示数字函数        
  * @param  y显示行数
  * @param  x显示列数
  * @param  num显示数字
  * @param  len显示数字长度
  * @retval None
**/
void OLED_Show_Num(uint8_t y,uint8_t x,uint32_t num,uint8_t len)
{
    if(len>10) len=10;
    for(uint64_t rest=10;len>0;len--)
    {
        OLED_ShowChar(y,x+(len-1),((num%rest)/(rest/10))+'0');
        rest*=10;
    }
}

/**
  * @brief  OLED显示16进制数字函数        
  * @param  y显示行数
  * @param  x显示列数
  * @param  num显示数字
  * @param  len显示数字长度
  * @retval None
**/
void OLDE_Show_HexNum(uint8_t y,uint8_t x,uint32_t num,uint8_t len)
{
    uint8_t i;
    if(len>9) len=9;
    OLED_Show_String(y,x,"0x");
    for(i=0;len>0;len--)
    {
        i=num&0x0F;
        num>>=4;
        if(i<10) OLED_Show_Num(y,x+1+len,i,1);
        else OLED_ShowChar(y,x+1+len,i+'A'-10);
    }
}


/**
  * @brief  OLED初始化函数        
  * @param  None
  * @retval None
**/
void OLED_Init(void)
{
    //uint8_t i;
    uint8_t OLED_Init_t[]=
    {
        OLED_Continuous_Write_Command,//连续传输命令
        OLED_CMD_DISPLAY_OFF,//关闭显示
        OLED_DEACTIVATE_SCROLL,//停止滚动
        OLED_CMD_SET_CLOCK_DIV,OLED_CMD_CLOCK_DEFAULT,//设置时钟分频比（0x80）
        OLED_CMD_SET_MUX_RATIO,OLED_CMD_MUX_64,//设置复用率（0x3F）
        OLED_CMD_SET_MEMORY_MODE,OLED_CMD_ADDR_PAGE,//设置内存模式（0x02）页寻址模式(默认)
        //OLED_CMD_SET_MEMORY_MODE,OLED_CMD_ADDR_HORIZONTAL,//设置内存模式（0x00）水平寻址模式
        //OLED_CMD_SET_MEMORY_MODE,OLED_CMD_ADDR_VERTICAL,//设置内存模式（0x01）垂直寻址模式
        OLED_CMD_SET_DISPLAY_OFFSET,OLED_CMD_SET_NO_OFFSET,//设置显示偏移(0x00)
        OLED_CMD_SET_DISPLAY_START,//设置显示起始行
        OLED_CMD_SET_SEG_REMAP1,//设置列地址映射
        OLED_CMD_SET_SCAN_DIR_REV,//设置COM扫描方向,反向扫描(上下翻转)
        //OLED_CMD_SET_SCAN_DIR_NORMAL,//设置COM扫描方向,正常扫描方向(默认)
        OLED_CMD_SET_COM_PIN,OLED_CMD_COM_PIN_RESET,//设置COM引脚硬件配置(0x12)
        OLED_CMD_SET_CONTRAST,OLED_CMD_CONTRAST_MAX,//设置对比度（0xFF）
        OLED_CMD_SET_PRE_CHARGE,OLED_CMD_PRE_CHARGE_DEFAULT,//设置预充电周期（0xF1）
        OLED_CMD_SET_VCOMH,OLED_CMD_VCOMH_DEFAULT,//设置VCOMH取消选择电平（0x30）
        OLED_CMD_NORMAL_DISPLAY_RAM,//按GDDRAM显示（默认/必用）
        //OLED_CMD_INVERSE_DISPLAY,//设置显示模式（反色）
        OLED_CMD_NORMAL_DISPLAY,//设置显示模式（正常）
        OLED_CMD_SET_CHARGE_PUMP,OLED_CMD_CHARGE_PUMP_ON,//设置电荷泵（必须开）
        //OLED_CMD_ENTIRE_DISPLAY_ON,// 全屏全亮（测试）
        OLED_CMD_DISPLAY_ON//开启显示
    };
    HAL_Delay(1);
    MX_DMA_Init();
    MX_I2C1_Init();
    HAL_Delay(1);
    OLED_I2C_Continuous_Write_CommandAndDat(OLED_Init_t,sizeof(OLED_Init_t));
    OLED_ClearAll();
}


void OLED_Scroll_Left_ENABLE(void)
{
    uint8_t OLED_Scroll_Left_ENABLE_t[]=
    {
        OLED_Continuous_Write_Command,
        OLED_ACTIVATE_SCROLL,
        OLED_HORIZONTAL_LEFT_SCROLL,
        0x00,
        0x00,
        0x00,
        0x07,
    };
    OLED_I2C_Continuous_Write_CommandAndDat(OLED_Scroll_Left_ENABLE_t,sizeof(OLED_Scroll_Left_ENABLE_t));
}

void OLED_Scroll_Left_DISABLE(void)
{
    uint8_t OLED_Scroll_Left_DISABLE_t[]=
    {
        OLED_Continuous_Write_Command,
        OLED_DEACTIVATE_SCROLL,
    };
    OLED_I2C_Continuous_Write_CommandAndDat(OLED_Scroll_Left_DISABLE_t,sizeof(OLED_Scroll_Left_DISABLE_t));
}

void OLED_Reverse(uint16_t time)
{
    uint8_t OLED_Reverse_t[]={OLED_Continuous_Write_Command,OLED_CMD_INVERSE_DISPLAY};
    OLED_I2C_Continuous_Write_CommandAndDat(OLED_Reverse_t,sizeof(OLED_Reverse_t));
    HAL_Delay(time);
    OLED_Reverse_t[1]=OLED_CMD_NORMAL_DISPLAY;
    OLED_I2C_Continuous_Write_CommandAndDat(OLED_Reverse_t,sizeof(OLED_Reverse_t));
    HAL_Delay(time);
}