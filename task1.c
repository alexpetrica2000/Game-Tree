#include "task1.h"
//creare radacina arbore multicai
trie_node *create_trie()
{
	trie_node *trie = (trie_node *)malloc(sizeof(trie_node));

	trie->head = NULL;
	return trie;
}

void add_matrix_node(trie_node *node, char **oldmatrix, int k, int n, int m, char player[2], int count)
{
	//testam daca jocul poate continua
	if (test_matrix(oldmatrix, n, m) == 0)
		return;

	int i, j, t;
	list_node *newnode = malloc(sizeof(list_node));

	newnode->child = malloc(sizeof(trie_node));
	newnode->child->head = NULL;
	newnode->player = player[count%2];
	newnode->level = count+1;
	newnode->matrix = (char **)malloc(n*sizeof(char *));
	//creare noua matrice din nod folosing matricea veche
	for (t = 0; t < n; t++)
		newnode->matrix[t] = (char *)malloc((m+1)*sizeof(char));
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			newnode->matrix[i][j] = oldmatrix[i][j];

	//functia primeste un indice k care este specific coloanei
	//astfel parcurgem liniile de jos in sus pentru a afla pozitia in care adaugam caracterul dorit
	for (i = n-1; i >= 0; i--)
		if (newnode->matrix[i][k] == '-') {
			newnode->matrix[i][k] = newnode->player;
			newnode->next = node->head;
			node->head = newnode;
			//daca s-a gasit o pozitie favorabila, se adauga recursiv in continuare
			//noul indice k devine t, adica se ia fiecare coloana in parte
			for (t = m-1; t >= 0; t--)
				add_matrix_node(newnode->child, newnode->matrix, t, n, m, player, count+1);
			return;
		}
	//Daca nu se adauga nod nou (nu se intra in for)
	//inseamna ca nu am avut '-' pe coloana
	//Prin urmare eliminam aceasta posibilitate adaugata
	for (i = 0; i < n; i++)
		free(newnode->matrix[i]);
	free(newnode->matrix);
	free(newnode->child);
	free(newnode);
}

void print_trie(trie_node *node, int n, int m, FILE *f2)
{
	list_node *p = node->head;
	int i, j, aux;
	//in stuctura am retinut nivelul fiecarui nod
	while (p != NULL) {
		fprintf(f2, "\n");
		for (i = 0; i < n; i++) {
			aux = p->level;
			//in functie de nivel se afiseaza taburi
			while (aux) {
				fprintf(f2, "\t");
				aux = aux - 1;
			}
			for (j = 0; j < m; j++) {
				if (j != m-1)
					fprintf(f2, "%c ", p->matrix[i][j]);
				else
					fprintf(f2, "%c\n", p->matrix[i][j]);
			}
		}
		//se coboara recursiv in lista de copii
		print_trie(p->child, n, m, f2);
		//la intoarcere din recursivitate de fiecare data se trece la nodul vecin
		p = p->next;
	}
}

int test_matrix(char **a, int n, int m)
{
	int i, j;
	//testam cazul linie
	for (i = 0; i < n; i++)
		for (j = 0; j < m-3; j++)
			if (a[i][j] == a[i][j+1] && a[i][j+2] == a[i][j+3])
				if (a[i][j+1] == a[i][j+2] && a[i][j] != '-')
					return 0;
	//testam cazul coloana
	for (j = 0; j < m; j++)
		for (i = 0; i < n-3; i++)
			if (a[i][j] == a[i+1][j] && a[i+2][j] == a[i+3][j])
				if (a[i+1][j] == a[i+2][j] && a[i][j] != '-')
					return 0;
	//testam cazul diagonal '\'
	for (i = 0; i < n-3; i++)
		for (j = 0; j < m-3; j++)
			if (a[i][j] == a[i+1][j+1] && a[i+2][j+2] == a[i+3][j+3])
				if (a[i+1][j+1] == a[i+2][j+2] && a[i][j] != '-')
					return 0;
	//testam cazul diagonal '/'
	for (i = n-1; i >= 3; i--)
		for (j = 0; j < m-3; j++)
			if (a[i][j] == a[i-1][j+1] && a[i-2][j+2] == a[i-3][j+3])
				if (a[i-1][j+1] == a[i-2][j+2] && a[i][j] != '-')
					return 0;
	//testam daca mai exista vreun caracter '-' in matrice
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			if (a[i][j] == '-')
				return 1;
	return 0;
}
void destroy_list(list_node *head, int n)
{

	list_node *p = head;
	list_node *q = head;
	int i;

	while (p != NULL) {
		q = p;
		p = p->next;
		//apelam recursiv functia pentru copii
		destroy_trie(q->child, n);
		q->next = NULL;
		//la intoarcere din recursivitate eliberam memoria alocata
		//liniilor din matrice cat si matricei
		for (i = 0; i < n; i++)
			free(q->matrix[i]);
		free(q->matrix);
		free(q);
	}
}


void destroy_trie(trie_node *trie, int n)
{
	destroy_list(trie->head, n);
	free(trie);
}








