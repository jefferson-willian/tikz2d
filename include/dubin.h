#ifndef GRAPHICS_INCLUDE_DUBIN_H_
#define GRAPHICS_INCLUDE_DUBIN_H_

#include "gl2d/include/arc.h"
#include "gl2d/include/circle.h"
#include "gl2d/include/point.h"
#include "gl2d/include/vector.h"
#include "gl2d/include/line_segment.h"

#include <string>
#include <vector>
#include <sstream>

namespace dubin {

class Path {
 private:
 public:
  gl2d::Arc out_;
  gl2d::Arc in_;
  gl2d::Arc mid_circle_;
  gl2d::LineSegment line_segment_;

  bool is_csc_;

 public:
  Path() = default;
  ~Path() = default;

  double Length() const {
    return out_.Length() + in_.Length() + (is_csc_ ? line_segment_.Length()
      : mid_circle_.Length());
  }

  static std::vector<Path> GetAllPaths(const gl2d::Point& a, const gl2d::Vector& d1,
      const gl2d::Point& b, const gl2d::Vector& d2, double curvature);

  static Path* ShortestPath(const gl2d::Point& a, const gl2d::Vector& d1,
      const gl2d::Point& b, const gl2d::Vector& d2, double curvature);
};

}  // namespace dubin

#endif  // GRAPHICS_INCLUDE_DUBIN_H_
