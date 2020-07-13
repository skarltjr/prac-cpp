#include<iostream>
#include<string>
using namespace std;

static char pageFirst[4][4];
int cardData[4][4] = { 1,2,3,4,5,6,7,8,8,7,6,5,4,3,2,1 };
int a = 0, b = 0, a1 = 0, b1 = 0;  //��ǥ��
int pl2Score = 0;
int pl1Score = 0;
int pl1 = 0, pl2 = 0;
void cardPrint(); // �⺻�迭 ���
void getPosition(); // ��ǥ�Է��Լ�
void checkPrint(); // ¦�� �´��� �Ǵ�
void finish(); //���Ḧ ���� �Լ�
int main()
{
	int select;
	cout << "2������ ���� ��尡 �ֽ��ϴ�." << endl;
	cout << "0�� ������ ������ġ / 1�� ������ ������ġ�Դϴ�." << endl;
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
	cout << "���ڴ� 0���� �������� �̸��˸��ϴ�" << endl;
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
			cout << " 1��° ī�� ���� �Է����ּ���" << endl;
			cin >> a;
			if (a >= 4)
			{
				cout << "��ǥ���� ������ �ʰ��߽��ϴ�. �ٽ��Է����ּ���" << endl;
				continue;
			}
			cout << " 1��° ī�� ���� �Է����ּ���" << endl;
			cin >> b;
			if (b >= 4)
			{
				cout << "��ǥ���� ������ �ʰ��߽��ϴ�. �ٽ��Է����ּ���" << endl;
				continue;
			}
			if (pageFirst[a][b] != 'x')
			{
				cout << "�̹� ������ ī���Դϴ�." << endl;
				continue;
			}
			break;
		}
		while (1)
		{
			cout << " 2��° ī�� ���� �Է����ּ���" << endl;
			cin >> a1;
			if (a1 >= 4)
			{
				cout << "��ǥ���� ������ �ʰ��߽��ϴ�. �ٽ��Է����ּ���" << endl;
				continue;
			}
			cout << " 2��° ī�� ���� �Է����ּ���" << endl;
			cin >> b1;
			if (b1 >= 4)
			{
				cout << "��ǥ���� ������ �ʰ��߽��ϴ�. �ٽ��Է����ּ���" << endl;
				continue;
			}
			if (pageFirst[a][b] != 'x')
			{
				cout << "�̹� ������ ī���Դϴ�." << endl;
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
			cout << " 1��° ī�� ���� �Է����ּ���" << endl;
			cin >> a;
			if (a >= 4)
			{
				cout << "��ǥ���� ������ �ʰ��߽��ϴ�. �ٽ��Է����ּ���" << endl;
				continue;
			}

			cout << " 1��° ī�� ���� �Է����ּ���" << endl;
			cin >> b;
			if (b >= 4)
			{
				cout << "��ǥ���� ������ �ʰ��߽��ϴ�. �ٽ��Է����ּ���" << endl;
				continue;
			}
			if (pageFirst[a][b] != 'x')
			{
				cout << "�̹� ������ ī���Դϴ�." << endl;
				continue;
			}
			break;
		}
		while (1)
		{
			cout << " 2��° ī�� ���� �Է����ּ���" << endl;
			cin >> a1;
			if (a1 >= 4)
			{
				cout << "��ǥ���� ������ �ʰ��߽��ϴ�. �ٽ��Է����ּ���" << endl;
				continue;
			}
			cout << " 2��° ī�� ���� �Է����ּ���" << endl;
			cin >> b1;
			if (b1 >= 4)
			{
				cout << "��ǥ���� ������ �ʰ��߽��ϴ�. �ٽ��Է����ּ���" << endl;
				continue;
			}
			if (pageFirst[a][b] != 'x')
			{
				cout << "�̹� ������ ī���Դϴ�." << endl;
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
		cout << "¦�� ������ϴ�!" << endl;
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
		cout << "¦�� �ȸ³׿�!" << endl;
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
		cout << "��� ���� �� ã�ҽ��ϴ�." << endl;
		cout << "���α׷��� �����ϵ��� 0�� �����ּ���." << endl;
		cin >> a;
		if (a == 0)
		{
			exit(0);
		}
	}
}
