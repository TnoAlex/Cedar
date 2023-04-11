//
// Created by NicoAlex on 2023/4/6.
//

#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_WINDOWS_UTF8
#define STBI_FAILURE_USERMSG
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#include <boost/log/trivial.hpp>

std::map<unsigned int, std::string> ImageTypeString = {
        {1, "GREY"},
        {2, "GREY_WITH_ALPHA"},
        {3, "RGB"},
        {4, "RGB_WITH_ALPHA"}
};

Image::Image(uchar *raw, int w, int h, int type)
{
    BOOST_LOG_TRIVIAL(info) << "Load Image" << "\n";
    this->width = w;
    this->height = h;
    this->type = (ImageType) type;
    this->channel = std::make_shared<Channel>(this->type, h, w, raw);
}

Image::Image(const std::string &fileName)
{
    BOOST_LOG_TRIVIAL(info) << "Load Image";
    int n = 0;
    uchar *data = stbi_load(fileName.c_str(), &this->width, &this->height, &n, 0);
    if (data == nullptr) {
        BOOST_LOG_TRIVIAL(error) << "Can not access the file";
        throw std::exception("IOException");
    }
    this->type = (ImageType) n;
    this->channel = std::make_shared<Channel>(this->type, height, width, data);
    stbi_image_free(data);
    BOOST_LOG_TRIVIAL(info) << "\n" << "width : " << width << "px" << "\n" << "height: "
                            << height <<"px"<< "\n" << "type: " << ImageTypeString[type];
}

Image::Image(vector<shared_ptr<ublas::matrix<unsigned char>>> &matrix, int num, int row, int col)
{
    this->width = col;
    this->height = row;
    this->type = (ImageType) num;
    this->channel = make_shared<Channel>(matrix, num, row, col);
}


std::shared_ptr<ublas::matrix<uchar>> Image::get_chunk(int d) const
{
    assert(d <= (uint) this->type && d >= 1);
    return this->channel->chunks->at(d);
}

void Image::swimg(const string &fileName) const
{
    BOOST_LOG_TRIVIAL(info)<<"out -> "<<fileName;
    auto raw = channel->to_raw();
    stbi_write_bmp(fileName.c_str(), width, height, 1, raw.get());
}

Image Image::to_gery()
{
    if (this->type == GREY || this->type == GREY_WITH_ALPHA) {
        return Image{*this};
    }
    auto matrix = std::make_shared<ublas::matrix<uchar>>(this->height, this->width);
    ublas::matrix<uchar> b = (*get_chunk(1));
    ublas::matrix<uchar> g = (*get_chunk(2));
    ublas::matrix<uchar> r = (*get_chunk(3));
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            (*matrix.get())(i, j) = ceil(r(i, j) * 0.3 + g(i, j) * 0.59 + b(i, j) * 0.11);
        }
    }
    Image img;
    auto new_channel = std::make_shared<Channel>(matrix, GREY, this->height, this->width);
    img.type = GREY;
    img.width = width;
    img.height = height;
    img.channel = std::move(new_channel);
    return img;
}





