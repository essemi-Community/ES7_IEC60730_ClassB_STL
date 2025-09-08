/**********************************************************************************
 *
 * @file    es7p_CpuRegCheck.c
 * @brief   CPU Register Self-Test Program
 *
 * @date    10 June 2020
 * @author  AE Team
 * @note
 *
 * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 **********************************************************************************/
 
#include <hic.h>
#include <string.h>
enum {SUCCESSED=0, FAILED=0xFF};
extern volatile unsigned char TestResult@0x0D;
volatile unsigned char temp1@0x02 = 0;
volatile unsigned char temp2@0x03 = 0;
const unsigned char TabRomTestData[]={
	0x55, 0xAA
};
void PSWCheck(){
	TestResult = 0;
	while(GIE != 0)GIE = 0;
	PSW = 0;
	__asm{
		MOVI 0x0
		ANDI 0x0
		JBS PSW,Z;0x0 AND 0x0 Z=1
		GOTO TEST_PSW_ERROR

		MOVI 0x1
		ANDI 0x1
		JBC PSW,Z;0x1 AND 0x1 Z=0
		GOTO TEST_PSW_ERROR

		MOVI 0x0
		SUBI 0x0
		JBC PSW,N;0x0 - 0x0 N=0
		GOTO TEST_PSW_ERROR

		MOVI 0x1
		SUBI 0x0
		JBS PSW,N;0x0 - 0x1 N=1
		GOTO TEST_PSW_ERROR

		ADDI 0x0F
		JBS PSW,DC;0xF ADD 0xFF DC=1
		GOTO TEST_PSW_ERROR

		ADDI 0x01
		JBC PSW,DC;0x1 ADD 0x0E DC=0
		GOTO TEST_PSW_ERROR

		SUBI 0x21
		JBS PSW,C;0x21-0x0F C=1
		GOTO TEST_PSW_ERROR

		SUBI 0x1
		JBC PSW,C;0x1-0x12 C=0
		GOTO TEST_PSW_ERROR

		GOTO TEST_PSW_END
TEST_PSW_ERROR:
		MOVI 0xFF
		SECSEL &TestResult& % 0x80
		MOVA &TestResult& % 0x80
TEST_PSW_END:
		NOP
	}
	GIE = 1;
}
void ACCCheck(){
	while(GIE != 0)GIE = 0;
	__asm{
		MOVI 0x5A
		SUBI 0x5A
		JBS PSW,Z;0xA5 - 0xA5 Z=1
		GOTO TEST_ACC_ERROR

		MOVI 0xA5
		SUBI 0xA5
		JBS PSW,Z;0xA5 - 0xA5 Z=1
		GOTO TEST_ACC_ERROR
		GOTO TEST_ACC_END
TEST_ACC_ERROR:
		MOVI 0xFF
		SECSEL &TestResult& % 0x80
		MOVA &TestResult& % 0x80
TEST_ACC_END:
		NOP
	}
	GIE = 1;
}

unsigned char Addressing(){
	while(GIE != 0)GIE = 0;
	temp1=0x55;
	temp2=0xAA;
	TestResult = SUCCESSED;
	if(temp1!=0x55 || temp2!=0xAA){//ºÏ≤‚RAM—∞÷∑
		return FAILED;
	}
	if(TabRomTestData[0]!=0x55 || TabRomTestData[1]!=0xAA){//ºÏ≤‚ROM—∞÷∑
		return FAILED;
	}
	temp1 = PCRL;
	__asm
	{
		MOVI 0x0;A=0	µÿ÷∑+1
		ANDI 0x0;A=A&0	µÿ÷∑+1
		ADDI 0x1;A=1+A	µÿ÷∑+1
		SUBI 0x1;A=1-A	µÿ÷∑+1
	}
	temp2 = PCRL;
	GIE = 1;
	if((temp2 - temp1) == 6)
	{
		return SUCCESSED;
	}
	else
	{
		return FAILED;
	}
}
