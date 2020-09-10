#ifndef _TEMA2_H
#define _TEMA2_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct nodes {

	int value;

	int type;

	int sum;

} nodes;
typedef struct trie_node2 trie_node2;

typedef struct list_node2 {

	int value;

	int level;

	trie_node2 *child;

	struct list_node2 *next;
} list_node2;

struct trie_node2 {

	list_node2 *head;
	list_node2 *tail;
};
trie_node2 *create_trie_2();
int max_of_trie(trie_node2 *node);
int min_of_trie(trie_node2 *node);
void add_node(trie_node2 *node, nodes *tool, int k, int s);
void print_trie_2(trie_node2 *node, FILE *f2);
void destroy_list_2(list_node2 *head);
void destroy_trie_2(trie_node2 *trie);
#endif
