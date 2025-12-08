#include <utils.hpp>

struct Range { std::int64_t h; std::int64_t l; };

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cerr<<"Input file required"<<'\n';
		return 1;
	}

	std::vector<Range> rangeVec;
	std::vector<Range> mergedVec;
	int ans1 = 0;
	std::int64_t ans2 = 0;
	aoc::processFile(argv[1], [&](auto const& line) mutable
	{
		if(auto const iter = line.find('-'); iter != std::string::npos)
		{
			auto const vec = aoc::split<std::int64_t>(line, "-");
			rangeVec.emplace_back(Range{.l = vec[0], .h = vec[1]});
			return;
		}
		if (line.size() == 0) return;

		std::int64_t num = boost::lexical_cast<std::int64_t>(line);
		for(auto const& r : rangeVec)
		{
			if(num >= r.l and num <= r.h)
			{
				++ans1;
				return;
			}
		}
	});
	std::cout<<ans1<<'\n';
	std::sort(rangeVec.begin(), rangeVec.end(), [](auto const& x, auto const& y) { return x.l < y.l; });
	for(auto const& r : rangeVec)
	{
		//aoc::log("[{},{}]", r.l, r.h);
		if(mergedVec.size() > 0 and r.l >= mergedVec.back().l and r.l <= mergedVec.back().h)
		{
			mergedVec.back().h = std::max(mergedVec.back().h, r.h);
		}
		else
		{
			mergedVec.push_back(r);
		}
	}
	for(auto const& r : mergedVec)
	{
		//aoc::log("[{},{}]", r.l, r.h);
		ans2 += r.h - r.l + 1;
	}
	std::cout<<ans2<<'\n';
	return 0;
}
