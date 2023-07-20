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
	for (int i = 0; i < M->len; i++)
	{
		OLink p;
		p = (OLink)malloc(sizeof(OLNode));
		cin >> p->row >> p->col >> p->x;
		Insert(M, p);
	}
}

void MatrixAdd(CrossList* A, CrossList* B, CrossList* C)
{
	OLink p, q;
	for (int i = 1; i <= A->m; i++)
	{
		p = A->row_head[i], q = B->row_head[i];
		while (p != NULL && q != NULL)
		{
			if (p->col == q->col)
			{
				int sum = p->x + q->x;
				if (sum != 0)
				{
					OLink m = (OLink)malloc(sizeof(OLNode));
					m->x = sum;
					m->row = i;
					m->col = p->col;
					Insert(C, m);
					C->len++;
				}
				p = p->right;
				q = q->right;
			}
			else if (p->col < q->col)
			{
				OLNode* m = (OLNode*)malloc(sizeof(OLNode));
				m->x = p->x;
				m->row = i;
				m->col = p->col;
				Insert(C, m);
				C->len++;
				p = p->right;
			}
			else
			{
				OLNode* m = (OLNode*)malloc(sizeof(OLNode));
				m->x = q->x;
				m->row = i;
				m->col = q->col;
				Insert(C, m);
				C->len++;
				q = q->right;
			}
		}
		while (p != NULL)
		{
			OLNode* m = (OLNode*)malloc(sizeof(OLNode));
			m->x = p->x;
			m->row = i;
			m->col = p->col;
			Insert(C, m);
			C->len++;
			p = p->right;
		}
		while (q != NULL)
		{
			OLNode* m = (OLNode*)malloc(sizeof(OLNode));
			m->x = q->x;
			m->row = i;
			m->col = q->col;
			Insert(C, m);
			C->len++;
			q = q->right;
		}
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
	cin >> A->m >> A->n >> A->len >> B->len;
	C->m = B->m = A->m;
	C->n = B->n = A->n;
	C->len = 0;
	CreatCrossList(A);
	CreatCrossList(B);
	CreatCrossList(C);
	MatrixAdd(A, B, C);
	output(C);
	return 0;
}