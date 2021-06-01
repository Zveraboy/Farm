/* USER CODE BEGIN Header */
//hello world
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

#define OLED_adress 0x78
#define OLED_SETCONTRAST 0x81
#define OLED_DISPLAYALLON_RESUME 0xA4
#define OLED_DISPLAYALLON 0xA5
#define OLED_NORMALDISPLAY 0xA6
#define OLED_INVERTDISPLAY 0xA7
#define OLED_DISPLAYOFF 0xAE
#define OLED_DISPLAYON 0xAF
#define OLED_SETDISPLAYOFFSET 0xD3
#define OLED_SETCOMPINS 0xDA
#define OLED_SETVCOMDETECT 0xDB
#define OLED_SETDISPLAYCLOCKDIV 0xD5
#define OLED_SETPRECHARGE 0xD9
#define OLED_SETMULTIPLEX 0xA8
#define OLED_SETLOWCOLUMN 0x00
#define OLED_SETHIGHCOLUMN 0x10
#define OLED_SETSTARTLINE 0x40
#define OLED_MEMORYMODE 0x20
#define OLED_COLUMNADDR 0x21
#define OLED_PAGEADDR   0x22
#define OLED_COMSCANINC 0xC0
#define OLED_COMSCANDEC 0xC8
#define OLED_SEGREMAP 0xA0
#define OLED_CHARGEPUMP 0x8D
#define OLED_SWITCHCAPVCC 0x2
#define OLED_NOP 0xE3

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_BUFFERSIZE (OLED_WIDTH*OLED_HEIGHT)/8
#define OLED_DEFAULT_SPACE 0

#define COMAND 0x00 // ������ �������� ������� (0�00) � ���� �������
#define DATA   0x40 //������ �������� ������(0�40) � ���� �������

RTC_TimeTypeDef sTime = {0};
RTC_DateTypeDef DateToUpdate = {0};

char trans_str[64] = {0,};
//char A = 'A', z = 'z', CyrA = '�', CyrB = '�', Cyrya = '�';

int32_t prevCounter = 0;

