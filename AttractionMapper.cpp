#include "provided.h"
#include "substituteMyMap.h"
using namespace std;

class AttractionMapperImpl
{
public:
	AttractionMapperImpl();
	~AttractionMapperImpl();
	void init(const MapLoader& ml);
	bool getGeoCoord(string attraction, GeoCoord& gc) const;

    MyMap<string, GeoCoord> map;
};

AttractionMapperImpl::AttractionMapperImpl()
{
}

AttractionMapperImpl::~AttractionMapperImpl()
{
}

void AttractionMapperImpl::init(const MapLoader& ml)
{
    for (int i = 0; i < ml.getNumSegments(); i++) {
        StreetSegment ss;
        if(!ml.getSegment(i,ss)) {continue;}
        for (int j = 0; j < ss.attractions.size(); j++) {
            map.associate(ss.attractions[j].name, ss.attractions[j].geocoordinates);
        }
    }
}

bool AttractionMapperImpl::getGeoCoord(string attraction, GeoCoord& gc) const
{
    transform(attraction.begin(), attraction.end(), attraction.begin(), ::tolower);
    GeoCoord *found = (GeoCoord *)map.find(attraction);
    if (!found) { return false;}
    gc = *found;
	return true;
}

//******************** AttractionMapper functions *****************************

// These functions simply delegate to AttractionMapperImpl's functions.
// You probably don't want to change any of this code.

AttractionMapper::AttractionMapper()
{
	m_impl = new AttractionMapperImpl;
}

AttractionMapper::~AttractionMapper()
{
	delete m_impl;
}

void AttractionMapper::init(const MapLoader& ml)
{
	m_impl->init(ml);
}

bool AttractionMapper::getGeoCoord(string attraction, GeoCoord& gc) const
{
	return m_impl->getGeoCoord(attraction, gc);
}
