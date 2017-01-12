
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <pthread.h>
#include<math.h>
#include <libgen.h>
#include <time.h>
#include <sys/time.h>
#include <ctype.h>
int MAX_FILENAME_SIZE=200;

//struct used to keep track of all of the information related to reading the files
typedef struct {
	char *fname;
	int start;
   	int len;
   	int tcount;
   	int number;
} file_struct;
	char* compressed(char*);
  	int T_compressed(void *args);
   	int charcount( FILE *const  );
  	void *print_message_function( void *ptr );
	char *filename(char *str);
  	char *extname(char *str);
//function that runs the multithreading and opens and reads the files
int compressT_LOLS(char *fname, int n){
    FILE *fp;
  	pthread_t thread[100];
.........
	.........
	.........
	.........
	.........
	
  	for(i=1;i<=n;i++)
  	{
    	file_struct *args = malloc(sizeof *args);
   		if (i==1){
  			args->fname=fname;
  			args->start=0;
  			args->len=x+balance;
  			args->tcount=n;
  			args->number=i;
  			iret[i] = pthread_create( &thread[i], NULL, T_compressed,args);
  		}
  		else
  		{
  			args->fname=fname;
  			args->start=x*(i-1)+balance;
  			args->len=x;
			args->tcount=n;
  			args->number=i;
  			iret[i] = pthread_create( &thread[i], NULL, T_compressed,args);
   		}
  	}
 	int ret;
    for (i = 1; i <= n; i++)
 	{
 		ret=  pthread_join(thread[i], NULL);
 	}
  	return(0);
  }
  
  //function that runs the compression code and opens the file
 int T_compressed(void *instruct)
  {
  	file_struct *file = instruct;
  	FILE *fp;
  	if ((fp = fopen(file->fname,"r")) == NULL){
    	printf("Error! opening file.................");
            // Program exits if the file pointer returns NULL.
        return(1);
  	}
  	
	 
	 .........
		 .........
		 .........
		 .........
		 .........
		 


  free(file);
  }


//function that sets the output file name
 char *filename(char *str) {
     char *result;
     
	 .........
		 .........
		 .........
		 .........
		 
	 
	 return str;
     }
 }
//function that also sets the output file name
 

int main(int argc, char ** argv){
	if(argc != 3){		//Error testing, number of inputs
		printf("Required format: \"./program <file to compress> <number of parts>\"\nExiting Program.\n\n");
		return 0;
	}
	
	int parts = atoi(argv[2]); 
	if(parts < 1){		//Error testing, number of parts is positive integer
		printf("Third paramater must be a positive integer\nExiting Program.\n\n");
		return 0;
	}
	
	compressT_LOLS(argv[1],parts);
	
	return 0;
}
 
