#include <boost/graph/adjacency_list.hpp>
#include <iostream>

#include "adapterGrToImg.hh"
#include "adapterImgtoGr.hh"

struct VertexProperties
{
  std::pair<int, int> coord;
  int value;
};

typedef boost::property<boost::edge_weight_t, int> EdgeWeightProperty;
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, VertexProperties, EdgeWeightProperty > DirectedGraph;
typedef boost::graph_traits<DirectedGraph>::edge_iterator edge_iterator;
 
int main()
{
    DirectedGraph g;
 
    boost::add_edge (0, 1, 8, g);
    boost::add_edge (0, 3, 18, g);
    boost::add_edge (1, 2, 20, g);
    boost::add_edge (2, 3, 2, g);
    boost::add_edge (3, 1, 1, g);
    boost::add_edge (1, 3, 7, g);
    boost::add_edge (1, 4, 1, g);
    boost::add_edge (4, 5, 6, g);
    boost::add_edge (2, 5, 7, g);

    int x = 0;
    for (unsigned i = 0; i < 3; ++i)
    {
      for (unsigned j = 0; j < 3; ++j)
      {  
        g[x].coord = std::make_pair(i, j);
        g[x].value = i * i;
        ++x;
      }
    } 

    AdapterGrToImg<std::pair<int, int>, int, DirectedGraph> a(g);

    std::cout << std::endl;

    auto map = a.pixels();

    AdapterImgToGr<std::pair<int, int>, int, AdapterGrToImg<std::pair<int, int>, int, DirectedGraph>> a2(4, a);

    std::cout << "----- " << boost::num_edges(a2()) << std::endl;

    return 0;
 }
