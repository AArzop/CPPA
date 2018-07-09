#include <boost/graph/adjacency_list.hpp>
#include <iostream>

#include "adapterGrToImg.hh"
#include "adapterImgtoGr.hh"

struct VertexProperties
{
  std::pair<int, int> coord; // 2D coordinates
  unsigned char value; // white and black image
};

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, VertexProperties> DirectedGraph;

template <class Image, class Predicate, typename T>
void fill_if(Image& img, Predicate pred, T v)
{
  static_assert(std::is_convertible<T, typename Image::value_type>::value, "");

  for (auto& [p,value] : img.pixels())
    if (pred(p))
    {
      std::cout << "--- " << (int)value << std::endl;
      value = v;
    }
}

int main()
{
    // Graph creation
    DirectedGraph g;
    boost::add_edge (0, 1, g);
    boost::add_edge (0, 3, g);
    boost::add_edge (1, 2, g);
    boost::add_edge (2, 3, g);
    boost::add_edge (3, 1, g);
    boost::add_edge (1, 3, g);
    boost::add_edge (1, 4, g);
    boost::add_edge (4, 5, g);
    boost::add_edge (2, 8, g);

    // Set vertex's properties
    g[0].coord = std::make_pair(0, 0);
    g[0].value = 0;
    
    g[1].coord = std::make_pair(1, 0);
    g[1].value = 0;
    
    g[2].coord = std::make_pair(2, 0);
    g[2].value = 0;
    
    g[3].coord = std::make_pair(0, 1);
    g[3].value = 56;
    
    g[4].coord = std::make_pair(1, 1);
    g[4].value = 215;
    
    g[5].coord = std::make_pair(2, 1);
    g[5].value = 127;
    
    g[6].coord = std::make_pair(0, 2);
    g[6].value = 255;
    
    g[7].coord = std::make_pair(1, 2);
    g[7].value = 255;

    g[8].coord = std::make_pair(2, 2);
    g[8].value = 42;

    
    AdapterGrToImg<std::pair<int, int>, unsigned char, DirectedGraph> a(g);

    for (auto [p, v]: a.pixels())
      std::cout << (int) v << std::endl;

    fill_if(a, [](std::pair<int, int> p) { return p.first == 0; }, 55);
    
    std::cout << "\n\n";

    for (auto [p, v]: a.pixels())
      std::cout << (int) v << std::endl;

    return 0;
 }
