#pragma once
#include <iostream>

#define MAX_QUEUE_SIZE 100

inline void error(const char* str) {
    std::cerr << str << "\n"; // ������ ���� std::cerr�� ����մϴ�.
    exit(1);
};

class CircularQueue {
protected:
    int front; // ���� �� (�����͸� ������ ��ġ)
    int rear; // ���� �� (�����͸� �ִ� ��ġ)  
    int data[MAX_QUEUE_SIZE];
public:
    CircularQueue() { front = rear = 0; }
    ~CircularQueue() {}
    bool isEmpty() { return front == rear; }
    bool isFull() { return (rear + 1) % MAX_QUEUE_SIZE == front; } // ������ �������� ��ġ�� ã���ϴ�.
    void enqueue(int val) { // ť �� �ڿ� �����͸� �߰�
        if (isFull()) {
            error(" Error: ť�� ��ȭ�����Դϴ�\n");
        }
        else {
            rear = (rear + 1) % MAX_QUEUE_SIZE;
            data[rear] = val;
        }
    }
    int dequeue() { // ť �� �տ��� �����͸� ����
        if (isEmpty()) {
            error(" Error: ť�� ��������Դϴ�\n");
        }
        else {
            front = (front + 1) % MAX_QUEUE_SIZE;//�׷��ϱ� �� �ղ� ������ ���¿���
            return data[front];//������ �κ��� �� �˷��ִ°� �ƴ϶� �� �״�� �� �ղ� �˷��ִϱ�
            //������ �κ��� �� ���̿����� �����ƴ���. ���� �Ǿ��� front+1�̴ϱ� front+1�� data�� �˷����
            //�� �յ����� �����ִ°���.? �ٵ� ť �Ǿյ����͸� ����?
        }
    }
};