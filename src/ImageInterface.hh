#pragma once

using coord = int;

template<class T>
class ImageInterface
{
public:
  using point_type = coord;
  using value_type = T;
  using pixel_type = std::pair<point_type, T>;
  using reference = T&;
  using const_reference = const T&;

  virtual const_reference operator() (point_type p) const = 0;
  virtual reference operator() (point_type p) = 0;

  virtual auto domain() const = 0;

  virtual auto values() const = 0;
  virtual auto values() = 0;

  virtual auto pixels() const = 0;
  virtual auto pixels() = 0;
  
protected:
  std::unique_ptr<T[]> buffer_;

};
