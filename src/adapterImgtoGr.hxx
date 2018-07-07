#include <iostream>
#include <tuple>
#include <vector>

#include "adapterImgtoGr.hh"

template<typename coordType, typename valueType, class Image>
AdapterImgToGr<coordType, valueType, Image>::AdapterImgToGr(unsigned connexite, Image img):
  connexite_(connexite)
{
  if (connexite != 2 && connexite != 4 && connexite != 8 && connexite != 6 
      && connexite != 26)
  {
    std::cerr << "Invalid connexite\n";
    graph = nullptr;
    return;
  }

  graph = std::make_unique<Graph>();
  createGraph(img);
}

template<typename coordType, typename valueType, class Image>
void AdapterImgToGr<coordType, valueType, Image>::createGraph(Image img)
{
  for (auto& [k, v]: img.pixels())
  {
    property_map[k] = v;
    unsigned id = boost::add_vertex(*graph);
    idCoordMap[id] = k;
  }
  
  switch (connexite_)
  {
    case 2:
      createEdge2();
      break;

    case 4:
      createEdge4();
      break;

    case 6:
      createEdge6();
      break;

    case 8:
      createEdge8();
      break;

    case 26:
      createEdge26();
      break;
  }
}

template<typename coordType, typename valueType, class Image>
void AdapterImgToGr<coordType, valueType, Image>::createEdge2()
{
  unsigned size = boost::num_vertices(*graph);
  for (unsigned i = 0; i < size; ++i)
  {
    for (unsigned j = i + 1; j < size; ++j)
    {
      int diff = idCoordMap[i] - idCoordMap[j];
      if (diff == 1 || diff == -1)
        boost::add_edge(i, j, *graph);
    }
  }
}

template<typename coordType, typename valueType, class Image>
void AdapterImgToGr<coordType, valueType, Image>::createEdge4()
{
  unsigned size = boost::num_vertices(*graph);
  for (unsigned i = 0; i < size; ++i)
  {
    for (unsigned j = i + 1; j < size; ++j)
    {
      auto coord_i = idCoordMap[i];
      auto coord_j = idCoordMap[j];
      if (coord_i.first == coord_j.first)
      {
        if (coord_i.second + 1 == coord_j.second || coord_i.second == coord_j.second + 1)
          boost::add_edge(i, j, *graph);
      }
      else if (coord_i.second == coord_j.second)
        if (coord_i.first + 1 == coord_j.first || coord_i.first == coord_j.first + 1)
          boost::add_edge(i, j, *graph);
    }
  }
}

void generateVect8(std::vector<std::tuple<int, int, int>> &vect)
{
  vect.emplace_back(1, 0, 0);
  vect.emplace_back(-1, 0, 0);
  vect.emplace_back(0, 1, 0);
  vect.emplace_back(0, -1, 0);
  vect.emplace_back(0, 0, 1);
  vect.emplace_back(0, 0, -1);
}

// In this case, coordType should be a tuple of 3 int
template<typename coordType, typename valueType, class Image>
void AdapterImgToGr<coordType, valueType, Image>::createEdge6()
{
  std::vector<std::tuple<int, int, int>> vect;
  generateVect8(vect);

  unsigned size = boost::num_vertices(*graph);
  for (unsigned i = 0; i < size; ++i)
  {
    auto c1 = idCoordMap[i];
    for (unsigned j = i + 1; j < size; ++j)
    {
       auto c2 = idCoordMap[j];
      for (auto [a, b, c]: vect)
      {
        if (std::get<0>(c1) + a == std::get<0>(c2) && 
            std::get<1>(c1) + b == std::get<1>(c2) && 
            std::get<2>(c1) + c == std::get<2>(c2))
        {
          boost::add_edge(i, j, *graph);
          continue;
        }
      }
    }
  }
}

template<typename coordType, typename valueType, class Image>
void AdapterImgToGr<coordType, valueType, Image>::createEdge8()
{
 
}

void generateVect26(std::vector<std::tuple<int, int, int>> &vect)
{
  vect.emplace_back(-1, -1, -1);
  vect.emplace_back(-1, -1, 0);
  vect.emplace_back(-1, -1, 1);
  vect.emplace_back(-1, 0, -1);
  vect.emplace_back(-1, 0, 0);
  vect.emplace_back(-1, 0, 1);
  vect.emplace_back(-1, 1, -1);
  vect.emplace_back(-1, 1, 0);
  vect.emplace_back(-1, 1, 1);

  vect.emplace_back(0, -1, -1);
  vect.emplace_back(0, -1, 0);
  vect.emplace_back(0, -1, 1);
  vect.emplace_back(0, 0, -1);
  vect.emplace_back(0, 0, 1);
  vect.emplace_back(0, 1, -1);
  vect.emplace_back(0, 1, 0);
  vect.emplace_back(0, 1, 1);

  vect.emplace_back(1, -1, -1);
  vect.emplace_back(1, -1, 0);
  vect.emplace_back(1, -1, 1);
  vect.emplace_back(1, 0, -1);
  vect.emplace_back(1, 0, 0);
  vect.emplace_back(1, 0, 1);
  vect.emplace_back(1, 1, -1);
  vect.emplace_back(1, 1, 0);
  vect.emplace_back(1, 1, 1);
}

template<typename coordType, typename valueType, class Image>
void AdapterImgToGr<coordType, valueType, Image>::createEdge26()
{
  std::vector<std::tuple<int, int, int>> vect;
  generateVect26(vect);

  unsigned size = boost::num_vertices(*graph);
  for (unsigned i = 0; i < size; ++i)
  {
    auto c1 = idCoordMap[i];
    for (unsigned j = i + 1; j < size; ++j)
    {
       auto c2 = idCoordMap[j];
      for (auto [a, b, c]: vect)
      {
        if (std::get<0>(c1) + a == std::get<0>(c2) && 
            std::get<1>(c1) + b == std::get<1>(c2) && 
            std::get<2>(c1) + c == std::get<2>(c2))
        {
          boost::add_edge(i, j, *graph);
          continue;
        }
      }
    }
  }
}

