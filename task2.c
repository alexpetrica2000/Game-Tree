#include "task2.h"

trie_node2 *create_trie_2()
{
	//crearea radacinii
	trie_node2 *trie = malloc(sizeof(trie_node2));

	trie->head = NULL;
	return trie;
}

int max_of_trie(trie_node2 *node)
{
	//functie ce returneaza maximul dintr-o lista de copii
	list_node2 *p = node->head;
	int max;

	if (p != NULL)
		max = p->value;
	while (p != NULL) {
		if (p->value > max)
			max = p->value;
		p = p->next;
	}
	return max;
}
int min_of_trie(trie_node2 *node)
{
	//functie ce returneaza minimul dintr-o lista de copii
	list_node2 *p = node->head;
	int min;

	if (p != NULL)
		min = p->value;
	while (p != NULL) {
		if (p->value < min)
			min = p->value;
		p = p->next;
	}
	return min;
}

void add_node(trie_node2 *node, nodes *tool, int k, int s)
{
	// int k este nivelul
	//nodes *tool este fisierul de intrare parsat intr-un vector de structuri
	//int s este pozitia din vectorul tool a informatiilor nodului ce trebuie inserat
	list_node2 *newnode = malloc(sizeof(list_node2));

	newnode->child = malloc(sizeof(trie_node2));
	newnode->child->head = NULL;
	newnode->level = k;
	newnode->next = NULL;
	int i, t;
	//adaugarea in lista de copii se face in O(1), se adauga in coada listei
	if (node->head == NULL) {
		node->head = newnode;
		node->tail = newnode;
	} else {
		node->tail->next = newnode;
		node->tail = newnode;
		}
		//daca am gasit un nod frunza in vectorul tool
		if (tool[s].type == 0) {
			newnode->value = tool[s].value;
			free(newnode->child);
			newnode->child = NULL;
			return;
		}
		//altfel, avem un nod copil
			t = tool[s].value;

			for (i = 0; i < t; i++)
				add_node(newnode->child, tool, k+1, i+tool[s].sum);
		//in functie de nivel se adauga minimul/maximul valorii nodului
		//dupa ce se iese din recursivitate
		if (k%2 == 0)
			newnode->value = max_of_trie(newnode->child);
		else
			newnode->value = min_of_trie(newnode->child);

}


void print_trie_2(trie_node2 *node, FILE *f2)
{
	//printarea se face recursiv, asemenea taskului1
	if (node == NULL)
		return;
	list_node2 *p = node->head;
	int aux;

	while (p != NULL) {
		aux = p->level;
		while (aux) {
			fprintf(f2, "\t");
			aux = aux - 1;
		}
		fprintf(f2, "%d\n", p->value);
		//se coboara in copii
		print_trie_2(p->child, f2);
		//la revenire din recursivitate se trece la vecini
		p = p->next;
	}
}

void destroy_list_2(list_node2 *head)
{
	list_node2 *p = head;
	list_node2 *q = head;

	while (p != NULL) {
		q = p;
		p = p->next;
		//apelam recursiv functia pentru copii
		destroy_trie_2(q->child);
		q->next = NULL;
		//la intoarcere din recursivitate eliberam memoria alocata nodului
		free(q);
	}
}

void destroy_trie_2(trie_node2 *trie)
{
	if (trie == NULL)
		return;
	destroy_list_2(trie->head);
	free(trie);
}




