#include <iostream>
#include <fstream>
#include "Tree.h"
#include "Queue.h"
#include <pthread.h>
using namespace std;

pthread_t tid2, tid3, tid4, tid5, tid6, tid7, tid8, tid9, tid10, tid11, tid12, tid13, tid14, tid15, tid16, tid17, tid18, tid19, tid20, tid21, tid22, tid23, tid24, tid25, tid26, tid27, tid28, tid29, tid30, tid31, tid32, tid33, tid34, tid35, tid36;

Tree::Tree()
{
	root = new T_Node;
}
Tree::~Tree()
{
}
T_Node* Tree::getRootNode()
{
	return root;
}
int* Tree::getChildrenArray(T_Node* node)
{
	return node->children;
}
bool Tree::GotGoal(T_Node* node)
{
	int num = 0;

	bool flag = true;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			num++;

			if(node->puzzle[i][j] == num)
			{
				flag = true;
			}
			else
			{
				flag = false;

				break;
			}
		}

		if(flag == false)
		{
			break;
		}
	}

	return flag;
}
void Tree::MakeRootNode(int** puzzle)
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			root->puzzle[i][j] = puzzle[i][j];
		}
	}
}
void Tree::NodePuzzlePrinting(T_Node* node)
{
	for(int i = 0; i < 4; i++)
	{
		cout << endl;

		for(int j = 0; j < 4; j++)
		{
			cout << node->puzzle[i][j] << " ";
		}
	}
}
void Tree::BlankTileRowandColumn(T_Node* node, int& blank_row, int& blank_col)
{
	bool flag = false;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(node->puzzle[i][j] == 16)
			{
				flag = true;

				blank_row = i;
				blank_col = j;

				break;
			}
		}
		if(flag == true)
		{
			break;
		}
	}
}
void Tree::PossibleChildren(T_Node* node, int blank_row, int blank_col)
{
	for(int i = 0; i < 4; i++)
	{
		cout << node->children[i] << " ";
	}
	
	cout << endl;

	if(blank_row == 0)
	{
		node->children[0] = 0;
	}
	if(blank_row == 3)
	{
		node->children[1] = 0;
	}
	if(blank_col == 0)
	{
		node->children[2] = 0;
	}
	if(blank_col == 3)
	{
		node->children[3] = 0;
	}

	for(int i = 0; i < 4; i++)
	{
		cout << node->children[i] << " ";
	}
}
void Tree::MakeTempPuzzle(int**& temp, T_Node* node)
{
	temp = new int*[4];
	
	for(int i = 0; i < 4; i++)
	{
		temp[i] = new int[4];
	}
	
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			temp[i][j] = node->puzzle[i][j];
		}
	}
}
void Tree::ChildPuzzleSameAsCurrentParent(bool& flag1, int** temp, T_Node* parent_node)
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(temp[i][j] == parent_node->puzzle[i][j])
			{
				flag1 = true;
			}
			else
			{
				flag1 = false;

				break;
			}
		}

		if(flag1 == false)
		{
			break;
		}
	}
}
bool Tree::MakeUpChild(T_Node* node, T_Node* parent_node, int blank_row, int blank_col, Queue* q, Queue* pq)
{
	if(node->children[0] == 1)
	{
		bool flag1 = true;

		int** temp;

		int temp1 = -1;

		MakeTempPuzzle(temp, node);

		temp1 = temp[blank_row][blank_col];

		temp[blank_row][blank_col] = temp[blank_row - 1][blank_col];

		temp[blank_row - 1][blank_col] = temp1;

		ChildPuzzleSameAsCurrentParent(flag1, temp, parent_node);

		if(flag1 == true)
		{
			node->children[0] = 0;
		}
		if(flag1 == false)
		{
			node->up = new T_Node;
	
			for(int i = 0; i < 4; i++)
			{
				for(int j = 0; j < 4; j++)
				{
					node->up->puzzle[i][j] = temp[i][j];
				}
			}
	
			cout << "\n\nUP";
	
			NodePuzzlePrinting(node->up);
			
			bool goalachieved = GotGoal(node->up);

			if(goalachieved == true)
			{
				cout << "---------------------Goal Achieved----------------------------";
				
				return true;
			}
			else
			{
				q->Enqueue(node->up);
				pq->Enqueue(node);
				
				return false;
			}
		}
	}
	
	return false;
}
bool Tree::MakeDownChild(T_Node* node, T_Node* parent_node, int blank_row, int blank_col, Queue* q, Queue* pq)
{
	if(node->children[1] == 1)
	{
		bool flag1 = true;

		int** temp;

		int temp1 = -1;

		MakeTempPuzzle(temp, node);

		temp1 = temp[blank_row][blank_col];

		temp[blank_row][blank_col] = temp[blank_row + 1][blank_col];

		temp[blank_row + 1][blank_col] = temp1;

		ChildPuzzleSameAsCurrentParent(flag1, temp, parent_node);

		if(flag1 == true)
		{
			node->children[1] = 0;
		}
		if(flag1 == false)
		{
			node->down = new T_Node;
	
			for(int i = 0; i < 4; i++)
			{
				for(int j = 0; j < 4; j++)
				{
					node->down->puzzle[i][j] = temp[i][j];
				}
			}
	
			cout << "\n\nDOWN";
	
			NodePuzzlePrinting(node->down);
			
			bool goalachieved = GotGoal(node->down);

			if(goalachieved == true)
			{
				cout << "---------------------Goal Achieved----------------------------";
				
				return true;
			}
			else
			{
				q->Enqueue(node->down);
				pq->Enqueue(node);
				
				return false;
			}
		}
	}
	
	return false;
}
bool Tree::MakeLeftChild(T_Node* node, T_Node* parent_node, int blank_row, int blank_col, Queue* q, Queue* pq)
{
	if(node->children[2] == 1)
	{
		bool flag1 = true;
	
		int** temp;
	
		int temp1 = -1;
	
		MakeTempPuzzle(temp, node);
	
		temp1 = temp[blank_row][blank_col];
	
		temp[blank_row][blank_col] = temp[blank_row][blank_col - 1];
	
		temp[blank_row][blank_col - 1] = temp1;
	
		ChildPuzzleSameAsCurrentParent(flag1, temp, parent_node);
	
		if(flag1 == true)
		{
			node->children[2] = 0;
		}
		if(flag1 == false)
		{
			node->left = new T_Node;
	
			for(int i = 0; i < 4; i++)
			{
				for(int j = 0; j < 4; j++)
				{
					node->left->puzzle[i][j] = temp[i][j];
				}
			}
	
			cout << "\n\nLEFT";
	
			NodePuzzlePrinting(node->left);
			
			bool goalachieved = GotGoal(node->left);

			if(goalachieved == true)
			{
				cout << "---------------------Goal Achieved----------------------------";

				return true;
			}
			else
			{
				q->Enqueue(node->left);
				pq->Enqueue(node);
				
				return false;
			}
		}
	}
	
	return false;
}
bool Tree::MakeRightChild(T_Node* node, T_Node* parent_node, int blank_row, int blank_col, Queue* q, Queue* pq)
{
	if(node->children[3] == 1)
	{
		bool flag1 = true;

		int** temp;

		int temp1 = -1;

		MakeTempPuzzle(temp, node);

		temp1 = temp[blank_row][blank_col];

		temp[blank_row][blank_col] = temp[blank_row][blank_col + 1];

		temp[blank_row][blank_col + 1] = temp1;

		ChildPuzzleSameAsCurrentParent(flag1, temp, parent_node);

		if(flag1 == true)
		{
			node->children[3] = 0;
		}
		if(flag1 == false)
		{
			node->right = new T_Node;

			for(int i = 0; i < 4; i++)
			{
				for(int j = 0; j < 4; j++)
				{
					node->right->puzzle[i][j] = temp[i][j];
				}
			}
	
			cout << "\n\nRIGHT";
	
			NodePuzzlePrinting(node->right);
			
			bool goalachieved = GotGoal(node->right);

			if(goalachieved == true)
			{
				cout << "---------------------Goal Achieved----------------------------";

				return true;
			}
			else
			{
				q->Enqueue(node->right);
				pq->Enqueue(node);
				
				return false;
			}
		}
	}
	
	return false;
}

