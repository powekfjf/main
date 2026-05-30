#include "MPU6050.H"

void I2C_Reste(I2C_HandleTypeDef *hi2c)
{
     // 1. 关外设时钟
    if (hi2c->Instance == I2C1)
    {
        __HAL_I2C_DISABLE(&hi2c1); // 关外设
        __HAL_RCC_I2C1_CLK_DISABLE();
        // 强制复位 + 释放
        __HAL_RCC_I2C1_FORCE_RESET();
        HAL_Delay(1);
        __HAL_RCC_I2C1_RELEASE_RESET();
        // 再开时钟
        __HAL_RCC_I2C1_CLK_ENABLE();
        MX_I2C1_Init();
    }
    if (hi2c->Instance == I2C2)
    {
        __HAL_I2C_DISABLE(&hi2c2); // 关外设
        __HAL_RCC_I2C2_CLK_DISABLE();//关外设时钟
        __HAL_RCC_I2C2_FORCE_RESET();//强制复位
        HAL_Delay(1);
        __HAL_RCC_I2C2_RELEASE_RESET();//释放复位
        __HAL_RCC_I2C2_CLK_ENABLE();//再开时钟
        MX_I2C2_Init();
    }
}

void MPU6050_WriteMem(uint8_t reg, uint8_t data)
{
    uint8_t buff=data;
    HAL_I2C_Mem_Write(&hi2c2,MPU6050_IDW,reg,1,&buff,1,500);
}

void MPU6050_Init(void)
{
    MX_I2C2_Init();
    HAL_Delay(10);
    MPU6050_WriteMem(MPU6050_PWR_MGMT_1,0x01);//唤醒，时钟源选择为PLL
    MPU6050_WriteMem(MPU6050_PWR_MGMT_2,0x00);//加速度/陀螺仪使能
    MPU6050_WriteMem(MPU6050_SMPLRT_DIV,0x00);//采样率分频：采样频率 = 时钟 / (分频值+1)
    MPU6050_WriteMem(MPU6050_CONFIG,0x03);//设置陀螺仪的低通滤波器
    MPU6050_WriteMem(MPU6050_GYRO_CONFIG,0x18);//设置陀螺仪的增益
    MPU6050_WriteMem(MPU6050_ACCEL_CONFIG,0x18);//设置加速度的增益
    //MPU6050_WriteMem(MPU6050_USER_CTRL,0x47);//使能用户寄存器
    MPU6050_WriteMem(MPU6050_FIFO_EN,0xF8);//使能主数据寄存器
}

float MPU6050_ReadData(int16_t *Ac_X_Y_Z, int16_t *Gy_X_Y_Z)
{
    uint8_t data[14]={0};
    if(HAL_I2C_Mem_Read(&hi2c2,MPU6050_IDR,MPU6050_ACCEL_XOUT_H,1,data,14,500)!=HAL_OK)
    {
        I2C_Reste(&hi2c2); // 复位
        return 0.0f;
    }
    Ac_X_Y_Z[0]=data[0]<<8|data[1];
    Ac_X_Y_Z[1]=data[2]<<8|data[3];
    Ac_X_Y_Z[2]=data[4]<<8|data[5];
    Gy_X_Y_Z[0]=data[8]<<8|data[9];
    Gy_X_Y_Z[1]=data[10]<<8|data[11];
    Gy_X_Y_Z[2]=data[12]<<8|data[13];
    return ((float)(data[6]<<8|data[7])/340.0f+36.53);
}


