#include <iostream>
#include "logger.h"

int main()
{
    init_logger();
    LOG(info)<<"test info";
    LOG(error) <<"test error";
    LOG(debug) << "test debug";
    LOG(warning) << "test warning";
    LOG(trace) <<"test trace";
    return 0;
}
