#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::VideoCapture video("video.mp4");

    if (!video.isOpened()) {
        std::cerr << "Error: Could not open video file." << std::endl;
        return -1;
    }

    int outputWidth = 640;  // 420p width
    int outputHeight = 360; // 420p height

    cv::VideoWriter outputVideo("output_video.mp4", cv::VideoWriter::fourcc('H', '2', '6', '4'), 30, cv::Size(outputWidth, outputHeight), true);

    if (!outputVideo.isOpened()) {
        std::cerr << "Error: Could not create the output video file." << std::endl;
        return -1;
    }

    while (true) {
        cv::Mat frame;
        video >> frame;

        if (frame.empty()) {
            break;
        }   
        cv::resize(frame, frame, cv::Size(outputWidth, outputHeight));
        outputVideo.write(frame);
        //cv::imshow("Resized Video", frame);
    }
    video.release();
    outputVideo.release();
    cv::destroyAllWindows();

    return 0;
}