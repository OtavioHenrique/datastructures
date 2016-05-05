#include <stdio.h>
#include <stdlib.h>

typedef struct { //Hash Item struct
 int key;
 int value;
}tHashItem;

typedef struct s_node node;

struct s_node { //Node struct
 tHashItem content;
 node* next;
};

typedef struct { //Linked List struct
 node* first;
 int total;
} tLde;

typedef struct { //Hash Table struct
 int size;
 int total;
 tLde* table;
}tHashTable; 

void prints(tLde* _list){

	node* ptrAtual = _list->first;

    while (ptrAtual != NULL) {
    	printf("=======================================Node=====================\n");
    	printf("Key: %d\n", ptrAtual->content.key);
    	printf("Value: %d\n", ptrAtual->content.value);
    	ptrAtual = ptrAtual->next;
    	printf("======================Final================\n");
    } 
}

int InsertList(tLde* _list, tHashItem _item){ //Function to insert number on linked list
	
	node* previus = NULL;
	node* current = _list->first;

	node* item = malloc(sizeof(node));
	item->content = _item;
	item->next = NULL;

	if(_list->total == 0) {
		_list->first = item;
		_list->total++;
		printf("Entrei5\n");
		return 1;
	} else {
		while(current != NULL) {
			previus = current;
			current = current->next;
		}

		current = item;
		previus->next = item;
		_list->total++;
		return 1;
	}
	
	return -1;

}
int RemoveList(tLde* _list, int _key){ //Function to remove item from linked list

	node* previus = NULL;
	node* current = _list->first;

	if (current->content.value == _key) {
		_list->first = current->next;
		free(current);
		return 1;
	} else {
		while(current != NULL && current->content.value != _key) {
			previus = current;
			current = current->next;
			}
		}
	

	if (current->next == NULL){
		previus->next = NULL;
		free(current);
		return 1;
	} else {
		previus->next = current->next;
		free(current);
		return 1;
	}

	return -1;

}
node* searchList(tLde* _list, int _key){ //Function to search for node on linked list

	node* current = _list->first;

	if (current->content.value == _key) {
		return current;
	} else {
		while(current != NULL) {
			current = current->next;
			if (current->content.value == _key)
				return current;
		}
		
	}

	return NULL;

}

void cleanList(tLde* _list){ //Method to clean linked list
	
	node* current = _list->first;
	node* aux = current;

	while(aux != NULL) {
		aux = current->next;			
		free(current);
	}
} 

int hashFunc(int _value, int _size){ //Hash Function (Return key)
	return _value % _size;
}

tHashTable* createHashTable(int _size){ //Method to create hash table

	tHashTable* hashTable = malloc(sizeof(tHashTable)); //Create hash table
	hashTable->size = _size; //Setting size of hash table equal argument of the function (_size)
	hashTable->total = 0; //Setting total equal 0
	hashTable->table = malloc(sizeof(tLde) * _size); //Create hash items 

	int i;

	for(i=0; i < _size; i++){ //Initializing hash table items  
		hashTable->table[i].first = NULL;
		hashTable->table[i].total = 0;
	} 

	return hashTable;

}
int insertHash(tHashItem _item, tHashTable* h){ //method to insert number on hash
	int answer = InsertList(&(h->table[_item.key]), _item);
	if (answer == 1)
		printf("Successful Insertion of the number: %d\n", _item.value);
	else 
		printf("Error 001 - Failed while inserting hash item\n");

	prints(&(h->table[_item.key]));

}
int removeHash(int key, tHashTable* h){ //Method to remove hash item
	int aux = hashFunc(key, h->size);

	int answer = RemoveList(&(h->table[aux]), key);
	if (answer == 1) 
		printf("Remove Successful\n");
	else 
		printf("Error 003 - Failed while removing node from list on remove hash method\n");


}
void destroyHash(tHashTable *h){ //Method to destroy hash

	int i;
	/*
	for(i=0; i < h->size; i++) {
		free(&(h->table[i]));
	}   BUG HERE */

	free(h);
	printf("Hash Destroyed\n");
}
tHashItem* searchHash(tHashTable* h, int key){ //Function to search hash item
	int aux = hashFunc(key, h->size);
	node* answer = searchList(&(h->table[aux]), key);

	if(answer != NULL) {
		return &(answer->content);
	}
}

void test(tHashTable* hash){
	int answer;
	tHashItem num1;
	num1.value = 15;
	num1.key = hashFunc(num1.value, hash->size);

	answer = insertHash(num1, hash);

	tHashItem num2;
	num2.value = 7;
	num2.key = hashFunc(num2.value, hash->size);

	answer = insertHash(num2, hash);

	tHashItem num3;
	num3.value = 2;
	num3.key = hashFunc(num3.value, hash->size);

	answer = insertHash(num3, hash);

	tHashItem num4;
	num4.value = 12;
	num4.key = hashFunc(num4.value, hash->size);

	answer = insertHash(num4, hash);

	tHashItem num5;
	num5.value = 22;
	num5.key = hashFunc(num5.value, hash->size);

	answer = insertHash(num5, hash);

	answer = removeHash(22, hash);

	tHashItem num6;

	num6.value = 32;
	num6.key = hashFunc(num6.value, hash->size);

	answer = insertHash(num6, hash);

	destroyHash(hash);


}
int main (int argc, char** argv){

	int size = 10;
	tHashTable* hash = createHashTable(size);

	test(hash);

}