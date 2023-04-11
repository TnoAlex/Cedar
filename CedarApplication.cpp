#include "logger.h"
#include "Complex.h"
#include "FFT.h"
#include "util.h"
#include "Image.h"
#include "GaussianFilter.h"

int main()
{
    init_logger();
    Image image(R"(E:\code\Cedar\test\Lena.bmp)");
//    image.show();
    Image gImage = image.to_gery();

    auto raw_data = gImage.channel->to_raw();
//    auto center_data = FFT::scale(raw_data, gImage.height, gImage.width);
    ublas::matrix<Complex> cMatrix(gImage.height, gImage.width);
    array_2_complex(cMatrix, raw_data);
    ublas::matrix<Complex> c2FFT(gImage.height, gImage.width);
    FFT::DFT(cMatrix, c2FFT);


    auto inv_data = make_shared<double[]>(gImage.height * gImage.width, 0);
    auto spectrum = make_shared<double[]>(gImage.height * gImage.width, 0);

    complex_2_double(c2FFT, spectrum);

    auto fftM = ublas::matrix<double>(gImage.height, gImage.width);
//    to_matrix(spectrum.get(), fftM);
    ublas::matrix<double> fed(gImage.height, gImage.width);
//    filter.filter(fftM, fed);
//    auto st = from_matrix(fed);

//    auto fftm_a = from_matrix(spectrum);

    ublas::matrix<Complex> fft2C (gImage.height, gImage.width);
    gaussian_filter(c2FFT, 12, 0);
    FFT::IDFT(c2FFT, fft2C);

    auto guss = make_shared<double[]>(gImage.height * gImage.width, 0);
    complex_2_double(fft2C, guss);
    complex_2_double(c2FFT, inv_data);
    auto guss_s = FFT::scale(guss, gImage.height, gImage.width);
    auto s = FFT::scale(spectrum, gImage.height, gImage.width);
    auto ss =  FFT::scale(inv_data, gImage.height, gImage.width);
    Image invImg = Image(ss.get(), gImage.width, gImage.height, gImage.type);
    Image speImg = Image(s.get(), gImage.width, gImage.height, gImage.type);
    Image gussImg = Image(guss_s.get(), gImage.width, gImage.height, gImage.type);
    invImg.swimg("inv.bmp");
    speImg.swimg("spe.bmp");
    gImage.swimg("test.bmp");
    gussImg.swimg("guss.bmp");
//    system("pause");
}
