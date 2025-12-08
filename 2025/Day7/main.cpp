#include <utils.hpp>

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cerr<<"Input file required"<<'\n';
		return 1;
	}

	std::int64_t ans1 = 0;
	std::int64_t ans2 = 0;
	std::vector<std::string> grid;
	int rowCount = 0;
	int r;
	int c;
	aoc::processFile(argv[1], [&](auto const& line) mutable
	{
		for(int i = 0; i < line.size(); ++i)
		{
			if(line[i] == 'S')
			{
				r = rowCount + 1;
				c = i;
			}
		}
		grid.push_back(line);
		++rowCount;
	});

	std::vector<std::vector<std::int64_t>> routeCount{grid.size(), std::vector<std::int64_t>(grid[0].size(), 0)};
	routeCount[r][c] = 1;

	for(int row = 1; row < grid.size() - 1; ++row)
	{
		for(int col = 0; col < grid[row].size(); ++col)
		{
			if(routeCount[row][col] == 0) continue;
			if(grid[row + 1][col] == '^')
			{
				++ans1;
				if(col - 1 >=0)
				{
					routeCount[row+1][col-1] += routeCount[row][col];
				}
				if(col + 1 < grid[row+1].size())
				{
					routeCount[row+1][col+1] += routeCount[row][col];
				}
			}
			else
			{
				routeCount[row+1][col] += routeCount[row][col];
			}
		}
	}

	for(auto const& v : routeCount.back())
	{
		ans2 += v;
	}

	std::cout<<ans1<<'\n';
	std::cout<<ans2<<'\n';
	return 0;
}
