# Colored Geometric Shape Detection with OpenCV

This C++ program utilizes the OpenCV library to detect and classify colored geometric shapes in an image. Below is a breakdown of its main components and operations:

## Components:

1. **Include Statements**:
   - `#include <iostream>`: Provides basic input/output services.
   - `#include <opencv2/opencv.hpp>`: Includes all OpenCV functionalities.

2. **Namespace Usage**:
   - `using namespace std;`: Allows elements from the `std` namespace to be used without specifying the namespace.
   - `using namespace cv;`: Allows elements from the `cv` namespace (OpenCV) to be used without specifying the namespace.

3. **Main Function**:
   - `main()`: The entry point of the program.

4. **Color Definitions**:
   - `lower` and `upper`: Maps defining the lower and upper bounds of each color in the HSV (Hue, Saturation, Value) color space. Used to create masks for each color.
   - `colors`: Maps defining the BGR (Blue, Green, Red) tuple of each color for drawing text on detected shapes.

5. **Image Loading and Preprocessing**:
   - `Mat frame = imread(...)`: Loads an image from a specified file path.
   - `GaussianBlur()`: Applies Gaussian blurring to the image to reduce noise.

## Operations:

1. **Color Detection**:
   - The program identifies colored shapes by applying color masks using the specified lower and upper bounds for each color.

2. **Shape Detection**:
   - Utilizes contours to detect geometric shapes in the image.

3. **Classification and Annotation**:
   - Classifies detected shapes based on their color and draws text labels using the predefined color map.

4. **Display**:
   - Renders the annotated image with detected shapes and color labels.

## Usage:

1. Compile the program with OpenCV installed.
2. Run the executable and provide the path to the image file.
3. The program will display the original image with annotated colored shapes.

## Note:
- Ensure you have OpenCV installed and properly configured before compiling and running the program.
- Experiment with different images to observe the detection and classification of colored geometric shapes.

## License:
This program is provided under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments:
Special thanks to the developers of OpenCV for their invaluable contributions to computer vision and image processing.
