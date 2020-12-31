#ifndef TREE_H
#define TREE_H
#include <iostream>
using namespace std;

struct T_Node
{
	public:
		T_Node* up;
		T_Node* down;
		T_Node* left;
		T_Node* right;

		int **puzzle = new int*[4];

		int* children = new int[4];

		T_Node()
		{
			for(int i = 0; i < 4; i++)
			{
				puzzle[i] = new int[4];

				children[i] = 1;
			}

			up = NULL;
			down = NULL;
			left = NULL;
			right = NULL;
		}
		~T_Node()
		{
		}
};

class Queue;

class Tree
{
	private:
		T_Node* root;

	public:
		Tree();

		~Tree();

		void MakeRootNode(int** puzzle);

		void NodePuzzlePrinting(T_Node* node);

		T_Node* getRootNode();

		int* getChildrenArray(T_Node* node);

		void BlankTileRowandColumn(T_Node* node, int& blank_row, int& blank_col);
		void PossibleChildren(T_Node* node, int blank_row, int blank_col);
		void MakeTempPuzzle(int**& temp, T_Node* node);
		void ChildPuzzleSameAsCurrentParent(bool& flag1, int** temp, T_Node* parent_node);
		
		bool MakeUpChild(T_Node* node, T_Node* parent_node, int blank_row, int blank_col, Queue* q, Queue* pq);
		bool MakeDownChild(T_Node* node, T_Node* parent_node, int blank_row, int blank_col, Queue* q, Queue* pq);
		bool MakeLeftChild(T_Node* node, T_Node* parent_node, int blank_row, int blank_col, Queue* q, Queue* pq);
		bool MakeRightChild(T_Node* node, T_Node* parent_node, int blank_row, int blank_col, Queue* q, Queue* pq);
		
		bool MakeChildren(Queue* q, Queue* pq, int i, Tree T, int NoT);

		bool GotGoal(T_Node* node);
};
#endif
