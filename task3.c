#include "task3.h"

trie_node3 *create_trie_3()
{
	trie_node3 *trie = malloc(sizeof(trie_node3));

	trie->head = NULL;
	return trie;
}
int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}
int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;

}
int max_of_trie3(trie_node3 *node)
{
	list_node3 *p = node->head;
	int max;
	//se returneaza maximul din lista de copii
	if (p != NULL)
		max = p->value;
	while (p != NULL) {
		if (p->value > max)
			max = p->value;
		p = p->next;
	}
	return max;
}
int min_of_trie3(trie_node3 *node)
{
	list_node3 *p = node->head;
	int min;
	//se returneaza minimul din lista de copii
	if (p != NULL)
		min = p->value;
	while (p != NULL) {
		if (p->value < min)
			min = p->value;
		p = p->next;
	}
	return min;
}

void add_node3(trie_node3 *node, nodes3 *tool, int k, int s, int alpha, int beta)
{
	//se primesc valorile alpha si beta ale nodului parinte
	//daca conditia nu este indeplinita, se iese, nu trebuie adaugat nod
	if (alpha >= beta)
		return;
	list_node3 *newnode = malloc(sizeof(list_node3));

	newnode->child = malloc(sizeof(trie_node3));
	newnode->child->head = NULL;
	newnode->level = k;
	newnode->next = NULL;
	newnode->alpha = alpha;
	newnode->beta = beta;
	int i, t;

	//se adauga in coada listei in O(1)
	if (node->head == NULL) {
		node->head = newnode;
		node->tail = newnode;
	} else {
		node->tail->next = newnode;
		node->tail = newnode;
		}
		//daca am gasit un nod frunza
		if (tool[s].type == 0) {
			newnode->value = tool[s].value;
			newnode->alpha = newnode->value;
			newnode->beta = newnode->value;
			free(newnode->child);
			newnode->child = NULL;
			return;

		}
		t = tool[s].value;
		//in caz contrar, suntem intr-un nod ce are copii, adaugam noduri
		for (i = 0; i < t; i++) {
			add_node3(newnode->child, tool, k+1, i+tool[s].sum, newnode->alpha, newnode->beta);
			//la fiecare iteratie se actualizeaza alpha si beta care sunt apoi trimisi iar
			//ca parametru pentru urmatoarele noduri din copii
			if (k%2 == 0)
				newnode->alpha = max(newnode->child->tail->beta, newnode->alpha);
			else
				newnode->beta = min(newnode->child->tail->alpha, newnode->beta);
			}
		//la terminarea forului inseamna ca am adaugat atatea noduri cat am avut nevoie
		//conform alpha-beta prunning
		//mai ramane sa atribuim valoarea nodului in functie de nivel
		if (k%2 == 0)
			newnode->value = max_of_trie3(newnode->child);
		else
			newnode->value = min_of_trie3(newnode->child);
}

void print_trie_3(trie_node3 *node, FILE *f2)
{

	if (node == NULL)
		return;
	list_node3 *p = node->head;
	int aux;

	while (p != NULL) {
		aux = p->level;
		while (aux) {
			fprintf(f2, "\t");
			aux = aux - 1;
		}
		fprintf(f2, "%d\n", p->value);
		//se coboara in copii
		print_trie_3(p->child, f2);
		//la revenire din recursivitate se trece la vecini
		p = p->next;
	}
}

void destroy_list_3(list_node3 *head)
{
	list_node3 *p = head;
	list_node3 *q = head;

	while (p != NULL) {
		q = p;
		p = p->next;
		//apelam recursiv functia pentru copii
		destroy_trie_3(q->child);
		q->next = NULL;
		//la intoarcere din recursivitate eliberam memoria alocata nodului
		free(q);
	}
}


void destroy_trie_3(trie_node3 *trie)
{
	if (trie == NULL)
		return;
	destroy_list_3(trie->head);
	free(trie);
}




