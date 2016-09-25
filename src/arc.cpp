#include "graphics/include/arc.h"

using std::string;

namespace graphics {

const string Arc::latex_model(const string& x, const string& y,
    const string& radians_start, const string& radians_end, const string& r,
    const string params) const {
  return "\\Arc{" + x + "}{" + y + "}{" + radians_start + "}{" + radians_end + "}{" + r + "}{" + params + "};";
}

const string Arc::Latex(double proportion) const {
  double start = start_.degree();
  double end = end_.degree();
  if (gl2d::util::cmpD(start, end) > 0)
    start -= 360;
  return latex_model(std::to_string(center_.x() * proportion), std::to_string(center_.y() * proportion),
      std::to_string(start), std::to_string(end), std::to_string(radius_ * proportion), "");
}

}  // namespace graphics
