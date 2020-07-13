#include <iostream>
#include <string>
#include <vector>
#include <random>
/*sir ���� �̿��� �����׷��� ����*/
#define MAX_VTXS 100
struct num
{
	int first = 0;
	int second = 0;
};
int getIntRandomNum()
{
	int a;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 99); //1���� 100������
	a = dis(gen);
	return a;
}
float getRandomNum()
{
	float a;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0, 1); //1���� 100������
	a = dis(gen);
	return a;
}
class Degree
{
public:
	std::vector<std::vector<int>> degree;
	std::vector<int> totalDeg;
	std::vector<float> chance;
	int total;

public:
	Degree()
	{
		degree.resize(MAX_VTXS);
		for (int i = 0; i < MAX_VTXS; i++)
		{
			degree[i].resize(MAX_VTXS, 0);
		}
		totalDeg.resize(MAX_VTXS, 0);
		chance.resize(MAX_VTXS, 0);
	}
	void plusdegree(int i, int j) //�������ִ� ���ÿ� ���� �ø���
	{
		degree[i][j]++;
		degree[j][i]++;
	}
	void setChance()
	{
		for (int j = 0; j < MAX_VTXS; j++)
		{
			for (int i = 0; i < MAX_VTXS; i++)
			{
				totalDeg[j] += degree[i][j]; //�׷� �� ��帶���� �� ������ �������� totalDeg�� �迭������
				total += degree[j][i];
			}
		}
		for (int i = 0; i < MAX_VTXS; i++)
		{
			chance[i] = static_cast<float>(totalDeg[i]) / total; //0~MAX_VTXS���� ����� Ȯ������
		}
	}
	num nextReturn()
	{
		num returnVal;
		int start;
		int max = MAX_VTXS;
		int num = 0;
		returnVal.first = -1;
		returnVal.second = -1;
		float ch = getRandomNum();
		while (returnVal.first == -1)
		{
			num = 0;
			for (int i = 0; i < MAX_VTXS; i++)
			{
				if (chance[i] != 0)
				{
					num++;
				}
			}
			for (int i = 0; i < max; i++)
			{
				if (ch <= chance[i]) //�̰� ���̾ȵȴ�. ��ó�� chance[i]���� ����ū�� �װź��� ū Ȯ���̳�����
									 //�翬�� �ڿ��� �ش�� �� ����.
				{
					returnVal.first = i; //0
					start = i;			 //0
					//std::cout << chance[i] << " " << ch << "\n";
					break;
				}
				if (ch > chance[i])
				{
					ch = getRandomNum();
				}
				//if (i == MAX_VTXS - 1 && returnVal.first == -1)
				if (i == num - 1 && returnVal.first == -1)
				{
					i = 0;
					max = num - 1;
				}
			} /*first�� ���� Ȯ���� �����ϴ� ����� ������ ����� �ε������ �ٽ� �������Ѵ�.

			 */
			if (returnVal.first != -1)
			{
				break;
			}
		}
		std::cout << "re-try"
				  << "\n";
		ch = getRandomNum();
		while (returnVal.second == -1)
		{
			for (int i = start; i < MAX_VTXS; i++)
			{
				if (ch <= chance[i] && returnVal.first != i)
				{
					returnVal.second = i;
					break;
				}
				if (ch > chance[i])
				{
					ch = getRandomNum();
					i = start;
				}
			}
			if (returnVal.second != -1)
			{
				break;
			}
		}
		return returnVal;
	}
};

class AdjMatGraph : public Degree
{
public:
	int size; //��ü �׷����� ������
	std::vector<std::string> vertices;
	std::vector<std::vector<int>> adj;

public:
	AdjMatGraph()
		: Degree()
	{
		vertices.resize(MAX_VTXS);
		adj.resize(MAX_VTXS);
		for (int i = 0; i < MAX_VTXS; i++)
		{
			adj[i].resize(MAX_VTXS);
		}
		reset();
	}

