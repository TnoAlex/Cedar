//
// Created by NicoAlex on 2023/4/6.
//

#include "Image.h"

#include <utility>

Image::Image(unsigned char *raw, int w, int h, int type)
{
            LOG(info) << "Load Image" << std::endl;
    this->width = w;
    this->height = h;
    this->type = (ImageType) type;
    this->channel = std::make_shared<Channel>(this->type, h, w, raw);
            LOG(info) << "width : " << w << "px" << std::endl << "height: "
                      << h << std::endl << "type: " << ImageTypeString[type] << std::endl;
}


std::shared_ptr<ublas::matrix<uint>> Image::get_chunk(int d) const
{
    assert(d <= (uint) this->type && d >= 1);
    return this->channel->chunks->at(d);
}

Image::Image(const std::string &fileName)
{
            LOG(info) << "Load Image" << std::endl;
    int w, h, n;
    stbi_uc *data = stbi_load(fileName.c_str(), &w, &h, &n, 0);
    if (data == nullptr) {
                LOG(error) << "Can not access image" << std::endl;
        throw std::runtime_error("IOException");
    }
    this->width = w;
    this->height = h;
    this->type = (ImageType) n;
    this->channel = std::make_shared<Channel>(this->type, h, w, data);
            LOG(info) << "width : " << w << "px" << std::endl << "height: "
                      << h << std::endl << "type: " << ImageTypeString[type] << std::endl;
}

Image Image::copy() const
{
    auto *i = new Image;
    i->width = width;
    i->type = type;
    i->height = height;
    i->channel = channel;
    return *i;
}


