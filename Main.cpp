//Uno version chino xdxdxdddxdxdd

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#define PLAYERNAME true
using namespace std;


//ARCHIVO CARD.H


class Card{
public:
	int value = -1;
	string cardcolor;
	Card *next;
	Card(){cardcolor = "";}
	Card(int v, string c);

friend class Deck;
friend class List;
};


//ARCHIVO CARD.CPP
//#include "card.h"


Card::Card(int v, string c){
		value = v;
		cardcolor = c;
		next = NULL;
	}


//ARCHIVO STACK.H
//#include "card.h"

class Stack{
public:
	int size;
	Card *top;
	Stack();
	void push(Card c);
	Card pop();


};

//ARCHIVO STACK.CPP
//#include "stack.h"
//#include "card.h"

Stack::Stack(){
		size = 0;
		top = NULL;
	}


void Stack::push(Card c){
	if (top == NULL){
		*top = c;
		size++;
	}
	else{
		c.next = top;
		*top = c;
		size++;
	}
}
Card Stack::pop(){
	Card* tmp = top;
	top = top->next;
	size--;
	return *tmp;
}
//ARCHIVO LIST.H

class List{
public:
	Card* first;
	int size;
	List();
	void add(Card c);
	void pop(int pos);
	Card select(int pos);
	bool empty(){return (size == 0);}
	void print();
};

//ARCHIVO LIST.CPP
//#include "list.h"

List::List(){first = NULL; size = 0;}
void List::add(Card c){
		if (first == NULL){
				first = new Card(c.value,c.cardcolor);
			 size++;
			 return;
		 }
		else{
			Card* aux = first;
			while (aux->next != NULL) aux = aux->next;
			aux->next = new Card(c.value,c.cardcolor);
			size++;
		}
	}
void List::pop(int pos){
		if (pos > size || pos <= 0){

		}
		else{
			if (pos == 1){
				Card* tmp= first;
				first = first->next;
				delete tmp;
			}
			else{
				int cont = 2;
				Card* aux = first;
				Card* tmp;
				while (cont<pos){
					aux = aux->next;
					cont++;
				}
				tmp = aux->next;
				aux->next = aux->next->next;
				delete tmp;
			}
		}
	}

Card List::select(int pos){
	if (pos > size || pos <= 0){
			Card tmp;
			return tmp;
		}
		else{
			if (pos == 1){
				Card* tmp= first;
				return *tmp;
			}
			else{
				int cont = 2;
				Card* aux = first;
				Card* tmp;
				while (cont<pos){
					aux = aux->next;
					cont++;
				}
				tmp = aux->next;
				return *tmp;
			}
		}
	}
void List::print(){
		Card* aux;
		aux = first;
		int i = 0;
		while(aux){
			cout << i << "  ";
			cout << aux->value << "  " << aux->cardcolor << endl;
			aux = aux->next;
			i++;
		}
	}


// ARCHIVO PLAYER.H
//#include "stack.h"
//#include "card.h"

class Player{
public:
	string name;
	List Hand;
	Player(string n){
		name = n;
	}
	void Draw(Card c){Hand.add(c);}
	bool win(){return Hand.empty();}
	void Use(int v){return Hand.pop(v);}
	Card check(int v){return Hand.select(v);}
};
//MAIN FUNCTIONS COULD BE CALLED FROM A ABSTRACT CLASS

int randomcolor(){
	int temp = rand()%1000;
	if (temp>= 0 && temp<230)    temp = 0;
	if (temp>= 230 && temp<460)  temp = 1;
	if (temp>= 460 && temp<690)  temp = 2;
	if (temp>= 690 && temp<920)  temp = 3;
	if (temp>= 920 && temp<1000) temp = 4;
	return temp;
}

Card DrawCard(){
	int v = rand()%10;
	int c = randomcolor();
	string cardcolor;
	if (c == 0) cardcolor = "red";
	if (c == 1) cardcolor = "green";
	if (c == 2) cardcolor = "blue";
	if (c == 3) cardcolor = "yellow";
	if (c == 4){cardcolor = "black"; v = v%2;}
	Card send(v,cardcolor);
	return send;
}

void generateDeck(){
	string cardcolor;
	vector<Card> vector;
	for(int j = 0; j<4; j++){
		for(int i = 0; i<=9; i++){
			if (j == 0) cardcolor = "red";
			if (j == 1) cardcolor = "green";
			if (j == 2) cardcolor = "blue";
			if (j == 3) cardcolor = "yellow";
			Card c(i, cardcolor);
		}
	}
}
bool samecard(Card a, Card b){
	if (a.value == b.value || a.cardcolor == b.cardcolor)return true;
	else return false;
}

//END OF MAIN FUNCTIONS

void loadHighscores(){
	ifstream file("Highscores.txt");
	cout << "HIGHSCORES" << endl;
	if (file.is_open()) cout << file.rdbuf();
}

bool playerwon(vector<Player> players, int playeramount){
	for (int i = 0; i<playeramount; i++){
		if(players[i].win()) return true;
	}
	return false;
}


int main(){
	loadHighscores();
	srand(time(0));
	int turn = 0;
	int playeramount = 2;
	vector<Player> Players;
	Card currentcard = DrawCard();
	string name1 = "PLayer 1";
	string name2 = "Player 2";
	#if PLAYERNAME
		cout << "Please choose player 1 name." << endl;
		cin >> name1;
		cout << "Please choose player 2 name." << endl;
		cin >> name2;
	#endif
	Player player1(name1);
	Player player2(name2);
	Players.push_back(player1);
	Players.push_back(player2);
	for (int j = 0; j<playeramount; j++){
		for (int i = 0; i<=6; i++) Players[j].Draw(DrawCard());
	}
	system("cls");
	while(!playerwon(Players, playeramount)){
		Player currentPlayer = Players[turn%playeramount];
		cout << "Current card is: " << currentcard.value << " " << currentcard.cardcolor << endl;
		int card = 0;
		cout << "it's: " << currentPlayer.name << " turn. " << endl;
		cout << "Use 0 to draw a card if you are not able to play a card" << endl;
		bool same = 0;
		int j = 1;
		currentPlayer.Hand.print();
		while (!same){
			cout << "Please choose a card to use" << endl;
			cin >> card;
			cout << "Card "<< card << " is being used ..."<< endl;
			same = samecard(currentcard, currentPlayer.Hand.select(card));
			if (card == 0) {
				currentPlayer.Draw(DrawCard());
				cout << "Drawing one card..." << endl;
				currentPlayer.Hand.print();
			}
			if (same){
				currentcard = currentPlayer.Hand.select(card);
				currentPlayer.Hand.pop(card);
			}
			else{
				cout << "Try again." << endl;
			}
		}
	}

}
