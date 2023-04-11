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

using namespace std;
namespace ublas = boost::numeric::ublas;

class Channel
{
public:
    int chunk_num = 0;
    int chunk_row = 0;
    int chunk_col = 0;
    map<int, shared_ptr<ublas::matrix<uchar>>> *chunks{};

    Channel();

    Channel(ImageType type, int row, int col, const uchar *raw);
    Channel(const shared_ptr<ublas::matrix<uchar>>&matrix, int num, int row, int col);

    Channel(std::vector<shared_ptr<ublas::matrix<uchar>>>&matrix, int num, int row, int col);

    ~Channel();

    [[nodiscard]] shared_ptr<uchar[]> to_raw() const;
};

#endif //CEDAR_CHANNEL_H
