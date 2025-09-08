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
*��  ��:  v1.0��������iDesigner(v4.2.3.172) + ������HRCC(v1.2.0.111)
*��  ��:  2020/06/10
*��  ��:  LRCƵ���ϵ��Լ죬RAM��ROM�ϵ��Լ죬PSW���ۼ����ϵ��Լ�
*��  ע:  ������������HR7P169BоƬ�������̽����ο�
���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
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
