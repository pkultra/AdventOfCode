#include <utils.hpp>

struct Coord { int row; int col; };

bool in(auto const& grid, int i, int j)
{
	return i >= 0 and i < grid.size() and j >=0 and j < grid.front().size();
}

int neighbours(auto const& grid, int r, int c)
{
	int count = 0;
	for(int i = r - 1; i <= r + 1; ++i)
	{
		for(int j = c - 1; j <= c + 1; ++j)
		{
			if(i == r and j == c) continue;
			if(in(grid, i, j) and grid[i][j] == '@') ++count;
		}
	}
	return count;
}

std::vector<Coord> check(auto const& grid)
{
	std::vector<Coord> coords;
	for(int r = 0; r < grid.size(); ++r)
	{
		for(int c = 0; c < grid.front().size(); ++c)
		{
			if(grid[r][c] == '@' and neighbours(grid, r, c) < 4)
			{
				coords.emplace_back(Coord{.row = r, .col = c});
			}
		}
	}
	return coords;
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cerr<<"Input file required"<<'\n';
		return 1;
	}

	std::vector<std::string> grid;
	aoc::processFile(argv[1], [&](auto const& line) mutable
	{
		grid.push_back(line);
	});
	int count = 0;
	std::vector<Coord> coords = check(grid);
	std::cout<<coords.size()<<'\n';

	while(coords.size())
	{
		count += coords.size();
		for(auto const& p : coords)
		{
			grid[p.row][p.col] = '.';
		}
		coords = check(grid);
	}

	std::cout<<count<<'\n';

	return 0;
}
