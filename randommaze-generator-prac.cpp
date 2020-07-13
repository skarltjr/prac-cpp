#include<iostream>
#include<stack>
#include<queue>
//#include"Location2D.h"
#include<random>
struct Location2D
{
	int row;
	int col;
	Location2D(int a = 0, int b = 0) { row = a, col = b; }
	bool isNeighbor(Location2D& p)
	{
		return ((row == p.row) && (col == p.col + 1 || col == p.col - 1))
			|| ((col == p.col) && (row == p.row + 1 || row == p.row - 1));
	}
	bool operator==(Location2D& p)
	{
		return row == p.row && col == p.col;
	}

};
const int MAZE_SIZE = 9;
/*
e:입구
o:출구
x:벽
r:길 로 설정해보기
*/
char map[MAZE_SIZE][MAZE_SIZE] =
{
	{'x', 'x', 'x', 'x', 'x', 'x','x','x','x'},
	{'x', 'x', 'x', 'x', 'x', 'x','x','x','x'},
	{'x', 'x', 'x', 'x', 'x', 'x','x','x','x'},
	{'x', 'x', 'x', 'x', 'x', 'x','x','x','x'},
	{'x', 'x', 'x', 'x', 'x', 'x','x','x','x'},
	{'x', 'x', 'x', 'x', 'x', 'x','x','x','x'},
	{'x', 'x', 'x', 'x', 'x', 'x','x','x','x'},
	{'x', 'x', 'x', 'x', 'x', 'x','x','x','x'},
	{'x', 'x', 'x', 'x', 'x', 'x','x','x','x'}
};

