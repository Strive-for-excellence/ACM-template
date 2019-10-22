struct Circle {
	Point c;
	double r;
	Circle (Point c = Point(0, 0), double r = 0): c(c), r(r) {}
	Point point(double a) {
		return Point(c.x + cos(a) * r, c.y + sin(a) * r);
	}
};

int GetCC(Circle C1, Circle C2, std::vector< Point> &sol) {
	double d = Length(C1.c - C2.c);
	if (dcmp(d) == 0) {
		if (dcmp(C1.r - C2.r) == 0) return -1;
		return 0;
	}
	if (dcmp(C1.r + C2.r - d) < 0) return 0;
	if (dcmp(fabs(C1.r - C2.r) - d) > 0) return 0;
	double a = angle(C2.c - C1.c);
	double da = acos((C1.r * C1.r + d * d - C2.r * C2.r) / (2 * C1.r * d));
	Point p1 = C1.point(a - da), p2 = C1.point(a + da);
	sol.push_back(p1);
	if (p1 == p2) return 1;
	sol.push_back(p2);
	return 2;
}
