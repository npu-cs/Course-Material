#include<iostream>
#include<cstring>
using namespace std;
const int N = 110;

int d[N][N], dis[N];	//��¼��֮��ľ���
bool flag[N];		//��¼�Ƿ񱻼��뼯��֮��

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
				//�ҵ����������0�������һ����
			{
				minn = d[0][j];
				v = j;
			}
		dis[v] = minn;
		flag[v] = true;		//���õ���뼯����
		for (int j = 0; j < n; j++)	//�øõ���������㵽0��ľ���
			if (d[0][j] > d[0][v] + d[v][j])
				d[0][j] = d[0][v] + d[v][j];
	}
	cout << 0 << endl;
	for (int i = 1; i < n; i++)
		cout << dis[i] << endl;
	return 0;
}