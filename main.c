#include <stdio.h>
#include <stdlib.h>
#define M 100
#define N 5
#define MAX 100
typedef int itemType;
typedef struct {
	itemType data[N];
	int indeks;
} stack;
typedef struct {
	int count;
	int front;
	int rear;
	itemType data[N];
}queue;
void djikstra();
void inisialisasiTQ();
void inisialisasiR();
int ada(int, queue *);
void baca_rute();

int Q[][5]=
    {{M, 1, 3, M, M},
     {M, M, 1, M, 5},
     {3, M, M, 2, M,},
     {M, M, M, M, 1},
     {M, 4, M, M, M},
};
int TQ[N], R[N];

void inisialisasiQueue(queue *);
int empty_q(queue *);
int full_q(queue *);
void enqueue(itemType, queue *);
itemType dequeue(queue *);

void inisialisasiStack(stack *);
int empty_s(stack *);
int full_s(stack *);
void push(itemType, stack *);
void push(itemType, stack *);
itemType pop(stack *);
int asal, tuj;
int main()
{
	int i;

    puts("Graph DJIKSTRA");
    djikstra();
    baca_rute();
	printf("Matriks TQ : ");
	for(i=0; i<N; i++)
		printf("%d ", TQ[i]);
	puts("");
	printf("Matriks R : ");
	for(i=0; i<N; i++)
		printf("%d ", R[i]);
	puts("");
    return 0;
}
void baca_rute(){
    int tuj_asli;
    stack tumpukan;

    inisialisasiStack(&tumpukan);
    tuj_asli = tuj;
    printf("\nRute dari %d ke %d = ", asal+1, tuj+1);
    while(R[tuj] != -1){
        push(R[tuj], &tumpukan);
        tuj = R[tuj];
    }
   // printf("%d - ", asal+1);
    while(!empty_s(&tumpukan)){
        printf("%d - ", pop(&tumpukan)+1);
    }
    printf("%d\n", tuj_asli+1);

	printf("Total beban = %d\n", TQ[tuj_asli]);
}
void djikstra(){
    int i, cn;
    queue antrian;

    printf("Masukkan asal : ");
    scanf("%d", &asal);
    asal--;
    fflush(stdin);
    printf("Masukkan tujuan : ");
    scanf("%d", &tuj);
    tuj--;
    inisialisasiTQ();
    inisialisasiR();
    inisialisasiQueue(&antrian);
    enqueue(asal, &antrian);
    while(!empty_q(&antrian)){
        cn = dequeue(&antrian);
        i=0;
        while(i<N){
            if(Q[cn][i] != M){
                if(Q[cn][i] + TQ[cn] < TQ[i]){
                    TQ[i] = Q[cn][i] + TQ[cn];
                    R[i] = cn;
                //    hsl = ada(i, &antrian);
                    if(i!=asal && i!=tuj && !ada(i, &antrian))
                        enqueue(i, &antrian);
                }

            }
			i++;
        }
    }
}
int ada(itemType x, queue *q){
    int hsl=0, i;

    for(i=0; i<N; i++){
        if(q->data[i] == x)
            hsl=1;
    }
    return hsl;
}
void inisialisasiQueue(queue *q)
{
    q->count = 0;
    q->front = 0;
    q->rear = 0;
}
void inisialisasiStack(stack *s)
{
    s->indeks = 0;
}

int empty_q(queue *q)
{
    if (q->count == 0)
        return 1;
    else
        return 0;
}
int empty_s(stack *s)
{
    if (s->indeks == 0)
        return 1;
    else
        return 0;
}

int penuh(queue *q)
{
    if (q->count == MAX )
        return 1;
    else
        return 0;
}

void enqueue(itemType x, queue *q)
{
    if (penuh(q))
        puts("\nSTOP!!!\nQueue Penuh! Data terakhir gak bs masuk!");
    else
    {
        q->data[q->rear] = x;
        q->rear = (q->rear + 1) % MAX;
        q->count++;
    }
}

itemType dequeue(queue *q)
{
    itemType temp;
    temp = q->data[q->front];
    q->front = (q->front + 1) % MAX;
    q->count--;
    return temp;
}
void push(itemType x, stack *s)
{
    if (penuh(s))
        puts("Stack penuh, data tidak dapat disimpan");
    else
        s->data[s->indeks++] = x;
}

itemType pop(stack *s)
{
    return s->data[--s->indeks];
}
void inisialisasiTQ() {


    for(int i = 0; i < N; i++) {
        if(i == asal)
            TQ[i] = 0;
        else
            TQ[i] = M;
    }
}

void inisialisasiR() {
    for(int i = 0; i < N; i++) {
        R[i] = -1;
    }
}
