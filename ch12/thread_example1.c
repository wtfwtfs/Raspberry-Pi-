#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_THREAD_NUM 100

void* newThread(void *arg){
  pthread_t tid;

  tid=pthread_self();
  printf("thread[%lu] start\n",tid);

  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

  while(1){
    sleep(1);
    printf("thread[%lu] work\n",tid);
  }
}

void main(void)
{
  int result;
  pthread_t thread[MAX_THREAD_NUM];

  int thread_num = 0;
  printf("n: make new thread\nd: delete last created thread\nh: help\n");

  while(1){
    char inputChar;

    scanf("%c", & inputChar);

    switch (inputChar)
    {
      case 'n':
      {
        printf("create thread");
        result = pthread_create(&thread[thread_num], NULL, newThread, NULL);

        if(result){
          printf(" ERORR [%d]/n", result);
			    }
	else{
	  printf(" SUCCESS [%lu]\n", thread[thread_num]);
          thread_num++;
        }
      }
      break;

      case 'd':
      {
	int i;
	if(thread_num){
	  printf("delete thread");
	  result = pthread_cancel(thread[thread_num-1]);
	  if(result){
	    printf(" ERORR [%d]\n", result);
	  }
	  else{
	    printf(" SUCCESS [%lu]\n", thread[i]);
	    thread_num--;
	  }
	}
	else{
	  printf("there is no thread to delete.\n");
	}
      }
      break;

      case'e':
      {
	printf("exit program.\n");
	return;
      }
      break;

      default:
      break;
    }
  }
}
