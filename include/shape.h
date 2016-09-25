#ifndef GRAPHICS_INCLUDE_SHAPE_H_
#define GRAPHICS_INCLUDE_SHAPE_H_

#include <string>

namespace graphics {

class Shape {
 protected:
  std::string params_;

  void add_param(const std::string param) {
    if (!params_.empty())
      params_ += ",";
    params_ += param;
  }

 public:
  Shape() = default;
  virtual ~Shape() = default;

  virtual const std::string Latex(double proportion) const = 0;
};

}  // namespace graphics

#endif  // GRAPHICS_INCLUDE_SHAPE_H_
