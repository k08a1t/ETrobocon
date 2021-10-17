//走行タスク（4ミリ秒周期）//走行方法パッケージ
#include "RunMethod/RunMethod.h"
#include "RunMethod/LineTraceMethod.h"
#include "RunMethod/InstructionMethod.h"
#include "RunMethod/RatioRotationMethod.h"
#include "RunMethod/PID.h"
#include "RunMethod/DirectionMethod.h"

//ルート案内パッケージ
#include "RouteGuide/RunCourse.h"
#include "RouteGuide/RunArea.h"
#include "RouteGuide/RunBlock.h"
#include "RouteGuide/CrossRunBlock.h"
#include "RouteGuide/StarWatchRunBlock.h"
#include "RouteGuide/DynamicRunArea.h"
#include "RouteGuide/RouteSearchRunBlock.h"
#include "RouteGuide/ResetRunBlock.h"
#include "RouteGuide/BlockLineRunArea.h"

//機体状態パッケージ
#include "Mode/Mode.h"

//条件パッケージ
#include "Condition/Condition.h"
#include "Condition/DirectionCondition.h"
#include "Condition/DistanceCondition.h"
#include "Condition/LineCondition.h"
#include "Condition/MultiCondition.h"
#include "Condition/ObstacleCondition.h"
#include "Condition/StepCondition.h"
#include "Condition/TimeDetectionCondition.h"
#include "Condition/ColorCondition.h"
#include "Condition/HSLCondition.h"
#include "Condition/AllDirectionCondition.h"
#include "Condition/CheckRGBCondition.h"
#include "Condition/CheckHSLCondition.h"
#include "Condition/RailDetectionCondition.h"
#include "Condition/PBPlaceDetectionCondition.h"

//計測器パッケージ
#include "Measure/Brightness.h"
#include "Measure/Calibration.h"
#include "Measure/DistanceMeasure.h"
#include "Measure/SpeedoMeter.h"
#include "Measure/TrainReader.h"
#include "Measure/StarReader.h"
#include "Measure/BlockReader.h"
#include "Measure/HSLMeasure.h"

//コミュニケーションパッケージ
#include "Communication/Communication.h"
#include "Communication/LogData.h"
#include "Communication/Sound.h"

//ブロック並べパッケージ
#include "BlockLay/BlackLine.h"
#include "BlockLay/Block.h"
#include "BlockLay/BlockPlace.h"
#include "BlockLay/BlockLayScenario.h"
#include "BlockLay/PolygonBlockPlace.h"
#include "BlockLay/Color.h"
#include "BlockLay/Field.h"
#include "BlockLay/Route.h"
#include "BlockLay/Shape.h"
#include "BlockLay/CenterBlockPlace.h"

//デバイス関連
#include "Device/SonarMeter.h"
#include "Motor.h"
#include "TouchSensor.h"
#include "ColorSensor.h"
#include "SonarSensor.h"
#include "GyroSensor.h"
#include "Clock.h"


#include "app.h"
#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

using namespace ev3api;
// using宣言
using ev3api::ColorSensor;
using ev3api::GyroSensor;
using ev3api::TouchSensor;
using ev3api::SonarSensor;
using ev3api::Motor;
using ev3api::Clock;



//ポート設定
const ePortS GYRO_SENSOR_PORT = PORT_4;
const ePortS SONAR_SENSOR_PORT = PORT_3;
const ePortS COLOR_SENSOR_PORT = PORT_2;
const ePortS TOUCH_SENSOR_PORT = PORT_1;
const ePortM ARM_MOTOR_PORT = PORT_A;
const ePortM RIGHT_MOTOR_PORT = PORT_B;
const ePortM LEFT_MOTOR_PORT = PORT_C;
//------------------------------


// Device objects
// オブジェクトを静的に確保する
ColorSensor colorSensor(COLOR_SENSOR_PORT);
GyroSensor  gyroSensor(GYRO_SENSOR_PORT);
TouchSensor touchSensor(TOUCH_SENSOR_PORT);
SonarSensor sonarSensor(SONAR_SENSOR_PORT);
Motor       leftMotor(LEFT_MOTOR_PORT);
Motor       rightMotor(RIGHT_MOTOR_PORT);
Motor       armMotor(ARM_MOTOR_PORT);
Clock       clock;

static FILE     *bt = NULL;     // Bluetoothファイルハンドル 
static int32_t   bt_cmd = 0; 
static int    prenum = 0;

//********************オブジェクトの定義********************//	


static Block*					RedBlock;
static Block*					YellowBlock;
static Block*					BlueBlock;
static Block*					GreenBlock;
static Block*					BlackBlock;
static BlackLine*				blackline0;
static BlackLine*				blackline1;
static BlackLine*				blackline2;
static BlackLine*				blackline3;
static BlackLine*				blackline4;
static BlackLine*				blackline5;
static BlackLine*				blackline6;
static BlackLine*				blackline7;
static BlackLine*				blackline8;
static BlackLine*				blackline9;
static BlackLine*				blackline10;
static BlackLine*				blackline11;
static BlackLine*				blackline12;
static BlackLine*				blackline13;
static BlackLine*				blackline14;
static BlackLine*				blackline15;
static BlackLine*				blackline16;
static BlackLine*				blackline17;
static BlackLine*				blackline18;
static BlackLine*				blackline19;
static BlackLine*				blackline20;
static BlackLine*				blackline21;
static BlackLine*				blackline22;
static BlackLine*				blackline23;
static BlackLine*				blackline24;
static BlackLine*				blackline25;
static BlackLine*				blackline26;
static CenterBlockPlace*		blockplace0;
static PolygonBlockPlace*		blockplace1;
static PolygonBlockPlace*		blockplace2;
static PolygonBlockPlace*		blockplace3;
static PolygonBlockPlace*		blockplace4;
static PolygonBlockPlace*		blockplace5;
static PolygonBlockPlace*		blockplace6;
static PolygonBlockPlace*		blockplace7;
static PolygonBlockPlace*		blockplace8;
static PolygonBlockPlace*		blockplace9;
static PolygonBlockPlace*		blockplace10;
static PolygonBlockPlace*		blockplace11;
static PolygonBlockPlace*		blockplace12;
static PolygonBlockPlace*		blockplace13;
static PolygonBlockPlace*		blockplace14;
static PolygonBlockPlace*		blockplace15;
static Shape*					shape1;
static Shape*					shape2;
static Shape*					shape3;
static Shape*					shape4;
static Shape*					shape5;
static Shape*					shape6;
static Shape*					shape7;
static Shape*					shape8;
static Shape*					shape9;
static Shape*					shape10;
static Shape*					shape11;
static Shape*					shape12;
static Shape*					shape13;
static Shape*					shape14;
static Field*					field;
static Route*					route;
static BlockLayScenario*		blocklayscenario;

//------------------コミュニケーションの定義------------------//
static  Brightness*				brightness;
static	Communication*			communication;
static	LogData*				logdata;
static	Sound*					sound;

//-----------------------計測器の定義-----------------------//
static	Calibration*			calibration;
static	DistanceMeasure*		distanceMeasure;
static	SpeedoMeter*			speedoMeter;
static	SonarMeter*				sonarMeter;
static  StarReader*				starReader;
static  BlockReader*            blockReader;
static  HSLMeasure*				HSLMesure;

//-----------------------PIDの定義-----------------------//
static	PID*					pid_StartUp;
static  PID*					pid_hispeedStraight;
static  PID*					pid_hiCurve;
static  PID*					pid_lowCurve;
static  PID*                    pid_lowspeedStraight;
static  PID*					pid_LowSpeedCurve;
static	PID*					pid_R_First;
static	PID*					pid_Curve;
static	PID*					pid_Uneri;
static	PID*					pid_nameraka;

//-----------------------検知条件の定義-----------------------//
//

static	Condition*				Start_StopDisCondition;

static	Condition*				First_SlowDisCondition;
static	Condition*				First_FastDisCondition;
static	Condition*				First_CircleDisCondition;
static	Condition*				First_CurveDisCondition;
static	Condition*				Second_CurveDisCondition;
static	Condition*				Second_UneriDisCondition;
static	Condition*				Second_Uneri2DisCondition;
static	Condition*				Second_FastDisCondition;
static	Condition*				Intogame_TurnDisCondition;
static	Condition*				Intogame_OverlineDisCondition;
static	Condition*				Intogame_FindturnDisCondition;
static	Condition*				Intogame_GoDisCondition;

static  Condition*				LineTraceCondition;
static  Condition*				Detection_PBPlaceCondition;
static  Condition*				Correction_middleCondition;
static  Condition*				Direction_Change_LCondition;
static  Condition*				Direction_Change_RCondition;

static  Condition*				Turn_Avoid_Angle0Condition;
static  Condition*				Turn_Angle30Condition;
static  Condition*				Turn_Avoid_Angle30Condition;
static  Condition*				Turn_AngleMinus30Condition;
static  Condition*				Turn_Avoid_AngleMinus30Condition;
static  Condition*				Turn_Angle45Condition;
static  Condition*				Turn_Avoid_Angle45Condition;
static  Condition*				Turn_AngleMinus45Condition;
static  Condition*				Turn_Avoid_AngleMinus45Condition;
static  Condition*				Turn_Angle60Condition;
static  Condition*				Turn_Avoid_Angle60Condition;
static  Condition*				Turn_AngleMinus60Condition;
static  Condition*				Turn_Avoid_AngleMinus60Condition;
static  Condition*				Turn_Angle90Condition;
static  Condition*				Turn_Avoid_Angle90Condition;
static  Condition*				Turn_AngleMinus90Condition;
static  Condition*				Turn_Avoid_AngleMinus90Condition;
static  Condition*				Turn_Angle105Condition;
static  Condition*				Turn_Avoid_Angle105Condition;
static  Condition*				Turn_AngleMinus105Condition;
static  Condition*				Turn_Avoid_AngleMinus105Condition;
static  Condition*				Turn_Angle120Condition;
static  Condition*				Turn_Avoid_Angle120Condition;
static  Condition*				Turn_AngleMinus120Condition;
static  Condition*				Turn_Avoid_AngleMinus120Condition;
static  Condition*				Turn_Angle135Condition;
static  Condition*				Turn_Avoid_Angle135Condition;
static  Condition*				Turn_AngleMinus135Condition;
static  Condition*				Turn_Avoid_AngleMinus135Condition;
static  Condition*				Turn_Angle150Condition;
static  Condition*				Turn_Avoid_Angle150Condition;
static  Condition*				Turn_AngleMinus150Condition;
static  Condition*				Turn_Avoid_AngleMinus150Condition;

