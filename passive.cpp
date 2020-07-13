
#include<iostream>
#include<stack>
#include<queue>
using namespace std;
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

//깊이우선탐색 stack으로 구현 먼저들어간게 나중에 나온다.
const int MAZE_SIZE = 6;
char map[MAZE_SIZE][MAZE_SIZE] = {
    {'e', '0', '1', '1', '1', '0'},
    {'1', '0', '1', '0', '0', '0'},//스택을 이용한 깊이우선탐색은 말 그대로 위아래에 우선순위가 크다
    {'1', '0', '0', '0', '1', '1'},//그러니까 위 아래로 먼저 끝까지 탐색해본 후 다음 갈림길에서 좌표로 넘어간다
    {'1', '0', '1', '0', '0', '0'},
    {'1', '0', '0', '0', '1', '0'},
    {'1', '1', '1', '1', '1', 'x'},
};
bool isValidLoc(int r, int c)
{
    if (r < 0 || c < 0 || r >= MAZE_SIZE || c >= MAZE_SIZE) { return false; }
    else { return  map[r][c] == '0' || map[r][c] == 'x'; }//유효한것은 0이나 x인 출구 1은 막힌길이니까
}

int main()
{
    /* std::stack<Location2D> locStack;
     static int arr[MAZE_SIZE][MAZE_SIZE] = { 0 };
       Location2D entry(0, 0);//스택에 입구 1,0이 쌓이고
       locStack.push(entry);//첫 입구 위치를 스택에 쌓아주고
       while (locStack.empty() == false)
       {
           Location2D here = locStack.top(); //현재위치를 설정해줘야하는데 현재위치는 가장 나중에 들어온 스택의 맨 윗단
           locStack.pop();//현재위치에 해당하는 맨 위 스택 지워준 후 다음으로 넘어간다.
           //현재위치 정보는 아직 here에 남아있으니
           int r = here.row;
           int c = here.col;
           //현재위치를 출력
           std::cout << "(" << r << "," << c << ")";
           if (map[r][c] == 'x')
           {
               std::cout << "탈출했습니다\n";
               std::cout << "최단 거리는: " << arr[r][c];
               return 0;
           }
           else
           {
               //그게 아니면 현재위치는 이제 거쳐간 위치니까
               map[r][c] = ',';
               if (isValidLoc(r - 1, c))
               { locStack.push(Location2D(r - 1, c)), arr[r - 1][c] = arr[r][c] + 1;}
               if (isValidLoc(r + 1, c))
               { locStack.push(Location2D(r + 1, c)), arr[r + 1][c] = arr[r][c] + 1;}
               if (isValidLoc(r, c - 1))
               { locStack.push(Location2D(r, c - 1)), arr[r][c-1] = arr[r][c] + 1; }
               if (isValidLoc(r, c + 1))
               { locStack.push(Location2D(r, c + 1)), arr[r][c+1] = arr[r][c] + 1;}
           }
       }std::cout << "탈출에 실패\n";
       return 0;*/

       /*std::queue<Location2D> locQueue;
       static int arr[MAZE_SIZE][MAZE_SIZE] = { 0 };
          Location2D entry(0, 0);
          locQueue.push(entry);// 큐는 일자형 모양이라 했을 때 뒤에서부터 넣어주고 앞에서부터 pop해주니까
          //먼저들어온게 먼저 빠져나가는 선입선출을 유지가능
          while (locQueue.empty() == false)
          {
              Location2D here = locQueue.front();//먼저들어온 위치에 대한 큐데이터는 선입선출을 위해 맨 앞에 위치
              locQueue.pop();
              int r = here.row;
              int c = here.col;
              std::cout << "(" << r << "," << c << ")";
              if (map[r][c] == 'x')
              {
                  std::cout << "탈출 했습니다" << std::endl;
                  std::cout << "최단거리 : "<<arr[r][c] << "\n";
                  return 0;
              }
              else
              {
                  map[r][c] = ',';
                  if (isValidLoc(r - 1, c)) { locQueue.push(Location2D(r - 1, c)), arr[r- 1][c] = arr[r][c] + 1;
                  }
                  if (isValidLoc(r + 1, c)) { locQueue.push(Location2D(r + 1, c)), arr[r + 1][c] = arr[r][c] + 1;
                  }
                  if (isValidLoc(r, c - 1)) { locQueue.push(Location2D(r, c - 1)), arr[r][c-1] = arr[r][c] + 1;
                  }
                  if (isValidLoc(r, c + 1)) { locQueue.push(Location2D(r, c + 1)), arr[r][c+1] = arr[r][c] + 1;
                  }
              }
          }std::cout << "탈출 실패" << std::endl;*/

    return 0;
}