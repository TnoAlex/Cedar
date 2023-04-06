//
// Created by NicoAlex on 2023/4/6.
//

#include "Channel.h"

Channel::~Channel()
{
    delete chunks;
}

Channel::Channel(ImageType type, int row, int col, const uchar *raw)
{
    this->size = type;
    this->chunks = new map<int, shared_ptr<ublas::matrix<uint>>>();
    try{
        for (int c = 1; c <= type; c++) {
            ublas::matrix<uint> chunk(row, col);
            for (int r = 0; r < row; r++) {
                for (int l = 0; l < col; l++) {
                    chunk(r, l) = raw[r * c + l];
                }
            }
            this->chunks->insert({c, std::shared_ptr<ublas::matrix<uint>>(&chunk)});
        }
    }catch (std::exception &e){
        LOG(error)<<"Raw data can not be converted to a matrix";
    }

}

Channel::Channel() = default;
