#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
const int N = 110;

int d[N][N], dis[N];
bool flag[N];
int pre[N];
int nex[N];

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> d[i][j];
	int origin, target;
	cin >> origin >> target;
	dis[origin] = 0;
	flag[origin] = true;	////将origin号结点加入到集合中
	for (int i = 0; i < n; i++)
		pre[i] = origin;	//将各结点到源节点的最短路径初始化为直接到源节点
	pre[origin] = -1;
	for (int i = 1; i < n; i++)
	{
		int minn = 10000, v;
		//找出集合外距离origin号结点最近的点
		for (int j = 0; j < n; j++)
			if (minn > d[origin][j] && flag[j] == false)
			{
				minn = d[origin][j];
				v = j;
			}
		dis[v] = minn;
		flag[v] = true;	//将该点加入到集合之中
		for (int j = 0; j < n; j++)
			if (d[origin][j] > d[origin][v] + d[v][j])
			{
				d[origin][j] = d[origin][v] + d[v][j];	//用该节点更新集合外的点到v号结点的距离
				pre[j] = v;	//被更新结点的最短路径中该节点的前一个结点为u
			}
	}
	int cnt = 0;
	while (target != -1) {
		nex[cnt++] = target;
		target = pre[target];
	}
	for (int i = cnt - 1; i >= 0; i--)
		cout << nex[i] << endl;
	return 0;
}