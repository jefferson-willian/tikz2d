#include "graphics/include/image.h"

#include <string>
#include <sstream>

using std::string;
using std::stringstream;

namespace graphics {

Image::Image(double proportion) : proportion_(proportion * 0.1) {
  latex_header << "\\documentclass[tikz,border=0.125cm]{standalone}\n"
    << "\\newcommand{\\Circle}[4]{\\draw [#4] (#1,#2) circle (#3);}\n"
    << "\\newcommand{\\LineSegment}[5]{\\draw [#5] (#1,#2) -- (#3,#4);}\n"
    << "\\newcommand{\\Vector}[5]{\\draw [#5] (#1,#2) -> (#3,#4);}\n"
    << "\\newcommand{\\Arc}[6]{\\draw[#6] (#1,#2) ++(#3:#5) arc (#3:#4:#5);}\n"
    << "\\begin{document}\n"
    << "\\begin{tikzpicture}\n";

  latex_footer << "\\end{tikzpicture}\n"
    << "\\end{document}\n";
}

void Image::Add(const Shape* shape) {
  latex_content << shape->Latex(proportion_) << std::endl;
}

const std::string Image::Latex() const {
  return latex_header.str() + latex_content.str() + latex_footer.str();
}

}  // namespace graphics
