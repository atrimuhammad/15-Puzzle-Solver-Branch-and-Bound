#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include "Tree.h"
using namespace std;

class Queue
{
	private:
		T_Node** queue;

		int size;

		int front;
		int rear;

	public:
		Queue();
		~Queue();

		void Enqueue(T_Node* node);
		T_Node* Dequeue();

		bool IsFull();
		bool IsEmpty();
		void MakeNull();
};
#endif
