#include<iostream>
#include<cstring>
using namespace std;
const int N = 110;

int d[N][N], dis[N];	//记录点之间的距离
bool flag[N];		//记录是否被加入集合之中

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> d[i][j];
	for (int i = 0; i < n; i++)
	{
		int minn = 10010, v = 0;
		for (int j = 0; j < n; j++)
			if (d[0][j] != 0 && minn > d[0][j] && flag[j] == false)
				//找到集合外距离0点最近的一个点
			{
				minn = d[0][j];
				v = j;
			}
		dis[v] = minn;
		flag[v] = true;		//将该点加入集合中
		for (int j = 0; j < n; j++)	//用该点更新其他点到0点的距离
			if (d[0][j] > d[0][v] + d[v][j])
				d[0][j] = d[0][v] + d[v][j];
	}
	cout << 0 << endl;
	for (int i = 1; i < n; i++)
		cout << dis[i] << endl;
	return 0;
}