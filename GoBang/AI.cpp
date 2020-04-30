#include "AI.h"
#define SHOW_DETAIL




std::clock_t start;


inline bool in(int x)
{
	return x >= 0 && x <= BOARD_SIZE - 1; // x在棋盘内
}

std::string szShowBoard() // 输出棋盘
{
	std::string temp;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			switch (board[i][j])
			{
			case 0:
				temp += "+";
				break;
			case 1:
				temp += "@";
				break;
			case 2:
				temp += "O";
				break;
			}
			temp += " ";
		}
		temp += '\n';
	}

	return temp;
}






void FindBest(int level) 
{

}



void AiTurn()
{
	start = clock();
	// 第一层遍历一遍后排序，确认搜索顺序
	std::vector<Deduction> root; // root层对所有考虑

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			Deduction temp(0, i, j);

		}
	}


	std::cout << (double)(clock() - start) / CLOCKS_PER_SEC * 1000 << " ms " << std::endl;

}