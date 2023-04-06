//
// Created by NicoAlex on 2023/4/6.
//

#ifndef CEDAR_CHANNEL_H
#define CEDAR_CHANNEL_H

#include <boost/numeric/ublas/matrix.hpp>
#include <map>
#include <memory>
#include "image_type.h"
#include "Pixel.h"

using namespace std;
namespace ublas = boost::numeric::ublas;

class Channel
{
    int size;
    map<int, shared_ptr<ublas::matrix<Pixel>>> *ch;

    Channel(ImageType type, int w, int h);
    ~Channel();
};

#endif //CEDAR_CHANNEL_H
