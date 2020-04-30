#include "variables.h"
//#define DETAIL_VARIABLE // 用于调试牌型
std::vector< std::vector<int> > board; // 棋盘

std::vector< std::vector<int> > remember; // 用于记录操作


const int PLAYER = 1; // player默认先手
const int AI = 2; // AI默认后手

int BOARD_SIZE = 0;
bool is_black = true; // 默认是先手


std::map<Type, int> SCOREMAP;
std::map<int, std::string> DIRECTIONMAP;
std::map<std::string, Type> TYPEMAP;
std::map<Type, std::string> TYPENAMEMAP;

template <typename T>
void combine_inner(T& data, int start, int n, int m, int depth, T temp, std::vector<T>& result)
{
    if (depth == m - 1)
    {
        //最内层循环 将temp加入result
        for (int i = start; i < n - (m - depth - 1); ++i)
        {
            temp[depth] = data[i];
            result.push_back(temp);
        }
    }
    else
        for (int i = start; i < n - (m - depth - 1); ++i)
        {
            temp[depth] = data[i];//每层输出一个元素
            combine_inner(data, i + 1, n, m, depth + 1, temp, result);
        }
}

//T可以调入vector<int>, string等，需要支持下标[]操作及size()函数
template <typename T>
std::vector<T> combine(T& data, int m)
{
    if (m <= 0)
        return{};
    int depth = 0;
    std::vector<T> result;
    T temp(m, 0);
    combine_inner(data, 0, data.size(), m, depth, temp, result);
    return result;
}

std::string Permutation(int n, int r) // 制作nCr组合数, 用01表示
{
    std::string a(r, '1');
    std::string b(n - r, '0');

    return b + a;
}

