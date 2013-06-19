#ifndef __resource_h__
#define __resource_h__
//images
static const char s_menu[] = "menu.png";
static const char s_bg[] = "bg.png";
static const char s_pause[] = "pause.png";
static const char s_play[] = "play.png";
static const char s_menuTitle[] = "menuTitle.png";
static const char s_gameBg[] = "game_bg.png";
static const char s_tom[] = "tom.jpg";
static const char s_jerry[] = "jerry.jpg";
static const char s_floor[] = "wall.png";
static const char s_ygBG[] = "yg_bg.png";
static const char s_yg[] = "yg.png";
static const char s_gameOver[] = "gameOver.png";
static const char s_exit[] = "exit.png";
static const char s_option[] = "option.png";

static const char* s_tomRight[] = {"right1.png", "right2.png", "right3.png", "right4.png"};
static const char* s_tomLeft[] = {"left1.png", "left2.png", "left3.png", "left4.png"};
static const char* s_tomUp[] = {"back1.png", "back2.png", "back1.png", "back2.png"};
static const char* s_tomDown[] = {"front1.png", "front2.png", "front1.png", "front2.png"};

static const char* s_jerryRight[] = {"mouce_right.png", "mouce_right.png", "mouce_right.png", "mouce_right.png"};
static const char* s_jerryLeft[] = {"mouce_left.png", "mouce_left.png", "mouce_left.png", "mouce_left.png"};
static const char* s_jerryUp[] = {"mouce_back.png", "mouce_back.png", "mouce_back.png", "mouce_back.png"};
static const char* s_jerryDown[] = {"mouce_front.png", "mouce_front.png", "mouce_front.png", "mouce_front.png"};

//font
static const char s_font[] = "Font/bitmapFontTest.fnt";

//Levels
static const char s_level1[] = "Levels/level1.txt";

//map
const int rows = 12;
const int cols = 16;
static int i_map[rows][cols] = {0};

//
enum Direction {UP, DOWN, LEFT, RIGHT, NONE};

#endif
