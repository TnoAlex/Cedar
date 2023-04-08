//
// Created by NicoAlex on 2023/4/6.
//

#include "Channel.h"

#include <boost/log/trivial.hpp>

Channel::~Channel()
{
    delete chunks;
}

Channel::Channel(ImageType type, int row, int col, const uchar *raw)
{
    this->chunk_num = type;
    this->chunks = new map<int, shared_ptr<ublas::matrix<uchar>>>();
    this->chunk_row = row;
    this->chunk_col = col;
    try {
        for (int c = 1; c <= type; c++) {
            auto chunk = make_shared<ublas::matrix<uchar>>(row, col);
            int pos = c-1;
            for (int r = 0; r < row; r++) {
                for (int l = 0; l < col; l++) {
                    (*chunk.get())(r, l) = raw[pos];
                    pos+=(uint)type;
                }
            }
            this->chunks->insert({c, chunk});
        }
    } catch (std::exception &e) {
        BOOST_LOG_TRIVIAL(error) << "Raw data can not be converted to a matrix";
        throw e;
    }
}

shared_ptr<uchar[]> Channel::to_raw() const
{
    uint size = chunk_num * chunk_row * chunk_col;
    auto res = make_shared<uchar[]>(size);
    int pos = 0;
    for (int c = 1; c <= chunk_num; c++) {
        auto chunk = chunks->at(c);
        for (int r = 0; r < chunk_row; r++) {
            for (int l = 0; l < chunk_col; l++) {
                res[pos] = (uchar)(*chunk)(r, l);
                pos++;
            }
        }
    }
    return res;
}

Channel::Channel(const shared_ptr<ublas::matrix<uchar>>& matrix, int num, int row, int col)
{
    this->chunks = new map<int, shared_ptr<ublas::matrix<uchar>>>();
    this->chunks->insert({1,matrix});
    this->chunk_num = num;
    this->chunk_row = row;
    this->chunk_col = col;
}

Channel::Channel() = default;
