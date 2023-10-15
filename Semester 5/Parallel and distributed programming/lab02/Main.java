import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Main {
    public static void populateVectors(List<Integer> vector, int size, int min, int max) {
        Random random = new Random();
        for (int index = 0; index < size; index++) {
            int randomValue = random.nextInt((max - min) + 1) + min;
            vector.add(randomValue);
        }
    }

    public static int computeScalarProduct(List<Integer> firstVector, List<Integer> secondVector) {
        int result = 0;
        for (int index = 0; index < firstVector.size(); index++)
            result += firstVector.get(index) * secondVector.get(index);

        return result;
    }

    public static void main(String[] args) {
        int vectorSize = 100;
        int minimumValue = 0;
        int maximumValue = 10;

        List<Integer> firstVector = new ArrayList<>();
        List<Integer> secondVector = new ArrayList<>();

        populateVectors(firstVector, vectorSize, minimumValue, maximumValue);
        populateVectors(secondVector, vectorSize, minimumValue, maximumValue);

        System.out.println("The expected scalar product of the vectors is: " + computeScalarProduct(firstVector, secondVector));

        Handler handler = new Handler();
        Producer producer = new Producer(handler, firstVector, secondVector);
        Consumer consumer = new Consumer(handler, vectorSize);

        producer.start();
        consumer.start();
    }
}