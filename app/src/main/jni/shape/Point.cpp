#include "Point.h"

Point::~Point() {

}

Point::Point() : BaseShape("point") {
    verticies.push_back(0);
    verticies.push_back(0);
    verticies.push_back(0);
}
