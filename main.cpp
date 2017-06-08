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
#define COLS 10//Number of columns
#define ROWS 10 //Number of rows

//Exit key
const char EXIT='1';

//Keys to move
const char UP='w';
const char DOWN='s';
const char RIGHT='d';
const char LEFT='a';
//const char UP=(char)-3272;
//const char DOWN=(char)-3280;
//const char RIGHT=(char)-3277;
//const char LEFT=(char)-3275;


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

int show(int field[][COLS], int score){
	
	system("CLS");
	
	for(int i=0;i<COLS*2+2;i++)
		cout<<setw(1)<<(char)254<<setw(1);
	cout<<endl;
	
	for(int i=0;i<ROWS;i++){
		cout<<setw(1)<<"|";
		for(int j=0;j<COLS;j++){
			if(field[i][j]==1){							//Snake node
				cout<<setw(2)<<char(254)<<setw(1);
			}else if(field[i][j]==2){										
					cout<<setw(2)<<"*"<<setw(1);
			}else if(field[i][j]==3){							//Snake node
						cout<<setw(2)<<"o"<<setw(1);
				}else
					cout<<setw(1)<<"  "<<setw(1);
		}
		cout<<setw(1)<<"|"<<endl;  
	}	
	
	for(int i=0;i<COLS*2+2;i++)
		cout<<setw(1)<<(char)254<<setw(1);
	cout<<endl;
	
	cout<<"SCORE: "<<score<<endl;
}

int snakeLength (node*head){
	
	node* p;
	int length;
	if (head==NULL)
		length=0;
		else
			length=1;
	p=head;
	while(p->next!=NULL){
		p=p->next;
		length++;
	}
	
	return length;
}

void changeDirection(node* head, char key,char& direction,char prevDir){
	
	int length;	
	length=snakeLength(head);
	cout<<length;
	
	if( key == UP && !(length>1 && prevDir=='D')){					//UP
		direction='U';		
	}else if( key == DOWN && !(length>1 && prevDir=='U')){			//DOWN
		direction='D';
	}else if( key == RIGHT && !(length>1 && prevDir=='L') ){			//RIGHT
		direction='R';
	}else if( key == LEFT && !(length>1 && prevDir=='R')){				//LEFT
		direction='L';
	}
	
}

int OLDmove(int field[][COLS],node* head, char direction){
	
//	cout<<"MOVE";
//	system("PAUSE");
	node* q;
	int prevX,prevY,t,r;
	
	int oldY=head->p.y;
	int oldX=head->p.x;
	
	field[oldY][oldX]=0;
	
//	if(field[head->p.y][head->p.x]==2)		
//		r=2;
	
	if(direction=='U' && head->p.y!=0){					//UP
		prevX=head->p.x;
		prevY=head->p.y;
//		cout<<"prossima posizione numero"<<field[head->p.y-1][head->p.x];
//		system("PAUSE");
		if(field[head->p.y-1][head->p.x]==2)		//The snake eats a drop
			r=2;
		head->p.y=head->p.y-1;
		q=head;
		
//		if(r==2)			//QUESTA COSA FA SCHIFO SISTEMA TUTTO
//		{
//			addTale
//		}	
		
			
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
//		cout<<"prossima posizione numero"<<field[head->p.y+1][head->p.x];
//		system("PAUSE");
		if(field[head->p.y+1][head->p.x]==2)		//The snake eats a drop
			r=2;
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
//		cout<<"prossima posizione numero"<<field[head->p.y][head->p.x+1];
//		system("PAUSE");
		if(field[head->p.y][head->p.x+1]==2)		//The snake eats a drop
			r=2;
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
//		cout<<"prossima posizione numero"<<field[head->p.y][head->p.x-1];
//		system("PAUSE");
		if(field[head->p.y][head->p.x-1]==2)		//The snake eats a drop
			r=2;
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
		r=0;
	}else{										//SUCCESSFULLY MOVED
		field[head->p.y][head->p.x]=1;
		if(r!=2)
			r=1;
	}
	
	return r;
	
}

