#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include <time.h> // dung lam random
#include<windows.h>	//chi su dung de lam dep. neu khong co no thuat toan van chay.
void gotoxy(int x,int y)//x,y l? t?a di?m x,y tr?n m?n h?nh
{  
    //C?c h?m n?y l? h?m thao t?c API v?i windows b?n c? coppy th?i kh?ng c?n ph?i hi?u qu? s?u.
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD a = {x, y};
    SetConsoleCursorPosition(h, a);
}

void displayAll(char **bg, int y, int x){
	int i,j;
	for(i=0;i<y;i++){
		for(j=0;j<x;j++){
			printf("%c", bg[i][j]);
		}
		printf("\n");
	}
}

struct snakeToken{
	int y;
	int x;
};
typedef struct snakeToken Token;

void addToken(char **bg, Token *arr, int *length){
	(*length) ++; //tang do dai cho ran
	arr = (Token*)realloc(arr, *length*sizeof(Token)); //tang them phan tu cho mang snakeArr
		if(arr[*length-3].y - arr[*length-2].y == -1){ // huong -Oy
		arr[*length-1].x = arr[*length-2].x;
		arr[*length-1].y = arr[*length-2].y+1;
	}else if(arr[*length-3].y - arr[*length-2].y == 1){ //huong Oy
		arr[*length-1].x = arr[*length-2].x;
		arr[*length-1].y = arr[*length-2].y-1;
	}else if(arr[*length-3].x - arr[*length-2].x == 1){ //huong Ox
		arr[*length-1].x = arr[*length-2].x-1;
		arr[*length-1].y = arr[*length-2].y;
	}else if(arr[*length-3].x - arr[*length-2].x == -1){ //huong -Ox
		arr[*length-1].x = arr[*length-2].x+1;
		arr[*length-1].y = arr[*length-2].y;
	}
	
}
void drawSnake(char **bg, Token *arr, int snakeLength, int y ,int x){
	int i,j,k;
	for(i=1;i<y-1;i++){
		for(j=1;j<x-1;j++){
			bg[i][j] = ' ';
		}
	}
	for(i=1;i<y-1;i++){
		for(j=1;j<x-1;j++){
			for(k=0;k<snakeLength;k++){
			if(i == arr[k].y && j == arr[k].x){
					if(k == 0){
						bg[i][j] = '0';
					}else{
						bg[i][j] = 'o';
					}
				}
			}
		}
	}
	bg[arr[0].y][arr[0].x] = '0';

}
void autoMove(char **bg, Token *arr, int length){
	int i;
	bg[arr[length-1].y][arr[length-1].x] = ' '; //xoa rong phan tu vua bi dich chuyen 
	
	
	if(arr[0].y - arr[1].y == -1){ // huong -Oy
		for(i=length-1;i>=1;i--){
			arr[i].x = arr[i-1].x;
			arr[i].y = arr[i-1].y;
		}
		arr[0].y --;
	}else if(arr[0].y - arr[1].y == 1){ //huong Oy
		for(i=length-1;i>=1;i--){
			arr[i].x = arr[i-1].x;
			arr[i].y = arr[i-1].y;
		}
		arr[0].y ++;
	}else if(arr[0].x - arr[1].x == 1){ //huong Ox
		for(i=length-1;i>=1;i--){
			arr[i].x = arr[i-1].x;
			arr[i].y = arr[i-1].y;
		}
		arr[0].x ++;		
	}else if(arr[0].x - arr[1].x == -1){ //huong -Ox
		for(i=length-1;i>=1;i--){
			arr[i].x = arr[i-1].x;
			arr[i].y = arr[i-1].y;
		}
		arr[0].x --;
	}
	
}
void controlSnake(char **bg, Token *arr, int length){
	char ctrl;
	int i;
	fflush(stdin);
	if (kbhit()) {		
		ctrl = getch();
		if(ctrl == 'a'){ // turn left
			if(arr[0].x - arr[1].x != 1 && arr[0].x - arr[1].x != -1){
				bg[arr[length-1].y][arr[length-1].x] = ' '; //xoa rong phan tu vua bi dich chuyen 
				for(i=length;i>=1;i--){
					arr[i].y = arr[i-1].y;
				}
				arr[0].x --;			
			}else{
				autoMove(bg, arr, length);	
			}	
		}else if(ctrl == 'd'){ //turn right
			if(arr[0].x - arr[1].x != 1 && arr[0].x - arr[1].x != -1){
				bg[arr[length-1].y][arr[length-1].x] = ' '; //xoa rong phan tu vua bi dich chuyen 
				for(i=length;i>=1;i--){
					arr[i].y = arr[i-1].y;
				}
				arr[0].x ++;			
			}else{
				autoMove(bg, arr, length);	
			}	
		}else if(ctrl == 'w'){ //move up
			if(arr[0].y - arr[1].y != 1 && arr[0].y - arr[1].y != -1){
				bg[arr[length-1].y][arr[length-1].x] = ' '; //xoa rong phan tu vua bi dich chuyen 
				for(i=length;i>=1;i--){
					arr[i].x = arr[i-1].x;
				}
				arr[0].y --;
			}else{
				autoMove(bg, arr, length);	
			}
		}else if(ctrl == 's'){ //move down
			if(arr[0].y - arr[1].y != 1 && arr[0].y - arr[1].y != -1){
				bg[arr[length-1].y][arr[length-1].x] = ' '; //xoa rong phan tu vua bi dich chuyen 
				for(i=length;i>=1;i--){
					arr[i].x = arr[i-1].x;
				}
				arr[0].y ++;
			}else{
				autoMove(bg, arr, length);	
			}
		}else{
			autoMove(bg, arr, length);	
		}	
	}else{
		autoMove(bg, arr, length);	
	}		
	
}
void createApple(char **bg, int *isEaten, int *xApple, int *yApple){
	if(*isEaten == 1){
		*xApple = rand() % 58 + 1;
		*yApple = rand() % 28 + 1;		
	}
	bg[*yApple][*xApple] = '$';
	*isEaten = 0;
}
int eatenApple(char **bg, Token *arr, int *isEaten, int xApple, int yApple){
	int i;
	if(arr[0].x == xApple && arr[0].y == yApple){
		*isEaten = 1;
		return 1;
	}
	return 0;
}