	~AdjMatGraph() {}
	std::string getVertex(int i) { return vertices[i]; }	 //i�� ° vertex�� ��������
	int getEdge(int i, int j) { return adj[i][j]; }			 //i��j���̿� edge�� �ִ��� ������ 1 ������ 0
	void setEdge(int i, int j, int val) { adj[i][j] = val; } //�� val�� ����ġ�� �ִ� �׷������� ���
	bool isEmpty() { return size == 0; }
	bool isFull() { return size >= MAX_VTXS; }

	void reset()
	{
		size = 0;
		for (int i = 0; i < MAX_VTXS; i++)
		{
			for (int j = 0; j < MAX_VTXS; j++)
			{
				setEdge(i, j, 0);
			}
		}
	}
	void insertVertex(std::string name)
	{
		if (!isFull())
		{
			vertices[size++] = name;
		} //������� 3���� �ְ�ʹ��ϸ�
		//index�� 0���ͽ����̴ϱ� vertices[2] 0,1,2 ������ �׷��ϱ� size++�� �����ִ°�
		else
		{
			std::cout << "�ִ� ������ �̻��� �Է��� �� ����";
		}
	}
	void insertEdge(int u, int v)
	{
		setEdge(u, v, 1); //1�� ������ ����ġ�������� �� ������ 1�θ����.
		setEdge(v, u, 1); //����ġ�� ������ ��Ī���
	}
	void insertEdgeZero(int u, int v)
	{
		setEdge(u, v, 0); //�ڱ��ڽſ��� ��ũ�� �� ������
	}
	void display()
	{
		for (int i = 0; i < MAX_VTXS; i++)
		{
			for (int j = 0; j < MAX_VTXS; j++)
			{
				std::cout << adj[i][j] << " ";
			}
			std::cout << "\n";
		}
	}
};
class SIR : public AdjMatGraph
{
public:
	std::vector<char> eachNode;
	float InfChance = 0.5; //�� 10���� 5Ȯ���� �����ȴٰ� ����
	//float InfChance = 0.3;//����ũ�� ������� �� �������� �� 30�ۼ�Ʈ��� ����
	float RecChance = 0.7; //ȸ���� Ȯ�� �� 70�ۼ�Ʈ�� ����
						   //float RecChance = 0.3;//��ġ���� �������� 30�ۼ�Ʈ
public:
	SIR()
	{
		for (int i = 0; i < MAX_VTXS; i++)
		{
			for (int j = 0; j < MAX_VTXS; j++)
			{
				if (adj[i][j] == 1)
				{
					adj[i][j] = 'S'; //ó���� ��� S�� �ʱ�ȭ
				}
			}
		}
		eachNode.resize(MAX_VTXS);
		for (int i = 0; i < MAX_VTXS; i++)
		{
			eachNode[i] = 'S'; //�� R�� �ٽ� ������ �� ����.��
		}
	}

