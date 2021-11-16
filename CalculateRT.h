//
// Created by finley on 16/11/2021.
//

#ifndef SELF_CALCULATERT_H
#define SELF_CALCULATERT_H
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <algorithm>

class CalculateRT{
private:
    cv::Mat left;
    cv::Mat right;
    cv::Mat K;
    cv::Mat distCoeffs;
    std::vector<cv::KeyPoint> keypoints_left;
    std::vector<cv::KeyPoint> keypoints_right;
    cv::Mat descriptor_left;
    cv::Mat descriptor_right;
    std::vector<cv::DMatch> good_matches;
    std::vector<cv::Point2f> sel_points_left;
    std::vector<cv::Point2f> sel_points_right;
    cv::Mat R;
    cv::Mat t;

public:
    CalculateRT()= default;
    ~CalculateRT()= default;
    void ReadImageandParam();
    void ORBDetectorandCalculate();
    void Match();
    void FindMatchPoint();
    void CalculateRnt();
    void run();
    cv::Mat GetK(){return K;};
    cv::Mat GetR(){return R;};
    cv::Mat Gett(){return t;};
};

#endif //SELF_CALCULATERT_H
