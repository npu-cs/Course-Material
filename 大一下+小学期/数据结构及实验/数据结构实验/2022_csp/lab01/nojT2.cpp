#include <iostream>

using namespace std;

typedef struct DNode *pNode;

//����Ҫ�߾��ȼ���PI��ֵ��������е���ѧ֪ʶ����Ҫ�������������õ����ݽṹ���д������������㣬������Ҫ��ľ����ظ����㣬���յõ��߾���ֵ��
//DList˫������������DNode˫��ڵ㣨����data, pNode next, pNode pre�����֣����й�����
struct DNode {
    int data;
    pNode next;
    pNode pre;
};
//��ʼ��˫������Ϊ�գ�Ϊ��ͷ����ռ�
pNode Init(){
    pNode head = new DNode;
    head->next = head->pre = head;
    return head;
}
//����˫����������ѭ��Ϊ�½ڵ����ռ䲢��ʼ�����нڵ�dataΪ0
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
    cin >> n;//��������ľ���n
    pNode num = Init(), sum = Init();
    pNode p, q, s;
    num = CreateDList(num);
    sum = CreateDList(sum);//��ʼ��˫������ָ��num(���ÿһ�μ������R(n)ֵ), sum(�������R(n)֮��)
    num->next->data = 2;
    sum->next->data = 2;
    int a = 0, b = 0;
    for (int i = 1; i < 2000; i++){
        p = num->pre;
        //�ȼ���˷�R��n��*n�����ô����˷���˼·���Ӻ���ǰ�㣬ģ�������λ��ÿ���ڵ���һλ������ret��Ž�λ��ʣ�����
        while (p != num){
            a = p->data * i + b;
            p->data = a % 10;
            b = a / 10;
            p = p->pre;
        }
        b = 0;
        p = p->next;
        //����R��n��*n/(2*n+1)�����ô���������˼·��ģ�����㣬ǰһλ��Ҫ*10��ÿ���ڵ���һλ������ret�������;
        while(p != num){
            a = p->data + b * 10;
            p->data = a / (2 * i + 1);
            b = a % (2 * i + 1);
            p = p->next;
        }
        b = 0;
        p = num->pre;
        q = sum->pre;
        //ʹ�ô����ӷ����Ӻ���ǰ�㣬ģ�������λ������Ӻ�õ������ݴ洢��sum��;
        while (p != num){
            a = p->data + q->data + b;
            q->data = a % 10;
            b = a / 10;
            p = p->pre;
            q = q->pre;
        }
    }
    //�������3.����Ȼ����nλ�ľ��ȣ�ѭ�����sum���ֵ
    cout << "3.";
    s = sum->next->next;
    for (int i = 0; i < n; i++){
        cout << s->data;
        s = s->next;
    }
    return 0;   
}
