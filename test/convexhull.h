typedef struct {
  float x;
  float y;
} point_t;

typedef point_t* point_ptr_t;

/* Three points are a counter-clockwise turn if ccw > 0, clockwise if
 * ccw < 0, and collinear if ccw = 0 because ccw is a determinant that
 * gives the signed area of the triangle formed by p1, p2 and p3.
 */
static float
ccw(point_t* p1, point_t* p2, point_t* p3)
{
  return (p2->x - p1->x)*(p3->y - p1->y) - (p2->y - p1->y)*(p3->x - p1->x);
}

int compare_func(const void *aa, const void *bb)
{
  point_t *a = (point_t *)aa;
  point_t *b = (point_t *)bb;
  return (a->x == b->x) ? 10e7*(a->y - b->y) : 10e7*(a->x - b->x);
}

/* Returns a list of points on the convex hull in counter-clockwise order.
 * Note: the last point in the returned list is the same as the first one.
 */
int
convex_hull(point_t* points, ssize_t npoints, point_ptr_t* hull)
{
  qsort(points, npoints, sizeof(point_t), compare_func);
  for(int i=0;i<npoints;i++)
    hull[i] = &points[i];

  int k = 0;

  /* lower hull */
  for (int i = 0; i < npoints; ++i) {
    while (k >= 2 && ccw(hull[k-2], hull[k-1], &points[i]) <= 0) --k;
    hull[k++] = &points[i];
  }

  /* upper hull */
  for (int i = npoints-2, t = k+1; i >= 0; --i) {
    while (k >= t && ccw(hull[k-2], hull[k-1], &points[i]) <= 0) --k;
    hull[k++] = &points[i];
  }
  return k;
}
