#ifndef GRAPHICS_INCLUDE_LINE_SEGMENT_H_
#define GRAPHICS_INCLUDE_LINE_SEGMENT_H_

#include "gl2d/include/line_segment.h"
#include "graphics/include/shape.h"

#include <string>

namespace graphics {

class LineSegment : public gl2d::LineSegment, public Shape {
 private:
  const std::string latex_model(const std::string& x_1, const std::string& y_1,
      const std::string& x_2, const std::string& y_2) const;

 public:
  using gl2d::LineSegment::LineSegment;

  LineSegment(const gl2d::LineSegment& line) : gl2d::LineSegment(line) {}
  ~LineSegment() = default;

  const std::string Latex(double proportion) const override;

  void SetArrow() {
    add_param("->,>=stealth");
  }

  void SetColor(const std::string& color) {
    add_param(color);
  }

};

}  // namespace graphics

#endif  // GRAPHICS_INCLUDE_LINE_SEGMENT_H_
