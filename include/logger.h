//
// Created by NicoAlex on 2023/4/3.
//


#ifndef CEDAR_LOGGER_H
#define CEDAR_LOGGER_H

#include <boost/log/core.hpp>
#include <boost/log/utility/formatting_ostream.hpp>

namespace logging = boost::log;
void coloring_formatter(logging::record_view const &rec, logging::formatting_ostream &strm);

void init_logger();


#endif //CEDAR_LOGGER_H
