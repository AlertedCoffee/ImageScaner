#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/features2d.hpp>

#include <iostream>

using namespace cv;
using namespace std;

namespace SIRFDetector {

/**@brief Поиск изображений по SIRF.
        @param[in] templatePath путь к изображению для поиска (что ищем)
        @param[in] imagePath пусть к исходнику (где ищем)
    */
void Detection(string templatePath, string imagePath);
}
