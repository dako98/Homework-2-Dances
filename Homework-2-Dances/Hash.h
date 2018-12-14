#include "Dancer.h"


size_t hash(const Dancer &dancer, size_t size)
{
	size_t hash = 0;

	const char* name = dancer.GetName().c_str();
	size_t len = strlen(name);

	for (size_t i = 0; i < len; i++)
	{
		hash += name[i] * name[i] + i;
	}

	return hash % size;
}