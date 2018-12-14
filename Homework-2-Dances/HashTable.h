#ifndef _HASH_TABLE_
#define _HAST_TABLE_

#include <vector>
#include <list>
#include "Dancer.h"


using Chain = std::list<Dancer*>;
using DataContainer = std::vector<Chain>;



class HashTable
{

public:

	HashTable(const Dancer &first, const Dancer &right)
		:capacity(4)
		, count(0)
		, longestChain(0)
	{
		table.resize(capacity);

		addToHash(first);
		addToHash(right);

		Dancer* _first = find(first);
		Dancer* _right = find(right);

		this->first = _first;

		_first->Initialise(*_right);
		
	}


	void add(Dancer& newcomer, Dancer& left, Dancer& right)
	{
		Dancer* _left = find(left);
		Dancer* _right = find(right);

		addToHash(newcomer);
		Dancer* _newcomer = find(newcomer);

		try {
			_newcomer->Connect(_left, _right);
		}
		catch (std::invalid_argument &e)
		{
			std::cout << e.what();
			return;
		}
	}



	//Think about double hashing.
	void addToHash(const Dancer &dancer)
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

			//Get longest chain count.
			if (longestChain < table[index].size())
			{
				longestChain = table[index].size();
			}
			return;
		}

		throw std::invalid_argument("No clones!");
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

		for (Dancer*& current : table[index])
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

	void PrintChains() const
	{
		for (const Chain &chain : table)
		{
			for (const Dancer* dancer : chain)
			{
				dancer->Print();
			}
			std::cout << '\n';
		}
	}

	void Print() const
	{
		_Print(*first->GetRight());
	}

	void _Print(const Dancer &current) const
	{
		if (current.GetName() == first->GetName())
		{
			current.Print();
			return;
		}
		else
		{
			current.Print();
			std::cout << "---";
			_Print(*current.GetRight());
		}
	}

private:

	DataContainer table;

	size_t count;
	size_t capacity;
	size_t longestChain;

	Dancer* first;
};







#endif // !_HASH_TABLE_
