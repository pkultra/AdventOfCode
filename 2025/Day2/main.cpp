#include <utils.hpp>

bool isValid(std::string const& str)
{
	if(str.size() % 2 == 1) return false;
	auto const offset = str.size() / 2;
	for(std::int64_t i = 0; i < offset; ++i)
	{
		if(str[i] != str[i+offset]) return false;
	}
	return true;
}

bool isRepeatedValid(std::string const& str)
{
	for(std::int64_t i = 1; i <= str.size() / 2; ++i)
	{
		if(str.size() % i !=0) continue;
		auto const n = str.size() / i;
		bool mismatch = false;
		auto const first = str.substr(0, i);
		for(int j = 0; j < n; ++j)
		{
			if(first != str.substr(i*j, i))
			{
				mismatch = true;
				continue;
			}
		}
		if(not mismatch) return true;
	}
	return false;
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cerr<<"Input file required"<<'\n';
		return 1;
	}

	aoc::processFile(argv[1], [&](auto const& line) mutable
	{
		std::int64_t ans1 = 0;
		std::int64_t ans2 = 0;
		auto const inputs = aoc::split(line);
		for(auto const& entry : inputs)
		{
			auto const vec = aoc::split<std::int64_t>(entry, "-");
			for(std::int64_t i = vec[0]; i <= vec[1]; ++i)
			{
				auto const str = boost::lexical_cast<std::string>(i);
				if(isValid(str)) ans1 += i;
				if(isRepeatedValid(str)) ans2 += i;
			}
		}
		std::cout<<ans1<<'\n';
		std::cout<<ans2<<'\n';
	});

	return 0;
}
