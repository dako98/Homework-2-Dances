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

			if (status == NONE)
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

	void Initialise(Dancer &right)
	{
		this->left = &right;
		this->right = &right;
		this->status = BOTH;

		right.left = this;
		right.right = this;
		right.status = BOTH;

	}

	void Connect(Dancer *left, Dancer *right)
	{
//		if (this == &left || this == &right)
//		{
//			assert(false);
//			//throw std::invalid_argument("Cloning people is not permitted.");
//		}

		//Are they neighbours and need swapping
		if (left->left == right &&
			right->right == left && 
			(left->right!=left->left))
		{
			std::swap(right, left);
		}
		if (left->right == right &&
			right->left == left)
		{

			this->right = right;
			this->left = left;
			this->Grab(BOTH);

			left->right = this;
			right->left = this;

			left->Grab(RIGHT);
			right->Grab(LEFT);
			

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

//		const char* name = this->GetName().c_str();
		size_t len = name.length();

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

	Dancer* GetRight() const
	{
		return right;
	}

	bool operator==(const Dancer &other)
	{
		return this->GetName() == other.GetName();
	}

	/*
	void Swap(Dancer &other)
	{
		//Changing with left neighbour
		if (*this->left == other &&
			other.right == this)
		{
			if ((this->status==NONE || this->status==LEFT) &&
				(other.status==NONE || other.status==RIGHT))
			{
				swap(*this.name)
			}
		}
	}
	*/
private:

	std::string name;

	Dancer* left;

	Dancer* right;

	Neighbours status;
};






#endif // !_DANCERS_
