#include "bonus.h"

trie_node_bonus *create_trie_bonus()
{
	//creare radacina
	trie_node_bonus *trie = malloc(sizeof(trie_node_bonus));

	trie->head = NULL;
	return trie;
}

//functie ce intoarce un vector, in functie de val max a primului elem
int *max_of_trie_bonus(trie_node_bonus *node, int n)
{
	list_node_bonus *p = node->head;
	int max, *dup, i;
	//se aloca memorie pt vectorul ce urmeaza a fii returnat
	int *vect_max = malloc(n*sizeof(int));
	//primul element din lista devine maxim
	//in *dup se retine adresa vectorului ce contine elem max
	if (p != NULL) {
		max = p->value[0];
		dup = p->value;
	}
	//se parcurge lista
	//daca se gaseste un element mai mare decat max
	//se schimba atat max cu noua valoare cat si dup cu adresa valorii
	while (p != NULL) {
		if (p->value[0] > max) {
			max = p->value[0];
			dup = p->value;
		}
		p = p->next;
	}
	//se formeaza duplicatul pentru a-l returna
	for (i = 0; i < n; i++)
		vect_max[i] = dup[i];
	return vect_max;
}

//functie ce intoarce un vector, in functie de val min a primului elem
int *min_of_trie_bonus(trie_node_bonus *node, int n)
{
	list_node_bonus *p = node->head;
	int min, *dup, i;
	//se aloca memorie pt vectorul ce urmeaza a fii returnat
	int *vect_min = malloc(n*sizeof(int));
	//primul element din lista devine minim
	//in *dup se retine adresa vectorului ce contine elem minim

	if (p != NULL) {
		min = p->value[0];
		dup = p->value;
	}
	//se parcurge lista
	//daca se gaseste un element mai mic decat min
	//se schimba atat min cu noua valoare cat si dup cu adresa valorii
	while (p != NULL) {
		if (p->value[0] < min) {
			min = p->value[0];
			dup = p->value;
		}
		p = p->next;
	}
	//se formeaza duplicatul pentru a-l returna
	for (i = 0; i < n; i++)
		vect_min[i] = dup[i];
	return vect_min;
}

//aceeiasi aplicabilitate ca la taskul2, doar cu parametrul int n in plus
//ce semnifica numarul de jucatori
void add_node_b(trie_node_bonus *node, nodes_bonus *tool, int k, int s, int n)
{

	list_node_bonus *newnode = malloc(sizeof(list_node_bonus));

	newnode->child = malloc(sizeof(trie_node_bonus));
	newnode->child->head = NULL;
	newnode->level = k;
	newnode->next = NULL;
	int i, t;
	//se adauga in coada listei in O(1)
	if (node->head == NULL) {
		node->head = newnode;
		node->tail = newnode;
	} else {
		node->tail->next = newnode;
		node->tail = newnode;
	}
	//daca nodul adaugat este frunza
	if (tool[s].type == 0) {
		newnode->value = malloc(n*sizeof(int));
		for (i = 0; i < n; i++)
			newnode->value[i] = tool[s].value[i];
		free(newnode->child);
		newnode->child = NULL;
		return;

		} else {
			t = tool[s].value[0];
			//se adauga nodurile in aceeiasi maniera ca la task2
			for (i = 0; i < t; i++)
				add_node_b(newnode->child, tool, k+1, i+tool[s].sum, n);
		//in urma adaugarii nodurilor copii, se foloseste functia ce returneaza
		//un vector max sau min, in functie de nivel si nr de jucatori
		if (k%n == 0)
			newnode->value = max_of_trie_bonus(newnode->child, n);
		else
			newnode->value = min_of_trie_bonus(newnode->child, n);

	}

}
void print_trie_bonus(trie_node_bonus *node, FILE *f2, int n)
{
	if (node == NULL)
		return;
	list_node_bonus *p = node->head;
	int aux, i;
	//afisarea taburilor se face in functie de nivel
	while (p != NULL) {
		aux = p->level;
		while (aux) {
			fprintf(f2, "\t");
			aux = aux - 1;
		}
		//se printeaza valorile nodului in functie de nr jucatori
		//in formatul cerut , intre [ ] si ,
		fprintf(f2, "[");
		for (i = 0; i < n; i++)
			if (i != n-1)
				fprintf(f2, "%d,", p->value[i]);
			else
				fprintf(f2, "%d]", p->value[i]);
		fprintf(f2, "\n");
		//se intra in maniera recursiva in copii
		print_trie_bonus(p->child, f2, n);
		//la revenire se trece la vecini
		p = p->next;
	}
}

void destroy_list_bonus(list_node_bonus *head)
{
	list_node_bonus *p = head;
	list_node_bonus *q = head;

	while (p != NULL) {
		q = p;
		p = p->next;
		//se intra recursiv in copii pentru a le elibera memoria
		destroy_trie_bonus(q->child);
		//la revenire se elibereaza atat vectorul de valori ca si nodul
		free(q->value);
		q->next = NULL;
		free(q);
	}
}


void destroy_trie_bonus(trie_node_bonus *trie)
{
	if (trie == NULL)
		return;
	destroy_list_bonus(trie->head);
	free(trie);
}




