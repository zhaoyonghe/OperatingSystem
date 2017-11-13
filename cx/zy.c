#include<stdio.h>
#include<pthread.h>
#define PMAX 16
#define CMAX 25
#define BUFFERSIZE 10
pthread_mutex_t the_mutex;
pthread_cond_t condc,condp;
int buffer=2;
//c++多線程實現生產者
void*producer(void*ptr){
	int i;
	for(i=1;i<=PMAX;i++){
		pthread_mutex_lock(&the_mutex);
		while(buffer==BUFFERSIZE){
			printf("producerwaiting...");
			pthread_cond_wait(&condp,&the_mutex);
		}	
		buffer=buffer+1;
		printf("producer %d\n",buffer);
		pthread_cond_broadcast(&condc);
		pthread_mutex_unlock(&the_mutex);	
	}
	pthread_exit(0);
}

void*consumer(void*ptr){
	int i;
	for(i=1;i<=CMAX;i++){
		pthread_mutex_lock(&the_mutex);
		while(buffer==0){
			printf("consumerwaiting...");
			pthread_cond_wait(&condc,&the_mutex);
		}	
		buffer=buffer-1;
		printf("consumer %d\n",buffer);
		pthread_cond_broadcast(&condp);
		pthread_mutex_unlock(&the_mutex);	
	}
	pthread_exit(0);
}

int main(int argc,char **argv){
	pthread_t pro1,pro2,pro3,con1,con2;
	pthread_mutex_init(&the_mutex,0);
	pthread_cond_init(&condc,0);
	pthread_cond_init(&condp,0);
	pthread_create(&con1,0,consumer,0);
	pthread_create(&con2,0,consumer,0);
	pthread_create(&pro1,0,producer,0);
	pthread_create(&pro2,0,producer,0);
	pthread_create(&pro3,0,producer,0);
	pthread_join(pro3,0);
	pthread_join(pro2,0);
	pthread_join(pro1,0);
	pthread_join(con2,0);
	pthread_join(con1,0);
	pthread_cond_destroy(&condc);
	pthread_cond_destroy(&condp);
	pthread_mutex_destroy(&the_mutex);
	printf("all finish");

}