static  Condition*				Correction_ShortStraightCondition;
static  Condition*				Detection_LineCondition;
static	Condition*				Short_AdvantageCondition;
static  Condition*				Detection_Line_LeftCondition;
static  Condition*				Detection_Line_RightCondition;

static  Condition*				Station_LineTraceCondition;
static  Condition*				Station_PBPlaceCondition;
static  Condition*				Station_BackCondition;

static  Condition*				TurnDisCondition;
static	Condition*				Goparking_Find_LineDisCondition;
static	Condition*				Goparking_OutDisCondition;
static	Condition*				Goparking_Turn_LineDisCondition;
static	Condition*				Goparking_TraceDisCondition;
static	Condition*				Letsparking_TurnDisCondition;
static	Condition*				Letsparking_MoveDisCondition;
static	Condition*				Letsparking_LastturnDisCondition;
static	Condition*				Letsparking_Find_GreenDisCondition;
static	Condition*				Letsparking_GooutDisCondition;
static	Condition*				Letsparking_Find_LineDisCondition;
static	Condition*				Letsparking_MiliDisCondition;
static	Condition*				Letsparking_FastDisCondition;

static	Condition*				Final_StopCondition;

//-----------------------機体状態の定義-----------------------//
static Mode*					lineMode;
static Mode*					WatchBlockMode;
static Mode*					CatchMode;
static Mode*					GetMode;
static Mode*                    search1Mode;
static Mode*                    search2Mode;

//-----------------------走行方法の定義-----------------------//

static	RunMethod*				Start_StopRun;

static	RunMethod*				First_SlowRun;
static	RunMethod*				First_FastRun;
static	RunMethod*				First_CircleRun;
static	RunMethod*				First_CurveRun;
static	RunMethod*				Second_CurveRun;
static	RunMethod*				Second_UneriRun;
static	RunMethod*				Second_Uneri2Run;
static	RunMethod*				Second_FastRun;
static	RunMethod*				Intogame_TurnRun;
static	RunMethod*				Intogame_OverlineRun;
static	RunMethod*				Intogame_FindturnRun;
static	RunMethod*				Intogame_GoRun;

static  RunMethod*				LineTraceRun;
static  RunMethod*				Detection_PBPlaceRun;
static  RunMethod*				Correction_middleRun;
static  RunMethod*				Direction_Change_LRun;
static  RunMethod*				Direction_Change_RRun;

static  RunMethod*				Turn_Avoid_Angle0Run;
static  RunMethod*				Turn_Angle30Run;
static  RunMethod*				Turn_Avoid_Angle30Run;
static  RunMethod*				Turn_AngleMinus30Run;
static  RunMethod*				Turn_Avoid_AngleMinus30Run;
static  RunMethod*				Turn_Angle45Run;
static  RunMethod*				Turn_Avoid_Angle45Run;
static  RunMethod*				Turn_AngleMinus45Run;
static  RunMethod*				Turn_Avoid_AngleMinus45Run;
static  RunMethod*				Turn_Angle60Run;
static  RunMethod*				Turn_Avoid_Angle60Run;
static  RunMethod*				Turn_AngleMinus60Run;
static  RunMethod*				Turn_Avoid_AngleMinus60Run;
static  RunMethod*				Turn_Angle90Run;
static  RunMethod*				Turn_Avoid_Angle90Run;
static  RunMethod*				Turn_AngleMinus90Run;
static  RunMethod*				Turn_Avoid_AngleMinus90Run;
static  RunMethod*				Turn_Angle105Run;
static  RunMethod*				Turn_Avoid_Angle105Run;
static  RunMethod*				Turn_AngleMinus105Run;
static  RunMethod*				Turn_Avoid_AngleMinus105Run;
static  RunMethod*				Turn_Angle120Run;
static  RunMethod*				Turn_Avoid_Angle120Run;
static  RunMethod*				Turn_AngleMinus120Run;
static  RunMethod*				Turn_Avoid_AngleMinus120Run;
static  RunMethod*				Turn_Angle135Run;
static  RunMethod*				Turn_Avoid_Angle135Run;
static  RunMethod*				Turn_AngleMinus135Run;
static  RunMethod*				Turn_Avoid_AngleMinus135Run;
static  RunMethod*				Turn_Angle150Run;
static  RunMethod*				Turn_Avoid_Angle150Run;
static  RunMethod*				Turn_AngleMinus150Run;
static  RunMethod*				Turn_Avoid_AngleMinus150Run;

static  RunMethod*				Correction_ShortStraightRun;
static	RunMethod*				Detection_LineRun;
static	RunMethod*				Short_AdvantageRun;
static  RunMethod*				Detection_Line_LeftRun;
static  RunMethod*				Detection_Line_RightRun;

static	RunMethod*				Station_LineTraceRun;
static	RunMethod*				Station_PBPlaceRun;
static	RunMethod*				Station_BackRun;

static	RunMethod*				TurnRun;
static	RunMethod*				Goparking_Find_LineRun;
static	RunMethod*				Goparking_OutRun;
static	RunMethod*				Goparking_Turn_LineRun;
static	RunMethod*				Goparking_TraceRun;
static	RunMethod*				Letsparking_TurnRun;
static	RunMethod*				Letsparking_MoveRun;
static	RunMethod*				Letsparking_LastturnRun;
static	RunMethod*				Letsparking_Find_GreenRun;
static	RunMethod*				Letsparking_GooutRun;
static	RunMethod*				Letsparking_Find_LineRun;
static	RunMethod*				Letsparking_MiliRun;
static	RunMethod*				Letsparking_FastRun;

static	RunMethod*				Final_StopRun;

//-----------------------走行コースの定義-----------------------//
static	RunCourse*				leftCourse;

//-----------------------走行エリアの定義-----------------------//
static	RunArea*				FirstRunArea;
static	RunArea*				Left_FieldMovingArea;
static	RunArea*				ParkingArea;
static	RunArea*				StationArea;
static	RunArea*				BLArea;

//-----------------------走行区画の定義-----------------------//
static	RunBlock*				Start_StopBlock;

static	RunBlock*				First_SlowBlock;
static	RunBlock*				First_FastBlock;
static	RunBlock*				First_CircleBlock;
static	RunBlock*				First_CurveBlock;
static	RunBlock*				Second_CurveBlock;
static	RunBlock*				Second_UneriBlock;
static	RunBlock*				Second_Uneri2Block;
static	RunBlock*				Second_FastBlock;
static	RunBlock*				Intogame_TurnBlock;
static	RunBlock*				Intogame_OverlineBlock;
static	RunBlock*				Intogame_FindturnBlock;
static	RunBlock*				Intogame_GoBlock;


static  RunBlock*				LineTraceBlock;
static  RunBlock*				Detection_PBPlaceBlock;
static  RunBlock*				Correction_middleBlock;
static  RunBlock*				Direction_Change_LBlock;
static  RunBlock*				Direction_Change_RBlock;

static  RunBlock*				Turn_Avoid_Angle0Block;
static  RunBlock*				Turn_Angle30Block;
static  RunBlock*				Turn_Avoid_Angle30Block;
static  RunBlock*				Turn_AngleMinus30Block;
static  RunBlock*				Turn_Avoid_AngleMinus30Block;
static  RunBlock*				Turn_Angle45Block;
static  RunBlock*				Turn_Avoid_Angle45Block;
static  RunBlock*				Turn_AngleMinus45Block;
static  RunBlock*				Turn_Avoid_AngleMinus45Block;
static  RunBlock*				Turn_Angle60Block;
static  RunBlock*				Turn_Avoid_Angle60Block;
static  RunBlock*				Turn_AngleMinus60Block;
static  RunBlock*				Turn_Avoid_AngleMinus60Block;
static  RunBlock*				Turn_Angle90Block;
static  RunBlock*				Turn_Avoid_Angle90Block;
static  RunBlock*				Turn_AngleMinus90Block;
static  RunBlock*				Turn_Avoid_AngleMinus90Block;
static  RunBlock*				Turn_Angle105Block;
static  RunBlock*				Turn_Avoid_Angle105Block;
static  RunBlock*				Turn_AngleMinus105Block;
static  RunBlock*				Turn_Avoid_AngleMinus105Block;
static  RunBlock*				Turn_Angle120Block;
static  RunBlock*				Turn_Avoid_Angle120Block;
static  RunBlock*				Turn_AngleMinus120Block;
static  RunBlock*				Turn_Avoid_AngleMinus120Block;
static  RunBlock*				Turn_Angle135Block;
static  RunBlock*				Turn_Avoid_Angle135Block;
static  RunBlock*				Turn_AngleMinus135Block;
static  RunBlock*				Turn_Avoid_AngleMinus135Block;
static  RunBlock*				Turn_Angle150Block;
static  RunBlock*				Turn_Avoid_Angle150Block;
static  RunBlock*				Turn_AngleMinus150Block;
static  RunBlock*				Turn_Avoid_AngleMinus150Block;