struct Children
{
	T_Node* node;
	T_Node* parent_node;
	int blank_row;
	int blank_col;
	Queue* q;
	Queue* pq;
	bool flag;
	
	Tree T;
};
//------------------1---------------
void* UpChildThread_8(void* arg)
{
	Children* U = (Children*)arg;
	
	bool flag = false;
	
	flag = U->T.MakeUpChild(U->node, U->parent_node, U->blank_row, U->blank_col, U->q, U->pq);
	
	U->flag = flag;
		
	void* u = (void*)U;
	
	return u;
}
void* DownChildThread_8(void* arg)
{
	Children* D = (Children*)arg;
	
	bool flag = false;
	
	flag = D->T.MakeDownChild(D->node, D->parent_node, D->blank_row, D->blank_col, D->q, D->pq);
	
	D->flag = flag;
		
	void* d = (void*)D;
	
	return d;
}
void* LeftChildThread_8(void* arg)
{
	Children* L = (Children*)arg;
	
	bool flag = false;
	
	flag = L->T.MakeLeftChild(L->node, L->parent_node, L->blank_row, L->blank_col, L->q, L->pq);
	
	L->flag = flag;
		
	void* l = (void*)L;
	
	return l;
}
void* RightChildThread_8(void* arg)
{
	Children* R = (Children*)arg;
	
	bool flag = false;
	
	flag = R->T.MakeRightChild(R->node, R->parent_node, R->blank_row, R->blank_col, R->q, R->pq);
	
	R->flag = flag;
		
	void* r = (void*)R;
	
	return r;
}
//-------------2-------------
void* AllChildThread_2(void* arg)
{
	Children* A = (Children*)arg;
	
	bool flag = false;
	
	flag = A->T.MakeUpChild(A->node, A->parent_node, A->blank_row, A->blank_col, A->q, A->pq);
	
	if(flag == true)
	{
		A->flag = true;
		
		void* a = (void*)A;
	
		return a;
	}
	
	flag = A->T.MakeDownChild(A->node, A->parent_node, A->blank_row, A->blank_col, A->q, A->pq);
	
	if(flag == true)
	{
		A->flag = true;
		
		void* a = (void*)A;
	
		return a;
	}
	
	flag = A->T.MakeLeftChild(A->node, A->parent_node, A->blank_row, A->blank_col, A->q, A->pq);
	
	if(flag == true)
	{
		A->flag = true;
		
		void* a = (void*)A;
	
		return a;
	}
	
	flag = A->T.MakeRightChild(A->node, A->parent_node, A->blank_row, A->blank_col, A->q, A->pq);
	
	if(flag == true)
	{
		A->flag = true;
		
		void* a = (void*)A;
	
		return a;
	}
	
	A->flag = false;
		
	void* a = (void*)A;
	
	return a;
}
//-----------------3---------------
void* UpDownChildThread_3(void* arg)
{
	Children* UD = (Children*)arg;
	
	bool flag = false;
	
	flag = UD->T.MakeUpChild(UD->node, UD->parent_node, UD->blank_row, UD->blank_col, UD->q, UD->pq);
	
	if(flag == true)
	{
		UD->flag = true;
		
		void* ud = (void*)UD;
	
		return ud;
	}
	
	flag = UD->T.MakeDownChild(UD->node, UD->parent_node, UD->blank_row, UD->blank_col, UD->q, UD->pq);
	
	if(flag == true)
	{
		UD->flag = true;
		
		void* ud = (void*)UD;
	
		return ud;
	}
	
	UD->flag = false;
		
	void* ud = (void*)UD;
	
	return ud;
}
void* LeftRightChildThread_3(void* arg)
{
	Children* LR = (Children*)arg;
	
	bool flag = false;
	
	flag = LR->T.MakeLeftChild(LR->node, LR->parent_node, LR->blank_row, LR->blank_col, LR->q, LR->pq);
	
	if(flag == true)
	{
		LR->flag = true;
		
		void* lr = (void*)LR;
	
		return lr;
	}
	
	flag = LR->T.MakeRightChild(LR->node, LR->parent_node, LR->blank_row, LR->blank_col, LR->q, LR->pq);
	
	if(flag == true)
	{
		LR->flag = true;
		
		void* lr = (void*)LR;
	
		return lr;
	}
	
	LR->flag = false;
		
	void* lr = (void*)LR;
	
	return lr;
}
bool Tree::MakeChildren(Queue* q, Queue* pq, int i, Tree T, int NoT)
{
	T_Node* node;
	T_Node* parent_node;

	if(i == 0)
	{
		node = root;
		parent_node = root;
	}
	else
	{
		node = q->Dequeue();
		parent_node = pq->Dequeue();
	}

	cout << "------Branch Node ------";

	NodePuzzlePrinting(node);
	
	int blank_row = -1, blank_col = -1;

	BlankTileRowandColumn(node, blank_row, blank_col);
	
	cout << endl << endl;
		
	PossibleChildren(node, blank_row, blank_col);
	
	if(NoT == 4)
	{
		Children U;
		U.node = node;
		U.parent_node = parent_node;
		U.blank_row = blank_row;
		U.blank_col = blank_col;
		U.q = q;
		U.pq = pq;
		U.T = T;
		
		Children D;
		D.node = node;
		D.parent_node = parent_node;
		D.blank_row = blank_row;
		D.blank_col = blank_col;
		D.q = q;
		D.pq = pq;
		D.T = T;
		
		Children L;
		L.node = node;
		L.parent_node = parent_node;
		L.blank_row = blank_row;
		L.blank_col = blank_col;
		L.q = q;
		L.pq = pq;
		L.T = T;
			
		Children R;
		R.node = node;
		R.parent_node = parent_node;
		R.blank_row = blank_row;
		R.blank_col = blank_col;
		R.q = q;
		R.pq = pq;
		R.T = T;
	
		void* u;
		void* d;
		void* l;
		void* r;
		
		Children* u1;
		Children* d1;
		Children* l1;
		Children* r1;
		
		pthread_create(&tid2, NULL, UpChildThread_8, (void*)&U);
		pthread_create(&tid3, NULL, DownChildThread_8, (void*)&D);
		pthread_create(&tid4, NULL, LeftChildThread_8, (void*)&L);
		pthread_create(&tid5, NULL, RightChildThread_8, (void*)&R);
	
		pthread_join(tid2, &u);
		pthread_join(tid3, &d);
		pthread_join(tid4, &l);
		pthread_join(tid5, &r);
		
		u1 = (Children*)u;
		d1 = (Children*)d;
		l1 = (Children*)l;
		r1 = (Children*)r;
		
		if(u1->flag == true)
		{
			return true;
		}
		
		if(d1->flag == true)
		{
			return true;
		}
		
		if(l1->flag == true)
		{
			return true;
		}
		
		if(r1->flag == true)
		{
			return true;
		}
		
		return false;
	}
	if(NoT == 3)
	{
		Children U;
		U.node = node;
		U.parent_node = parent_node;
		U.blank_row = blank_row;
		U.blank_col = blank_col;
		U.q = q;
		U.pq = pq;
		U.T = T;
		
		Children D;
		D.node = node;
		D.parent_node = parent_node;
		D.blank_row = blank_row;
		D.blank_col = blank_col;
		D.q = q;
		D.pq = pq;
		D.T = T;
	
		Children LR;
		LR.node = node;
		LR.parent_node = parent_node;
		LR.blank_row = blank_row;
		LR.blank_col = blank_col;
		LR.q = q;
		LR.pq = pq;
		LR.T = T;
		
		void* u;
		void* d;
		void* lr;
		
		Children* u1;
		Children* d1;
		Children* lr1;
		
		pthread_create(&tid24, NULL, UpChildThread_8, (void*)&U);
		pthread_create(&tid25, NULL, DownChildThread_8, (void*)&D);
		pthread_create(&tid26, NULL, LeftRightChildThread_3, (void*)&LR);
		
		pthread_join(tid24, &u);
		pthread_join(tid25, &d);
		pthread_join(tid26, &lr);
		
		u1 = (Children*)u;
		d1 = (Children*)d;
		lr1 = (Children*)lr;
		
		if(u1->flag == true)
		{
			return true;
		}
		
		if(d1->flag == true)
		{
			return true;
		}
		
		if(lr1->flag == true)
		{
			return true;
		}
		
		return false;
	}
	if(NoT == 2)
	{
		Children UD;
		UD.node = node;
		UD.parent_node = parent_node;
		UD.blank_row = blank_row;
		UD.blank_col = blank_col;
		UD.q = q;
		UD.pq = pq;
		UD.T = T;
			
		Children LR;
		LR.node = node;
		LR.parent_node = parent_node;
		LR.blank_row = blank_row;
		LR.blank_col = blank_col;
		LR.q = q;
		LR.pq = pq;
		LR.T = T;
		
		void* ud;
		void* lr;
		
		Children* ud1;
		Children* lr1;
		
		pthread_create(&tid15, NULL, UpDownChildThread_3, (void*)&UD);
		pthread_create(&tid16, NULL, LeftRightChildThread_3, (void*)&LR);
		
		pthread_join(tid15, &ud);
		pthread_join(tid16, &lr);
	
		ud1 = (Children*)ud;
		lr1 = (Children*)lr;
		
		if(ud1->flag == true)
		{
			return true;
		}
		
		if(lr1->flag == true)
		{
			return true;
		}
		
		return false;
	}
	if(NoT == 1)
	{
		Children A;
		A.node = node;
		A.parent_node = parent_node;
		A.blank_row = blank_row;
		A.blank_col = blank_col;
		A.q = q;
		A.pq = pq;
		A.T = T;
	
		void* a;
		
		Children* a1;
		
		pthread_create(&tid10, NULL, AllChildThread_2, (void*)&A);
		
		pthread_join(tid10, &a);
		
		a1 = (Children*)a;
		
		return a1->flag;
	}
}
