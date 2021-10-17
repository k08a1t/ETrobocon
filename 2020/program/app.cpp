#include "app.h"
#include "RunMethod.h"
#include "InstructionMethod.h"

#include "RunCourse.h"
#include "RunArea.h"
#include "RunSection.h"

#include "Form.h"

#include "Condition.h"
#include "DistanceCondition.h"

#include "DistanceMeter.h"

#include "Motor.h"
#include "Clock.h"

// デストラクタ問題の回避
void *__dso_handle=0;

// using宣言
using ev3api::ColorSensor;
using ev3api::TouchSensor;
using ev3api::Motor;
using ev3api::Clock;

// Device objects
// オブジェクトを静的に確保する

ColorSensor colorsensor(PORT_2);
TouchSensor touchSensor(PORT_1);
Motor       leftMotor(PORT_C);
Motor       rightMotor(PORT_B);
Motor       armMotor(PORT_A);
Clock       clock;


// オブジェクトの定義
static DistanceMeter* distancemeter;

static Condition* testCondition;

static Form* testForm;

static RunMethod* testMethod;

static RunCourse* testCourse;

static RunArea* testArea;

static RunSection* testSection;


// scene object
static Scene gScenes[] = {
    { TURN_LEFT,   1250 * 1000, 0 },  // 左旋回1.25秒
    { GO_STRAIGHT, 5000 * 1000, 0 },  // 直進5秒
    { TURN_LEFT,   1250 * 1000, 0 },  // 左旋回1.25秒
    { GO_STRAIGHT, 2500 * 1000, 0 }   // 直進2.5秒
};

/**
 * EV3システム生成
 */
static void user_system_create() {
    // [TODO] タッチセンサの初期化に2msのdelayがあるため、ここで待つ
    tslp_tsk(2U * 1000U);

    // オブジェクトの作成
    distancemeter = new DistanceMeter(&leftMotor, &rightMotor);

    testCourse = new RunCourse();

    testArea = new RunArea();

    testCondition = new DistanceCondition(100, distancemeter);

    testMethod = new InstructionMethod(10, 10, &leftMotor, &rightMotor);

    testForm = new Form(30, &armMotor, &clock);

    testSection = new RunSection(0, testCondition, testMethod, distancemeter, testForm);


    // 初期化完了通知
    ev3_led_set_color(LED_ORANGE);
}

/**
 * EV3システム破棄
 */
static void user_system_destroy() {
    leftMoter.reset();
    rightMoter.reset();

    delete distancemeter;

    delete testCourse;
    delete testArea;
    delete testCondition;
    delete testMethod;
    delete testForm;
    delete testSection;
}

/**
 * メインタスク
 */
void main_task(intptr_t unused) {
    user_system_create();  // センサやモータの初期化処理

    testCourse->addRunArea(testArea);

    testArea->addSection(testSection);

    // 周期ハンドラ開始
    sta_cyc(EV3_CYC_RUN);

    slp_tsk();  // バックボタンが押されるまで待つ

    // 周期ハンドラ停止
    stp_cyc(EV3_CYC_RUN);

    user_system_destroy();  // 終了処理

    ext_tsk();
}

/**
 * ライントレースタスク
 */
void run_task(intptr_t exinf) {
    if (testCourse->startRun() == true) {
        armMotor.setPWM(0);
        leftMotor.setPWM(0);
        rightMotor.setPWM(0);
        stp_cyc(EV3_CYC_RUN);
        ext_tsk();
    }
}
