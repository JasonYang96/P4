#include "provided.h"
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include "substituteMyMap.h"
using namespace std;

class MapLoaderImpl
{
public:
	MapLoaderImpl();
	~MapLoaderImpl();
	bool load(string mapFile);
	size_t getNumSegments() const;
	bool getSegment(size_t segNum, StreetSegment& seg) const;

    vector<StreetSegment> ss;
};

MapLoaderImpl::MapLoaderImpl()
{
}

MapLoaderImpl::~MapLoaderImpl()
{
}

bool MapLoaderImpl::load(string mapFile)
{
    ifstream data(mapFile);
    if (data.fail() || data.bad() || !data.good() || !data.is_open()) { return false; }

    for (string line; getline(data, line); ) {
        StreetSegment s;
        s.streetName = line;

        getline(data, line);
        GeoCoord start(line.substr(0,10), line.substr(12,12));
        GeoCoord end(line.substr(25,10), line.substr(36, 12));
        GeoSegment gs(start, end);
        s.segment = gs;

        vector<Attraction> attractions;
        s.attractions = attractions;
        getline(data, line);
        int num = stoi(line);
        for (int i = 0; i < num; i++) {
            Attraction a;
            getline(data,line);
            stringstream ss(line);
            getline(ss, line, '|');
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            a.name = line;

            getline(ss, line);
            GeoCoord c(line.substr(0,10), line.substr(12,12));
            a.geocoordinates = c;
            attractions.push_back(a);
        }
    }
	return true;  // This compiles, but may not be correct
}

size_t MapLoaderImpl::getNumSegments() const
{
	return ss.size();
}

bool MapLoaderImpl::getSegment(size_t segNum, StreetSegment &seg) const
{
    if (segNum > ss.size()) {return false;}
    seg = ss[segNum];
    return true;
}

//******************** MapLoader functions ************************************

// These functions simply delegate to MapLoaderImpl's functions.
// You probably don't want to change any of this code.

MapLoader::MapLoader()
{
	m_impl = new MapLoaderImpl;
}

MapLoader::~MapLoader()
{
	delete m_impl;
}

bool MapLoader::load(string mapFile)
{
	return m_impl->load(mapFile);
}

size_t MapLoader::getNumSegments() const
{
	return m_impl->getNumSegments();
}

bool MapLoader::getSegment(size_t segNum, StreetSegment& seg) const
{
   return m_impl->getSegment(segNum, seg);
}
