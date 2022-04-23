#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
// global variables
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;



void* thread_func(void* arg)
{

  unsigned long thread = (unsigned long) arg;

  // Critical Section
  pthread_mutex_lock(&mutex);

  printf("Thread: %lu\n", thread);

  pthread_mutex_unlock(&mutex);


  return NULL;
}

int main(int argc, char **argv) {
    //declaring dirent struct
    struct dirent *entry;

    // check for correct number of arguments
    if (argc != 2) return -1;
    chdir(argv[1]);

    // set my current directory
    DIR *current = opendir(".");

    // variable for number of root directories
    int root_count = -2;

    // count number of directories
    while( (entry = readdir(current)) ) 
        {
		if (entry->d_type == DT_DIR)
            {
			printf("%s is a directory\n", entry->d_name);
            root_count ++;
		    }
        }
    
    // create an array of pthread_t's for each root directory
    pthread_t tids[root_count];

    for(unsigned long i = 0; i < root_count; i++)
    {
        pthread_create(&tids[i], NULL, thread_func(),)
    }
}

