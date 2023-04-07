#include "RgbImage.h"
#include "logger.h"
#include "GrayImage.h"

int main()
{
    init_logger();
    RgbImage image(R"(E:\code\Cedar\test\Lena.bmp)");
    image.show();
//    GrayImage gImage;
//    image.to_gray_image(gImage);
//    gImage.show();
//    system("pause");
}
