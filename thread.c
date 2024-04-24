#include <pthread.h>
#include <stdio.h>
#include <stdint.h>

void *thr(void *arg) {
  printf("%d\n", *((uint8_t *)arg));
}

int main(int argc, char **argv) {
  pthread_t thr1;
  pthread_t thr2;

  int a = 1;
  int b = 2;
  int rc;

  if(rc = pthread_create(&thr1, NULL, thr, &a)) {
    printf("err %d\n", rc);
  }

  if(rc = pthread_create(&thr2, NULL, thr, &b)) {
    printf("err %d\n", rc);
  }

  pthread_join(thr1, NULL);
  pthread_join(thr2, NULL);
}
