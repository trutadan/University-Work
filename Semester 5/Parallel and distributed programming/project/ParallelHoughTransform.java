import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.highgui.HighGui;
import org.opencv.imgcodecs.Imgcodecs;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.*;

public class ParallelHoughTransform {
    private static final int THREADS_NUMBER = 8;
    private static final int CHUNKS_NUMBER = 2;

    public static List<List<Mat>> parallelImageProcessing(List<Mat> grayscaleImageChunks, List<Mat> colorImageChunks) {
        // create a thread pool with a fixed number of threads
        ExecutorService executor = Executors.newFixedThreadPool(THREADS_NUMBER);

        // lists to store the futures for each type of transformation
        List<Future<Mat>> linesTransformFutures = new ArrayList<>();
        List<Future<Mat>> circlesTransformFutures = new ArrayList<>();
        List<Future<Mat>> probabilisticLinesTransformFutures = new ArrayList<>();

        // submit tasks for each chunk to perform the transformations in parallel
        for (Mat chunk : grayscaleImageChunks) {
            // task for Hough Lines transformation
            Callable<Mat> linesTask = () -> HoughTransformHelper.houghLinesTransform(chunk);
            Future<Mat> linesFuture = executor.submit(linesTask);
            linesTransformFutures.add(linesFuture);

            // task for Hough Probabilistic Lines transformation
            Callable<Mat> probabilisticLinesTask = () -> HoughTransformHelper.houghProbabilisticLinesTransform(chunk);
            Future<Mat> probabilisticLinesFuture = executor.submit(probabilisticLinesTask);
            probabilisticLinesTransformFutures.add(probabilisticLinesFuture);
        }

        for (Mat chunk : colorImageChunks) {
            // task for Hough Circles transformation
            Callable<Mat> circlesTask = () -> HoughTransformHelper.houghCirclesTransform(chunk);
            Future<Mat> circlesFuture = executor.submit(circlesTask);
            circlesTransformFutures.add(circlesFuture);
        }

        // lists to store the results for each type of transformation
        List<Mat> linesResultList = new ArrayList<>();
        List<Mat> circlesResultList = new ArrayList<>();
        List<Mat> probabilisticLinesResultList = new ArrayList<>();

        // collect the results from the futures
        for (int i = 0; i < grayscaleImageChunks.size(); i++) {
            try {
                // get the result for Hough Lines transformation
                Mat linesResult = linesTransformFutures.get(i).get();
                linesResultList.add(linesResult);

                // get the result for Hough Circles transformation
                Mat circlesResult = circlesTransformFutures.get(i).get();
                circlesResultList.add(circlesResult);

                // get the result for Hough Probabilistic Lines transformation
                Mat probabilisticLinesResult = probabilisticLinesTransformFutures.get(i).get();
                probabilisticLinesResultList.add(probabilisticLinesResult);
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
            }
        }

        executor.shutdown();

        // create a list to store the results for each type of transformation
        List<List<Mat>> results = new ArrayList<>();
        results.add(linesResultList);
        results.add(circlesResultList);
        results.add(probabilisticLinesResultList);

        return results;
    }

    private static List<Mat> processHorizontalChunks(Mat grayscaleSourceImage, Mat colorSourceImage) {
        List<Mat> grayscaleImageChunks = HoughTransformHelper.splitImageInChunksHorizontally(grayscaleSourceImage, CHUNKS_NUMBER);
        List<Mat> colorImageChunks = HoughTransformHelper.splitImageInChunksHorizontally(colorSourceImage, CHUNKS_NUMBER);

        List<Mat> linesProcessedChunks = parallelImageProcessing(grayscaleImageChunks, colorImageChunks).get(0);
        List<Mat> circlesProcessedChunks = parallelImageProcessing(grayscaleImageChunks, colorImageChunks).get(1);
        List<Mat> probabilisticLinesProcessedChunks = parallelImageProcessing(grayscaleImageChunks, colorImageChunks).get(2);

        // display the processed chunks
        // HoughTransformHelper.displayChunks(linesProcessedChunks);

        // display the processed chunks
        // HoughTransformHelper.displayChunks(circlesProcessedChunks);

        // display the processed chunks
        // HoughTransformHelper.displayChunks(probabilisticLinesProcessedChunks);

        List<Mat> results = new ArrayList<>();
        results.add(HoughTransformHelper.concatenateChunksVertically(linesProcessedChunks));
        results.add(HoughTransformHelper.concatenateChunksVertically(circlesProcessedChunks));
        results.add(HoughTransformHelper.concatenateChunksVertically(probabilisticLinesProcessedChunks));

        return results;
    }

