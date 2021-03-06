#include "tikz2d/circle.h"

using std::string;

namespace tikz2d {

const string Circle::latex_model(const string& x, const string& y,
    const string& r, const string params) const {
  return "\\Circle{" + x + "}{" + y + "}{" + r + "}{" + params + "};";
}

const string Circle::Latex(double proportion) const {
  return latex_model(std::to_string(center_.x() * proportion), std::to_string(center_.y() * proportion),
      std::to_string(radius_ * proportion), params_);
}

}  // namespace tikz2d
