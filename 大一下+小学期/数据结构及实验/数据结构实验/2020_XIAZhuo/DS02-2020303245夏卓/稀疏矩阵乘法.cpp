#include<iostream>

using namespace std;

typedef struct OLNode
{
	int row, col, x;
	OLNode* right, * down;
}OLNode, * OLink;

struct CrossList
{
	OLink* row_head, * col_head;
	int m, n, len;
};

void Insert(CrossList* M, OLink p)
{
	OLink q;
	if (M->row_head[p->row] == NULL)
	{
		M->row_head[p->row] = p;
		p->right = NULL;
	}
	else
	{
		q = M->row_head[p->row];
		while (q->right != NULL && q->right->col < p->col)
			q = q->right;
		p->right = q->right;
		q->right = p;
	}
	if (M->col_head[p->col] == NULL)
	{
		M->col_head[p->col] = p;
		p->down = NULL;
	}
	else
	{
		q = M->col_head[p->col];
		while (q->down != NULL && q->down->row < p->row)
			q = q->down;
		p->down = q->down;
		q->down = p;
	}
}

void CreatCrossList(CrossList* M)
{
	M->row_head = (OLink*)malloc((M->m + 1) * sizeof(OLink));
	M->col_head = (OLink*)malloc((M->n + 1) * sizeof(OLink));
	for (int i = 1; i <= M->m; i++)
		M->row_head[i] = NULL;
	for (int i = 1; i <= M->n; i++)
		M->col_head[i] = NULL;
}

void MatrixMul(CrossList* A, CrossList* B, CrossList* C)
{
	OLink p, q;
	for (int i = 1; i <= A->m; i++)
	{
		for (int j = 1; j <= B->n; j++)
		{
			p = A->row_head[i];
			q = B->col_head[j];
			int sum = 0;
			while (p != NULL && q != NULL)
			{
				if (p->col == q->row)
				{
					sum += p->x * q->x;
					p = p->right;
					q = q->down;
				}
				else if (p->col < q->row)
					p = p->right;
				else q = q->down;
			}
			if (sum != 0)
			{
				OLink r = (OLink)malloc(sizeof(OLNode));
				r->row = i;
				r->col = j;
				r->x = sum;
				Insert(C, r);
				C->len++;
			}
		}
	}
}

void Input(CrossList* M)
{
	int r, c, e;
	while (cin >> r >> c >> e)
	{
		if (r == 0) break;
		OLink p = (OLink)malloc(sizeof(OLNode));
		p->row = r;
		p->col = c;
		p->x = e;
		Insert(M, p);
		M->len++;
	}
}

void output(CrossList* C)
{
	for (int i = 1; i <= C->m; i++)
	{
		OLink p = C->row_head[i];
		while (p != NULL)
		{
			cout << p->row << ' ' << p->col << ' ' << p->x << endl;
			p = p->right;
		}
	}
}

int main()
{
	CrossList* A, * B, * C;
	A = (CrossList*)malloc(sizeof(CrossList));
	B = (CrossList*)malloc(sizeof(CrossList));
	C = (CrossList*)malloc(sizeof(CrossList));
	cin >> A->m >> A->n;
	CreatCrossList(A);
	Input(A);
	cin >> B->m >> B->n;
	CreatCrossList(B);
	Input(B);
	C->m = A->m;
	C->n = B->n;
	C->len = 0;
	CreatCrossList(C);
	MatrixMul(A, B, C);
	output(C);
	return 0;
}