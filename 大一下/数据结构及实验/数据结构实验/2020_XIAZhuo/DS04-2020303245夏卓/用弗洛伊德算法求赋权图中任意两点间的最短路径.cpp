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
				pre[i][j] = i;	//ָ����j��i·���ϵĵ�һ����
		}
	for (int k = 0; k < n; k++)	//��һ��ѭ�����������м���
		for (int i = 0; i < n; i++)	//�ڶ���ѭ����������Դ��
			for (int j = 0; j < n; j++)	//��һ��ѭ�����������յ�
				if (d[i][j] > d[i][k] + d[k][j])
				{
					d[i][j] = d[i][k] + d[k][j];
					pre[i][j] = pre[k][j];	//�����³ɹ������յ㵽Դ���ǰһ�����Ϊ�м���
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