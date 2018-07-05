#include <boost/graph/adjacency_list.hpp>
#include <iostream>

#include "adapter.hh"

struct VertexProperties
{
  int coord;
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

    for (unsigned i = 0; i < boost::num_vertices(g); i++)
    {
      g[i].coord = i; 
      g[i].value = i * i;
    } 

    std::pair<edge_iterator, edge_iterator> ei = edges(g);
 
    std::cout << "Number of edges = " << num_edges(g) << "\n";
    std::cout << "Edge list:\n";
 
    std::copy( ei.first, ei.second,
                std::ostream_iterator<boost::adjacency_list<>::edge_descriptor>{
                    std::cout, "\n"});
 
    std::cout << std::endl;
    
    Adapter<int, int, DirectedGraph> a(g);

    std::cout << std::endl;

    auto map = a.pixels();

    for (auto [k, v]: map)
      std::cout << " -> " << k << "   " << v << std::endl;

    return 0;
 }
