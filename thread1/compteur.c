/*
 * compteur.c
 *
 *  Created on: 12 nov. 2016
 *      Author: walid
 */
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#define Max 100;
int cpt=0;
sem_t mutex;
void* count(void* data)
{
	int i;
    sem_wait(&mutex);
    printf("Le thread %d entre  dans la section critique \n",
    data);
	for (i=0;i<100;i++)
	{
		printf("Thread %d: Counter Value: %d\n", data, cpt);
		cpt++;
		printf("le thread %d a modifié le compteur %d\n",data,cpt);

	}
	printf("Le thread %d sort de la section critique \n",
	data);
	sem_post(&mutex);
	pthread_exit(NULL);

}
int main()
{
	pthread_t t1,t2;
	sem_init(&mutex,0,1);// sémaphore mutex binaire
	pthread_create(&t1, NULL, count, (void*)1); // création du premier thread
	pthread_create(&t2, NULL, count, (void*)2); // création du second thread
	pthread_join(t1, NULL); // attente de terminaison du premier thread
	pthread_join(t2, NULL); // attente de terminaison du second thread
	sem_destroy(&mutex);
	printf("Compteur: %d\n", cpt);


}



