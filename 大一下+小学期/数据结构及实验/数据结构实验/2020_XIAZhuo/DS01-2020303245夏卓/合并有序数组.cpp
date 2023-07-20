#include<iostream>
#include<algorithm>
using namespace std;
const int N = 30;

int a[N], b[N], c[2 * N];

int main()
{
	int n, m;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	cin >> m;
	for (int i = 0; i < m; i++)
		cin >> b[i];
	int cnt = 0, i, j;
	for (i = 0, j = 0; i < n && j < m;)
	{
		if (a[i] < b[j])
			c[cnt++] = a[i++];
		else
			c[cnt++] = b[j++];
	}
	while (i < n)
		c[cnt++] = a[i++];
	while (j < m)
		c[cnt++] = b[j++];
	for (int i = 0; i < n; i++)
		cout << a[i] << endl;
	for (int i = 0; i < m; i++)
		cout << b[i] << endl;
	for (int i = 0; i < cnt; i++)
		cout << c[i] << endl;
	return 0;
}