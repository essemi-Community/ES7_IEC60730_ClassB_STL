/**********************************************************************************
 *
 * @file    es7p_RamCheck.c
 * @brief   RAM Self-Check Program
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
static volatile unsigned int section8 IAA @ 0xFF81;
volatile unsigned int RamPointer@0x0A = 0;
volatile unsigned char RamBuf@0x0C = 0;
volatile unsigned char TestResult@0x0D = 0;
unsigned char RamCheckStart(void){//MarchC+
    for(IAA=0; IAA<0x0400; IAA++){
        IAD = 0x00;//w00
    }
	for(IAA=0; IAA<0x0400; IAA++){//升序
		if(IAD != 0){//r00
			return FAILED;
		}
		IAD = 0xFF;//wff
		if(IAD != 0xFF){//rff
			return FAILED;
		}
	}
	for(IAA=0; IAA<0x0400; IAA++){//升序
		if(IAD != 0xFF){//rff
			return FAILED;
		}
		IAD = 0x00;//w00
		if(IAD != 0x00){//r00
			return FAILED;
		}
	}
	for(IAA=0x03FF; IAA>0; IAA--){//降序
		if(IAD != 0x00){//r00
			return FAILED;
		}
		IAD = 0xFF;//wff
		if(IAD != 0xFF){//rff
			return FAILED;
		}
	}
	IAD = 0xFF;//wff
	if(IAD != 0xFF){//rff
		return FAILED;
	}
	for(IAA=0x03FF; IAA>0; IAA--){//降序
		if(IAD != 0xFF){//rff
			return FAILED;
		}
		IAD = 0x00;//w00
		if(IAD != 0x00){//r00
			return FAILED;
		}
	}
	IAD = 0x00;//w00
	if(IAD != 0x00){//r00
		return FAILED;
	}
	for(IAA=0x03FF; IAA>0; IAA--){//降序
		if(IAD != 0x00){//r00
			return FAILED;
		}
	}
	IAD = 0x00;//w00
	if(IAD != 0x00){//r00
		return FAILED;
	}
	return SUCCESSED;
}
unsigned char RamCheckRun(void){//每次检测一个字节
    RamPointer++;
	if(RamPointer >= 0x0400){//RAM检测范围
		RamPointer = 0x10;//不检测前16个字节
	}
	TestResult = SUCCESSED;
	IAA = RamPointer;
	RamBuf = IAD;//保存当前地址RAM的值
	IAD = 0x00;//w00
	if(IAD != 0){//r00
		TestResult = FAILED;
	}
	IAD = 0xFF;//wff
	if(IAD != 0xFF){//rff
		TestResult = FAILED;
	}
	IAD = 0x55;//w55
	if(IAD != 0x55){//r55
		TestResult = FAILED;
	}
	IAD = 0xAA;//waa
	if(IAD != 0xAA){//raa
		TestResult = FAILED;
	}
	IAD = RamBuf;//还原当前RAM的值
	return TestResult;
}
