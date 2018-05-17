#include <stdlib.h>
#include "head4list.h"

seqlist *init_seqlist(int size)
{
	seqlist *sl = (seqlist *)malloc(sizeof(seqlist));
	if(sl != NULL)
	{
		sl->data = (ln_datatype *)malloc(size);
		sl->size = size;
		sl->last = -1;
	}

	return ((sl->data != NULL) ? sl : (free(sl), NULL));
}

bool is_full_sl(seqlist *sl)
{
	return sl->last >= sl->size - 1;
}

bool is_empty_sl(seqlist *sl)
{
	return sl->last == -1;
}

bool seqlist_insert(seqlist *sl, ln_datatype data)
{
	if(is_full_sl(sl))
		return false;

	sl->data[++(sl->last)] = data;
	return true;
}

int len_sl(seqlist *sl)
{
	return sl->last + 1;
}
