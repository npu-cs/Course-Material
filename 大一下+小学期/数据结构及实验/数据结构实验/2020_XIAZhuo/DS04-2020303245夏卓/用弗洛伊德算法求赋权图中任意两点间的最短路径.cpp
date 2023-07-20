#include<iostream>
#include<algorithm>
using namespace std;
const int N = 110;
int d[N][N];
int pre[N][N];

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> d[i][j];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				pre[i][j] = -1;
			else
				pre[i][j] = i;	//指的是j到i路径上的第一个点
		}
	for (int k = 0; k < n; k++)	//第一重循环遍历的是中间结点
		for (int i = 0; i < n; i++)	//第二重循环遍历的是源点
			for (int j = 0; j < n; j++)	//第一重循环遍历的是终点
				if (d[i][j] > d[i][k] + d[k][j])
				{
					d[i][j] = d[i][k] + d[k][j];
					pre[i][j] = pre[k][j];	//若更新成功，则终点到源点的前一个结点为中间结点
				}
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int origin, target;
		cin >> origin >> target;
		int t = target;
		int ans[N], cnt = 0;
		while (pre[origin][target] != -1)
		{
			ans[cnt++] = pre[origin][target];
			target = pre[origin][target];
		}
		while (cnt--) {
			cout << ans[cnt] << endl;
		}
		cout << t << endl;
	}
	return 0;
}