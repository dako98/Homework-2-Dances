#ifndef _DANCERS_
#define _DANCERS_

#include <string>
#include <assert.h>

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




private:

	std::string name;

	Dancer* left;

	Dancer* right;

	Neighbours status;
};






#endif // !_DANCERS_