int move(int field[][COLS],node* head, char direction){
	
//	cout<<"MOVE";
//	system("PAUSE");
	node* q;
	int prevX,prevY,t,r=1;
	
	field[head->p.y][head->p.x]=0;
	
	int xoff=0,yoff=0;
			
	if(direction=='U' && head->p.y!=0){							//UP
		yoff=-1;
		}else if(direction=='D' && head->p.y<(ROWS-1)){			//DOWN	
				yoff=+1;
			}else if(direction=='R' && head->p.x<(COLS-1)){		//RIGHT
					xoff=+1;
				}else if(direction=='L' && head->p.x!=0){		//LEFT
					xoff=-1;
				}else return 0; 								//GAME OVER! THE SNAKE HIT A WALL

		
		prevX=head->p.x;
		prevY=head->p.y;		
		if(field[head->p.y+yoff][head->p.x+xoff]==2)		
			r=2;											//The snake eats a drop	
			else if (field[head->p.y+yoff][head->p.x+xoff]==3)
				return 0;									//GAME OVER!! THE SNAKE ATE HIS TAIL		
		head->p.y=head->p.y+yoff;
		head->p.x=head->p.x+xoff;
		field[head->p.y][head->p.x]=1;		
		q=head;	
	
		while(q->next!=NULL){								//This moves the tail
			q=q->next;
			field[q->p.y][q->p.x]=0;
			t=q->p.y;
			q->p.y=prevY;
			prevY=t;
			t=q->p.x;		
			q->p.x=prevX;
			prevX=t;
			field[q->p.y][q->p.x]=3;
		}
	
	return r;
	
}

void debugSnake(node* head){
	node* q=head;
	while(q->next!=NULL){
		cout<<"X: "<<q->p.x<<" Y: "<<q->p.y<<" NEXT: "<<q->next<<endl;
		
		q=q->next;
	}
}

point newDrop(int field[][COLS]){
	
	point drop;
	int x;
	int y;
	do{
		x = rand() % COLS;
		y = rand() % ROWS;
	}while(field[y][x]!=0);
	drop.x=x;
	drop.y=y;
	field[y][x]=2;
	return drop;
}

int addTale (int field[][COLS], node*&head){
	node* t; 
	node* p;

	t=new node;	
	if(t==NULL){
		cout<<"Memoria esaurita";
		return 1;
	}		

	t->next=NULL;
	if(head==NULL){
		head=t;
		return 0;
	}
	p=head;
	while(p->next!=NULL)
		p=p->next;
	p->next=t;
	t->p.x=p->p.x;
	t->p.y=p->p.y;
	field[t->p.y][t->p.x]=3;
	return 0;
}


int main(int argc, char** argv) {
	
	int field[ROWS][COLS]={0};
	node* head=new node();	//The head of the snake
	char key;	//Key pressed
	char dir;	//Direction of the snake (T Top D Down R Right L Left)+
	char prevDir; //Previous direction of the snake;
	long startTime, currentTime;
	point drop;
	int r;				 //To keep the result of move
	int score=0;
	
	srand (time(NULL));	//Generate random seed 
	
	//Setup
	field[0][0]=1; 		//Snake starts at the top left and heading right
	head->p.x=0;
	head->p.y=0;
	head->next=NULL;
	prevDir=dir='R';	
	drop=newDrop(field);	
//	addTale(field,head,3,0);
//	addTale(field,head,2,0);
//	addTale(field,head,1,0);
//	addTale(field,head,0,0);
//	debugSnake(head);
	
	while(key!=(int)'1'){
			if( _kbhit() ){
		key = _getch();
		cout<<(int)key;

	}
	}

		
	system("PAUSE");

	
	show(field,score);
	startTime=GetTickCount();

	
	while(true){
			
		currentTime=GetTickCount()-startTime;
		
		if ( currentTime >= 200 ){			// half a second
			
			if( _kbhit() ){
			key = _getch();
			
			if (key==EXIT)		//End the game
				break;
			
			prevDir=dir;
			changeDirection(head,key,dir,prevDir);	
			}
		
		
			r=move(field,head,dir);
//			cout<<"move result:"<<r<<endl;
//			system("PAUSE");
			if(r==0){
				cout<<endl<<"****** GAME OVER! ******"<<endl;
				break;
			}else if (r==2)
			{
				score+=100;
				newDrop(field);
				addTale(field,head);			
			}
			show(field,score);
			startTime=GetTickCount();
		}
		

			
		
	}
	
	system("PAUSE");
	return 0;
}