void checkGameOver(char **bg, Token *arr, int y, int x, int length, int *gameOver){
	if(arr[0].x == 0 || arr[0].x == x-1 || arr[0].y == 0 || arr[0].y == y-1 ){
		*gameOver = 1;
	}
	int i;
	for(i=1;i<length;i++){
		if(arr[0].x == arr[i].x && arr[0].y == arr[i].y){
			*gameOver = 1;
		}
	}
}

void printGameStart(){
	gotoxy(0,0);
	/*
	    ///\\\    ||\\  ||       /\        ||  //   ||||||\      
	    ||        || \\ ||      //\\       || //    ||     
	    \\==\\    ||  \\||     //  \\      ||//     ||===     
	         ||   ||   \\|    //====\\     || \\    ||      
	    \\\///    ||    \|   //      \\    ||  \\   ||||||/      
	*/
	printf("    ///\\\\\\    ||\\\\  ||       /\\       ||  //   ||||||\\\n");
	printf("    ||        || \\\\ ||      //\\\\      || //    ||     \n");
	printf("    \\\\==\\\\    ||  \\\\||     //  \\\\     ||//     ||===  \n");
	printf("        ||    ||   \\||    //====\\\\    || \\\\    ||       \n");
	printf("    \\\\\\///    ||    \\|   //      \\\\   ||  \\\\   ||||||/  \n");
}

