#define BLACKSIDE 18				//格子走行の黒より位置設定16

//走行方法パッケージ
#include "RunMethod/RunMethod.h"
#include "RunMethod/LineTraceMethod.h"
#include "RunMethod/InstructionMethod.h"
#include "RunMethod/RatioRotationMethod.h"
#include "RunMethod/PID.h"

//ルート案内パッケージ
#include "RouteGuide/RunCourse.h"
#include "RouteGuide/RunArea.h"
#include "RouteGuide/DynamicRunArea.h"
#include "RouteGuide/BlockLineRunArea.h"
#include "RouteGuide/RunBlock.h"
#include "RouteGuide/LookblockRunBlock.h"
#include "RouteGuide/CrossRunBlock.h"
#include "Routeguide/RouteSearchRunBlock.h"
#include "RouteGuide/StarWatchRunBlock.h"
#include "RouteGuide/EscapeRunBlock.h"


//機体状態パッケージ
#include "Mode/Mode.h"

//条件パッケージ
#include "Condition/Condition.h"
#include "Condition/DirectionCondition.h"
#include "Condition/DistanceCondition.h"
#include "Condition/LineCondition.h"
#include "Condition/WhiteCondition.h"
#include "Condition/LineoutCondition.h"
#include "Condition/MultiCondition.h"
#include "Condition/ObstacleCondition.h"
#include "Condition/StepCondition.h"
#include "Condition/TimeDetectionCondition.h"
#include "Condition/ColorCondition.h"
#include "Condition/BlockplaceCondition.h"

//計測器パッケージ
#include "Measure/Brightness.h"
#include "Measure/Calibration.h"
#include "Measure/DistanceMeasure.h"
#include "Measure/SpeedoMeter.h"
#include "Measure/TrainReader.h"

//コミュニケーションパッケージ
#include "Communication/Communication.h"
#include "Communication/LogData.h"
#include "Communication/Sound.h"

//ブロック並べ解法パッケージ
#include "BlockLined/Solution.h"
#include "BlockLined/Block.h"
#include "BlockLined/ColorDistinguish.h"
#include "BlockLined/Route.h"
#include "BlockLined/Color.h"
#include "BlockLined/MovementType.h"
#include "BlockLined/Place.h"
#include "BlockLined/RouteInfo.h"

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

static FILE     *bt = NULL;

// オブジェクトの定義

//ブロック並べの定義

static Route*					route;
static ColorDistinguish*		colordisA;
static ColorDistinguish*		colordisB;
static ColorDistinguish*		colordisC;
static ColorDistinguish*		colordisD;
static Block*					blockA;
static Block*					blockB;
static Block*					blockC;
static Block*					blockD;
static Solution*				solution;
static Place*					place00;
static Place*                   place01;
static Place*                   place02;
static Place*                   place03;
static Place*                   place10;
static Place*                   place11;
static Place*                   place12;
static Place*                   place13;
static Place*                   place20;
static Place*                   place21;
static Place*                   place22;
static Place*				    place23;
static Place*                   place30;
static Place*                   place31;
static Place*                   place32;
static Place*                   place33;
static Placegroup*              RedPlacegroup;
static Placegroup*              BluePlacegroup;
static Placegroup*              YellowPlacegroup;
static Placegroup*              GreenPlacegroup;
static Placegroup*              EscapePlacegroup;
static Field*					field;
static RouteInfo*				routeInfo;


//コミュニケーションの定義
static  Brightness*				brightness;
static	Communication*			communication;
static	LogData*				logdata;
static	Sound*					sound;

//計測器の定義
static	Calibration*			calibration;
static	DistanceMeasure*		distanceMeasure;
static	SpeedoMeter*			speedoMeter;
static	SonarMeter*				sonarMeter;

//PIDの定義
static	PID*					pid_R_First;
static  PID*					pid_R_Look;
static	PID*					pid_R_Game;
static	PID*					pid_straight;
static  PID*					pid_hispeedStraight;
static  PID*					pid_curve;
static	PID*					pid_End;
static	PID*					pid_gray;
static	PID*					pid_Technic_Curve2;
static	PID*					pid_curve3;

//検知条件の定義
static	Condition*				Start_StopDisCondition;

static	Condition*				First_Long_StraightDisCondition;
static	Condition*				First_TurnDisCondition;
static	Condition*				First_Short_StraightDisCondition;
static	Condition*				First_Detection_LineDisCondition;
static	Condition*				First_Return_StraightDisCondition;
static	Condition*				First_Return_Short_Straight_RDisCondition;
static	Condition*				First_Return_Line_RDisCondition;
static	Condition*				First_Return_Detection_Turn_RDisCondition;
static	Condition*				First_Return_Short_Straight_LDisCondition;
static	Condition*				First_Return_Line_LDisCondition;
static	Condition*				First_Return_Detection_Turn_LDisCondition;

static	Condition*				Game_Color_PlaceDisCondition;
static  Condition*				Game_CenterDisCondition;
static  Condition*				Game_Short_StraightDisCondition;
static	Condition*				Game_Turn_RDisCondition;
static  Condition*				Game_Detection_Turn_RDisCondition;
static	Condition*				Game_Turn_LDisCondition;
static  Condition*				Game_Detection_Turn_LDisCondition;
static	Condition*				Game_Revolution_RDisCondition;
static  Condition*				Game_Detection_Revolution_RDisCondition;
static	Condition*				Game_Revolution_ConnectDisCondition;
static  Condition*				Game_Correct_LineDisCondition;
static	Condition*				Game_StraightDisCondition;
static	Condition*				Game_Connect_BackDisCondition;
static	Condition*				Game_Connect_Short_StraightDisCondition;
static	Condition*				Game_Connect_Short_Straight_RLDisCondition;
static	Condition*				Game_Connect_StraightDisCondition;
static	Condition*				Game_Connect_Turn_SRDisCondition;
static	Condition*				Game_Connect_Detection_LineDisCondition;
static	Condition*				Game_Connect_Over_PlaceDisCondition;
static	Condition*				Game_Connect_Detection_SDisCondition;
static	Condition*				Game_Connect_Correct_Line_SDisCondition;
static	Condition*				Game_Connect_Turn_RDisCondition;
static	Condition*				Game_Connect_Correct_Line_RDisCondition;
static	Condition*				Game_Connect_Turn_LDisCondition;
static	Condition*				Game_Connect_Correct_Line_LDisCondition;
static	Condition*				Game_Connect_Revolution_BDisCondition;
static	Condition*				Game_Connect_Correct_Line_BDisCondition;

static	Condition*				Look_Color_PlaceDisCondition;
static  Condition*				Look_Color_Short_BackDisCondition;
static	Condition*				Look_Color_Armup_FirstDisCondition;
static	Condition*				Look_Color_ArmdownDisCondition;
static	Condition*				Look_Color_Armup_SecondDisCondition;
static	Condition*				Look_Color_ReturnDisCondition;

static	Condition*				Station_Color_PlaceDisCondition;
static  Condition*				Station_Short_BackDisCondition;
static	Condition*				Station_Revolution_RDisCondition;
static  Condition*				Station_Detection_Revolution_RDisCondition;
static  Condition*				Station_Correct_LineDisCondition;
static	Condition*				Station_StraightDisCondition;

static	Condition*				Escape_ConsiderDisCondition;
static	Condition*				Escape_RightDisCondition;
static	Condition*				Escape_Short_StraightDisCondition;
static	Condition*				Escape_BackerDisCondition;
static	Condition*				Escape_Short_BackerDisCondition;
static	Condition*				Escape_LeftDisCondition;
static	Condition*				Escape_OvercolorDisCondition;
static	Condition*				Escape_Detection_StopDisCondition;
static	Condition*				Escape_Short_DisCondition;
static  Condition*				Escape_Turn_R90DisCondition;
static  Condition*				Escape_Slowspeed_RunDisCondition;
static	Condition*				Escape_Turn_FirstA;//マルチ用A
static	Condition*				Escape_Turn_FirstB;//マルチ用B
static	Condition*				Escape_Turn_FirstDisCondition;//マルチ用
static  Condition*              Escape_Slowspeed_Run_to2DisCondition;
static	Condition*				Escape_Hispeed_Run_to2DisCondition;


static	Condition*				Technic_A_Curve2_ADisCondition;
static	Condition*				Technic_A_Slowspeed_Run_to3_ADisCondition;
static	Condition*				Technic_A_Hispeed_Run_to3_ADisCondition;
static	Condition*				Technic_A_StopDisCondition;
static  Condition*              Technic_A_Curve_Detection_ADisCondition;
static  Condition*              Technic_A_Curve3_Run_ADisCondition;
static	Condition*				Technic_A_Hispeed_Run_to4_ADisCondition;
static	Condition*				Technic_A_Slow_ADisCondition;
static  Condition*				Technic_A_Slowspeed_Run_toGoal_ADisCondition;
static	Condition*				Technic_A_Hispeed_Run_ADisCondition;

static	Condition*				Technic_B_Curve2_BDisCondition;
static	Condition*				Technic_B_Over_Green_BDisCondition;
static	Condition*				Technic_B_Stop_Lined_BDisCondition;
static	Condition*				Technic_B_Short_Run_BDisCondition;
static  Condition*              Technic_B_Gate_Stop_BDisCondition;
static  Condition*              Technic_B_Turn_To_Goal_BDisCondition;
static	Condition*				Technic_B_Stop_Togoal_Line_BDisCondition;
static	Condition*				Technic_B_Slow_BDisCondition;
static  Condition*				Technic_B_Slowspeed_Run_toGoal_BDisCondition;
static	Condition*				Technic_B_Hispeed_Run_BDisCondition;

static	Condition*				Technic_C_Curve2_CDisCondition;
static	Condition*				Technic_C_Over_Green_CDisCondition;
static	Condition*				Technic_C_Stop_Lined_CDisCondition;
static	Condition*				Technic_C_Short_Run_CDisCondition;
static  Condition*              Technic_C_Turn_to_Curve_4_CDisCondition;
static  Condition*              Technic_C_Run_To_Goal_CDisCondition;
static	Condition*				Technic_C_Slow_Run_Togoal_CDisCondition;
static	Condition*				Technic_C_Goout_CDisCondition;
static	Condition*				Technic_C_Edgechange_CDisCondition;
static	Condition*				Technic_C_Slow_CDisCondition;
static  Condition*				Technic_C_Slowspeed_Run_toGoal_CDisCondition;
static	Condition*				Technic_C_Hispeed_Run_CDisCondition;

static	Condition*				Final_StopDisCondition;

//機体状態の定義
static Mode*					lineMode;
static Mode*                    search1Mode;
static Mode*                    search2Mode;
static Mode*					destroyMode;

//走行方法の定義
static	RunMethod*				Start_StopRun;

static	RunMethod*				First_Long_StraightRun;
static	RunMethod*				First_TurnRun;
static	RunMethod*				First_Short_StraightRun;
static	RunMethod*				First_Detection_LineRun;
static	RunMethod*				First_Return_StraightRun;
static	RunMethod*				First_Return_Short_Straight_RRun;
static	RunMethod*				First_Return_Line_RRun;
static	RunMethod*				First_Return_Detection_Turn_RRun;
static	RunMethod*				First_Return_Short_Straight_LRun;
static	RunMethod*				First_Return_Line_LRun;
static	RunMethod*				First_Return_Detection_Turn_LRun;

static	RunMethod*				Game_Color_PlaceRun;
static  RunMethod*				Game_CenterRun;
static  RunMethod*				Game_Short_StraightRun;
static	RunMethod*				Game_Turn_RRun;
static  RunMethod*				Game_Detection_Turn_RRun;
static	RunMethod*				Game_Turn_LRun;
static  RunMethod*				Game_Detection_Turn_LRun;
static	RunMethod*				Game_Revolution_RRun;
static  RunMethod*				Game_Detection_Revolution_RRun;
static	RunMethod*				Game_Revolution_ConnectRun;
static  RunMethod*				Game_Correct_LineRun;
static	RunMethod*				Game_StraightRun;
static	RunMethod*				Game_Connect_BackRun;
static	RunMethod*				Game_Connect_Short_StraightRun;
static	RunMethod*				Game_Connect_Short_Straight_RLRun;
static	RunMethod*				Game_Connect_StraightRun;
static	RunMethod*				Game_Connect_Turn_SRRun;
static	RunMethod*				Game_Connect_Detection_LineRun;
static	RunMethod*				Game_Connect_Over_PlaceRun;
static  RunMethod*				Game_Connect_Detection_SRun;
static	RunMethod*				Game_Connect_Correct_Line_SRun;
static	RunMethod*				Game_Connect_Turn_RRun;
static	RunMethod*				Game_Connect_Correct_Line_RRun;
static	RunMethod*				Game_Connect_Turn_LRun;
static	RunMethod*				Game_Connect_Correct_Line_LRun;
static	RunMethod*				Game_Connect_Revolution_BRun;
static	RunMethod*				Game_Connect_Correct_Line_BRun;

