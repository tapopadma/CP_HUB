#include "ConvexHullEfficient.h"

struct PointS
{
	int x, y;
};

// A globle PointS needed for  sorting PointSs with reference
// to  the first PointS Used in compare function of qsort()
PointS p0;

// A utility function to find next to top in a stack
PointS nextToTop(stack<PointS> &S)
{
	PointS p = S.top();
	S.pop();
	PointS res = S.top();
	S.push(p);
	return res;
}

// A utility function to swap two PointSs
int swap(PointS &p1, PointS &p2)
{
	PointS temp = p1;
	p1 = p2;
	p2 = temp;
	return 1;
}

// A utility function to return square of distance
// between p1 and p2
int distSq(PointS p1, PointS p2)
{
	return (p1.x - p2.x)*(p1.x - p2.x) +
		(p1.y - p2.y)*(p1.y - p2.y);
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(PointS p, PointS q, PointS r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;  // colinear
	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// A function used by library function qsort() to sort an array of
// PointSs with respect to the first PointS
int compare(const void *vp1, const void *vp2)
{
	PointS *p1 = (PointS *)vp1;
	PointS *p2 = (PointS *)vp2;

	// Find orientation
	int o = orientation(p0, *p1, *p2);
	if (o == 0)
		return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;

	return (o == 2) ? -1 : 1;
}

// Prints convex hull of a set of n PointSs.
void convexHullEff(PointS PointSs[], int n)
{
	// Find the bottommost PointS
	int ymin = PointSs[0].y, min = 0;
	for (int i = 1; i < n; i++)
	{
		int y = PointSs[i].y;

		// Pick the bottom-most or chose the left
		// most PointS in case of tie
		if ((y < ymin) || (ymin == y &&
			PointSs[i].x < PointSs[min].x))
			ymin = PointSs[i].y, min = i;
	}

	// Place the bottom-most PointS at first position
	swap(PointSs[0], PointSs[min]);

	// Sort n-1 PointSs with respect to the first PointS.
	// A PointS p1 comes before p2 in sorted ouput if p2
	// has larger polar angle (in counterclockwise
	// direction) than p1
	p0 = PointSs[0];
	qsort(&PointSs[1], n - 1, sizeof(PointS), compare);

	// If two or more PointSs make same angle with p0,
	// Remove all but the one that is farthest from p0
	// Remember that, in above sorting, our criteria was
	// to keep the farthest PointS at the end when more than
	// one PointSs have same angle.
	int m = 1; // Initialize size of modified array
	for (int i = 1; i<n; i++)
	{
		// Keep removing i while angle of i and i+1 is same
		// with respect to p0
		while (i < n - 1 && orientation(p0, PointSs[i],
			PointSs[i + 1]) == 0)
			i++;


		PointSs[m] = PointSs[i];
		m++;  // Update size of modified array
	}

	// If modified array of PointSs has less than 3 PointSs,
	// convex hull is not possible
	if (m < 3) return;

	// Create an empty stack and push first three PointSs
	// to it.
	stack<PointS> S;
	S.push(PointSs[0]);
	S.push(PointSs[1]);
	S.push(PointSs[2]);

	// Process remaining n-3 PointSs
	for (int i = 3; i < m; i++)
	{
		// Keep removing top while the angle formed by
		// PointSs next-to-top, top, and PointSs[i] makes
		// a non-left turn
		while (orientation(nextToTop(S), S.top(), PointSs[i]) != 2)
			S.pop();
		S.push(PointSs[i]);
	}

	// Now stack has the output PointSs, print contents of stack
	while (!S.empty())
	{
		PointS p = S.top();
		cout << "(" << p.x << ", " << p.y << ")" << endl;
		S.pop();
	}
}

void ConvexHullEfficient::testConvexHullEfficient(){
	PointS PointSs[] = { { 0, 3 }, { 1, 1 }, { 2, 2 }, { 4, 4 },
	{ 0, 0 }, { 1, 2 }, { 3, 1 }, { 3, 3 } };
	int n = sizeof(PointSs) / sizeof(PointSs[0]);
	convexHullEff(PointSs, n);
}