#include "LineIntersectionChecker.h"

struct PointLI
{
	int x;
	int y;
};

// Given three colinear PointLIs p, q, r, the function checks if
// PointLI q lies on line segment 'pr'
bool onSegment(PointLI p, PointLI q, PointLI r)
{
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return true;

	return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientationLI(PointLI p, PointLI q, PointLI r)
{
	// See http://www.geeksforgeeks.org/orientation-3-ordered-PointLIs/
	// for details of below formula.
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;  // colinear

	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool doIntersect(PointLI p1, PointLI q1, PointLI p2, PointLI q2)
{
	// Find the four orientations needed for general and
	// special cases
	int o1 = orientationLI(p1, q1, p2);
	int o2 = orientationLI(p1, q1, q2);
	int o3 = orientationLI(p2, q2, p1);
	int o4 = orientationLI(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are colinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and p2 are colinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are colinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are colinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases
}

void LineIntersectionChecker::testLineIntersection(){
	struct PointLI p1 = { 1, 1 }, q1 = { 10, 1 };
	struct PointLI p2 = { 1, 2 }, q2 = { 10, 2 };

	doIntersect(p1, q1, p2, q2) ? cout << "Yes\n" : cout << "No\n";

	p1 = { 10, 0 }, q1 = { 0, 10 };
	p2 = { 0, 0 }, q2 = { 10, 10 };
	doIntersect(p1, q1, p2, q2) ? cout << "Yes\n" : cout << "No\n";

	p1 = { -5, -5 }, q1 = { 0, 0 };
	p2 = { 1, 1 }, q2 = { 10, 10 };
	doIntersect(p1, q1, p2, q2) ? cout << "Yes\n" : cout << "No\n";

}