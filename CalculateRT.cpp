//
// Created by finley on 16/11/2021.
//
#include "CalculateRT.h"


void CalculateRT::ReadImageandParam() {
    left = cv::imread("../data/DSC_0341.JPG");
    right = cv::imread("../data/DSC_0342.JPG");
    cv::FileStorage fs("../calib_param.yml", cv::FileStorage::READ);
    fs["camera_matrix"] >> K;
    fs["distortion_coefficients"] >> distCoeffs;
}

void CalculateRT::ORBDetectorandCalculate() {
    cv::Ptr<cv::FeatureDetector> detector = cv::ORB::create();
    cv::Ptr<cv::DescriptorExtractor> descriptor = cv::ORB::create();
    detector->detect(left, keypoints_left);
    detector->detect(right, keypoints_right);
    descriptor->compute(left, keypoints_left, descriptor_left);
    descriptor->compute(right, keypoints_right, descriptor_right);
}

void CalculateRT::Match() {
    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("BruteForce-Hamming");
    std::vector<cv::DMatch> matches;
    matcher->match(descriptor_left, descriptor_right, matches);
    auto min_max = std::minmax_element(matches.begin(), matches.end(), [](const cv::DMatch &m1, const cv::DMatch &m2){return m1.distance<m2.distance;});
    double min_dist = min_max.first->distance;
    for(int i = 0; i<descriptor_left.rows; i++){
        if(matches[i].distance <= std::max(2*min_dist, 30.0)){
            good_matches.push_back(matches[i]);
        }
    }
}

void CalculateRT::FindMatchPoint() {
    std::vector<int> pointIndexesLeft, pointIndexesRight;
    for (std::vector<cv::DMatch>::const_iterator it = good_matches.begin();
         it != good_matches.end(); ++it)
    {
        pointIndexesLeft.push_back(it->queryIdx);
        pointIndexesRight.push_back(it->trainIdx);
    }

    cv::KeyPoint::convert(keypoints_left, sel_points_left, pointIndexesLeft);
    cv::KeyPoint::convert(keypoints_right, sel_points_right, pointIndexesRight);
}

void CalculateRT::CalculateRnt() {
    cv::Mat E;
    cv::Mat F;
    cv::Mat mask;
    F = cv::findFundamentalMat(sel_points_left, sel_points_right, cv::FM_RANSAC, 1,
                               0.99, mask);
    std::vector<cv::Point2f> realPointsLeft, realPointsRight;
    for (int i = 0; i < mask.size().height; i++)
    {
        int flag = mask.at<uchar>(i, 0);

        if (flag == 1)
        {
            realPointsLeft.push_back(sel_points_left[i]);
            realPointsRight.push_back(sel_points_right[i]);
        }
        sel_points_left = realPointsLeft;
        sel_points_right = realPointsRight;
    }
    E = cv::findEssentialMat(sel_points_left, sel_points_right, K);

    cv::recoverPose(E, sel_points_left, sel_points_right, K, R, t);
}

void CalculateRT::run() {
    ReadImageandParam();
    ORBDetectorandCalculate();
    Match();
    FindMatchPoint();
    CalculateRnt();
}