static  RunBlock*				Correction_ShortStraightBlock;
static	RunBlock*				Detection_LineBlock;
static	RunBlock*				Short_AdvantageBlock;
static  RunBlock*				Detection_Line_LeftBlock;
static  RunBlock*				Detection_Line_RightBlock;

static	RunBlock*				Station_LineTraceBlock;
static	RunBlock*				Station_PBPlaceBlock;
static	RunBlock*				Station_BackBlock;

static	RunBlock*				TurnBlock;
static	RunBlock*				Goparking_Find_LineBlock;
static	RunBlock*				Goparking_OutBlock;
static	RunBlock*				Goparking_Turn_LineBlock;
static	RunBlock*				Goparking_TraceBlock;
static	RunBlock*				Letsparking_TurnBlock;
static	RunBlock*				Letsparking_MoveBlock;
static	RunBlock*				Letsparking_LastturnBlock;
static	RunBlock*				Letsparking_Find_GreenBlock;
static	RunBlock*				Letsparking_GooutBlock;
static	RunBlock*				Letsparking_Find_LineBlock;
static	RunBlock*				Letsparking_MiliBlock;
static	RunBlock*				Letsparking_FastBlock;

static	RunBlock*				Final_StopBlock;

static void user_system_create() {
	//******************インスタンスが複数ないクラスの設定**********//
	sonarMeter = new SonarMeter(&sonarSensor);
	brightness = new Brightness(&colorSensor);
	logdata = new LogData();
	HSLMesure = new HSLMeasure(&colorSensor);
	distanceMeasure = new DistanceMeasure(&leftMotor, &rightMotor);
	speedoMeter = new SpeedoMeter(distanceMeasure);
	calibration = new Calibration(&touchSensor, &colorSensor, &clock, &gyroSensor, brightness,HSLMesure);
	sound = new Sound(&clock);
	communication = new Communication(sound);
	starReader = new StarReader(&colorSensor);
	blockReader = new BlockReader(&colorSensor);


	//***********ブロック並べエリアで使うインスタンス*************//
	

	RedBlock = new Block(Red);
	YellowBlock = new Block(Yellow);
	BlueBlock = new Block(Blue);
	GreenBlock = new Block(Green);
	BlackBlock = new Block(Black);
	blackline0 = new BlackLine(0);
	blackline1 = new BlackLine(1);
	blackline2 = new BlackLine(2);
	blackline3 = new BlackLine(3);
	blackline4 = new BlackLine(4);
	blackline5 = new BlackLine(5);
	blackline6 = new BlackLine(6);
	blackline7 = new BlackLine(7);
	blackline8 = new BlackLine(8);
	blackline9 = new BlackLine(9);
	blackline10 = new BlackLine(10);
	blackline11 = new BlackLine(11);
	blackline12 = new BlackLine(12);
	blackline13 = new BlackLine(13);
	blackline14 = new BlackLine(14);
	blackline15 = new BlackLine(15);
	blackline16 = new BlackLine(16);
	blackline17 = new BlackLine(17);
	blackline18 = new BlackLine(18);
	blackline19 = new BlackLine(19);
	blackline20 = new BlackLine(20);
	blackline21 = new BlackLine(21);
	blackline22 = new BlackLine(22);
	blackline23 = new BlackLine(23);
	blackline24 = new BlackLine(24);
	blackline25 = new BlackLine(25);
	blackline26 = new BlackLine(26);
	blockplace0 = new CenterBlockPlace(0, 100,2,4,6,2,4,6,4,6,2,8,4,6,8,8,6);
	blockplace1 = new PolygonBlockPlace(1, 2,100,2,4,2,2,4,4,4,4,6,6,6,6,6,4,blackline2,blackline22,blackline24,nullptr,Red);
	blockplace2 = new PolygonBlockPlace(2, 4,2,100,2,6,2,2,4,4,6,4,6,6,6,6,4,blackline3,blackline4,blackline24,blackline25,Blue);
	blockplace3 = new PolygonBlockPlace(3, 6,4,2,100,6,4,2,6,4,8,2,8,8,6,8,6,blackline5,blackline6,blackline25,blackline26,Yellow);
	blockplace4 = new PolygonBlockPlace(4, 2,2,4,6,100,4,6,2,6,2,8,4,4,6,8,4,blackline7,blackline23,blackline26,nullptr,Blue);
	blockplace5 = new PolygonBlockPlace(5, 4,2,2,4,4,100,4,2,2,6,6,4,4,4,4,2,blackline2,blackline3,blackline8,blackline9,Yellow);
	blockplace6 = new PolygonBlockPlace(6, 6,4,2,2,6,4,100,6,2,8,2,8,6,4,4,6,blackline4,blackline5,blackline10,blackline11,Green);
	blockplace7 = new PolygonBlockPlace(7, 4,4,4,6,2,2,6,100,4,4,8,2,2,4,6,2,blackline6,blackline7,blackline12,blackline13,Red);
	blockplace8 = new PolygonBlockPlace(8, 6,4,4,4,6,2,2,4,100,8,4,6,4,2,2,2,blackline9,blackline10,blackline14,blackline15,Red);
	blockplace9 = new PolygonBlockPlace(9, 2,4,6,8,2,6,8,4,8,100,10,2,4,6,8,6,blackline11,blackline12,blackline16,blackline17,Blue);
	blockplace10 = new PolygonBlockPlace(10, 8,6,4,2,8,6,2,8,4,10,100,8,6,4,2,6,blackline8,blackline18,blackline22,nullptr,Green);
	blockplace11 = new PolygonBlockPlace(11, 4,6,6,8,4,4,8,2,6,2,8,100,2,4,6,4,blackline13,blackline21,blackline23,nullptr,Green);
	blockplace12 = new PolygonBlockPlace(12, 6,6,6,8,4,4,6,2,4,4,6,2,100,2,4,2,blackline14,blackline18,blackline19,nullptr,Blue);
	blockplace13 = new PolygonBlockPlace(13, 8,6,6,6,6,4,4,4,2,6,4,4,2,100,2,2,blackline1,blackline15,blackline19,nullptr,Yellow);
	blockplace14 = new PolygonBlockPlace(14, 8,6,6,4,8,4,4,6,2,8,2,6,4,2,100,4,blackline1,blackline16,blackline20,nullptr,Red);
	blockplace15 = new PolygonBlockPlace(15, 6,4,4,6,4,2,4,2,2,6,6,4,2,2,4,100,blackline17,blackline20,blackline21,nullptr,Yellow);
	shape1 = new Shape(blockplace6,blockplace8,blockplace9,blockplace13,blockplace14);//五角形
	shape2 = new Shape(blockplace1,blockplace2,blockplace5,blockplace10,nullptr);//四角形
	shape3 = new Shape(blockplace2,blockplace3,blockplace6,blockplace8,nullptr);
	shape4 = new Shape(blockplace3,blockplace6,blockplace7,blockplace9,nullptr);
	shape5 = new Shape(blockplace3,blockplace4,blockplace7,blockplace11,nullptr);
	shape6 = new Shape(blockplace5,blockplace8,blockplace10,blockplace12,nullptr);
	shape7 = new Shape(blockplace7,blockplace9,blockplace11,blockplace15,nullptr);
	shape8 = new Shape(blockplace1,blockplace2,blockplace5,nullptr,nullptr);//三角形
	shape9 = new Shape(blockplace2,blockplace3,blockplace6,nullptr,nullptr);
	shape10 = new Shape(blockplace3,blockplace4,blockplace7,nullptr,nullptr);
	shape11 = new Shape(blockplace1,blockplace5,blockplace10,nullptr,nullptr);
	shape12 = new Shape(blockplace4,blockplace7,blockplace11,nullptr,nullptr);
	shape13 = new Shape(blockplace8,blockplace12,blockplace13,nullptr,nullptr);
	shape14 = new Shape(blockplace9,blockplace14,blockplace15,nullptr,nullptr);
	field = new Field(10,RedBlock,YellowBlock,BlueBlock,GreenBlock,BlackBlock);
	route = new Route(field);
	blocklayscenario = new BlockLayScenario(route, RedBlock, YellowBlock, BlackBlock, GreenBlock, BlackBlock);

	//************走行コースと走行エリアの設定************//
	//-------------------走行コースの設定-------------------//
	leftCourse = new RunCourse(calibration, communication);

	//-------------------走行エリアの設定-------------------//
	FirstRunArea = new RunArea();
	Left_FieldMovingArea = new DynamicRunArea();
	ParkingArea = new RunArea();
	StationArea = new RunArea();
	BLArea = new BlockLineRunArea(Left_FieldMovingArea, StationArea, blocklayscenario);
	//*****************インスタンスが複数あるクラスの設定**********//

	//-----------------------PIDの設定-----------------------//
	pid_StartUp = new PID(0.6, 0.0, 9.0);
	pid_lowspeedStraight = new PID(0.45, 0.0, 2.0);
	pid_hiCurve = new PID(1.9, 0.0, 18.0);//PID(1.65, 0.0, 18.0)
	pid_lowCurve = new PID(1.50, 0.0, 17.0);//PID(1.50, 0.0, 17.0)
	pid_LowSpeedCurve = new PID(0.5, 0.0, 10.0);
	pid_hispeedStraight = new PID(2.00, 0.0, 30.0);//PID(2.00, 0.0, 30.0)
	pid_R_First = new PID(1.2, 0.0, 18.0);
	pid_Curve = new PID(1.170, 0.1, 17.5);
	pid_Uneri = new PID(1.25, 0.1, 16.5);
	pid_nameraka = new PID(1.22, 0.1, 19.0);

	//******************条件と走行方法クラスのAPI**********************//
	//	距離検知				DistanceCondition(距離mm,distanceMeasure);
	//	時間検知				TimeDetectionCondition(ミリ秒,&clock);
	//	段差検知				StepCondition(ジャイロ値,速度,&gyroSensor,speedoMeter);
	//	方向検知				DirectionCondition(角度°,distanceMeasure);
	//	ライン検知				LineCondition(&colorSensor,calibration);
	//	ｽﾃｱﾘﾝｸﾞ検知				SteeringCondition(角度°,&steerMotor);
	//	障害物検知				ObstacleCondition(sonarMeter,目標距離cm);
	//	複数検知				MultiCondition(論理条件bool,検知条件のインスタンス,検知条件のインスタンス);
	//	直線検知				StraightCondition(&steerMotor)


	//	ライントレース走行		LineTraceMethod(速度, ステア限界角度, ステア基準角度変更, エッジ（bool 0で右 1で左）, 境界線値変更, &leftMotor, &rightMotor,   diff, brightness, お好きなpid);
	//	指定走行				InstructionMethod(左速度, 右速度, ステア角度, &leftMotor, &rightMotor, &steerMotor);
	//	等回転比走行			RatioRotationMethod(旋回係数, 旋回補助, 速度, &leftMotor, &rightMotor, distanceMeasure);
	//*****************************************************************//	

//Condition
	Start_StopDisCondition =				new TimeDetectionCondition(1000, &clock);

	First_SlowDisCondition =				new DistanceCondition(390, distanceMeasure);
	First_FastDisCondition =				new DistanceCondition(1600, distanceMeasure);
	First_CircleDisCondition =				new DistanceCondition(1600, distanceMeasure);
	First_CurveDisCondition =				new DistanceCondition(1400, distanceMeasure);
	Second_CurveDisCondition =				new DistanceCondition(1500, distanceMeasure);
	Second_UneriDisCondition =				new DistanceCondition(1550, distanceMeasure);
	Second_Uneri2DisCondition =				new DistanceCondition(550, distanceMeasure);
	Second_FastDisCondition =				new DistanceCondition(1800, distanceMeasure);
	Intogame_TurnDisCondition =				new DirectionCondition(30, distanceMeasure);
	Intogame_OverlineDisCondition =			new DistanceCondition(20, distanceMeasure);
	Intogame_FindturnDisCondition =			new LineCondition(-18, brightness);
	Intogame_GoDisCondition =				new DistanceCondition(750, distanceMeasure);

	LineTraceCondition =					new DistanceCondition(90, distanceMeasure);
	Detection_PBPlaceCondition =			new PBPlaceDetectionCondition(&colorSensor, true, calibration);
	Correction_middleCondition =			new DistanceCondition(80, distanceMeasure);
	Direction_Change_LCondition =			new DirectionCondition(-190, distanceMeasure);
	Direction_Change_RCondition =			new DirectionCondition(190, distanceMeasure);

	Turn_Avoid_Angle0Condition =			new DirectionCondition(-350, distanceMeasure);
	Turn_Angle30Condition =					new DirectionCondition(50, distanceMeasure);
	Turn_Avoid_Angle30Condition =			new DirectionCondition(-300, distanceMeasure);
	Turn_AngleMinus30Condition =			new DirectionCondition(-65, distanceMeasure);
	Turn_Avoid_AngleMinus30Condition =		new DirectionCondition(300, distanceMeasure);
	Turn_Angle45Condition =					new DirectionCondition(80, distanceMeasure);
	Turn_Avoid_Angle45Condition =			new DirectionCondition(-270, distanceMeasure);
	Turn_AngleMinus45Condition =			new DirectionCondition(-80, distanceMeasure);
	Turn_Avoid_AngleMinus45Condition =		new DirectionCondition(270, distanceMeasure);
	Turn_Angle60Condition =					new DirectionCondition(125, distanceMeasure);
	Turn_Avoid_Angle60Condition =			new DirectionCondition(-220, distanceMeasure);
	Turn_AngleMinus60Condition =			new DirectionCondition(-125, distanceMeasure);
	Turn_Avoid_AngleMinus60Condition =		new DirectionCondition(220, distanceMeasure);
	Turn_Angle90Condition =					new DirectionCondition(180, distanceMeasure);
	Turn_Avoid_Angle90Condition =			new DirectionCondition(-170, distanceMeasure);
	Turn_AngleMinus90Condition =			new DirectionCondition(-190, distanceMeasure);
	Turn_Avoid_AngleMinus90Condition =		new DirectionCondition(170, distanceMeasure);
	Turn_Angle105Condition =				new DirectionCondition(225, distanceMeasure);
	Turn_Avoid_Angle105Condition =			new DirectionCondition(-120, distanceMeasure);
	Turn_AngleMinus105Condition =			new DirectionCondition(-225, distanceMeasure);
	Turn_Avoid_AngleMinus105Condition =		new DirectionCondition(120, distanceMeasure);
	Turn_Angle120Condition =				new DirectionCondition(255, distanceMeasure);
	Turn_Avoid_Angle120Condition =			new DirectionCondition(-70, distanceMeasure);
	Turn_AngleMinus120Condition =			new DirectionCondition(-255, distanceMeasure);
	Turn_Avoid_AngleMinus120Condition =		new DirectionCondition(70, distanceMeasure);
	Turn_Angle135Condition =				new DirectionCondition(280, distanceMeasure);
	Turn_Avoid_Angle135Condition =			new DirectionCondition(-20, distanceMeasure);
	Turn_AngleMinus135Condition =			new DirectionCondition(-275, distanceMeasure);
	Turn_Avoid_AngleMinus135Condition =		new DirectionCondition(20, distanceMeasure);
	Turn_Angle150Condition =				new DirectionCondition(328, distanceMeasure);
	Turn_Avoid_Angle150Condition =			new DirectionCondition(0, distanceMeasure);
	Turn_AngleMinus150Condition =			new DirectionCondition(-315, distanceMeasure);
	Turn_Avoid_AngleMinus150Condition =		new DirectionCondition(0, distanceMeasure);

	Correction_ShortStraightCondition =		new DistanceCondition(90, distanceMeasure);
	Detection_LineCondition =				new LineCondition(15, brightness);
	Short_AdvantageCondition =				new DistanceCondition(60, distanceMeasure);
	Detection_Line_LeftCondition =			new LineCondition(15, brightness);
	Detection_Line_RightCondition =			new LineCondition(15, brightness);

	Station_LineTraceCondition =			new DistanceCondition(80, distanceMeasure);
	Station_PBPlaceCondition =				new PBPlaceDetectionCondition(&colorSensor, true, calibration);
	Station_BackCondition =					new DistanceCondition(-190, distanceMeasure);
	
	TurnDisCondition =						new DirectionCondition(85,distanceMeasure);
	Goparking_Find_LineDisCondition =		new LineCondition(-18,brightness);
	Goparking_OutDisCondition =				new DistanceCondition(30,distanceMeasure);
	Goparking_Turn_LineDisCondition =		new LineCondition(-18,brightness);
	Goparking_TraceDisCondition =			new DistanceCondition(320,distanceMeasure);
	Letsparking_TurnDisCondition =			new DirectionCondition(-85,distanceMeasure);
	Letsparking_MoveDisCondition =			new DistanceCondition(190, distanceMeasure);
	Letsparking_LastturnDisCondition =		new DirectionCondition(90,distanceMeasure);
	Letsparking_Find_GreenDisCondition =	new LineCondition(-18,brightness);
	Letsparking_GooutDisCondition =			new DistanceCondition(350, distanceMeasure);
	Letsparking_Find_LineDisCondition =		new LineCondition(-18,brightness);
	Letsparking_MiliDisCondition =			new DistanceCondition(50,distanceMeasure);
	Letsparking_FastDisCondition =			new DistanceCondition(700,distanceMeasure);

	Final_StopCondition =					new TimeDetectionCondition(2000, &clock);

	//------------------すべてのAreaの走行状態を設定------------------//
	lineMode =								new Mode(35, &armMotor, &clock);
	WatchBlockMode =						new Mode(90, &armMotor, &clock);
	CatchMode =								new Mode(5, &armMotor, &clock);
	GetMode =								new Mode(180, &armMotor, &clock);
	search1Mode =							new Mode(70, &armMotor, &clock);
	search2Mode =							new Mode(85, &armMotor, &clock);

	//RunMethod
	Start_StopRun =							new InstructionMethod(0, 0, &leftMotor, &rightMotor);

	First_SlowRun =							new LineTraceMethod(80, 50, 1, 0, brightness, pid_R_First, &leftMotor, &rightMotor);
	First_FastRun =							new LineTraceMethod(100, 85, 1, 0, brightness, pid_R_First, &leftMotor, &rightMotor);
	First_CircleRun =						new LineTraceMethod(80, 160, 1, -4, brightness, pid_Curve, &leftMotor, &rightMotor);
	First_CurveRun =						new LineTraceMethod(80, 120, 1, -9, brightness, pid_Curve, &leftMotor, &rightMotor);
	Second_CurveRun =						new LineTraceMethod(80, 130, 1, -2, brightness, pid_Curve, &leftMotor, &rightMotor);
	Second_UneriRun =						new LineTraceMethod(70, 155, 1, 1, brightness, pid_Uneri, &leftMotor, &rightMotor);
	Second_Uneri2Run =						new LineTraceMethod(85, 150, 1, -4, brightness, pid_nameraka, &leftMotor, &rightMotor);
	Second_FastRun =						new LineTraceMethod(100, 100, 1, -7, brightness, pid_R_First, &leftMotor, &rightMotor);
	Intogame_TurnRun =						new InstructionMethod(20, 10, &leftMotor, &rightMotor);
	Intogame_OverlineRun =					new InstructionMethod(30, 30, &leftMotor, &rightMotor);
	Intogame_FindturnRun =					new InstructionMethod(10, 20, &leftMotor, &rightMotor);
	Intogame_GoRun =						new LineTraceMethod(70, 150, 0, 0, brightness, pid_Uneri, &leftMotor, &rightMotor);
	
	LineTraceRun =							new LineTraceMethod(20, 350, 0, 0, brightness, pid_lowspeedStraight, &leftMotor, &rightMotor);
	Detection_PBPlaceRun =					new LineTraceMethod(20, 10, 0, 0, brightness, pid_lowspeedStraight, &leftMotor, &rightMotor);
	Correction_middleRun =					new InstructionMethod(20, 20, &leftMotor, &rightMotor);
	Direction_Change_LRun =					new InstructionMethod(-20, 20, &leftMotor, &rightMotor);
	Direction_Change_RRun =					new InstructionMethod(20, -20, &leftMotor, &rightMotor);

	Turn_Avoid_Angle0Run =					new InstructionMethod(13, 25, &leftMotor, &rightMotor);
	Turn_Angle30Run =						new InstructionMethod(20, -20, &leftMotor, &rightMotor);
	Turn_Avoid_Angle30Run =					new InstructionMethod(13, 25, &leftMotor, &rightMotor);
	Turn_AngleMinus30Run =					new InstructionMethod(-20, 20, &leftMotor, &rightMotor);
	Turn_Avoid_AngleMinus30Run =			new InstructionMethod(25, 13, &leftMotor, &rightMotor);
	Turn_Angle45Run =						new InstructionMethod(20, -20, &leftMotor, &rightMotor);
	Turn_Avoid_Angle45Run =					new InstructionMethod(13, 25, &leftMotor, &rightMotor);
	Turn_AngleMinus45Run =					new InstructionMethod(-20, 20, &leftMotor, &rightMotor);
	Turn_Avoid_AngleMinus45Run =			new InstructionMethod(25, 13, &leftMotor, &rightMotor);
	Turn_Angle60Run =						new InstructionMethod(20, -20, &leftMotor, &rightMotor);
	Turn_Avoid_Angle60Run =					new InstructionMethod(13, 25, &leftMotor, &rightMotor);
	Turn_AngleMinus60Run =					new InstructionMethod(-20, 20, &leftMotor, &rightMotor);
	Turn_Avoid_AngleMinus60Run =			new InstructionMethod(25, 13, &leftMotor, &rightMotor);
	Turn_Angle90Run =						new InstructionMethod(20, -20, &leftMotor, &rightMotor);
	Turn_Avoid_Angle90Run =					new InstructionMethod(13, 25, &leftMotor, &rightMotor);
	Turn_AngleMinus90Run =					new InstructionMethod(-20, 20, &leftMotor, &rightMotor);
	Turn_Avoid_AngleMinus90Run =			new InstructionMethod(25, 13, &leftMotor, &rightMotor);
	Turn_Angle105Run =						new InstructionMethod(20, -20, &leftMotor, &rightMotor);
	Turn_Avoid_Angle105Run =				new InstructionMethod(13, 25, &leftMotor, &rightMotor);
	Turn_AngleMinus105Run =					new InstructionMethod(-20, 20, &leftMotor, &rightMotor);
	Turn_Avoid_AngleMinus105Run =			new InstructionMethod(25, 13, &leftMotor, &rightMotor);
	Turn_Angle120Run =						new InstructionMethod(20, -20, &leftMotor, &rightMotor);
	Turn_Avoid_Angle120Run =				new InstructionMethod(13, 25, &leftMotor, &rightMotor);
	Turn_AngleMinus120Run =					new InstructionMethod(-20, 20, &leftMotor, &rightMotor);
	Turn_Avoid_AngleMinus120Run =			new InstructionMethod(25, 13, &leftMotor, &rightMotor);
	Turn_Angle135Run =						new InstructionMethod(20, -20, &leftMotor, &rightMotor);
	Turn_Avoid_Angle135Run =				new InstructionMethod(13, 25, &leftMotor, &rightMotor);
	Turn_AngleMinus135Run =					new InstructionMethod(-20, 20, &leftMotor, &rightMotor);
	Turn_Avoid_AngleMinus135Run =			new InstructionMethod(25, 13, &leftMotor, &rightMotor);
	Turn_Angle150Run =						new InstructionMethod(10, -10, &leftMotor, &rightMotor);
	Turn_Avoid_Angle150Run =				new InstructionMethod(10, -10, &leftMotor, &rightMotor);
	Turn_AngleMinus150Run =					new InstructionMethod(-10, 10, &leftMotor, &rightMotor);
	Turn_Avoid_AngleMinus150Run =			new InstructionMethod(-10, 10, &leftMotor, &rightMotor);

	Correction_ShortStraightRun =			new InstructionMethod(20, 20, &leftMotor, &rightMotor);
	Detection_LineRun =						new InstructionMethod(20, 20, &leftMotor, &rightMotor);
	Short_AdvantageRun =					new InstructionMethod(20, 20, &leftMotor, &rightMotor);
	Detection_Line_LeftRun =				new InstructionMethod(-15, 15, &leftMotor, &rightMotor);
	Detection_Line_RightRun =				new InstructionMethod(15, -15, &leftMotor, &rightMotor);

	Station_LineTraceRun =					new LineTraceMethod(20, 350, 0, 0, brightness, pid_lowspeedStraight, &leftMotor, &rightMotor);
	Station_PBPlaceRun =					new LineTraceMethod(20, 10, 0, 0, brightness, pid_lowspeedStraight, &leftMotor, &rightMotor);
	Station_BackRun =						new InstructionMethod(-20, -20, &leftMotor, &rightMotor);
	
	TurnRun =								new InstructionMethod(30, -30, &leftMotor, &rightMotor);
	Goparking_Find_LineRun =				new InstructionMethod(50, 50, &leftMotor, &rightMotor);
	Goparking_OutRun =						new InstructionMethod(20, 20, &leftMotor, &rightMotor);
	Goparking_Turn_LineRun =				new InstructionMethod(-20, 20, &leftMotor, &rightMotor);
	Goparking_TraceRun =					new LineTraceMethod(40, 120, 0, -4, brightness, pid_Curve,&leftMotor, &rightMotor);
	Letsparking_TurnRun =					new InstructionMethod(-30, 30, &leftMotor, &rightMotor);
	Letsparking_MoveRun =					new InstructionMethod(30, 30, &leftMotor, &rightMotor);
	Letsparking_LastturnRun =				new InstructionMethod(20, -20, &leftMotor, &rightMotor);
	Letsparking_Find_GreenRun =				new InstructionMethod(40, 40, &leftMotor, &rightMotor);
	Letsparking_GooutRun =					new InstructionMethod(40, 40, &leftMotor, &rightMotor);
	Letsparking_Find_LineRun =				new InstructionMethod(40, 40, &leftMotor, &rightMotor);
	Letsparking_MiliRun =					new InstructionMethod(20, 20, &leftMotor, &rightMotor);
	Letsparking_FastRun =					new LineTraceMethod(80, 100, 1, 1, brightness, pid_Uneri, &leftMotor, &rightMotor);
	
	Final_StopRun =							new InstructionMethod(0, 0, &leftMotor, &rightMotor);

	//RunBlock
	Start_StopBlock =						new RunBlock(0, Start_StopDisCondition, Start_StopRun, distanceMeasure, communication, lineMode);

	First_SlowBlock =						new RunBlock(0, First_SlowDisCondition, First_SlowRun, distanceMeasure, communication, lineMode);
	First_FastBlock =						new RunBlock(0, First_FastDisCondition, First_FastRun, distanceMeasure, communication, lineMode);
	First_CircleBlock =						new RunBlock(0, First_CircleDisCondition, First_CircleRun, distanceMeasure, communication, lineMode);
	First_CurveBlock =						new RunBlock(0, First_CurveDisCondition, First_CurveRun, distanceMeasure, communication, lineMode);
	Second_CurveBlock =						new RunBlock(0, Second_CurveDisCondition, Second_CurveRun, distanceMeasure, communication, lineMode);
	Second_UneriBlock =						new RunBlock(0, Second_UneriDisCondition, Second_UneriRun, distanceMeasure, communication, lineMode);
	Second_Uneri2Block =					new RunBlock(0, Second_Uneri2DisCondition, Second_Uneri2Run, distanceMeasure, communication, lineMode);
	Second_FastBlock =						new RunBlock(0, Second_FastDisCondition, Second_FastRun, distanceMeasure, communication, lineMode);
	Intogame_TurnBlock =					new RunBlock(0, Intogame_TurnDisCondition, Intogame_TurnRun, distanceMeasure, communication, lineMode);
	Intogame_OverlineBlock =				new RunBlock(0, Intogame_OverlineDisCondition, Intogame_OverlineRun, distanceMeasure, communication, lineMode);
	Intogame_FindturnBlock =				new RunBlock(0, Intogame_FindturnDisCondition, Intogame_FindturnRun, distanceMeasure, communication, lineMode);
	Intogame_GoBlock =						new RunBlock(0, Intogame_GoDisCondition, Intogame_GoRun, distanceMeasure, communication, lineMode);

	LineTraceBlock =						new CrossRunBlock(0, LineTraceCondition, LineTraceRun, distanceMeasure, communication, lineMode, dynamic_cast<DynamicRunArea*>(Left_FieldMovingArea), blocklayscenario);
	Detection_PBPlaceBlock =				new RunBlock(34, Detection_PBPlaceCondition, Detection_PBPlaceRun, distanceMeasure, communication, lineMode);
	Correction_middleBlock =				new RunBlock(34, Correction_middleCondition, Correction_middleRun, distanceMeasure, communication, lineMode);
	Direction_Change_LBlock=				new RunBlock(36, Direction_Change_LCondition, Direction_Change_LRun, distanceMeasure, communication, lineMode);//ブロック有で反時計回り
	Direction_Change_RBlock =				new RunBlock(37, Direction_Change_RCondition, Direction_Change_RRun, distanceMeasure, communication, lineMode);//ブロック有で時計回り

	Turn_Avoid_Angle0Block =				new RunBlock(1, Turn_Avoid_Angle0Condition, Turn_Avoid_Angle0Run, distanceMeasure, communication, lineMode);
	Turn_Angle30Block =						new RunBlock(2, Turn_Angle30Condition, Turn_Angle30Run, distanceMeasure, communication, lineMode);
	Turn_Avoid_Angle30Block =				new RunBlock(3, Turn_Avoid_Angle30Condition, Turn_Avoid_Angle30Run, distanceMeasure, communication, lineMode);
	Turn_AngleMinus30Block =				new RunBlock(4, Turn_AngleMinus30Condition, Turn_AngleMinus30Run, distanceMeasure, communication, lineMode);
	Turn_Avoid_AngleMinus30Block =			new RunBlock(5, Turn_Avoid_AngleMinus30Condition, Turn_Avoid_AngleMinus30Run, distanceMeasure, communication, lineMode);
	Turn_Angle45Block =						new RunBlock(6, Turn_Angle45Condition, Turn_Angle45Run, distanceMeasure, communication, lineMode);
	Turn_Avoid_Angle45Block =				new RunBlock(7, Turn_Avoid_Angle45Condition, Turn_Avoid_Angle45Run, distanceMeasure, communication, lineMode);
	Turn_AngleMinus45Block =				new RunBlock(8, Turn_AngleMinus45Condition, Turn_AngleMinus45Run, distanceMeasure, communication, lineMode);
	Turn_Avoid_AngleMinus45Block =			new RunBlock(9, Turn_Avoid_AngleMinus45Condition, Turn_Avoid_AngleMinus45Run, distanceMeasure, communication, lineMode);
	Turn_Angle60Block =						new RunBlock(10, Turn_Angle60Condition, Turn_Angle60Run, distanceMeasure, communication, lineMode);
	Turn_Avoid_Angle60Block =				new RunBlock(11, Turn_Avoid_Angle60Condition, Turn_Avoid_Angle60Run, distanceMeasure, communication, lineMode);
	Turn_AngleMinus60Block =				new RunBlock(12, Turn_AngleMinus60Condition, Turn_AngleMinus60Run, distanceMeasure, communication, lineMode);
	Turn_Avoid_AngleMinus60Block =			new RunBlock(13, Turn_Avoid_AngleMinus60Condition, Turn_Avoid_AngleMinus60Run, distanceMeasure, communication, lineMode);
	Turn_Angle90Block =						new RunBlock(14, Turn_Angle90Condition, Turn_Angle90Run, distanceMeasure, communication, lineMode);
	Turn_Avoid_Angle90Block =				new RunBlock(15, Turn_Avoid_Angle90Condition, Turn_Avoid_Angle90Run, distanceMeasure, communication, lineMode);
	Turn_AngleMinus90Block =				new RunBlock(16, Turn_AngleMinus90Condition, Turn_AngleMinus90Run, distanceMeasure, communication, lineMode);
	Turn_Avoid_AngleMinus90Block =			new RunBlock(17, Turn_Avoid_AngleMinus90Condition, Turn_Avoid_AngleMinus90Run, distanceMeasure, communication, lineMode);
	Turn_Angle105Block =					new RunBlock(18, Turn_Angle105Condition, Turn_Angle105Run, distanceMeasure, communication, lineMode);
	Turn_Avoid_Angle105Block =				new RunBlock(19, Turn_Avoid_Angle105Condition, Turn_Avoid_Angle105Run, distanceMeasure, communication, lineMode);
	Turn_AngleMinus105Block =				new RunBlock(20, Turn_AngleMinus105Condition, Turn_AngleMinus105Run, distanceMeasure, communication, lineMode);
	Turn_Avoid_AngleMinus105Block =			new RunBlock(21, Turn_Avoid_AngleMinus105Condition, Turn_Avoid_AngleMinus105Run, distanceMeasure, communication, lineMode);
	Turn_Angle120Block =					new RunBlock(22, Turn_Angle120Condition, Turn_Angle120Run, distanceMeasure, communication, lineMode);
	Turn_Avoid_Angle120Block =				new RunBlock(23, Turn_Avoid_Angle120Condition, Turn_Avoid_Angle120Run, distanceMeasure, communication, lineMode);
	Turn_AngleMinus120Block =				new RunBlock(24, Turn_AngleMinus120Condition, Turn_AngleMinus120Run, distanceMeasure, communication, lineMode);
	Turn_Avoid_AngleMinus120Block =			new RunBlock(25, Turn_Avoid_AngleMinus120Condition, Turn_Avoid_AngleMinus120Run, distanceMeasure, communication, lineMode);
	Turn_Angle135Block =					new RunBlock(26, Turn_Angle135Condition, Turn_Angle135Run, distanceMeasure, communication, lineMode);
	Turn_Avoid_Angle135Block =				new RunBlock(27, Turn_Avoid_Angle135Condition, Turn_Avoid_Angle135Run, distanceMeasure, communication, lineMode);
	Turn_AngleMinus135Block =				new RunBlock(28, Turn_AngleMinus135Condition, Turn_AngleMinus135Run, distanceMeasure, communication, lineMode);
	Turn_Avoid_AngleMinus135Block =			new RunBlock(29, Turn_Avoid_AngleMinus135Condition, Turn_Avoid_AngleMinus135Run, distanceMeasure, communication, lineMode);
	Turn_Angle150Block =					new RunBlock(30, Turn_Angle150Condition, Turn_Angle150Run, distanceMeasure, communication, lineMode);
	Turn_Avoid_Angle150Block =				new RunBlock(31, Turn_Avoid_Angle150Condition, Turn_Avoid_Angle150Run, distanceMeasure, communication, lineMode);
	Turn_AngleMinus150Block =				new RunBlock(32, Turn_AngleMinus150Condition, Turn_AngleMinus150Run, distanceMeasure, communication, lineMode);
	Turn_Avoid_AngleMinus150Block =			new RunBlock(33, Turn_Avoid_AngleMinus150Condition, Turn_Avoid_AngleMinus150Run, distanceMeasure, communication, lineMode);
	
	Correction_ShortStraightBlock =			new RunBlock(34, Correction_ShortStraightCondition, Correction_ShortStraightRun, distanceMeasure, communication, lineMode);//ブロック無し
	Detection_LineBlock =					new RunBlock(35, Detection_LineCondition, Detection_LineRun, distanceMeasure, communication, lineMode);//ブロック有
	Short_AdvantageBlock =					new RunBlock(35, Short_AdvantageCondition, Short_AdvantageRun, distanceMeasure, communication, lineMode);//ブロック有
	Detection_Line_LeftBlock =				new RunBlock(38, Detection_Line_LeftCondition, Detection_Line_LeftRun, distanceMeasure, communication, lineMode);//反時計回り
	Detection_Line_RightBlock =				new RunBlock(39, Detection_Line_RightCondition, Detection_Line_RightRun, distanceMeasure, communication, lineMode);//時計回り
	
	Station_LineTraceBlock =				new RunBlock(40, Station_LineTraceCondition, Station_LineTraceRun, distanceMeasure, communication, lineMode);
	Station_PBPlaceBlock =					new RunBlock(40, Station_PBPlaceCondition, Station_PBPlaceRun, distanceMeasure, communication, lineMode);
	Station_BackBlock =						new RunBlock(40, Station_BackCondition, Station_BackRun, distanceMeasure, communication, lineMode);

	TurnBlock =								new RunBlock(0, TurnDisCondition, TurnRun, distanceMeasure, communication, lineMode);
	Goparking_Find_LineBlock =				new RunBlock(0, Goparking_Find_LineDisCondition, Goparking_Find_LineRun, distanceMeasure, communication, lineMode);
	Goparking_OutBlock =					new RunBlock(0, Goparking_OutDisCondition, Goparking_OutRun, distanceMeasure, communication, lineMode);
	Goparking_Turn_LineBlock =				new RunBlock(0, Goparking_Turn_LineDisCondition, Goparking_Turn_LineRun, distanceMeasure, communication, lineMode);
	Goparking_TraceBlock =					new RunBlock(0, Goparking_TraceDisCondition, Goparking_TraceRun, distanceMeasure, communication, lineMode);
	Letsparking_TurnBlock =					new RunBlock(0,Letsparking_TurnDisCondition, Letsparking_TurnRun, distanceMeasure, communication, lineMode);
	Letsparking_MoveBlock =					new RunBlock(0,Letsparking_MoveDisCondition, Letsparking_MoveRun, distanceMeasure, communication, lineMode);
	Letsparking_LastturnBlock =				new RunBlock(0,Letsparking_LastturnDisCondition, Letsparking_LastturnRun, distanceMeasure, communication, lineMode);
	Letsparking_Find_GreenBlock =			new RunBlock(0,Letsparking_Find_GreenDisCondition, Letsparking_Find_GreenRun, distanceMeasure, communication, lineMode);
	Letsparking_GooutBlock =				new RunBlock(0,Letsparking_GooutDisCondition, Letsparking_GooutRun, distanceMeasure, communication, lineMode);
	Letsparking_Find_LineBlock =			new RunBlock(0,Letsparking_Find_LineDisCondition, Letsparking_Find_LineRun, distanceMeasure, communication, lineMode);
	Letsparking_MiliBlock =					new RunBlock(0,Letsparking_MiliDisCondition, Letsparking_MiliRun, distanceMeasure, communication, lineMode);
	Letsparking_FastBlock =					new RunBlock(0,Letsparking_FastDisCondition, Letsparking_FastRun, distanceMeasure, communication, lineMode);
		
	Final_StopBlock =						new RunBlock(0, Final_StopCondition, Final_StopRun, distanceMeasure, communication, lineMode);

	//------------------モーターのブレーキ設定------------------//
	armMotor.setBrake(false);		// Aモータフロートモード関数：ステアリング
	leftMotor.setBrake(false);		// Bモータフロートモード関数：左モータ
	rightMotor.setBrake(false);		// Cモータフロートモード関数：右モータ
}
static void user_system_destroy() {
	delete  sonarMeter;
	delete  brightness;
	delete	calibration;
	delete	distanceMeasure;
	delete	logdata;

	//
	delete  First_SlowDisCondition;
	delete	First_FastDisCondition;
	delete	First_CircleDisCondition;
	delete	First_CurveDisCondition;
	delete	Second_CurveDisCondition;
	delete	Second_UneriDisCondition;
	delete	Second_Uneri2DisCondition;
	delete	Second_FastDisCondition;
	delete	Intogame_TurnDisCondition;
	delete	Intogame_OverlineDisCondition;
	delete	Intogame_FindturnDisCondition;
	delete	Intogame_GoDisCondition;
	
	delete  LineTraceCondition;
	delete  Detection_PBPlaceCondition;
	delete  Correction_middleCondition;
	delete  Direction_Change_LCondition;
	delete	Direction_Change_RCondition;

	delete  Turn_Avoid_Angle0Condition;
	delete  Turn_Angle30Condition;
	delete  Turn_Avoid_Angle30Condition;
	delete  Turn_AngleMinus30Condition;
	delete  Turn_Avoid_AngleMinus30Condition;
	delete  Turn_Angle45Condition;
	delete  Turn_Avoid_Angle45Condition;
	delete  Turn_AngleMinus45Condition;
	delete  Turn_Avoid_AngleMinus45Condition;
	delete  Turn_Angle60Condition;
	delete  Turn_Avoid_Angle60Condition;
	delete  Turn_AngleMinus60Condition;
	delete  Turn_Avoid_AngleMinus60Condition;
	delete  Turn_Angle90Condition;
	delete  Turn_Avoid_Angle90Condition;
	delete  Turn_AngleMinus90Condition;
	delete  Turn_Avoid_AngleMinus90Condition;
	delete  Turn_Angle105Condition;
	delete  Turn_Avoid_Angle105Condition;
	delete  Turn_AngleMinus105Condition;
	delete  Turn_Avoid_AngleMinus105Condition;
	delete  Turn_Angle120Condition;
	delete  Turn_Avoid_Angle120Condition;
	delete  Turn_AngleMinus120Condition;
	delete  Turn_Avoid_AngleMinus120Condition;
	delete  Turn_Angle135Condition;
	delete  Turn_Avoid_Angle135Condition;
	delete  Turn_AngleMinus135Condition;
	delete  Turn_Avoid_AngleMinus135Condition;
	delete  Turn_Angle150Condition;
	delete  Turn_Avoid_Angle150Condition;
	delete  Turn_AngleMinus150Condition;
	delete  Turn_Avoid_AngleMinus150Condition;

	delete  Correction_ShortStraightCondition;
	delete	Detection_LineCondition;
	delete	Short_AdvantageCondition;
	delete  Detection_Line_LeftCondition;
	delete  Detection_Line_RightCondition;

	delete  Station_LineTraceCondition;
	delete	Station_PBPlaceCondition;
	delete	Station_BackCondition;

	delete  Goparking_Find_LineDisCondition;
	delete	Goparking_OutDisCondition;
	delete	Goparking_Turn_LineDisCondition;
	delete	Goparking_TraceDisCondition;
	delete	Letsparking_TurnDisCondition;
	delete	Letsparking_MoveDisCondition;
	delete	Letsparking_LastturnDisCondition;
	delete	Letsparking_Find_GreenDisCondition;
	delete	Letsparking_GooutDisCondition;
	delete	Letsparking_Find_LineDisCondition;
	delete	Letsparking_MiliDisCondition;
	delete	Letsparking_FastDisCondition;

	delete Final_StopCondition;
	
	//
	delete  First_SlowRun;
	delete	First_FastRun;
	delete	First_CircleRun;
	delete	First_CurveRun;
	delete	Second_CurveRun;
	delete	Second_UneriRun;
	delete	Second_Uneri2Run;
	delete	Second_FastRun;
	delete	Intogame_TurnRun;
	delete	Intogame_OverlineRun;
	delete	Intogame_FindturnRun;
	delete	Intogame_GoRun;

	delete  LineTraceRun;
	delete  Detection_PBPlaceRun;
	delete  Correction_middleRun;
	delete  Direction_Change_LRun;
	delete  Direction_Change_RRun;

	delete  Turn_Avoid_Angle0Run;
	delete  Turn_Angle30Run;
	delete  Turn_Avoid_Angle30Run;
	delete  Turn_AngleMinus30Run;
	delete  Turn_Avoid_AngleMinus30Run;
	delete  Turn_Angle45Run;
	delete  Turn_Avoid_Angle45Run;
	delete  Turn_AngleMinus45Run;
	delete  Turn_Avoid_AngleMinus45Run;
	delete  Turn_Angle60Run;
	delete  Turn_Avoid_Angle60Run;
	delete  Turn_AngleMinus60Run;
	delete  Turn_Avoid_AngleMinus60Run;
	delete  Turn_Angle90Run;
	delete  Turn_Avoid_Angle90Run;
	delete  Turn_AngleMinus90Run;
	delete  Turn_Avoid_AngleMinus90Run;
	delete  Turn_Angle105Run;
	delete  Turn_Avoid_Angle105Run;
	delete  Turn_AngleMinus105Run;
	delete  Turn_Avoid_AngleMinus105Run;
	delete  Turn_Angle120Run;
	delete  Turn_Avoid_Angle120Run;
	delete  Turn_AngleMinus120Run;
	delete  Turn_Avoid_AngleMinus120Run;
	delete  Turn_Angle135Run;
	delete  Turn_Avoid_Angle135Run;
	delete  Turn_AngleMinus135Run;
	delete  Turn_Avoid_AngleMinus135Run;
	delete  Turn_Angle150Run;
	delete  Turn_Avoid_Angle150Run;
	delete  Turn_AngleMinus150Run;
	delete  Turn_Avoid_AngleMinus150Run;

	delete  Correction_ShortStraightRun;
	delete	Detection_LineRun;
	delete	Short_AdvantageRun;
	delete  Detection_Line_LeftRun;
	delete  Detection_Line_RightRun;

	delete	Station_LineTraceRun;
	delete	Station_PBPlaceRun;
	delete	Station_BackRun;

	delete  Goparking_Find_LineRun;
	delete	Goparking_OutRun;
	delete	Goparking_Turn_LineRun;
	delete	Goparking_TraceRun;
	delete	Letsparking_TurnRun;
	delete	Letsparking_MoveRun;
	delete	Letsparking_LastturnRun;
	delete	Letsparking_Find_GreenRun;
	delete	Letsparking_GooutRun;
	delete	Letsparking_Find_LineRun;
	delete	Letsparking_MiliRun;
	delete	Letsparking_FastRun;

	delete  Final_StopRun;

//
	delete  First_SlowBlock;
	delete	First_FastBlock;
	delete	First_CircleBlock;
	delete	First_CurveBlock;
	delete	Second_CurveBlock;
	delete	Second_UneriBlock;
	delete	Second_Uneri2Block;
	delete	Second_FastBlock;
	delete	Intogame_TurnBlock;
	delete	Intogame_OverlineBlock;
	delete	Intogame_FindturnBlock;
	delete	Intogame_GoBlock;

	delete  LineTraceBlock;
	delete  Detection_PBPlaceBlock;
	delete  Correction_middleBlock;
	delete  Direction_Change_LBlock;
	delete  Direction_Change_RBlock;

	delete  Turn_Avoid_Angle0Block;
	delete  Turn_Angle30Block;
	delete  Turn_Avoid_Angle30Block;
	delete  Turn_AngleMinus30Block;
	delete  Turn_Avoid_AngleMinus30Block;
	delete  Turn_Angle45Block;
	delete  Turn_Avoid_Angle45Block;
	delete  Turn_AngleMinus45Block;
	delete  Turn_Avoid_AngleMinus45Block;
	delete  Turn_Angle60Block;
	delete  Turn_Avoid_Angle60Block;
	delete  Turn_AngleMinus60Block;
	delete  Turn_Avoid_AngleMinus60Block;
	delete  Turn_Angle90Block;
	delete  Turn_Avoid_Angle90Block;
	delete  Turn_AngleMinus90Block;
	delete  Turn_Avoid_AngleMinus90Block;
	delete  Turn_Angle105Block;
	delete  Turn_Avoid_Angle105Block;
	delete  Turn_AngleMinus105Block;
	delete  Turn_Avoid_AngleMinus105Block;
	delete  Turn_Angle120Block;
	delete  Turn_Avoid_Angle120Block;
	delete  Turn_AngleMinus120Block;
	delete  Turn_Avoid_AngleMinus120Block;
	delete  Turn_Angle135Block;
	delete  Turn_Avoid_Angle135Block;
	delete  Turn_AngleMinus135Block;
	delete  Turn_Avoid_AngleMinus135Block;
	delete  Turn_Angle150Block;
	delete  Turn_Avoid_Angle150Block;
	delete  Turn_AngleMinus150Block;
	delete  Turn_Avoid_AngleMinus150Block;

	delete  Correction_ShortStraightBlock;
	delete	Detection_LineBlock;
	delete	Short_AdvantageBlock;
	delete  Detection_Line_LeftBlock;
	delete  Detection_Line_RightBlock;

	delete	Station_LineTraceBlock;
	delete	Station_PBPlaceBlock;
	delete	Station_BackBlock;

	delete  Goparking_Find_LineBlock;
	delete	Goparking_OutBlock;
	delete	Goparking_Turn_LineBlock;
	delete	Goparking_TraceBlock;
	delete	Letsparking_TurnBlock;
	delete	Letsparking_MoveBlock;
	delete	Letsparking_LastturnBlock;
	delete	Letsparking_Find_GreenBlock;
	delete	Letsparking_GooutBlock;
	delete	Letsparking_Find_LineBlock;
	delete	Letsparking_MiliBlock;
	delete	Letsparking_FastBlock;

	delete  Final_StopBlock;

	delete  FirstRunArea;
	delete  Left_FieldMovingArea;
	delete  ParkingArea;
	delete  StationArea;
	delete  BLArea;
	
	delete	sound;
	delete	speedoMeter;
	delete	communication;
	delete  lineMode;
}

