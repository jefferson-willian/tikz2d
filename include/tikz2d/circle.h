#ifndef GRAPHICS_INCLUDE_CIRCLE_H_
#define GRAPHICS_INCLUDE_CIRCLE_H_

#include "gl2d/circle.h"
#include "tikz2d/shape.h"

#include <string>

namespace tikz2d {

class Circle : public gl2d::Circle, public Shape {
 private:
  const std::string latex_model(const std::string& x, const std::string& y,
      const std::string& r, const std::string params) const;

 public:
  using gl2d::Circle::Circle;

  Circle(const gl2d::Circle& circle) : gl2d::Circle(circle) {}
  ~Circle() = default;

  const std::string Latex(double proportion) const override;
};

}  // namespace tikz2d

#endif  // GRAPHICS_INCLUDE_CIRCLE_H_
