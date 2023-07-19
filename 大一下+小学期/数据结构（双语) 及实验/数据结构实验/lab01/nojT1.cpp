#include <iostream>

using namespace std;

const int MAXSIZE = 100;

typedef struct SeqList *pList;
//SeqList顺序表，内含elenum（元素个数）和list[]两个元素。
struct SeqList {
    int elenum;
    int list[MAXSIZE];
};
//构建顺序表，将pList和元素个数n作为输入值，采用循环输入填充数组
void CreateSeq(pList p, int n){
    for (int i=0; i<n; i++){
        cin >> p->list[i];
    }
}
//按照思路，不断比较两个数组的元素并将其填入新数组，当一个数组为空时，将未遍历完的数组的剩余元素直接填入新数组
void MergeList(pList pa, pList pb, pList pc){
    int i=0, j=0, k=0;
    while(i<pa->elenum && j<pb->elenum){
        if (pa->list[i] < pb->list[j]){
            pc->list[k++] = pa->list[i++];
        } else {
            pc->list[k++] = pb->list[j++];
        }
    }
    while(i<pa->elenum){
        pc->list[k++] = pa->list[i++];
    }
    while(j<pb->elenum){
        pc->list[k++] = pb->list[j++];
    }
    pc->elenum = k;
}
//在遍历完成后，将新数组的结构体指针作为传入值，将得到的新数组采用循环输出，每次输出均换行的形式打印出来
void PrintList(pList p){
    for (int i=0; i<p->elenum; i++){
        cout << p->list[i] << endl;
    }
}

int main(){
    int n, m;
    pList pa = new SeqList;
    pList pb = new SeqList;
    pList pc = new SeqList;   
    cin >> n;
    pa->elenum = n;
    CreateSeq(pa, n);
    cin >> m;
    pb->elenum = m;
    CreateSeq(pb, m);
    MergeList(pa, pb, pc);
    PrintList(pc);
}