void InitVariables()
{
    SCOREMAP[ONE] = 10;
    SCOREMAP[TWO] = 100;
    SCOREMAP[THREE] = 1000;
    SCOREMAP[FOUR] = 100000;
    SCOREMAP[FIVE] = 10000000;
    SCOREMAP[BLOCKED_ONE] = 1;
    SCOREMAP[BLOCKED_TWO] = 10;
    SCOREMAP[BLOCKED_THREE] = 100;
    SCOREMAP[BLOCKED_FOUR] = 10000;

    DIRECTIONMAP[0] = "垂直方向";
    DIRECTIONMAP[1] = "水平方向";
    DIRECTIONMAP[2] = "反斜杠方向";
    DIRECTIONMAP[3] = "斜杠方向";

    TYPENAMEMAP[ONE] = "ONE";
    TYPENAMEMAP[TWO] = "TWO";
    TYPENAMEMAP[THREE] = "THREE";
    TYPENAMEMAP[FOUR] = "FOUR";
    TYPENAMEMAP[FIVE] = "FIVE";
    TYPENAMEMAP[BLOCKED_ONE] = "BLOCKED_ONE";
    TYPENAMEMAP[BLOCKED_TWO] = "BLOCKED_TWO";
    TYPENAMEMAP[BLOCKED_THREE] = "BLOCKED_THREE";
    TYPENAMEMAP[BLOCKED_FOUR] = "BLOCKED_FOUR";


    for (int lenth = 5; lenth <= 9; lenth++) // 表示长度
    {
        for (int j = 1; j <= lenth; j++) // 每个长度都有几种表示方法
        {
            std::string choice = Permutation(lenth, j);
            do {
                //std::cout << choice << std::endl;
                if (choice.find("11111") != std::string::npos) // 匹配活5
                {
                    TYPEMAP[choice] = FIVE;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("011110") != std::string::npos) // 匹配活4
                {
                    TYPEMAP[choice] = FOUR;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }
                if (choice.find("101110111") != std::string::npos) // 匹配活4
                {
                    TYPEMAP[choice] = FOUR;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }


                if (choice.find("111011101") != std::string::npos) // 匹配活4
                {
                    TYPEMAP[choice] = FOUR;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }
                if (choice.find("11011011") != std::string::npos) // 匹配活4
                {
                    TYPEMAP[choice] = FOUR;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("110110110") != std::string::npos) // 匹配活4
                {
                    TYPEMAP[choice] = FOUR;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }
                if (choice.find("011011011") != std::string::npos) // 匹配活4
                {
                    TYPEMAP[choice] = FOUR;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("01111") != std::string::npos) // 匹配死4
                {
                    TYPEMAP[choice] = BLOCKED_FOUR;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("11110") != std::string::npos) // 匹配死4
                {
                    TYPEMAP[choice] = BLOCKED_FOUR;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("10111") != std::string::npos) // 匹配死4
                {
                    TYPEMAP[choice] = BLOCKED_FOUR;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("11101") != std::string::npos) // 匹配死4
                {
                    TYPEMAP[choice] = BLOCKED_FOUR;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("11011") != std::string::npos) // 匹配死4
                {
                    TYPEMAP[choice] = BLOCKED_FOUR;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("01110") != std::string::npos) // 匹配活3
                {
                    TYPEMAP[choice] = THREE;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("011010") != std::string::npos) // 匹配活3
                {
                    TYPEMAP[choice] = THREE;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("010110") != std::string::npos) // 匹配活3
                {
                    TYPEMAP[choice] = THREE;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("0101010") != std::string::npos) // 匹配活3
                {
                    TYPEMAP[choice] = THREE;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }


                if (choice.find("10101") != std::string::npos) // 匹配死3
                {
                    TYPEMAP[choice] = BLOCKED_THREE;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("11001") != std::string::npos) // 匹配死3
                {
                    TYPEMAP[choice] = BLOCKED_THREE;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("10011") != std::string::npos) // 匹配死3
                {
                    TYPEMAP[choice] = BLOCKED_THREE;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("11100") != std::string::npos) // 匹配死3
                {
                    TYPEMAP[choice] = BLOCKED_THREE;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("00111") != std::string::npos) // 匹配死3
                {
                    TYPEMAP[choice] = BLOCKED_THREE;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("11010") != std::string::npos) // 匹配死3
                {
                    TYPEMAP[choice] = BLOCKED_THREE;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("01011") != std::string::npos) // 匹配死3
                {
                    TYPEMAP[choice] = BLOCKED_THREE;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("01100") != std::string::npos) // 匹配活2
                {
                    TYPEMAP[choice] = TWO;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("00110") != std::string::npos) // 匹配活2
                {
                    TYPEMAP[choice] = TWO;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("01010") != std::string::npos) // 匹配活2
                {
                    TYPEMAP[choice] = TWO;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("010010") != std::string::npos) // 匹配活2
                {
                    TYPEMAP[choice] = TWO;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("11000") != std::string::npos) // 匹配死2
                {
                    TYPEMAP[choice] = BLOCKED_TWO;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("00011") != std::string::npos) // 匹配死2
                {
                    TYPEMAP[choice] = BLOCKED_TWO;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("00101") != std::string::npos) // 匹配死2
                {
                    TYPEMAP[choice] = BLOCKED_TWO;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("10100") != std::string::npos) // 匹配死2
                {
                    TYPEMAP[choice] = BLOCKED_TWO;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("10010") != std::string::npos) // 匹配死2
                {
                    TYPEMAP[choice] = BLOCKED_TWO;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("01001") != std::string::npos) // 匹配死2
                {
                    TYPEMAP[choice] = BLOCKED_TWO;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("10010") != std::string::npos) // 匹配死2
                {
                    TYPEMAP[choice] = BLOCKED_TWO;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("10001") != std::string::npos) // 匹配死2
                {
                    TYPEMAP[choice] = BLOCKED_TWO;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("00010") != std::string::npos) // 匹配活1
                {
                    TYPEMAP[choice] = ONE;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("00100") != std::string::npos) // 匹配活1
                {
                    TYPEMAP[choice] = ONE;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("01000") != std::string::npos) // 匹配活1
                {
                    TYPEMAP[choice] = ONE;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("00001") != std::string::npos) // 匹配死1
                {
                    TYPEMAP[choice] = BLOCKED_ONE;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }

                if (choice.find("10000") != std::string::npos) // 匹配死1
                {
                    TYPEMAP[choice] = BLOCKED_ONE;
#ifdef DETAIL_VARIABLE   
                    std::cout << choice << TYPENAMEMAP[TYPEMAP[choice]] << std::endl;
#endif
                    continue;
                }


                assert(true);  // 理论上讲不可能到这里
            } while (std::next_permutation(choice.begin(), choice.end()));
        }

    }
}

void Drop(int who, int row, int col) // 落子
{
    board[row][col] = who; // 落子

    std::vector<int> rem; // 步骤记录
    rem.push_back(row);
    rem.push_back(col);

    remember.push_back(rem);
}

void Undo() // 悔棋
{
    assert(board[(remember.back())[0]][(remember.back())[1]]); // 撤销的应该是有值的

    board[(remember.back())[0]][(remember.back())[1]] = 0; // 撤销
    remember.pop_back();

    return;
}

std::string szPoint(int row, int col) // 输出某一点
{
    return "( " + std::to_string(row) + " , " + std::to_string(col) + " )  "
        + std::to_string(board[row][col]);
}