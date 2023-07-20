#include<iostream>
using namespace std;

typedef struct OLNode{
    int i,j;
    int val;
    struct OLNode *right,*down;
}OLNode,*OLink;

typedef struct{
    OLink *rhead,*chead;
    int mu,nu,tu;
}CrossList;

void CreatMatrix(CrossList *M, int m, int n, int t){
    M->rhead = M->chead = NULL;
    M->mu = m;
    M->nu = n;
    M->tu = t;
    M->rhead = new OLink[m+1];
    M->chead = new OLink[n+1];
    for(int k=1;k<=m;k++){
        M->rhead[k] = NULL;
    }
    for(int k=1;k<=n;k++){
        M->chead[k] = NULL;
    }
    int i,j,v;
    for(int k=0;k<t;k++){
        int i,j,v;
        OLink p,q;
        cin >> i >> j >> v;
        p = new OLNode;
        p->i = i;
        p->j = j;
        p->val = v;
        if(M->rhead[i]==NULL || M->rhead[i]->j>j){
            M->rhead[i] = p;
        }
        else{
            for(q=M->rhead[i];(q->right)&&(q->right->j<j);q=q->right);
            p->right = q->right;
            q->right = p;
        }
        p->down = NULL;
        if(M->chead[j]==NULL || M->chead[j]->i>i){
            M->chead[j] = p;
        }
        else{
            for(q=M->chead[j];(q->down)&&(q->down->i<i);q=q->down);
            p->down = q->down;
            q->down = p;
        }
        p->right = NULL;
    }
}

void Insert(CrossList *M, OLink p){
    int i=p->i,j=p->j;
    if(M->rhead[i]==NULL){
        M->rhead[i] = p;
        M->tu++;
    }
    else{
        OLink q=M->rhead[i];
        OLink pre = q;
        while(q&&(q->j<p->j)){
            pre = q;
            q = q->right;
        }
        if(q&&(q->j==p->j)){
            q->val += p->val;
            if(q->val==0){
                if(pre==q){
                    M->rhead[i] = q->right;
                }
                else{
                    pre->right = q->right;
                }
                M->tu--;
            }
        }
        else{
            if(pre==q){
                    M->rhead[i] = p;
                    p->right = q;
                }
                else{
                    pre->right = p;
                    p->right =q;
                }
                M->tu++;
        }
    }
    if(M->chead[j]==NULL){
        M->chead[j] = p;
    }
    else{
        OLink q=M->chead[j];
        OLink pre = q;
        while(q&&(q->i<p->i)){
            pre = q;
            q = q->down;
        }
    }
}

void AddElem(CrossList *M, CrossList *N){
   OLink p,q;
   p = new OLNode;
   for(int k=1;k<=N->mu;k++){
        p = N->rhead[k];
        while(p){
            q = new OLNode;
            q->down = p->down;
            q->right = q->right;
            q->val = p->val;
            q->i = p->i;
            q->j = p->j;
            Insert(M,q);
            p = p->right;
        }
    }
}

void PrintMatrix_OL(CrossList *M){
    for(int i=1;i<=M->mu;i++){
        OLink p=M->rhead[i];
        for(int j=1;j<=M->nu;j++){
            if(p&&j==p->j){
                cout << p->i << " " << p->j << " " << p->val << endl;
                p=p->right;
            }
        }
    }
}

int main(){
    int m,n,t1,t2;
    cin >> m >> n >> t1 >> t2;
    CrossList *M,*N;
    M = new CrossList;
    N = new CrossList;
    CreatMatrix(M,m,n,t1);
    CreatMatrix(N,m,n,t2);
    AddElem(M,N);
    PrintMatrix_OL(M);
    return 0;
}

