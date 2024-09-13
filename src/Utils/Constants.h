#pragma once

#define RED slSetForeColor(255, 0, 0, 1);
#define GREEN slSetForeColor(0, 255, 0, 1);
#define BLUE slSetForeColor(0, 0, 255, 1);
#define WHITE slSetForeColor(255, 255, 255, 1);
#define BLACK slSetForeColor(0, 0, 0, 1);

//Screen size
const int screenWidth = 1280;
const int screenHeight = 720;

//Screen Limits
const int limitDown = 15;
const int limitUp = screenHeight - limitDown;
const int limitLeft = limitDown;
const int limitRight = screenWidth - limitLeft;

const int paddleSpeed = 700;