#pragma once
#include <vector>

struct Point {
	double x, y;
};

using Points = std::vector < Point >;

ref class PointsStorage {
public:
	PointsStorage();
	~PointsStorage();
	Points& points;
};

