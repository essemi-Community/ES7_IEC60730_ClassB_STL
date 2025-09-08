/**********************************************************************************
 *
 * @file    es7p_ClockCheck.c
 * @brief   Clock Self-Check Program
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
volatile unsigned char T8Ncnt@0x00 = 0;
volatile unsigned char T11cnt@0x01 = 0;
unsigned char LRCClockCheckSart(){
	T8N = 240;//16/(32KHz/2)=1ms
	T8NC = 0x48;//T8N时钟源为32KHz，定时器模式，预分频1:2
	T8NIF = 0;

	T11L = 0;
	T11H = 0;
	T11CL = 0x00;//定时器模式
	T11CM = 0x0F;//预分频1:16
	T11CH = 0;
	T11PH = 0x03;
	T11PL = 0xE7;//(999+1)/(16000000Hz/16)=1ms
	T11VIF = 0;

	T8Ncnt = 0;
	T11cnt = 0;

	T8NEN = 1;
	T11EN = 1;
	while(1){
		if(T8NIF == 1){
			T8NIF = 0;
			T8N += 240;
			T8Ncnt++;
		}
		if(T11VIF == 1){
			T11VIF = 0;
			T11cnt++;
			if(T11cnt >= 100){
				if((T8Ncnt < 80) || (T8Ncnt > 120)){//允许误差20%
					return FAILED;
				}
				else{
					return SUCCESSED;
				}
			}
		}
	}
}