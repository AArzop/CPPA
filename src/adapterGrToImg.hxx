#include "adapterGrToImg.hh"

#include <range/v3/view/zip.hpp>

#include <iostream>

template<typename coordType, typename valueType, typename Graph>
AdapterGrToImg<coordType, valueType, Graph>::AdapterGrToImg(Graph g)
{
  for (unsigned i = 0; i < boost::num_vertices(g); i++)
  {
    coords.push_back(g[i].coord);
    value.push_back(g[i].value);
  }
}


template<typename coordType, typename valueType, typename Graph>
const valueType& AdapterGrToImg<coordType, valueType, Graph>::operator() (point_type p) const
{
  for (unsigned i = 0; i < coords.size(); ++i)
  {
    if (coords[i] == p)
      return value[i];
  }
  return value[0];
}

template<typename coordType, typename valueType, typename Graph>
valueType& AdapterGrToImg<coordType, valueType, Graph>::operator() (point_type p)
{
  for (unsigned i = 0; i < coords.size(); ++i)
  {
    if (coords[i] == p)
      return value[i];
  }
  return value[0];
}

template<typename coordType, typename valueType, typename Graph>
auto AdapterGrToImg<coordType, valueType, Graph>::domain() const
{
  return coords;
}

template<typename coordType, typename valueType, typename Graph>
auto AdapterGrToImg<coordType, valueType, Graph>::values() const
{
  return value;
}

template<typename coordType, typename valueType, typename Graph>
auto AdapterGrToImg<coordType, valueType, Graph>::values()
{
  return value;
}

template<typename coordType, typename valueType, typename Graph>
auto AdapterGrToImg<coordType, valueType, Graph>::pixels() const
{
  return ranges::view::zip(coords, value);
}

template<typename coordType, typename valueType, typename Graph>
auto AdapterGrToImg<coordType, valueType, Graph>::pixels()
{
  return ranges::view::zip(coords, value);
}
