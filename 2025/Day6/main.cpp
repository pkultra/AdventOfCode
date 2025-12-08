#include <utils.hpp>
#include <regex>

auto solve(auto const& ops, auto const& nums)
{
	std::int64_t result{};
	for(int i = 0; i < ops.size(); ++i)
	{
		std::int64_t local = ops[i] == "+" ? 0 : 1;
		for(int j = 0; j < nums[i].size(); ++j)
		{
			if(ops[i] == "+")
			{
				local += nums[i][j];
			}
			else
			{
				local *= nums[i][j];
			}
		}
		result += local;
	}

	return result;
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cerr<<"Input file required"<<'\n';
		return 1;
	}

	std::vector<std::vector<std::int64_t>> nums;
	std::vector<std::string> ops;
	std::vector<std::string> lines;
	std::int64_t ans1 = 0;
	std::int64_t ans2 = 0;
	aoc::processFile(argv[1], [&](auto const& line) mutable
	{
		lines.push_back(line);
		auto const leftTrimmed = std::regex_replace(line, std::regex("^\\s+"), "");
		auto const rightTrimmed = std::regex_replace(leftTrimmed, std::regex("\\s+$"), "");
		auto const processedLine = std::regex_replace(rightTrimmed, std::regex("\\s+"), ",");
		if(auto const iter = processedLine.find('*'); iter == std::string::npos)
		{
			auto vec = aoc::split<std::int64_t>(processedLine);
			if(nums.size() == 0)
			{
				nums.resize(vec.size());
			}
			for(int i = 0; i < vec.size(); ++i)
			{
				nums[i].push_back(vec[i]);
			}
		}
		else
		{
			ops = aoc::split(processedLine);
		}
	});
	ans1 += solve(ops, nums);

	std::vector<std::vector<std::int64_t>> nums2;
	std::vector<std::string> ops2;
	std::vector<std::int64_t> colNums;
	for(int j = lines[0].size() - 1; j >=0; --j)
	{
		std::string numString{};
		for(auto i = 0; i < lines.size(); ++i)
		{
			if(lines[i][j] == ' ')
			{
				continue;
			}
			if(lines[i][j] != '*' and lines[i][j] != '+')
			{
				numString.push_back(lines[i][j]);
			}
			else
			{
				ops2.push_back(std::string{lines[i][j]});
			}
		}
		if(numString.empty())
		{
			nums2.push_back(std::move(colNums));
		}
		else
		{
			colNums.push_back(boost::lexical_cast<std::int64_t>(numString));
		}
		if(j == 0)
		{
			nums2.push_back(std::move(colNums));
		}
	}

	ans2 += solve(ops2, nums2);

	std::cout<<ans1<<'\n';
	std::cout<<ans2<<'\n';
	return 0;
}
