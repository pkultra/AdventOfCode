#include <array>
#include <cmath>
#include <concepts>
#include <fstream>
#include <format>
#include <iostream>
#include <map>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>

namespace aoc
{

template<typename T>
concept Iterable = requires(T t)
{
	std::begin(t);
	std::end(t);
};

template<typename T>
concept MapType = requires { typename T::mapped_type; };

template<typename T>
concept NonMapIterable = Iterable<T> and not MapType<T>;

template<typename... Args>
void log(const std::format_string<Args...> fmt, Args&&... args)
{
	std::cout << std::vformat(fmt.get(), std::make_format_args(args...)) << '\n';
}

void processFile(std::string const& filename, auto cb)
{
	std::ifstream file(filename);
	std::string line;
	if(file.is_open())
	{
		while(std::getline(file, line))
		{
			cb(line);
		}
		file.close();
	}
}

template<typename T = std::string>
std::vector<T> split(std::string const& line, std::string const& delimitor = ",")
{
	std::vector<std::string> strs;
	boost::split(strs, line, boost::is_any_of(delimitor));
	std::vector<T> result;
	for(auto const& v : strs)
	{
		result.emplace_back(boost::lexical_cast<T>(v));
	}
	return result;
}

void print(auto const& container)
{
	std::cout<<container;
}

void print(std::string const& container)
{
	std::cout<<container;
}

void print(NonMapIterable auto const& container)
{
	std::cout<<"[";
	for(auto iter = container.begin(); iter != container.end(); ++iter)
	{
		if(iter != container.begin()) { std::cout<<","; }
		print(*iter);
	}
	std::cout<<"]";
}

void print(MapType auto const& container)
{
	std::cout<<"{";
	for(auto iter = container.begin(); iter != container.end(); ++iter)
	{
		if(iter != container.begin()) { std::cout<<","; }
		std::cout<<"{"<<iter->first<<": ";
		print(iter->second);
		std::cout<<"}";
	}
	std::cout<<"}\n";
}

}
