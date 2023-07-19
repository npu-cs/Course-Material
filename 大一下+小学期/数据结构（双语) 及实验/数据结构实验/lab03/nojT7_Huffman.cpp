#include <iostream>
#include <cstring>

using namespace std;

//哈夫曼树的存储表示
const int N = 100;
const int M = 2*N - 1;
typedef struct {
    int weight;
    int parent, lchild, rchild;
    char data;
} HTNode, HuffmanTree[M+1];

//哈夫曼编码的存储表示
typedef struct {
    int cd[N]; //存放哈夫曼编码
    int start; //编码在cd中的起始位置
} HCodeNode, HuffmanCode[N+1];

//构造选择函数：权值最小的两个结点s1和s2
void select(HuffmanTree ht, int pos, int* s1, int* s2) {
    int min1 = 100000, min2 = 100000;
    for(int i=1; i<=pos; i++){
        if(ht[i].parent == 0){
            if(ht[i].weight < min1){
                min2 = min1;
                *s2 = *s1;
                min1 = ht[i].weight;
                *s1 = i;    
            }
            else if(ht[i].weight < min2){
                min2 = ht[i].weight;
                *s2 = i;
            }
        }
    }
}

//构造哈夫曼树
void CreateHT(HuffmanTree ht, int n){
    if(n <= 1) return;
    int m = 2*n -1;
    for(int i=0; i<=m; i++){
        ht[i].parent = 0;
        ht[i].lchild = 0;
        ht[i].rchild = 0;
        ht[i].weight = 0;
    }
    for(int i=1; i<=n; i++){
        cin >> ht[i].data;
    }
    for(int i=1; i<=n; i++){
        cin >> ht[i].weight;
    }
    int s1, s2;
    for(int i=n+1; i<=m; i++){
        select(ht, i-1, &s1, &s2);
        ht[s1].parent = i;
        ht[s2].parent = i;
        ht[i].lchild = s1;
        ht[i].rchild = s2;
        ht[i].weight = ht[s1].weight + ht[s2].weight;
    }
}

//哈夫曼编码
void encode(HuffmanTree ht, HuffmanCode hc, int n){
for(int i=1; i<=n; i++){
    hc[i].start = n;
    int child, parent;
    child = i;
    parent = ht[child].parent;
    while(parent != 0){
        if(ht[parent].lchild == child){
            hc[i].cd[hc[i].start--] = 0;
        }
        else{
            hc[i].cd[hc[i].start--] = 1;
        }
        child = parent;
        parent = ht[child].parent;
    }
    hc[i].start++;
}
}

//打印哈夫曼编码
int len = 0;
int str[1000]={0};
void printCode(HuffmanTree ht, HuffmanCode hc, int n){
    char code[1000];
    cin >> code;
    for(int i=0; i<strlen(code); i++){
        for(int j=1; j<=n; j++){
            if(code[i] == ht[j].data){
                for(int k=hc[j].start; k<=n; k++){
                    cout << hc[j].cd[k];
                    str[len++] = hc[j].cd[k];
                }
            }
        }
    }
}

//哈夫曼编码解码
void decode(HuffmanTree ht, int n){
    int p;
    int i = 0;
    while(i < len){
        p = 2*n - 1;
        while(ht[p].lchild != 0 && ht[p].rchild != 0){
            if(str[i] == 0){
                p = ht[p].lchild;
            }
            else{
                p = ht[p].rchild;
            }
            i++;
        }
    cout << ht[p].data;
    }
}

int main(){
    int n;
    cin >> n;
    HuffmanTree ht;
    HuffmanCode hc;
    CreateHT(ht, n);
    encode(ht, hc, n);
    printCode(ht, hc, n);
    cout << endl;
    decode(ht, n);
    return 0;
}
