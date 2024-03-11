#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    // lower and upper bounds of each color in HSV space
    map<string, Scalar> lower = {{"red", Scalar(166, 84, 141)}, {"green", Scalar(50, 50, 120)}, {"blue", Scalar(97, 100, 117)},
                                  {"yellow", Scalar(23, 59, 119)}, {"orange", Scalar(0, 50, 80)}, {"purple", Scalar(130, 80, 80)}};
    map<string, Scalar> upper = {{"red", Scalar(186, 255, 255)}, {"green", Scalar(70, 255, 255)}, {"blue", Scalar(117, 255, 255)},
                                  {"yellow", Scalar(54, 255, 255)}, {"orange", Scalar(20, 255, 255)}, {"purple", Scalar(150, 255, 255)}};

    // BGR tuple of each color
    map<string, Scalar> colors = {{"red", Scalar(0, 0, 255)}, {"green", Scalar(0, 255, 0)}, {"blue", Scalar(255, 0, 0)},
                                   {"yellow", Scalar(0, 255, 217)}, {"orange", Scalar(0, 140, 255)}, {"purple", Scalar(211, 0, 148)}};

    Mat frame = imread("/Users/damsara/Desktop/Virtualpaint/test/test/Geometric-Shapes.jpg");

    Mat blurred, hsv;
    GaussianBlur(frame, blurred, Size(11, 11), 0);
    cvtColor(blurred, hsv, COLOR_BGR2HSV);

    vector<Mat> mlist;
    vector<vector<Point>> clist;
    vector<string> ks;

    for (auto &pair : upper) {
        Mat mask;
        inRange(hsv, lower[pair.first], pair.second, mask);
        morphologyEx(mask, mask, MORPH_OPEN, Mat(), Point(-1, -1), 2);
        dilate(mask, mask, Mat(), Point(-1, -1), 1);
        mlist.push_back(mask);

        vector<vector<Point>> cnts;
        findContours(mask.clone(), cnts, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        if (!cnts.empty()) {
            clist.push_back(cnts.back());
            ks.push_back(pair.first);
        }
    }

    for (size_t i = 0; i < clist.size(); ++i) {
        vector<Point> cnt = clist[i];
        vector<Point> approx;
        approxPolyDP(cnt, approx, 0.01 * arcLength(cnt, true), true);
        Scalar color = colors[ks[i]];

        Moments M = moments(cnt);
        int x = static_cast<int>(M.m10 / M.m00);
        int y = static_cast<int>(M.m01 / M.m00);

        if (approx.size() == 3) {
            putText(frame, ks[i] + " Triangle", Point(x, y), FONT_HERSHEY_SIMPLEX, 0.6, color, 2);
        } else if (approx.size() == 4) {
            int x2 = approx[2].x;
            int y2 = approx[2].y;
            int x4 = approx[4].x;
            int y4 = approx[4].y;
            int side1 = abs(x2 - x);
            int side2 = abs(y4 - y);

            if (abs(side1 - side2) <= 2) {
                putText(frame, ks[i] + " Square", Point(x, y), FONT_HERSHEY_SIMPLEX, 0.6, color, 2);
            } else {
                putText(frame, ks[i] + " Rectangle", Point(x, y), FONT_HERSHEY_SIMPLEX, 0.6, color, 2);
            }
        } else if (approx.size() == 5) {
            putText(frame, ks[i] + " Pentagon", Point(x, y), FONT_HERSHEY_SIMPLEX, 0.6, color, 2);
        } else if (approx.size() > 10) {
            putText(frame, ks[i] + " Circle", Point(x, y), FONT_HERSHEY_SIMPLEX, 0.6, color, 2);
        }
    }

    imshow("Frame", frame);
    waitKey(0);
    destroyAllWindows();

    return 0;
}
