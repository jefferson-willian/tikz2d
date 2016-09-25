#ifndef GRAPHICS_INCLUDE_CIRCLE_H_
#define GRAPHICS_INCLUDE_CIRCLE_H_

#include "gl2d/include/circle.h"
#include "graphics/include/shape.h"

#include <string>

namespace graphics {

class Circle : public gl2d::Circle, public Shape {
 private:
  const std::string latex_model(const std::string& x, const std::string& y,
      const std::string& r, const std::string params) const;

 public:
  using gl2d::Circle::Circle;
  ~Circle() = default;

  const std::string Latex(double proportion) const override;
};

}  // namespace graphics

#endif  // GRAPHICS_INCLUDE_CIRCLE_H_
