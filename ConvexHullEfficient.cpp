#include "ConvexHullEfficient.h"

struct PointS
{
	int x, y;
};

PointS p0;

PointS nextToTop(stack<PointS> &S)
{
	PointS p = S.top();
	S.pop();
	PointS res = S.top();
	S.push(p);
	return res;
}

int swap(PointS &p1, PointS &p2)
{
	PointS temp = p1;
	p1 = p2;
	p2 = temp;
	return 1;
}

int distSq(PointS p1, PointS p2)
{
	return (p1.x - p2.x)*(p1.x - p2.x) +
		(p1.y - p2.y)*(p1.y - p2.y);
}

int orientation(PointS p, PointS q, PointS r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;  // colinear
	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

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

void convexHullEff(PointS PointSs[], int n)
{
	int ymin = PointSs[0].y, min = 0;
	for (int i = 1; i < n; i++)
	{
		int y = PointSs[i].y;

		if ((y < ymin) || (ymin == y &&
			PointSs[i].x < PointSs[min].x))
			ymin = PointSs[i].y, min = i;
	}
	swap(PointSs[0], PointSs[min]);

	p0 = PointSs[0];
	qsort(&PointSs[1], n - 1, sizeof(PointS), compare);
	int m = 1;
	for (int i = 1; i<n; i++)
	{
		while (i < n - 1 && orientation(p0, PointSs[i],
			PointSs[i + 1]) == 0)
			i++;


		PointSs[m] = PointSs[i];
		m++; 
	}

	if (m < 3) return;

	stack<PointS> S;
	S.push(PointSs[0]);
	S.push(PointSs[1]);
	S.push(PointSs[2]);
	for (int i = 3; i < m; i++)
	{
		while (orientation(nextToTop(S), S.top(), PointSs[i]) != 2)
			S.pop();
		S.push(PointSs[i]);
	}

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
