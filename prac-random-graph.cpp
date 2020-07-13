#include <iostream>
#include <string>
#include <vector>
#include <random>
/*sir 모델을 이용한 랜덤그래프 연습*/
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
	std::uniform_int_distribution<int> dis(0, 99); //1부터 100까지만
	a = dis(gen);
	return a;
}
float getRandomNum()
{
	float a;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0, 1); //1부터 100까지만
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
	void plusdegree(int i, int j) //연결해주는 동시에 차수 늘리고
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
				totalDeg[j] += degree[i][j]; //그럼 각 노드마다의 총 차수가 구해져서 totalDeg에 배열로저장
				total += degree[j][i];
			}
		}
		for (int i = 0; i < MAX_VTXS; i++)
		{
			chance[i] = static_cast<float>(totalDeg[i]) / total; //0~MAX_VTXS까지 노드의 확률저장
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
				if (ch <= chance[i]) //이게 말이안된다. 맨처음 chance[i]값이 가장큰데 그거보다 큰 확률이나오면
									 //당연히 뒤에껀 해당될 수 없다.
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
			} /*first가 만약 확률이 존재하는 노드중 마지막 노드의 인덱스라면 다시 돌려야한다.

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
	int size; //전체 그래프의 사이즈
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
	std::string getVertex(int i) { return vertices[i]; }	 //i번 째 vertex를 가져오는
	int getEdge(int i, int j) { return adj[i][j]; }			 //i와j사이에 edge가 있는지 있으면 1 없으면 0
	void setEdge(int i, int j, int val) { adj[i][j] = val; } //이 val은 가중치가 있는 그래프에서 사용
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
		} //예를들어 3번에 넣고싶다하면
		//index가 0부터시작이니까 vertices[2] 0,1,2 에들어간다 그러니까 size++로 맞춰주는것
		else
		{
			std::cout << "최대 정점수 이상을 입력할 수 없다";
		}
	}
	void insertEdge(int u, int v)
	{
		setEdge(u, v, 1); //1인 이유는 가중치가없으니 다 동일한 1로맞춘다.
		setEdge(v, u, 1); //가중치가 없으니 대칭행렬
	}
	void insertEdgeZero(int u, int v)
	{
		setEdge(u, v, 0); //자기자신에겐 링크될 수 없으니
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
	float InfChance = 0.5; //약 10분의 5확률로 감염된다고 가정
	//float InfChance = 0.3;//마스크를 사용했을 때 감염률이 약 30퍼센트라고 가정
	float RecChance = 0.7; //회복할 확률 약 70퍼센트로 가정
						   //float RecChance = 0.3;//완치율이 낮아져서 30퍼센트
public:
	SIR()
	{
		for (int i = 0; i < MAX_VTXS; i++)
		{
			for (int j = 0; j < MAX_VTXS; j++)
			{
				if (adj[i][j] == 1)
				{
					adj[i][j] = 'S'; //처음에 모두 S로 초기화
				}
			}
		}
		eachNode.resize(MAX_VTXS);
		for (int i = 0; i < MAX_VTXS; i++)
		{
			eachNode[i] = 'S'; //★ R은 다시 감염될 수 없다.★
		}
	}

	void changeS_I_First(int n) //감염시도 함수 . 임의로 감염된 노드를 고르고 그 eachNode를 I로 바꿔주고 시작
	{
		float randF = 0;
		eachNode[n] = 'I'; //처음 감염.
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
			} //처음 노드 N 이웃들 감염시작

			int a = 0; //2번째 스텝에서 아무도 감염이 안되면 진행이 안되니까
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
	int changeS_I_R(int n) //처음 감염된 노드 n
	{
		//그 다음 지금까지 2이미 감염된 노드를 대상으로 회복
		//위에서 이미 임의의 한 노드 감염시킨 후 그 이웃을 감염시킨 다 음 에! 회복 - 감염 -회복 -감염 -회복...
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
		{ //이렇게하면 한스텝한스텝씩이 아니다 왜냐면 새로감염시킨 노드는 치료에서 빼야ㅕ하는데 지금 새로 감염시킨 노드까지.
			//치료한다.
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
			/*for (int i = 0; i < MAX_VTXS; i++)  //자가격리 인원수
			{
				if (temp[i] == 'R')
				{
					still_R++;
				}
			}
			if (turn == 4) //3일 동안 대면시험을 치뤘을 경우
			{
				break;
			}*/
		}

		//return still_I;
		//return still_I+still_R;
		return turn;
		//종료조건.S가 없을 때 까지지 for문돌려서
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
		sir.setChance();	  //확률 만들고
		b = sir.nextReturn(); //확률에 따라 다음 링크해줄 숫자 받아오고

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

	// 접촉이 가장 많은 사람을 고르기 위한 반복문 ★
	/*int compare = 0;
	for (int i = 0; i < MAX_VTXS; i++)
	{
		if (sir.totalDeg[i] > compare)
		{
			compare = i;
		}
	}*/

	//접촉이 가장 적은 사람을 고르기위한 반복문 8

	/*int compare = 100;
	for (int i = 0; i < MAX_VTXS; i++)
	{
		if (sir.totalDeg[i] < compare)
		{
			compare = i;
		}
	}*/

	//임의로 고르기 위해
	//int compare = 50;

	/*사회적 거리두기를 위한 랜덤으로 링크끊기
	int ran1 = getIntRandomNum();
	int ran2 = getIntRandomNum();*/

	/*	sir.changeS_I_First(compare);//매개중심성. 이웃이 가장많은 노드와 가장적은 노드 넣어보기
	step = sir.changeS_I_R(compare);
	std::cout << step;*/

	return 0;
}