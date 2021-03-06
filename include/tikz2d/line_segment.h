#ifndef GRAPHICS_INCLUDE_LINE_SEGMENT_H_
#define GRAPHICS_INCLUDE_LINE_SEGMENT_H_

#include "gl2d/line_segment.h"
#include "tikz2d/shape.h"

#include <string>

namespace tikz2d {

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
};

}  // namespace tikz2d

#endif  // GRAPHICS_INCLUDE_LINE_SEGMENT_H_
