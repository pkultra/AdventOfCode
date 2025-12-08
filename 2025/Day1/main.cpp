#include <utils.hpp>

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cerr<<"Input file required"<<'\n';
		return 1;
	}

	int const MAX = 100;
	int value = 50;
	int count = 0;
	int count2 = 0;
	aoc::processFile(argv[1], [&](auto const& line) mutable
	{
		auto const direction = line.substr(0,1);
		auto const steps = boost::lexical_cast<int>(line.substr(1));
		auto const n = steps / MAX;
		auto const modSteps = steps % MAX;
		if(direction == "L")
		{
			if((value < 0 and value - modSteps <= -MAX) or (value > 0 and value - modSteps <= 0)) { count2++; }
			value = (value - steps) % MAX;
		}
		else
		{
			if((value < 0 and value + modSteps >= 0) or (value > 0 and value + modSteps >= MAX)) { count2++; }
			value = (value + steps) % MAX;
		}
		count2 += n;
		// aoc::log("Direction={} steps={} value={}", direction, steps, value);
		if(value == 0) { ++count; }
	});
	std::cout<<count<<'\n';
	std::cout<<count2<<'\n';
	return 0;
}
