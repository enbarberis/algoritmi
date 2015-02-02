typedef struct st *St;

St 	st_init(int n);
void	st_insert(St st, char *str);
int	st_pos(St st, char *str); 	//ritorna pos. di str, -1 se non la trova
char*	st_get(St st, int pos);
void	st_destroy(St st);

