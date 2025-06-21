
//Struct for dynamic directory entry array with initial capacity of 10 entries
typedef struct ent_arr {
	struct dents **ents;
	int cap;
	int used;
	int last_accessed;
	struct ent_arr *prev;
} ent_arr;

typedef struct dents {
	char *name;
	char type;
	int size;
} dents;

typedef struct dirent dirent;

//string compare for qsort
int cmpdir(void const *a, void const *b);

//Create new ent_arr capacity 5
ent_arr *ent_list_new();

//add to ent_arr, increase capacity by 5 and add if full
void add_to_ent(ent_arr *list, dirent *add);
