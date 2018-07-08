#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <map>

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::bidirectionalS> Graph;
template<typename coordType, typename valueType, class Image>
class AdapterImgToGr
{
  public:
    AdapterImgToGr(unsigned connexite, Image img);

    auto getGraph() const { return *graph; }
    const Graph& operator() () const { return *graph; };
    Graph operator() () { return *graph; };

  private:
    unsigned connexite_;
    std::unique_ptr<Graph> graph;
};

template<typename valueType, class Image>
class AdapterImgToGr<int, valueType, Image>
{
  public:
    AdapterImgToGr(unsigned connexite, Image img);

    auto getGraph() const { return *graph; }
    const Graph& operator() () const { return *graph; };
    Graph operator() () { return *graph; };

  private:
    struct Vertex
    {
      int coord;
      valueType value;
    };
    unsigned connexite_;
    std::unique_ptr<Graph> graph;
    std::map<unsigned, struct Vertex> propertyMap;

    void createGraph(Image img);
    void createEdge2();
};

template<typename valueType, class Image>
class AdapterImgToGr<std::pair<int, int>, valueType, Image>
{
  public:
    AdapterImgToGr(unsigned connexite, Image img);

    auto getGraph() const { return *graph; }
    const Graph& operator() () const { return *graph; };
    Graph operator() () { return *graph; };

  private:
    struct Vertex
    {
      std::pair<int, int> coord;
      valueType value;
    };
    unsigned connexite_;
    std::unique_ptr<Graph> graph;
    std::map<unsigned, struct Vertex> propertyMap;

    void createGraph(Image img);
    void createEdge4();
    void createEdge8();
};

template<typename valueType, class Image>
class AdapterImgToGr<std::tuple<int, int, int>, valueType, Image>
{
  public:
    AdapterImgToGr(unsigned connexite, Image img);

    auto getGraph() const { return *graph; }
    const Graph& operator() () const { return *graph; };
    Graph operator() () { return *graph; };

  private:
    struct Vertex
    {
      std::tuple<int, int, int> coord;
      valueType value;
    };
    unsigned connexite_;
    std::unique_ptr<Graph> graph;
    std::map<unsigned, struct Vertex> propertyMap;

    void createGraph(Image img);
    void createEdge6();
    void createEdge26();
};
#include "adapterImgtoGr.hxx"
