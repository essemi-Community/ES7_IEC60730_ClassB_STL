/**********************************************************************************
 *
 * @file    main.c
 * @brief   main.c
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
 
/*********************************************************
*Copyright (C), 2018, Shanghai Eastsoft Microelectronics Co., Ltd
*版  本:  v1.0，编译于iDesigner(v4.2.3.172) + 工具链HRCC(v1.2.0.111)
*日  期:  2020/06/10
*描  述:  LRC频率上电自检，RAM和ROM上电自检，PSW和累加器上电自检
*备  注:  本例程适用于HR7P169B芯片，本例程仅供参考
本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include <hic.h>
#include <string.h>
static volatile unsigned int section8 IAA @ 0xFF81;
enum {SUCCESSED=0, FAILED=0xFF};
unsigned char LRCClockCheckSart();
void PSWCheck();
void ACCCheck();
unsigned char Addressing();
unsigned char RamCheckStart(void);
unsigned char RamCheckRun(void);
unsigned char FlashCheckStart(void);
unsigned char FlashCheckRun(void);
extern unsigned char TestResult;
unsigned char r;
void main(void){
	PSWCheck();
	r=TestResult;
	ACCCheck();
	r=TestResult;
	r=RamCheckStart();
	r=FlashCheckStart();
    r=LRCClockCheckSart();
	while(1){
		PSWCheck();
		r=TestResult;
		ACCCheck();
		r=TestResult;
		r=Addressing();
		r=RamCheckRun();
		r=FlashCheckRun();
	}
}
