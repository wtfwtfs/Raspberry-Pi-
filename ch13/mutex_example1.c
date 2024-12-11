#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_OF_THREAD 2

int static shareValue;
pthread_mutex_t mutex;

void* addThread(void *arg){
	pthread_t tid = pthread_self();
	
	printf("[START]%s[%lu] shareValue = %d\n", __func__, tid, shareValue);
	
	pthread_mutex_lock(&mutex);
	printf("[MUTEX-IN]%s[%lu] shareValue =%d\n", __func__, tid, shareValue);
	
	for(int i = 0; i < 100000; i++){
		shareValue++;
	}
	
	printf("[MUTEX-OUT]%s[%lu] shareValue = %d\n", __func__, tid, shareValue);
	pthread_mutex_unlock(&mutex);
	
	printf("[END]%s[%lu] shareValue = %d\n", __func__, tid, shareValue);
}

void* minusThread(void *arg){
	pthread_t tid = pthread_self();
	
	printf("[START]%s[%lu] shareValue = %d\n", __func__, tid, shareValue);
	
	pthread_mutex_lock(&mutex);
	printf("[MUTEX-IN]%s[%lu] shareValue = %d\n", __func__, tid, shareValue);
	
	for(int i =0; i < 100000; i++){
		shareValue--;
	}
	
	printf("[MUTEX-OUT]%s[%lu] ShareValue = %d\n", __func__, tid, shareValue);
	pthread_mutex_unlock(&mutex);
	
	printf("[END]%s[%lu] shareValue = %d\n", __func__, tid, shareValue);
}

void main(void)
{
	int result;
	
	pthread_t thread[NUM_OF_THREAD];
	shareValue = 0;
	
	pthread_mutex_init(&mutex,NULL);
	
	result = pthread_create(&thread[0], NULL, addThread, NULL);
	if(result){
		printf(" ERORR [%d]\n", result);
		return;
	}
	
	result = pthread_create(&thread[1], NULL, minusThread, NULL);
	if(result){
		printf(" ERORR [%d]\n", result);
		return;
	}
	
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	
	pthread_mutex_destroy(&mutex);
	
	printf("exit program.\n");
	return;
}
