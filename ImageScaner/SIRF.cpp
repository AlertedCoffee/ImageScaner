#include "SIRF.h"


using namespace cv;
using namespace std;



namespace SIFTDetector {

    static const Scalar color = Scalar(0, 0, 255);

    // Метод чтения файлов.
    void OpenFiles(string templatePath, string imagePath, Mat &templ, Mat &img) {

//        if (templatePath.empty() || imagePath.empty()) throw exception("Empty path.");

        Mat inputTemplate = imread(templatePath);
        Mat inputImage = imread(imagePath);

        // Подсчет коэффициента для сжатия картинок.
        // Данные формулы выбраны для увеличения быстродействия программы, уменьшения расхода оперативной памяти
        // и исключения излишних ключевых точек.
        double imageResizeRatio = 720.0 / inputImage.rows;
        double templateResizeRatio = 240.0 / inputTemplate.rows;

        // Для работы без сжатия.
//        img = inputImage.clone();
//        templ = inputTemplate.clone();

        resize(inputImage, img, Size(), imageResizeRatio, imageResizeRatio);
        resize(inputTemplate, templ, Size(), templateResizeRatio, templateResizeRatio);

        inputTemplate.release();
        inputImage.release();
    }

    // Обработка изображений. Здесь конвертация в серый + блюр для исключения лишних ключевых точке.
    void Processing(Mat &img, Mat &templ) {
        GaussianBlur(img, img, Size(3, 3), 2);
        GaussianBlur(templ, templ, Size(3, 3), 2);
        cvtColor(img, img, COLOR_BGR2GRAY);
        cvtColor(templ, templ, COLOR_BGR2GRAY);
    }

    void Detection(string templatePath, string imagePath) {

        // Чтение изображений.
        Mat img, templ;
        OpenFiles(templatePath, imagePath, templ, img);


        // Сохранение нормального вида изображений для последующего отображения
        // на них результата работы алгоритма поиска.
        Mat normalImage = img.clone();
        Mat normalTemplate = templ.clone();


        Processing(img, templ);


        // Создание SIFT feature extractor and descriptor.
        Ptr<Feature2D> sift = SIFT::create();

        // Вычисление ключевых точек и дескрипторов.
        vector<KeyPoint> templKeypoints, imageKeypoints;
        Mat templDescriptors, imageDescriptors;
        sift->detectAndCompute(templ, Mat(), templKeypoints, templDescriptors);
        sift->detectAndCompute(img, Mat(), imageKeypoints, imageDescriptors);

        sift.release();

        // Вычисление совпадений дескрипторов.
        Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
        vector< vector<DMatch> > matches;
        matcher->knnMatch(templDescriptors, imageDescriptors, matches, 2);

        // Фильтрация совпавших точек.
        const float ratioThresh = 0.7f;
        vector<DMatch> goodMatches;
        for (size_t i = 0; i < matches.size(); i++)
        {
            if (matches[i][0].distance < ratioThresh * matches[i][1].distance)
            {
                goodMatches.push_back(matches[i][0]);
            }
        }

        // Отрисовка ключевых точек.
//        cv::Mat matchImage;
//        cv::drawMatches(templ, templKeypoints, img, imageKeypoints, goodMatches, matchImage, Scalar::all(-1),
//                        Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
//        imshow("SIFT Matches", matchImage);

        // Отрисовка аннотированного вида отображения. Закомментирована отрисовка квадарта вокруг области совпадения.
//        vector<Point> poly;
        for (size_t i = 0; i < goodMatches.size(); i++)
        {
//            poly.push_back(imageKeypoints[goodMatches[i].trainIdx].pt);

            circle(normalImage, imageKeypoints[goodMatches[i].trainIdx].pt, 3, color, FILLED);
            circle(normalTemplate, templKeypoints[goodMatches[i].queryIdx].pt, 3, color, FILLED);

        }

//        if (poly.size() != 0) {
//            Rect boundRect = boundingRect(poly);

//            rectangle(normalImage, boundRect, color, 3);
//            //putText(normalImage, "Detected", boundRect.tl(), FONT_HERSHEY_PLAIN, 2, color, 2);

//        }

        // Отображение.
        imshow("Image", normalImage);
        imshow("Templ", normalTemplate);

    }
}
