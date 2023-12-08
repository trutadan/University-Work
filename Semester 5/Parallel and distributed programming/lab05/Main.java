import java.util.concurrent.ExecutionException;

public class Main {
    public static void main(String[] args) throws InterruptedException, ExecutionException {
        Polynomial first = new Polynomial(3);
        first.populateRandomly(10);

        Polynomial second = new Polynomial(3);
        second.populateRandomly(10);

        System.out.println("First polynomial: " + first);
        System.out.println("Second polynomial: " + second);
        System.out.println();

        System.out.println(classicSequential(first, second) + "\n");
        System.out.println(classicParallelized(first, second) + "\n");
        System.out.println(karatsubaSequential(first, second).toString() + "\n");
        System.out.println(karatsubaParallelized(first, second).toString() + "\n");
    }

    private static Polynomial classicSequential(Polynomial p, Polynomial q) {
        long startTime = System.currentTimeMillis();
        Polynomial result1 = Algorithms.ClassicSequential(p, q);
        long endTime = System.currentTimeMillis();
        System.out.println("Classic Sequential:");
        System.out.println("Time: " + (endTime - startTime) + " ms");
        return result1;
    }

    private static Polynomial classicParallelized(Polynomial p, Polynomial q) throws InterruptedException {
        long startTime = System.currentTimeMillis();
        Polynomial result2 = Algorithms.ClassicParallelized(p, q);
        long endTime = System.currentTimeMillis();
        System.out.println("Classic Parallelized:");
        System.out.println("Time: " + (endTime - startTime) + " ms");
        return result2;
    }

    private static Polynomial karatsubaSequential(Polynomial p, Polynomial q) {
        long startTime = System.currentTimeMillis();
        Polynomial result3 = Algorithms.KaratsubaSequential(p, q);
        long endTime = System.currentTimeMillis();
        System.out.println("Karatsuba Sequential:");
        System.out.println("Time: " + (endTime - startTime) + " ms");
        return result3;
    }

    private static Polynomial karatsubaParallelized(Polynomial p, Polynomial q) throws ExecutionException, InterruptedException {
        long startTime = System.currentTimeMillis();
        Polynomial result4 = Algorithms.KaratsubaParallelized(p, q, 1);
        long endTime = System.currentTimeMillis();
        System.out.println("Karatsuba Parallelized:");
        System.out.println("Time: " + (endTime - startTime) + " ms");
        return result4;
    }
}
