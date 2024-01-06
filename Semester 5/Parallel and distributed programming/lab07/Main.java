import mpi.*;

import java.util.ArrayList;
import java.util.List;

public class Main {
    private static final int POLYNOMIAL_ORDER = 10000;

    private static void mainProcess(Polynomial first, Polynomial second, int processesCount) {
        long startTime = System.currentTimeMillis();

        int currentStartDegree, currentFinishDegree = 0;
        int lengthRangeDegrees = (first.getDegree() + 1 ) / (processesCount - 1);

        for (int i = 1; i < processesCount; i++) {
            currentStartDegree = currentFinishDegree;

            if (i == processesCount - 1) {
                currentFinishDegree = first.getDegree() + 1;
            } else {
                currentFinishDegree += lengthRangeDegrees;
            }

            MPI.COMM_WORLD.Send(new Object[]{first}, 0, 1, MPI.OBJECT, i, 0);
            MPI.COMM_WORLD.Send(new Object[]{second}, 0, 1, MPI.OBJECT, i, 0);

            MPI.COMM_WORLD.Send(new int[]{currentStartDegree}, 0, 1, MPI.INT, i, 0);
            MPI.COMM_WORLD.Send(new int[]{currentFinishDegree}, 0, 1, MPI.INT, i, 0);
        }

        Object[] results = new Object[processesCount - 1];
        for (int i = 1; i < processesCount; i++) {
            MPI.COMM_WORLD.Recv(results, i - 1, 1, MPI.OBJECT, i, 0);
        }

        List<Integer> coefficients = new ArrayList<>();
        int productDegree = first.getDegree() + second.getDegree();
        for (int degree = 0; degree <= productDegree; degree++) {
            coefficients.add(0);
        }

        for (int degree = 0; degree <= productDegree; degree++) {
            for (Object object : results) {
                int newValue = coefficients.get(degree) + ((Polynomial) object).getCoefficients().get(degree);
                coefficients.set(degree, newValue);
            }
        }

        Polynomial result = new Polynomial(coefficients);

        long endTime = System.currentTimeMillis();

        Polynomial expectedResult = Polynomial.getRegularSequentialProduct(first, second);

        System.out.println("Result : " + result);
        System.out.println("Expected result : " + expectedResult);
        System.out.println("Are the results equivalent: " + Polynomial.equals(result, expectedResult));
        System.out.println("Time: " + (endTime - startTime) + " ms");

        // karatsuba might actually be slower since there are made a lot of useless computations
        // (a lot of times the first polynomial is full of zeros)
    }

    private static void multiplySimpleWorker() {
        Object[] firstAsObject = new Object[2];
        Object[] secondAsObject = new Object[2];

        int[] startDegree = new int[1];
        int[] finishDegree = new int[1];

        MPI.COMM_WORLD.Recv(firstAsObject, 0, 1, MPI.OBJECT, 0, 0);
        MPI.COMM_WORLD.Recv(secondAsObject, 0, 1, MPI.OBJECT, 0, 0);

        MPI.COMM_WORLD.Recv(startDegree, 0, 1, MPI.INT, 0, 0);
        MPI.COMM_WORLD.Recv(finishDegree, 0, 1, MPI.INT, 0, 0);

        Polynomial first = (Polynomial) firstAsObject[0];
        Polynomial second = (Polynomial) secondAsObject[0];

        Polynomial result = Polynomial.getRegularSequentialProductInGivenRange(first, second, startDegree[0], finishDegree[0]);

        MPI.COMM_WORLD.Send(new Object[]{result}, 0, 1, MPI.OBJECT, 0, 0);
    }

    private static void multiplyKaratsubaWorker() {
        Object[] firstAsObject = new Object[2];
        Object[] secondAsObject = new Object[2];

        int[] begin = new int[1];
        int[] end = new int[1];

        MPI.COMM_WORLD.Recv(firstAsObject, 0, 1, MPI.OBJECT, 0, 0);
        MPI.COMM_WORLD.Recv(secondAsObject, 0, 1, MPI.OBJECT, 0, 0);

        MPI.COMM_WORLD.Recv(begin, 0, 1, MPI.INT, 0, 0);
        MPI.COMM_WORLD.Recv(end, 0, 1, MPI.INT, 0, 0);

        Polynomial first = (Polynomial) firstAsObject[0];
        Polynomial second = (Polynomial) secondAsObject[0];

        List<Integer> firstPolynomialCoefficients = first.getCoefficients();

        for (int i = 0; i < begin[0]; i++) {
            firstPolynomialCoefficients.set(i, 0);
        }

        for (int j = end[0]; j < firstPolynomialCoefficients.size(); j++) {
            firstPolynomialCoefficients.set(j, 0);
        }

        Polynomial result = Polynomial.getKaratsubaSequentialProduct(first, second);

        MPI.COMM_WORLD.Send(new Object[]{result}, 0, 1, MPI.OBJECT, 0, 0);
    }

    public static void main(String[] args) {
        // initialize the MPI environment
        MPI.Init(args);

        Polynomial firstPolynomial = Polynomial.getRandomPolynomial(POLYNOMIAL_ORDER);
        Polynomial secondPolynomial = Polynomial.getRandomPolynomial(POLYNOMIAL_ORDER);

        // MPI.COMM_WORLD.Recv(buffer, offset, count, datatype, source, tag);
        // MPI.COMM_WORLD.Send(buffer, offset, count, datatype, destination, tag);

        // returns the rank of the calling process within the MPI.COMM_WORLD communicator
        int rank = MPI.COMM_WORLD.Rank();

        // returns the total number of processes of the MPI.COMM_WORLD communicator
        int processesCount = MPI.COMM_WORLD.Size();

        if (rank == 0) {
            System.out.println("First polynomial : " + firstPolynomial);
            System.out.println("Second polynomial : " + secondPolynomial);

            mainProcess(firstPolynomial, secondPolynomial, processesCount);
        } else {
//            multiplySimpleWorker();
            multiplyKaratsubaWorker();
        }

        MPI.Finalize();
    }
}