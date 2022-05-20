#pragma once
#include <SFML/Graphics.hpp>

const int MENU_BUTTONS_INT_RECT[8][2] = { {24,23}, {21, 35}, {18, 31}, {21, 15},{21, 16},{30,30},{37,37},{25,24} };
const int MENU_BUTTONS_LOC[8][2] = { {210, 205}, {160, 205}, {100,205},{105, 112},{105, 128} , {185,165},{115,165},{185,165} };

const int SOUND_X = 172;
const int SOUND_Y = 120;


const int CHOSE_LEVEL_BUTTONS_INT_RECT[3][2] = { {48, 18}, {21, 15}, {21, 16} };
const int CHOSE_LEVEL_BUTTONS_LOC[3][2] = { {200, 150}, {140, 145}, {141,165} };

const int TOOLBAR_BUTTONS_LOC[2][2] = {{21, 15}, {21,16}};

const int SCORE_PIX_LOC_SIZE = 10;
const int SC_N_H = 21;


const int DELTA_ENGINE_CONECT[2][2] = {{13,-6}, {13,0}}; //1 mouse engine, fix change name, 2conveyor

const int NUM_OF_OBJECTS = 11; // update when adding an object 

const int BUTTON_DELTA_TYPE = 100;
enum Type_t
{
	//objects
	balloon,
	basketBall,
	baseBall,
	bowlingBall,
	conveyor,
	brickWall,
	pipeWall,
	fancyWall,
	mouseEngine,
	trampoline,
	scissors,
	belt,
	//---------

	play,
	arrowRButton,
	arrowLButton,
	menuBackground,
	frame,
	sound,
	//menu buttons
	exitButton,
	startButton,
	reset,
	upSound,
	downSound,
	choseLevel,
	build,
	save,
	endMenuButtons,
	//-----------

	//chose level menu
	choseLevelMenu,
	playButton,
	upButton,
	downButton,
	endChoseLevelButtons,


	//----------------
	none,
	rotateButton,
	resizeButton,

	puzzleComplete,
	replayButton,
	advanceButton,
	onePixel,

	connectButton,

	numbers,
	score,
	
	balloonButton = BUTTON_DELTA_TYPE,
	basketButton,
	baseButton,
	bowlingButton,
	conveyorButton,
	brickWallButton,
	pipeWallButton,
	fancyWallButton,
	mouseEngineButton,
	trampolineButton,
	scissorsButton,
	beltButton


};

struct ObjInfo
{
	Type_t _typ;
	sf::Vector2f _loc;
	int _angle = -1;
	int _size = -1;
	int _fliped = -1; // -1 not intersting, 0 regular , 1 filped
};

const struct ObjInfo wallInitTransforms = {brickWall, sf::Vector2f(0.f,0.f), 0, 1, -1};// fix check if everyone starts like this and then no need


struct PhysicsInfo
{
	bool _shape;
	float _friction;
	float _restitution;
	float _density;
};

 const bool CIRCLE = true;
 const bool RECT = false;



 const PhysicsInfo physicsInfo[NUM_OF_OBJECTS] = {{CIRCLE, 0.1f, 0.4f, 0.7f},    //balloon
                                                  {CIRCLE, 0.5f, 0.775f, 0.2f},  //basketBall
                                                  {CIRCLE, 0.8f, 0.4f, 0.25f},  //baseBall
                                                  {CIRCLE, 0.5f, 0.2f, 0.2f},    //bowlingBall
                                                  {RECT,   0.5f, 0.4f, 0.7f},    //conveyor
                                                  {RECT,   0.5f, 0.4f, 0.7f},   //brickWall
												  {RECT,   0.5f, 0.4f, 0.7f},   //pipeWall
												  {RECT,   0.5f, 0.4f, 0.7f},   //fancyWall
												  {RECT,   0.5f, 0.4f, 0.7f},   //mouseEngine
												  {RECT,   0.5f, 0.4f, 0.7f},   //trampoline
												  {RECT,   0.5f, 0.4f, 0.7f}};   //trampoline 

	// m_fixtureDef.friction = 1;
    // m_fixtureDef.restitution = 0.4f;
    // m_fixtureDef.density = 0.7f;


const float TIMESTEP = 1.0f / 60.0f;
const int VELITER = 10;
const int POSITER = 10;

const int NUM_DIFF = 10;


const bool DYNAMIC = true;
const bool STATIC = false;
const bool MOVABLE = true;
const bool UNMOVABLE = false;

const float DEG_TO_RAD = 0.0174533f;

//images
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 450;


const int FLOORING_UNIT = 16; //pixels
const int FLOORING_MARGIN = 1; //pix
const int FRAME_SIZE = 8;
const int SCORE_H = 60;

const int FRAME_X = WINDOW_WIDTH/2;
const int FRAME_Y = (WINDOW_HEIGHT-SCORE_H)/2;

const int PLAY_BUTTON_H = 50;
const int ARROWS_H = 20;

