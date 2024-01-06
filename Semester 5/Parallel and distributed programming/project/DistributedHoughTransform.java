import mpi.*;

import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.core.MatOfByte;
import org.opencv.highgui.HighGui;
import org.opencv.imgcodecs.Imgcodecs;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

record ChunkInputWrapper(byte[] grayscaleImageChunk, byte[] colorImageChunk) implements Serializable {
}

record ChunkOutputWrapper(byte[] chunkLines, byte[] chunkCircles, byte[] chunkProbabilisticLines) implements Serializable {
}

public class DistributedHoughTransform {
    static {
        System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
    }

    private static byte[] matToByteArray(Mat mat) {
        MatOfByte matOfByte = new MatOfByte();
        Imgcodecs.imencode(".png", mat, matOfByte);
        return matOfByte.toArray();
    }

    private static Mat byteArrayToMat(byte[] bytes) {
        return Imgcodecs.imdecode(new MatOfByte(bytes), Imgcodecs.IMREAD_UNCHANGED);
    }

    public static void administrator(String filename) {
        System.out.println("admin started...");

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

        int numberOfProcesses = MPI.COMM_WORLD.Size();
        int numberOfChunks = numberOfProcesses - 1;

        List<Mat> grayscaleImageChunks = HoughTransformHelper.splitImageInChunksHorizontally(grayscaleSourceImage, numberOfChunks);
        List<Mat> colorImageChunks = HoughTransformHelper.splitImageInChunksHorizontally(colorSourceImage, numberOfChunks);

//        List<Mat> grayscaleImageChunks = HoughTransformHelper.splitImageInChunksVertically(grayscaleSourceImage, numberOfChunks);
//        List<Mat> colorImageChunks = HoughTransformHelper.splitImageInChunksVertically(colorSourceImage, numberOfChunks);

        for (int process = 1; process < numberOfProcesses; process++){
            Mat grayscaleImageChunkAsMat = grayscaleImageChunks.get(process - 1);
            Mat colorImageChunkAsMat = colorImageChunks.get(process - 1);

            ChunkInputWrapper wrapper = new ChunkInputWrapper(matToByteArray(grayscaleImageChunkAsMat), matToByteArray(colorImageChunkAsMat));
            MPI.COMM_WORLD.Send(new Object[]{wrapper}, 0, 1, MPI.OBJECT, process, 0);
        }

        // lists to store the results for each all the transformations
        List<Mat> linesResultList = new ArrayList<>();
        List<Mat> circlesResultList = new ArrayList<>();
        List<Mat> probabilisticLinesResultList = new ArrayList<>();

        for (int process = 1; process < numberOfProcesses; process++){
            Object[] receivedObject = new Object[1];
            MPI.COMM_WORLD.Recv(receivedObject, 0, 1, MPI.OBJECT, process, 0);
            ChunkOutputWrapper chunkInputWrapper = (ChunkOutputWrapper) receivedObject[0];

            byte[] chunkLinesAsBytes = chunkInputWrapper.chunkLines();
            byte[] chunkCirclesAsBytes = chunkInputWrapper.chunkCircles();
            byte[] chunkProbabilisticLinesAsBytes = chunkInputWrapper.chunkProbabilisticLines();

            Mat chunkLinesAsMat = byteArrayToMat(chunkLinesAsBytes);
            Mat chunkCirclesAsMat = byteArrayToMat(chunkCirclesAsBytes);
            Mat chunkProbabilisticLinesAsMat = byteArrayToMat(chunkProbabilisticLinesAsBytes);

            linesResultList.add(chunkLinesAsMat);
            circlesResultList.add(chunkCirclesAsMat);
            probabilisticLinesResultList.add(chunkProbabilisticLinesAsMat);
        }

        Mat linesImage = HoughTransformHelper.concatenateChunksVertically(linesResultList);
        Mat circlesImage = HoughTransformHelper.concatenateChunksVertically(circlesResultList);
        Mat probabilisticLinesImage = HoughTransformHelper.concatenateChunksVertically(probabilisticLinesResultList);

//        Mat linesImage = HoughTransformHelper.concatenateChunksHorizontally(linesResultList);
//        Mat circlesImage = HoughTransformHelper.concatenateChunksHorizontally(circlesResultList);
//        Mat probabilisticLinesImage = HoughTransformHelper.concatenateChunksHorizontally(probabilisticLinesResultList);

        // display the results of the hough transforms
        HighGui.imshow("source image", colorSourceImage);
        HighGui.imshow("detected lines",linesImage);
        HighGui.imshow("detected circles", circlesImage);
        HighGui.imshow("detected probabilistic lines", probabilisticLinesImage);

        // End measuring time
        long endTime = System.currentTimeMillis();

        // Calculate and print the elapsed time
        long elapsedTime = endTime - startTime;
        System.out.println("Elapsed Time: " + elapsedTime + " milliseconds");

        System.out.println("admin finished...");

        HighGui.waitKey();
        System.exit(0);
    }

    public static void worker() {
        int id = MPI.COMM_WORLD.Rank();
        System.out.println("worker " + id + " started...");

        Object[] receivedObject = new Object[1];
        MPI.COMM_WORLD.Recv(receivedObject, 0, 1, MPI.OBJECT, 0, 0);
        ChunkInputWrapper chunkInputWrapper = (ChunkInputWrapper) receivedObject[0];

        byte[] receivedGrayscaleChunkAsBytes = chunkInputWrapper.grayscaleImageChunk();
        byte[] receivedColorChunkAsBytes = chunkInputWrapper.colorImageChunk();

        Mat receivedGrayscaleChunkAsMat = byteArrayToMat(receivedGrayscaleChunkAsBytes);
        Mat receivedColorChunkAsMat = byteArrayToMat(receivedColorChunkAsBytes);

        Mat chunkLinesAsMat = HoughTransformHelper.houghLinesTransform(receivedGrayscaleChunkAsMat);
        Mat chunkCirclesAsMat = HoughTransformHelper.houghCirclesTransform(receivedColorChunkAsMat);
        Mat chunkProbabilisticLinesAsMat = HoughTransformHelper.houghProbabilisticLinesTransform(receivedGrayscaleChunkAsMat);

        byte[] chunkLinesAsBytes = matToByteArray(chunkLinesAsMat);
        byte[] chunkCirclesAsBytes = matToByteArray(chunkCirclesAsMat);
        byte[] chunkProbabilisticLinesAsBytes = matToByteArray(chunkProbabilisticLinesAsMat);

        ChunkOutputWrapper wrapper = new ChunkOutputWrapper(chunkLinesAsBytes, chunkCirclesAsBytes, chunkProbabilisticLinesAsBytes);
        MPI.COMM_WORLD.Send(new Object[]{wrapper}, 0, 1, MPI.OBJECT, 0, 0);

        System.out.println("worker " + id + " finished...");
    }

    public static void main(String[] args) {
        MPI.Init(args);

        int id = MPI.COMM_WORLD.Rank();

        if (id == 0) {
            DistributedHoughTransform.administrator("./example.png");
        } else {
            DistributedHoughTransform.worker();
        }

        MPI.Finalize();
    }
}

