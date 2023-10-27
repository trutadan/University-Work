import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class Main {
    public static void main(String[] args) {
        // create matrices of a certain size
        int matrixSize = 250;
        Matrix matrix1 = new Matrix(matrixSize, matrixSize);
        Matrix matrix2 = new Matrix(matrixSize, matrixSize);

        // populate the matrices with random values
        matrix1.populateMatrix(1, 10);
        matrix2.populateMatrix(1, 10);

        // print the matrices
        System.out.println("Matrix 1:");
        System.out.println(matrix1);
        System.out.println("Matrix 2:");
        System.out.println(matrix2);

        int numberOfTasks = 10;

        // perform matrix multiplication using row approach and measure performance
        System.out.println("Matrix multiplication using row tasks:");
        Matrix resultRowTasks = multiplyUsingRowTasks(matrix1, matrix2, numberOfTasks);
//        System.out.println("Result using row tasks:");
//        System.out.println(resultRowTasks);

        // perform matrix multiplication using thread pools and row approach and measure performance
        System.out.println("Matrix multiplication using row tasks with ThreadPool:");
        Matrix resultRowTasksThreadPool = multiplyUsingRowTasksThreadPool(matrix1, matrix2, numberOfTasks);
//        System.out.println("Result using row tasks with ThreadPool:");
//        System.out.println(resultRowTasksThreadPool);

        // check if the implementations have the same result
        checkMatrixEquivalence(resultRowTasksThreadPool, resultRowTasks);

        // perform matrix multiplication using column approach and measure performance
        System.out.println("Matrix multiplication using column tasks:");
        Matrix resultColumnTasks = multiplyUsingColumnTasks(matrix1, matrix2, numberOfTasks);
//        System.out.println("Result using column tasks:");
//        System.out.println(resultColumnTasks);

        // perform matrix multiplication using thread pools and column approach and measure performance
        System.out.println("Matrix multiplication using column tasks with ThreadPool:");
        Matrix resultColumnTasksThreadPool = multiplyUsingColumnTasksThreadPool(matrix1, matrix2, numberOfTasks);
//        System.out.println("Result using column tasks with ThreadPool:");
//        System.out.println(resultColumnTasksThreadPool);

        // check if the implementations have the same result
        checkMatrixEquivalence(resultColumnTasksThreadPool, resultColumnTasks);

        // perform matrix multiplication using kth approach and measure performance
        System.out.println("Matrix multiplication using k-th tasks:");
        Matrix resultKthTasks = multiplyUsingKthTasks(matrix1, matrix2, numberOfTasks);
//        System.out.println("Result using k-th tasks:");
//        System.out.println(resultKthTasks);

        // perform matrix multiplication using thread pools and kth approach and measure performance
        System.out.println("Matrix multiplication using k-th tasks with ThreadPool:");
        Matrix resultKthTasksThreadPool = multiplyUsingKthTasksThreadPool(matrix1, matrix2, numberOfTasks);
//        System.out.println("Result using k-th tasks with ThreadPool:");
//        System.out.println(resultKthTasksThreadPool);

        // check if the implementations have the same result
        checkMatrixEquivalence(resultKthTasksThreadPool, resultKthTasks);

        System.out.println("Checking all the implementations...");
        // check if all implementations have the same result
        checkMatrixEquivalence(resultRowTasks, resultColumnTasks);
        checkMatrixEquivalence(resultColumnTasks, resultKthTasks);
    }

    // helper method to perform matrix multiplication using row tasks
    public static Matrix multiplyUsingRowTasks(Matrix matrix1, Matrix matrix2, int numberOfTasks) {
        long startTime = System.currentTimeMillis();

        Integer[][] result = new Integer[matrix1.getNumberOfRows()][matrix2.getNumberOfColumns()];
        Thread[] threads = new Thread[numberOfTasks];
        int elementsPerTask = (matrix1.getNumberOfRows() * matrix2.getNumberOfColumns()) / numberOfTasks;

        for (int index = 0; index < numberOfTasks; index++) {
            int left = index * elementsPerTask;
            int right = index == numberOfTasks - 1 ? matrix1.getNumberOfRows() * matrix2.getNumberOfColumns() : (index + 1) * elementsPerTask;

            threads[index] = new Thread(new RowTask(result, matrix1, matrix2, left, right));
            threads[index].start();
        }

        for (Thread thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException exception) {
                System.out.println(exception.getMessage());
            }
        }

        long endTime = System.currentTimeMillis();
        System.out.println("Row tasks took " + (endTime - startTime) + " milliseconds");

        return new Matrix(result);
    }

    // helper method to perform matrix multiplication using column tasks
    public static Matrix multiplyUsingColumnTasks(Matrix matrix1, Matrix matrix2, int numberOfTasks) {
        long startTime = System.currentTimeMillis();

        Integer[][] result = new Integer[matrix1.getNumberOfRows()][matrix2.getNumberOfColumns()];
        Thread[] threads = new Thread[numberOfTasks];
        int elementsPerTask = (matrix1.getNumberOfRows() * matrix2.getNumberOfColumns()) / numberOfTasks;

        for (int index = 0; index < numberOfTasks; index++) {
            int left = index * elementsPerTask;
            int right = index == numberOfTasks - 1 ? matrix1.getNumberOfRows() * matrix2.getNumberOfColumns() : (index + 1) * elementsPerTask;

            threads[index] = new Thread(new ColumnTask(result, matrix1, matrix2, left, right));
            threads[index].start();
        }

        for (Thread thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException exception) {
                System.out.println(exception.getMessage());
            }
        }

        long endTime = System.currentTimeMillis();
        System.out.println("Column tasks took " + (endTime - startTime) + " milliseconds");

        return new Matrix(result);
    }

    // Helper method to perform matrix multiplication using k-th tasks
    public static Matrix multiplyUsingKthTasks(Matrix matrix1, Matrix matrix2, int numberOfTasks) {
        long startTime = System.currentTimeMillis();

        Integer[][] resultingMatrix = new Integer[matrix1.getNumberOfRows()][matrix2.getNumberOfColumns()];
        Thread[] threads = new Thread[numberOfTasks];

        for (int index = 0; index < numberOfTasks; index++) {
            threads[index] = new Thread(new KthTask(resultingMatrix, matrix1, matrix2, index, numberOfTasks));
            threads[index].start();
        }

        for (Thread thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException exception) {
                System.out.println(exception.getMessage());
            }
        }

        long endTime = System.currentTimeMillis();
        System.out.println("K-th tasks took " + (endTime - startTime) + " milliseconds");

        return new Matrix(resultingMatrix);
    }

    public static Matrix multiplyUsingRowTasksThreadPool(Matrix matrix1, Matrix matrix2, int numberOfTasks) {
        long startTime = System.currentTimeMillis();
        int poolSize = numberOfTasks/3;

        Integer[][] result = new Integer[matrix1.getNumberOfRows()][matrix2.getNumberOfColumns()];
        ExecutorService executorService = Executors.newFixedThreadPool(poolSize);
        int elementsPerTask = (matrix1.getNumberOfRows() * matrix2.getNumberOfColumns()) / numberOfTasks;

        for (int index = 0; index < numberOfTasks; index++) {
            int left = index * elementsPerTask;
            int right = index == numberOfTasks - 1 ? matrix1.getNumberOfRows() * matrix2.getNumberOfColumns() : (index + 1) * elementsPerTask;

            executorService.submit(new RowTask(result, matrix1, matrix2, left, right));
        }

        executorService.shutdown();
        try {
            executorService.awaitTermination(Long.MAX_VALUE, TimeUnit.NANOSECONDS);
        } catch (InterruptedException exception) {
            System.out.println(exception.getMessage());
        }

        long endTime = System.currentTimeMillis();
        System.out.println("Row tasks with ThreadPool took " + (endTime - startTime) + " milliseconds");

        return new Matrix(result);
    }

    public static Matrix multiplyUsingColumnTasksThreadPool(Matrix matrix1, Matrix matrix2, int numberOfTasks) {
        long startTime = System.currentTimeMillis();
        int poolSize = numberOfTasks/3;

        Integer[][] result = new Integer[matrix1.getNumberOfRows()][matrix2.getNumberOfColumns()];
        ExecutorService executorService = Executors.newFixedThreadPool(poolSize);
        int elementsPerTask = (matrix1.getNumberOfRows() * matrix2.getNumberOfColumns()) / numberOfTasks;

        for (int index = 0; index < numberOfTasks; index++) {
            int left = index * elementsPerTask;
            int right = index == numberOfTasks - 1 ? matrix1.getNumberOfRows() * matrix2.getNumberOfColumns() : (index + 1) * elementsPerTask;

            executorService.submit(new ColumnTask(result, matrix1, matrix2, left, right));
        }

        executorService.shutdown();
        try {
            executorService.awaitTermination(Long.MAX_VALUE, TimeUnit.NANOSECONDS);
        } catch (InterruptedException exception) {
            System.out.println(exception.getMessage());
        }

        long endTime = System.currentTimeMillis();
        System.out.println("Column tasks with ThreadPool took " + (endTime - startTime) + " milliseconds");

        return new Matrix(result);
    }

    public static Matrix multiplyUsingKthTasksThreadPool(Matrix matrix1, Matrix matrix2, int numberOfTasks) {
        long startTime = System.currentTimeMillis();
        int poolSize = numberOfTasks/3;

        Integer[][] resultingMatrix = new Integer[matrix1.getNumberOfRows()][matrix2.getNumberOfColumns()];
        ExecutorService executorService = Executors.newFixedThreadPool(poolSize);

        for (int index = 0; index < numberOfTasks; index++) {
            executorService.submit(new KthTask(resultingMatrix, matrix1, matrix2, index, numberOfTasks));
        }

        executorService.shutdown();
        try {
            executorService.awaitTermination(Long.MAX_VALUE, TimeUnit.NANOSECONDS);
        } catch (InterruptedException exception) {
            System.out.println(exception.getMessage());
        }

        long endTime = System.currentTimeMillis();
        System.out.println("K-th tasks with ThreadPool took " + (endTime - startTime) + " milliseconds");

        return new Matrix(resultingMatrix);
    }

    // Helper method to check if two matrices are equivalent
    public static void checkMatrixEquivalence(Matrix matrix1, Matrix matrix2) {
        if (matrix1.equals(matrix2)) {
            System.out.println("Matrices are equivalent.");
        } else {
            System.out.println("Matrices are not equivalent.");
        }
    }
}
