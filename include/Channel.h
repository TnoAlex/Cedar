//
// Created by NicoAlex on 2023/4/6.
//

#ifndef CEDAR_CHANNEL_H
#define CEDAR_CHANNEL_H

#include <boost/numeric/ublas/matrix.hpp>
#include <map>
#include <memory>
#include "image_type.h"
#include "type_assign.h"
#include "logger.h"

using namespace std;
namespace ublas = boost::numeric::ublas;

class Channel
{
public:
    int size = 0;
    map<int, shared_ptr<ublas::matrix<uint>>> *chunks{};

    Channel();

    Channel(ImageType type, int row, int col, const uchar *raw);

    ~Channel();
};

#endif //CEDAR_CHANNEL_H
