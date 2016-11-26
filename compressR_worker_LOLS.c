//sed96, sp1106

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

char buff[1000];

//LOLS compression algorithm
char * compress(){
	int copies,curIndex, lolIndex = 0; 
	char compare; 
	char lols[sizeof(buff)];
	int i;
	for(i = 0; i < strlen(buff); i++){
		compare = buff[i];
		if(!isalpha(compare)){  //if current char to compare is not a letter, continue
			continue;
		}
		copies=1;
		curIndex = i+1;
		if(compare != buff[curIndex]){		//if the next char in buff doesn't match...
			while(!isalpha(buff[curIndex]) && curIndex<strlen(buff)){	//if it isn't a letter, keep going until a letter or end of buff
				curIndex++;
			}
			if((isalpha(buff[curIndex]) && compare != buff[curIndex])|| curIndex == strlen(buff)){ //if never reach same char, place in lols and continue to next char to compare
				lols[lolIndex] = compare;
				lolIndex++;
				continue;
			}
		}
		while(compare == buff[curIndex] && curIndex<strlen(buff)){ //if there is more than one of the same char in a row, count until pattern ends
			copies++;
			curIndex++;
			while(!isalpha(buff[curIndex]) && curIndex<strlen(buff)){	
				 curIndex++;
			}
		}
		if(copies > 2){		//more than 2 of the same
			if(copies <=9){
				lols[lolIndex]= copies + '0';
			}else if(copies >= 10 && copies < 100){
				char dec[3];
				dec[1]= (copies%10) +'0';
				copies/=10;
				dec[0]= (copies%10) +'0';
				dec[2]='\0';
				lols[lolIndex] = dec[0];
				lolIndex++;
				lols[lolIndex] = dec[1];
			}
			lolIndex++;
			lols[lolIndex]=compare;
			lolIndex++;
		}
		else{		//only 2 of the same
			lols[lolIndex]=compare;
			lols[lolIndex+1]=compare;
			lolIndex+=2;
		}
		i = (curIndex-1); //incriment index
	}
	
	lols[lolIndex]='\0';
	char * lolRet= (char*)malloc(sizeof(lols));
	strcpy(lolRet, lols);
	//printf("lols = %s	\n", lolRet);
	return lolRet;
}

//read file and save portion to encode in buff[]
void readFilePart(FILE * fp, int off, int par){
	char temp[par+1];
	int i;
	fseek(fp,off, SEEK_SET);
	for(i = 0; i < par; i++){
		temp[i] = fgetc(fp);
	}	
	temp[i] = '\0';
	strcpy(buff,temp);
	return;
}

void compressR_worker_LOLS(char ** argv){
	
	//printf("offset =%s , par = %s--	",argv[2],argv[3]);
	FILE * fp = fopen(argv[1],"r");	//open file
	readFilePart(fp,atoi(argv[2]),atoi(argv[3]));
//	printf("%s --> ",buff);
	FILE * nf = fopen(argv[4],"w+");
	if(nf == NULL){		//Error testing, readable uncoded file 
		printf("Cannot create new file.\nExiting Program.\n\n");
		return;
	}
	fprintf(nf,"%s\n", compress());
	//printf("pth of nf == %s", realpath(argv[4],NULL));
	fclose(fp);
	fclose(nf);
	
	return; 
}


int main(int argc, char ** argv){
	
	compressR_worker_LOLS(argv);

	return 0;
}
