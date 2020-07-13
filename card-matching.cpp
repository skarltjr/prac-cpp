#include<iostream>
#include<string>
using namespace std;

static char pageFirst[4][4];
int cardData[4][4] = { 1,2,3,4,5,6,7,8,8,7,6,5,4,3,2,1 };
int a = 0, b = 0, a1 = 0, b1 = 0;  //좌표용
int pl2Score = 0;
int pl1Score = 0;
int pl1 = 0, pl2 = 0;
void cardPrint(); // 기본배열 출력
void getPosition(); // 좌표입력함수
void checkPrint(); // 짝이 맞는지 판단
void finish(); //종료를 위한 함수
int main()
{
	int select;
	cout << "2가지의 게임 모드가 있습니다." << endl;
	cout << "0을 누르면 고정배치 / 1을 누르면 랜덤배치입니다." << endl;
	cin >> select;
	int randomMat[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			randomMat[i][j] = rand() % 8 + 1;
		}
	}
	if (select == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				cardData[i][j] = randomMat[i][j];
			}
		}
	}
	cardPrint();
	cout << "숫자는 0부터 시작함을 미리알립니다" << endl;
	getPosition();

}

void cardPrint()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			pageFirst[i][j] = 'x';
			cout << pageFirst[i][j];
		}cout << endl;
	}
}
void getPosition()
{
	if (pl1 <= pl2)
	{
		cout << "pl1's turn" << endl;
		while (1)
		{
			cout << " 1번째 카드 행을 입력해주세요" << endl;
			cin >> a;
			if (a >= 4)
			{
				cout << "좌표값의 범위를 초과했습니다. 다시입력해주세요" << endl;
				continue;
			}
			cout << " 1번째 카드 열을 입력해주세요" << endl;
			cin >> b;
			if (b >= 4)
			{
				cout << "좌표값의 범위를 초과했습니다. 다시입력해주세요" << endl;
				continue;
			}
			if (pageFirst[a][b] != 'x')
			{
				cout << "이미 뒤집힌 카드입니다." << endl;
				continue;
			}
			break;
		}
		while (1)
		{
			cout << " 2번째 카드 행을 입력해주세요" << endl;
			cin >> a1;
			if (a1 >= 4)
			{
				cout << "좌표값의 범위를 초과했습니다. 다시입력해주세요" << endl;
				continue;
			}
			cout << " 2번째 카드 열을 입력해주세요" << endl;
			cin >> b1;
			if (b1 >= 4)
			{
				cout << "좌표값의 범위를 초과했습니다. 다시입력해주세요" << endl;
				continue;
			}
			if (pageFirst[a][b] != 'x')
			{
				cout << "이미 뒤집힌 카드입니다." << endl;
				continue;
			}
			break;
		}pl1++;
	}
	else
	{
		cout << "pl2's turn" << endl;
		while (1)
		{
			cout << " 1번째 카드 행을 입력해주세요" << endl;
			cin >> a;
			if (a >= 4)
			{
				cout << "좌표값의 범위를 초과했습니다. 다시입력해주세요" << endl;
				continue;
			}

			cout << " 1번째 카드 열을 입력해주세요" << endl;
			cin >> b;
			if (b >= 4)
			{
				cout << "좌표값의 범위를 초과했습니다. 다시입력해주세요" << endl;
				continue;
			}
			if (pageFirst[a][b] != 'x')
			{
				cout << "이미 뒤집힌 카드입니다." << endl;
				continue;
			}
			break;
		}
		while (1)
		{
			cout << " 2번째 카드 행을 입력해주세요" << endl;
			cin >> a1;
			if (a1 >= 4)
			{
				cout << "좌표값의 범위를 초과했습니다. 다시입력해주세요" << endl;
				continue;
			}
			cout << " 2번째 카드 열을 입력해주세요" << endl;
			cin >> b1;
			if (b1 >= 4)
			{
				cout << "좌표값의 범위를 초과했습니다. 다시입력해주세요" << endl;
				continue;
			}
			if (pageFirst[a][b] != 'x')
			{
				cout << "이미 뒤집힌 카드입니다." << endl;
				continue;
			}
			break;
		}pl2++;
	}
	checkPrint();
}
void checkPrint()
{
	if (cardData[a][b] == cardData[a1][b1])
	{
		pageFirst[a][b] = cardData[a][b] + '0';
		pageFirst[a1][b1] = cardData[a1][b1] + '0';
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				cout << pageFirst[i][j];
			}cout << endl;
		}
		cout << "짝을 맞췄습니다!" << endl;
		if (pl1 <= pl2)
		{
			if (cardData[a][b] == 7)
			{
				pl1Score += 2;
			}
			pl1Score++;
		}
		else
		{
			if (cardData[a][b] == 7)
			{
				pl2Score += 2;
			}
			pl2Score++;
		}
		finish();
		getPosition();
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				cout << pageFirst[i][j];
			}cout << endl;
		}
		cout << "짝이 안맞네요!" << endl;
		getPosition();
	}
}
void finish()
{
	int num = 0;
	int i, j, a;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{

			if (cardData[i][j] == (pageFirst[i][j] - '0'))
			{
				++num;
			}
		}
	}
	if (num == 16)
	{
		cout << "pl1's score" << pl1Score << endl;
		cout << "pl2's score" << pl2Score << endl;
		cout << "모든 쌍을 다 찾았습니다." << endl;
		cout << "프로그램을 종료하도록 0을 눌러주세요." << endl;
		cin >> a;
		if (a == 0)
		{
			exit(0);
		}
	}
}
