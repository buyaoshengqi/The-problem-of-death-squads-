//�����⣬���������⣬Լɪ�򻷣�M���ˣ���ĳһ���˿�ʼ����������5����˳�ȥ�����Ŵ������¸��˿�ʼ��1��ʼ�������ų�Ϊһ����Ҫ����ȥ���ҵ����ĸ��˿�ʼ���ų�����ȥ�� 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
//ѭ��������
typedef struct Node {
	int data;
	struct Node *next ;
} LNode; //����ڵ�����
//����ѭ�������������д洢�����ݼ�Ϊ��� 
LNode *CreatList(int n) { 
	LNode *s, *q, *L;
	int i;
	if (n != 0) {
		L = q = (LNode *)malloc(sizeof(LNode)); 
		q->data = 1; 
		for (i = 2; i <= n; i++) {
			s = (LNode *)malloc(sizeof(LNode)); 
			q->next = s;
			q->next->data = i; 
			q = q->next;
		}
		q->next = L;
	}
	return L;
}
//�����ɾ�� 
int DeleteList (LNode *L) { 
	LNode *a;
	int i;
	while (L->next != L) {
		for (i = 1; i < 4; i++) //����Ҫɾ���ڵ��ǰһ���ڵ㣬i<4 
			L = L->next;
		a = L->next;
		L->next = a->next; 
		free(a);
		L = L->next ;
	}
	printf("\n");
	return (L->data );
}

//ѭ������
#define MAXSIZE 1000//��������� 
typedef struct {
	int data[MAXSIZE];
	int front;
	int rear;
	int count; //����������¼����Ԫ������
} CirQueue;
// ����˳����У��ÿ� 
void InitQueue(CirQueue *Q) {
	Q->front = Q->rear = 0;
	Q->count = 0; 
}
// �ж��п�
int CirQueueEmpty(CirQueue *Q) {
	return Q->front == Q->rear;
}
//�ж�����
int CirQueueFull(CirQueue *Q) {
	return Q->rear == MAXSIZE - 1 + Q->front;
}
//����
void EnQueue(CirQueue *Q, int x) {
	//���,�˳�����
	if (CirQueueFull(Q)) {
		printf("�������"); 
		exit(0);
	}
	Q->data[Q->rear] = x; //�����β
	Q->rear = (Q->rear + 1) % MAXSIZE; //ѭ�������½�βָ�����ƶ�һ��λ�� 
	Q->count ++; 
}
//����
int DeQueue(CirQueue *Q) {
	int temp;
	if (CirQueueEmpty(Q)) {
		printf("����Ϊ��"); //���п�,�˳�����
		exit(0);
	}
	temp = Q->data[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE; //ͷָ�������ƶ�һ��λ�� 
	Q->count--; 
	return temp;
}
int main() {
	int s, i, count = 0,flag=1; 
	LNode *p;
	int z, y; 
	int M;
	int choice;
	while (flag) {
		printf("1.ѭ������\n");
		printf("2.ѭ������\n");
		printf("3.�˳�\n");
		printf("��ѡ��ʹ�õĴ洢�ṹ����1~3��\n\n");
		scanf("%d", &choice);
		if (choice > 3 || choice < 1) {
			printf("��������,����������\n");
			continue;
		}
		switch (choice) {
			case 1:
				    printf("��ѡ�����ѭ������洢�ṹ\n");
					printf("����������ӵ�����:\n");
					scanf("%d", &M);
					if (M < 1) {
						printf("������������������\n");
						continue;
					} else {
						p = CreatList(M);
						y = DeleteList(p); //����Ӹ��ڵ����ʣ�µ�y
						z = M - y + 2; //�����˭����ʣ�¸��ڵ㣬��ʽ1+M-y+1,Լɪ�򻷵ݹ鹫ʽ 
						if (z % M == 0)
							printf("�ӵ�%d�ſ�ʼ���������ų����һ�����¡�\n", z);
						else
							printf("�ӵ�%d�ſ�ʼ���������ų����һ�����¡�\n", (M - y + 2)%M);
					}
					break;
			case 2:
				    printf("��ѡ�����ѭ�����д洢�ṹ\n");
				    int start, count, i,j;
				    CirQueue s;
					printf("����������ӵ����� :\n");
					scanf("%d", &M);
					if (M < 1||M>1000) {
						printf("������������������\n");
						continue;
					}
					for (start = 1; start <= M; start++) { //startΪ���,���ϱ任��� 
						InitQueue(&s);
						for (i = 1; i <= M; i++) {
							EnQueue(&s, i);
						}//�������� 
						for (i = 1; i < start; i++) {
							j = DeQueue(&s);
							EnQueue(&s, j);
						}//����ͷԪ�طŵ���β��ѭ����start�ڶ�ͷ
						count = 1;
						while (count < M) {
							for (i = 1; i < 5; i++) {
								j = DeQueue(&s);
								EnQueue(&s, j);
							}//4���ŵ���β
							j = DeQueue(&s); //ɾ����ͷԪ�� 
							count++;
						}
						if (s.data[s.front] == 1)//�ж��Ƿ�Ϊ�ų� 
							break;
					}
					printf("�ӵ�%d�ſ�ʼ���������ų����һ�����¡�\n", start);
					break;
			case 3:
				exit(0);
		}
	}
}
