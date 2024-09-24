#pragma once

//Cambiar
#define ORANGE slSetForeColor(255, 255, 0, 1);
#define RED slSetForeColor(255, 0, 0, 1);
#define GREEN slSetForeColor(0, 255, 0, 1);
#define BLUE slSetForeColor(0, 0, 255, 1);
#define WHITE slSetForeColor(255, 255, 255, 1);
#define BLACK slSetForeColor(0, 0, 0, 1);

#ifndef PI
#define PI 3.14159265358979323846f
#endif


//Screen size
const int screenWidth = 1280;
const int screenHeight = 720;

//Screen Limits
const int limitDown = 15;
const int limitUp = screenHeight - limitDown;
const int limitLeft = limitDown;
const int limitRight = screenWidth - limitLeft;

//Blocks
const float blockWidth = 106; //screenWidth / 12;
const float blockHeight = 36; //screenHeight / 20;
const int blockCols = 12; //screenWidth / blockWidth;
const int blockRows = 6; //(screenHeight / 3) / blockHeight;
const int totalBlocks = blockCols * blockRows; //72

//Paddle Speed
const int paddleSpeed = 700;

//Keys
const char KEY_SPACE = 32;

//Font size 
const int baseFontSize = 50;