#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "bonus.h"

int main(int argc, char **argv) {
if (strstr(argv[1], "-c1") != NULL) {

	//in vectorul player se vor retine
	//cele doua valori pt jucatori, 'R' si 'B'
	char player[2], s[100], *p, **a;
	int i, j, t;
	i = 0;
	FILE *f1 = fopen(argv[2], "r");
	fgets(s, 100, f1);
	s[strlen(s)-1] = '\0';
	int n, m;
	//se citesc numarul de linii si de coloane
	p = strtok(s, " ");
	n = atoi(p);
	p = strtok(NULL, " ");
	m = atoi(p);
	p = strtok(NULL, " ");
	player[0] = *p;

	if (player[0] == 'R')
		player[1] = 'B';
		else {
			player[0] = 'B';
			player[1] = 'R';
		}
	//se aloca matricea initiala
	a = (char **)malloc(n*sizeof(char *));
	for (t = 0; t < n; t++)
		a[t] = (char *)malloc((m+1)*sizeof(char));
	while (fgets(s, 100, f1) != NULL) {
		j = 0;
		p = strtok(s, " \n");
		a[i][j] = *p;
		p = strtok(NULL, " \n");

		while (p != NULL) {
			j++;
			a[i][j] = *p;
			p = strtok(NULL, " \n");
		}
		i++;
	}
	//se printeaza matricea initiala
	FILE *f2 = fopen(argv[3], "w");
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++) {
			if (j != m-1)
				fprintf(f2, "%c ", a[i][j]);
			else
				fprintf(f2, "%c\n", a[i][j]);
		}
	fclose(f1);
	trie_node *game = create_trie();
	//pornind de la matricea initiala, pentru fiecare coloana
	//se aplica functia de creare a nodurilor
	for (j = m-1; j >= 0; j--)
		add_matrix_node(game, a, j, n, m, player, 0);
	//se printeaza nodurile in fisier
	print_trie(game, n, m, f2);
	fprintf(f2, "\n");
	//se elibereaza memoria arborelui multicai
	destroy_trie(game, n);
	//se elibereaza matricea initiala
	for (i = 0; i < n; i++)
		free(a[i]);
	free(a);
	fclose(f2);
}
if (strstr(argv[1], "-c2") != NULL) {

	char s[500000], a, b;
	FILE *f1 = fopen(argv[2], "r");
	fgets(s, 500000, f1);
	s[strlen(s)-1] = '\0';
	int i, x, sum;
	i = 0, sum = 1;
	//se aloca memorie vectorului tool
	nodes *tool = (nodes *)malloc(500000*sizeof(nodes));

	//in acesta se parseaza fisierul de intrare
	//fiecare nod copil/frunza este retinut in structura
	//cu o valoare, un tip(frunza/nod cu copii)
	// si suma valorilor nodurilor copii anterioare
	while (fscanf(f1, "%c%d%c ", &a, &x, &b) != EOF) {
		tool[i].value = x;
		if (a == '(') {
			tool[i].type = 1;
			tool[i].sum = sum;
			sum += x;
		}
		if (a == '[') {
			tool[i].type =  0;
			tool[i].sum = 0;
		}
		i++;
	}

	fclose(f1);
	trie_node2 *game = create_trie_2();
	//se adauga noduri pornind de la nivelul 0
	//dar si din elementul 0 din tool
	add_node(game, tool, 0, 0);
	FILE *f2 = fopen(argv[3], "w");
	//se printeaza arborele de joc
	print_trie_2(game, f2);
	fclose(f2);
	//se elibereaza memoria alocata arborelui
	destroy_trie_2(game);
	//se elibereaza memoria vectorului de structuri auxiliara
	free(tool);
}
if (strstr(argv[1], "-c3") != NULL) {

	char s[500000], a, b;
	FILE *f1 = fopen(argv[2], "r");
	fgets(s, 500000, f1);
	s[strlen(s)-1] = '\0';
	int i, x, sum;
	i = 0, sum = 1;
	//se aloca memorie vectorului tool
	nodes3 *tool = (nodes3 *)malloc(500000*sizeof(nodes3));

	//in acesta se parseaza fisierul de intrare
	//fiecare nod copil/frunza este retinut in structura
	//cu o valoare, un tip(frunza/nod cu copii)
	// si suma valorilor nodurilor copii anterioare
	while (fscanf(f1, "%c%d%c ", &a, &x, &b) != EOF) {
		tool[i].value = x;
		if (a == '(') {
			tool[i].type = 1;
			tool[i].sum = sum;
			sum += x;

		}
		if (a == '[') {
			tool[i].type =  0;
			tool[i].sum = 0;
		}
		i++;
	}

	fclose(f1);
	trie_node3 *game = create_trie_3();
	//fata de taskul2 acum se trimit ca parametrii alpha si beta
	//initial acestia ar trebuii -inf si +inf
	//lucrand cu valori int am decis sa le pun -32000 si 32000
	//se pot actualiza usor
	add_node3(game, tool, 0, 0, -32000, 32000);
	FILE *f2 = fopen(argv[3], "w");
	//se printeaza arborele multicai
	print_trie_3(game, f2);
	fclose(f2);
	//se elibereaza memoria atat arborelui multicai cat si vectorului
	//de structuri auxiliar
	destroy_trie_3(game);
	free(tool);
}

if (strstr(argv[1], "-b") != NULL) {

	char s[500000], a, b, *p;
	FILE *f1 = fopen(argv[2], "r");
	fgets(s, 500000, f1);
	s[strlen(s)-1] = '\0';
	int n, i, x, sum, j;
	p = strtok(s, " ");
	p = strtok(NULL, " ");
	n = atoi(p);
	i = 0, sum = 1;
	//se foloseste vectorul de structuri auxiliar de la task2
	//de data aceasta in value este un vector
	nodes_bonus *tool = (nodes_bonus *)malloc(500000*sizeof(nodes_bonus));
	//se identifica primul caracter, daca este '('stim ca are o singula valoare int
	//daca este '[' stim ca urmeaza un set de n valori
	while (fscanf(f1, "%c", &a) != EOF) {
		if (a == ' ' || a == '\n')
			continue;
		tool[i].value = malloc(n*sizeof(long));
		if (a == '(') {
			fscanf(f1, "%d%c", &x, &b);
			tool[i].value[0] = x;
			tool[i].type = 1;
			tool[i].sum = sum;
			sum += x;

		}
		if (a == '[') {
			for (j = 0; j < n; j++) {
				fscanf(f1, "%d", &x);
				fscanf(f1, "%c", &b);
				tool[i].value[j] = x;
			}
		tool[i].type =  0;
		tool[i].sum = 0;
		}
		i++;
	}

	fclose(f1);
	trie_node_bonus *game = create_trie_bonus();
	//se creeaza arborele de joc asemenea taskului2, diferenta fiind
	//numarul de jucatori
	add_node_b(game, tool, 0, 0, n);
	FILE *f2 = fopen(argv[3], "w");
	//se printeaza arborele multicai
	print_trie_bonus(game, f2, n);
	fclose(f2);
	//se elibereaza memoria pentru arbore, vectorul de int din fiecare
	//structura cat si vectorul de structuri in sine
	destroy_trie_bonus(game);
	for (j = 0; j < i; j++)
		free(tool[j].value);
	free(tool);
}
return 0;
}
