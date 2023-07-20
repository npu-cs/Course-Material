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
	flag[origin] = true;	////��origin�Ž����뵽������
	for (int i = 0; i < n; i++)
		pre[i] = origin;	//������㵽Դ�ڵ�����·����ʼ��Ϊֱ�ӵ�Դ�ڵ�
	pre[origin] = -1;
	for (int i = 1; i < n; i++)
	{
		int minn = 10000, v;
		//�ҳ����������origin�Ž������ĵ�
		for (int j = 0; j < n; j++)
			if (minn > d[origin][j] && flag[j] == false)
			{
				minn = d[origin][j];
				v = j;
			}
		dis[v] = minn;
		flag[v] = true;	//���õ���뵽����֮��
		for (int j = 0; j < n; j++)
			if (d[origin][j] > d[origin][v] + d[v][j])
			{
				d[origin][j] = d[origin][v] + d[v][j];	//�øýڵ���¼�����ĵ㵽v�Ž��ľ���
				pre[j] = v;	//�����½������·���иýڵ��ǰһ�����Ϊu
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