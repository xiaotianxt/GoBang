#pragma once
#include "variables.h"


class Deduction // 一次下子后的推演
{
public:
	int score; // 推演结果封装在推演中
	int level; // 推演在第n层
	int x, y; // 推演建立在哪一个点下棋的基础上
	bool visited = false; // 建立的时候没有访问
	Deduction* previous; // 上一个推演
	std::vector<Deduction*> children; // 建立在此推演基础上的推演

	Deduction(int level, int x, int y);
	void dfs(int remain);

};

