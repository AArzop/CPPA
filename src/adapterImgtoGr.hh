#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <map>

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::bidirectionalS> Graph;
template<typename coordType, typename valueType, class Image>
class AdapterImgToGr
{
  public:
    AdapterImgToGr(unsigned connexite, Image img);

  private:
    unsigned connexite_;
    std::unique_ptr<Graph> graph;
    std::map<coordType, valueType> property_map;
    std::map<unsigned, coordType> idCoordMap;

    void createGraph(Image img);
    void createEdge2();
    void createEdge4();
    void createEdge6();
    void createEdge8();
    void createEdge26();
};

#include "adapterImgtoGr.hxx"
