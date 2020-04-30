#include "Player.h"
void Drop(int row, int col)
{
	board[row][col] = PLAYER;

	std::vector<int> rem;
	rem.push_back(row);
	rem.push_back(col);

	remember.push_back(rem);
}

bool PlayerDrop(int row, int col) // 玩家下棋
{
	if (row < 0 || col < 0 || row >= BOARD_SIZE || col >= BOARD_SIZE)
	{
		std::cout << "索引错误！！" << std::endl;
		return false;
	}

	if (board[row][col])
	{
		std::cout << "已经有子啦！！" << std::endl;
		return false;
	}

	Drop(row, col);
	
	Evaluate();
	return true;
}
