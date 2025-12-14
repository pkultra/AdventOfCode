#include <utils.hpp>

struct Device
{
	std::string name;
	std::vector<Device*> children;
};

std::int64_t dfs(auto& devices, std::unordered_map<std::string, std::int64_t>& cachedCount, std::string const& src, std::string const& dst)
{
	if(src == dst) return 1;
	
	auto iter = cachedCount.find(src);
	if(iter != cachedCount.end()) return iter->second;

	std::int64_t count = 0;
	auto& parent = devices[src];
	for(auto const& child : parent.children)
	{
		count += dfs(devices, cachedCount, child->name, dst);
	}
	cachedCount[src] = count;
	return count;
}

std::int64_t solve(auto& devices, std::string const& src, std::string const& dst)
{
	std::unordered_map<std::string, std::int64_t> cachedCount;
	return dfs(devices, cachedCount, src, dst);
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

	std::unordered_map<std::string, Device> devices;

	aoc::processFile(argv[1], [&](auto const& line) mutable
	{
		auto const vec = aoc::split(line, " ");
		// aoc::print(vec);
		// std::cout<<'\n';
		auto const parentName = vec[0].substr(0, vec[0].size() - 1);
		auto& parent = devices[parentName];
		parent.name = parentName;
		for(int i = 1; i < vec.size(); ++i)
		{
			auto& child = devices[vec[i]];
			child.name = vec[i];
			parent.children.push_back(&child);
		}
	});

	ans1 = solve(devices, "you", "out");
	std::cout<<ans1<<'\n';

	ans2 = solve(devices, "svr", "fft") * solve(devices, "fft", "dac") * solve(devices, "dac", "out")
		 + solve(devices, "svr", "dac") * solve(devices, "dac", "fft") * solve(devices, "fft", "out")
		 ;
	std::cout<<ans2<<'\n';
	return 0;
}