	void changeS_I_First(int n) //�����õ� �Լ� . ���Ƿ� ������ ��带 ���� �� eachNode�� I�� �ٲ��ְ� ����
	{
		float randF = 0;
		eachNode[n] = 'I'; //ó�� ����.
		while (1)
		{
			for (int i = 0; i < MAX_VTXS; i++)
			{
				if (adj[i][n] == 1 && eachNode[i] == 'S')
				{
					randF = getRandomNum();
					if (randF < InfChance)
					{
						eachNode[i] = 'I';
					}
				}
			} //ó�� ��� N �̿��� ��������

			int a = 0; //2��° ���ܿ��� �ƹ��� ������ �ȵǸ� ������ �ȵǴϱ�
			for (int i = 0; i < MAX_VTXS; i++)
			{
				if (eachNode[i] != 'S')
				{
					a++;
				}
			}
			if (a > 0)
			{
				break;
			}
		}
	}
	void changeS_I(int num)
	{
		float randF = 0;
		//float apartment = 0.7;
		//float randA = 0;
		for (int i = 0; i < MAX_VTXS; i++)
		{
			if (adj[i][num] == 1 && eachNode[i] == 'S')
			{
				randF = getRandomNum();
				//randA = getRandomNum();
				/*if (randA < 0.7)
				{
					InfChance = 0.8;
				}
				else
				{
					InfChance = 0.4;
				}*/
				if (randF < InfChance)
				{
					eachNode[i] = 'I';
				}
			}
		}
	}
	int changeS_I_R(int n) //ó�� ������ ��� n
	{
		//�� ���� ���ݱ��� 2�̹� ������ ��带 ������� ȸ��
		//������ �̹� ������ �� ��� ������Ų �� �� �̿��� ������Ų �� �� ��! ȸ�� - ���� -ȸ�� -���� -ȸ��...
		float randF_I = 0;
		float randF_R = getRandomNum();
		int turn = 2;
		int still_I = 0;
		int still_R = 0;
		std::vector<char> temp;
		temp.resize(MAX_VTXS);
		if (randF_R < RecChance)
		{
			eachNode[n] = 'R';
		}
		while (1)
		{ //�̷����ϸ� �ѽ����ѽ��ܾ��� �ƴϴ� �ֳĸ� ���ΰ�����Ų ���� ġ�ῡ�� ���ߤ��ϴµ� ���� ���� ������Ų ������.
			//ġ���Ѵ�.
			++turn;
			temp = eachNode;
			//infect
			for (int i = 0; i < MAX_VTXS; i++)
			{
				if (eachNode[i] == 'I')
				{
					changeS_I(i);
				}
			}
			//recovery
			for (int i = 0; i < MAX_VTXS; i++)
			{
				if (temp[i] == 'I')
				{
					randF_R = getRandomNum();
					if (randF_R < RecChance)
					{
						temp[i] = 'R';
						eachNode[i] = 'R';
					}
				}
			}
			still_I = 0;
			for (int i = 0; i < MAX_VTXS; i++)
			{
				if (temp[i] == 'I')
				{
					still_I++;
				}
			}
			if (still_I == 0)
			{
				break;
			}
			/*for (int i = 0; i < MAX_VTXS; i++)  //�ڰ��ݸ� �ο���
			{
				if (temp[i] == 'R')
				{
					still_R++;
				}
			}
			if (turn == 4) //3�� ���� �������� ġ���� ���
			{
				break;
			}*/
		}

		//return still_I;
		//return still_I+still_R;
		return turn;
		//��������.S�� ���� �� ������ for��������
	}
};
int main()
{
	SIR sir;
	int step = 0;
	sir.plusdegree(0, 1);
	sir.insertEdge(0, 1);
	int a = 2;
	num b;

	while (1)
	{
		sir.setChance();	  //Ȯ�� �����
		b = sir.nextReturn(); //Ȯ���� ���� ���� ��ũ���� ���� �޾ƿ���

		if (b.second == -1)
		{
			break;
		}
		if (sir.adj[a][b.first] != 1)
		{
			//std::cout << a << " " << b.first << " " << "\n";
			if (a != b.first)
			{
				sir.insertEdge(a, b.first);
				sir.plusdegree(a, b.first);
			}
			else if (a == b.first)
			{
				sir.insertEdgeZero(a, b.first);
			}
		}

		if (sir.adj[a][b.second] != 1)
		{
			if (a != b.second)
			{
				sir.insertEdge(a, b.second);
				sir.plusdegree(a, b.second);
			}
			else if (a == b.second)
			{
				sir.insertEdgeZero(a, b.second);
			}
		}
		a++;
		if (a == MAX_VTXS)
		{
			break;
		}
	}

	sir.display();

	std::cout << "\n";

	// ������ ���� ���� ����� ���� ���� �ݺ��� ��
	/*int compare = 0;
	for (int i = 0; i < MAX_VTXS; i++)
	{
		if (sir.totalDeg[i] > compare)
		{
			compare = i;
		}
	}*/

	//������ ���� ���� ����� �������� �ݺ��� 8

	/*int compare = 100;
	for (int i = 0; i < MAX_VTXS; i++)
	{
		if (sir.totalDeg[i] < compare)
		{
			compare = i;
		}
	}*/

	//���Ƿ� ���� ����
	//int compare = 50;

	/*��ȸ�� �Ÿ��α⸦ ���� �������� ��ũ����
	int ran1 = getIntRandomNum();
	int ran2 = getIntRandomNum();*/

	/*	sir.changeS_I_First(compare);//�Ű��߽ɼ�. �̿��� ���帹�� ���� �������� ��� �־��
	step = sir.changeS_I_R(compare);
	std::cout << step;*/

	return 0;
}