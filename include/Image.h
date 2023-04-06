//
// Created by NicoAlex on 2023/4/6.
//

#ifndef CEDAR_IMAGE_H
#define CEDAR_IMAGE_H

#define STB_IMAGE_IMPLEMENTATION
#define STBI_WINDOWS_UTF8
#define STBI_FAILURE_USERMSG

#include <memory>
#include <string>
#include <cassert>
#include "Channel.h"
#include "image_type.h"
#include "logger.h"
#include "type_assign.h"
#include "stb/stb_image.h"


class Image
{
public:
    int width = 0, height = 0;
    std::shared_ptr<Channel> channel;
    ImageType type;

    Image();

    Image(unsigned char *raw, int w, int h, int type);

    explicit Image(const std::string &fileName);

    [[nodiscard]] std::shared_ptr<ublas::matrix<uint>> get_chunk(int d) const;

protected:
    Image copy() const;
};


#endif //CEDAR_IMAGE_H
