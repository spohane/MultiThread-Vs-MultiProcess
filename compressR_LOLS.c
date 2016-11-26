//sed96, sp1106

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/time.h>

static int charCount;
static int curCount;

//counts how many total chars in the file (no work, just glancing)
void cCount(FILE * fp){
	fseek(fp,0,SEEK_END);
	charCount = ftell(fp);
	rewind(fp);
}

//how many chars each child needs to read in from the file
int toRead(int p, int r){
	int ret, tot= charCount-curCount;
	if(tot%(p-r)==0){
		ret = tot/(p-r);
	}else{
		ret = (1+((tot-1)/(p-r)));
	}
	return ret;
}

//gets file name to create children files
char * getFileName(char * file){
	char * ext;
	char * filenm = (char*)malloc(sizeof(strlen(file))+1);
	if((filenm = (char*)malloc(sizeof(strlen(file))+1)) == NULL){
		return NULL;
	}
	strcpy(filenm,file);
	ext = strchr(filenm,'.');
	if(ext!=NULL){
		*ext = '\0';
	}
	return filenm;	
}


void compressR_LOLS(char * file, int parts){
	
	FILE * fp = fopen(file,"r");	//open file
	if(fp == NULL){		//Error testing, readable uncoded file 
		printf("Cannot open file.\nExiting Program.\n\n");
		return;
	}
	char * filename = getFileName(file);
	
	if(parts < 1){		//Error testing, number of parts is positive integer
		printf("Third paramater must be a positive integer\nExiting Program.\n\n");
		return;
	}
	
	
	cCount(fp);	//read file to get size
	//printf("charCount = %d\n",charCount);
	if(parts > charCount){//Error testing, too many splits
		printf("Cannot split into more parts than there are characters in the given file\nExiting Program.\n\n");
		return;
	}
	
	int status, i, k = 0;
	curCount=0;
	for(i = 0; i < parts; i++){
		curCount +=k;
		char redirect[100]; 
		
		if(parts==1)
		{
		sprintf(redirect, "%s_txt_LOLS", filename);
		}
		else{
		sprintf(redirect, "%s_txt_LOLS%d",filename ,i);}
		pid_t id = fork();  //fork children processes here
		waitpid(id, &status, 0);
		k = toRead(parts,i);
		
		if (id == -1) exit(1); // fork failed 
		if (id > 0){	//is parent
			continue;
		 }else{
			char off[10];	//get starting offset
			sprintf(off, "%d",curCount);
			char par[10];	//get # of chars to read
			sprintf(par,"%d",k);
			char * cmd = "./worker";
			char *args[]= {cmd,file,off, par, redirect, NULL};  //arguments to pass when exec()ing
			execvp(cmd, args);
		}	
	}
	
	return;
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
	
	compressR_LOLS(argv[1],parts);
	
	return 0;
}
