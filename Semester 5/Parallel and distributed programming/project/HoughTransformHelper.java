import org.opencv.core.*;
import org.opencv.highgui.HighGui;
import org.opencv.imgproc.Imgproc;

import java.util.ArrayList;
import java.util.List;

public class HoughTransformHelper {
    public static Mat houghCirclesTransform(Mat sourceImage) {
        Mat result = sourceImage.clone();

        Mat gray = new Mat();
        Imgproc.cvtColor(result, gray, Imgproc.COLOR_BGR2GRAY);
        Imgproc.medianBlur(gray, gray, 5);

        Mat circles = new Mat();
        Imgproc.HoughCircles(gray, circles, Imgproc.HOUGH_GRADIENT, 1.0,
                (double)gray.rows() / 16, // change this value to detect circles with different distances to each other
                100.0, 30.0, 1, 30); // last two parameters can be changed

        // (min_radius & max_radius) to detect larger circles
        for (int x = 0; x < circles.cols(); x++) {
            double[] c = circles.get(0, x);
            Point center = new Point(Math.round(c[0]), Math.round(c[1]));

            // circle outline
            int radius = (int) Math.round(c[2]);
            Imgproc.circle(result, center, radius, new Scalar(255, 0, 255), 2, 8, 0);
        }

        return result;
    }

    public static Mat houghLinesTransform(Mat sourceImage) {
        Mat imageWithEdges = new Mat();

        // edge detection
        Imgproc.Canny(sourceImage, imageWithEdges, 50, 200, 3, false);

        // copy edges to the images that will display the results in BGR
        Mat imageWithLines = new Mat();
        Imgproc.cvtColor(imageWithEdges, imageWithLines, Imgproc.COLOR_GRAY2BGR);

        // will hold the results of the detection
        Mat lines = new Mat();

        // run the detection
        Imgproc.HoughLines(imageWithEdges, lines, 1, Math.PI/180, 150);

        // draw the lines
        for (int x = 0; x < lines.rows(); x++) {
            double rho = lines.get(x, 0)[0],
                    theta = lines.get(x, 0)[1];

            double a = Math.cos(theta), b = Math.sin(theta);
            double x0 = a*rho, y0 = b*rho;

            Point pt1 = new Point(Math.round(x0 + 1000*(-b)), Math.round(y0 + 1000*(a)));
            Point pt2 = new Point(Math.round(x0 - 1000*(-b)), Math.round(y0 - 1000*(a)));

            Imgproc.line(imageWithLines, pt1, pt2, new Scalar(0, 0, 255), 3, Imgproc.LINE_AA, 0);
        }

        return imageWithLines;
    }

    public static Mat houghProbabilisticLinesTransform(Mat sourceImage) {
        Mat imageWithEdges = new Mat();

        // edge detection
        Imgproc.Canny(sourceImage, imageWithEdges, 50, 200, 3, false);

        // copy edges to the images that will display the results in BGR
        Mat imageWithLines = new Mat();
        Imgproc.cvtColor(imageWithEdges, imageWithLines, Imgproc.COLOR_GRAY2BGR);

        // will hold the results of the detection
        Mat lines = new Mat();

        // run the detection
        Imgproc.HoughLinesP(imageWithEdges, lines, 1, Math.PI/180, 50, 50, 10);

        // draw the lines
        for (int x = 0; x < lines.rows(); x++) {
            double[] l = lines.get(x, 0);
            Imgproc.line(imageWithLines, new Point(l[0], l[1]), new Point(l[2], l[3]), new Scalar(0, 0, 255), 3, Imgproc.LINE_AA, 0);
        }

        return imageWithLines;
    }

    public static List<Mat> splitImageInChunksHorizontally(Mat sourceImage, int chunksNumber) {
        List<Mat> chunksList = new ArrayList<>();
        int chunkHeight = sourceImage.rows() / chunksNumber;
        int remainingRows = sourceImage.rows() % chunksNumber;

        int startRow = 0;
        for (int i = 0; i < chunksNumber; i++) {
            int currentChunkHeight = chunkHeight + (i < remainingRows ? 1 : 0);

            Rect roi = new Rect(0, startRow, sourceImage.cols(), currentChunkHeight);
            Mat chunk = new Mat(sourceImage, roi);
            chunksList.add(chunk);

            startRow += currentChunkHeight;
        }

        return chunksList;
    }

    public static Mat concatenateChunksVertically(List<Mat> chunks) {
        Mat result = new Mat();
        Core.vconcat(chunks, result);
        return result;
    }

    public static List<Mat> splitImageInChunksVertically(Mat sourceImage, int chunksNumber) {
        List<Mat> chunksList = new ArrayList<>();
        int chunkWidth = sourceImage.cols() / chunksNumber;
        int remainingCols = sourceImage.cols() % chunksNumber;

        int startCol = 0;
        for (int i = 0; i < chunksNumber; i++) {
            int currentChunkWidth = chunkWidth + (i < remainingCols ? 1 : 0);

            Rect roi = new Rect(startCol, 0, currentChunkWidth, sourceImage.rows());
            Mat chunk = new Mat(sourceImage, roi);
            chunksList.add(chunk);

            startCol += currentChunkWidth;
        }

        return chunksList;
    }

    public static Mat concatenateChunksHorizontally(List<Mat> chunks) {
        Mat result = new Mat();
        Core.hconcat(chunks, result);
        return result;
    }

    public static Mat uniteMat(Mat mat1, Mat mat2) {
        Mat result = new Mat();
        Core.bitwise_or(mat1, mat2, result);
        return result;
    }

    public static void displayChunks(List<Mat> chunks) {
        for (int i = 0; i < chunks.size(); i++) {
            Mat chunk = chunks.get(i);
            HighGui.imshow("Chunk " + i, chunk);
        }
    }
}
