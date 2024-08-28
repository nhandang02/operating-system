#include<pthread.h>

#include<stdio.h>

#include<stdlib.h>

int min,max; /* this data is shared by the thread(s) */

int a[100];
int size;

void * runner(void * param); /* threads call this function */
// nguyên mẫu các hàm gửi cho thread con
void * trungbinh(void * param);
void * lonnhat(void * param);
void * nhonhat(void * param);
int main(int argc, char * argv[]) {
 
  // thêm data vào struct mang A;
  int i; 
  size = argc - 1;
  for(i=0; i < size; i++) {
    a[i] = atoi(argv[i+1]);
  }
  pthread_t tid[3]; /* the thread identifier */
  pthread_attr_t attr; /* set of thread attributes */
  /* set the default attributes of the thread */
  pthread_attr_init( & attr);
  /* create the thread */
  pthread_create( & tid[0], & attr, trungbinh, NULL);
    pthread_create( & tid[1], & attr, lonnhat, NULL);
    pthread_create( & tid[2], & attr, nhonhat, NULL);
  /* wait for the thread to exit */
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
}
/* The thread will execute in this function */
void * trungbinh(void * param) {
  
  // tìm trung bình
  int i, S=0, j=0;
  double TB;
  for(i=0; i < size; i++) {
    S+=a[i];
    j++;
  }
  TB = S*1.0/ j;
  printf("Gia tri trung binh: %.2f\n", TB);
  pthread_exit(0);
}

/* The thread will execute in this function */
void * lonnhat(void * param) {
  // tìm max
  int i;
  max = a[0];
  for(i=1; i < size; i++) {
    if(a[i]>max)
      max = a[i];
  }
  printf("Gia tri lon nhat: %d\n", max);
  pthread_exit(0);
}

/* The thread will execute in this function */
void * nhonhat(void * param) {
  int i;
  // tìm min
  min = a[0];
  for(i=1; i < size; i++) {
    if(a[i]<min)  
      min = a[i];
  }
  printf("Gia tri nho nhat: %d\n", min);
  pthread_exit(0);
}