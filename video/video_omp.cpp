#include <opencv2/opencv.hpp>
#include <iostream>
#include <omp.h>

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

    // Determine the number of threads to use (adjust as needed)
    int numThreads = omp_get_max_threads();

    while (true) {
        cv::Mat frame;
        video >> frame;

        if (frame.empty()) {
            break;
        }

        // Parallelize frame processing
        #pragma omp parallel num_threads(numThreads)
        {
            int thread_id = omp_get_thread_num();
            int start = (frame.rows / numThreads) * thread_id;
            int end = (thread_id == numThreads - 1) ? frame.rows : (frame.rows / numThreads) * (thread_id + 1);

            cv::Mat framePart = frame.rowRange(start, end);
            cv::Mat resizedFrame;
            cv::resize(framePart, resizedFrame, cv::Size(outputWidth, outputHeight));

            #pragma omp critical
            {
                outputVideo.write(resizedFrame);
            }
        }

        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    video.release();
    outputVideo.release();
    cv::destroyAllWindows();

    return 0;
}
