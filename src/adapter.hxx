#include "adapter.hh"

#include <iostream>

template<class T>
Adapter<T>::Adapter(Graph_list g)
{
  std::cout << "OK\n";
}

template<typename T>
Adapter<T>::Adapter(int i)
{
  std::cout << i << std::endl;
}
