#ifndef __OLED_DEFINE_H
#define __OLED_DEFINE_H

typedef enum Direction_e
{
    Direction_Up = 0,
    Direction_Down,
    Direction_Left,
    Direction_Right
}Direction_e;

#define OLED_Write_ID 0x78//设备ID写操作
#define OLED_Read_ID 0x7A//设备ID读操作
#define OLED_Continuous_Write_Command 0x00//连续传输命令
#define OLED_Continuous_Write_Data 0x40//连续传输存储在GDDRM中的数据字节

/********************* 0.96寸OLED(SSD1306) 命令宏定义 *********************/
// 1. 基础显示控制命令
#define OLED_CMD_DISPLAY_OFF         0xAE  // 关闭显示(休眠)
#define OLED_CMD_DISPLAY_ON          0xAF  // 开启显示(正常工作)

// 2. 寻址模式设置命令
#define OLED_CMD_SET_MEMORY_MODE     0x20  // 设置内存寻址模式
#define OLED_CMD_ADDR_PAGE           0x02  // 页寻址模式(默认)
#define OLED_CMD_ADDR_VERTICAL       0x01  // 垂直寻址模式
#define OLED_CMD_ADDR_HORIZONTAL     0x00  // 水平寻址模式

// 3. 列地址设置 (水平/垂直寻址模式用)
#define OLED_CMD_SET_COLUMN_ADDR     0x21  // 设置列起始/结束地址
// 4. 页地址设置 (水平/垂直寻址模式用)
#define OLED_CMD_SET_PAGE_ADDR       0x22  // 设置页起始/结束地址

// 4. 硬件显示方向控制
#define OLED_CMD_SET_SEG_REMAP0      0xA0  // 列地址0映射SEG0(默认)
#define OLED_CMD_SET_SEG_REMAP1      0xA1  // 列地址127映射SEG0(左右翻转)
#define OLED_CMD_SET_SCAN_DIR_NORMAL 0xC0  // 正常扫描方向(默认)
#define OLED_CMD_SET_SCAN_DIR_REV    0xC8  // 反向扫描(上下翻转)

// 5. 显示起始行与偏移设置
#define OLED_CMD_SET_DISPLAY_START   0x40  // 设置显示起始行(0~63, 0x40=第0行)
#define OLED_CMD_SET_DISPLAY_OFFSET  0xD3  // 设置显示偏移
#define OLED_CMD_SET_NO_OFFSET       0x00  // 无偏移(默认)

// 6. 时钟与分频设置
#define OLED_CMD_SET_CLOCK_DIV       0xD5  // 设置时钟分频&震荡频率
#define OLED_CMD_CLOCK_DEFAULT       0x80  // 默认配置(推荐)

// 7. 多路复用率设置
#define OLED_CMD_SET_MUX_RATIO       0xA8  // 设置多路复用率
#define OLED_CMD_MUX_64              0x3F  // 0.96寸OLED(64行高度)专用

// 8. 电荷泵设置 (OLED必须开启,否则不亮)
#define OLED_CMD_SET_CHARGE_PUMP     0x8D  // 电荷泵设置命令
#define OLED_CMD_CHARGE_PUMP_ON      0x14  // 开启电荷泵(核心)
#define OLED_CMD_CHARGE_PUMP_OFF     0x10  // 关闭电荷泵

// 9. 对比度设置
#define OLED_CMD_SET_CONTRAST        0x81  // 设置对比度
#define OLED_CMD_CONTRAST_MAX        0xFF  // 最大对比度
#define OLED_CMD_CONTRAST_MID        0x7F  // 中等对比度
#define OLED_CMD_CONTRAST_MIN        0x00  // 最小对比度

// 10. 普通/反色显示
#define OLED_CMD_NORMAL_DISPLAY      0xA6  // 正常显示(0灭1亮)
#define OLED_CMD_INVERSE_DISPLAY     0xA7  // 反色显示(0亮1灭)

// 11. 屏幕刷新/亮度调节
#define OLED_CMD_SET_PRE_CHARGE      0xD9  // 设置预充电周期
#define OLED_CMD_PRE_CHARGE_DEFAULT  0xF1  // 默认周期
#define OLED_CMD_SET_VCOMH           0xDB  // 设置VCOMH取消电平
#define OLED_CMD_VCOMH_DEFAULT       0x30  // 默认配置

// 水平左右滚动
#define OLED_HORIZONTAL_RIGHT_SCROLL    0x26  // 向右水平滚动
#define OLED_HORIZONTAL_LEFT_SCROLL     0x27  // 向左水平滚动

// 垂直+水平混合滚动
#define OLED_VERTICAL_RIGHT_SCROLL      0x29  // 垂直+向右滚动
#define OLED_VERTICAL_LEFT_SCROLL       0x2A  // 垂直+向左滚动

// 滚动控制命令
#define OLED_ACTIVATE_SCROLL            0x2F  // 启动滚动
#define OLED_DEACTIVATE_SCROLL          0x2E  // 停止滚动
#define OLED_SET_VERTICAL_SCROLL_AREA   0xA3  // 设置垂直滚动区域

// 滚动速度参数（常用）
#define OLED_SCROLL_SPEED_5_FRAMES      0x00
#define OLED_SCROLL_SPEED_64_FRAMES     0x01
#define OLED_SCROLL_SPEED_128_FRAMES    0x02
#define OLED_SCROLL_SPEED_256_FRAMES    0x03

// 12. 页寻址模式专用命令 (常用)
#define OLED_CMD_SET_PAGE_START      0xB0  // 页起始地址(0xB0~0xB7, 共8页)
#define OLED_CMD_SET_COLUMN_HIGH     0x10  // 设置列地址高4位
#define OLED_CMD_SET_COLUMN_LOW      0x00  // 设置列地址低4位

// 7. COM引脚硬件配置 (你要的 0xDA！核心命令！)
#define OLED_CMD_SET_COM_PIN         0xDA  // 设置COM引脚硬件配置
#define OLED_CMD_COM_PIN_RESET       0x12  // 0.96寸OLED标准配置(必须用这个

// 2. 显示模式（你要的 0xA4！）
#define OLED_CMD_NORMAL_DISPLAY_RAM  0xA4  // 按GDDRAM显示（默认/必用）
#define OLED_CMD_ENTIRE_DISPLAY_ON   0xA5  // 全屏全亮（测试）

#endif // 