static	RunMethod*				Look_Color_PlaceRun;
static  RunMethod*				Look_Color_Short_BackRun;
static	RunMethod*				Look_Color_Armup_FirstRun;
static	RunMethod*				Look_Color_ArmdownRun;
static	RunMethod*				Look_Color_Armup_SecondRun;
static	RunMethod*				Look_Color_ReturnRun;

static	RunMethod*				Station_Color_PlaceRun;
static  RunMethod*				Station_Short_BackRun;
static	RunMethod*				Station_Revolution_RRun;
static  RunMethod*				Station_Detection_Revolution_RRun;
static  RunMethod*				Station_Correct_LineRun;
static	RunMethod*				Station_StraightRun;

static	RunMethod*				Escape_ConsiderRun;
static	RunMethod*				Escape_RightRun;
static	RunMethod*				Escape_Short_StraightRun;
static	RunMethod*				Escape_BackerRun;
static	RunMethod*				Escape_Short_BackerRun;
static	RunMethod*				Escape_LeftRun;
static	RunMethod*				Escape_OvercolorRun;
static	RunMethod*				Escape_Detection_StopRun;
static	RunMethod*				Escape_Short_Run;
static  RunMethod*				Escape_Turn_R90Run;
static  RunMethod*				Escape_Slowspeed_RunRun;
static	RunMethod*				Escape_Normal_Run_to1Run;
static  RunMethod*              Escape_Slowspeed_Run_to2Run;
static	RunMethod*				Escape_Hispeed_Run_to2Run;


static	RunMethod*				Technic_A_Curve2_ARun;
static	RunMethod*				Technic_A_Slowspeed_Run_to3_ARun;
static	RunMethod*				Technic_A_Hispeed_Run_to3_ARun;
static	RunMethod*				Technic_A_StopRun;
static  RunMethod*              Technic_A_Curve_Detection_ARun;
static  RunMethod*              Technic_A_Curve3_Run_ARun;
static	RunMethod*				Technic_A_Hispeed_Run_to4_ARun;
static	RunMethod*				Technic_A_Slow_ARun;
static  RunMethod*				Technic_A_Slowspeed_Run_toGoal_ARun;
static	RunMethod*				Technic_A_Hispeed_Run_ARun;

static	RunMethod*				Technic_B_Curve2_BRun;
static	RunMethod*				Technic_B_Over_Green_BRun;
static	RunMethod*				Technic_B_Stop_Lined_BRun;
static	RunMethod*				Technic_B_Short_Run_BRun;
static  RunMethod*              Technic_B_Gate_Stop_BRun;
static  RunMethod*              Technic_B_Turn_To_Goal_BRun;
static	RunMethod*				Technic_B_Stop_Togoal_Line_BRun;
static	RunMethod*				Technic_B_Slow_BRun;
static  RunMethod*				Technic_B_Slowspeed_Run_toGoal_BRun;
static	RunMethod*				Technic_B_Hispeed_Run_BRun;

static	RunMethod*				Technic_C_Curve2_CRun;
static	RunMethod*				Technic_C_Over_Green_CRun;
static	RunMethod*				Technic_C_Stop_Lined_CRun;
static	RunMethod*				Technic_C_Short_Run_CRun;
static  RunMethod*              Technic_C_Turn_to_Curve_4_CRun;
static  RunMethod*              Technic_C_Run_To_Goal_CRun;
static	RunMethod*				Technic_C_Slow_Run_Togoal_CRun;
static	RunMethod*				Technic_C_Goout_CRun;
static	RunMethod*				Technic_C_Edgechange_CRun;
static	RunMethod*				Technic_C_Slow_CRun;
static  RunMethod*				Technic_C_Slowspeed_Run_toGoal_CRun;
static	RunMethod*				Technic_C_Hispeed_Run_CRun;

static	RunMethod*				Final_StopRun;


//走行コースの定義
static	RunCourse*				rightCourse;

//走行エリアの定義
static	RunArea*				FirstArea;
static	RunArea*				GameArea;
static	RunArea*				Look_ColorArea;
static	RunArea*				StationArea;
static  RunArea*				BLArea;
static	RunArea*				EscapeArea;
static	RunArea*				Technic_AArea;
static	RunArea*				Technic_BArea;
static	RunArea*				Technic_CArea;

//走行区画の定義
static	RunBlock*				Start_StopBlock;

static	RunBlock*				First_Long_StraightBlock;
static	RunBlock*				First_TurnBlock;
static	RunBlock*				First_Short_StraightBlock;
static	RunBlock*				First_Detection_LineBlock;
static	RunBlock*				First_Return_StraightBlock;
static	RunBlock*				First_Return_Short_Straight_RBlock;
static	RunBlock*				First_Return_Line_RBlock;
static	RunBlock*				First_Return_Detection_Turn_RBlock;
static	RunBlock*				First_Return_Short_Straight_LBlock;
static	RunBlock*				First_Return_Line_LBlock;
static	RunBlock*				First_Return_Detection_Turn_LBlock;

static	RunBlock*				Game_Color_PlaceBlock;
static  RunBlock*				Game_CenterBlock;
static  RunBlock*				Game_Short_StraightBlock;
static	RunBlock*				Game_Turn_RBlock;
static	RunBlock*				Game_Detection_Turn_RBlock;
static	RunBlock*				Game_Turn_LBlock;
static	RunBlock*				Game_Detection_Turn_LBlock;
static	RunBlock*				Game_Revolution_RBlock;
static	RunBlock*				Game_Detection_Revolution_RBlock;
static	RunBlock*				Game_Revolution_ConnectBlock;
static  RunBlock*				Game_Correct_LineBlock;
static	RunBlock*				Game_StraightBlock;
static	RunBlock*				Game_Connect_BackBlock;
static	RunBlock*				Game_Connect_Short_StraightBlock;
static	RunBlock*				Game_Connect_Short_Straight_RLBlock;
static	RunBlock*				Game_Connect_StraightBlock;
static	RunBlock*				Game_Connect_Turn_SRBlock;
static	RunBlock*				Game_Connect_Detection_LineBlock;
static	RunBlock*				Game_Connect_Over_PlaceBlock;
static	RunBlock*				Game_Connect_Detection_SBlock;
static	RunBlock*				Game_Connect_Correct_Line_SBlock;
static	RunBlock*				Game_Connect_Turn_RBlock;
static	RunBlock*				Game_Connect_Correct_Line_RBlock;
static	RunBlock*				Game_Connect_Turn_LBlock;
static	RunBlock*				Game_Connect_Correct_Line_LBlock;
static	RunBlock*				Game_Connect_Revolution_BBlock;
static	RunBlock*				Game_Connect_Correct_Line_BBlock;

static	RunBlock*				Look_Color_PlaceBlock;
static  RunBlock*				Look_Color_Short_BackBlock;
static	RunBlock*				Look_Color_Armup_FirstBlock;
static	RunBlock*				Look_Color_Armup_SecondBlock;
static	RunBlock*				Look_Color_ArmdownBlock;
static	RunBlock*				Look_Color_ReturnBlock;

static	RunBlock*				Station_Color_PlaceBlock;
static  RunBlock*				Station_Short_BackBlock;
static	RunBlock*				Station_Revolution_RBlock;
static	RunBlock*				Station_Detection_Revolution_RBlock;
static  RunBlock*				Station_Correct_LineBlock;
static	RunBlock*				Station_StraightBlock;

static	RunBlock*				Escape_ConsiderBlock;
static	RunBlock*				Escape_RightBlock;
static	RunBlock*				Escape_Short_StraightBlock;
static	RunBlock*				Escape_BackerBlock;
static	RunBlock*				Escape_Short_BackerBlock;
static	RunBlock*				Escape_LeftBlock;
static	RunBlock* 				Escape_OvercolorBlock;
static	RunBlock*				Escape_Detection_StopBlock;
static	RunBlock*				Escape_Short_Block;
static  RunBlock*				Escape_Turn_R90Block;
static  RunBlock*				Escape_Slowspeed_RunBlock;
static	RunBlock*				Escape_Normal_Run_to1Block;
static	RunBlock*               Escape_Slowspeed_Run_to2Block;
static	RunBlock*				Escape_Hispeed_Run_to2Block;


static	RunBlock* 				Technic_A_Curve2_ABlock;
static	RunBlock* 				Technic_A_Slowspeed_Run_to3_ABlock;
static	RunBlock* 				Technic_A_Hispeed_Run_to3_ABlock;
static	RunBlock*				Technic_A_StopBlock;
static  RunBlock*               Technic_A_Curve_Detection_ABlock;
static  RunBlock*               Technic_A_Curve3_Run_ABlock;
static	RunBlock*				Technic_A_Hispeed_Run_to4_ABlock;
static	RunBlock* 				Technic_A_Slow_ABlock;
static  RunBlock*				Technic_A_Slowspeed_Run_toGoal_ABlock;
static	RunBlock* 				Technic_A_Hispeed_Run_ABlock;

static	RunBlock* 				Technic_B_Curve2_BBlock;
static	RunBlock* 				Technic_B_Over_Green_BBlock;
static	RunBlock* 				Technic_B_Stop_Lined_BBlock;
static	RunBlock*				Technic_B_Short_Run_BBlock;
static  RunBlock*               Technic_B_Gate_Stop_BBlock;
static  RunBlock*               Technic_B_Turn_To_Goal_BBlock;
static	RunBlock*				Technic_B_Stop_Togoal_Line_BBlock;
static	RunBlock* 				Technic_B_Slow_BBlock;
static  RunBlock*				Technic_B_Slowspeed_Run_toGoal_BBlock;
static	RunBlock* 				Technic_B_Hispeed_Run_BBlock;

static	RunBlock* 				Technic_C_Curve2_CBlock;
static	RunBlock* 				Technic_C_Over_Green_CBlock;
static	RunBlock* 				Technic_C_Stop_Lined_CBlock;
static	RunBlock* 				Technic_C_Goout_CBlock;
static	RunBlock* 				Technic_C_Edgechange_CBlock;
static	RunBlock*				Technic_C_Short_Run_CBlock;
static  RunBlock*               Technic_C_Turn_to_Curve_4_CBlock;
static  RunBlock*               Technic_C_Run_To_Goal_CBlock;
static	RunBlock*				Technic_C_Slow_Run_Togoal_CBlock;
static	RunBlock* 				Technic_C_Slow_CBlock;
static  RunBlock*				Technic_C_Slowspeed_Run_toGoal_CBlock;
static	RunBlock* 				Technic_C_Hispeed_Run_CBlock;

static	RunBlock*				Final_StopBlock;


