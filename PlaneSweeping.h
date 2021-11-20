//
// Created by finley on 16/11/2021.
//

#ifndef PLANESWEEPING_PLANESWEEPING_H
#define PLANESWEEPING_PLANESWEEPING_H

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


class PlaneSweeping{
private:
    cv::Mat left;
    cv::Mat right;
    cv::Mat K;
    cv::Mat R;
    cv::Mat t;
    std::vector<cv::Mat> costall;
    double depthpre;
public:
    void LoadInformation(cv::Mat pleft, cv::Mat pright, cv::Mat pK, cv::Mat pR, cv::Mat pt);
    void EstimateDepth();
    void CostAggregation();
};

#endif //PLANESWEEPING_PLANESWEEPING_H
