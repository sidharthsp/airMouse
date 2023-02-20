#include <opencv2/opencv.hpp>
int main(int argc, char** argv) {
    // Load the Haar cascade classifier for palm detection
    cv::CascadeClassifier cascade("palm.xml");

    // Load the input image or video
    cv::VideoCapture cap(0);

    // Check if the input is loaded successfully
    if (!cap.isOpened()) {
        std::cout << "Error: Unable to open the input source."<< std::endl;
               return -1;
                   }    // Loop through each frame of the video
                      while (cap.isOpened()) {
                                cv::Mat frame;       
                                cap >>frame;

        // Check if the frame is empty
        if (frame.empty()) {
            break;
        }

        // Convert the frame to grayscale
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Detect palm in the frame
        std::vector<cv::Rect> palms;
        cascade.detectMultiScale(gray, palms, 1.1, 2, 0, cv::Size(30, 30));

        // Draw rectangles around the detected palms
        for (const cv::Rect& palm : palms) {
            cv::rectangle(frame, palm, cv::Scalar(0, 255, 0), 2);
        }

        // Display the processed frame
        cv::imshow("Palm Detection", frame);

        // Check if the user has pressed the 'esc' key
        if (cv::waitKey(30) == 27) {
            break;
        }
    }

    // Release the video capture
    cap.release();

    return 0;
}
