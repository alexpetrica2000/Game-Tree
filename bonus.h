#ifndef _BONUS_H
#define _BONUS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodes_bonus {

	int *value;

	int type;

	int sum;

} nodes_bonus;
typedef struct trie_node_bonus trie_node_bonus;

typedef struct list_node_bonus {

	int *value;

	int level;

	trie_node_bonus *child;

	struct list_node_bonus *next;
} list_node_bonus;

struct trie_node_bonus {

	list_node_bonus *head;
	list_node_bonus *tail;
};
trie_node_bonus *create_trie_bonus();
int *max_of_trie_bonus(trie_node_bonus *node, int n);
int *min_of_trie_bonus(trie_node_bonus *node, int n);
void add_node_b(trie_node_bonus *node, nodes_bonus *tool, int k, int s, int n);
void print_trie_bonus(trie_node_bonus *node, FILE *f2, int n);
void destroy_list_bonus(list_node_bonus *head);
void destroy_trie_bonus(trie_node_bonus *trie);
#endif
