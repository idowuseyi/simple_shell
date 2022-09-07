#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
/**
 * steps for realloc
 * 1: declare a temp mem
 * 2: check if the pointer pass is empty return malloc of the new size
 * 3: free buff
 * 4: reallocate buff with newsize
 * 5: copy from tmp to buff
 * 6: free tmp
 * 7: return the new buff 
 */

void *_realloc(void *ptr, int oldsize, int newsize)
{
	void *tmp;
	int i, min;

	if (ptr == NULL)
	{
		tmp = malloc(newsize);
		return (malloc(newsize));
	}
	
	else if (newsize == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	else if (newsize == oldsize)
	{	
		return (ptr);
	}
	else
	{
		min = (new < old) ? new : old;
		tmp = malloc(new);
		if (tmp)
		{
			for (i = 0; i < min; i++)
				*((char *)tmp + i) = *((char *)ptr + i);
			free(ptr);
			return (tmp);
		}
		else
			return (NULL);
	}
}

