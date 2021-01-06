/*
 * mpu6050.c
 *
 *  Created on: Jan 2, 2021
 *      Author: mint
 */

#include "stm32f1xx_hal.h"
#include "mpu6050.h"
#include <stdio.h>
#include <string.h>

#define MPU6050_I2C_ADDRESS		0x68U

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;

static void writeRegister(uint8_t, uint8_t);
static void readRegister(uint8_t, uint8_t *);

/**
  * @brief Read MPU6050 accelerometer, gyro and temp data
  * @param me: pointer to an IMUDataStruct
  * @retval None
  */
void MPU6050Read(IMUDataStruct * const me)
{
	uint8_t  Ax_l = 0;
	uint8_t  Ax_h = 0;
	uint8_t  Ay_l = 0;
	uint8_t  Ay_h = 0;
	uint8_t  Az_l = 0;
	uint8_t  Az_h = 0;
	uint8_t  T_l = 0;
	uint8_t  T_h = 0;
	uint8_t  Gx_l = 0;
	uint8_t  Gx_h = 0;
	uint8_t  Gy_l = 0;
	uint8_t  Gy_h = 0;
	uint8_t  Gz_l = 0;
	uint8_t  Gz_h = 0;

	readRegister(ACCEL_XOUT_H, &Ax_h);
	readRegister(ACCEL_XOUT_L, &Ax_l);
	me->Ax = Ax_h<<8 | Ax_l;

	readRegister(ACCEL_YOUT_H, &Ay_h);
	readRegister(ACCEL_YOUT_L, &Ay_l);
	me->Ay = Ay_h<<8 | Ay_l;

	readRegister(ACCEL_ZOUT_H, &Az_h);
	readRegister(ACCEL_ZOUT_L, &Az_l);
	me->Az = Az_h<<8 | Az_l;

	readRegister(TEMP_OUT_H, &T_h);
	readRegister(TEMP_OUT_L, &T_l);
	me->tRaw = T_h<<8 | T_l;
	getTempC(me);

	readRegister(GYRO_XOUT_H, &Gx_h);
	readRegister(GYRO_XOUT_L, &Gx_l);
	me->Gx = Gx_h<<8 | Gx_l;

	readRegister(GYRO_YOUT_H, &Gy_h);
	readRegister(GYRO_YOUT_L, &Gy_l);
	me->Gy = Gy_h<<8 | Gy_l;

	readRegister(GYRO_ZOUT_H, &Gz_h);
	readRegister(GYRO_ZOUT_L, &Gz_l);
	me->Gz = Gz_h<<8 | Gz_l;

}

/**
  * @brief Print the contents of the IMUDataStruct to UART
  * @param me: pointer to an IMUDataStruct
  * @retval None
  */
void monitorData(IMUDataStruct * const me)
{
	uint8_t buffer[35] = {'\0'};

	sprintf((char *)buffer, "ID = 0x%02x    ", me->whoAmI);
	HAL_UART_Transmit(&huart1, buffer, sizeof(buffer), 100);

	sprintf((char *)buffer,"Ax = %d    ", me->Ax);
	HAL_UART_Transmit(&huart1, buffer, sizeof(buffer), 100);

	sprintf((char *)buffer,"Ay = %d    ", me->Ay);
	HAL_UART_Transmit(&huart1, buffer, sizeof(buffer), 100);

	sprintf((char *)buffer,"Az = %d    ", me->Az);
	HAL_UART_Transmit(&huart1, buffer, sizeof(buffer), 100);

	sprintf((char *)buffer,"T = %.0f   ", me->tC);
	HAL_UART_Transmit(&huart1, buffer, sizeof(buffer), 100);

	sprintf((char *)buffer,"Gx = %d    ", me->Gx);
	HAL_UART_Transmit(&huart1, buffer, sizeof(buffer), 100);

	sprintf((char *)buffer,"Gy = %d    ", me->Gy);
	HAL_UART_Transmit(&huart1, buffer, sizeof(buffer), 100);

	sprintf((char *)buffer,"Gz = %d\r\n", me->Gz);
	HAL_UART_Transmit(&huart1, buffer, sizeof(buffer), 100);

}

/**
  * @brief Initialize an MPU6050
  * @param me: pointer to an IMUDataStruct
  * @retval None
  */
void mpu6050Setup(IMUDataStruct * const me)
{
	// Power-Up Delay of 100ms
	HAL_Delay(100);

	// Set sample rate divider to 1kHz
	writeRegister(SMPLRT_DIV, DLPF_ENABLE);

	// Set the power mode and clock source
	writeRegister(PWR_MGMT_1, PLL_XREF);

	// Set the Digital Low Pass Filter
	writeRegister(CONFIG, 0x06);

	// Configure the Accelerometer
	writeRegister(ACCEL_CONFIG, FULL_SCALE_2g);

	// Configure the Gyroscope
	writeRegister(GYRO_CONFIG, FULL_SCALE_2k);

	// Enable Interrupts
	writeRegister(INT_ENABLE, DISABLE_INT);

	// Check WHO AM I Register
	readRegister(WHO_AM_I, &(me->whoAmI));
}

/**
  * @brief Returns the IMU temperature in degrees C
  * @param me: pointer to an IMUDataStruct
  * @retval None
  */
void getTempC(IMUDataStruct * const me)
{
	me->tC = (float)me->tRaw/ 340.0 + 36.53;
}

/**
  * @brief Writes a single register from the MPU6050IMU
  * @param _register: The register to write to
  * @param  data: the value to be written
  * @retval None
  */
static void writeRegister(uint8_t _register, uint8_t data)
{
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_I2C_ADDRESS << 1, _register, 1U, &data, 1U, 100U);
}

/**
  * @brief Reads a single register from the MPU6050IMU
  * @param _register: The register to read from
  * @param  data: pointer to a variable for the data
  * @retval None
  */
static void readRegister(uint8_t _register, uint8_t *data)
{
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_I2C_ADDRESS << 1, _register, 1, data, 1U, 1000);
}
