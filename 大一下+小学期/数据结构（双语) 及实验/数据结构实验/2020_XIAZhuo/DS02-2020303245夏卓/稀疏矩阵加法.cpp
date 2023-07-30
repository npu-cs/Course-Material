#include<iostream>

using namespace std;
const int N = 500;

struct Triple
{
	int row, col, x;
};

struct TSMatrix
{
	Triple data[N];
	int m, n, len;
};

TSMatrix A, B, C;

void Init() {
	cin >> A.m >> A.n;
	C.m = B.m = A.m;
	C.n = B.n = A.n;
	cin >> A.len >> B.len;
	for (int i = 0; i < A.len; i++)
		cin >> A.data[i].row >> A.data[i].col >> A.data[i].x;
	for (int i = 0; i < B.len; i++)
		cin >> B.data[i].row >> B.data[i].col >> B.data[i].x;
}

void MatrixAdd()
{
	int i = 0, j = 0, k = 0, sum;
	while (i < A.len && j < B.len)
	{
		if (A.data[i].row == B.data[j].row)
		{
			if (A.data[i].col == B.data[j].col)
			{
				sum = A.data[i].x + B.data[j].x;
				if (sum != 0)
				{
					C.data[k].x = sum;
					C.data[k].row = A.data[i].row;
					C.data[k].col = A.data[i].col;
					C.len++;
					k++;
				}
				i++;
				j++;
			}
			else if (A.data[i].col > B.data[j].col)
			{
				C.data[k].x = B.data[j].x;
				C.data[k].row = B.data[j].row;
				C.data[k].col = B.data[j].col;
				C.len++;
				j++;
				k++;
			}
			else
			{
				C.data[k].x = A.data[i].x;
				C.data[k].row = A.data[i].row;
				C.data[k].col = A.data[i].col;
				C.len++;
				i++;
				k++;
			}
		}
		else if (A.data[i].row < B.data[j].row)
		{
			C.data[k].x = A.data[i].x;
			C.data[k].row = A.data[i].row;
			C.data[k].col = A.data[i].col;
			C.len++;
			i++;
			k++;
		}
		else
		{
			C.data[k].x = B.data[j].x;
			C.data[k].row = B.data[j].row;
			C.data[k].col = B.data[j].col;
			C.len++;
			j++;
			k++;
		}
	}
	while (i < A.len)
	{
		C.data[k].x = A.data[i].x;
		C.data[k].row = A.data[i].row;
		C.data[k].col = A.data[i].col;
		C.len++;
		i++;
		k++;
	}
	while (j < B.len)
	{
		C.data[k].x = B.data[j].x;
		C.data[k].row = B.data[j].row;
		C.data[k].col = B.data[j].col;
		C.len++;
		j++;
		k++;
	}
}

int main()
{
	Init();
	MatrixAdd();
	for (int i = 0; i < C.len; i++)
		cout << C.data[i].row << ' ' << C.data[i].col << ' ' << C.data[i].x << endl;
	return 0;
}