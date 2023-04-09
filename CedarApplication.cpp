#include "RgbImage.h"
#include "logger.h"
#include "GrayImage.h"
#include "Complex.h"
#include "FFT.h"

int main()
{
    init_logger();
    RgbImage image(R"(E:\code\Cedar\test\cat.jpg)");
//    image.show();
    GrayImage gImage;
    image.to_gray_image(gImage);

    auto raw_data = gImage.channel->to_raw();
//    auto center_data = FFT::scale(raw_data, gImage.height, gImage.width);
    ublas::matrix<Complex> cMatrix(gImage.height, gImage.width);
    FFT::byte_2_complex(cMatrix, raw_data);
    ublas::matrix<Complex> c2FFT(gImage.height, gImage.width);
    FFT::fft2d(cMatrix, c2FFT, 1);
    ublas::matrix<Complex> fft2C(gImage.height, gImage.width);
    FFT::fft2d(c2FFT, fft2C, -1);

    auto inv_data = make_shared<uchar[]>(gImage.height * gImage.width,0);
    auto spectrum = make_shared<double[]>(gImage.height * gImage.width,0);

    FFT::complex_2_byte(fft2C,inv_data);
    FFT::complex_2_double(c2FFT,spectrum);
    auto s = FFT::scale(spectrum,gImage.height,gImage.width);
    Image invImg = Image(inv_data.get(),gImage.width,gImage.height,gImage.type);
    Image speImg = Image(s.get(),gImage.width,gImage.height,gImage.type);
    invImg.show("inv.png");
    speImg.show("spe.png");
    gImage.show("test.png");
//    system("pause");
}
