#ifndef pran
#define pran
#include <iostream>
#include <random>
namespace NRandom
{
	inline std::mt19937 generate()
	{
		std::random_device rd{};
		std::seed_seq ss{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
		return std::mt19937{ss};
	}
	inline std::mt19937 mt{generate()};
}
//		std::uniform_int_distribution numbers{1, 100};
//		int KJ{ numbers(random::mt) };
#endif