    private static List<Mat> processVerticalChunks(Mat grayscaleSourceImage, Mat colorSourceImage) {
        List<Mat> grayscaleImageChunks = HoughTransformHelper.splitImageInChunksVertically(grayscaleSourceImage, CHUNKS_NUMBER);
        List<Mat> colorImageChunks = HoughTransformHelper.splitImageInChunksVertically(colorSourceImage, CHUNKS_NUMBER);

        List<Mat> linesProcessedChunks = parallelImageProcessing(grayscaleImageChunks, colorImageChunks).get(0);
        List<Mat> circlesProcessedChunks = parallelImageProcessing(grayscaleImageChunks, colorImageChunks).get(1);
        List<Mat> probabilisticLinesProcessedChunks = parallelImageProcessing(grayscaleImageChunks, colorImageChunks).get(2);

        // display the processed chunks
        // HoughTransformHelper.displayChunks(linesProcessedChunks);

        // display the processed chunks
        // HoughTransformHelper.displayChunks(circlesProcessedChunks);

        // display the processed chunks
        // HoughTransformHelper.displayChunks(probabilisticLinesProcessedChunks);

        List<Mat> results = new ArrayList<>();
        results.add(HoughTransformHelper.concatenateChunksHorizontally(linesProcessedChunks));
        results.add(HoughTransformHelper.concatenateChunksHorizontally(circlesProcessedChunks));
        results.add(HoughTransformHelper.concatenateChunksHorizontally(probabilisticLinesProcessedChunks));

        return results;
    }

    private static List<Mat> processHorizontalAndVerticalChunks(Mat grayscaleSourceImage, Mat colorSourceImage) {
        List<Mat> processedHorizontalChunks = processHorizontalChunks(grayscaleSourceImage, colorSourceImage);
        List<Mat> processedVerticalChunks = processVerticalChunks(grayscaleSourceImage, colorSourceImage);

        List<Mat> results = new ArrayList<>();
        for (int index = 0; index < processedHorizontalChunks.size(); index++) {
            results.add(HoughTransformHelper.uniteMat(processedHorizontalChunks.get(index), processedVerticalChunks.get(index)));
        }

        return results;
    }

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

        // start measuring time
        long startTime = System.currentTimeMillis();

        List<Mat> resultingImages = processHorizontalChunks(grayscaleSourceImage, colorSourceImage);
        // List<Mat> resultingImages = processVerticalChunks(grayscaleSourceImage, colorSourceImage);
//         List<Mat> resultingImages = processHorizontalAndVerticalChunks(grayscaleSourceImage, colorSourceImage);

        Mat linesImage = resultingImages.get(0);
        Mat circlesImage = resultingImages.get(1);
        Mat probabilisticLinesImage = resultingImages.get(2);

        HighGui.imshow("source image", colorSourceImage);
        HighGui.imshow("detected lines",linesImage);
        HighGui.imshow("detected circles", circlesImage);
        HighGui.imshow("detected probabilistic lines", probabilisticLinesImage);

        // end measuring time
        long endTime = System.currentTimeMillis();

        // calculate and print the elapsed time
        long elapsedTime = endTime - startTime;
        System.out.println("Elapsed Time: " + elapsedTime + " milliseconds");

        HighGui.waitKey();
        System.exit(0);
    }

    public static void main(String[] args) {
        ParallelHoughTransform.run("./example.png");
    }
}
