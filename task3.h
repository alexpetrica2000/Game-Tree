#ifndef _TEMA3_H
#define _TEMA3_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodes3 {

	int value;

	int type;

	int sum;

} nodes3;
typedef struct trie_node3 trie_node3;

typedef struct list_node3 {

	int value;

	int level;

	trie_node3 *child;

	int alpha;

	int beta;

	struct list_node3 *next;
} list_node3;
struct trie_node3 {

	list_node3 *head;
	list_node3 *tail;
};
trie_node3 *create_trie_3();
int max(int a, int b);
int min(int a, int b);
int max_of_trie3(trie_node3 *node);
int min_of_trie3(trie_node3 *node);
void add_node3(trie_node3 *node, nodes3 *tool, int k, int s, int alpha, int beta);
void print_trie_3(trie_node3 *node, FILE *f2);
void destroy_list_3(list_node3 *head);
void destroy_trie_3(trie_node3 *trie);
#endif
