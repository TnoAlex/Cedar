//
// Created by NicoAlex on 2023/4/3.
//
#include "logger.h"


void coloring_formatter(
        logging::record_view const &rec, logging::formatting_ostream &strm)
{

    const std::string red("\033[0;31m");
    const std::string green("\033[0;32m");
    const std::string yellow("\033[0;33m");
    const std::string blue("\033[0;34m");
    const std::string magenta("\033[0;35m");
    const std::string cyan("\033[0;36m");
    const std::string reset("\033[0m");

    const std::map<logging::trivial::severity_level, std::string> severity_colors = {
            {logging::trivial::trace,   blue},
            {logging::trivial::debug,   green},
            {logging::trivial::info,    cyan},
            {logging::trivial::warning, yellow},
            {logging::trivial::error,   red},
            {logging::trivial::fatal,   magenta}
    };

    auto severity = rec[logging::trivial::severity].get();
    auto color_iter = severity_colors.find(severity);
    auto color = cyan;
    if (color_iter != severity_colors.end())
        color = color_iter->second;

    strm << std::setw(6) << std::setfill('0') << color << "[" << std::this_thread::get_id() << "]" << " "
         << rec["TimeStamp"].extract<boost::posix_time::ptime>()
         <<" [" << severity << "] "
         << expr::smessage;

    strm << rec[expr::smessage] ;

    if (severity) {
        strm << reset;
    }
}

void init_logger()
{
    typedef sinks::synchronous_sink<sinks::text_ostream_backend> text_sink;
    boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();

    boost::shared_ptr<std::ostream> stream(&std::cout, boost::null_deleter());
    sink->locked_backend()->add_stream(stream);

    sink->set_formatter(&coloring_formatter);

    sink->set_filter(logging::trivial::severity >= logging::trivial::debug);
    logging::core::get()->add_sink(sink);
    logging::add_common_attributes();
}

