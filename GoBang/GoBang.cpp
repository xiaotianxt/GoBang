// GoBang.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "variables.h"
#include "AI.h"
#include "Player.h"

#define SHOW_DETAIL // 是否显示详情



void PrintBoard() // 输出当前棋局
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			switch (board[i][j])
			{
			case 0:
				std::cout << '+' << ' ';
				break;
			case 1:
				std::cout << '@' << ' ';
				break;
			case 2:
				std::cout << 'O' << ' ';
				break;
			}
		}
		std::cout << std::endl;
	}
}

void BoardInit()
{
	int temp_input;

	std::cout << "请输入棋盘尺寸：" << std::endl;
	while (true)
	{
		std::cin >> temp_input;
		if ((temp_input <= 5) || (temp_input > 50)) // 不能过大/过小
		{
			std::cout << "请输入5~50的棋盘尺寸！" << std::endl;
			continue;
		}
		else
			break;
	}

	BOARD_SIZE = temp_input; // 棋盘大小

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		std::vector<int>temp_row;
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			temp_row.push_back(0);
		}

		board.push_back(temp_row);
	}

	assert(board[1][1] == 0);
	
#ifdef _DEBUG
	std::cout << "数组尺寸" << board.size() * board.size() << std::endl;
#endif // DEBUG



	std::cout << "开始下围棋！" << std::endl;

}

void Withdraw(int num) // 撤销
{
	assert(board[(remember.back())[0]][(remember.back())[1]]); // 撤销的应该是有值的

	for (int i = 0; i < num; i++)
	{
		board[(remember.back())[0]][(remember.back())[1]] = 0; // 撤销
		remember.pop_back();
	}

	return;
}

bool WinCheck(int who) // 是否胜利
{
	int row = (remember.back())[0];
	int col = (remember.back())[1];

	// 向上下找找
	int count = 0;
	int add = 1;

	while ((row + add < BOARD_SIZE) && board[row + add][col] == who) count++, add++;
	add = 1;
	while ((row - add >= 0) && board[row - add][col] == who) count++, add++;

	if (count == 4) return true;

	// 向左右找找
	count = 0;
	add = 1;

	while ((col + add < BOARD_SIZE) && board[row][col + add] == who) count++, add++;
	add = 1;
	while ((col - add >= 0) && board[row][col - add] == who) count++, add++;

	if (count >= 4)	return true;

	// 斜杠方向

	count = 0;
	add = 1;

	while ((row + add < BOARD_SIZE) && (col + add < BOARD_SIZE) && board[row + add][col + add] == who) count++, add++;
	add = 1;
	while ((row - add >= 0) && (col - add >= 0) && board[row - add][col - add] == who) count++, add++;

	if (count == 4)	return true;

	//反斜杠

	count = 0;
	add = 1;

	while ((row + add < BOARD_SIZE) && (col - add >= 0) && board[row + add][col - add] == who) count++, add++;
	add = 1;
	while ((row - add >= 0) && (col + add < BOARD_SIZE) && board[row - add][col + add] == who) count++, add++;

	if (count == 4)	return true;

	return false;
}



void Play()
{
	std::string temp_line; // 用于记录操作
	std::smatch result;
	std::regex pattern("(\\d+)\\s+(\\d+)");
	if (AI == 1) // 如果AI是先手
	{

		board[BOARD_SIZE / 2][BOARD_SIZE / 2] = AI; // 直接在棋盘中间下棋
		std::vector<int> rem;
		rem.push_back(BOARD_SIZE);
		rem.push_back(BOARD_SIZE);


		remember.push_back(rem); // 存下来
	}

	while (true) // 开始打游戏
	{
		while (true) // 玩家下棋
		{
			std::getline(std::cin, temp_line);

			if (std::regex_match(temp_line, result, pattern))
			{
				if (!PlayerDrop(atoi(result[1].str().c_str()), atoi(result[2].str().c_str()))) // 下棋知道成功
				{
					PrintBoard();
					std::cout << "索引有误！" << std::endl;
					continue;
				}

				PrintBoard();
				if (WinCheck(PLAYER))
				{
					std::cout << "YOU WIN!!!" << std::endl;
					return;
				}
				break; // 下棋成功，离开
			}
		}

		//AiTurn();
		if (WinCheck(AI))
		{
			std::cout << "AI WINS!!" << std::endl;

			return;
		}

	}
}

void Initialize()
{
	InitVariables();
	BoardInit();
	Play();
	return;
}

int main()
{
	Initialize();
}

