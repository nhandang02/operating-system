#include<pthread.h>

#include<stdio.h>

#include<stdlib.h>

#include<math.h>

struct partition {
int start;
int end;
};

struct partition A;
struct partition B;

// nguyên mẫu các hàm con
void * songuyento(void * param);

int main(int argc, char * argv[]) {
  // xác định n
  if(argc > 2)
    printf("Qua nhieu tham so");
  else if(atoi(argv[1]) == 0)
    printf("Loi truyen tham so");
  else
  {
    int n = atoi(argv[1]);
    if(n < 2)
      printf("ko co so nguyen to");
    else
    {
      // xác định phân đoạn A
      A.start = 2;
      A.end = n/2;
      // xác định phân đoạn B
      B.start = n/2 + 1;
      B.end = n;

      pthread_t tid[2]; /* the thread identifier */
      pthread_attr_t attr; /* set of thread attributes */
      /* set the default attributes of the thread */
      pthread_attr_init( & attr);
      /* create the thread */
      pthread_create( & tid[0], & attr, songuyento, (void *) &A);
      pthread_create( & tid[1], & attr, songuyento, (void *) &B);
      /* wait for the thread to exit */
      pthread_join(tid[0], NULL);
      pthread_join(tid[1], NULL);
    }
  }
}

/* The thread will execute in this function */
void * songuyento(void * param) {
struct partition * X  = (struct partition *) param;
int start = X->start;
int end = X->end;
int i, j;
 for(i = start; i <= end ; i++) //do something
 {
   int count = 0;
   for(j = 2; j < i; j++)
   {
     if(i % j == 0)
       count++;
   }
   //nếu i là số nguyên tố thì in ra màn hình
   if(count == 0)
     fprintf(stderr,"%d\t", i);
 }
  pthread_exit(0);
}