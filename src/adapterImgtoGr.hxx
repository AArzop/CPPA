#include <iostream>
#include <tuple>
#include <vector>

#include "adapterImgtoGr.hh"

template<typename coordType, typename valueType, class Image>
AdapterImgToGr<coordType, valueType, Image>::AdapterImgToGr(unsigned connexite, Image img):
  connexite_(connexite)
{
  graph = std::make_unique<Graph>();
  img = img;
  std::cerr << "Invalid type\n";
}

template<typename valueType, class Image>
AdapterImgToGr<int, valueType, Image>::AdapterImgToGr(unsigned connexite, Image img):
  connexite_(connexite)
{
  graph = std::make_unique<Graph>();
  if (connexite != 2)
  {
    std::cerr << "Invalid connexite\n";
    return;
  }
  createGraph(img);
}

template<typename valueType, class Image>
AdapterImgToGr<std::pair<int, int>, valueType, Image>::AdapterImgToGr(unsigned connexite, Image img):
  connexite_(connexite)
{
  graph = std::make_unique<Graph>();
  if (connexite != 4 && connexite != 8)
  {
    std::cerr << "Invalid connexite\n";
    return;
  }
  createGraph(img);
}

template<typename valueType, class Image>
AdapterImgToGr<std::tuple<int, int, int>, valueType, Image>::AdapterImgToGr(unsigned connexite, Image img):
  connexite_(connexite)
{
  graph = std::make_unique<Graph>();
  if (connexite != 6 && connexite != 26)
  {
    std::cerr << "Invalid connexite\n";
    return;
  }
  createGraph(img);
}






template<typename valueType, class Image>
void AdapterImgToGr<int, valueType, Image>::createGraph(Image img)
{
  for (auto&& [k, v]: img.pixels())
  {
    struct Vertex vertex;
    vertex.coord = k;
    vertex.value = v;

    unsigned id = boost::add_vertex(*graph);
    propertyMap[id] = vertex;
  }
  createEdge2();  
}

template<typename valueType, class Image>
void AdapterImgToGr<std::pair<int, int>, valueType, Image>::createGraph(Image img)
{
  for (auto&& [k, v]: img.pixels())
  {
    struct Vertex vertex;
    vertex.coord = k;
    vertex.value = v;

    unsigned id = boost::add_vertex(*graph);
    propertyMap[id] = vertex;
  }
  if (connexite_ == 4)
    createEdge4();
  else
    createEdge8();  
}

template<typename valueType, class Image>
void AdapterImgToGr<std::tuple<int, int, int>, valueType, Image>::createGraph(Image img)
{
  for (auto&& [k, v]: img.pixels())
  {
    struct Vertex vertex;
    vertex.coord = k;
    vertex.value = v;

    unsigned id = boost::add_vertex(*graph);
    propertyMap[id] = vertex;
  }
  if (connexite_ == 6)
    createEdge6();
  else
    createEdge26();  
}






template<typename valueType, class Image>
void AdapterImgToGr<int, valueType, Image>::createEdge2()
{
  unsigned size = boost::num_vertices(*graph);
  for (unsigned i = 0; i < size; ++i)
  {
    for (unsigned j = i + 1; j < size; ++j)
    {
      int diff = propertyMap[i].coord - propertyMap[j].coord;
      if (diff == 1 || diff == -1)
        boost::add_edge(i, j, *graph);
    }
  }
}


void check_conex_8(std::pair<int, int> coord_i, std::pair<int, int> coord_j, int i, int j, Graph& graph)
{                                                                               
  if (coord_i.first + 1 == coord_j.first || coord_i.first == coord_j.first + 1) 
    if (coord_i.second + 1 == coord_j.second || coord_i.second == coord_j.second + 1)
      boost::add_edge(i, j, graph);                                             
} 

void check_conex_4(std::pair<int, int> coord_i, std::pair<int, int> coord_j, int i, int j, Graph& graph)
{                                                                               
  if (coord_i.first == coord_j.first)                                            
  {                                                                              
    if (coord_i.second + 1 == coord_j.second || coord_i.second - 1 == coord_j.second)
      boost::add_edge(i, j, graph);                                             
  }                                                                             
  else if (coord_i.second == coord_j.second)                                    
  {                                                                             
    if (coord_i.first + 1 == coord_j.first || coord_i.first == coord_j.first + 1)
     boost::add_edge(i, j, graph);                                              
  }                                                                             
}

template<typename valueType, class Image>
void AdapterImgToGr<std::pair<int, int>, valueType, Image>::createEdge4()
{
  unsigned size = boost::num_vertices(*graph);
  for (unsigned i = 0; i < size; ++i)
  {
    for (unsigned j = i + 1; j < size; ++j)
    {
      auto& coord_i = propertyMap[i].coord;
      auto& coord_j = propertyMap[j].coord;
      check_conex_4(coord_i, coord_j, i, j, *graph);
    }
  }
}

void generateVect6(std::vector<std::tuple<int, int, int>> &vect)
{
  vect.emplace_back(1, 0, 0);
  vect.emplace_back(-1, 0, 0);
  vect.emplace_back(0, 1, 0);
  vect.emplace_back(0, -1, 0);
  vect.emplace_back(0, 0, 1);
  vect.emplace_back(0, 0, -1);
}

template<typename valueType, class Image>
void AdapterImgToGr<std::tuple<int, int, int>, valueType, Image>::createEdge6()
{
  std::vector<std::tuple<int, int, int>> vect;
  generateVect6(vect);

  unsigned size = boost::num_vertices(*graph);
  for (unsigned i = 0; i < size; ++i)
  {
    auto& c1 = propertyMap[i].coord;
    for (unsigned j = i + 1; j < size; ++j)
    {
      auto& c2 = propertyMap[j].coord;
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

template<typename valueType, class Image>
void AdapterImgToGr<std::pair<int, int>, valueType, Image>::createEdge8()
{
  unsigned size = boost::num_vertices(*graph);                                     
  for (unsigned i = 0; i < size; ++i)                                              
  {                                                                                
    for (unsigned j = i + 1; j < size; ++j)                                        
    {                                                                              
      auto& coord_i = propertyMap[i].coord;                                        
      auto& coord_j = propertyMap[j].coord;                                        
      check_conex_4(coord_i, coord_j, i, j, *graph); 
      check_conex_8(coord_i, coord_j, i, j, *graph); 
    }                                                                              
  }      
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

template<typename valueType, class Image>
void AdapterImgToGr<std::tuple<int, int, int>, valueType, Image>::createEdge26()
{
  std::vector<std::tuple<int, int, int>> vect;
  generateVect26(vect);

  unsigned size = boost::num_vertices(*graph);
  for (unsigned i = 0; i < size; ++i)
  {
    auto& c1 = propertyMap[i].coord;
    for (unsigned j = i + 1; j < size; ++j)
    {
      auto& c2 = propertyMap[j].coord;
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

