//sp1106, sed96
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
  	if ((fp = fopen(fname,"r")) == NULL){
    	printf("Error! opening file");
            // Program exits if the file pointer returns NULL.
   	return(1);
  	}
  	fseek(fp, 0L, SEEK_END);
  	double size = ftell(fp);
  	fclose(fp);
	//size=size-1;
  	if(size<n)
  	{printf(" Error! Size of file is less than number of parts...");
  	return(1);
	}
  	double segment=size/n;
  	int iret[200], x=segment-((int)segment%1);
  	int balance=((int)size % x);
  	int i;
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
  	fseek(fp, 0L, SEEK_SET); //Reset
  	fseek(fp, file->start, SEEK_SET);
  	char *str=malloc(file->len+1);
  	unsigned long long int i=0,m=0;
  	char c;
  	char *copy, *input ;
  	for( i=0;i<file->len;i++ ){
        c = fgetc( fp );
        if( c == EOF || c == '\n' || !isalpha(c)){
            continue;
        }
		str[m++]=c;
  	}
  	fclose(fp);
  	str[m]='\0';
 	for (copy = str, input = str; *copy; copy++) {
   		unsigned long long int count = 1;
        if(copy[0]!=copy[1] )
        {
        	input[0] = copy[0]; input++;
        }
        else if ( copy[1]!= copy[2])
        {
            input[0] = copy[0]; input++;
        }
        else
        {
            while (copy[0] == copy[1]) {
                count++;
                copy++;
            }
    		if (count>9)
    		{
    			char buff[50];
    			sprintf(buff, "%llu", count);
    			for(i = 0; buff[i] != '\0'; ++i)
        		{
            		input[0] = buff[i];input++;
        		}
    		}
    		else
     		{      input[0]='0'+count; input++;
     		}
      		input[0]=copy[0]; input++;
        }
    }
    input[0] = 0;

 char* ts1 = strdup(file->fname);
 char* ts2 = strdup(file->fname);
 char* dir = dirname(ts1);
 char *fname=basename(ts2);
 char* fname2 = filename(fname);
 char* extname2 = extname(fname);
 char outfile[100];
 sprintf(outfile,"%s/%s_%s_LOLS",dir,fname2,extname2);
 FILE *fp2;
  if (file->tcount==1)
{
 fp2=fopen(outfile,"w");
 if(fp2 == NULL)
    {
       printf("\nError opening file %s for writing or file already..exists!!",outfile);
       exit(1);
    }
    fprintf(fp2,"%s",str);
  fclose(fp2);
}
else
 {
 int inum= file->number;
 sprintf(outfile,"%s/%s_%s_LOLS%d",dir,fname2,extname2,inum-1);


fp2=fopen(outfile,"w");
 if(fp2 == NULL)
    {
       printf("\nError opening file %s for writing or file already exists!!",outfile);
       exit(1);
    }
    fprintf(fp2,"%s",str);
  fclose(fp2);
}


  free(file);
  }


//function that sets the output file name
 char *filename(char *str) {
     char *result;
     char *last;
     if ((last = strrchr(str, '.')) != NULL ) {
         if ((*last == '.') && (last == str))
             return str;
         else {
             result = (char*) malloc(MAX_FILENAME_SIZE);
             snprintf(result, sizeof result, "%.*s", (int)(last - str), str);
             return result;
         }
     } else {
         return str;
     }
 }
//function that also sets the output file name
 char *extname(char *str) {
     char *result;
     char *last;
     if ((last = strrchr(str, '.')) != NULL) {
         if ((*last == '.') && (last == str))
             return "";
         else {
             result = (char*) malloc(MAX_FILENAME_SIZE);
             snprintf(result, sizeof result, "%s", last + 1);
             return result;
         }
     } else {
         return ""; // Empty/NULL string
     }
 }
 

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
 
