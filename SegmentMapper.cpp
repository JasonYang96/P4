#include "provided.h"
#include "substituteMyMap.h"
#include <vector>
using namespace std;

class SegmentMapperImpl
{
public:
	SegmentMapperImpl();
	~SegmentMapperImpl();
	void init(const MapLoader& ml);
	vector<StreetSegment> getSegments(const GeoCoord& gc) const;

    MyMap<GeoCoord, vector<StreetSegment> > map;
};

SegmentMapperImpl::SegmentMapperImpl()
{
}

SegmentMapperImpl::~SegmentMapperImpl()
{
}

void SegmentMapperImpl::init(const MapLoader& ml)
{
    for (int i = 0; i < ml.getNumSegments(); i++) {
        StreetSegment ss;
        if(!ml.getSegment(i,ss)) {continue;}

        //deal with start
        vector<StreetSegment> *found = (vector<StreetSegment> *)map.find(ss.segment.start);
        if (found) {
            found->push_back(ss);
        }
        else {
            vector<StreetSegment> s;
            s.push_back(ss);
            map.associate(ss.segment.start, s);
        }

        //then end
        found = (vector<StreetSegment> *)map.find(ss.segment.end);
        if (found) {
            found->push_back(ss);
        }
        else {
            vector<StreetSegment> s;
            s.push_back(ss);
            map.associate(ss.segment.end, s);
        }
        
    }
}

vector<StreetSegment> SegmentMapperImpl::getSegments(const GeoCoord& gc) const
{
	return *map.find(gc);
}

//******************** SegmentMapper functions ********************************

// These functions simply delegate to SegmentMapperImpl's functions.
// You probably don't want to change any of this code.

SegmentMapper::SegmentMapper()
{
	m_impl = new SegmentMapperImpl;
}

SegmentMapper::~SegmentMapper()
{
	delete m_impl;
}

void SegmentMapper::init(const MapLoader& ml)
{
	m_impl->init(ml);
}

vector<StreetSegment> SegmentMapper::getSegments(const GeoCoord& gc) const
{
	return m_impl->getSegments(gc);
}
