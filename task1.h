#ifndef _TEMA_H
#define _TEMA_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct trie_node trie_node;

typedef struct list_node {

	char **matrix;

	char player;

	int level;

	trie_node *child;

	struct list_node *next;
} list_node;

struct trie_node {

	list_node *head;
};
trie_node *create_trie();
void add_matrix_node(trie_node *node, char **oldmatrix, int k, int n, int m, char player[2], int count);
void print_trie(trie_node *node, int n, int m, FILE *f2);
int test_matrix(char **a, int n, int m);
void destroy_trie(trie_node *trie, int n);
void destroy_list(list_node *head, int n);
#endif
