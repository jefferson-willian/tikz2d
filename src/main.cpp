#include <iostream>
#include <fstream>
#include <vector>

#include <cstdlib>

#include "tikz2d/circle.h"
#include "tikz2d/line_segment.h"
#include "tikz2d/point.h"
#include "tikz2d/image.h"
#include "tikz2d/arc.h"

#include "gl2d/tangent.h"
#include "gl2d/line_segment.h"
#include "gl2d/distance.h"
#include "gl2d/point.h"
#include "gl2d/vector.h"
#include "gl2d/radians.h"

int main(int argc, char** argv) {

  tikz2d::Image img(10);

  tikz2d::LineSegment w1(gl2d::Point(0, 0), gl2d::Point(0, 1));
  tikz2d::LineSegment w2(gl2d::Point(1, 0), gl2d::Point(1, 1));

  srand(time(0));

  /*
  w1.a(gl2d::Point(rand() % 20 - 10, rand() % 20 - 10));
  w1.b(gl2d::Point(rand() % 20 - 10, rand() % 20 - 10));
  w2.a(gl2d::Point(rand() % 20 - 10, rand() % 20 - 10));
  w2.b(gl2d::Point(rand() % 20 - 10, rand() % 20 - 10));
  */

  w1.SetArrow();
  w1.SetColor("red");
  w2.SetArrow();
  w2.SetColor("blue");

  gl2d::Point wayOutOrigin = w1.a();
  gl2d::Point wayInOrigin = w2.a();

  gl2d::Vector wayOutDirection = w1.Normal();
  gl2d::Vector wayInDirection = w2.Normal();

  wayOutDirection.Rotate(-(gl2d::Radians::PI / 2));
  wayInDirection.Rotate(-(gl2d::Radians::PI / 2));

  img.Add(&w1);
  img.Add(&w2);

  std::cout << img.Latex() << '\n';

  return 0;
}
