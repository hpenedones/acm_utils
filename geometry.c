#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _point {
  double x;
  double y;
} point;

typedef struct _line_segment {
  point a;
  point b;
} line_segment;

typedef struct _circle {
  point center;
  double radius;
} circle;

point add(point a, point b) {
  point d;
  d.x = b.x + a.x;
  d.y = b.y + a.y;
  return d;
}

point diff(point a, point b) {
  point d;
  d.x = a.x - b.x;
  d.y = a.y - b.y;
  return d;
}

double norm(point v) { return sqrt(v.x * v.x + v.y * v.y); }

point scale(point a, double f) {
  point b;
  b.x = a.x * f;
  b.y = a.y * f;
  return b;
}

int side_of(point p, line_segment l) {
  point v1 = diff(p, l.a);
  point v2 = diff(l.b, l.a);

  double z = v1.x * v2.y - v1.y * v2.x;

  if (z < 0) return 1;
  if (z > 0) return -1;

  return 0;
}

point mid_point(line_segment l) {
  point mid;
  mid.x = (l.a.x + l.b.x) / 2;
  mid.y = (l.a.y + l.b.y) / 2;
  return mid;
}

int intersects_line(line_segment l1, line_segment l2) {
  int s1 = side_of(l1.a, l2);
  int s2 = side_of(l1.b, l2);

  if (s1 == 0 || s2 == 0 || (s1 != s2)) return 1;
  return 0;
}

int intersects_line_segment(line_segment l1, line_segment l2) {
  int i1 = intersects_line(l1, l2);
  int i2 = intersects_line(l2, l1);

  return (i1 && i2);
}

line_segment rotate90(line_segment l) {
  point d = diff(l.b, l.a);
  double tmp = d.x;
  d.x = -d.y;
  d.y = tmp;

  line_segment rot;
  rot.a = l.a;
  rot.b = add(l.a, d);
  return rot;
}

int intersects_circle(line_segment l, circle c) {
  line_segment ortho = rotate90(l);
  point v = diff(ortho.b, ortho.a);
  point r = scale(v, c.radius / norm(v));

  line_segment diameter;
  diameter.a = add(c.center, r);
  diameter.b = add(c.center, scale(r, -1));

  /*
  printf("%lf %lf %lf %lf\n", diameter.a.x, diameter.a.y, diameter.b.x,
  diameter.b.y); printf("%lf %lf %lf %lf\n", l.a.x, l.a.y, l.b.x, l.b.y);
  */

  return intersects_line_segment(diameter, l);
}

int main(int argc, char* argv[]) {
  circle c = {.center = {.x = 0, .y = 2}, .radius = 1};

  double y = atof(argv[1]);

  line_segment l = {.a = {.x = -2, .y = 0}, .b = {.x = 1, .y = y}};

  printf("%d\n", intersects_circle(l, c));

  return 0;
}
