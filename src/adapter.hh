#pragma once

#include <boost/graph/adjacency_list.hpp>

#include "fwd.hh"

using coord = int;

template<class T>
class Adapter
{
public:
  using point_type = coord;
  using value_type = T;
  using pixel_type = std::pair<coord, T>;
  using reference = T&;
  using const_reference = const T&;

  Adapter(Graph_list g);
  Adapter(int i);

  const_reference operator() (point_type p) const
  {
    return buffer_[0];
  }

  reference operator() (point_type p) 
  {
    return buffer_[0];
  }

  auto domain() const 
  {

  }

  auto values() const 
  {

  }

  auto values() 
  {

  }

  auto pixels() const 
  {

  }

  auto pixels() 
  {

  }

private:
  std::unique_ptr<T[]> buffer_;

};

#include "adapter.hxx"
