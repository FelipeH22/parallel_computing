#include <opencv2/opencv.hpp>

int main() {
    // Open the video file
    cv::VideoCapture video("input_video.mp4");

    if (!video.isOpened()) {
        std::cerr << "Error: Could not open video file." << std::endl;
        return -1;
    }

    // Define the output resolution
    int outputWidth = 640;  // 420p width
    int outputHeight = 360; // 420p height

    // Create a VideoWriter to save the output video
    cv::VideoWriter outputVideo("output_video.mp4", cv::VideoWriter::fourcc('H', '2', '6', '4'), 30, cv::Size(outputWidth, outputHeight), true);

    if (!outputVideo.isOpened()) {
        std::cerr << "Error: Could not create the output video file." << std::endl;
        return -1;
    }

    while (true) {
        cv::Mat frame;
        video >> frame;

        if (frame.empty()) {
            break; // End of video
        }

        // Resize the frame to the desired resolution
        cv::resize(frame, frame, cv::Size(outputWidth, outputHeight));

        // Write the resized frame to the output video
        outputVideo.write(frame);

        // Display the resized frame (optional)
        cv::imshow("Resized Video", frame);

        // Exit the loop if 'q' is pressed
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    // Release video objects
    video.release();
    outputVideo.release();
    cv::destroyAllWindows();

    return 0;
}
//g++ -o video_resizer video_resizer.cpp `pkg-config --cflags --libs opencv4`