static void user_system_create() {
	//******************インスタンスが複数ないクラスの設定**********//
	sonarMeter =			new SonarMeter(&sonarSensor);
	brightness =			new Brightness(&colorSensor);
	logdata =				new LogData();
	distanceMeasure =		new DistanceMeasure(&leftMotor, &rightMotor);
	speedoMeter =			new SpeedoMeter(distanceMeasure);
	calibration =			new Calibration(&touchSensor, &colorSensor, &clock, &gyroSensor, brightness);
	sound =					new Sound(&clock);
	communication =			new Communication(sound);
	//******************ブロック並べエリアで使うインスタンス*********//

	routeInfo =				new RouteInfo(4);//走行体がブロックBに到着した時の走行体の方向を入れる  スタート側１、出る側２、Lコース側３、走る側４

	colordisA =				new ColorDistinguish(&colorSensor);
	colordisB =				new ColorDistinguish(&colorSensor);
	colordisC =				new ColorDistinguish(&colorSensor);
	colordisD =				new ColorDistinguish(&colorSensor);

	blockA =				new Block(Green, colordisA,0);
	blockB =				new Block(Green, colordisB,1);
	blockC =				new Block(Green, colordisC,2);
	blockD =				new Block(Green, colordisD,3);
	
	place00 =				new Place(nullptr, 0,routeInfo, blockA, blockB, blockC, blockD);
	place01 =				new Place(blockC, 1,routeInfo, blockA, blockB, blockC, blockD);
	place02 =				new Place(blockB, 2,routeInfo, blockA, blockB, blockC, blockD);
	place03 =				new Place(nullptr, 3,routeInfo, blockA, blockB, blockC, blockD);
	place10 =				new Place(nullptr, 4,routeInfo, blockA, blockB, blockC, blockD);
	place11 =				new Place(nullptr, 5,routeInfo, blockA, blockB, blockC, blockD);
	place12 =				new Place(blockA, 6,routeInfo, blockA, blockB, blockC, blockD);
	place13 =               new Place(nullptr, 7,routeInfo, blockA, blockB, blockC, blockD);
	place20 =               new Place(nullptr, 8,routeInfo, blockA, blockB, blockC, blockD);
	place21 =				new Place(nullptr, 9,routeInfo, blockA, blockB, blockC, blockD);
	place22 =				new Place(nullptr,10,routeInfo, blockA, blockB, blockC, blockD);
	place23 =				new Place(nullptr,11,routeInfo, blockA, blockB, blockC, blockD);
	place30 =				new Place(nullptr,12,routeInfo, blockA, blockB, blockC, blockD);
	place31 =               new Place(nullptr,13,routeInfo, blockA, blockB, blockC, blockD);
	place32 =				new Place(nullptr,14,routeInfo, blockA, blockB, blockC, blockD);
	place33 =				new Place(blockD,15,routeInfo, blockA, blockB, blockC, blockD);

	RedPlacegroup =			new Placegroup(place11, place10, place01, place00);
	BluePlacegroup =		new Placegroup(place12, place13, place02, place03);
	YellowPlacegroup =		new Placegroup(place21, place20, place31, place30);
	GreenPlacegroup =		new Placegroup(place22, place23, place32, place33);
	EscapePlacegroup =		new Placegroup(place13, place23, place03, place33);

	field =					new Field(place02);

	route =					new Route(field,routeInfo, blockA, blockB, blockC, blockD);

	solution =				new Solution(route, blockA, blockB, blockC, blockD);

	//*****************走行コースと走行エリアの設定**********//
	//走行コースの設定
	rightCourse =			new RunCourse(calibration, communication);

	//走行エリアの設定

	FirstArea =				new RunArea();
	GameArea =				new DynamicRunArea();
	Look_ColorArea =		new RunArea();
	StationArea =			new RunArea();
	BLArea =				new BlockLineRunArea(GameArea, StationArea, Look_ColorArea, solution);
	EscapeArea =			new DynamicRunArea();
	Technic_AArea =			new RunArea();
	Technic_BArea =			new RunArea();
	Technic_CArea =			new RunArea();




	/******************条件と走行方法クラスのAPI**********************
	距離検知				DistanceCondition(距離mm,distanceMeasure);
	時間検知				TimeDetectionCondition(ミリ秒,&clock);
	段差検知				StepCondition(ジャイロ値,速度,&gyroSensor,speedoMeter);
	方向検知				DirectionCondition(角度°,distanceMeasure);
	ライン検知				LineCondition(反射光の値,brightness);
	白検知					WhiteCondition(反射光の値,brightness);
	コースアウト検知		LineoutCondition(コースアウトとみなす秒数(４ミリ秒),白とみなす反射光の値,brightness);
	ｽﾃｱﾘﾝｸﾞ検知				SteeringCondition(角度°,&steerMotor);
	障害物検知				ObstacleCondition(sonarMeter,目標距離cm);
	複数検知				MultiCondition(論理条件bool,検知条件のインスタンス,検知条件のインスタンス);
	直線検知				StraightCondition(&steerMotor)
	色検知　　　　　　　　　ColorCondition(色num,&colorSensor)  none=0,black=1,blue=2,green=3,yellow=4,red=5,white=6,brown=7
	RGB検知					BlockplaceCondition(&colorSensor)

	ライントレース走行		LineTraceMethod(速度, ステア限界角度, エッジ（bool 0で右 1で左）, 境界線値変更, brightness, お好きなpid, &leftMotor, &rightMotor);
	指定走行				InstructionMethod(左速度, 右速度, &leftMotor, &rightMotor);
	等回転比走行			RatioRotationMethod(旋回係数, 旋回補助, 速度, &leftMotor, &rightMotor,  distanceMeasure);
	***************************************************/

	//rightコース-FirstAreaの終了条件を設定
	Start_StopDisCondition =						new TimeDetectionCondition(500, &clock);

	First_Long_StraightDisCondition =				new DistanceCondition(480, distanceMeasure);//左に曲がる時570　//右に曲がる時480
	First_TurnDisCondition =						new DirectionCondition(-180, distanceMeasure);
	First_Short_StraightDisCondition =				new DistanceCondition(400, distanceMeasure);
	First_Detection_LineDisCondition =				new LineCondition(0, brightness);
	First_Return_Short_Straight_RDisCondition =		new DistanceCondition(50, distanceMeasure);
	First_Return_Line_RDisCondition =				new DirectionCondition(100, distanceMeasure);
	First_Return_Detection_Turn_RDisCondition =		new LineCondition(0, brightness);
	First_Return_Short_Straight_LDisCondition =		new DistanceCondition(45, distanceMeasure);
	First_Return_Line_LDisCondition =				new DirectionCondition(-100, distanceMeasure);
	First_Return_Detection_Turn_LDisCondition =		new LineCondition(0, brightness);
	First_Return_StraightDisCondition =				new DistanceCondition(20, distanceMeasure);

	//rightコース-GameAreaの終了条件を設定
	Game_Color_PlaceDisCondition =					new BlockplaceCondition(&colorSensor);
	Game_CenterDisCondition =						new DistanceCondition(53, distanceMeasure);
	Game_Short_StraightDisCondition =				new DistanceCondition(60, distanceMeasure);
	Game_Turn_RDisCondition =						new DirectionCondition(170, distanceMeasure);
	Game_Detection_Turn_RDisCondition =				new LineCondition(0, brightness);
	Game_Turn_LDisCondition =						new DirectionCondition(-170, distanceMeasure);
	Game_Detection_Turn_LDisCondition =				new LineCondition(0, brightness);
	Game_Revolution_RDisCondition =					new DirectionCondition(380, distanceMeasure);
	Game_Detection_Revolution_RDisCondition =		new LineCondition(0, brightness);
	Game_Revolution_ConnectDisCondition =			new DirectionCondition(-60, distanceMeasure);
	Game_Correct_LineDisCondition =					new DistanceCondition(25, distanceMeasure);
	Game_StraightDisCondition =						new DistanceCondition(100, distanceMeasure);
	Game_Connect_BackDisCondition =					new DistanceCondition(-75, distanceMeasure);
	Game_Connect_Short_StraightDisCondition =		new DistanceCondition(45, distanceMeasure);
	Game_Connect_Short_Straight_RLDisCondition =	new DistanceCondition(60, distanceMeasure);
	Game_Connect_StraightDisCondition =				new DistanceCondition(70, distanceMeasure);
	Game_Connect_Turn_SRDisCondition =				new DirectionCondition(140, distanceMeasure);
	Game_Connect_Detection_LineDisCondition =		new LineCondition(0, brightness);
	Game_Connect_Over_PlaceDisCondition =			new DistanceCondition(250, distanceMeasure);
	Game_Connect_Detection_SDisCondition =			new LineCondition(0, brightness);
	Game_Connect_Correct_Line_SDisCondition =		new LineCondition(0, brightness);
	Game_Connect_Turn_RDisCondition =				new DirectionCondition(90, distanceMeasure);
	Game_Connect_Correct_Line_RDisCondition =		new DirectionCondition(80, distanceMeasure);
	Game_Connect_Turn_LDisCondition =				new DirectionCondition(-90, distanceMeasure);
	Game_Connect_Correct_Line_LDisCondition =		new DirectionCondition(-80, distanceMeasure);
	Game_Connect_Revolution_BDisCondition =			new DirectionCondition(380, distanceMeasure);
	Game_Connect_Correct_Line_BDisCondition =		new DirectionCondition(-10, distanceMeasure);

	//rightコース-Look_ColorAreaの終了条件を設定
	Look_Color_PlaceDisCondition =					new BlockplaceCondition(&colorSensor);
	Look_Color_Short_BackDisCondition =				new DistanceCondition(-40, distanceMeasure);
	Look_Color_Armup_FirstDisCondition =			new TimeDetectionCondition(300, &clock);
	Look_Color_Armup_SecondDisCondition =			new TimeDetectionCondition(300, &clock);
	Look_Color_ArmdownDisCondition =				new TimeDetectionCondition(1000, &clock);
	Look_Color_ReturnDisCondition =					new BlockplaceCondition(&colorSensor);

	//rightコース-stationAreaの終了条件を設定
	Station_Color_PlaceDisCondition =				new BlockplaceCondition(&colorSensor);
	Station_Short_BackDisCondition =				new DistanceCondition(-80, distanceMeasure);
	Station_Revolution_RDisCondition =				new DirectionCondition(360, distanceMeasure);
	Station_Detection_Revolution_RDisCondition =	new LineCondition(0, brightness);
	Station_Correct_LineDisCondition =				new DirectionCondition(-10, distanceMeasure);
	Station_StraightDisCondition =					new DistanceCondition(100, distanceMeasure);

	//rightコース-EscapeAreaの終了条件を設定
	Escape_ConsiderDisCondition =					new TimeDetectionCondition(20, &clock);
	Escape_RightDisCondition =						new DirectionCondition(200, distanceMeasure);
	Escape_Short_StraightDisCondition =				new DistanceCondition(60, distanceMeasure);
	Escape_BackerDisCondition =						new DirectionCondition(410, distanceMeasure);
	Escape_Short_BackerDisCondition =				new DistanceCondition(60, distanceMeasure);
	Escape_LeftDisCondition =						new DirectionCondition(-200, distanceMeasure);
	Escape_OvercolorDisCondition =					new DistanceCondition(280, distanceMeasure);
	Escape_Detection_StopDisCondition =				new LineCondition(-15, brightness);
	Escape_Short_DisCondition =						new DistanceCondition(30, distanceMeasure);
	Escape_Turn_R90DisCondition =					new LineCondition(-15, brightness);
	Escape_Slowspeed_RunDisCondition =				new DistanceCondition(180, distanceMeasure);
	Escape_Turn_FirstA=								new LineoutCondition(80, 30, brightness);
	Escape_Turn_FirstB =							new DirectionCondition(60, distanceMeasure);
	Escape_Turn_FirstDisCondition = 				new MultiCondition(true,Escape_Turn_FirstA,Escape_Turn_FirstB);
	Escape_Slowspeed_Run_to2DisCondition =			new DistanceCondition(900, distanceMeasure);
	Escape_Hispeed_Run_to2DisCondition =			new DirectionCondition(-190, distanceMeasure);//曲がる
	
	//rightコース-TechnicAreaの終了条件を設定
	Technic_A_Curve2_ADisCondition =					new DistanceCondition(1100, distanceMeasure);
	Technic_A_Slowspeed_Run_to3_ADisCondition =			new DistanceCondition(1070, distanceMeasure);
	Technic_A_Hispeed_Run_to3_ADisCondition =			new DirectionCondition(20, distanceMeasure);
	Technic_A_StopDisCondition =						new TimeDetectionCondition(200, &clock);
	Technic_A_Curve_Detection_ADisCondition =			new LineCondition(-10, brightness);
	Technic_A_Curve3_Run_ADisCondition =				new DistanceCondition(750, distanceMeasure);
	Technic_A_Hispeed_Run_to4_ADisCondition =			new DistanceCondition(1780, distanceMeasure);
	Technic_A_Slow_ADisCondition =						new DistanceCondition(300, distanceMeasure);
	Technic_A_Slowspeed_Run_toGoal_ADisCondition =		new DistanceCondition(360, distanceMeasure);
	Technic_A_Hispeed_Run_ADisCondition =				new DistanceCondition(4500, distanceMeasure);

	Technic_B_Curve2_BDisCondition = 					new LineCondition(-15, brightness);//緑
	Technic_B_Over_Green_BDisCondition = 				new WhiteCondition(-15, brightness);//白
	Technic_B_Stop_Lined_BDisCondition = 				new LineCondition(-15, brightness);//LINE
	Technic_B_Short_Run_BDisCondition = 				new DistanceCondition(40, distanceMeasure);//ちょっと
	Technic_B_Gate_Stop_BDisCondition = 				new LineCondition(-15, brightness);//復帰
	Technic_B_Turn_To_Goal_BDisCondition = 				new DistanceCondition(520, distanceMeasure);//rainsusumu
	Technic_B_Stop_Togoal_Line_BDisCondition = 			new DistanceCondition(725, distanceMeasure);//koeru
	Technic_B_Slow_BDisCondition =						new LineCondition(-15, brightness);//kennti
	Technic_B_Slowspeed_Run_toGoal_BDisCondition =		new LineCondition(-15, brightness);/////////
	Technic_B_Hispeed_Run_BDisCondition =				new DistanceCondition(40, distanceMeasure);//tyotto
	
	Technic_C_Curve2_CDisCondition = 					new LineCondition(-15, brightness);//kaiten
	Technic_C_Over_Green_CDisCondition = 				new DistanceCondition(370 ,distanceMeasure);//gate
	Technic_C_Stop_Lined_CDisCondition = 				new DirectionCondition(365, distanceMeasure);//mawaru
	Technic_C_Edgechange_CDisCondition = 				new LineCondition(-15, brightness);
	Technic_C_Goout_CDisCondition = 					new DistanceCondition(420, distanceMeasure);
	Technic_C_Short_Run_CDisCondition = 				new DistanceCondition(40, distanceMeasure);//
	Technic_C_Turn_to_Curve_4_CDisCondition = 			new LineCondition(-15, brightness);//
	Technic_C_Run_To_Goal_CDisCondition = 				new DistanceCondition(250, distanceMeasure);//
	Technic_C_Slow_Run_Togoal_CDisCondition = 			new DirectionCondition(70, distanceMeasure);//
	Technic_C_Slow_CDisCondition = 						new DistanceCondition(350, distanceMeasure);//
	Technic_C_Slowspeed_Run_toGoal_CDisCondition = 		new DistanceCondition(250, distanceMeasure);//
	Technic_C_Hispeed_Run_CDisCondition =				new DistanceCondition(4000, distanceMeasure);

	Final_StopDisCondition =							new TimeDetectionCondition(2000, &clock);

	//rightコースの走行状態を設定
	lineMode =									new Mode(30, &armMotor, &clock);
	search1Mode =								new Mode(80, &armMotor, &clock);
	search2Mode =								new Mode(95, &armMotor, &clock);
	destroyMode =								new Mode(10, &armMotor, &clock);

	//*****************インスタンスが複数あるクラスの設定**********//

	//PIDの設定
	pid_R_First =			new PID(0.3, 0.0, 3.0);
	pid_R_Look =			new PID(0.5, 0.0, 0.3);
	pid_R_Game =			new PID(0.45, 0.0, 8.5);
	pid_straight =			new PID(0.9, 0.0, 12.5);
	pid_hispeedStraight =	new PID(0.7, 0.0, 6.0);
	pid_curve =				new PID(1.1, 0.0, 11.2);
	pid_gray =				new PID(1.0, 0.0, 12.0);
	pid_Technic_Curve2 =	new PID(0.6, 0.0, 9.4);
	pid_curve3 =			new PID(0.85, 0.0, 13.7);
	pid_End =				new PID(1.5, 0.0, 21.0);


	//rightコース-FirstAreaの走行方法を設定
	Start_StopRun =							new InstructionMethod(0, 0, &leftMotor, &rightMotor);

	First_Long_StraightRun =				new LineTraceMethod(40, 500, 1, 0, brightness, pid_R_First, &leftMotor, &rightMotor);//30
	First_TurnRun =							new InstructionMethod(-20, 20, &leftMotor, &rightMotor);
	First_Short_StraightRun =				new InstructionMethod(30, 30, &leftMotor, &rightMotor);
	First_Detection_LineRun =				new InstructionMethod(30, 30, &leftMotor, &rightMotor);
	First_Return_StraightRun =				new LineTraceMethod(20, 550, 1, 0, brightness, pid_R_First, &leftMotor, &rightMotor);
	First_Return_Short_Straight_RRun =		new InstructionMethod(10, 10, &leftMotor, &rightMotor);
	First_Return_Line_RRun =				new InstructionMethod(20, -20, &leftMotor, &rightMotor);
	First_Return_Detection_Turn_RRun =		new InstructionMethod(20, -20, &leftMotor, &rightMotor);
	First_Return_Short_Straight_LRun =		new InstructionMethod(10, 10, &leftMotor, &rightMotor);
	First_Return_Line_LRun =				new InstructionMethod(-30, 30, &leftMotor, &rightMotor);
	First_Return_Detection_Turn_LRun =		new InstructionMethod(-30, 30, &leftMotor, &rightMotor);

	//rightコース-GameAreaの走行方法を設定
	Game_Color_PlaceRun =					new LineTraceMethod(18, 5, 1, BLACKSIDE, brightness, pid_R_Game, &leftMotor, &rightMotor);//15,3
	Game_CenterRun =						new RatioRotationMethod(1, 0, 20, &leftMotor, &rightMotor, distanceMeasure);
	Game_Short_StraightRun =				new RatioRotationMethod(1, 0, 20, &leftMotor, &rightMotor, distanceMeasure);
	Game_Turn_RRun =						new InstructionMethod(30, -10, &leftMotor, &rightMotor);
	Game_Detection_Turn_RRun =				new InstructionMethod(20, -20, &leftMotor, &rightMotor);
	Game_Turn_LRun =						new InstructionMethod(-10, 30, &leftMotor, &rightMotor);
	Game_Detection_Turn_LRun =				new InstructionMethod(-20, 30, &leftMotor, &rightMotor);
	Game_Revolution_RRun =					new InstructionMethod(20, -8, &leftMotor, &rightMotor);
	Game_Detection_Revolution_RRun =		new InstructionMethod(20, -8, &leftMotor, &rightMotor);
	Game_Revolution_ConnectRun =			new InstructionMethod(-20, 20, &leftMotor, &rightMotor);
	Game_Correct_LineRun =					new InstructionMethod(1, 10, &leftMotor, &rightMotor);
	Game_StraightRun =						new LineTraceMethod(25, 650, 1, 0, brightness, pid_R_Game, &leftMotor, &rightMotor);
	Game_Connect_BackRun =					new InstructionMethod(-15, -15, &leftMotor, &rightMotor);
	Game_Connect_Short_StraightRun =		new InstructionMethod(15, 15, &leftMotor, &rightMotor);
	Game_Connect_Short_Straight_RLRun =		new InstructionMethod(15, 15, &leftMotor, &rightMotor);
	Game_Connect_StraightRun =				new LineTraceMethod(20, 650, 1, 0, brightness, pid_R_Game, &leftMotor, &rightMotor);
	Game_Connect_Turn_SRRun =				new InstructionMethod(15, -15, &leftMotor, &rightMotor);
	Game_Connect_Detection_LineRun =		new InstructionMethod(20, 20, &leftMotor, &rightMotor);
	Game_Connect_Over_PlaceRun =			new RatioRotationMethod(1.8, 0, 30, &leftMotor, &rightMotor, distanceMeasure);
	Game_Connect_Detection_SRun =			new RatioRotationMethod(2.1, 0, 30, &leftMotor, &rightMotor, distanceMeasure);
	Game_Connect_Correct_Line_SRun =		new InstructionMethod(20, -20, &leftMotor, &rightMotor);
	Game_Connect_Turn_RRun =				new InstructionMethod(15, -15, &leftMotor, &rightMotor);
	Game_Connect_Correct_Line_RRun =		new InstructionMethod(20, -20, &leftMotor, &rightMotor);
	Game_Connect_Turn_LRun =				new InstructionMethod(-15, 15, &leftMotor, &rightMotor);
	Game_Connect_Correct_Line_LRun =		new InstructionMethod(-20, 20, &leftMotor, &rightMotor);
	Game_Connect_Revolution_BRun =			new InstructionMethod(30, -30, &leftMotor, &rightMotor);
	Game_Connect_Correct_Line_BRun =		new InstructionMethod(-10, 10, &leftMotor, &rightMotor);

	//rihgtコース-Look_ColorAreaの走行方法を設定
	Look_Color_PlaceRun =					new LineTraceMethod(20, 5, 1, BLACKSIDE, brightness, pid_R_Game, &leftMotor, &rightMotor);
	Look_Color_Short_BackRun =				new InstructionMethod(-20, -20, &leftMotor, &rightMotor);
	Look_Color_Armup_FirstRun =				new InstructionMethod(0, 0, &leftMotor, &rightMotor);
	Look_Color_Armup_SecondRun =			new InstructionMethod(0, 0, &leftMotor, &rightMotor);
	Look_Color_ArmdownRun =					new InstructionMethod(0, 0, &leftMotor, &rightMotor);
	Look_Color_ReturnRun =					new LineTraceMethod(15, 500, 1, BLACKSIDE, brightness, pid_R_Look, &leftMotor, &rightMotor);

	//rightコース-stationAreaの走行方法を設定
	Station_Color_PlaceRun =				new InstructionMethod(0, 0, &leftMotor, &rightMotor);
	Station_Short_BackRun =					new InstructionMethod(-20, -20, &leftMotor, &rightMotor);
	Station_Revolution_RRun =				new InstructionMethod(30, -20, &leftMotor, &rightMotor);
	Station_Detection_Revolution_RRun =		new InstructionMethod(30, -20, &leftMotor, &rightMotor);
	Station_Correct_LineRun =				new InstructionMethod(-30, 30, &leftMotor, &rightMotor);
	Station_StraightRun =					new LineTraceMethod(30, 500, 1, 0, brightness, pid_R_Game, &leftMotor, &rightMotor);

	//rightコース-EscapeAreaの走行方法を設定
	Escape_ConsiderRun =					new RatioRotationMethod(0, 0, 0, &leftMotor, &rightMotor, distanceMeasure);
	Escape_RightRun =						new InstructionMethod(40, -40, &leftMotor, &rightMotor);
	Escape_Short_StraightRun =				new RatioRotationMethod(1, 0, 50, &leftMotor, &rightMotor, distanceMeasure);
	Escape_BackerRun =						new InstructionMethod(40, -40, &leftMotor, &rightMotor);
	Escape_Short_BackerRun =				new RatioRotationMethod(1, 0, 50, &leftMotor, &rightMotor, distanceMeasure);
	Escape_LeftRun =						new InstructionMethod(-40, 40, &leftMotor, &rightMotor);
	Escape_OvercolorRun =					new RatioRotationMethod(1, 0, 50, &leftMotor, &rightMotor, distanceMeasure);
	Escape_Detection_StopRun =				new InstructionMethod(30, 30, &leftMotor, &rightMotor);
	Escape_Short_Run =						new InstructionMethod(30, 30, &leftMotor, &rightMotor);
	Escape_Turn_R90Run =					new InstructionMethod(20, -20, &leftMotor, &rightMotor);
	Escape_Slowspeed_RunRun =				new LineTraceMethod(28, 500, 1, 0, brightness, pid_curve, &leftMotor, &rightMotor);
	Escape_Normal_Run_to1Run =				new LineTraceMethod(55, 40, 1, 0, brightness, pid_hispeedStraight, &leftMotor, &rightMotor);
	Escape_Slowspeed_Run_to2Run =			new LineTraceMethod(40, 40, 1, 0, brightness, pid_curve, &leftMotor, &rightMotor);//
	Escape_Hispeed_Run_to2Run =				new InstructionMethod(-20, 20, &leftMotor, &rightMotor);///
	
	//rightコース-TechnicAreaの走行方法を設定
	Technic_A_Curve2_ARun =					new LineTraceMethod(35, 60, 1, -5, brightness, pid_Technic_Curve2, &leftMotor, &rightMotor);
	Technic_A_Slowspeed_Run_to3_ARun =		new LineTraceMethod(70, 60, 1, 0, brightness, pid_straight, &leftMotor, &rightMotor);
	Technic_A_Hispeed_Run_to3_ARun =		new LineTraceMethod(25, 60, 1, 0, brightness, pid_straight, &leftMotor, &rightMotor);
	Technic_A_StopRun =						new InstructionMethod(0, 0, &leftMotor, &rightMotor);
	Technic_A_Curve_Detection_ARun =		new InstructionMethod(20, -10, &leftMotor, &rightMotor);
	Technic_A_Curve3_Run_ARun =				new LineTraceMethod(35, 40, 1, 8, brightness, pid_curve3, &leftMotor, &rightMotor);
	Technic_A_Hispeed_Run_to4_ARun =		new LineTraceMethod(75, 60, 1, 0, brightness, pid_gray, &leftMotor, &rightMotor);
	Technic_A_Slow_ARun =					new LineTraceMethod(40, 40, 1, 0, brightness, pid_curve3, &leftMotor, &rightMotor);
	Technic_A_Slowspeed_Run_toGoal_ARun =	new LineTraceMethod(50, 40, 1, 0, brightness, pid_curve, &leftMotor, &rightMotor);
	Technic_A_Hispeed_Run_ARun =			new LineTraceMethod(90, 1000, 1, 0, brightness, pid_End, &leftMotor, &rightMotor);
	
	Technic_B_Curve2_BRun = 				new InstructionMethod(50, 50, &leftMotor, &rightMotor);//
	Technic_B_Over_Green_BRun = 			new InstructionMethod(50, 50, &leftMotor, &rightMotor);//
	Technic_B_Stop_Lined_BRun = 			new InstructionMethod(20, 20, &leftMotor, &rightMotor);//
	Technic_B_Short_Run_BRun = 				new InstructionMethod(20, 20, &leftMotor, &rightMotor);//
	Technic_B_Gate_Stop_BRun = 				new InstructionMethod(20, -20, &leftMotor, &rightMotor);//
	Technic_B_Turn_To_Goal_BRun = 			new LineTraceMethod(67, 297, 1, 0, brightness, pid_curve3, &leftMotor, &rightMotor);//
	Technic_B_Stop_Togoal_Line_BRun = 		new InstructionMethod(40, 40, &leftMotor, &rightMotor);
	Technic_B_Slow_BRun =					new InstructionMethod(20, 20, &leftMotor, &rightMotor);
	Technic_B_Slowspeed_Run_toGoal_BRun =	new InstructionMethod(-20, 20, &leftMotor, &rightMotor);/////////////
	Technic_B_Hispeed_Run_BRun =			new InstructionMethod(20, 20, &leftMotor, &rightMotor);
	
	Technic_C_Curve2_CRun = 				new InstructionMethod(-20, 20, &leftMotor, &rightMotor);
	Technic_C_Over_Green_CRun = 			new LineTraceMethod(40, 300, 1, 0, brightness, pid_straight, &leftMotor, &rightMotor);//
	Technic_C_Stop_Lined_CRun = 			new InstructionMethod(20, -20, &leftMotor, &rightMotor);//
	Technic_C_Edgechange_CRun = 			new InstructionMethod(20, -20, &leftMotor, &rightMotor);//
	Technic_C_Goout_CRun = 					new LineTraceMethod(30, 200, 1, 0, brightness, pid_straight, &leftMotor, &rightMotor);//
	Technic_C_Short_Run_CRun = 				new InstructionMethod(40, 40, &leftMotor, &rightMotor);//////
	Technic_C_Turn_to_Curve_4_CRun = 		new InstructionMethod(10, -10, &leftMotor, &rightMotor);////////
	Technic_C_Run_To_Goal_CRun = 			new LineTraceMethod(40, 200, 1, 0, brightness, pid_straight, &leftMotor, &rightMotor);///////
	Technic_C_Slow_Run_Togoal_CRun = 		new LineTraceMethod(40, 500, 1, 0, brightness, pid_straight, &leftMotor, &rightMotor);/////////
	Technic_C_Slow_CRun = 					new LineTraceMethod(35, 500, 1, 0, brightness, pid_curve3, &leftMotor, &rightMotor);///////
	Technic_C_Slowspeed_Run_toGoal_CRun = 	new LineTraceMethod(80, 350, 1, 0, brightness, pid_curve3, &leftMotor, &rightMotor);//////////
	Technic_C_Hispeed_Run_CRun = 			new LineTraceMethod(100, 1000, 1, 0, brightness, pid_End, &leftMotor, &rightMotor);

	Final_StopRun =							new InstructionMethod(0, 0, &leftMotor, &rightMotor);

	//rightコースのFirstAreaの走行区画を設定
	Start_StopBlock =						new RunBlock(0, Start_StopDisCondition, Start_StopRun, distanceMeasure, communication, lineMode);

	First_Long_StraightBlock =				new RunBlock(0, First_Long_StraightDisCondition, First_Long_StraightRun, distanceMeasure, communication, lineMode);
	First_TurnBlock =						new RunBlock(0, First_TurnDisCondition, First_TurnRun, distanceMeasure, communication, lineMode);
	First_Short_StraightBlock =				new RunBlock(0, First_Short_StraightDisCondition, First_Short_StraightRun, distanceMeasure, communication, lineMode);
	First_Detection_LineBlock =				new RunBlock(0, First_Detection_LineDisCondition, First_Detection_LineRun, distanceMeasure, communication, lineMode);
	First_Return_StraightBlock =			new RunBlock(0, First_Return_StraightDisCondition, First_Return_StraightRun, distanceMeasure, communication, lineMode);
	First_Return_Short_Straight_RBlock =	new RunBlock(0, First_Return_Short_Straight_RDisCondition, First_Return_Short_Straight_RRun, distanceMeasure, communication, lineMode);
	First_Return_Line_RBlock =				new RunBlock(0, First_Return_Line_RDisCondition, First_Return_Line_RRun, distanceMeasure, communication, lineMode);
	First_Return_Detection_Turn_RBlock =	new RunBlock(0, First_Return_Detection_Turn_RDisCondition, First_Return_Detection_Turn_RRun, distanceMeasure, communication, lineMode);
	First_Return_Short_Straight_LBlock =	new RunBlock(0, First_Return_Short_Straight_LDisCondition, First_Return_Short_Straight_LRun, distanceMeasure, communication, lineMode);
	First_Return_Line_LBlock =				new RunBlock(0, First_Return_Line_LDisCondition, First_Return_Line_LRun, distanceMeasure, communication, lineMode);
	First_Return_Detection_Turn_LBlock =	new RunBlock(0, First_Return_Detection_Turn_LDisCondition, First_Return_Detection_Turn_LRun, distanceMeasure, communication, lineMode);

	//rightコース-GameAreaの走行区画を設定
	Game_Color_PlaceBlock =					new CrossRunBlock(0, Game_Color_PlaceDisCondition, Game_Color_PlaceRun, distanceMeasure, communication, lineMode, dynamic_cast<DynamicRunArea*>(GameArea), solution);
	Game_Short_StraightBlock =				new RunBlock(1, Game_Short_StraightDisCondition, Game_Short_StraightRun, distanceMeasure, communication, lineMode);
	Game_Turn_RBlock =						new RunBlock(2, Game_Turn_RDisCondition, Game_Turn_RRun, distanceMeasure, communication, lineMode);
	Game_Detection_Turn_RBlock =			new RunBlock(2, Game_Detection_Turn_RDisCondition, Game_Detection_Turn_RRun, distanceMeasure, communication, lineMode);
	Game_Turn_LBlock =						new RunBlock(3, Game_Turn_LDisCondition, Game_Turn_LRun, distanceMeasure, communication, lineMode);
	Game_Detection_Turn_LBlock =			new RunBlock(3, Game_Detection_Turn_LDisCondition, Game_Detection_Turn_LRun, distanceMeasure, communication, lineMode);
	Game_Revolution_RBlock =				new RunBlock(4, Game_Revolution_RDisCondition, Game_Revolution_RRun, distanceMeasure, communication, lineMode);
	Game_Detection_Revolution_RBlock =		new RunBlock(4, Game_Detection_Revolution_RDisCondition, Game_Detection_Revolution_RRun, distanceMeasure, communication, lineMode);
	Game_Revolution_ConnectBlock =			new RunBlock(4, Game_Revolution_ConnectDisCondition, Game_Revolution_ConnectRun, distanceMeasure, communication, lineMode);
	Game_Connect_Turn_SRBlock =				new RunBlock(5, Game_Connect_Turn_SRDisCondition, Game_Connect_Turn_SRRun, distanceMeasure, communication, lineMode);
	Game_Connect_Over_PlaceBlock =			new RunBlock(5, Game_Connect_Over_PlaceDisCondition, Game_Connect_Over_PlaceRun, distanceMeasure, communication, lineMode);
	Game_Connect_Detection_SBlock =			new RunBlock(5, Game_Connect_Detection_SDisCondition, Game_Connect_Detection_SRun, distanceMeasure, communication, lineMode);
	Game_Connect_Correct_Line_SBlock =		new RunBlock(5, Game_Connect_Correct_Line_SDisCondition, Game_Connect_Correct_Line_SRun, distanceMeasure, communication, lineMode);
	Game_Connect_Turn_RBlock =				new RunBlock(6, Game_Connect_Turn_RDisCondition, Game_Connect_Turn_RRun, distanceMeasure, communication, lineMode);
	Game_Connect_Correct_Line_RBlock =		new RunBlock(6, Game_Connect_Correct_Line_RDisCondition, Game_Connect_Correct_Line_RRun, distanceMeasure, communication, lineMode);
	Game_Connect_Turn_LBlock =				new RunBlock(7, Game_Connect_Turn_LDisCondition, Game_Connect_Turn_LRun, distanceMeasure, communication, lineMode);
	Game_Connect_Correct_Line_LBlock =		new RunBlock(7, Game_Connect_Correct_Line_LDisCondition, Game_Connect_Correct_Line_LRun, distanceMeasure, communication, lineMode);
	Game_Connect_Revolution_BBlock =		new RunBlock(8, Game_Connect_Revolution_BDisCondition, Game_Connect_Revolution_BRun, distanceMeasure, communication, lineMode);
	Game_Connect_Correct_Line_BBlock =		new RunBlock(8, Game_Connect_Correct_Line_BDisCondition, Game_Connect_Correct_Line_BRun, distanceMeasure, communication, lineMode);
	Game_CenterBlock =						new RunBlock(10, Game_CenterDisCondition, Game_CenterRun, distanceMeasure, communication, lineMode);
	Game_Correct_LineBlock =				new RunBlock(10, Game_Correct_LineDisCondition, Game_Correct_LineRun, distanceMeasure, communication, lineMode);
	Game_StraightBlock =					new RunBlock(10, Game_StraightDisCondition, Game_StraightRun, distanceMeasure, communication, lineMode);
	Game_Connect_BackBlock =				new RunBlock(11, Game_Connect_BackDisCondition, Game_Connect_BackRun, distanceMeasure, communication, lineMode);
	Game_Connect_Short_StraightBlock =		new RunBlock(11, Game_Connect_Short_StraightDisCondition, Game_Connect_Short_StraightRun, distanceMeasure, communication, lineMode);
	Game_Connect_StraightBlock =			new RunBlock(11, Game_Connect_StraightDisCondition, Game_Connect_StraightRun, distanceMeasure, communication, lineMode);
	Game_Connect_Detection_LineBlock =		new RunBlock(12, Game_Connect_Detection_LineDisCondition, Game_Connect_Detection_LineRun, distanceMeasure, communication, lineMode);
	Game_Connect_Short_Straight_RLBlock =	new RunBlock(12, Game_Connect_Short_Straight_RLDisCondition, Game_Connect_Short_Straight_RLRun, distanceMeasure, communication, lineMode);
	
	//rightコース-Look_ColorAreaの走行区画の設定
	Look_Color_PlaceBlock =					new RunBlock(0, Game_Color_PlaceDisCondition, Game_Color_PlaceRun, distanceMeasure, communication, lineMode);
	Look_Color_Short_BackBlock =			new RunBlock(0, Look_Color_Short_BackDisCondition, Look_Color_Short_BackRun, distanceMeasure, communication, lineMode);
	Look_Color_Armup_FirstBlock =			new RunBlock(0, Look_Color_Armup_FirstDisCondition, Look_Color_Armup_FirstRun, distanceMeasure, communication, search1Mode);
	Look_Color_Armup_SecondBlock =			new LookblockRunBlock(0, Look_Color_Armup_SecondDisCondition, Look_Color_Armup_SecondRun, distanceMeasure, communication, search2Mode, solution);
	Look_Color_ArmdownBlock =				new RunBlock(0, Look_Color_ArmdownDisCondition, Look_Color_ArmdownRun, distanceMeasure, communication, lineMode);
	Look_Color_ReturnBlock =				new RunBlock(0, Look_Color_ReturnDisCondition, Look_Color_ReturnRun, distanceMeasure, communication, lineMode);

	//rightコース-StationAreaの走行区画の設定
	Station_Color_PlaceBlock =				new RunBlock(0, Game_Color_PlaceDisCondition, Game_Color_PlaceRun, distanceMeasure, communication, lineMode);
	Station_Short_BackBlock =				new RunBlock(0, Station_Short_BackDisCondition, Station_Short_BackRun, distanceMeasure, communication, lineMode);
	Station_Revolution_RBlock =				new RunBlock(0, Station_Revolution_RDisCondition, Station_Revolution_RRun, distanceMeasure, communication, lineMode);
	Station_Detection_Revolution_RBlock =	new RunBlock(0, Station_Detection_Revolution_RDisCondition, Station_Detection_Revolution_RRun, distanceMeasure, communication, lineMode);
	Station_Correct_LineBlock =				new RunBlock(0, Station_Correct_LineDisCondition, Station_Correct_LineRun, distanceMeasure, communication, lineMode);
	Station_StraightBlock =					new RunBlock(0, Station_StraightDisCondition, Station_StraightRun, distanceMeasure, communication, lineMode);

	//rightコース-EscapeAreaの走行区画の設定
	Escape_ConsiderBlock = 					new EscapeRunBlock(0, Escape_ConsiderDisCondition, Escape_ConsiderRun, distanceMeasure, communication, lineMode, dynamic_cast<DynamicRunArea*>(EscapeArea), solution);
	Escape_RightBlock= 						new RunBlock(1, Escape_RightDisCondition, Escape_RightRun, distanceMeasure, communication, lineMode);
	Escape_Short_StraightBlock =			new RunBlock(2, Escape_Short_StraightDisCondition, Escape_Short_StraightRun, distanceMeasure, communication, lineMode);
	Escape_BackerBlock =					new RunBlock(3, Escape_BackerDisCondition, Escape_BackerRun, distanceMeasure, communication, lineMode);
	Escape_Short_BackerBlock =				new RunBlock(3, Escape_Short_BackerDisCondition, Escape_Short_BackerRun, distanceMeasure, communication, lineMode);
	Escape_LeftBlock =						new RunBlock(4, Escape_LeftDisCondition, Escape_LeftRun, distanceMeasure, communication, lineMode);
	Escape_OvercolorBlock = 				new RunBlock(0, Escape_OvercolorDisCondition, Escape_OvercolorRun, distanceMeasure, communication, lineMode);
	Escape_Detection_StopBlock =			new RunBlock(0, Escape_Detection_StopDisCondition, Escape_Detection_StopRun, distanceMeasure, communication, lineMode);
	Escape_Short_Block = 					new RunBlock(0, Escape_Short_DisCondition, Escape_Short_Run, distanceMeasure, communication, lineMode);
	Escape_Turn_R90Block = 					new RunBlock(0, Escape_Turn_R90DisCondition, Escape_Turn_R90Run, distanceMeasure, communication, lineMode);
	Escape_Slowspeed_RunBlock =				new RunBlock(0, Escape_Slowspeed_RunDisCondition, Escape_Slowspeed_RunRun, distanceMeasure, communication, lineMode);
	Escape_Normal_Run_to1Block = 			new RunBlock(0, Escape_Turn_FirstDisCondition, Escape_Normal_Run_to1Run, distanceMeasure, communication, lineMode);
	Escape_Slowspeed_Run_to2Block =			new RunBlock(0, Escape_Slowspeed_Run_to2DisCondition, Escape_Slowspeed_Run_to2Run, distanceMeasure, communication, lineMode);
	Escape_Hispeed_Run_to2Block =			new RunBlock(0, Escape_Hispeed_Run_to2DisCondition, Escape_Hispeed_Run_to2Run, distanceMeasure, communication, lineMode);
	
	//rightコース-TechnicAreaの走行区画の設定
	Technic_A_Curve2_ABlock = 				new RunBlock(0, Technic_A_Curve2_ADisCondition, Technic_A_Curve2_ARun, distanceMeasure, communication, lineMode);
	Technic_A_Slowspeed_Run_to3_ABlock =	new RunBlock(0, Technic_A_Slowspeed_Run_to3_ADisCondition, Technic_A_Slowspeed_Run_to3_ARun, distanceMeasure, communication, lineMode);
	Technic_A_Hispeed_Run_to3_ABlock =		new RunBlock(0, Technic_A_Hispeed_Run_to3_ADisCondition, Technic_A_Hispeed_Run_to3_ARun, distanceMeasure, communication, lineMode);
	Technic_A_StopBlock = 					new RunBlock(0, Technic_A_StopDisCondition, Technic_A_StopRun, distanceMeasure, communication, lineMode);
	Technic_A_Curve_Detection_ABlock = 		new RunBlock(0, Technic_A_Curve_Detection_ADisCondition, Technic_A_Curve_Detection_ARun, distanceMeasure, communication, lineMode);
	Technic_A_Curve3_Run_ABlock =			new RunBlock(0, Technic_A_Curve3_Run_ADisCondition, Technic_A_Curve3_Run_ARun, distanceMeasure, communication, lineMode);
	Technic_A_Hispeed_Run_to4_ABlock = 		new RunBlock(0, Technic_A_Hispeed_Run_to4_ADisCondition, Technic_A_Hispeed_Run_to4_ARun, distanceMeasure, communication, lineMode);
	Technic_A_Slow_ABlock =					new RunBlock(0, Technic_A_Slow_ADisCondition, Technic_A_Slow_ARun, distanceMeasure, communication, lineMode);
	Technic_A_Slowspeed_Run_toGoal_ABlock =	new RunBlock(0, Technic_A_Slowspeed_Run_toGoal_ADisCondition, Technic_A_Slowspeed_Run_toGoal_ARun, distanceMeasure, communication, lineMode);
	Technic_A_Hispeed_Run_ABlock =			new RunBlock(0, Technic_A_Hispeed_Run_ADisCondition, Technic_A_Hispeed_Run_ARun, distanceMeasure, communication, lineMode);

	Technic_B_Curve2_BBlock = 			 	new RunBlock(0, Technic_B_Curve2_BDisCondition, Technic_B_Curve2_BRun, distanceMeasure, communication, lineMode);
	Technic_B_Over_Green_BBlock = 			new RunBlock(0, Technic_B_Over_Green_BDisCondition, Technic_B_Over_Green_BRun, distanceMeasure, communication, lineMode);
	Technic_B_Stop_Lined_BBlock =	 		new RunBlock(0, Technic_B_Stop_Lined_BDisCondition, Technic_B_Stop_Lined_BRun, distanceMeasure, communication, lineMode);
	Technic_B_Short_Run_BBlock = 			new RunBlock(0, Technic_B_Short_Run_BDisCondition, Technic_B_Short_Run_BRun, distanceMeasure, communication, lineMode);
	Technic_B_Gate_Stop_BBlock = 	 		new RunBlock(0, Technic_B_Gate_Stop_BDisCondition, Technic_B_Gate_Stop_BRun, distanceMeasure, communication, lineMode);
	Technic_B_Turn_To_Goal_BBlock =		 	new RunBlock(0, Technic_B_Turn_To_Goal_BDisCondition, Technic_B_Turn_To_Goal_BRun, distanceMeasure, communication, lineMode);
	Technic_B_Stop_Togoal_Line_BBlock =  	new RunBlock(0, Technic_B_Stop_Togoal_Line_BDisCondition, Technic_B_Stop_Togoal_Line_BRun, distanceMeasure, communication, lineMode);
	Technic_B_Slow_BBlock =					new RunBlock(0, Technic_B_Slow_BDisCondition, Technic_B_Slow_BRun, distanceMeasure, communication, lineMode);
	Technic_B_Slowspeed_Run_toGoal_BBlock =	new RunBlock(0, Technic_B_Slowspeed_Run_toGoal_BDisCondition, Technic_B_Slowspeed_Run_toGoal_BRun, distanceMeasure, communication, lineMode);
	Technic_B_Hispeed_Run_BBlock =			new RunBlock(0, Technic_B_Hispeed_Run_BDisCondition, Technic_B_Hispeed_Run_BRun, distanceMeasure, communication, lineMode);

	Technic_C_Curve2_CBlock = 			 	new RunBlock(0, Technic_C_Curve2_CDisCondition, Technic_C_Curve2_CRun, distanceMeasure, communication, lineMode);
	Technic_C_Over_Green_CBlock = 			new RunBlock(0, Technic_C_Over_Green_CDisCondition, Technic_C_Over_Green_CRun, distanceMeasure, communication, lineMode);
	Technic_C_Stop_Lined_CBlock =	 		new RunBlock(0, Technic_C_Stop_Lined_CDisCondition, Technic_C_Stop_Lined_CRun, distanceMeasure, communication, lineMode);
	Technic_C_Short_Run_CBlock = 		 	new RunBlock(0, Technic_C_Short_Run_CDisCondition, Technic_C_Short_Run_CRun, distanceMeasure, communication, lineMode);
	Technic_C_Turn_to_Curve_4_CBlock = 	 	new RunBlock(0, Technic_C_Turn_to_Curve_4_CDisCondition, Technic_C_Turn_to_Curve_4_CRun, distanceMeasure, communication, lineMode);
	Technic_C_Run_To_Goal_CBlock =		 	new RunBlock(0, Technic_C_Run_To_Goal_CDisCondition, Technic_C_Run_To_Goal_CRun, distanceMeasure, communication, lineMode);
	Technic_C_Slow_Run_Togoal_CBlock = 	 	new RunBlock(0, Technic_C_Slow_Run_Togoal_CDisCondition, Technic_C_Slow_Run_Togoal_CRun, distanceMeasure, communication, lineMode);
	Technic_C_Goout_CBlock =				new RunBlock(0, Technic_C_Goout_CDisCondition, Technic_C_Goout_CRun, distanceMeasure, communication, lineMode);
	Technic_C_Edgechange_CBlock =			new RunBlock(0, Technic_C_Edgechange_CDisCondition, Technic_C_Edgechange_CRun, distanceMeasure, communication, destroyMode);
	Technic_C_Slow_CBlock =					new RunBlock(0, Technic_C_Slow_CDisCondition, Technic_C_Slow_CRun, distanceMeasure, communication, lineMode);
	Technic_C_Slowspeed_Run_toGoal_CBlock =	new RunBlock(0, Technic_C_Slowspeed_Run_toGoal_CDisCondition, Technic_C_Slowspeed_Run_toGoal_CRun, distanceMeasure, communication, lineMode);
	Technic_C_Hispeed_Run_CBlock =			new RunBlock(0, Technic_C_Hispeed_Run_CDisCondition, Technic_C_Hispeed_Run_CRun, distanceMeasure, communication, lineMode);

	Final_StopBlock =						new RunBlock(0, Final_StopDisCondition, Final_StopRun, distanceMeasure, communication, lineMode);


	//モーターのブレーキ設定
	armMotor.setBrake(false);		// Aモータフロートモード関数：ステアリング
	leftMotor.setBrake(false);			// Bモータフロートモード関数：左モータ
	rightMotor.setBrake(false);		// Cモータフロートモード関数：右モータ
}



