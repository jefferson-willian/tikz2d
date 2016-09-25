#ifndef GRAPHICS_INCLUDE_ARC_H_
#define GRAPHICS_INCLUDE_ARC_H_

#include "gl2d/include/arc.h"
#include "graphics/include/shape.h"

#include <string>

namespace graphics {

class Arc : public gl2d::Arc, public Shape {
 private:
  const std::string latex_model(const std::string& x, const std::string& y,
      const std::string& radians_start, const std::string& radians_end,
      const std::string& r, const std::string params) const;

 public:
  using gl2d::Arc::Arc;

  Arc(const gl2d::Arc& arc) : gl2d::Arc(arc) {}
  ~Arc() = default;

  const std::string Latex(double proportion) const override;
};

}  // namespace graphics

#endif  // GRAPHICS_INCLUDE_ARC_H_
