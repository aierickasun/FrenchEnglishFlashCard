#include <stdio.h>
#include <string.h>

#define MAXWORDS 10

struct flashcard{ //a struct. it's size is everything added
  char English[16];//english meaning of it.
  char French[16];//french meaning of it. The word size is 16 letters
  char spchPart; //the part of speech of the word.
  int errorFlg; //if the person got it right.
} enFr[MAXWORDS];//makes an array of 10 structs



//put some input and it will be outputted into the file.

void initlze(); //creates a list of English and french words
void testword(char *, char *, char);
main(){
	char ch; 
	char toAsk[8], toAnswer[8], whchWrds;

	initlze();      /*display the menu */
	while(1==1){
		printf("\n\t\t\tLanguage Flashcards \n\n");
		printf("\n\n\t\t1 - English to French, nouns");
		printf("\n\n\t\t5 - French to English, nouns");
		printf("\n\n\t\t0 - Quit");
		printf("\n\n\t\tWhat is your choice > ");
		//gets is dangerous because no test for overflow buffer is done. So you gotta trust the user.
		scanf(" %c",&ch); //interesting use. out of many other functions such as getchar() ; scanf();
		if(ch == '1'){
			strcpy(toAsk, "English");
			strcpy(toAnswer, "French");
		}
		if(ch == '5'){
			strcpy(toAsk, "French");
			strcpy(toAnswer, "English");
		}
		if     (ch == '1' || ch == '5')   whchWrds = 'N';
		else if(ch == '0')                  break;
		else{
			putchar(7);
			continue;
		}
		testword(toAsk, toAnswer, whchWrds);
	}

}

void initlze(){
	int i;
	int k;
	int catcher;
	char holdingthings[25];
	FILE *frencheng;

	frencheng = fopen("frenchandeng.txt", "r");
	for(i = 0; i < MAXWORDS; i++){                //stops adding once second arg is true
		catcher = 0;
		fgets(holdingthings, 25, frencheng); 
		for(k = 0; holdingthings[k] != ' '; k++){
			enFr[i].English[k] = holdingthings[k];
			catcher++;
		}
		k++;
		catcher++;
		for(k; holdingthings[k+1] != '\n'; k++){ //the most ghetto fix ive ever done :DDD HAHHAHA
			enFr[i].French[k - catcher] = holdingthings[k];
		}

		enFr[i].spchPart = holdingthings[k];
		enFr[i].errorFlg = 0;


	}
	fclose(frencheng);
}

void testword(char toAsk[], char toAnswer[], char whchWrds){

	int keep = 1;
	int correct;
	int i, k;

	char answer[16];
	while(keep==1){
		if(toAsk[0] == 'E'){
			printf("\nAsk English \t\tPress 0 to go back to main menu\n");
			for(i = 0; i < MAXWORDS; i++){
				printf("What is %s in English? > ", enFr[i].French);
				scanf(" %s", answer);
                        	if(answer[0] == '0'){
					 break;
				}
				correct = 0;

				printf("\n%s\n", answer);
				if(strcmp(answer,enFr[i].English) == 0) printf("\nCoRRECTO!\n");
				else if(strcmp(answer, enFr[i].English) != 0) printf("\nAww wrong. English: %s is French: %s\n", enFr[i].English, enFr[i].French); 
			}

		}
		else if(toAsk[0] == 'F'){
			 printf("\nAsk French\t\tPress 0 to go back to main menu\n");
			for(i = 0; i < MAXWORDS; i++){
				printf("What is %s in French? > ", enFr[i].English);
				scanf(" %s", answer);
				if(answer[0] == '0'){
					break;
				}
				correct = 0;
	                        printf("\n%s\n", answer);
                                if(strcmp(answer,enFr[i].French) == 0) printf("\nCoRRECTO!\n");
                                else if(strcmp(answer, enFr[i].English) != 0) printf("\nAww wrong. French: %s is English: %s\n",  enFr[i].French, enFr[i].English);
			}
		}
		else break;
		if(answer[0] == '0') break;
	}
}
