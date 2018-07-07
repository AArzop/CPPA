#include <iostream>

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

}

template<typename coordType, typename valueType, class Image>
void AdapterImgToGr<coordType, valueType, Image>::createEdge6()
{

}

template<typename coordType, typename valueType, class Image>
void AdapterImgToGr<coordType, valueType, Image>::createEdge8()
{

}

template<typename coordType, typename valueType, class Image>
void AdapterImgToGr<coordType, valueType, Image>::createEdge26()
{

}
