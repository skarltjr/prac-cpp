#pragma once
#include <iostream>

#define MAX_QUEUE_SIZE 100

inline void error(const char* str) {
    std::cerr << str << "\n"; // 에러의 경우는 std::cerr로 출력합니다.
    exit(1);
};

class CircularQueue {
protected:
    int front; // 가장 앞 (데이터를 꺼내는 위치)
    int rear; // 가장 뒤 (데이터를 넣는 위치)  
    int data[MAX_QUEUE_SIZE];
public:
    CircularQueue() { front = rear = 0; }
    ~CircularQueue() {}
    bool isEmpty() { return front == rear; }
    bool isFull() { return (rear + 1) % MAX_QUEUE_SIZE == front; } // 나머지 연산으로 위치를 찾습니다.
    void enqueue(int val) { // 큐 맨 뒤에 데이터를 추가
        if (isFull()) {
            error(" Error: 큐가 포화상태입니다\n");
        }
        else {
            rear = (rear + 1) % MAX_QUEUE_SIZE;
            data[rear] = val;
        }
    }
    int dequeue() { // 큐 맨 앞에서 데이터를 꺼냄
        if (isEmpty()) {
            error(" Error: 큐가 공백상태입니다\n");
        }
        else {
            front = (front + 1) % MAX_QUEUE_SIZE;//그러니까 맨 앞꺼 삭제한 상태에서
            return data[front];//삭제된 부분의 값 알려주는게 아니라 말 그대로 맨 앞꺼 알려주니까
            //삭제된 부분이 맨 앞이였지만 이젠아니지. 이제 맨앞은 front+1이니까 front+1의 data를 알려줘야
            //맨 앞데이터 보여주는거지.? 근데 큐 맨앞데이터를 꺼냄?
        }
    }
};