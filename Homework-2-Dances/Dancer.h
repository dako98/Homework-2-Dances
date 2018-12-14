#ifndef _DANCERS_
#define _DANCERS_

#include <string>
#include <assert.h>
#include <iostream>

enum Neighbours
{
	NONE, LEFT, RIGHT, BOTH
};

class Dancer
{
public:

	Dancer(std::string name)
		:name(name)
		, left(nullptr)
		, right(nullptr)
		, status(NONE)
	{};

	void Grab(Neighbours side)
	{
		switch (side)
		{
		case NONE:
			break;
		case LEFT:

			if (status==NONE)
			{
				status = LEFT;
			}
			if (status == RIGHT)
			{
				status = BOTH;
			}

			break;
		case RIGHT:

			if (status == NONE)
			{
				status = RIGHT;
			}
			if (status == LEFT)
			{
				status = BOTH;
			}

			break;
		case BOTH:
			status = BOTH;

			break;
		default:
			throw std::invalid_argument("Unknown side.");
			break;
		}
	}

	void Release(Neighbours side)
	{
		switch (side)
		{
		case NONE:
			break;
		case LEFT:

			if (status == BOTH)
			{
				status = RIGHT;
			}
			if (status == LEFT)
			{
				status = NONE;
			}

			break;
		case RIGHT:

			if (status == BOTH)
			{
				status = LEFT;
			}
			if (status == RIGHT)
			{
				status = NONE;
			}

			break;
		case BOTH:
			status = NONE;

			break;
		default:
			throw std::invalid_argument("Unknown side.");
			break;
		}
	}

	void Connect(Dancer &newcomer, Dancer &first, Dancer &second)
	{
		if (&newcomer == &first|| &newcomer==&second)
		{
			assert(false);
			//throw std::invalid_argument("Cloning people is not permitted.");
		}

		//Are they neighbours
		if (first.left == &second && second.right == &first)
		{
			first.left = &newcomer;
			newcomer.right = &first;
			second.right = &newcomer;
			newcomer.left = &second;
			newcomer.Grab(BOTH);
			first.Grab(LEFT);
			second.Grab(RIGHT);
		}
		else if (first.right == &second && second.left == &first)
		{
			first.right = &newcomer;
			newcomer.left = &first;
			second.left = &newcomer;
			newcomer.right = &second;
			newcomer.Grab(BOTH);
			first.Grab(RIGHT);
			second.Grab(LEFT);
		}
		else
		{
			throw std::invalid_argument("Dancers are not neighbours.");
		}

	}

	void Print() const
	{
		if (this->left->status == RIGHT || this->left->status == BOTH)
		{
			std::cout << '>';
		}
		else
		{
			std::cout << '-';
		}

		std::cout << name;

		if (this->right->status == LEFT || this->left->status == BOTH)
		{
			std::cout << '<';
		}
		else
		{
			std::cout << '-';
		}
	}

	std::string GetName() const
	{
		return name;
	}

	size_t hash(size_t size) const
	{
		size_t hash = 0;

		const char* name = this->GetName().c_str();
		size_t len = strlen(name);

		for (size_t i = 0; i < len; i++)
		{
			hash += name[i] * name[i] + i;
		}

		return hash % size;
	}

	bool IsFree() const
	{
		return status == NONE && left->status < RIGHT && right->status < LEFT;
	}

private:

	std::string name;

	Dancer* left;

	Dancer* right;

	Neighbours status;
};






#endif // !_DANCERS_
