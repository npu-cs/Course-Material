#include <iostream>

using namespace std;

typedef struct DNode *pNode;

//对于要高精度计算PI的值，结合已有的数学知识，主要核心是依赖采用的数据结构进行大数的四则运算，根据所要求的精度重复计算，最终得到高精度值。
//DList双向链表，依赖于DNode双向节点（包括data, pNode next, pNode pre三部分）进行构建。
struct DNode {
    int data;
    pNode next;
    pNode pre;
};
//初始化双向链表为空，为表头分配空间
pNode Init(){
    pNode head = new DNode;
    head->next = head->pre = head;
    return head;
}
//创建双向链表，采用循环为新节点分配空间并初始化所有节点data为0
pNode CreateDList(pNode head){
    pNode p, q;
    p = new DNode;
    p = head;
    for (int i=0; i<1000; i++){
        q = new DNode;
        q->data = 0;
        q->pre = p;
        p->next = q;
        q->next = head;
        head->pre = q;
        p = p->next;    
    }
    return head;
}

int main(){
    int n;
    cin >> n;//接受输入的精度n
    pNode num = Init(), sum = Init();
    pNode p, q, s;
    num = CreateDList(num);
    sum = CreateDList(sum);//初始化双向链表指针num(存放每一次计算出的R(n)值), sum(存放所有R(n)之和)
    num->next->data = 2;
    sum->next->data = 2;
    int a = 0, b = 0;
    for (int i = 1; i < 2000; i++){
        p = num->pre;
        //先计算乘法R（n）*n，利用大数乘法的思路，从后往前算，模拟手算进位，每个节点存放一位数，用ret存放进位后剩余的数
        while (p != num){
            a = p->data * i + b;
            p->data = a % 10;
            b = a / 10;
            p = p->pre;
        }
        b = 0;
        p = p->next;
        //计算R（n）*n/(2*n+1)，利用大数除法的思路，模拟手算，前一位需要*10，每个节点存放一位数，用ret存放余数;
        while(p != num){
            a = p->data + b * 10;
            p->data = a / (2 * i + 1);
            b = a % (2 * i + 1);
            p = p->next;
        }
        b = 0;
        p = num->pre;
        q = sum->pre;
        //使用大数加法，从后往前算，模拟手算进位，将相加后得到的数据存储到sum中;
        while (p != num){
            a = p->data + q->data + b;
            q->data = a % 10;
            b = a / 10;
            p = p->pre;
            q = q->pre;
        }
    }
    //先输出”3.”，然后按照n位的精度，循环输出sum里的值
    cout << "3.";
    s = sum->next->next;
    for (int i = 0; i < n; i++){
        cout << s->data;
        s = s->next;
    }
    return 0;   
}
