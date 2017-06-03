#include <iostream>	//input output
#include <iomanip> 	//setw() function
#include <conio.h> //getch() function
#include <Windows.h>	//getTickCount
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;


//Configurations

//Field size
#define COLS 30 //Number of columns
#define ROWS 20 //Number of rows

//Exit key
const char EXIT='1';

//Keys to move
const char UP='w';
const char DOWN='s';
const char RIGHT='d';
const char LEFT='a';


struct point{	// A point on the matrix
	int x;	//Index of the column
	int y;	//Index of the row
};

struct node{
	point p;
	node* next;
};

void visualize(int field[][COLS]){	//For debugging
	
	for(int i=0;i<ROWS;i++){
		for(int j=0;j<COLS;j++){
			cout<<field[i][j];
		}
		cout<<endl;  
	}	
}

int show(int field[][COLS]){
	
	system("CLS");
	
	for(int i=0;i<COLS*2+2;i++)
		cout<<setw(1)<<(char)254<<setw(1);
	cout<<endl;
	
	for(int i=0;i<ROWS;i++){
		cout<<setw(1)<<"|";
		for(int j=0;j<COLS;j++){
			if(field[i][j]==1){							//Snake node
				cout<<setw(2)<<(char)254<<setw(1);
			}else if(field[i][j]==2){										
					cout<<setw(2)<<"*"<<setw(1);
			}else
				cout<<setw(1)<<"  "<<setw(1);
		}
		cout<<setw(1)<<"|"<<endl;  
	}	
	
	for(int i=0;i<COLS*2+2;i++)
		cout<<setw(1)<<(char)254<<setw(1);
	cout<<endl;
}

void changeDirection(char key,char& direction){
		
	if( key == UP ){					//UP
		direction='U';		
	}else if( key == DOWN ){			//DOWN
		direction='D';
	}else if( key == RIGHT ){			//RIGHT
		direction='R';
	}else if( key == LEFT){				//LEFT
		direction='L';
	}
	
}

int move(int field[][COLS],node* head, char direction){
	
//	cout<<"MOVE";
//	system("PAUSE");
	node* q;
	int prevX,prevY,t;
	
	int oldY=head->p.y,oldX=head->p.x;
	
	field[oldY][oldX]=0;
	
	if(direction=='U' && head->p.y!=0){					//UP
		prevX=head->p.x;
		prevY=head->p.y;
		head->p.y=head->p.y-1;
		q=head;
		while(q->next!=NULL){
			q=q->next;
			field[q->p.y][q->p.x]=0;
			t=q->p.y;
			q->p.y=prevY;
			prevY=t;
			t=q->p.x;		
			q->p.x=prevX;
			prevX=t;
			field[q->p.y][q->p.x]=1;
		}		
	}else if(direction=='D' && head->p.y<(ROWS-1)){		//DOWN
		prevX=head->p.x;
		prevY=head->p.y;
		head->p.y=head->p.y+1;
		q=head;
		while(q->next!=NULL){
			q=q->next;
			field[q->p.y][q->p.x]=0;
			t=q->p.y;
			q->p.y=prevY;
			prevY=t;
			t=q->p.x;		
			q->p.x=prevX;
			prevX=t;
			field[q->p.y][q->p.x]=1;
		}
	}else if(direction=='R' && head->p.x<(COLS-1)){		//RIGHT
		prevX=head->p.x;
		prevY=head->p.y;
		head->p.x=head->p.x+1;
		q=head;
		while(q->next!=NULL){
			q=q->next;
			field[q->p.y][q->p.x]=0;
			t=q->p.y;
			q->p.y=prevY;
			prevY=t;
			t=q->p.x;		
			q->p.x=prevX;
			prevX=t;
			field[q->p.y][q->p.x]=1;
		}
	}else if(direction=='L' && head->p.x!=0){			//LEFT
		prevX=head->p.x;
		prevY=head->p.y;
		head->p.x=head->p.x-1;
		q=head;
		while(q->next!=NULL){
			q=q->next;
			field[q->p.y][q->p.x]=0;
			t=q->p.y;
			q->p.y=prevY;
			prevY=t;
			t=q->p.x;		
			q->p.x=prevX;
			prevX=t;
			field[q->p.y][q->p.x]=1;
		}
	}
	
	if( head->p.y==oldY && head->p.x==oldX){		//GAME OVER!
		return 0;
	}else{										//SUCCESSFULLY MOVED
		field[head->p.y][head->p.x]=1;
		return 1;
	}
	
}

void debugSnake(node* head)
{
	node* q=head;
	while(q->next!=NULL){
		cout<<"X: "<<q->p.x<<" Y: "<<q->p.y<<" NEXT: "<<q->next<<endl;
		
		q=q->next;
	}
}

point newDrop(int field[][COLS]){
	
	point drop;
	int x = rand() % COLS;
	int y = rand() % ROWS;
	drop.x=x;
	drop.y=y;
	field[y][x]=2;
	return drop;
}

int addTale (int field[][COLS], node*&head, int x, int y){
	node* t; 
	node* p;

	t=new node;	
	if(t==NULL){
		cout<<"Memoria esaurita";
		return 1;
	}
	
	t->p.x=x;
	t->p.y=y;
	field[y][x]=1;
	t->next=NULL;
	if(head==NULL){
		head=t;
		return 0;
	}
	p=head;
	while(p->next!=NULL)
		p=p->next;
	p->next=t;
	return 0;
}


int main(int argc, char** argv) {
	
	int field[ROWS][COLS]={0};
	node* head=new node();	//The head of the snake
	char key;	//Key pressed
	char dir;	//Direction of the snake (T Top D Down R Right L Left)
	long startTime, currentTime;
	point drop;
	
	srand (time(NULL));	//Generate random seed 
	
	//Setup
	field[0][1]=1; 		//Snake starts at the top left and heading right
	head->p.x=0;
	head->p.y=0;
	dir='R';	
	drop=newDrop(field);
	head->p.x=4;
	head->p.y=0;	
	addTale(field,head,3,0);
	addTale(field,head,2,0);
	addTale(field,head,1,0);
	addTale(field,head,0,0);
	debugSnake(head);
	system("PAUSE");

	
	show(field);
	startTime=GetTickCount();

	
	while(true){
			
		currentTime=GetTickCount()-startTime;
		
		if ( currentTime >= 500 ){			// half a second
			if( !move(field,head,dir) ){
				cout<<"****** GAME OVER! ******"<<endl;
				break;
			}
			show(field);
			startTime=GetTickCount();
		}
		
		if( _kbhit() ){
			key = _getch();
			
			if (key==EXIT)		//End the game
				break;
				
			changeDirection(key,dir);	
		}
			
		
	}
	
	system("PAUSE");
	return 0;
}
