#include<iostream>

using namespace std;
const int N = 1000;
const int M = 5000;

void Init();
void Add();
void Mul(int);
void Dev(int);

struct Node
{
	int data;
	Node* pre, * next;
};

Node* Ls, * Li, * p, * q;

int main()
{
	int n;
	cin >> n;
	Init();
	for (int i = 1; i < M; i++)
	{
		Mul(i);
		Dev(2 * i + 1);
		Add();
	}
	int cnt = 0;
	p = Ls->next;
	cout << p->data << '.';
	p = p->next;
	while (cnt < n && p != Ls)
	{
		cout << p->data;
		cnt++;
		p = p->next;
	}
	return 0;
}

void Init()
{
	Ls = (Node*)malloc(sizeof(Node));
	Ls->next = Ls;
	Ls->pre = Ls;
	for (int i = 0; i < N; i++)
	{
		p = (Node*)malloc(sizeof(Node));
		p->data = 0;
		p->pre = Ls->pre;
		p->next = Ls;
		Ls->pre->next = p;
		Ls->pre = p;
	}
	Ls->next->data = 2;

	Li = (Node*)malloc(sizeof(Node));
	Li->next = Li;
	Li->pre = Li;
	for (int i = 0; i < N; i++)
	{
		p = (Node*)malloc(sizeof(Node));
		p->data = 0;
		p->pre = Li->pre;
		p->next = Li;
		Li->pre->next = p;
		Li->pre = p;
	}
	Li->next->data = 2;
}

void Add()
{
	int carry = 0;
	for (p = Ls->pre, q = Li->pre; p != Ls && q != Li; q = q->pre, p = p->pre)
	{
		carry += p->data + q->data;
		p->data = carry % 10;
		carry /= 10;
	}
}

void Mul(int i)
{
	int rem = 0;
	for (p = Li->pre; p != Li; p = p->pre)
	{
		rem += p->data * i;
		p->data = rem % 10;
		rem /= 10;
	}
}

void Dev(int i)
{
	int leave = 0;
	for (p = Li->next; p != Li; p = p->next)
	{
		leave = leave * 10 + p->data;
		p->data = leave / i;
		leave %= i;
	}
}