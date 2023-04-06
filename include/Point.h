//
// Created by NicoAlex on 2023/4/6.
//

#ifndef CEDAR_POINT_H
#define CEDAR_POINT_H


class Point
{
public:
    int x,y;

    bool operator ==(const Point &p) const;
    bool operator !=(const Point &p) const;
};


#endif //CEDAR_POINT_H
