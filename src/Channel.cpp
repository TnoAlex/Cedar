//
// Created by NicoAlex on 2023/4/6.
//

#include "Channel.h"

Channel::~Channel()
{
    delete ch;
}

Channel::Channel(ImageType type, int w, int h)
{
    this->size = type;
    this->ch = new map<int, shared_ptr<ublas::matrix<Pixel>>>();
    for (int i = 0; i < type; i++) {
        this->ch->insert({i, make_shared<ublas::matrix<Pixel>>(w, h)});
    }
}
