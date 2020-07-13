#pragma once
#include<iostream>
#include<string>
#define MAX_STACK_SIZE 100

inline int error(const char* str) //상수일 때 const붙여주는 습관 갖자.
{
	std::cerr << str << std::endl; // 에러를 나타낼때 cout 대신 cerr을 쓰는 법
	exit(1);  //1인 이유는 이 함수가 사용될때는 비정상 종료이기때문에 정상인경우만 0을 쓴다.
}

template<typename T>
class ArrayStack
{
private:
	T data[MAX_STACK_SIZE];
	int top; // 요소의 위치를 알 수 있게해주는 변수
public:
	ArrayStack()
	{
		top = -1; // 스택을 배열로 만든다. 그럼 맨 첫번째. 맨아래는 0번부터 시작할텐데 비어있음을 알려주기위해 0보다 작은 -1사용
	}
	~ArrayStack() {}
	bool isEmpty() { return top == -1; }//top=-1이면 당연히 비어있는 상태
	bool isFull() { return top == MAX_STACK_SIZE - 1; }//0부터 시작이니까 끝은 99임을 생각
	void push(T e)
	{
		if (isFull())
		{
			error("스택이 가득 차 있습니다.");
		}
		data[++top] = e; //맨 위에 정보 추가니까 top이 ++된 위치에 e를 넣어준다 ++top인 이유는 증가를 먼저 해줘야하니까
	}

	T pop() // 데이터를 꺼내 보여주는 함수. 당연히 여기선 정수데이터를 입력받으니 보내줄때도 int형이어야한다
	{
		if (isEmpty())
		{
			error("스택이 비어있습니다");
		}
		return data[top--]; //top-- 인 이유는 top에 데이터를 보여준 후! 그 top을 삭제하니까 갯수도 줄기 때문
	}

	T peek()
	{
		if (isEmpty())
		{
			error("스택이 비어있습니다");
		}
		return data[top];
	}

	void display()
	{
		std::cout << "스택 항목의 수= " << top + 1 << "개 "; // top는 0부터시작이니까
		//size 변수를 만들어 줄 필요가없는게 size는 어차피 top+1이랑 같다.
		for (int i = 0; i <= top; i++)
		{
			std::cout << "[ " << data[i] << " ]";
		}
		std::cout << std::endl;
	}
};