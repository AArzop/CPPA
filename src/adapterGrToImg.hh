#pragma once

#include <boost/property_map/property_map.hpp>
#include <map>

template<typename coordType, typename valueType, typename Graph>
class AdapterGrToImg
{
public:
  using point_type = coordType;
  using value_type = valueType;
  using pixel_type = std::pair<coordType, valueType>;
  using reference = valueType&;
  using const_reference = const valueType&;
  
  AdapterGrToImg(Graph g);
  
  const_reference operator() (point_type p) const;
  reference operator() (point_type p);

  auto domain() const;

  auto values() const;
  auto values();

  auto pixels() const;
  auto pixels();

private:
  std::map<coordType, valueType> pixelMap;
};

#include "adapterGrToImg.hxx"
