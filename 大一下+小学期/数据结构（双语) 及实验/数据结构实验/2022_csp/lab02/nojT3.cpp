#include <iostream>
using namespace std;
const int max_size = 1000;

typedef struct{
    int row, col, e;
}Triple;

typedef struct{
    Triple data[max_size + 1];
    int m, n, len;
}TSMatrix;

void InitSMatrix(TSMatrix *M, int m, int n, int len){
    M->m = m;
    M->n = n;
    M->len = len;
}

void CreateSMatrix(TSMatrix *M){
    cin>>M->m>>M->n;
    M->len = 0;
    int i, j, e;
    while(1){
        cin>>i;
        getchar();
        cin>>j;
        getchar();
        cin>>e;
        if(i == 0 && j == 0 && e == 0) break;
        M->len++;
        M->data[M->len].row = i;
        M->data[M->len].col = j;
        M->data[M->len].e = e;       
    }
}

void FastTranspseTSMatrix(TSMatrix M, TSMatrix *T){
    int num[max_size], cpot[max_size];
    int col, i, j, p;
    if(T->len){
        for(i = 1; i <= M.n; i++) num[i] = 0;
        for(i = 1; i <= M.len; i++) num[M.data[i].col]++;
        cpot[1] = 1;
        for(i = 2; i <= M.n; i++) cpot[i] = cpot[i - 1] + num[i - 1];
        for(i = 1; i <= M.len; i++){
            col = M.data[i].col;
            j = cpot[col];
            T->data[j].row = M.data[i].col;
            T->data[j].col = M.data[i].row;
            T->data[j].e = M.data[i].e;
            cpot[col]++;
        }
    }
}

void PrintSMatrix(TSMatrix M){
    for(int i = 1; i <= M.len; i++){
        cout<<M.data[i].row<<" "<<M.data[i].col<<" "<<M.data[i].e<<endl;
    }
}

int main(){
    TSMatrix M, T;    
    CreateSMatrix(&M);
    InitSMatrix(&T, M.n, M.m, M.len);
    FastTranspseTSMatrix(M, &T);
    PrintSMatrix(T);
    return 0;
}