void ev3_cyc_run(intptr_t exinf) {
	act_tsk(RUN_TASK);
}
void ev3_cyc_communication(intptr_t exinf) {
	act_tsk(COMMUNICATION_TASK);
}

void ev3_cyc_emergencystop(intptr_t exinf) {
	act_tsk(EMERGENCYSTOP_TASK);
}

//走行タスク（4ミリ秒周期）
void main_task(intptr_t unused)
{
	user_system_create();  // センサやモータの初期化処理

						   // Open Bluetooth file 
	bt = ev3_serial_open_file(EV3_SERIAL_BT);
	assert(bt != NULL);

	//***********設定した走行エリアや走行区画を走行コースや走行エリアが所有するリストに追加する（走行の順番を決める）***************************/
	/**走行エリアの順番の設定**/


	leftCourse->addRunArea(FirstRunArea);
	leftCourse->addRunArea(BLArea);
	leftCourse->addRunArea(ParkingArea);
	//

	//FirstRunArea->addBlock(Start_StopBlock);

	FirstRunArea->addBlock(First_SlowBlock);
	FirstRunArea->addBlock(First_FastBlock);
	FirstRunArea->addBlock(First_CircleBlock);
	FirstRunArea->addBlock(First_CurveBlock);
	FirstRunArea->addBlock(Second_CurveBlock);
	FirstRunArea->addBlock(Second_UneriBlock);
	FirstRunArea->addBlock(Second_Uneri2Block);
	FirstRunArea->addBlock(Second_FastBlock);
	FirstRunArea->addBlock(Intogame_TurnBlock);
	FirstRunArea->addBlock(Intogame_OverlineBlock);
	FirstRunArea->addBlock(Intogame_FindturnBlock);
	FirstRunArea->addBlock(Intogame_GoBlock);
	//*****************************************************//

	Left_FieldMovingArea->addBlock(LineTraceBlock);
	Left_FieldMovingArea->addBlock(Detection_PBPlaceBlock);
	Left_FieldMovingArea->addBlock(Correction_middleBlock);
	Left_FieldMovingArea->addBlock(Direction_Change_LBlock);
	Left_FieldMovingArea->addBlock(Direction_Change_RBlock);

	Left_FieldMovingArea->addBlock(Turn_Avoid_Angle0Block);
	Left_FieldMovingArea->addBlock(Turn_Avoid_Angle30Block);
	Left_FieldMovingArea->addBlock(Turn_AngleMinus30Block);
	Left_FieldMovingArea->addBlock(Turn_Avoid_AngleMinus30Block);
	Left_FieldMovingArea->addBlock(Turn_Angle45Block);
	Left_FieldMovingArea->addBlock(Turn_Avoid_Angle45Block);
	Left_FieldMovingArea->addBlock(Turn_AngleMinus45Block);
	Left_FieldMovingArea->addBlock(Turn_Avoid_AngleMinus45Block);
	Left_FieldMovingArea->addBlock(Turn_Angle60Block);
	Left_FieldMovingArea->addBlock(Turn_Avoid_Angle60Block);
	Left_FieldMovingArea->addBlock(Turn_AngleMinus60Block);
	Left_FieldMovingArea->addBlock(Turn_Avoid_AngleMinus60Block);
	Left_FieldMovingArea->addBlock(Turn_Angle90Block);
	Left_FieldMovingArea->addBlock(Turn_Avoid_Angle90Block);
	Left_FieldMovingArea->addBlock(Turn_AngleMinus90Block);
	Left_FieldMovingArea->addBlock(Turn_Avoid_AngleMinus90Block);
	Left_FieldMovingArea->addBlock(Turn_Angle105Block);
	Left_FieldMovingArea->addBlock(Turn_Avoid_Angle105Block);
	Left_FieldMovingArea->addBlock(Turn_AngleMinus105Block);
	Left_FieldMovingArea->addBlock(Turn_Avoid_AngleMinus105Block);
	Left_FieldMovingArea->addBlock(Turn_Angle120Block);
	Left_FieldMovingArea->addBlock(Turn_Avoid_Angle120Block);
	Left_FieldMovingArea->addBlock(Turn_AngleMinus120Block);
	Left_FieldMovingArea->addBlock(Turn_Avoid_AngleMinus120Block);
	Left_FieldMovingArea->addBlock(Turn_Angle135Block);
	Left_FieldMovingArea->addBlock(Turn_Avoid_Angle135Block);
	Left_FieldMovingArea->addBlock(Turn_AngleMinus135Block);
	Left_FieldMovingArea->addBlock(Turn_Avoid_AngleMinus135Block);
	Left_FieldMovingArea->addBlock(Turn_Angle150Block);
	Left_FieldMovingArea->addBlock(Turn_Avoid_Angle150Block);
	Left_FieldMovingArea->addBlock(Turn_AngleMinus150Block);
	Left_FieldMovingArea->addBlock(Turn_Avoid_AngleMinus150Block);

	Left_FieldMovingArea->addBlock(Correction_ShortStraightBlock);
	Left_FieldMovingArea->addBlock(Detection_LineBlock);
	Left_FieldMovingArea->addBlock(Short_AdvantageBlock);
	Left_FieldMovingArea->addBlock(Detection_Line_LeftBlock);
	Left_FieldMovingArea->addBlock(Detection_Line_RightBlock);

	Left_FieldMovingArea->addBlock(Station_LineTraceBlock);//置く
	Left_FieldMovingArea->addBlock(Station_PBPlaceBlock);
	Left_FieldMovingArea->addBlock(Station_BackBlock);

	//****************************************************//

	ParkingArea->addBlock(Goparking_Find_LineBlock);
	ParkingArea->addBlock(Goparking_OutBlock);
	ParkingArea->addBlock(Goparking_Turn_LineBlock);
	ParkingArea->addBlock(Goparking_TraceBlock);
	ParkingArea->addBlock(Letsparking_TurnBlock);
	ParkingArea->addBlock(Letsparking_MoveBlock);
	ParkingArea->addBlock(Letsparking_LastturnBlock);

	ParkingArea->addBlock(Final_StopBlock);


	ev3_speaker_play_tone(NOTE_C4, 100);
	tslp_tsk(200);
	//**************************************************************//

	lineMode->preMode();
	leftCourse->prepareRun();

	act_tsk(BT_TASK);
	
	 while(1)
    {

        if (bt_cmd == 1)
        {
            break; /* リモートスタート */
        }

		if (ev3_button_is_pressed(ENTER_BUTTON)) {
			while (ev3_button_is_pressed(ENTER_BUTTON));
			break;
		}
    	        clock.sleep(10);
    }
	
	
	
	ev3_speaker_play_tone(NOTE_C4, 100);

	//各周期ハンドラを起動させる。（周期タスクが開始する）
	ev3_sta_cyc(EV3_CYC_RUN);
	ev3_sta_cyc(EV3_CYC_COMMUNICATION);
	ev3_sta_cyc(EV3_CYC_EMERGENCYSTOP);
	slp_tsk();
	ev3_stp_cyc(EV3_CYC_RUN);
	ev3_stp_cyc(EV3_CYC_COMMUNICATION);
	ev3_stp_cyc(EV3_CYC_EMERGENCYSTOP);

    ter_tsk(BT_TASK);
    fclose(bt);
	user_system_destroy();
	ext_tsk();
}

