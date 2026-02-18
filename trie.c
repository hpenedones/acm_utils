#include <stdlib.h>
#include <string.h>

typedef struct _trie{
	struct _trie * next[26];
	int count;
} trie;


trie * new_trie() {
	trie * t = (trie *) malloc(sizeof(trie));	
	t->count = 0;
	memset(t->next, 0, 26*sizeof(trie*));	

	return t;
}

int insert(trie * t, const char * s, int n) {

	if (n == 0) {
		return (++t->count);
	}
	int index = (int) (*s - 'a');
	if (!t->next[index]) {
		t->next[index] = new_trie();
		}
	return insert(t->next[index], ++s, n-1);
}

void clean(trie * t) {

	if (!t) return;
	int i;
	for (i=0; i<26; i++)
		clean(t->next[i]);
	free(t);	
}


