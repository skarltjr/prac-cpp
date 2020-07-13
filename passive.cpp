
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

//���̿켱Ž�� stack���� ���� �������� ���߿� ���´�.
const int MAZE_SIZE = 6;
char map[MAZE_SIZE][MAZE_SIZE] = {
    {'e', '0', '1', '1', '1', '0'},
    {'1', '0', '1', '0', '0', '0'},//������ �̿��� ���̿켱Ž���� �� �״�� ���Ʒ��� �켱������ ũ��
    {'1', '0', '0', '0', '1', '1'},//�׷��ϱ� �� �Ʒ��� ���� ������ Ž���غ� �� ���� �����濡�� ��ǥ�� �Ѿ��
    {'1', '0', '1', '0', '0', '0'},
    {'1', '0', '0', '0', '1', '0'},
    {'1', '1', '1', '1', '1', 'x'},
};
bool isValidLoc(int r, int c)
{
    if (r < 0 || c < 0 || r >= MAZE_SIZE || c >= MAZE_SIZE) { return false; }
    else { return  map[r][c] == '0' || map[r][c] == 'x'; }//��ȿ�Ѱ��� 0�̳� x�� �ⱸ 1�� �������̴ϱ�
}

int main()
{
    /* std::stack<Location2D> locStack;
     static int arr[MAZE_SIZE][MAZE_SIZE] = { 0 };
       Location2D entry(0, 0);//���ÿ� �Ա� 1,0�� ���̰�
       locStack.push(entry);//ù �Ա� ��ġ�� ���ÿ� �׾��ְ�
       while (locStack.empty() == false)
       {
           Location2D here = locStack.top(); //������ġ�� ����������ϴµ� ������ġ�� ���� ���߿� ���� ������ �� ����
           locStack.pop();//������ġ�� �ش��ϴ� �� �� ���� ������ �� �������� �Ѿ��.
           //������ġ ������ ���� here�� ����������
           int r = here.row;
           int c = here.col;
           //������ġ�� ���
           std::cout << "(" << r << "," << c << ")";
           if (map[r][c] == 'x')
           {
               std::cout << "Ż���߽��ϴ�\n";
               std::cout << "�ִ� �Ÿ���: " << arr[r][c];
               return 0;
           }
           else
           {
               //�װ� �ƴϸ� ������ġ�� ���� ���İ� ��ġ�ϱ�
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
       }std::cout << "Ż�⿡ ����\n";
       return 0;*/

       /*std::queue<Location2D> locQueue;
       static int arr[MAZE_SIZE][MAZE_SIZE] = { 0 };
          Location2D entry(0, 0);
          locQueue.push(entry);// ť�� ������ ����̶� ���� �� �ڿ������� �־��ְ� �տ������� pop���ִϱ�
          //�������°� ���� ���������� ���Լ����� ��������
          while (locQueue.empty() == false)
          {
              Location2D here = locQueue.front();//�������� ��ġ�� ���� ť�����ʹ� ���Լ����� ���� �� �տ� ��ġ
              locQueue.pop();
              int r = here.row;
              int c = here.col;
              std::cout << "(" << r << "," << c << ")";
              if (map[r][c] == 'x')
              {
                  std::cout << "Ż�� �߽��ϴ�" << std::endl;
                  std::cout << "�ִܰŸ� : "<<arr[r][c] << "\n";
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
          }std::cout << "Ż�� ����" << std::endl;*/

    return 0;
}