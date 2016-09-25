#include "graphics/include/line_segment.h"

using std::string;

namespace graphics {

const string LineSegment::latex_model(const string& x_1, const string& y_1,
    const string& x_2, const string& y_2) const {
  return "\\LineSegment{" + x_1 + "}{" + y_1 + "}{" + x_2 + "}{" + y_2 + "}{" + params_ + "};";
}

const string LineSegment::Latex(double proportion) const {
  return latex_model(std::to_string(a_.x() * proportion), std::to_string(a_.y() * proportion),
      std::to_string(b_.x() * proportion), std::to_string(b_.y() * proportion));
}

}  // namespace graphics
