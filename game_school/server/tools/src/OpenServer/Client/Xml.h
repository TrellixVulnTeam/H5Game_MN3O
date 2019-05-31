
#include <cassert>
#include <string>
#include <map>
#include <algorithm>
#include <list>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <queue>
#include <stack>
#include <iostream>
#include <functional>
#include <sstream>
#include <expat.h>
#include <float.h>

namespace pwutils
{
	class Xml
	{
	public:
		Xml();
		~Xml();
	public:
		int LoadFromFile(const std::string& file);
		int LoadFromStream(std::istream& stream);
		int LoadFromString(const std::string& text);
	public:
		std::string GetValue(const std::string& path,const std::string& defaultValue = "");
	public:
		typedef std::map<std::string,std::string> CollectionValuesT;
	private:
		CollectionValuesT mValues;
	};

}