#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ターゲット依存の定義
 */

#include "ev3api.h"

/*
 *  各タスクの優先度の定義
 */

#define MAIN_PRIORITY    TMIN_APP_TPRI + 1
#define RUN_PRIORITY  TMIN_APP_TPRI + 2

/*
 *  ターゲットに依存する可能性のある定数の定義
 */

#ifndef STACK_SIZE
#define	STACK_SIZE		4096		/* タスクのスタックサイズ */
#endif /* STACK_SIZE */

#ifndef LOOP_REF
#define LOOP_REF		ULONG_C(1000000)	/* 速度計測用のループ回数 */
#endif /* LOOP_REF */

/*
 *  関数のプロトタイプ宣言
 */
#ifndef TOPPERS_MACRO_ONLY
extern void	main_task(intptr_t exinf);
extern void	run_task(intptr_t exinf);

#endif /* TOPPERS_MACRO_ONLY */

#ifdef __cplusplus
}
#endif
