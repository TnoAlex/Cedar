//
// Created by NicoAlex on 2023/4/6.
//

#include "RgbImage.h"


GrayImage RgbImage::to_gray_image()
{
    auto new_channel = std::make_shared<Channel>();
    ublas::matrix<uint> matrix = (*get_chunk(1)) * 0.3 + (*get_chunk(2)) * 0.59 + (*get_chunk(3)) * 0.11;
    new_channel->chunks->insert({0, std::shared_ptr<ublas::matrix<uint>>(&matrix)});
    auto new_img = copy();
    new_img.channel = std::move(new_channel);
    return (GrayImage) new_img;
}
