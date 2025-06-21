#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "dirfunc.h"

int main (int argc, char *argv[]) {
	dirent *dhold;
	DIR *fd;
	ent_arr *list = ent_list_new();

	if(!argv[1]) {
		printf("Directory not specified.\n");
		return 1;
	}

	//Attempt to open directory
	fd = opendir(argv[1]);
	if (!fd) {
		printf("Directory not accessible.\n");
		return 1;
	}

	while ((dhold = readdir(fd)) != NULL) {
		add_to_ent(list, dhold);
	}

	rewinddir(fd);

	//test print of non-recursive cwd entries
	while ((dhold = readdir(fd)) != NULL) {
				printf("%s\n", dhold->d_name);
	}

	qsort(list->dent, list->used, sizeof(dirent*), cmpdir); 
	for(int i = 0; i < list->used; i++) {
		printf("%s\n", list->dent[i]->d_name);
	}

	printf("%d used\n", list->used);
	closedir(fd);
	return 0;
}
