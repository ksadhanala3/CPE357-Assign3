#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include "dirfunc.h"

//compare directory entry names
int cmpdir(void const *a, void const *b) {
        const dents *aa = *(const dents **)a;
        const dents *bb = *(const dents **)b;

        return strcmp(aa->name, bb->name);
}

//creates and allocs dynamic list of dents with intital capacity of 5
ent_arr *ent_list_new() {
	ent_arr *new_arr = malloc(sizeof(ent_arr));
	new_arr->dents = malloc(5 * sizeof(dents*));
	new_arr->cap = 5;
	new_arr->used = 0;
	new_arr->last_accessed = 0;

	return new_arr;
}

//add to ent_arr list
void add_to_ent(ent_arr *list, dirent *add) {
	struct stat sb;
	char type;
	
	if (lstat(add->d_name, &sb) == -1) {
		perror("lstat");
		exit(EXIT_FAILURE);
	}

	//will store what kind of thing, only concerned with directory type for now, rest is fluff
	switch (sb.st_mode & S_IFMT) {
		case S_IFDIR: type = 'd'; break;
		case S_IFLNK: type = 'l'; break;
		case S_IFREF: type = 'f'; break;
		default:      type = '?'; break;

	if (list->used < list->cap) {
		list->ents[list->used]->name = strdup(add->name);
		list->ents[list->used]->type = type;
		list->ents[list->used]->size = (int) sb.st_size;
		list->used++;
		return;
	}

	list->dent = realloc(list->ents, (list->cap + 5) * sizeof(dents*));
	list->ents[list->used]->name = strdup(add);
	list->ents[list->used]->type = type;
        list->ents[list->used]->size = (int) sb.st_size;
	list->cap += 5;
	list->used++;
	return;
}
