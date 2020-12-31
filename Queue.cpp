#include <iostream>
#include "Queue.h"
using namespace std;

Queue::Queue()
{
	queue = new T_Node *[10000000];
	size = 10000000;

	front = -1;
	rear = -1;
}
Queue::~Queue()
{

}
void Queue::Enqueue(T_Node* node)
{
	if(IsFull())
	{
		cout << "\nQueue is Full";

		return;
	}
	if(IsEmpty())
	{
		front = 0;
		rear = 0;
	}
	else
	{
		rear = (rear + 1) % size;
	}

	queue[rear] = node;
}
T_Node* Queue::Dequeue()
{
	if(IsEmpty())
	{
		cout << "Can't Dequeue, as Queue is Empty";

		return NULL;
	}

	T_Node* node = queue[front];

	if(front == rear)
	{
		front = -1;
		rear = -1;
	}
	else
	{
		front = (front + 1) % size;
	}

	return node;
}
bool Queue::IsFull()
{
	if(((rear + 1) % size) == front)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Queue::IsEmpty()
{
	if(front == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Queue::MakeNull()
{
	front = -1;
	rear = -1;
}
