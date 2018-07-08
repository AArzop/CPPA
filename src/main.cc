#include <boost/graph/adjacency_list.hpp>
#include <iostream>

#include "adapterGrToImg.hh"
#include "adapterImgtoGr.hh"

struct VertexProperties
{
  std::tuple<int, int, int> coord;
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
    boost::add_edge (2, 7, 7, g);

    int x = 0;
    for (int i = 0; i < 2; ++i)
    {
      for (int j = 0; j < 2; ++j)
      {
        for (int k = 0;  k < 2; ++k)
        {
          g[x].coord = std::make_tuple(i, j, k);
          g[x].value = i * i;
          ++x;
        }
      }
    }

    for (unsigned i = 0; i < boost::num_vertices(g); ++i)
      std::cout << "**** " << i << " -> " << std::get<0>(g[i].coord) << "; " << std::get<1>(g[i].coord) << "; " << std::get<2>(g[i].coord) << std::endl;

    AdapterGrToImg<std::tuple<int, int, int>, int, DirectedGraph> a(g);

    std::cout << std::endl;

    auto map = a.pixels();

    AdapterImgToGr<std::tuple<int, int, int>, int, AdapterGrToImg<std::tuple<int, int, int>, int, DirectedGraph>> a2(6, a);

    std::cout << "----- " << boost::num_edges(a2()) << std::endl;

    return 0;
 }
