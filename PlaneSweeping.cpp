//
// Created by finley on 16/11/2021.
//

#include "PlaneSweeping.h"

void PlaneSweeping::LoadInformation(cv::Mat pleft, cv::Mat pright, cv::Mat pK, cv::Mat pR, cv::Mat pt) {
    left = pleft;
    right = pright;
    K = pK;
    R = pR;
    t = pt;
}

void PlaneSweeping::EstimateDepth() {
    cv::Size imgSize = left.size();
    int delta = 10;
    cv::Mat n_t = cv::Mat::zeros(1, 3, CV_64FC1);
    n_t.at<double>(0, 2) = -1;
    cv::Mat kernel = cv::Mat::ones((2 * delta + 1), (delta * 2 + 1), CV_8UC1);
    cv::Mat sad = cv::Mat::ones(imgSize.height, imgSize.width, CV_64FC1) * 255 * ((2 * delta + 1) * (2 * delta + 1));
    cv::Mat depth = cv::Mat::zeros(imgSize.height, imgSize.width, CV_64FC1);
    cv::Mat gray_left, gray_right;
    cv::cvtColor(left, gray_left, cv::COLOR_BGR2GRAY);
    cv::cvtColor(right, gray_right, cv::COLOR_BGR2GRAY);
    for(int i = 700; i>0; i--){
        std::cout<<"Planing "<<i<<std::endl;
        double d = (K.at<double>(0,0) + K.at<double>(1, 1))/2/i;
        std::cout<<"Planing depth "<<d<<std::endl;
        if(d>15) break;
        cv::Mat H = R - t * n_t / d;
        cv::Mat KHKinv = K * H * K.inv();
        cv::Mat warp_right;
        warpPerspective(gray_right, warp_right, KHKinv.inv(), imgSize);
        cv::Mat diff;
        filter2D(abs(gray_left - warp_right), diff, CV_64F, kernel);
        for (int row = 0; row < imgSize.height; row++)
        {
            for (int col = 0; col < imgSize.width; col++)
            {
                int tmp;
                tmp = diff.at<double>(row, col);
                //cost.at<double>(row, col) = tmp;
                if (tmp < sad.at<double>(row, col))
                {
                    sad.at<double>(row, col) = tmp;
                    depth.at<double>(row, col) = d;
                }
            }
        }
        //costall.push_back(cost);
    }
    double min, max;
    minMaxLoc(depth, &min, &max);
    depth.convertTo(depth, CV_8UC1, 255.0 / (max - min),
                    -min * 255.0 / (max - min));
    //cv::imshow("img", depth);
    cv::imwrite("../depthkitti.jpg", depth);
}

