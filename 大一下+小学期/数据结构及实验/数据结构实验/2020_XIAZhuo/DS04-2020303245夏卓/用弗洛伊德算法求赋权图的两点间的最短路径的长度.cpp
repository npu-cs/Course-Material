#include<iostream>
#include<algorithm>
using namespace std;
const int N = 110;
int d[N][N];

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> d[i][j];
	for (int k = 0; k < n; k++)	//第一重循环遍历的是中间结点
		for (int i = 0; i < n; i++)	//第二重循环遍历的是源点
			for (int j = 0; j < n; j++)	//第一重循环遍历的是终点
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	int m;
	int ans[N];
	cin >> m;
	for (int i = 0; i < m; i++) {
		int origin, target;
		cin >> origin >> target;
		ans[i] = d[origin][target];
	}
	for (int i = 0; i < m; i++)
		cout << ans[i] << endl;
	return 0;
}