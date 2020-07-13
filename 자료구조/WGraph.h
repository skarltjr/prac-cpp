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
	int size; //��ü �׷����� ������
	std::string vertices[MAX_VTXS]; //��  vertex�� �̸�
	int adj[MAX_VTXS][MAX_VTXS];//�������
public:
	AdjMatGraph() { reset(); }
	~AdjMatGraph() {}
	std::string getVertex(int i) { return vertices[i]; }//i�� ° vertex�� ��������
	int getEdge(int i, int j) { return adj[i][j]; }//i��j���̿� edge�� �ִ��� ������ 1 ������ 0
	void setEdge(int i, int j, int val) { adj[i][j] = val; }//�� val�� ����ġ�� �ִ� �׷������� ���
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
		if (!isFull()) { vertices[size++] = name; }//������� 3���� �ְ�ʹ��ϸ�
		//index�� 0���ͽ����̴ϱ� vertices[2] 0,1,2 ������ �׷��ϱ� size++�� �����ִ°�
		else { std::cout << "�ִ� ������ �̻��� �Է��� �� ����"; }
	}
	void insertEdge(int u, int v)
	{
		setEdge(u, v, 1);//1�� ������ ����ġ�������� �� ������ 1�θ����.
		setEdge(v, u, 1);//����ġ�� ������ ��Ī���
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
		std::ifstream ifs(filename);//������ �Է¹ް�
		std::string line;
		std::getline(ifs, line);//line�� ���Ͽ��ִ� ���ڿ��� �� �پ� �޾ƿ����ϰ�.
		std::stringstream ls(line);//A0101�� �� �ٷ� �� ��Ʈ���� ��������� ���
		int n;
		ls >> n; //ù �ٿ� std::cout << size << "\n";�ϱ� size�� 4�� ���������Ŵϱ� �� ù��4�� n�� ����
		for (int i = 0; i < n; i++)//��ü�׷����� ������  ��ķ� ��Ÿ���� ������ ABCD�ϱ� size�� 4�� �̶� ���� . ���� 4
		{
			std::getline(ifs, line);// �� ��4 ���� �� ���� �ޱ����� �ٽ� 2��° �ٺ��� getline
			std::string str;
			int val;
			std::stringstream ls(line);//��������� �����ϱ� A 0 1 0 1 �϶�
			ls >> str;//�̰�  A B C Dó�� vertex�̸� ��������� �� �տ��� ��� ó���� A
			insertVertex(str);
			for (int j = 0; j < n; j++)
			{
				ls >> val;//�� ���� �� ���� 0 1 0 1 
				if (val != 0)
				{
					insertEdge(i, j);
				}
			}//�ٽ� �� �ٲ�� �̹��� B 
		}ifs.close();
	}
	void store(std::string filename)//display�� �Ȱ���
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
	//���� �����ʿ� x
public:
	WGraph() {}
	~WGraph() {}
	bool hasEdge(int i, int j) { return (getEdge(i, j) < INF); }//�ִ밪���� ũ�� �����̾��°Ŵ�
	void insertEdge(int u, int v, int weight)
	{
		if (weight >= INF) { weight = INF; }//������ ���°��
		setEdge(u, v, weight); //����ġ�� �ִ밪���� ������ ������ �ִ°�
	}
	void load(std::string filename)
	{
		std::ifstream ifs(filename);//������ �Է¹ް�
		std::string line;
		std::getline(ifs, line);//line�� ���Ͽ��ִ� ���ڿ��� �� �پ� �޾ƿ����ϰ�.
		std::stringstream ls(line);//A0101�� �� �ٷ� �� ��Ʈ���� ��������� ���
		int n;
		ls >> n; //ù �ٿ� std::cout << size << "\n";�ϱ� size�� 4�� ���������Ŵϱ� �� ù��4�� n�� ����
		for (int i = 0; i < n; i++)//��ü�׷����� ������  ��ķ� ��Ÿ���� ������ ABCD�ϱ� size�� 4�� �̶� ���� . ���� 4
		{
			std::getline(ifs, line);// �� ��4 ���� �� ���� �ޱ����� �ٽ� 2��° �ٺ��� getline
			std::string str;
			int val;
			std::stringstream ls(line);//��������� �����ϱ� A 0 1 0 1 �϶�
			ls >> str;//�̰�  A B C Dó�� vertex�̸� ��������� �� �տ��� ��� ó���� A
			insertVertex(str);
			for (int j = 0; j < n; j++)
			{
				ls >> val;//�� ���� �� ���� 0 1 0 1 
				if (val != 0)
				{
					insertEdge(i, j, val);//����ġ�� ���� �� �翬�� val����ġ�߰�
				}
			}//�ٽ� �� �ٲ�� �̹��� B 
		}ifs.close();
	}
};
/*int main()
{
	WGraph g;
	g.load("graph4.txt");
	g.display();
}*/