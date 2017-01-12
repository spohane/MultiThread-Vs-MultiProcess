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
.........
.........
}

//how many chars each child needs to read in from the file
int toRead(int p, int r){
	int ret, tot= charCount-curCount;
.........
.........
.........
	return ret;
}

//gets file name to create children files
char * getFileName(char * file){
	char * ext;
.........
	.........
	.........
	return filenm;	
}


void compressR_LOLS(char * file, int parts){
	
	FILE * fp = fopen(file,"r");	//open file
	if(fp == NULL){		//Error testing, readable uncoded file 
		printf("Cannot open file.\nExiting Program.\n\n");
	
.........	
.........	
.........	
	}
	
	return;
}

int main(int argc, char ** argv){
	.........
		.........
		.........
		.........
		
	compressR_LOLS(argv[1],parts);
	
	return 0;
}
