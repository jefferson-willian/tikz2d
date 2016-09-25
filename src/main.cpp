#include <iostream>
#include <fstream>
#include <vector>

#include <cstdlib>

#include "graphics/include/circle.h"
#include "graphics/include/line_segment.h"
#include "graphics/include/point.h"
#include "graphics/include/image.h"
#include "graphics/include/arc.h"
#include "graphics/include/dubin.h"

#include "gl2d/include/tangent.h"
#include "gl2d/include/line_segment.h"
#include "gl2d/include/distance.h"
#include "gl2d/include/point.h"
#include "gl2d/include/vector.h"
#include "gl2d/include/radians.h"

std::pair<gl2d::Circle, gl2d::Circle> TangentCircles(const gl2d::Point& orig,
    gl2d::Vector dir, double radius) {
  dir.Normalize();
  dir *= radius;

  dir.Rotate(gl2d::Radians::PI / 2);
  gl2d::Circle c1(orig + dir.Point(), radius);

  dir.Rotate(-gl2d::Radians::PI);
  gl2d::Circle c2(orig + dir.Point(), radius);

  return {c1, c2};
}

void NormalizeLine(gl2d::LineSegment* line) {
  gl2d::Vector v(line->a(), line->b());
  v.Normalize();
  line->b(line->a() + v.Point());
}

gl2d::Arc GetArc(const gl2d::Circle& c, const gl2d::Point& p1, const gl2d::Point& p2) {
  return gl2d::Arc(c, gl2d::Vector(c.Center(), p1).Angle(),
      gl2d::Vector(c.Center(), p2).Angle());
}

std::pair<gl2d::Circle, gl2d::Circle> GetMidCircle(const gl2d::Circle& c1, const gl2d::Circle& c2) {
  gl2d::Radians myangle = gl2d::Radians::Acos((gl2d::Distance(c1.Center(), c2.Center()) / 2) / (c1.Radius() * 2));
  graphics::Circle midCircle1, midCircle2;

  gl2d::Vector v(c1.Center(), c2.Center());
  v.Normalize();
  v *= 2 * c1.Radius();

  v.Rotate(myangle);
  midCircle1.Center(c1.Center() + v.Point());
  midCircle1.Radius(c1.Radius());

  v.Rotate(-2 * myangle);
  midCircle2.Center(c1.Center() + v.Point());
  midCircle2.Radius(c1.Radius());

  return {midCircle1, midCircle2};
}

