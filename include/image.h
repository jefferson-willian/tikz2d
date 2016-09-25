#ifndef GRAPHICS_INCLUDE_IMAGE_H_
#define GRAPHICS_INCLUDE_IMAGE_H_

#include "graphics/include/shape.h"

#include <string>
#include <sstream>

namespace graphics {

class Image {
 private:
  std::stringstream latex_header;
  std::stringstream latex_content;
  std::stringstream latex_footer;

  double proportion_;

 public:
  Image(double proportion);
  ~Image() = default;

  void Add(const Shape* shape);

  const std::string Latex() const;
};

}  // namespace graphics

#endif  // GRAPHICS_INCLUDE_IMAGE_H_
