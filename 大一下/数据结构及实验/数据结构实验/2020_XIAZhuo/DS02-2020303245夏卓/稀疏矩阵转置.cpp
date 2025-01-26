#include<iostream>
#include<cstring>
using namespace std;
const int MAXSIZE = 1010;

//三元组表示法
struct Triple
{
	int row, col, x;
};

//稀疏矩阵
struct TSMatrix
{
	Triple data[MAXSIZE];
	int m, n, len;
};

void Init(TSMatrix* A, TSMatrix* B) {
	cin >> A->m >> A->n;
	char str;
	A->len = 0;
	while (1)
	{
		cin >> A->data[A->len].row;
		str = getchar();
		cin >> A->data[A->len].col;
		str = getchar();
		cin >> A->data[A->len].x;
		if (str == '?')
			break;
		A->len++;
	}
}

void FastTransposeTSMatrix(TSMatrix* A, TSMatrix* B)
{
	B->len = A->len;
	B->m = A->n;
	B->n = A->m;
	int pos[MAXSIZE], num[MAXSIZE];
	memset(num, 0, sizeof(num));
	for (int i = 0; i < (*A).len; i++)
		num[(*A).data[i].col]++;
	pos[1] = 0;
	for (int i = 2; i <= (*A).n; i++)
		pos[i] = pos[i - 1] + num[i - 1];
	for (int i = 0; i < (*A).len; i++)
	{
		int col = (*A).data[i].col;		//通过A的列col确定B的行pos[col]
		B->data[pos[col]].col = (*A).data[i].row;
		B->data[pos[col]].row = (*A).data[i].col;
		B->data[pos[col]].x = (*A).data[i].x;
		pos[col]++;
	}
}

int main()
{
	TSMatrix A, B;
	Init(&A, &B);
	FastTransposeTSMatrix(&A, &B);
	for (int i = 0; i < B.len; i++)
		cout << B.data[i].row << ' ' << B.data[i].col << ' ' << B.data[i].x << endl;
	return 0;
}