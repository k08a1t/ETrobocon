/******************************************************************************
 *  app.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Task main_task
 *  Author: Kazuhiro.Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "ev3api.h"

	
#ifndef STACK_SIZE
#define STACK_SIZE      8192        /* タスクのスタックサイズ */
#endif /* STACK_SIZE */

/*
 *  関数のプロトタイプ宣言
 */
#ifndef TOPPERS_MACRO_ONLY

extern void main_task(intptr_t exinf);
extern void run_task(intptr_t exinf);
extern void communication_task(intptr_t exinf);
extern void emergencystop_task(intptr_t exinf);
extern void bt_task(intptr_t exinf);
extern void ev3_cyc_run(intptr_t exinf);
extern void ev3_cyc_communication(intptr_t exinf);
extern void ev3_cyc_emergencystop(intptr_t exinf);

#endif /* TOPPERS_MACRO_ONLY */

#ifdef __cplusplus
}
#endif

