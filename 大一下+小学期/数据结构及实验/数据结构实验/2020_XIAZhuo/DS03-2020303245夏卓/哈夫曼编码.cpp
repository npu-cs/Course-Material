//详细注释请见实验报告核心算法的伪代码框架部分

#include<iostream>
#include<queue>
#include<map>
using namespace std;

const int N = 110;
const int M = 2 * N - 1;
typedef pair<int, int> PII;

typedef struct {
	int weight;
	int parent, LChild, RChild;
}HTNode, HuffmanTree[M + 1];

void CreatHuffmanTree(HuffmanTree ht, int w[], int n) {
	priority_queue<PII, vector<PII>, greater<PII>> heap;
	for (int i = 1; i <= n; i++)
	{
		ht[i] = { w[i],0,0,0 };
		heap.push({ ht[i].weight,i });
	}
	int m = 2 * n - 1;
	for (int i = n + 1; i <= m; i++)
		ht[i] = { 0,0,0,0 };
	for (int i = n + 1; i <= m; i++) {
		int s1, s2;
		s1 = heap.top().second; heap.pop();
		s2 = heap.top().second; heap.pop();
		ht[i].weight = ht[s1].weight + ht[s2].weight;
		ht[i].LChild = s1; ht[i].RChild = s2;
		ht[s1].parent = i; ht[s2].parent = i;
		heap.push({ ht[i].weight,i });
	}
}

void CreatHuffmanCode(HuffmanTree ht, string hc[], int n) {
	for (int i = 1; i <= n; i++)
	{
		string str;
		for (int c = i, p = ht[i].parent; p != 0; c = p, p = ht[c].parent)
		{
			if (ht[p].LChild == c)
				str += '0';
			else
				str += '1';
		}
		for (int j = str.size() - 1; j >= 0; j--) {
			hc[i] += str[j];
		}
	}
}

int main()
{
	map<char, int> c;
	int n, w[N];
	char ch[N];
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> ch[i];
		c[ch[i]] = i;
	}
	for (int i = 1; i <= n; i++)
		cin >> w[i];
	string str, decoded_str;
	cin >> str;
	HuffmanTree ht;
	CreatHuffmanTree(ht, w, n);
	string hc[N];
	CreatHuffmanCode(ht, hc, n);
	for (int i = 0; i < str.size(); i++)
	{
		int pos = c[str[i]];
		decoded_str += hc[pos];
		cout << hc[pos];
	}
	cout << endl;
	while (decoded_str.size() != 0) {
		int i;
		for (i = 1; i <= n; i++)
			if (decoded_str.find(hc[i]) == 0)
				break;
		cout << ch[i];
		decoded_str.erase(0, hc[i].size());
	}
	return 0;
}

