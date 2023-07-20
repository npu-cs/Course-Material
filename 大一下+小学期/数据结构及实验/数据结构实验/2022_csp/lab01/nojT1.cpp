#include <iostream>

using namespace std;

const int MAXSIZE = 100;

typedef struct SeqList *pList;
//SeqList˳����ں�elenum��Ԫ�ظ�������list[]����Ԫ�ء�
struct SeqList {
    int elenum;
    int list[MAXSIZE];
};
//����˳�����pList��Ԫ�ظ���n��Ϊ����ֵ������ѭ�������������
void CreateSeq(pList p, int n){
    for (int i=0; i<n; i++){
        cin >> p->list[i];
    }
}
//����˼·�����ϱȽ����������Ԫ�ز��������������飬��һ������Ϊ��ʱ����δ������������ʣ��Ԫ��ֱ������������
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
//�ڱ�����ɺ󣬽�������Ľṹ��ָ����Ϊ����ֵ�����õ������������ѭ�������ÿ����������е���ʽ��ӡ����
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
