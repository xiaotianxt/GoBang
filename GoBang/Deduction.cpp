#include "Deduction.h"
#define SHOW_DETAIL


int Evaluate() // 评估某一落子
{
	int row = (remember.back())[0]; // 记录行
	int col = (remember.back())[1]; // 记录列
	int who = board[row][col]; // 记录是sei

	int score = 0;

	int dir[8] = { 1, 0, 0, 1, 1, 1, 1, -1 }; // 用于提供方向，两两一组
	for (int i = 0; i < 4; i++) // 四个方向
	{
		const int addr = dir[i * 2];
		const int addc = dir[i * 2 + 1]; // 确认方向

		// 首先找到边界

		int fbound[2] = { row, col };
		int tbound[2] = { row, col };

		for (int i = 1; i < 5; i++) // 向后查找4个是否可以延伸
		{
			if (fbound[0] - addr < 0 || fbound[1] - addc > BOARD_SIZE - 1 ||
				fbound[0] - addr > BOARD_SIZE - 1 || fbound[1] - addc < 0) // 如果已经到了结尾
			{
				break;
			}
			if (board[fbound[0] - addr][fbound[1] - addc] != who && board[fbound[0] - addr][fbound[1] - addc] != 0) // 如果是敌方
				break;
			else
			{
				fbound[0] -= addr;
				fbound[1] -= addc;
			}
		}

		for (int i = 1; i < 5; i++) // 向后查找4个是否可以延伸
		{
			if (tbound[0] + addr < 0 || tbound[1] + addc > BOARD_SIZE - 1 ||
				tbound[0] + addr > BOARD_SIZE - 1 || tbound[1] + addc < 0) // 如果已经到了结尾
			{
				break;
			}
			if (board[tbound[0] + addr][tbound[1] + addc] != who
				&& board[tbound[0] + addr][tbound[1] + addc] != 0) // 如果是敌方
				break;
			else
			{
				tbound[0] += addr;
				tbound[1] += addc;
			}
		}

#ifdef SHOW_DETAIL
		std::cout << "方向：" << DIRECTIONMAP[i] << std::endl;
		std::cout << addr << ' ' << addc << std::endl;
		std::cout << "边界为点 " << szPoint(fbound[0], fbound[1]) << " 和 "
			<< szPoint(tbound[0], tbound[1]) << std::endl;
		//std::cout << szShowBoard() << std::endl;
#endif

		// ***************开始在此方向上查找******************//

		int lenth = 0;
		if (i != 1) // 除了垂直的情况，否则都可以用fbound判断长度
			lenth = tbound[0] - fbound[0] + 1;
		else
			lenth = tbound[1] - fbound[1] + 1;

#ifdef SHOW_DETAIL
		std::cout << "长度为" << lenth << std::endl;
#endif // SHOW_DETAIL

		if (lenth < 5) // 如果长度太短就不需要考虑了
			continue;

		int x = fbound[0];
		int y = fbound[1]; // 存储当前位置

		std::string temp = ""; // 用于检索棋型

		for (int i = 0; i < lenth; i++) // 遍历所有位置,构建字符串
		{
			if (board[x][y]) // 如果有棋子
				temp += '1';
			else
				temp += '0';

			x += addr;
			y += addc;
		}

		score += SCOREMAP[TYPEMAP[temp]]; // 匹配得分
#ifdef SHOW_DETAIL
		std::cout << "得分" << score << std::endl;
#endif // SHOW_DETAIL

	}
#ifdef SHOW_DETAIL
	std::cout << "总得分" << score << std::endl;
#endif
	return score;
}

Deduction::Deduction(int level, int x, int y)
{
	score = Evaluate(); // 下在这里的得分
}

void Deduction::dfs(int remain)
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (level % 2) // 如果是奇数层，需要遍历ai下棋
			{
				Drop(AI, i, j);
				Deduction child(level + 1, i, j);
				
				Undo();
			}

		}
	}
}
