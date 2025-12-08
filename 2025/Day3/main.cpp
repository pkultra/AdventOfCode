#include <utils.hpp>

struct Result { std::int64_t value{}; std::int64_t idx{}; };

Result search(std::string const& line, int l, int r)
{
	std::int64_t maxV = 0;
	std::int64_t maxId = 0;
	for(std::int64_t i = l; i <= r; ++i)
	{
		std::int64_t v = line[i] - '0';
		if(v > maxV)
		{
			maxV = v;
			maxId = i;
		}
	}
	return {maxV, maxId};
}

std::int64_t getMax(std::string const& line, int N)
{
	std::int64_t sum = 0;
	int l = 0;
	std::int64_t factor = std::pow(10, N - 1);
	while(N)
	{
		auto const r = search(line, l, line.size() - N);
		sum += r.value * factor;
		l = r.idx + 1;
		factor /= 10;
		--N;
	}
	return sum;
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cerr<<"Input file required"<<'\n';
		return 1;
	}

	std::int64_t ans1 = 0;
	std::int64_t ans2 = 0;
	aoc::processFile(argv[1], [&](auto const& line) mutable
	{
		auto const inputs = aoc::split(line);
		for(auto const& entry : inputs)
		{
			ans1 += getMax(line, 2);
			ans2 += getMax(line, 12);
		}
	});
	std::cout<<ans1<<'\n';
	std::cout<<ans2<<'\n';

	return 0;
}
