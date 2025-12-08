#include <utils.hpp>

using Junction = std::vector<std::int64_t>;

struct DistancePair
{
	std::vector<int> ids;
	std::int64_t distance;
	bool operator<(DistancePair const& rhs) const
	{
		return distance < rhs.distance;
	}
};

std::int64_t dist(Junction const& u, Junction const& v)
{
	std::int64_t distance = 0;
	for(int i = 0; i < 3; ++i)
	{
		distance += (u[i] - v[i]) * (u[i] - v[i]);
	}
	return distance;
}

int find(std::vector<int>& parent, int id)
{
	if(parent[id] == id) return id;
	parent[id] = find(parent, parent[id]);
	return parent[id];
}

void merge(std::vector<int>& parent, int x, int y)
{
	int px = find(parent, x);
	int py = find(parent, y);
	if(px < py)
	{
		parent[py] = px;
		find(parent, y);
	}
	if(py < px)
	{
		parent[px] = py;
		find(parent, x);
	}
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cerr<<"Input file required"<<'\n';
		return 1;
	}

	std::int64_t ans1 = 1;
	std::int64_t ans2 = 1;
	std::vector<Junction> junctions;
	std::vector<DistancePair> distancePairs;
	std::vector<int> parent;
	std::unordered_map<int, std::vector<int>> circuits;

	aoc::processFile(argv[1], [&](auto const& line) mutable
	{
		junctions.push_back(aoc::split<std::int64_t>(line));
	});

	for(int i = 0; i < junctions.size(); ++i) { parent.push_back(i); }

	for(int i = 0; i < junctions.size() - 1; ++i)
	{
		for(int j = i + 1; j < junctions.size(); ++j)
		{
			DistancePair p;
			p.ids = {i, j};
			p.distance = dist(junctions[i], junctions[j]);
			distancePairs.push_back(std::move(p));
		}
	}
	std::sort(distancePairs.begin(), distancePairs.end());

	std::string inputFileName{argv[1]};
	int N = inputFileName.find("test") == std::string::npos ? 1000 : 10;

	for(int i = 0; i < N; ++i)
	{
		merge(parent, distancePairs[i].ids[0], distancePairs[i].ids[1]);
	}
	for(int i = 0; i < junctions.size(); ++i)
	{
		int const p = find(parent, i);
		auto& circuit = circuits[p];
		circuit.push_back(i);
	}

	std::vector<int> maxSize;
	for(auto&& [key, entry] : circuits)
	{
		maxSize.push_back(entry.size());
	}
	std::sort(maxSize.begin(), maxSize.end(), std::greater<std::size_t>());
	for(int i = 0; i < 3; ++i)
	{
		ans1 *= maxSize[i];
	}
	
	int resultPair = -1;
	for(int i = 0; i < distancePairs.size(); ++i)
	{
		merge(parent, distancePairs[i].ids[0], distancePairs[i].ids[1]);
		bool good = true;
		for(int p = 0; p < parent.size(); ++p)
		{
			if(find(parent, p) != 0)
			{
				good = false;
				break;
			}
		}
		if(good)
		{
			resultPair = i;
			break;
		}
	}

	ans2 = junctions[distancePairs[resultPair].ids[0]][0] * junctions[distancePairs[resultPair].ids[1]][0];
	std::cout<<ans1<<'\n';
	std::cout<<ans2<<'\n';
	return 0;
}
