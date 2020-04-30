#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <regex>
#include <assert.h>
#include <algorithm>
#include <map>

extern std::vector< std::vector<int> > board; // 棋盘

extern std::vector< std::vector<int> > remember; // 用于记录操作

extern const int PLAYER; // player默认先手
extern const int AI; // AI默认后手

extern int BOARD_SIZE;
extern bool is_black; // 默认是先手
enum Type {
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	BLOCKED_ONE,
	BLOCKED_TWO,
	BLOCKED_THREE,
	BLOCKED_FOUR,
};

extern std::map<Type, int> SCOREMAP;
extern std::map<int, std::string> DIRECTIONMAP;
extern std::map<std::string, Type> TYPEMAP;
extern std::map<Type, std::string> TYPENAMEMAP;

void InitVariables();

void Drop(int who, int row, int col);

void Undo();

std::string szPoint(int row, int col); // 输出某一点
