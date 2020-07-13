#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>

#define INF 999
#define MAX_VTXS 256
class AdjMatGraph
{
protected:
	int size; //전체 그래프의 사이즈
	std::string vertices[MAX_VTXS]; //각  vertex의 이름
	int adj[MAX_VTXS][MAX_VTXS];//인접행렬
public:
	AdjMatGraph() { reset(); }
	~AdjMatGraph() {}
	std::string getVertex(int i) { return vertices[i]; }//i번 째 vertex를 가져오는
	int getEdge(int i, int j) { return adj[i][j]; }//i와j사이에 edge가 있는지 있으면 1 없으면 0
	void setEdge(int i, int j, int val) { adj[i][j] = val; }//이 val은 가중치가 있는 그래프에서 사용
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
		if (!isFull()) { vertices[size++] = name; }//예를들어 3번에 넣고싶다하면
		//index가 0부터시작이니까 vertices[2] 0,1,2 에들어간다 그러니까 size++로 맞춰주는것
		else { std::cout << "최대 정점수 이상을 입력할 수 없다"; }
	}
	void insertEdge(int u, int v)
	{
		setEdge(u, v, 1);//1인 이유는 가중치가없으니 다 동일한 1로맞춘다.
		setEdge(v, u, 1);//가중치가 없으니 대칭행렬
	}
	void display()
	{
		std::cout << size << "\n";
		for (int i = 0; i < size; i++)
		{
			std::cout << getVertex(i) << " ";
			for (int j = 0; j < size; j++)
			{
				std::cout << getEdge(i, j) << " ";
			}std::cout << "\n";
		}
	}
	void load(std::string filename)
	{
		std::ifstream ifs(filename);//파일을 입력받고
		std::string line;
		std::getline(ifs, line);//line에 파일에있는 문자열을 한 줄씩 받아오게하고.
		std::stringstream ls(line);//A0101을 한 줄로 즉 스트링을 공백단위로 끊어서
		int n;
		ls >> n; //첫 줄에 std::cout << size << "\n";니까 size인 4만 적혀있을거니까 이 첫줄4가 n에 들어가고
		for (int i = 0; i < n; i++)//전체그래프의 사이즈  행렬로 나타내면 맨위에 ABCD니까 size가 4줄 이라 생각 . 행이 4
		{
			std::getline(ifs, line);// 맨 위4 다음 한 줄을 받기위해 다시 2번째 줄부터 getline
			std::string str;
			int val;
			std::stringstream ls(line);//공백단위로 끊으니까 A 0 1 0 1 일때
			ls >> str;//이건  A B C D처럼 vertex이름 공백단위로 맨 앞에꺼 밭고 처음엔 A
			insertVertex(str);
			for (int j = 0; j < n; j++)
			{
				ls >> val;//그 다음 열 따라 0 1 0 1 
				if (val != 0)
				{
					insertEdge(i, j);
				}
			}//다시 행 바뀌면 이번엔 B 
		}ifs.close();
	}
	void store(std::string filename)//display랑 똑같다
	{
		std::ofstream ofs(filename);
		ofs << size << "\n";
		for (int i = 0; i < MAX_VTXS; i++)
		{
			ofs << getVertex(i) << " ";
			for (int j = 0; j < MAX_VTXS; j++)
			{
				ofs << getEdge(i, j) << " ";
			}ofs << "\n";
		}ofs.close();
	}
};
class WGraph :public AdjMatGraph
{
	//따로 변수필요 x
public:
	WGraph() {}
	~WGraph() {}
	bool hasEdge(int i, int j) { return (getEdge(i, j) < INF); }//최대값보다 크면 간선이없는거다
	void insertEdge(int u, int v, int weight)
	{
		if (weight >= INF) { weight = INF; }//간선이 없는경우
		setEdge(u, v, weight); //가중치가 최대값보다 작으면 간선이 있는것
	}
	void load(std::string filename)
	{
		std::ifstream ifs(filename);//파일을 입력받고
		std::string line;
		std::getline(ifs, line);//line에 파일에있는 문자열을 한 줄씩 받아오게하고.
		std::stringstream ls(line);//A0101을 한 줄로 즉 스트링을 공백단위로 끊어서
		int n;
		ls >> n; //첫 줄에 std::cout << size << "\n";니까 size인 4만 적혀있을거니까 이 첫줄4가 n에 들어가고
		for (int i = 0; i < n; i++)//전체그래프의 사이즈  행렬로 나타내면 맨위에 ABCD니까 size가 4줄 이라 생각 . 행이 4
		{
			std::getline(ifs, line);// 맨 위4 다음 한 줄을 받기위해 다시 2번째 줄부터 getline
			std::string str;
			int val;
			std::stringstream ls(line);//공백단위로 끊으니까 A 0 1 0 1 일때
			ls >> str;//이건  A B C D처럼 vertex이름 공백단위로 맨 앞에꺼 밭고 처음엔 A
			insertVertex(str);
			for (int j = 0; j < n; j++)
			{
				ls >> val;//그 다음 열 따라 0 1 0 1 
				if (val != 0)
				{
					insertEdge(i, j, val);//가중치가 있을 땐 당연히 val가중치추가
				}
			}//다시 행 바뀌면 이번엔 B 
		}ifs.close();
	}
};
/*int main()
{
	WGraph g;
	g.load("graph4.txt");
	g.display();
}*/