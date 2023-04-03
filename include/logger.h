//
// Created by NicoAlex on 2023/4/3.
//
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/support/date_time.hpp>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <thread>

#ifndef CEDAR_LOGGER_H
#define CEDAR_LOGGER_H

#define LOG BOOST_LOG_TRIVIAL

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;


void coloring_formatter(logging::record_view const &rec, logging::formatting_ostream &strm);

void init_logger();


#endif //CEDAR_LOGGER_H