const int TB_W = 56;
const int TB_H = WINDOW_HEIGHT - SCORE_H - PLAY_BUTTON_H - ARROWS_H-60;//frames
const int TB_TOP = 100;//PLAYH+ARRH+3FRAMES~


const int TB_X = WINDOW_WIDTH - FRAME_SIZE - TB_W; //topleft
const int TB_OBJ_X = WINDOW_WIDTH - FRAME_SIZE- TB_W/2;

const int PLAY_Y = FRAME_SIZE + PLAY_BUTTON_H/2;
const int ARROWS_Y = PLAY_BUTTON_H + 2*FRAME_SIZE + ARROWS_H/2;
const int ARROWS_W = TB_W/2;
const int L_ARR_X = TB_OBJ_X - ARROWS_W/2;
const int R_ARR_X = TB_OBJ_X + ARROWS_W/2;

const int BAR_Y = PLAY_BUTTON_H + ARROWS_H + TB_H/2;

const float BUTTON_SCALE = .9f;

const int MENU_X = (WINDOW_WIDTH - (TB_W + FRAME_SIZE*2)) /2;
const int MENU_Y = (WINDOW_HEIGHT - SCORE_H - FRAME_SIZE) / 2;


const float BOARD_W = 560;
const float BOARD_H = 352;
const float TINY_BOARD_W = 263;
const float TINY_BOARD_H = 166;

const float BOARDS_RATIO_X = TINY_BOARD_W / BOARD_W ;
const float BOARDS_RATIO_Y = TINY_BOARD_H / BOARD_H ;


const int PUZZLE_COMPLETE_X = 400;
const int PUZZLE_COMPLETE_Y = 300;
const int REPLAY_BUTTON_X = 350;
const int REPLAY_BUTTON_Y = 350;
const int ADVANCE_BUTTON_X = 460;
const int ADVANCE_BUTTON_Y = 350;

const int SC_H = 67;
const int SC_N_W = 24;
const int INT_RECT_H = 42;
const int SC_SEP = 8;
const int SC_N_INITIAL = WINDOW_WIDTH/2 - SC_N_W*2;

const int SC_X =  WINDOW_WIDTH/2;
const int SC_Y = 404;

const int SC_INS_RECT_Y = 198;
const int SC_INS_RECT_X = 0;

const int NUM_OF_NUMBERS_TEX = 4;

const int NUM_DELTA_Y_FROM_SCORE = 12;

const int INIT_SCORE = 9999;

const int BUTTONS_IN_PAGE = 5;
const int SPACING = 25;
const int BUTTON_OBJ_SIZE = (TB_H-(SPACING*(BUTTONS_IN_PAGE+1)))/BUTTONS_IN_PAGE;


const float PPM = 64.f;
const float MPP = 0.015625f;

const unsigned CHARATER_SIZE = 11;
const float CHARATER_OUTLINE_THICKNESS = 0.1; 

const sf::Vector2f PUZZLE_COMPLETE{ FRAME_X, FRAME_Y };
const sf::Vector2f REPLAY_BUTTON{ PUZZLE_COMPLETE .x - 50,PUZZLE_COMPLETE .y+40};
const sf::Vector2f ADVANCE_BUTTON{ PUZZLE_COMPLETE.x+50,REPLAY_BUTTON .y};

const sf::Vector2f LEVEL_GOAL_TEXT_LOC{ 70,270 };
const sf::Vector2f LEVEL_SCORE_TEXT_LOC{ FRAME_X-40,FRAME_Y+15 };

const sf::Vector2f LEVEL_NO_TEXT_LOC_MENU{ 95,36 };
const sf::Vector2f LEVEL_NAME_TEXT_LOC_MENU{ 200,36 };

const sf::Vector2f LEVEL_NO_TEXT_LOC_CHOSE_LEVEL{ 125,85.5 };
const sf::Vector2f LEVEL_NAME_TEXT_LOC_CHOSE_LEVEL{ 80,204 };

const double ANIMATION_TIME = 0.5;


const int MENU = 0;
const int CHOOSE_LEVEL = 1;
const int BUILD = 2;

const bool ON = true;
const bool OFF = false;


const int SMALLEST_SIZE = 	1;
const int BIGGEST_SIZE = 	5;
const int FIRST_ANGLE = 	0;
const int LAST_ANGLE = 		3;
const int NOT_RELEVANT=		-1; //future updates will include fliping


const int MEDIUM_VOL = 	56;
const int VOL_STEP = 	14;
const int VOL_MAX = 	100;
const int VOL_MIN = 	0;

const int NO_ONE = -1;

const bool SAVE = false;
const bool OPEN = true;

const int INFINITE_AMOUNT = -1;

const bool RUNNING = true;
const bool NOT_RUNNING = false;


const int MID_VOL_X = 440;
const int VOL_Y_RECT = 0;
const int VOL_WIDTH = 110;
const int VOL_HEIGHT = 28;

const int NUM_OF_SOUNDS = 6;