int main(int argc, char** argv) {
  std::vector<gl2d::Circle> neighborhoods;

  int N = atoi(argv[1]);
  int K = atoi(argv[2]);
  int Q = atoi(argv[3]);
  int A = atoi(argv[4]);
  double R = atof(argv[5]);
  std::istream* input = new std::ifstream(argv[6]);

  for (int i = 0;i < N;i++) {
    double x, y, r;
    int id;
    *input >> id >> x >> y >> r;
    neighborhoods.emplace_back(gl2d::Circle(x, y, r));
  }

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      for (int u = 0; u < Q; ++u) {
        for (int v = 0; v < Q; ++v) {
          for (int a = 0; a < A; ++a) {
            for (int b = 0; b < A; ++b) {
              gl2d::Vector w1 = gl2d::Vector::i;
              gl2d::Vector w2 = gl2d::Vector::i;

              w1.Rotate(gl2d::Radians::TWOPI * ((double) u / Q));
              w1 *= neighborhoods[i].Radius();
              w1 += gl2d::Vector(neighborhoods[i].Center());

              w2.Rotate(gl2d::Radians::TWOPI * ((double) v / Q));
              w2 *= neighborhoods[j].Radius();
              w2 += gl2d::Vector(neighborhoods[j].Center());

              gl2d::Vector v1 = gl2d::Vector::i;
              gl2d::Vector v2 = gl2d::Vector::i;

              v1.Rotate(gl2d::Radians::TWOPI * ((double) a / A));
              v2.Rotate(gl2d::Radians::TWOPI * ((double) b / A));

              auto path = dubin::Path::ShortestPath(w1.Point(), v1, w2.Point(), v2, R);

              if (path)
                std::cout << path->Length() << std::endl;
//                std::cout << path->Length() << " = " << w1.Point().x() << " " << w1.Point().y() << " - " << v1.x() << " " << v1.y() << " | " << w2.Point().x() << " " << w2.Point().y() << " - " << v2.x() << " " << v2.y() << std::endl;
              else
                std::cout << 0 << std::endl;
              
              //dist[i][j][u][v][a][b] = dubinDubinsCurve::GetMinimumCurve(w1.Point(),
              //    v1, w2.Point(), v2, R).Length();
            }
          }
        }
      }
    }
  }

  return 0;

  graphics::Image img(10);

  graphics::LineSegment w1(gl2d::Point(0, 0), gl2d::Point(0, 1));
  graphics::LineSegment w2(gl2d::Point(1, 0), gl2d::Point(1, 1));

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

  NormalizeLine(&w1);
  NormalizeLine(&w2);

  gl2d::Point wayOutOrigin = w1.a();
  gl2d::Point wayInOrigin = w2.a();

  gl2d::Vector wayOutDirection = w1.Normal();
  gl2d::Vector wayInDirection = w2.Normal();

  wayOutDirection.Rotate(-(gl2d::Radians::PI / 2));
  wayInDirection.Rotate(-(gl2d::Radians::PI / 2));

  auto paths = dubin::Path::GetAllPaths(wayOutOrigin, wayOutDirection, wayInOrigin, wayInDirection, R);

  img.Add(&w1);
  img.Add(&w2);

  for (auto path : paths) {
    img.Add(new graphics::Arc(path.out_));
    if (path.is_csc_)
      img.Add(new graphics::LineSegment(path.line_segment_));
    else
      img.Add(new graphics::Arc(path.mid_circle_));
    img.Add(new graphics::Arc(path.in_));
  }

  std::cout << img.Latex() << '\n';

  return 0;

  // Start DUBINS
  auto outCircles = TangentCircles(wayOutOrigin, wayOutDirection, 1);
  auto inCircles = TangentCircles(wayInOrigin, wayInDirection, 1);

  std::vector<gl2d::LineSegment> lines;

  lines = gl2d::Tangent(outCircles.second, inCircles.second);
  if (lines.size() >= 1) {
    auto line = graphics::LineSegment(lines[0]);
    img.Add(new graphics::LineSegment(line));

    auto arc_out = GetArc(outCircles.second, line.a(), wayOutOrigin);
    auto arc_in = GetArc(inCircles.second, wayInOrigin, line.b());

    img.Add(new graphics::Arc(arc_out));
    img.Add(new graphics::Arc(arc_in));
  }

  lines = gl2d::Tangent(outCircles.first, inCircles.first);
  if (lines.size() >= 2) {
    auto line = graphics::LineSegment(lines[1]);
    img.Add(new graphics::LineSegment(line));

    auto arc_out = GetArc(outCircles.first, wayOutOrigin, line.a());
    auto arc_in = GetArc(inCircles.first, line.b(), wayInOrigin);

    img.Add(new graphics::Arc(arc_out));
    img.Add(new graphics::Arc(arc_in));
  }

  lines = gl2d::Tangent(outCircles.second, inCircles.first);
  if (lines.size() >= 3) {
    auto line = graphics::LineSegment(lines[2]);
    img.Add(new graphics::LineSegment(line));

    auto arc_out = GetArc(outCircles.second, line.a(), wayOutOrigin);
    auto arc_in = GetArc(inCircles.first, line.b(), wayInOrigin);

    img.Add(new graphics::Arc(arc_out));
    img.Add(new graphics::Arc(arc_in));
  }

  lines = gl2d::Tangent(outCircles.first, inCircles.second);
  if (lines.size() >= 4) {
    auto line = graphics::LineSegment(lines[3]);
    img.Add(new graphics::LineSegment(line));

    auto arc_out = GetArc(outCircles.first, wayOutOrigin, line.a());
    auto arc_in = GetArc(inCircles.second, wayInOrigin, line.b());

    img.Add(new graphics::Arc(arc_out));
    img.Add(new graphics::Arc(arc_in));
  }

  /*
  img.Add(&arc1);
  img.Add(&arc2);
  img.Add(&arc3);
  img.Add(&arc4);
  img.Add(&arc5);
  img.Add(&arc6);
  img.Add(&arc7);
  img.Add(&arc8);
  */

  img.Add(&w1);
  img.Add(&w2);

  auto c1 = GetMidCircle(outCircles.first, inCircles.first).first;
  auto c2 = GetMidCircle(outCircles.second, inCircles.second).second;

  //img.Add(&c1);
  //img.Add(&c2);


  //img.Add(&outCircles.first);
  //img.Add(&outCircles.second);
  //img.Add(&inCircles.first);
  //img.Add(&inCircles.second);
  /*
  auto lines = gl2d::Tangent(outCircles.first, inCircles.first);
  img.Add(new graphics::LineSegment(lines[2]));
  img.Add(new graphics::LineSegment(lines[3]));
  */

  std::cout << img.Latex() << '\n';

  return 0;
}
