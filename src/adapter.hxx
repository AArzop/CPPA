#include "adapter.hh"

#include <iostream>
#include <vector>

template<typename coordType, typename valueType, typename Graph>
Adapter<coordType, valueType, Graph>::Adapter(Graph g)
{
  for (unsigned i = 0; i < boost::num_vertices(g); i++)
    pixelMap[g[i].coord] = g[i].value;

  for (auto it = pixelMap.begin(); it != pixelMap.end(); ++it)
    std::cout << "***** " << it->first << "   " << it->second << std::endl;
}


template<typename coordType, typename valueType, typename Graph>
const valueType& Adapter<coordType, valueType, Graph>::operator() (point_type p) const
{
  return pixelMap[p];
}

template<typename coordType, typename valueType, typename Graph>
valueType& Adapter<coordType, valueType, Graph>::operator() (point_type p)
{
  return pixelMap[p];
}

template<typename coordType, typename valueType, typename Graph>
auto Adapter<coordType, valueType, Graph>::domain() const
{
  std::vector<coordType> ret;

  for (auto it = pixelMap.begin(); it != pixelMap.end(); ++it)
    ret.push_back(it->first);

  return ret;
}

template<typename coordType, typename valueType, typename Graph>
auto Adapter<coordType, valueType, Graph>::values() const
{
  std::vector<valueType> ret;

  for (auto it = pixelMap.begin(); it != pixelMap.end(); ++it)
    ret.push_back(it->second);

  return ret;
}

template<typename coordType, typename valueType, typename Graph>
auto Adapter<coordType, valueType, Graph>::values()
{
  std::vector<valueType> ret;

  for (auto it = pixelMap.begin(); it != pixelMap.end(); ++it)
    ret.push_back(it->second);

  return ret;
}

template<typename coordType, typename valueType, typename Graph>
auto Adapter<coordType, valueType, Graph>::pixels() const
{
  return pixelMap;
}

template<typename coordType, typename valueType, typename Graph>
auto Adapter<coordType, valueType, Graph>::pixels()
{
  return pixelMap;
}