uint8_t temp[2] = {0,0};
uint8_t temp_char[9] = {0,0,0,0,0,0,0,0,0,};
unsigned char LCD_X,LCD_Y;
unsigned char LCD_Buffer[] =
{
////////////////////////��������� �������, ���� ������� ��������� � ������? ������ �� ���� ��� ������ �� ����� ������� ���� �������� �� ������/////////////////////////////////


							/*	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,*/


//////////////////// ��������� ����� ////////////////////////////// � 112 �� 207 ������������, �������� ������
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char
						        0x00, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char !
						        0x00, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00,  // Code for char "
						        0xE8, 0x3C, 0x2B, 0xE8, 0x3C, 0x2B, 0x00, 0x00,  // Code for char #
						        0x46, 0x89, 0xFF, 0x91, 0x62, 0x00, 0x00, 0x00,  // Code for char $
						        0x06, 0x89, 0x46, 0x20, 0x18, 0x04, 0x62, 0x91,  // Code for char %
						        0x70, 0x90, 0x8E, 0xB9, 0x45, 0xA3, 0x98, 0x48,  // Code for char &
						        0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char '
						        0xFC, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char (
						        0x01, 0x02, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char )
						        0x0A, 0x04, 0x1F, 0x04, 0x0A, 0x00, 0x00, 0x00,  // Code for char *
						        0x10, 0x10, 0x7C, 0x10, 0x10, 0x00, 0x00, 0x00,  // Code for char +
						        0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char ,
						        0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char -
						        0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char .
						        0xC0, 0x3C, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char /
						        0x7E, 0x81, 0x81, 0x81, 0x7E, 0x00, 0x00, 0x00,  // Code for char 0
						        0x00, 0x81, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00,  // Code for char 1
						        0x82, 0xC1, 0xA1, 0x91, 0xCE, 0x00, 0x00, 0x00,  // Code for char 2
						        0x82, 0x81, 0x89, 0x89, 0x76, 0x00, 0x00, 0x00,  // Code for char 3
						        0x30, 0x2C, 0x22, 0xFF, 0x20, 0x00, 0x00, 0x00,  // Code for char 4
						        0x80, 0x86, 0x85, 0x89, 0x71, 0x00, 0x00, 0x00,  // Code for char 5
						        0x78, 0x96, 0x8A, 0x89, 0x71, 0x00, 0x00, 0x00,  // Code for char 6
						        0x02, 0x01, 0xC1, 0x39, 0x07, 0x00, 0x00, 0x00,  // Code for char 7
						        0x66, 0x99, 0x89, 0x99, 0x66, 0x00, 0x00, 0x00,  // Code for char 8
						        0x8E, 0x91, 0x51, 0x71, 0x1E, 0x00, 0x00, 0x00,  // Code for char 9
						        0x00, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char :
						        0x00, 0x88, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char ;
						        0x10, 0x28, 0x28, 0x28, 0x44, 0x00, 0x00, 0x00,  // Code for char <
						        0x28, 0x28, 0x28, 0x28, 0x28, 0x00, 0x00, 0x00,  // Code for char =
						        0x44, 0x28, 0x28, 0x28, 0x10, 0x00, 0x00, 0x00,  // Code for char >
						        0x02, 0xB1, 0x09, 0x06, 0x00, 0x00, 0x00, 0x00,  // Code for char ?
						        0xF8, 0x04, 0x72, 0x89, 0x85, 0x75, 0x4D, 0x42,  // Code for char @
						        0x80, 0xE0, 0xBC, 0x23, 0xBC, 0xE0, 0x80, 0x00,  // Code for char A
						        0x81, 0xFF, 0x89, 0x89, 0x89, 0x76, 0x00, 0x00,  // Code for char B
						        0x3C, 0x42, 0x81, 0x81, 0x81, 0x43, 0x00, 0x00,  // Code for char C
						        0x81, 0xFF, 0x81, 0x81, 0x81, 0x42, 0x3C, 0x00,  // Code for char D
						        0x81, 0xFF, 0x89, 0x9D, 0x81, 0xC3, 0x00, 0x00,  // Code for char E
						        0x81, 0xFF, 0x89, 0x1D, 0x01, 0x03, 0x00, 0x00,  // Code for char F
						        0x3C, 0x42, 0x81, 0x81, 0x91, 0x73, 0x10, 0x00,  // Code for char G
						        0x81, 0xFF, 0x89, 0x08, 0x89, 0xFF, 0x81, 0x00,  // Code for char H
						        0x81, 0xFF, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char I
						        0x80, 0x81, 0x7F, 0x01, 0x00, 0x00, 0x00, 0x00,  // Code for char J
						        0x81, 0xFF, 0x89, 0x14, 0xA3, 0xC1, 0x81, 0x80,  // Code for char K
						        0x81, 0xFF, 0x81, 0x80, 0x80, 0xC0, 0x00, 0x00,  // Code for char L
						        0x81, 0xFF, 0x87, 0x38, 0xC0, 0x38, 0x87, 0xFF,  // Code for char M
						        0x81, 0xFF, 0x84, 0x18, 0x21, 0xFF, 0x01, 0x00,  // Code for char N
						        0x3C, 0x42, 0x81, 0x81, 0x81, 0x42, 0x3C, 0x00,  // Code for char O
						        0x81, 0xFF, 0x91, 0x11, 0x11, 0x0E, 0x00, 0x00,  // Code for char P
						        0x3C, 0x42, 0x81, 0x81, 0x81, 0x42, 0x3C, 0x00,  // Code for char Q
						        0x81, 0xFF, 0x89, 0x19, 0x69, 0x86, 0x80, 0x00,  // Code for char R
						        0xC6, 0x89, 0x91, 0x63, 0x00, 0x00, 0x00, 0x00,  // Code for char S
						        0x03, 0x01, 0x81, 0xFF, 0x81, 0x01, 0x03, 0x00,  // Code for char T
						        0x01, 0x7F, 0x81, 0x80, 0x81, 0x7F, 0x01, 0x00,  // Code for char U
						        0x01, 0x07, 0x39, 0xC0, 0x39, 0x07, 0x01, 0x00,  // Code for char V
						        0x01, 0x07, 0x39, 0xC0, 0x31, 0x0F, 0x31, 0xC0,  // Code for char W
						        0x81, 0xC3, 0xA5, 0x18, 0xA5, 0xC3, 0x81, 0x00,  // Code for char X
						        0x01, 0x03, 0x8D, 0xF0, 0x8D, 0x03, 0x01, 0x00,  // Code for char Y
						        0xC3, 0xA1, 0x99, 0x85, 0x83, 0xC1, 0x00, 0x00,  // Code for char Z
						        0x00, 0xFF, 0x81, 0x81, 0x00, 0x00, 0x00, 0x00,  // Code for char [
						        0x03, 0x3C, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char BackSlash
						        0x81, 0x81, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char ]
						        0x0C, 0x03, 0x03, 0x0C, 0x00, 0x00, 0x00, 0x00,  // Code for char ^
						        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00,  // Code for char _
						        0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char `
						        0x40, 0xA8, 0xA8, 0xF0, 0x80, 0x00, 0x00, 0x00,  // Code for char a
						        0x7F, 0x88, 0x88, 0x70, 0x00, 0x00, 0x00, 0x00,  // Code for char b
						        0x70, 0x88, 0x88, 0x98, 0x00, 0x00, 0x00, 0x00,  // Code for char c
						        0x70, 0x88, 0x89, 0xFF, 0x80, 0x00, 0x00, 0x00,  // Code for char d
						        0x70, 0xA8, 0xA8, 0xB0, 0x00, 0x00, 0x00, 0x00,  // Code for char e
						        0x88, 0xFE, 0x89, 0x01, 0x03, 0x00, 0x00, 0x00,  // Code for char f
						        0x74, 0xAA, 0xAA, 0xA6, 0x42, 0x00, 0x00, 0x00,  // Code for char g
						        0x81, 0xFF, 0x90, 0x08, 0xF8, 0x80, 0x00, 0x00,  // Code for char h
						        0x88, 0xF9, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char i
						        0x88, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char j
						        0x81, 0xFF, 0x20, 0xD8, 0x88, 0x00, 0x00, 0x00,  // Code for char k
						        0x81, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char l
						        0x88, 0xF8, 0x90, 0x08, 0xF8, 0x90, 0x08, 0xF8,  // Code for char m
						        0x88, 0xF8, 0x90, 0x08, 0xF8, 0x80, 0x00, 0x00,  // Code for char n
						        0x70, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00, 0x00,  // Code for char o
						        0x82, 0xFE, 0xA2, 0x22, 0x1C, 0x00, 0x00, 0x00,  // Code for char p
						        0x1C, 0x22, 0xA2, 0xFE, 0x80, 0x00, 0x00, 0x00,  // Code for char q
						        0x88, 0xF8, 0x90, 0x08, 0x00, 0x00, 0x00, 0x00,  // Code for char r
						        0x90, 0xA8, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char s
						        0x08, 0xFE, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char t
						        0x78, 0x80, 0x80, 0xF8, 0x80, 0x00, 0x00, 0x00,  // Code for char u
						        0x08, 0x38, 0xC0, 0x28, 0x18, 0x08, 0x00, 0x00,  // Code for char v
						        0x38, 0xC0, 0x20, 0x38, 0xC0, 0x38, 0x00, 0x00,  // Code for char w
						        0x88, 0xD8, 0x20, 0xD8, 0x88, 0x00, 0x00, 0x00,  // Code for char x
						        0x82, 0x8E, 0x70, 0x1A, 0x06, 0x02, 0x00, 0x00,  // Code for char y
						        0x98, 0xC8, 0xA8, 0x98, 0xC8, 0x00, 0x00, 0x00,  // Code for char z
						        0x10, 0x6C, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char {
						        0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char |
						        0x00, 0x82, 0x6C, 0x10, 0x00, 0x00, 0x00, 0x00,  // Code for char }
						        0x30, 0x10, 0x30, 0x20, 0x30, 0x00, 0x00, 0x00,  // Code for char ~
						        0xFF, 0x81, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,   // Code for char 


				//������� ������, ������ ��� �� ���� ��� ����� ������������ ��� ��������� c 211 �� 274 ������������
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

				//�������� �� 196 (��� ����� ����) �� 255: �278 �� 340 � ��������� �����

								0x80, 0xE0, 0xBC, 0x23, 0xBC, 0xE0, 0x80, 0x00,  // Code for char 
								0x81, 0xFF, 0x89, 0x89, 0x89, 0x73, 0x00, 0x00,  // Code for char 
								0x81, 0xFF, 0x89, 0x89, 0x89, 0x76, 0x00, 0x00,  // Code for char 
								0x81, 0xFF, 0x81, 0x01, 0x01, 0x03, 0x00, 0x00,  // Code for char 
								0xC0, 0x71, 0x4F, 0x41, 0x41, 0x7F, 0xC1, 0x00,  // Code for char 
								0x81, 0xFF, 0x89, 0x9D, 0x81, 0xC3, 0x00, 0x00,  // Code for char 
								0xC6, 0x28, 0x10, 0xFE, 0x10, 0x28, 0xC6, 0x00,  // Code for char 
								0x43, 0x89, 0x89, 0x89, 0x76, 0x00, 0x00, 0x00,  // Code for char 
								0x81, 0xFF, 0xA1, 0x18, 0x85, 0xFF, 0x81, 0x00,  // Code for char 
								0x81, 0xFF, 0xA1, 0x18, 0x85, 0xFF, 0x81, 0x00,  // Code for char 
								0x81, 0xFF, 0x89, 0x18, 0x66, 0x81, 0x81, 0x00,  // Code for char 
								0x81, 0x7F, 0x01, 0x81, 0xFF, 0x81, 0x00, 0x00,  // Code for char 
								0xFF, 0x07, 0x38, 0xC0, 0x38, 0x07, 0xFF, 0x00,  // Code for char
								0x81, 0xFF, 0x89, 0x08, 0x89, 0xFF, 0x81, 0x00,  // Code for char
								0x3C, 0x42, 0x81, 0x81, 0x81, 0x42, 0x3C, 0x00,  // Code for char
								0x81, 0xFF, 0x81, 0x01, 0x81, 0xFF, 0x81, 0x00,  // Code for char
								0x81, 0xFF, 0x91, 0x11, 0x11, 0x0E, 0x00, 0x00,  // Code for char
								0x3C, 0x42, 0x81, 0x81, 0x81, 0x43, 0x00, 0x00,  // Code for char !
								0x03, 0x01, 0x81, 0xFF, 0x81, 0x01, 0x03, 0x00,  // Code for char "
								0x01, 0x83, 0x85, 0x98, 0x60, 0x1D, 0x03, 0x01,  // Code for char #
								0x18, 0x24, 0xA5, 0xFF, 0xA5, 0x24, 0x18, 0x00,  // Code for char $
								0x81, 0xC3, 0xA5, 0x18, 0xA5, 0xC3, 0x81, 0x00,  // Code for char %
								0x41, 0x7F, 0x41, 0x40, 0x41, 0xFF, 0xC1, 0x80,  // Code for char &
								0x01, 0x1F, 0x11, 0x10, 0x89, 0xFF, 0x81, 0x00,  // Code for char '
								0xFE, 0x80, 0x80, 0xFE, 0x80, 0x80, 0xFE, 0x00,  // Code for char (
								0xFE, 0x80, 0x80, 0xFE, 0x80, 0x80, 0xFE, 0x00,  // Code for char )
								0x03, 0x81, 0xFF, 0x89, 0x88, 0x88, 0x70, 0x00,  // Code for char *
								0x81, 0xFF, 0x89, 0x88, 0x88, 0x70, 0x81, 0xFF,  // Code for char +
								0x81, 0xFF, 0x89, 0x88, 0x88, 0x70, 0x00, 0x00,  // Code for char ,
								0x43, 0x82, 0x89, 0x89, 0x4A, 0x3C, 0x00, 0x00,  // Code for char -
								0xFF, 0x89, 0x08, 0x7E, 0x81, 0x81, 0x81, 0x7E,  // Code for char .
								0x86, 0x69, 0x19, 0x89, 0xFF, 0x81, 0x00, 0x00,  // Code for char /
								0x40, 0xA8, 0xA8, 0xF0, 0x80, 0x00, 0x00, 0x00,  // Code for char 0
								0x7E, 0x89, 0x89, 0x89, 0x71, 0x00, 0x00, 0x00,  // Code for char 1
								0x88, 0xF8, 0xA8, 0xD8, 0x00, 0x00, 0x00, 0x00,  // Code for char 2
								0x88, 0xF8, 0x88, 0x18, 0x00, 0x00, 0x00, 0x00,  // Code for char 3
								0xE4, 0x5C, 0x44, 0x7C, 0xC4, 0x00, 0x00, 0x00,  // Code for char 4
								0x70, 0xA8, 0xA8, 0xB0, 0x00, 0x00, 0x00, 0x00,  // Code for char 5
								0x88, 0xD8, 0x20, 0xF8, 0x20, 0xD8, 0x88, 0x00,  // Code for char 6
								0x88, 0xA8, 0xD8, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char 7
								0x88, 0xF8, 0xA8, 0x10, 0xF8, 0x88, 0x00, 0x00,  // Code for char 8
								0x88, 0xF9, 0xAA, 0x12, 0xF9, 0x88, 0x00, 0x00,  // Code for char 9
								0x88, 0xF8, 0xA0, 0x58, 0x88, 0x00, 0x00, 0x00,  // Code for char :
								0x88, 0xF8, 0x08, 0xF8, 0x88, 0x00, 0x00, 0x00,  // Code for char ;
								0x88, 0xF8, 0x18, 0xE0, 0x18, 0xF8, 0x88, 0x00,  // Code for char <
								0x88, 0xF8, 0xA8, 0x20, 0xF8, 0x88, 0x00, 0x00,  // Code for char =
								0x70, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00, 0x00,  // Code for char >
								0x88, 0xF8, 0x88, 0x08, 0xF8, 0x88, 0x00, 0x00,  // Code for char ?
								0x82, 0xFE, 0xA2, 0x22, 0x1C, 0x00, 0x00, 0x00,  // Code for char @
								0x70, 0x88, 0x88, 0x98, 0x00, 0x00, 0x00, 0x00,  // Code for char A
								0x18, 0x88, 0xF8, 0x88, 0x18, 0x00, 0x00, 0x00,  // Code for char B
								0x82, 0x8E, 0x70, 0x1A, 0x06, 0x02, 0x00, 0x00,  // Code for char C
								0x10, 0x28, 0xAA, 0xFE, 0xA8, 0x28, 0x10, 0x00,  // Code for char D
								0x88, 0xD8, 0x20, 0xD8, 0x88, 0x00, 0x00, 0x00,  // Code for char E
								0x44, 0x7C, 0x44, 0x40, 0x7C, 0x44, 0x80, 0x00,  // Code for char F
								0x08, 0x38, 0x28, 0xA0, 0xF8, 0x88, 0x00, 0x00,  // Code for char G
								0xF8, 0x80, 0x80, 0xF8, 0x80, 0x80, 0xF8, 0x00,  // Code for char H
								0x44, 0x7C, 0x44, 0x40, 0x7C, 0x40, 0x7C, 0xC4,  // Code for char I
								0x10, 0x88, 0xF8, 0xA8, 0xE0, 0x00, 0x00, 0x00,  // Code for char J
								0x88, 0xF8, 0xA8, 0xE0, 0x88, 0xF8, 0x88, 0x00,  // Code for char K
								0x88, 0xF8, 0xA8, 0xE0, 0x00, 0x00, 0x00, 0x00,  // Code for char L
								0x88, 0xA8, 0xA8, 0x70, 0x00, 0x00, 0x00, 0x00,  // Code for char M
								0x88, 0xF8, 0xA8, 0x70, 0x88, 0x88, 0x70, 0x00,  // Code for char N
								0x80, 0xD8, 0x28, 0xF8, 0x88, 0x00, 0x00, 0x00   // Code for char O

};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_RTC_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

void i2c_init(void);// ??????? ????????????? ???? TWI
void OLED_init(void);
//unsigned char OLED_write(unsigned char data);
void sendCommand(unsigned char command);
void LCD_Clear(void);
void LCD_Char(unsigned int c);
void LCD_Goto(unsigned char x, unsigned char y);
void LCD_DrawImage(unsigned char num_image);
void OLED_string(char *string);
void OLED_num_to_str(unsigned int value, unsigned char nDigit);
void init();


void init() {
    // ... ��������� ...

    // ��� ����� ���������� ��������� �������� ��������:
     __HAL_TIM_SET_COUNTER(&htim1, 32760);

    // �� �������� �������� ������!
    HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
}

void sendCommand(uint8_t command_s)
{
	temp[0] = COMAND;
	temp[1] = command_s;
	HAL_I2C_Master_Transmit(&hi2c1,OLED_adress,temp,2,100);
}

void sendData(uint8_t data_s)
{
	temp[0] = DATA;
	temp[1] = data_s;
	HAL_I2C_Master_Transmit(&hi2c1,OLED_adress,temp,2,100);
}

void LCD_Goto(unsigned char x, unsigned char y)
{
	LCD_X = x;
	LCD_Y = y;
	sendCommand(0xB0 + y);
	sendCommand(x & 0xf);
	sendCommand(0x10 | (x >> 4));
}


void LCD_Clear(void)
{
	unsigned short i;
	unsigned short x=0;
	unsigned short y=0;
	LCD_Goto(0,0);

	for (i=0; i<(OLED_BUFFERSIZE); i++) //(SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT/8)
	{
		LCD_Char(' ');
		x ++;
		if(x>OLED_WIDTH)
		{
			x =0;
			y++;
			LCD_Goto(0,y);
		}
	}
	LCD_X =OLED_DEFAULT_SPACE;
	LCD_Y =0;
}

void LCD_Char(unsigned int c)
{
	unsigned char x = 0;
	temp_char[0] = 0x40; // ������� ������ ��� ����� �������� � ������ �������� ������(DATA 0x40), � �� �������(0x00)
	for (x=0; x<8; x++)
	{
		temp_char[x+1] = LCD_Buffer[(c-32)*8+x]; // ����� �������� �������� �� ������ � �������� �� temp_char �� ��������� � 1 ���� P.S. ����� �� ������� ������ ������ � �������� ���������� ����� � ������ ���� (� + 31)
	}
	//temp_char[9] = 0; // �� ����, ���� ���� ���������
	HAL_I2C_Master_Transmit(&hi2c1, OLED_adress, temp_char, 9,1000); // ����������� �� IIC1 �����, ����� ������ � ������ ������, 9 - ���������� ������������� ������, 1000 - ���� ��������� ������ ��� 1000��

/*	LCD_X += 1; // �� ��� �� ������ �� ����� ����� �� �������
	if(LCD_X>OLED_WIDTH) // Oled_width = 128
	{
		LCD_X = OLED_DEFAULT_SPACE;
	}
	*/
}


void OLED_string(char *string)
{
	while(*string != '\0')
	{
		LCD_Char(*string);
		string++;
	}
}

void OLED_num_to_str(unsigned int value, unsigned char nDigit)
{
	switch(nDigit)
	{
		case 5: LCD_Char(value/10000+48);
		case 4: LCD_Char((value/1000)%10+48);
		case 3: LCD_Char((value/100)%10+48);
		case 2: LCD_Char((value/10)%10+48);
		case 1: LCD_Char(value%10+48);
	}
}


void OLED_init(void)
{
		// Turn display off
		sendCommand(OLED_DISPLAYOFF);

		sendCommand(OLED_SETDISPLAYCLOCKDIV);
		sendCommand(0x80);

		sendCommand(OLED_SETMULTIPLEX);
		//sendCommand(0x1F);//128x32
		sendCommand(0x3F);//128x64

		sendCommand(OLED_SETDISPLAYOFFSET);
		sendCommand(0x00);

		sendCommand(OLED_SETSTARTLINE | 0x00);//0

		// We use internal charge pump
		sendCommand(OLED_CHARGEPUMP);
		sendCommand(0x14);

		// Horizontal memory mode
		sendCommand(OLED_MEMORYMODE);
		sendCommand(0x00);

		sendCommand(OLED_SEGREMAP | 0x1);

		sendCommand(OLED_COMSCANDEC);

		sendCommand(OLED_SETCOMPINS);
		//sendCommand(0x02);//128x32
		sendCommand(0x12);//128x64

		// Max contrast
		sendCommand(OLED_SETCONTRAST);
		//sendCommand(0x0F);//0xCF
		sendCommand(0xCF);//0xCF

		sendCommand(OLED_SETPRECHARGE);
		sendCommand(0xF1);

		sendCommand(OLED_SETVCOMDETECT);
		//sendCommand(0x10);//0x40
		sendCommand(0x40);//0x40

		sendCommand(OLED_DISPLAYALLON_RESUME);

		// Non-inverted display
		sendCommand(OLED_NORMALDISPLAY);

		// Turn display back on
		sendCommand(OLED_DISPLAYON);
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_RTC_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
	HAL_Delay(100);
	OLED_init();
	LCD_Clear();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  int currCounter = __HAL_TIM_GET_COUNTER(&htim1);
	      currCounter = 32767 - ((currCounter-1) & 0xFFFF) / 2;
	      if(currCounter != prevCounter) {
	        //  char buff[16];
	        // snprintf(buff, sizeof(buff), "%06d", currCounter);

	          // ������� ����-�� currCounter
	          // ... ��������� ...

	          prevCounter = currCounter;

	      }

LCD_Goto(50,6);
OLED_num_to_str(CNT,5);
HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN); // RTC_FORMAT_BIN , RTC_FORMAT_BCD
//snprintf(trans_str, 63, "Time %d:%d:%d\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
LCD_Goto(85,1);
OLED_num_to_str(sTime.Seconds, 2);
LCD_Goto(65,1);
OLED_num_to_str(sTime.Minutes, 2);
LCD_Goto(44,1);
OLED_num_to_str(sTime.Hours, 2);

LCD_Goto(36,0);
OLED_num_to_str(  DateToUpdate.WeekDay, 2);
LCD_Goto(52,0);
OLED_string("/");
LCD_Goto(58,0);
OLED_num_to_str (DateToUpdate.Month, 2);

HAL_RTC_GetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN);
//snprintf(trans_str, 63, "Date %d-%d-20%d\n", DateToUpdate.Date, DateToUpdate.Month, DateToUpdate.Year);
//HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
HAL_Delay(100);

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 10;
  sTime.Minutes = 34;
  sTime.Seconds = 0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_MONDAY;
  DateToUpdate.Month = RTC_MONTH_JANUARY;
  DateToUpdate.Date = 1;
  DateToUpdate.Year = 0;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 0;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 0;
  if (HAL_TIM_Encoder_Init(&htim1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
