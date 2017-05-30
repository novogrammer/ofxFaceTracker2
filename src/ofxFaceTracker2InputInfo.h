#pragma once

#include "ofConstants.h"
#include "ofMatrix4x4.h"

#include "ofxCv.h"

class ofxFaceTracker2InputInfo {
public:
    int inputWidth, inputHeight;
    int landmarkWidth, landmarkHeight;
    int imageRotation;
    cv::Mat cameraMatrix;
    
    // Parameters calculated automatically
    ofMatrix4x4 rotationMatrix;
    ofxCv::Intrinsics intrinsics;
    
    // Constructor
    ofxFaceTracker2InputInfo(){};
    
    ofxFaceTracker2InputInfo(int inputWidth, int inputHeight,int landmarkWidth, int landmarkHeight, int imageRotation, cv::Mat cameraMatrix)
    : inputWidth(inputWidth)
    , inputHeight(inputHeight)
    , landmarkWidth(landmarkWidth)
    , landmarkHeight(landmarkHeight)
    , imageRotation(imageRotation)
    , cameraMatrix(cameraMatrix) {
        // Calculate rotation matrix
        if(imageRotation == 90){
            rotationMatrix.makeIdentityMatrix();
            rotationMatrix.translate(-landmarkWidth,0,0);
            rotationMatrix.scale(((float)inputWidth / landmarkHeight), ((float)inputWidth / landmarkHeight), 1);
            rotationMatrix.rotate(-90, 0,0,1);
        } else if(imageRotation == 270){
            rotationMatrix.makeIdentityMatrix();
            rotationMatrix.translate(0, -landmarkHeight,0);
            rotationMatrix.scale(((float)inputWidth / landmarkHeight), ((float)inputWidth / landmarkHeight), 1);
            rotationMatrix.rotate(90, 0,0,1);
        } else if(imageRotation == 180){
            rotationMatrix.makeIdentityMatrix();
            rotationMatrix.translate(-landmarkWidth, -landmarkHeight,0);
            rotationMatrix.scale(((float)inputWidth / landmarkWidth), ((float)inputWidth / landmarkWidth), 1);
            rotationMatrix.rotate(180, 0,0,1);
        } else {
            rotationMatrix.makeIdentityMatrix();
            rotationMatrix.scale(((float)inputWidth / landmarkWidth), ((float)inputWidth / landmarkWidth), 1);
        }
        
        
        // Calculate intrinsics
        cameraMatrix.at<double>(0,2)=inputWidth/2;
        cameraMatrix.at<double>(1,2)=inputHeight/2;
        cv::Size2i imageSize(inputWidth, inputHeight);
        intrinsics.setup(cameraMatrix, imageSize);
    }
};