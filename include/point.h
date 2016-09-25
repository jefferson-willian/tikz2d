#ifndef GRAPHICS_INCLUDE_POINT_H_
#define GRAPHICS_INCLUDE_POINT_H_

#include "gl2d/include/point.h"
#include "graphics/include/shape.h"

#include <string>

namespace graphics {

class Point : public gl2d::Point, public Shape {
 private:
  const std::string latex_model(const std::string& x, const std::string& y,
      const std::string& r, const std::string params) const;

 public:
  using gl2d::Point::Point;
  ~Point() = default;

  const std::string Latex(double proportion) const override;
};

}  // namespace graphics

#endif  // GRAPHICS_INCLUDE_POINT_H_
