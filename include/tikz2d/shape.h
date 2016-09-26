#ifndef GRAPHICS_INCLUDE_SHAPE_H_
#define GRAPHICS_INCLUDE_SHAPE_H_

#include <string>

namespace tikz2d {

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

  virtual void SetColor(const std::string& color) {
    add_param(color);
  }
};

}  // namespace tikz2d

#endif  // GRAPHICS_INCLUDE_SHAPE_H_