static void user_system_destroy() {
	delete  sonarMeter;
	delete  brightness;
	delete	calibration;
	delete	distanceMeasure;
	delete	logdata;


	delete colordisA;
	delete colordisB;
	delete colordisC;
	delete colordisD;
	delete blockA;
	delete blockB;
	delete blockC;
	delete blockD;
	delete solution;
	delete place00;
	delete place01;
	delete place02;
	delete place03;
	delete place10;
	delete place11;
	delete place12;
	delete place13;
	delete place20;
	delete place21;
	delete place22;
	delete place23;
	delete place30;
	delete place31;
	delete place32;
	delete place33;
	delete RedPlacegroup;
	delete BluePlacegroup;
	delete YellowPlacegroup;
	delete GreenPlacegroup;
	delete EscapePlacegroup;
	delete field;
	delete route;


	//FirstArea
	delete  Start_StopDisCondition;

	delete  First_Long_StraightDisCondition;
	delete  First_TurnDisCondition;
	delete  First_Short_StraightDisCondition;
	delete  First_Detection_LineDisCondition;
	delete  First_Return_StraightDisCondition;
	delete  First_Return_Short_Straight_RDisCondition;
	delete  First_Return_Line_RDisCondition;
	delete  First_Return_Detection_Turn_RDisCondition;
	delete  First_Return_Short_Straight_LDisCondition;
	delete  First_Return_Line_LDisCondition;
	delete  First_Return_Detection_Turn_LDisCondition;

	//GameArea
	delete  Game_Color_PlaceDisCondition;
	delete  Game_CenterDisCondition;
	delete  Game_Short_StraightDisCondition;
	delete  Game_Turn_RDisCondition;
	delete  Game_Detection_Turn_RDisCondition;
	delete  Game_Turn_LDisCondition;
	delete  Game_Detection_Turn_LDisCondition;
	delete  Game_Revolution_RDisCondition;
	delete  Game_Detection_Revolution_RDisCondition;
	delete  Game_Revolution_ConnectDisCondition;
	delete  Game_Correct_LineDisCondition;
	delete  Game_StraightDisCondition;
	delete  Game_Connect_BackDisCondition;
	delete  Game_Connect_Short_StraightDisCondition;
	delete  Game_Connect_Short_Straight_RLDisCondition;
	delete  Game_Connect_StraightDisCondition;
	delete  Game_Connect_Turn_SRDisCondition;
	delete  Game_Connect_Detection_LineDisCondition;
	delete  Game_Connect_Over_PlaceDisCondition;
	delete  Game_Connect_Detection_SDisCondition;
	delete  Game_Connect_Correct_Line_SDisCondition;
	delete  Game_Connect_Turn_RDisCondition;
	delete  Game_Connect_Correct_Line_RDisCondition;
	delete  Game_Connect_Turn_LDisCondition;
	delete  Game_Connect_Correct_Line_LDisCondition;
	delete  Game_Connect_Revolution_BDisCondition;
	delete  Game_Connect_Correct_Line_BDisCondition;

	//Look_ColorArea
	delete  Look_Color_PlaceDisCondition;
	delete  Look_Color_Short_BackDisCondition;
	delete  Look_Color_Armup_FirstDisCondition;
	delete  Look_Color_Armup_SecondDisCondition;
	delete  Look_Color_ArmdownDisCondition;
	delete  Look_Color_ReturnDisCondition;

	//StationArea
	delete  Station_Color_PlaceDisCondition;
	delete  Station_Short_BackDisCondition;
	delete  Station_Revolution_RDisCondition;
	delete  Station_Detection_Revolution_RDisCondition;
	delete  Station_Correct_LineDisCondition;
	delete  Station_StraightDisCondition;

	//EscapeArea
	delete  Escape_ConsiderDisCondition;
	delete  Escape_RightDisCondition;
	delete  Escape_Short_StraightDisCondition;
	delete  Escape_BackerDisCondition;
	delete  Escape_Short_BackerDisCondition;
	delete  Escape_LeftDisCondition;
	delete	Escape_OvercolorDisCondition;
	delete  Escape_Detection_StopDisCondition;
	delete	Escape_Short_DisCondition;
	delete  Escape_Turn_R90DisCondition;
	delete  Escape_Slowspeed_RunDisCondition;
	delete  Escape_Turn_FirstA;
	delete  Escape_Turn_FirstB;
	delete  Escape_Turn_FirstDisCondition;
	delete  Escape_Slowspeed_Run_to2DisCondition;
	delete  Escape_Hispeed_Run_to2DisCondition;

	//TechnicArea
	delete	Technic_A_Curve2_ADisCondition;
	delete	Technic_A_Slowspeed_Run_to3_ADisCondition;
	delete	Technic_A_Hispeed_Run_to3_ADisCondition;
	delete  Technic_A_StopDisCondition;
	delete  Technic_A_Curve_Detection_ADisCondition;
	delete  Technic_A_Curve3_Run_ADisCondition;
	delete  Technic_A_Hispeed_Run_to4_ADisCondition;
	delete	Technic_A_Slow_ADisCondition;
	delete  Technic_A_Slowspeed_Run_toGoal_ADisCondition;
	delete	Technic_A_Hispeed_Run_ADisCondition;

	delete	Technic_B_Curve2_BDisCondition;
	delete	Technic_B_Over_Green_BDisCondition;
	delete	Technic_B_Stop_Lined_BDisCondition;
	delete  Technic_B_Short_Run_BDisCondition;
	delete  Technic_B_Gate_Stop_BDisCondition;
	delete  Technic_B_Turn_To_Goal_BDisCondition;
	delete  Technic_B_Stop_Togoal_Line_BDisCondition;
	delete	Technic_B_Slow_BDisCondition;
	delete  Technic_B_Slowspeed_Run_toGoal_BDisCondition;
	delete	Technic_B_Hispeed_Run_BDisCondition;
	
	delete	Technic_C_Curve2_CDisCondition;
	delete	Technic_C_Over_Green_CDisCondition;
	delete	Technic_C_Stop_Lined_CDisCondition;
	delete  Technic_C_Short_Run_CDisCondition;
	delete  Technic_C_Turn_to_Curve_4_CDisCondition;
	delete  Technic_C_Run_To_Goal_CDisCondition;
	delete  Technic_C_Slow_Run_Togoal_CDisCondition;
	delete	Technic_C_Goout_CDisCondition;
	delete	Technic_C_Edgechange_CDisCondition;
	delete	Technic_C_Slow_CDisCondition;
	delete  Technic_C_Slowspeed_Run_toGoal_CDisCondition;
	delete	Technic_C_Hispeed_Run_CDisCondition;

	delete  Final_StopDisCondition;


	//FirstArea
	delete  Start_StopRun;

	delete	First_Long_StraightRun;
	delete	First_TurnRun;
	delete	First_Short_StraightRun;
	delete	First_Detection_LineRun;
	delete	First_Return_StraightRun;
	delete	First_Return_Short_Straight_RRun;
	delete	First_Return_Line_RRun;
	delete	First_Return_Detection_Turn_RRun;
	delete	First_Return_Short_Straight_LRun;
	delete	First_Return_Line_LRun;
	delete	First_Return_Detection_Turn_LRun;

	//GameArea
	delete	Game_Color_PlaceRun;
	delete  Game_CenterRun;
	delete  Game_Short_StraightRun;
	delete  Game_Turn_RRun;
	delete  Game_Detection_Turn_RRun;
	delete  Game_Turn_LRun;
	delete  Game_Detection_Turn_LRun;
	delete  Game_Revolution_RRun;
	delete  Game_Detection_Revolution_RRun;
	delete  Game_Revolution_ConnectRun;
	delete  Game_Correct_LineRun;
	delete	Game_StraightRun;
	delete	Game_Connect_BackRun;
	delete	Game_Connect_Short_StraightRun;
	delete	Game_Connect_Short_Straight_RLRun;
	delete	Game_Connect_StraightRun;
	delete	Game_Connect_Turn_SRRun;
	delete	Game_Connect_Detection_LineRun;
	delete	Game_Connect_Over_PlaceRun;
	delete	Game_Connect_Detection_SRun;
	delete	Game_Connect_Correct_Line_SRun;
	delete	Game_Connect_Turn_RRun;
	delete	Game_Connect_Correct_Line_RRun;
	delete	Game_Connect_Turn_LRun;
	delete	Game_Connect_Correct_Line_LRun;
	delete	Game_Connect_Revolution_BRun;
	delete	Game_Connect_Correct_Line_BRun;

	//Look_ColorArea
	delete	Look_Color_PlaceRun;
	delete  Look_Color_Short_BackRun;
	delete  Look_Color_Armup_FirstRun;
	delete  Look_Color_Armup_SecondRun;
	delete  Look_Color_ArmdownRun;
	delete  Look_Color_ReturnRun;

	//StationArea
	delete	Station_Color_PlaceRun;
	delete  Station_Short_BackRun;
	delete  Station_Revolution_RRun;
	delete  Station_Detection_Revolution_RRun;
	delete  Station_Correct_LineRun;
	delete	Station_StraightRun;

	//EscapeArea
	delete  Escape_ConsiderRun;
	delete  Escape_RightRun;
	delete  Escape_Short_StraightRun;
	delete  Escape_BackerRun;
	delete  Escape_Short_BackerRun;
	delete  Escape_LeftRun;
	delete	Escape_OvercolorRun;
	delete	Escape_Detection_StopRun;
	delete	Escape_Short_Run;
	delete  Escape_Turn_R90Run;
	delete  Escape_Slowspeed_RunRun;
	delete	Escape_Normal_Run_to1Run;
	delete  Escape_Slowspeed_Run_to2Run;
	delete	Escape_Hispeed_Run_to2Run;

	//TechnicArea
	delete	Technic_A_Curve2_ARun;
	delete	Technic_A_Slowspeed_Run_to3_ARun;
	delete	Technic_A_Hispeed_Run_to3_ARun;
	delete  Technic_A_StopRun;
	delete  Technic_A_Curve_Detection_ARun;
	delete  Technic_A_Curve3_Run_ARun;
	delete  Technic_A_Hispeed_Run_to4_ARun;
	delete	Technic_A_Slow_ARun;
	delete  Technic_A_Slowspeed_Run_toGoal_ARun;
	delete	Technic_A_Hispeed_Run_ARun;

	delete	Technic_B_Curve2_BRun;
	delete	Technic_B_Over_Green_BRun;
	delete	Technic_B_Stop_Lined_BRun;
	delete  Technic_B_Short_Run_BRun;
	delete  Technic_B_Gate_Stop_BRun;
	delete  Technic_B_Turn_To_Goal_BRun;
	delete  Technic_B_Stop_Togoal_Line_BRun;
	delete	Technic_B_Slow_BRun;
	delete  Technic_B_Slowspeed_Run_toGoal_BRun;
	delete	Technic_B_Hispeed_Run_BRun;

	delete	Technic_C_Curve2_CRun;
	delete	Technic_C_Over_Green_CRun;
	delete	Technic_C_Stop_Lined_CRun;
	delete  Technic_C_Short_Run_CRun;
	delete  Technic_C_Turn_to_Curve_4_CRun;
	delete  Technic_C_Run_To_Goal_CRun;
	delete  Technic_C_Slow_Run_Togoal_CRun;
	delete	Technic_C_Goout_CRun;
	delete	Technic_C_Edgechange_CRun;
	delete	Technic_C_Slow_CRun;
	delete  Technic_C_Slowspeed_Run_toGoal_CRun;
	delete	Technic_C_Hispeed_Run_CRun;

	delete  Final_StopRun;


	//FirstArea
	delete  Start_StopBlock;

	delete	First_Long_StraightBlock;
	delete	First_TurnBlock;
	delete	First_Short_StraightBlock;
	delete	First_Detection_LineBlock;
	delete	First_Return_StraightBlock;
	delete	First_Return_Short_Straight_RBlock;
	delete	First_Return_Line_RBlock;
	delete	First_Return_Detection_Turn_RBlock;
	delete	First_Return_Short_Straight_LBlock;
	delete	First_Return_Line_LBlock;
	delete	First_Return_Detection_Turn_LBlock;

	//GameArea
	delete	Game_Color_PlaceBlock;
	delete  Game_CenterBlock;
	delete  Game_Short_StraightBlock;
	delete  Game_Turn_RBlock;
	delete  Game_Detection_Turn_RBlock;
	delete  Game_Turn_LBlock;
	delete  Game_Detection_Turn_LBlock;
	delete  Game_Revolution_RBlock;
	delete  Game_Detection_Revolution_RBlock;
	delete  Game_Revolution_ConnectBlock;
	delete  Game_Correct_LineBlock;
	delete	Game_StraightBlock;
	delete	Game_Connect_BackBlock;
	delete	Game_Connect_Short_StraightBlock;
	delete	Game_Connect_Short_Straight_RLBlock;
	delete	Game_Connect_StraightBlock;
	delete	Game_Connect_Turn_SRBlock;
	delete	Game_Connect_Detection_LineBlock;
	delete	Game_Connect_Over_PlaceBlock;
	delete	Game_Connect_Detection_SBlock;
	delete	Game_Connect_Correct_Line_SBlock;
	delete	Game_Connect_Turn_RBlock;
	delete	Game_Connect_Correct_Line_RBlock;
	delete	Game_Connect_Turn_LBlock;
	delete	Game_Connect_Correct_Line_LBlock;
	delete	Game_Connect_Revolution_BBlock;
	delete	Game_Connect_Correct_Line_BBlock;

	//Look_ColorArea
	delete	Look_Color_PlaceBlock;
	delete  Look_Color_Short_BackBlock;
	delete  Look_Color_Armup_FirstBlock;
	delete  Look_Color_Armup_SecondBlock;
	delete  Look_Color_ArmdownBlock;
	delete  Look_Color_ReturnBlock;

	//StationArea
	delete	Station_Color_PlaceBlock;
	delete  Station_Short_BackBlock;
	delete  Station_Revolution_RBlock;
	delete  Station_Detection_Revolution_RBlock;
	delete  Station_Correct_LineBlock;
	delete	Station_StraightBlock;

	//EscapeArea
	delete  Escape_ConsiderBlock;
	delete  Escape_RightBlock;
	delete  Escape_Short_StraightBlock;
	delete  Escape_BackerBlock;
	delete  Escape_Short_BackerBlock;
	delete  Escape_LeftBlock;
	delete	Escape_OvercolorBlock;
	delete	Escape_Detection_StopBlock;
	delete	Escape_Short_Block;
	delete  Escape_Turn_R90Block;
	delete  Escape_Slowspeed_RunBlock;
	delete	Escape_Normal_Run_to1Block;
	delete  Escape_Slowspeed_Run_to2Block;
	delete	Escape_Hispeed_Run_to2Block;

	//TechnicArea
	delete	Technic_A_Curve2_ABlock;
	delete	Technic_A_Slowspeed_Run_to3_ABlock;
	delete	Technic_A_Hispeed_Run_to3_ABlock;
	delete  Technic_A_StopBlock;
	delete  Technic_A_Curve_Detection_ABlock;
	delete  Technic_A_Curve3_Run_ABlock;
	delete  Technic_A_Hispeed_Run_to4_ABlock;
	delete	Technic_A_Slow_ABlock;
	delete  Technic_A_Slowspeed_Run_toGoal_ABlock;
	delete	Technic_A_Hispeed_Run_ABlock;
	
	delete	Technic_B_Curve2_BBlock;
	delete	Technic_B_Over_Green_BBlock;
	delete	Technic_B_Stop_Lined_BBlock;
	delete  Technic_B_Short_Run_BBlock;
	delete  Technic_B_Gate_Stop_BBlock;
	delete  Technic_B_Turn_To_Goal_BBlock;
	delete  Technic_B_Stop_Togoal_Line_BBlock;
	delete	Technic_B_Slow_BBlock;
	delete  Technic_B_Slowspeed_Run_toGoal_BBlock;
	delete	Technic_B_Hispeed_Run_BBlock;

	delete	Technic_C_Curve2_CBlock;
	delete	Technic_C_Over_Green_CBlock;
	delete	Technic_C_Stop_Lined_CBlock;
	delete  Technic_C_Short_Run_CBlock;
	delete  Technic_C_Turn_to_Curve_4_CBlock;
	delete  Technic_C_Run_To_Goal_CBlock;
	delete  Technic_C_Slow_Run_Togoal_CBlock;
	delete	Technic_C_Goout_CBlock;
	delete	Technic_C_Edgechange_CBlock;
	delete	Technic_C_Slow_CBlock;
	delete  Technic_C_Slowspeed_Run_toGoal_CBlock;
	delete	Technic_C_Hispeed_Run_CBlock;
	
	delete  Final_StopBlock;


	delete  FirstArea;
	delete  GameArea;
	delete  Look_ColorArea;
	delete  StationArea;
	delete  BLArea;
	delete	EscapeArea;
	delete  Technic_AArea;
	delete  Technic_BArea;
	delete  Technic_CArea;
	delete	rightCourse;
	delete	pid_R_First;
	delete	pid_hispeedStraight;
	delete	pid_R_Look;
	delete	pid_R_Game;
	delete  pid_straight;
	delete  pid_hispeedStraight;
	delete  pid_curve;
	delete  pid_End;
	delete  pid_gray;
	delete  pid_Technic_Curve2;
	delete  pid_curve3;
	delete	sound;
	delete	speedoMeter;
	delete	communication;
	delete  lineMode;
	delete  search1Mode;
	delete  search2Mode;
	delete  destroyMode;
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

	bt = ev3_serial_open_file(EV3_SERIAL_BT);
	assert(bt != NULL);

	//***********置き場に周辺置き場を設定する***********/
	place00->addAdjoinPlace(place10, place01, nullptr, nullptr);
	place01->addAdjoinPlace(place11, place02, place00, nullptr);
	place02->addAdjoinPlace(place12, place03, place01, nullptr);
	place03->addAdjoinPlace(place13, nullptr, place02, nullptr);
	place10->addAdjoinPlace(place20, place11, nullptr, place00);
	place11->addAdjoinPlace(place21, place12, place10, place01);
	place12->addAdjoinPlace(place22, place13, place11, place02);
	place13->addAdjoinPlace(place23, nullptr, place12, place03);
	place20->addAdjoinPlace(place30, place21, nullptr, place10);
	place21->addAdjoinPlace(place31, place22, place20, place11);
	place22->addAdjoinPlace(place32, place23, place21, place12);
	place23->addAdjoinPlace(place33, nullptr, place22, place13);
	place30->addAdjoinPlace(nullptr, place31, nullptr, place20);
	place31->addAdjoinPlace(nullptr, place32, place30, place21);
	place32->addAdjoinPlace(nullptr, place33, place31, place22);
	place33->addAdjoinPlace(nullptr, nullptr, place32, place23);

	//***********ルートに置き場を設定する*************/
	route->addPlace(place00);
	route->addPlace(place01);
	route->addPlace(place02);
	route->addPlace(place03);
	route->addPlace(place10);
	route->addPlace(place11);
	route->addPlace(place12);
	route->addPlace(place13);
	route->addPlace(place20);
	route->addPlace(place21);
	route->addPlace(place22);
	route->addPlace(place23);
	route->addPlace(place30);
	route->addPlace(place31);
	route->addPlace(place32);
	route->addPlace(place33);
	//***********フィールドに置き場を設定する*************/
	field->addPlace(place00);
	field->addPlace(place01);
	field->addPlace(place02);
	field->addPlace(place03);
	field->addPlace(place10);
	field->addPlace(place11);
	field->addPlace(place12);
	field->addPlace(place13);
	field->addPlace(place20);
	field->addPlace(place21);
	field->addPlace(place22);
	field->addPlace(place23);
	field->addPlace(place30);
	field->addPlace(place31);
	field->addPlace(place32);
	field->addPlace(place33);

	//*************フィールドに置き場群を設定する*************/
	field->addPlacegroup(RedPlacegroup);
	field->addPlacegroup(BluePlacegroup);
	field->addPlacegroup(YellowPlacegroup);
	field->addPlacegroup(GreenPlacegroup);
	field->addPlacegroup(EscapePlacegroup);

	//***********設定した走行エリアや走行区画を走行コースや走行エリアが所有するリストに追加する（走行の順番を決める）***************************/
	/**rightコースの走行エリアの順番の設定**/

	rightCourse->addRunArea(FirstArea);
	rightCourse->addRunArea(BLArea);
	rightCourse->addRunArea(EscapeArea);
	//rightCourse->addRunArea(Technic_AArea);//ノーマル
	rightCourse->addRunArea(Technic_BArea);//ピンクショートカット
	rightCourse->addRunArea(Technic_CArea);


	/**rightコースのstraightArea（スタートエリア）の走行区画の順番の設定**/

	//FirstArea
	FirstArea->addBlock(Start_StopBlock);

	FirstArea->addBlock(First_Long_StraightBlock);
	FirstArea->addBlock(First_TurnBlock);
	FirstArea->addBlock(First_Short_StraightBlock);
	FirstArea->addBlock(First_Detection_LineBlock);
	////////////////////////////////////////////////////////////
	FirstArea->addBlock(First_Return_Short_Straight_RBlock);
	FirstArea->addBlock(First_Return_Line_RBlock);				//右に曲がる時
	FirstArea->addBlock(First_Return_Detection_Turn_RBlock);
	FirstArea->addBlock(First_Return_StraightBlock);
	////////////////////////////////////////////////////////////
	//FirstArea->addBlock(First_Return_Short_Straight_LBlock);
	//FirstArea->addBlock(First_Return_Line_LBlock);					//左に曲がる時
	//FirstArea->addBlock(First_Return_Detection_Turn_LBlock);
	//FirstArea->addBlock(First_Return_StraightBlock);

	//GameArea
	GameArea->addBlock(Game_Color_PlaceBlock);
	GameArea->addBlock(Game_CenterBlock);
	GameArea->addBlock(Game_Short_StraightBlock);
	GameArea->addBlock(Game_Turn_RBlock);
	GameArea->addBlock(Game_Detection_Turn_RBlock);
	GameArea->addBlock(Game_Turn_LBlock);
	GameArea->addBlock(Game_Detection_Turn_LBlock);
	GameArea->addBlock(Game_Revolution_RBlock);
	GameArea->addBlock(Game_Detection_Revolution_RBlock);
	GameArea->addBlock(Game_Revolution_ConnectBlock);
	GameArea->addBlock(Game_Correct_LineBlock);
	GameArea->addBlock(Game_StraightBlock);
	GameArea->addBlock(Game_Connect_BackBlock);
	GameArea->addBlock(Game_Connect_Turn_SRBlock);
	GameArea->addBlock(Game_Connect_Turn_RBlock);
	GameArea->addBlock(Game_Connect_Turn_LBlock);
	GameArea->addBlock(Game_Connect_Revolution_BBlock);
	GameArea->addBlock(Game_Connect_Detection_LineBlock);
	GameArea->addBlock(Game_Connect_Over_PlaceBlock);
	GameArea->addBlock(Game_Connect_Detection_SBlock);
	GameArea->addBlock(Game_Connect_Short_StraightBlock);
	GameArea->addBlock(Game_Connect_Correct_Line_SBlock);
	GameArea->addBlock(Game_Connect_Correct_Line_RBlock);
	GameArea->addBlock(Game_Connect_Correct_Line_LBlock);
	GameArea->addBlock(Game_Connect_Correct_Line_BBlock);
	GameArea->addBlock(Game_Connect_StraightBlock);

	//Look_ColorArea
	Look_ColorArea->addBlock(Look_Color_PlaceBlock);
	Look_ColorArea->addBlock(Look_Color_Short_BackBlock);
	Look_ColorArea->addBlock(Look_Color_Armup_FirstBlock);
	Look_ColorArea->addBlock(Look_Color_Armup_SecondBlock);
	Look_ColorArea->addBlock(Look_Color_ArmdownBlock);
	Look_ColorArea->addBlock(Look_Color_ReturnBlock);

	//StationArea
	StationArea->addBlock(Station_Color_PlaceBlock);

	//EscapeArea
	EscapeArea->addBlock(Escape_ConsiderBlock);
	EscapeArea->addBlock(Escape_RightBlock);
	EscapeArea->addBlock(Escape_Short_StraightBlock);
	EscapeArea->addBlock(Escape_BackerBlock);
	EscapeArea->addBlock(Escape_Short_BackerBlock);
	EscapeArea->addBlock(Escape_LeftBlock);
	EscapeArea->addBlock(Escape_OvercolorBlock);//ブロック並べ地帯からの離脱
	EscapeArea->addBlock(Escape_Detection_StopBlock);//ライン上で停止する
	EscapeArea->addBlock(Escape_Short_Block);
	EscapeArea->addBlock(Escape_Turn_R90Block);//ライントレースさせる為約90°回転
	EscapeArea->addBlock(Escape_Slowspeed_RunBlock);//機体をラインの上に乗せるため低速で走行
	EscapeArea->addBlock(Escape_Normal_Run_to1Block);//第１カーブまで移動
	//EscapeArea->addBlock(Final_StopBlock);
	//EscapeArea->addBlock(Escape_Slowspeed_Run_to2Block);//機体をラインの上に乗せるため低速で走行
	//EscapeArea->addBlock(Escape_Hispeed_Run_to2Block);//第２カーブまで移動
	
	//TechnicArea
	Technic_AArea->addBlock(Technic_A_Curve2_ABlock);//第２カーブを低速で移動
	Technic_AArea->addBlock(Technic_A_Slowspeed_Run_to3_ABlock);//機体をラインの上に乗せるため低速で走行
	Technic_AArea->addBlock(Technic_A_Hispeed_Run_to3_ABlock);//第３カーブまで移動
	Technic_AArea->addBlock(Technic_A_StopBlock);
	Technic_AArea->addBlock(Technic_A_Curve_Detection_ABlock);//ライントレースさせる為約90°回転
	Technic_AArea->addBlock(Technic_A_Curve3_Run_ABlock);//第３カーブを低速で移動
	Technic_AArea->addBlock(Technic_A_Hispeed_Run_to4_ABlock);//第４カーブまで移動
	Technic_AArea->addBlock(Technic_A_Slow_ABlock);//低速前進
	Technic_AArea->addBlock(Technic_A_Slowspeed_Run_toGoal_ABlock);//機体をラインの上に乗せるため低速で走行
	Technic_AArea->addBlock(Technic_A_Hispeed_Run_ABlock);//ゴールまで直進
	Technic_AArea->addBlock(Final_StopBlock);
	
	Technic_BArea->addBlock(Escape_Slowspeed_Run_to2Block);
	Technic_BArea->addBlock(Escape_Hispeed_Run_to2Block);
	Technic_BArea->addBlock(Technic_B_Curve2_BBlock);//第２カーブを低速で移動
	Technic_BArea->addBlock(Technic_B_Over_Green_BBlock);//機体をラインの上に乗せるため低速で走行
	Technic_BArea->addBlock(Technic_B_Stop_Lined_BBlock);//第３カーブまで移動
	Technic_BArea->addBlock(Technic_B_Short_Run_BBlock);
	Technic_BArea->addBlock(Technic_B_Gate_Stop_BBlock);//ライントレースさせる為約90°回転
	Technic_BArea->addBlock(Technic_B_Turn_To_Goal_BBlock);//第３カーブを低速で移動
	Technic_BArea->addBlock(Technic_B_Stop_Togoal_Line_BBlock);//第４カーブまで移動
	Technic_BArea->addBlock(Technic_B_Slow_BBlock);//低速前進
	//Technic_BArea->addBlock(Technic_B_Slowspeed_Run_toGoal_BBlock);//機体をラインの上に乗せるため低速で走行
	Technic_BArea->addBlock(Technic_B_Hispeed_Run_BBlock);//ゴールまで直進
	//Technic_BArea->addBlock(Final_StopBlock);
	
	Technic_CArea->addBlock(Technic_C_Curve2_CBlock);//第２カーブを低速で移動
	Technic_CArea->addBlock(Technic_C_Over_Green_CBlock);//しかし緑は越えない
	Technic_CArea->addBlock(Technic_C_Stop_Lined_CBlock);//むしろ緑で止まる
	Technic_CArea->addBlock(Technic_C_Edgechange_CBlock);//しろ
	Technic_CArea->addBlock(Technic_C_Goout_CBlock);//くろ
	//Technic_CArea->addBlock(Technic_C_Short_Run_CBlock);//すすむ
	//Technic_CArea->addBlock(Technic_C_Turn_to_Curve_4_CBlock);//ライントレースさせる為約90°回転
	//Technic_CArea->addBlock(Technic_C_Run_To_Goal_CBlock);//第３カーブを低速で移動
	//Technic_CArea->addBlock(Technic_C_Slow_Run_Togoal_CBlock);//第４カーブまで移動
	//Technic_CArea->addBlock(Technic_C_Slow_CBlock);//低速前進
	//Technic_CArea->addBlock(Technic_C_Slowspeed_Run_toGoal_CBlock);//機体をラインの上に乗せるため低速で走行
	Technic_CArea->addBlock(Technic_C_Hispeed_Run_CBlock);//ゴールまで直進
	Technic_CArea->addBlock(Final_StopBlock);



	ev3_speaker_play_tone(NOTE_C4, 100);
	tslp_tsk(200);
	//**************************************************************/

	lineMode->preMode();
	rightCourse->prepareRun();

	ev3_speaker_play_tone(NOTE_C4, 100);
	//各周期ハンドラを起動させる。（周期タスクが開始する）
	ev3_sta_cyc(EV3_CYC_RUN);
	ev3_sta_cyc(EV3_CYC_COMMUNICATION);
	ev3_sta_cyc(EV3_CYC_EMERGENCYSTOP);
	slp_tsk();
	ev3_stp_cyc(EV3_CYC_RUN);
	ev3_stp_cyc(EV3_CYC_COMMUNICATION);
	ev3_stp_cyc(EV3_CYC_EMERGENCYSTOP);

	user_system_destroy();
	ext_tsk();
}

