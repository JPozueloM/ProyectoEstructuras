//Uno version chino xdxdxdddxdxdd

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;


//ARCHIVO CARD.H


class Card{
public:
	int value = -1;
	string cardcolor;
	Card *next;
	Card(int v, string c);
	
friend class Deck;
friend class List;
};


//ARCHIVO CARD.CPP
//#include "card.h"


Card::Card(int v, string c){
		value = v;
		cardcolor = c;
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
		first = NULL;
	}


void Stack::push(Card c){
	if (top == NULL){
		tope = c;
		size++;
	}
	else{
		c->next = top;
		top = c;
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
	Card pop(int pos);
};

//ARCHIVO LIST.CPP
//#include "list.h"

List::List(){first == NULL; size = 0;}
void List::add(Card c){
		if (first == NULL){first = c; size++;}
		else{
			Card* aux = first;
			while (aux->next != NULL;) aux = aux->next;
			aux->next = c;
			size++;
		}
	}
Card List::pop(int pos){
		if (pos > size || pos <= 0){
			Card tmp = NULL;
			return tmp;
		}
		else{
			if (pos == 1){
				Card* tmp= first;
				first = first->next;
				return tmp;
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
				return tmp;
			}
		}
	}








// ARCHIVO PLAYER.H
//#include "stack.h"
//#include "card.h"

class Player{
public:
	string name;
	Stack Deck;
	Player(string n){
		name = n;
	}
	void Draw(Card c){Deck.push_back(c);}
	bool win(){return Deck.empty();}
	void Use(int v){Deck.erase(Deck.begin() + (v - 1));}
};