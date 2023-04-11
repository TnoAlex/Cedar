#include "logger.h"
#include "Complex.h"
#include "FFT.h"
#include "util.h"
#include "Image.h"
#include "GaussianFilter.h"
#include <boost/program_options.hpp>
#include <boost/log/trivial.hpp>

using namespace std;
namespace program = boost::program_options;

int main(int argc, char *argv[])
{
    init_logger();
    program::options_description desc("Allowed options");
    desc.add_options()
            ("help", "show the help message")
            ("i", program::value<string>(), "input image")
            ("sigma", program::value<double>(), "The sigma of Gaussian filter")
            ("ft", program::value<int>()->default_value(0), "filter type : Low-pass=0,High-pass=1")
            ("obs", program::value<bool>()->default_value(false),
             "Output the frequency domain map of the original image")
            ("oas", program::value<bool>()->default_value(false),
             "Output the frequency domain map of the filtered image");
    program::variables_map vm;
    program::store(program::parse_command_line(argc, argv, desc), vm);
    program::notify(vm);

    if (vm.count("help")) {
        BOOST_LOG_TRIVIAL(info) << desc;
        return 1;
    }

    if (!vm.count("sigma")) {
        BOOST_LOG_TRIVIAL(error) << "UnKnown Sigma";
        return -1;
    }

    if (vm.count("i")) {
        Image image = Image(vm["i"].as<std::string>());
        Image gery_img = image.to_gery();
        ublas::matrix<Complex> gery_matrix(gery_img.height, gery_img.width);
        array_2_complex(gery_img.channel->to_raw(), gery_matrix);
        ublas::matrix<Complex> fdp(gery_img.height, gery_img.width);
        BOOST_LOG_TRIVIAL(info) << "Image in Fourier transform ...";
        FFT::DFT(gery_matrix, fdp);
        if (vm["obs"].as<bool>()) {
            BOOST_LOG_TRIVIAL(info) <<"Write out the frequency domain image ...";
            auto ofdp = make_shared<double[]>(gery_img.height * gery_img.width, 0);
            ublas::matrix<double> ofdp_matrix(gery_img.height, gery_img.width);
            complex_2_double(fdp, ofdp);
            to_matrix(ofdp.get(), ofdp_matrix);
            center_matrix(ofdp_matrix);
            Image ofdp_img = Image(FFT::scale(from_matrix(ofdp_matrix), gery_img.height, gery_img.width).get(),
                                   gery_img.width, gery_img.height, GREY);
            ofdp_img.swimg("frequency_domain_img.bmp");
        }
        BOOST_LOG_TRIVIAL(info) <<"Gaussian filtering ...";
        gaussian_filter(fdp, 12, vm["ft"].as<int>());
        auto filtered_i =  make_shared<double[]>(gery_img.height * gery_img.width, 0);
        ublas::matrix<Complex> filtered_i_matrix(gery_img.height, gery_img.width);
        FFT::IDFT(fdp,filtered_i_matrix);
        complex_2_double(filtered_i_matrix,filtered_i);
        Image filtered_img = Image(FFT::scale(filtered_i, gery_img.height, gery_img.width).get(),
                               gery_img.width, gery_img.height, GREY);
        filtered_img.swimg("filtered_img.bmp");
        if(vm["oas"].as<bool>()){
            BOOST_LOG_TRIVIAL(info) <<"Write out the frequency domain image ...";
            auto afdp = make_shared<double[]>(gery_img.height * gery_img.width, 0);
            ublas::matrix<double> afdp_matrix(gery_img.height, gery_img.width);
            complex_2_double(fdp, afdp);
            to_matrix(afdp.get(), afdp_matrix);
            center_matrix(afdp_matrix);
            Image ofdp_img = Image(FFT::scale(from_matrix(afdp_matrix), gery_img.height, gery_img.width).get(),
                                   gery_img.width, gery_img.height, GREY);
            ofdp_img.swimg("filtered_frequency_domain_img.bmp");
        }
    } else {
        BOOST_LOG_TRIVIAL(error) << "Input file was not set.";
        return -1;
    }
    return 0;
}