int getRandomNum()//랜덤으로 난수만들어주고 if로 n~m까지는 어느방향으로 가도록 설정해줘보자
{
	int a;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(1, 100);//1부터 100까지만
	a = dis(gen);
	return a;
}
bool isValidLoc(int r, int c)
{
	if (r < 0 || c < 0 || r >= MAZE_SIZE || c >= MAZE_SIZE) { return false; }
	else { return  map[r][c] == 'x'; }
}
bool isValidLoc_solve(int r, int c)//탐색을 위한 함수 따로 구현하기
{
	if (r < 0 || c < 0 || r >= MAZE_SIZE || c >= MAZE_SIZE) { return false; }
	else { return  map[r][c] == 'r' || map[r][c] == 'o'; }
}
int main()
{
	std::stack<Location2D> mine;
	Location2D start(0, 0);
	mine.push(start);
	while (mine.empty() == false)
	{
		Location2D here = mine.top();
		mine.pop();
		int r = here.row;
		int c = here.col;
		int a = getRandomNum();
		//std::cout << a << " ";
		if (a >= 1 && a < 25)//두 점을 이어주는 길이 존재한다. 두 점을 설정하고 점과 그 사이를 모두 길로 만들어보자
		{
			if (isValidLoc(r - 2, c))
			{
				mine.push(Location2D(r - 2, c)); map[r][c] = 'r'; map[r - 1][c] = 'r'; map[r - 2][c] = 'r';
			}
			if (isValidLoc(r, c + 2))
			{
				mine.push(Location2D(r, c + 2)); map[r][c] = 'r'; map[r][c + 1] = 'r'; map[r][c + 2] = 'r';
			}
			if (isValidLoc(r + 2, c))
			{
				mine.push(Location2D(r + 2, c)); map[r][c] = 'r'; map[r + 1][c] = 'r'; map[r + 2][c] = 'r';
			}
			if (isValidLoc(r, c - 2))
			{
				mine.push(Location2D(r, c - 2)); map[r][c] = 'r'; map[r][c - 1] = 'r'; map[r][c - 2] = 'r';
			}
		}
		else if (a >= 25 && a < 50)
		{
			if (isValidLoc(r, c + 2))
			{
				mine.push(Location2D(r, c + 2)); map[r][c] = 'r'; map[r][c + 1] = 'r'; map[r][c + 2] = 'r';
			}
			if (isValidLoc(r, c - 2))
			{
				mine.push(Location2D(r, c - 2)); map[r][c] = 'r'; map[r][c - 1] = 'r'; map[r][c - 2] = 'r';
			}
			if (isValidLoc(r - 2, c))
			{
				mine.push(Location2D(r - 2, c)); map[r][c] = 'r'; map[r - 1][c] = 'r'; map[r - 2][c] = 'r';
			}
			if (isValidLoc(r + 2, c))
			{
				mine.push(Location2D(r + 2, c)); map[r][c] = 'r'; map[r + 1][c] = 'r'; map[r + 2][c] = 'r';
			}
		}
		else if (a >= 50 && a < 75)
		{
			if (isValidLoc(r + 2, c))
			{
				mine.push(Location2D(r + 2, c)); map[r][c] = 'r'; map[r + 1][c] = 'r'; map[r + 2][c] = 'r';
			}
			if (isValidLoc(r, c - 2))
			{
				mine.push(Location2D(r, c - 2)); map[r][c] = 'r'; map[r][c - 1] = 'r'; map[r][c - 2] = 'r';
			}
			if (isValidLoc(r - 2, c))
			{
				mine.push(Location2D(r - 2, c)); map[r][c] = 'r'; map[r - 1][c] = 'r'; map[r - 2][c] = 'r';
			}
			if (isValidLoc(r, c + 2))
			{
				mine.push(Location2D(r, c + 2)); map[r][c] = 'r'; map[r][c + 1] = 'r'; map[r][c + 2] = 'r';
			}
		}
		else
		{
			if (isValidLoc(r + 2, c))
			{
				mine.push(Location2D(r + 2, c)); map[r][c] = 'r'; map[r + 1][c] = 'r'; map[r + 2][c] = 'r';
			}
			if (isValidLoc(r, c + 2))
			{
				mine.push(Location2D(r, c + 2)); map[r][c] = 'r'; map[r][c + 1] = 'r'; map[r][c + 2] = 'r';
			}
			if (isValidLoc(r, c - 2))
			{
				mine.push(Location2D(r, c - 2)); map[r][c] = 'r'; map[r][c - 1] = 'r'; map[r][c - 2] = 'r';
			}
			if (isValidLoc(r - 2, c))
			{
				mine.push(Location2D(r - 2, c)); map[r][c] = 'r'; map[r - 1][c] = 'r'; map[r - 2][c] = 'r';
			}
		}

	}map[0][0] = 'e'; map[8][8] = 'o';
	std::cout << "\n";
	for (int i = 0; i < MAZE_SIZE; i++)
	{
		for (int j = 0; j < MAZE_SIZE; j++)
		{
			std::cout << map[i][j] << " ";
		}std::cout << std::endl;
	}

	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";
	//============================================== solve
	//DFS 깊이우선탐색
	/*std::stack<Location2D> locStack;
	Location2D entry1(0, 0);
	locStack.push(entry1);
	while (!locStack.empty())
	{
		Location2D here = locStack.top();
		locStack.pop();
		int row = here.row;
		int col = here.col;
		std::cout << "(" << row << "," << col << ")";
		if (map[row][col] == 'o')
		{
			std::cout << "탈출했습니다" << std::endl;
			return 0;
		}
		else
		{
			map[row][col] = ',';
			if (isValidLoc_solve(row - 1, col)) { locStack.push(Location2D(row - 1, col)); }
			if (isValidLoc_solve(row + 1, col)) { locStack.push(Location2D(row + 1, col)); }
			if (isValidLoc_solve(row, col - 1)) { locStack.push(Location2D(row, col - 1)); }
			if (isValidLoc_solve(row, col + 1)) { locStack.push(Location2D(row, col + 1)); }
		}
	}std::cout << "탈출에 실패했습니다" << std::endl;*/


	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";

	//==============================================================
	//BFS 넓이우선 탐색
	/*std::queue<Location2D> locQueue;
	static int arr[MAZE_SIZE][MAZE_SIZE] = { 0 }; //별도의 배열을 생성하고 일단 모두 0으로 초기화 최단거리
	Location2D entry2(0, 0);
	locQueue.push(entry2);
	while (!locQueue.empty())
	{
		Location2D here = locQueue.front();
		locQueue.pop();
		int row = here.row;
		int col = here.col;
		std::cout << "(" << row << "," << col << ")";
		if (map[row][col] == 'o')
		{
			std::cout << "탈출했습니다" << std::endl;
			std::cout << "최단 거리는: "<<arr[row][col];
			return 0;
		}
		else
		{
			map[row][col] = ',';
			if (isValidLoc_solve(row - 1, col))
			{ locQueue.push(Location2D(row - 1, col)),arr[row-1][col]=arr[row][col]+1; }
			if (isValidLoc_solve(row + 1, col))
			{ locQueue.push(Location2D(row + 1, col)), arr[row + 1][col] = arr[row][col] + 1; }
			if (isValidLoc_solve(row, col - 1))
			{ locQueue.push(Location2D(row, col - 1)), arr[row][col-1] = arr[row][col] + 1; }
			if (isValidLoc_solve(row, col + 1))
			{ locQueue.push(Location2D(row, col + 1)), arr[row][col+1] = arr[row][col] + 1; }
		}
	}std::cout << "탈출에 실패했습니다" << std::endl;
	*/

	return 0;
}