void run_task(intptr_t exinf)
{
	speedoMeter->update();



	if (leftCourse->startRun() == true) {
		armMotor.setPWM(0);
		leftMotor.setPWM(0);
		rightMotor.setPWM(0);
		ev3_stp_cyc(EV3_CYC_RUN);
		ext_tsk();
	}
	/* Bluetooth通信タスクの起動 */

}
   	
void bt_task(intptr_t exinf)
{
	
	ev3_speaker_play_tone(NOTE_C4, 100);
	ev3_speaker_play_tone(NOTE_D4, 100);
	ev3_speaker_play_tone(NOTE_E4, 100);
	ev3_speaker_play_tone(NOTE_C4, 100);
	ev3_speaker_play_tone(NOTE_D4, 100);
	ev3_speaker_play_tone(NOTE_A4, 100);
	 ev3_led_set_color(LED_RED);
	
  	 	 uint64_t a = fgetc(bt); 
    	 fputc(a, bt); /* エコーバック */
    	 uint64_t b = fgetc(bt);
    	 fputc(b, bt); /* エコーバック */
   		 uint64_t c = fgetc(bt);
    	 fputc(c, bt); /* エコーバック */
     	 uint64_t d = fgetc(bt);
    	 fputc(d, bt); /* エコーバック */
    	 uint64_t e = fgetc(bt);
   		 fputc(e, bt); /* エコーバック */
        
    	prenum = a*10000+b*1000+c*100+d*10+e;
	
		bt_cmd = 1;

		field->convertEPcode(prenum);
}

void communication_task(intptr_t exinf) {
	communication->update();
	sonarMeter->ReadDistance();
	ext_tsk();
}

void emergencystop_task(intptr_t exinf) {
	ext_tsk();
}
//Copyright (c) 2014 Kagaku No Yousei. All Rights Reserved.
