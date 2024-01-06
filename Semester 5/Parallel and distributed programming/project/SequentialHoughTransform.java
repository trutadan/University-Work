import org.opencv.core.*;
import org.opencv.highgui.HighGui;
import org.opencv.imgcodecs.Imgcodecs;

public class SequentialHoughTransform {
    public static void run(String filename) {
        System.loadLibrary(Core.NATIVE_LIBRARY_NAME);

        // load the image
        Mat grayscaleSourceImage = Imgcodecs.imread(filename, Imgcodecs.IMREAD_GRAYSCALE);
        Mat colorSourceImage = Imgcodecs.imread(filename, Imgcodecs.IMREAD_COLOR);

        // check if image is loaded fine
        if(grayscaleSourceImage.empty() || colorSourceImage.empty()) {
            System.out.println("Error opening image!");
            System.exit(-1);
        }

        // Start measuring time
        long startTime = System.currentTimeMillis();

        // display the results of the hough transforms
        HighGui.imshow("source image", colorSourceImage);
        HighGui.imshow("detected circles", HoughTransformHelper.houghCirclesTransform(colorSourceImage));
        HighGui.imshow("detected lines", HoughTransformHelper.houghLinesTransform(grayscaleSourceImage));
        HighGui.imshow("detected probabilistic lines", HoughTransformHelper.houghProbabilisticLinesTransform(grayscaleSourceImage));

        // End measuring time
        long endTime = System.currentTimeMillis();

        // Calculate and print the elapsed time
        long elapsedTime = endTime - startTime;
        System.out.println("Elapsed Time: " + elapsedTime + " milliseconds");

        HighGui.waitKey();
        System.exit(0);
    }

    public static void main(String[] args) {
        SequentialHoughTransform.run("./example.png");
    }
}