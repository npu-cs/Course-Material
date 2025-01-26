#include <iostream>
using namespace std;
const int MAXSIZE = 1000;

typedef struct triple {
    int r, c, e;
} triple;

typedef struct matrix {
    int m, n, t;
    triple data[MAXSIZE];
} matrix;

void initMatrix(matrix* M) {
    cin >> M->m >> M->n;
    M->t = 0;
    while (true) {
        triple p;
        cin >> p.r >> p.c >> p.e;
        if (!p.c)
            break;
        M->t++;
        M->data[M->t] = p;
    }
}

void multiplyMatrix(matrix A, matrix B, matrix* C) {
    int temp = 0;
    for (int i = 1; i <= A.m; i++) {
        for (int j = 1; j <= B.n; j++) {
            for (int p = 1; p <= A.t; p++) {
                for (int q = 1; q <= B.t; q++)
                    if (A.data[p].r == i && B.data[q].c == j && A.data[p].c == B.data[q].r) {
                        temp += A.data[p].e * B.data[q].e;
                    }
            }

            if (!temp)
                continue;
            else {
                C->t++;
                C->data[C->t].r = i;
                C->data[C->t].c = j;
                C->data[C->t].e = temp;
                temp = 0;
            }
        }
    }
}

void printMatrix(matrix M) {
    for (int i = 1; i <= M.t; i++) {
        cout << M.data[i].r << " " << M.data[i].c << " " << M.data[i].e << endl;
    }
}

int main() {
    matrix A, B, C;
    initMatrix(&A);
    initMatrix(&B);
    C.m = A.m;
    C.n = B.n;
    multiplyMatrix(A, B, &C);
    printMatrix(C);
    return 0;
}
