#ifndef __MPU6050_H__
#define __MPU6050_H__

#include "main.h"
#include "I2C.H"

#define MPU6050_IDW 0xD0
#define MPU6050_IDR 0xD1

//=============================================
// ********** 1. 配置与控制寄存器 **********
//=============================================
#define MPU6050_PWR_MGMT_1        0x6B  // 电源管理1：唤醒、时钟源选择
#define MPU6050_PWR_MGMT_2        0x6C  // 电源管理2：加速度/陀螺仪低功耗模式

#define MPU6050_SMPLRT_DIV        0x19  // 采样率分频：采样频率 = 时钟 / (分频值+1)
#define MPU6050_CONFIG            0x1A  // 配置寄存器：低通滤波(DLPF)设置
#define MPU6050_GYRO_CONFIG       0x1B  // 陀螺仪配置：量程选择
#define MPU6050_ACCEL_CONFIG      0x1C  // 加速度计配置：量程选择

//=============================================
// ********** 2. 加速度计寄存器 **********
//=============================================
#define MPU6050_ACCEL_XOUT_H      0x3B  // 加速度X轴 高8位
#define MPU6050_ACCEL_XOUT_L      0x3C  // 加速度X轴 低8位

#define MPU6050_ACCEL_YOUT_H      0x3D  // 加速度Y轴 高8位
#define MPU6050_ACCEL_YOUT_L      0x3E  // 加速度Y轴 低8位

#define MPU6050_ACCEL_ZOUT_H      0x3F  // 加速度Z轴 高8位
#define MPU6050_ACCEL_ZOUT_L      0x40  // 加速度Z轴 低8位

//=============================================
// ********** 3. 温度传感器寄存器 **********
//=============================================
#define MPU6050_TEMP_OUT_H        0x41  // 温度 高8位
#define MPU6050_TEMP_OUT_L        0x42  // 温度 低8位

//=============================================
// ********** 4. 陀螺仪寄存器 **********
//=============================================
#define MPU6050_GYRO_XOUT_H       0x43  // 陀螺仪X轴 高8位
#define MPU6050_GYRO_XOUT_L       0x44  // 陀螺仪X轴 低8位

#define MPU6050_GYRO_YOUT_H       0x45  // 陀螺仪Y轴 高8位
#define MPU6050_GYRO_YOUT_L       0x46  // 陀螺仪Y轴 低8位

#define MPU6050_GYRO_ZOUT_H       0x47  // 陀螺仪Z轴 高8位
#define MPU6050_GYRO_ZOUT_L       0x48  // 陀螺仪Z轴 低8位

//=============================================
// ********** 5. I2C 从机 / FIFO / 中断 **********
//=============================================
#define MPU6050_INT_PIN_CFG       0x37  // 中断引脚配置
#define MPU6050_INT_ENABLE        0x38  // 中断使能
#define MPU6050_INT_STATUS        0x3A  // 中断状态

#define MPU6050_USER_CTRL         0x6A  // 用户控制：FIFO、I2C主模式使能
#define MPU6050_FIFO_EN           0x23  // FIFO 使能
#define MPU6050_FIFO_COUNT_H      0x72  // FIFO 计数 高8位
#define MPU6050_FIFO_COUNT_L      0x73  // FIFO 计数 低8位
#define MPU6050_FIFO_R_W          0x74  // FIFO 数据读写

//=============================================
// ********** 6. WHO_AM_I 身份ID **********
//=============================================
#define MPU6050_WHO_AM_I          0x75  // 芯片ID寄存器，默认值=0x68（用于校验通信）

void MPU6050_Init(void);
void I2C_Reste(I2C_HandleTypeDef *hi2c);
float MPU6050_ReadData(int16_t *Ac_X_Y_Z, int16_t *Gy_X_Y_Z);

#endif // !__MPU6050_H__

