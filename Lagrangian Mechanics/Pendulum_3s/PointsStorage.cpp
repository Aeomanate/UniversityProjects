#include "stdafx.h"
#include "PointsStorage.h"

PointsStorage::PointsStorage(): points(*new std::vector<Point>) { }
PointsStorage::~PointsStorage() {
	delete &points;
}


