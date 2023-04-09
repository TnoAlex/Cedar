//
// Created by NicoAlex on 2023/4/6.
//

#ifndef CEDAR_IMAGE_H
#define CEDAR_IMAGE_H

#include <memory>
#include <string>
#include <cassert>
#include <Windows.h>
#include "Channel.h"
#include "image_type.h"
#include "type_assign.h"

class Image
{
public:
    int width = 0, height = 0;
    std::shared_ptr<Channel> channel;
    ImageType type = GREY;

    Image() = default;

    Image(const shared_ptr<ublas::matrix<uchar>>&matrix, int num, int row, int col);
    Image(unsigned char *raw, int w, int h, int type);

    explicit Image(const std::string &fileName);

    void show(const string &fileName) const;

    [[nodiscard]] std::shared_ptr<ublas::matrix<uchar>> get_chunk(int d) const;

};


#endif //CEDAR_IMAGE_H
