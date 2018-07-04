#pragma once

#include <boost/graph/adjacency_list.hpp>

#include "ImageInterface.hh"

class Adapter: public ImageInterface
{
public:
  using boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph_list;

  Adapter(Graph_list &g);

private:


};
