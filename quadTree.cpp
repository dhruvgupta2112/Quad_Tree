#include "quadTree.h"

bool Rectangle::contains(const Point & point){
    return (point.x >= x - w/2 && point.x <= x + w/2 &&
            point.y >= y - h/2 && point.y <= h/2);
}

bool Rectangle::intersects(const Rectangle & R2){
    return !(R2.x - R2.w/2 > x + w/2 ||
             R2.x + R2.w/2 < x - w/2 ||
             R2.y - R2.h/2 > y + h/2 ||
             R2.y + R2.h/2 < y - h/2);
}
void quadTree::insert(){

}