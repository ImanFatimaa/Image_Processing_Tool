//libraries for open cv
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
using namespace cv;
Mat editedImage;
class image {
    Mat originalImage; //Privatemembers
    
public:
    //Loading and displaying image
    void loadAndDisplayImage() {
        string imagePath;
        // Ask the user to enter the image file path
        cout << "Enter the path to the image file (e.g., image.jpg): ";
        cin >> imagePath;
        
        // Load the image from the specified path
        originalImage = imread(imagePath);

        // Check if the image was loaded successfully
        if (originalImage.empty()) {
            cout << "Failed to load the image!" << endl;
            return;
        }

        // Display the loaded image
        imshow("Original Image", originalImage);
        waitKey(0);

        // Create a copy of the original image for editing
        editedImage = originalImage.clone();
    }
    //Preview image after editing
    void editAndPreviewImage() {
        imshow("Edited Image Preview", editedImage);
        waitKey(0);

    }
    //Resizng function
    void resizeImage(int width, int height) {
        // Resize the image while maintaining its aspect ratio
        Mat resizedImage;
        resize(editedImage, resizedImage, cv::Size(width, height));

        // Update the editedimage with the resized image
        editedImage = resizedImage;
    }
    //Cropping function
    void cropImage(int x, int y, int width, int height) {
        // Crop the image to the selected region
        Rect regionOfInterest(x, y, width, height);
        editedImage = editedImage(regionOfInterest);
    }
    //Rotated image function
    void rotateImage(double angleDegrees) {
        // Rotate the image by the specified angle in degrees
        Point2f center(editedImage.cols / 2, editedImage.rows / 2);
        Mat rotationMatrix = getRotationMatrix2D(center, angleDegrees, 1.0);
        warpAffine(editedImage, editedImage, rotationMatrix, editedImage.size());
    }
    //brightness and contrast function
    void changeBrightnessAndContrast(int brightness, int contrast) {
        Mat res = Mat::zeros(editedImage.size(), editedImage.type());
        editedImage.convertTo(res, -1, brightness / 100.0, contrast / 100.0);
        editedImage = res;
    }
    //gray image function
    void grayscale() {
       // editedImage = cvtColor(editedImage, COLOR_BGR2GRAY);
       cvtColor(editedImage, editedImage, COLOR_BGR2GRAY);
    }
    //blur image function
    void blurimage(int b) {
        blur(editedImage, editedImage, Size(b, b));
    }
    //sharpenimage function
    void sharpenimage() {
        Mat kernel3 = (Mat_<double>(3, 3) << 0, -1, 0,
            -1, 5, -1,
            0, -1, 0);
        filter2D(editedImage,editedImage, -1, kernel3, Point(-1, -1), 0, BORDER_DEFAULT);
    }
};
int main() {
    image obj;
    int chk = 1; //for loop to continue till user wants to edit
    obj.loadAndDisplayImage(); //loading and displaying image
    do {
        if (chk == 1) {
            int choice; //for switching

            // Show a menu of options for the user
            cout << "Image Processing Menu:" << endl;
            cout << "1. Resize Image" << endl;
            cout << "2. Crop Image" << endl;
            cout << "3. Rotate Image" << endl;
            cout << "4. Brightness and Contrast Adjustments" << endl;
            cout << "5. Convert to Grey Image" << endl;
            cout << "6. Sharpen Image" << endl;
            cout << "7. Blur Image" << endl;
            cout << "Enter your choice (1-7): ";
            cin >> choice;
            //switch to edit image according to user
            switch (choice) {
            case 1:
                //new width or height for resizing
                int newWidth, newHeight;
                cout << "Enter the new width: ";
                cin >> newWidth;
                cout << "Enter the new height: ";
                cin >> newHeight;
                obj.resizeImage(newWidth, newHeight);
                break;
            case 2:
                //new dimensons for cropping of image
                int cropX, cropY, cropWidth, cropHeight;
                std::cout << "Enter the x-coordinate of the top-left corner: ";
                cin >> cropX;
                cout << "Enter the y-coordinate of the top-left corner: ";
                cin >> cropY;
                cout << "Enter the width of the cropped region: ";
                cin >> cropWidth;
                cout << "Enter the height of the cropped region: ";
                cin >> cropHeight;
                obj.cropImage(cropX, cropY, cropWidth, cropHeight);
                break;
            case 3:
                //for rotating image at a specific angle
                double rotationAngle;
                cout << "Enter the rotation angle in degrees: ";
                cin >> rotationAngle;
                obj.rotateImage(rotationAngle);
                break;
            case 4:
                //for brightness and contrast 
                cout << "entre brightness level: ";
                int x, y;
                cin >> x;
                cout << "entre contrast level: ";
                cin >> y;
                obj.changeBrightnessAndContrast(x, y);
                break;
            case 5:
                //for grayimage
                obj.grayscale();
                break;
            case 6:
                //for sharpen of image
                obj.sharpenimage();
                break;
            case 7:
                //blurr image factors
                cout << "Entre Blur factor: ";
                int b;
                cin >> b;
                obj.blurimage(b);
                break;
            //deafult case
            default:
                cout << "Invalid choice. Please enter a valid option (1-5)." << endl;
                break;
            }
            //preview image before saving
            obj.editAndPreviewImage();
            cout << "press 1 to continue to image edior or zero to end program:  ";
            cin >> chk;
        }
    } while (chk == 1);
    //saving image if user wants to save
    cout << "press 1 to save changes and 0 to discard changes: ";
    int save;
    cin >> save;
    //for saving new edited image
    if (save == 1) {
        imwrite("edited_image", editedImage);
        cout << "edited image is saved\n";
    }
    else {
        //if user do not want to save image
        cout << "edited image is discard\n";
    }
    return 0;
}