void run_task(intptr_t exinf)
{
	speedoMeter->update();

	//int log1 = 0, log2 = 0, log3 = 0, log4 = 0, log5 = 0, log6 = 0, log7 = 0, log8 = 0, log9 = 0, log10 = 0, log11 = 0, log12 = 0, log13 = 0, log14 = 0, log15 = 0, log16 = 0;
	//dynamic_cast<BlockplaceCondition*>(Game_Color_PlaceDisCondition)->log(log1, log2, log3);
	//routeInfo->log(log1, log2, log3, log4, log5, log6);
	//field->log(log1, log2, log3, log4, log5, log6, log7, log8, log9, log10, log11, log12, log13, log14, log15, log16);
	//route->log(log1, log2, log3);
/*fprintf(bt, "%d,", log1);
	fprintf(bt, "%d,", log2);
	fprintf(bt, "%d,", log3);
	fprintf(bt, "%d,", log4);
	fprintf(bt, "%d,", log5);
	fprintf(bt, "%d,", log6);
	fprintf(bt, "%d,", log7);
	fprintf(bt, "%d,", log8);
	fprintf(bt, "%d,", log9);
	fprintf(bt, "%d,", log10);
	fprintf(bt, "%d,", log11);
	fprintf(bt, "%d,", log12);
	fprintf(bt, "%d,", log13);
	fprintf(bt, "%d,", log14);
	fprintf(bt, "%d,", log15);
	fprintf(bt, "%d\n", log16);*/

	if (rightCourse->startRun() == true) {
		armMotor.setPWM(0);
		leftMotor.setPWM(0);
		rightMotor.setPWM(0);
		ev3_stp_cyc(EV3_CYC_RUN);
		ext_tsk();
	}
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
