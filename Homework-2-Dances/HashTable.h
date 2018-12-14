#ifndef _HASH_TABLE_
#define _HAST_TABLE_

#include <vector>
#include <forward_list>
#include "Dancer.h"

// const size_t MAX_CHAIN_LENGTH = 64;

using Chain = std::forward_list<Dancer*>;
using DataContainer = std::vector<Chain>;

class HashTable
{

public:


	//Think about double hashing.
	void add(const Dancer &dancer)
	{
		if (find(dancer) == nullptr)
		{//Adding new dancer

			if (longestChain > table.capacity()/2)
			{
				Rehash();
			}
			int index = dancer.hash(capacity);

			Dancer* tmp = new Dancer(dancer);

			table[index].push_front(tmp);
			if (longestChain < table[index].size())	//Think of a way to keep chain length. Either tuple or list.
			{

			}
		}
		
	}

	void Rehash()
	{
		DataContainer tmp;
		capacity = table.capacity() * 2;

		tmp.resize(capacity);

		for(Chain chain : table)
			for (Dancer* dancer : chain)
			{
				tmp[dancer->hash(capacity)].push_front(dancer);
			}
		table = tmp;
	}

	Dancer* find(const Dancer &dancer)
	{
		int index = dancer.hash(capacity);

		for (Dancer* current : table[index])
		{
			if (current->GetName() == dancer.GetName())
			{
				return current;
			}
		}
		return nullptr;
	}

	bool Remove(Dancer &target)
	{
		if (target.IsFree())
		{
			table[target.hash(capacity)].remove(&target);
			return true;
		}
		return false;
	}




private:

	DataContainer table;

	size_t capacity;
	size_t longestChain;

};







#endif // !_HASH_TABLE_
