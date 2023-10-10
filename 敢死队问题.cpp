//第三题，敢死队问题，约瑟夫环，M个人，从某一个人开始报数，报到5这个人出去，接着从他的下个人开始从1开始报数，排长为一号需要最后出去，找到从哪个人开始让排长最后出去。 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
//循环单链表
typedef struct Node {
	int data;
	struct Node *next ;
} LNode; //定义节点类型
//创建循环单链表，链表中存储的数据即为序号 
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
//链表的删除 
int DeleteList (LNode *L) { 
	LNode *a;
	int i;
	while (L->next != L) {
		for (i = 1; i < 4; i++) //查找要删除节点的前一个节点，i<4 
			L = L->next;
		a = L->next;
		L->next = a->next; 
		free(a);
		L = L->next ;
	}
	printf("\n");
	return (L->data );
}

//循环队列
#define MAXSIZE 1000//队列最长长度 
typedef struct {
	int data[MAXSIZE];
	int front;
	int rear;
	int count; //计数器，记录队中元素总数
} CirQueue;
// 创建顺序队列，置空 
void InitQueue(CirQueue *Q) {
	Q->front = Q->rear = 0;
	Q->count = 0; 
}
// 判队列空
int CirQueueEmpty(CirQueue *Q) {
	return Q->front == Q->rear;
}
//判队列满
int CirQueueFull(CirQueue *Q) {
	return Q->rear == MAXSIZE - 1 + Q->front;
}
//进队
void EnQueue(CirQueue *Q, int x) {
	//溢出,退出运行
	if (CirQueueFull(Q)) {
		printf("队列溢出"); 
		exit(0);
	}
	Q->data[Q->rear] = x; //插入队尾
	Q->rear = (Q->rear + 1) % MAXSIZE; //循环意义下将尾指向下移动一个位置 
	Q->count ++; 
}
//出队
int DeQueue(CirQueue *Q) {
	int temp;
	if (CirQueueEmpty(Q)) {
		printf("队列为空"); //队列空,退出运行
		exit(0);
	}
	temp = Q->data[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE; //头指针向下移动一个位置 
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
		printf("1.循环链表\n");
		printf("2.循环队列\n");
		printf("3.退出\n");
		printf("请选择使用的存储结构：（1~3）\n\n");
		scanf("%d", &choice);
		if (choice > 3 || choice < 1) {
			printf("输入有误,请重新输入\n");
			continue;
		}
		switch (choice) {
			case 1:
				    printf("您选择的是循环链表存储结构\n");
					printf("请输入敢死队的人数:\n");
					scanf("%d", &M);
					if (M < 1) {
						printf("输入有误请重新输入\n");
						continue;
					} else {
						p = CreatList(M);
						y = DeleteList(p); //计算从根节点出发剩下的y
						z = M - y + 2; //计算从谁出发剩下根节点，公式1+M-y+1,约瑟夫环递归公式 
						if (z % M == 0)
							printf("从第%d号开始计数能让排长最后一个留下。\n", z);
						else
							printf("从第%d号开始计数能让排长最后一个留下。\n", (M - y + 2)%M);
					}
					break;
			case 2:
				    printf("您选择的是循环队列存储结构\n");
				    int start, count, i,j;
				    CirQueue s;
					printf("请输入敢死队的人数 :\n");
					scanf("%d", &M);
					if (M < 1||M>1000) {
						printf("输入有误，请重新输入\n");
						continue;
					}
					for (start = 1; start <= M; start++) { //start为起点,不断变换起点 
						InitQueue(&s);
						for (i = 1; i <= M; i++) {
							EnQueue(&s, i);
						}//以序号入队 
						for (i = 1; i < start; i++) {
							j = DeQueue(&s);
							EnQueue(&s, j);
						}//将队头元素放到队尾，循环后start在队头
						count = 1;
						while (count < M) {
							for (i = 1; i < 5; i++) {
								j = DeQueue(&s);
								EnQueue(&s, j);
							}//4个放到队尾
							j = DeQueue(&s); //删除队头元素 
							count++;
						}
						if (s.data[s.front] == 1)//判断是否为排长 
							break;
					}
					printf("从第%d号开始计数能让排长最后一个留下。\n", start);
					break;
			case 3:
				exit(0);
		}
	}
}
