#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <unistd.h>
#include "Tree.h"
#include "Tree.cpp"
#include "Queue.h"
#include "Queue.cpp"
#include <chrono>
#include <pthread.h>
using namespace std;
using namespace std::chrono;

int check(int **puzzlee, int num, int k, int l)
{
	bool flag = false;
	int ret = -1;
	
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(((i == k) && (j == l)) && (puzzlee[i][j] != num))
			{
				flag = true;
				
				ret = 0;
			}
			if(puzzlee[i][j] == num)
			{
				flag = true;
				
				ret = 1;
			}
			if(flag == true)
			{
				break;
			}
		}
		if(flag == true)
		{
			break;
		}
	}
	
	return ret;
}
int** PuzzleGenerator()
{
	int num = -1;
	int **puzzle = new int*[4];

	for(int i = 0; i < 4; i++)
	{
		puzzle[i] = new int[4];
	}

	bool flag = false;

	srand(time(NULL));

	for(int m = 0; m < 4; m++)
	{
		for(int n = 0; n < 4; n++)
		{
			puzzle[m][n] = -1;
		}
	}

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			num = rand() % 16 + 1;

			flag = false;

			for(int k = 0; k < 4; k++)
			{
				for(int l = 0; l < 4; l++)
				{
					if((k == i) && (l == j))
					{
						flag = true;
						break;
					}
					if(num == puzzle[k][l])
					{
						int flag = -1;

						do
						{
							num = rand() % 16 + 1;

							flag = check(puzzle, num, k, l);

						} while(flag == 1);
					}
				}

				if(flag == true)
				{
					break;
				}
			}

			puzzle[i][j] = num;
		}
	}

	return puzzle;
}
int main(int argc, char* argv[])
{
	auto start = high_resolution_clock::now();
	
	int numofthreads = 0;
	
	numofthreads = atoi(argv[1]);
	
	cout << "Number of Threads : " << numofthreads << endl << endl;
	
	int **puzzle = PuzzleGenerator();

	puzzle[0][0] = 2;
	puzzle[0][1] = 3;
	puzzle[0][2] = 4;
	puzzle[0][3] = 16;
	puzzle[1][0] = 1;
	puzzle[1][1] = 5;
	puzzle[1][2] = 6;
	puzzle[1][3] = 7;
	puzzle[2][0] = 10;
	puzzle[2][1] = 11;
	puzzle[2][2] = 12;
	puzzle[2][3] = 8;
	puzzle[3][0] = 9;
	puzzle[3][1] = 13;
	puzzle[3][2] = 14;
	puzzle[3][3] = 15;

	/* ----------------- */

	Tree T;

	T.MakeRootNode(puzzle);

	//T.NodePuzzlePrinting(T.getRootNode());

	Queue* q = new Queue;
	Queue* pq = new Queue;

	bool flag = false;

	int i = 0;

	while(flag == false)
	{
		flag = T.MakeChildren(q, pq, i, T, numofthreads);

		i++;

		cout << endl << endl;
		//sleep(5);
	}
	
	auto stop = high_resolution_clock::now();
	
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "\n\nBranch & Bound Running Time : " << duration.count() << " microseconds\n";
}
