#include <utils.hpp>

using Point = std::vector<std::int64_t>;
using Edge = std::vector<Point*>;

std::int64_t area(Point const& p, Point const& q)
{
	return (std::abs(p[0] - q[0]) + 1) * (std::abs(p[1] - q[1]) + 1);
}

bool edgeOutsideRectangle(Edge const& e, Point const& p, Point const& q)
{
	std::int64_t minRecCol, maxRecCol;
	std::tie(minRecCol, maxRecCol) = std::minmax(p[0], q[0]);
	std::int64_t minRecRow, maxRecRow;
	std::tie(minRecRow, maxRecRow) = std::minmax(p[1], q[1]);
	
	auto const& v0 = *e[0];
	auto const& v1 = *e[1];

	std::int64_t minEdgeCol, maxEdgeCol;
	std::tie(minEdgeCol, maxEdgeCol) = std::minmax(v0[0], v1[0]);
	std::int64_t minEdgeRow, maxEdgeRow;
	std::tie(minEdgeRow, maxEdgeRow) = std::minmax(v0[1], v1[1]);

	return maxEdgeCol < minRecCol + 1
		or minEdgeCol > maxRecCol - 1
		or maxEdgeRow < minRecRow + 1
		or minEdgeRow > maxRecRow - 1
		;
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

	std::vector<Point> point;
	std::vector<Edge> edge;

	aoc::processFile(argv[1], [&](auto const& line) mutable
	{
		point.push_back(aoc::split<std::int64_t>(line));
	});

	for(int i = 0; i < point.size() - 1; ++i)
	{
		edge.push_back(Edge{&point[i], &point[i+1]});

		for(int j = i + 1; j < point.size(); ++j)
		{
			auto const a = area(point[i], point[j]);
			ans1 = std::max(a, ans1);
		}
	}
	edge.push_back(Edge{&point[0], &point[point.size() - 1]});

	for(int i = 0; i < point.size() - 1; ++i)
	{
		for(int j = i + 1; j < point.size(); ++j)
		{
			bool isValid = true;
			for(auto const& entry : edge)
			{
				if(not edgeOutsideRectangle(entry, point[i], point[j]))
				{
					isValid = false;
					break;
				}
			}
			if(isValid)
			{
				auto const a = area(point[i], point[j]);
				ans2 = std::max(a, ans2);
			}
		}
	}

	std::cout<<ans1<<'\n';
	std::cout<<ans2<<'\n';
	return 0;
}
