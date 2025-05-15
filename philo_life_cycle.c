#include "philo.h"

// void* life_cycle(void* arg)
// {
// 	if (the sun is shining)
// 		  return NULL;
// 	  printf("Thread is running.\n");
// 	  return NULL;
// }
  
void init_threads(t_data *data) 
{
    int i;
	i = 0;
	
	pthread_t *thread;
	thread = malloc (sizeof (pthread_t) * data->num_philo);
	
	// Create threads
	while (i++ < data->num_philo)
        pthread_create(&thread[i], NULL, life_cycle, &data);
	// Wait for threads to finish
	i = 0;
	while (i++ < data->num_philo)
	  pthread_join(thread[i], NULL);
	return 0;
}