void printGameOver(){
	/*
		////\\\      //\\       |\\    //|    |||||||\      //||||\\    \\      //   |||||||\   ||||||\                   
	   ||           //  \\      ||\\  //||    ||            ||     ||    \\    //    ||         ||   ||                    
	   ||   |||    //    \\     || \\// ||    ||====        ||     ||     \\  //     ||====     ||||||/              
	   ||    ||   //======\\    ||      ||    ||            ||     ||      \\//      ||         ||   \\         
	    \\\\///  //        \\   ||      ||    |||||||/      \\||||//        \/       |||||||/   ||    \\                        
	*/
	printf(" //\\\\\\     //\\\\     |\\\\    //|  |||||\\    //||\\\\  \\\\      // |||||\\  ||||||\\  \n");
	printf("||        //  \\\\    ||\\\\  //||  ||        ||   ||  \\\\    //  ||      ||   ||   \n");
	printf("|| |||   //    \\\\   || \\\\// ||  ||==      ||   ||   \\\\  //   ||==    ||||||/ \n");
	printf("||  ||  //======\\\\  ||      ||  ||        ||   ||    \\\\//    ||      ||   \\\\\n");
	printf(" \\\\/// //        \\\\ ||      ||  |||||/    \\\\||//      \\/     |||||/  ||    \\\\ \n");
	
}

int main(){
	
	srand(time(NULL)); //khoi tao thoi gian
	char gameContinue;
	
	do{
		system("cls");
		printGameStart();
		printf("\n Press any key to start game...");
		fflush(stdin);
		gameContinue = getch();
		//do kho
		gotoxy(10,10);
		int difficultyButton, difficulty;
		printf("choose your mode: \n");
		gotoxy(10,11);
		printf("1. easy");
		gotoxy(10,12);
		printf("2. medium");
		gotoxy(10,13);
		printf("3. hard");
		fflush(stdin);
		difficultyButton = getch();
		switch(difficultyButton){
			case 50:
				difficulty = 10;
				break;
			case 51:
				difficulty = 0;
				break;
			case 49:
			default:
				difficulty = 50;
		}
		
		
		gotoxy(0,0);
		// start game
		
		//khai bao cac bien dem
		int i,j,k;
		int gameOver = 0;
		int isEaten = 1;
		int xApple, yApple;
		int score = 0;
		
		//khai bao background
		int y = 30;
		int x = 60;
		char **background;
		//cap phat bo nho cho con tro 2 chieu (o day se tuong tu nhu new int trong cpp)
		background = (char **)malloc(y*sizeof(char*));
		
		for(i=0;i<y;i++){
			background[i] = (char*)malloc(x*sizeof(char));
			for(j=0;j<x;j++){
				if(i == 0 || i == y-1 || j == 0 || j == x-1){
					background[i][j] = '=';
				}else{
					background[i][j] = ' ';
				}
			}
		}
		displayAll(background, y, x);
		//khai bao va cap phat bo nho cho snake
	                 
		int lengthOfSnake = 2;
		Token* snakeArr = (Token*)malloc(lengthOfSnake*sizeof(Token));
		//thiet lap snake goc
		snakeArr[0].x = 30;
		snakeArr[0].y = 20;
		snakeArr[1].x = 30;
		snakeArr[1].y = 21;
		
		//vong lap chinh
		while(gameOver == 0){
			Sleep(difficulty);
			eatenApple(background, snakeArr, &isEaten, xApple, yApple);		
			if(eatenApple(background, snakeArr, &isEaten, xApple, yApple) == 1){
				addToken(background, snakeArr, &lengthOfSnake);
				score++;
			}
			drawSnake(background, snakeArr, lengthOfSnake, y, x);
			createApple(background, &isEaten, &xApple, &yApple);	
				
			checkGameOver(background, snakeArr, y, x, lengthOfSnake, &gameOver);
			controlSnake(background, snakeArr, lengthOfSnake);
			gotoxy(0,0);
			displayAll(background, y, x);
			
			printf("\nSCORE: %d\n", score);	
		}
			
		printGameOver();
		//giai phong du lieu bo nho cho snake
		free(snakeArr);
		//giai phong du lieu bo nho cho background
		for(i=0;i<y;i++){
			free(background[i]);
		}
		free(background);
		getch();
		
		// menu moi
		system("cls");
		printf("\n Press any key to start game or ESC to exit game...");
		fflush(stdin);
		gameContinue = getch();
	}while(gameContinue != 27);

	return 0;
}


