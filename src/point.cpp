#include "graphics/include/point.h"

using std::string;

namespace graphics {

const string Point::latex_model(const string& x, const string& y,
    const string& r, const string params) const {
  return "\\Circle{" + x + "}{" + y + "}{" + r + "}{" + params + "};";
}

const string Point::Latex(double proportion) const {
  return latex_model(std::to_string(x_), std::to_string(y_),
      std::to_string(0.1), "fill");
}

}  // namespace graphics
