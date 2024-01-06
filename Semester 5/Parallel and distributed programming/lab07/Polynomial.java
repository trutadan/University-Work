import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.Random;

public final class Polynomial implements Serializable {
    private final List<Integer> coefficients;

    public Polynomial(List<Integer> coefficients) {
        this.coefficients = coefficients;
    }

    public List<Integer> getCoefficients() {
        return coefficients;
    }

    public int getDegree() {
        return this.coefficients.size() - 1;
    }

    public static Polynomial getRandomPolynomial(int degree) {
        int MAXIMUM_COEFFICIENT_VALUE = 10;

        Random random = new Random();
        List<Integer> coefficients = new ArrayList<>();

        // generate random coefficients for each term
        for (int index = 0; index < degree; index++) {
            coefficients.add(random.nextInt(MAXIMUM_COEFFICIENT_VALUE));
        }

        // ensure the highest-degree coefficient is not zero
        coefficients.add(random.nextInt(MAXIMUM_COEFFICIENT_VALUE - 1) + 1);

        return new Polynomial(coefficients);
    }

    public static Polynomial extendDegree(Polynomial polynomial, int differenceDegree) {
        List<Integer> coefficients = new ArrayList<>();
        // add zero coefficients for the specified difference in degree
        for (int index = 0; index < differenceDegree; index++) {
            coefficients.add(0);
        }

        // add existing coefficients to the new polynomial
        coefficients.addAll(polynomial.getCoefficients());

        return new Polynomial(coefficients);
    }

    public static Polynomial addTwoPolynomials(Polynomial first, Polynomial second) {
        List<Integer> coefficients = new ArrayList<>();

        int minDegree = Math.min(first.getDegree(), second.getDegree());
        int maxDegree = Math.max(first.getDegree(), second.getDegree());

        List<Integer> firstPolynomialCoefficients = first.getCoefficients();
        List<Integer> secondPolynomialCoefficients = second.getCoefficients();

        // add coefficients up to the minimum degree
        for (int index = 0; index <= minDegree; index++) {
            coefficients.add(firstPolynomialCoefficients.get(index) + secondPolynomialCoefficients.get(index));
        }

        // add the remaining coefficients from the polynomial with a higher degree
        if (minDegree != maxDegree) {
            if (maxDegree == first.getDegree()) {
                for (int i = minDegree + 1; i <= maxDegree; i++) {
                    coefficients.add(firstPolynomialCoefficients.get(i));
                }
            } else {
                for (int i = minDegree + 1; i <= maxDegree; i++) {
                    coefficients.add(secondPolynomialCoefficients.get(i));
                }
            }
        }

        return new Polynomial(coefficients);
    }

    public static Polynomial subtractTwoPolynomials(Polynomial first, Polynomial second) {
        // a - b = a + (-b)
        Polynomial negativeSecond = Polynomial.getNegativePolynomial(second);
        return Polynomial.addTwoPolynomials(first, negativeSecond);
    }

    public static Polynomial getNegativePolynomial(Polynomial polynomial) {
        List<Integer> coefficients = new ArrayList<>();

        // negate each coefficient in the polynomial
        for (int index = 0; index <= polynomial.getDegree(); index++) {
            coefficients.add(-polynomial.getCoefficients().get(index));
        }

        return new Polynomial(coefficients);
    }

    public static Polynomial getRegularSequentialProductInGivenRange(Polynomial first, Polynomial second, int startDegree, int finishDegree) {
        List<Integer> coefficients = new ArrayList<>();
        int productDegree = first.getDegree() + second.getDegree();

        // initialize resulting coefficients list with zeros
        for (int index = 0; index <= productDegree; index++) {
            coefficients.add(0);
        }

        List<Integer> firstPolynomialCoefficients = first.getCoefficients();
        List<Integer> secondPolynomialCoefficients = second.getCoefficients();

        // compute the product within the specified degree range
        for (int i = startDegree; i < finishDegree; i++) {
            for (int j = 0; j <= second.getDegree(); j++) {
                int newValue = coefficients.get(i + j) + firstPolynomialCoefficients.get(i) * secondPolynomialCoefficients.get(j);
                coefficients.set(i + j, newValue);
            }
        }

        return new Polynomial(coefficients);
    }

    public static Polynomial getRegularSequentialProduct(Polynomial first, Polynomial second) {
        int resultDegree = first.getDegree() + second.getDegree();
        List<Integer> coefficients = new ArrayList<>();

        // initialize coefficients list with zeros
        for (int index = 0; index <= resultDegree; index++) {
            coefficients.add(0);
        }

        // compute the product for each term in both polynomials
        for (int i = 0; i <= first.getDegree(); i++) {
            for (int j = 0; j <= second.getDegree(); j++) {
                int current_coefficient_degree = i + j;
                int value = coefficients.get(current_coefficient_degree) + first.getCoefficients().get(i) * second.getCoefficients().get(j);
                coefficients.set(current_coefficient_degree, value);
            }
        }

        return new Polynomial(coefficients);
    }

    public static Polynomial getKaratsubaSequentialProduct(Polynomial first, Polynomial second) {
        // if either polynomial has a degree less than 2, use regular sequential product
        if (first.getDegree() < 2 || second.getDegree() < 2)
            return getRegularSequentialProduct(first, second);
        // checking if first is full of 0 valued coefficients does not help with efficiency

        // determine the length for splitting polynomials
        int splitLength = Math.max(first.getDegree(), second.getDegree()) / 2;

        List<Integer> firstPolynomialCoefficients = first.getCoefficients();
        List<Integer> secondPolynomialCoefficients = second.getCoefficients();

        // split polynomials into low and high parts
        Polynomial firstLow = new Polynomial(firstPolynomialCoefficients.subList(0, splitLength));
        Polynomial firstHigh = new Polynomial(firstPolynomialCoefficients.subList(splitLength, first.getDegree() + 1));
        Polynomial secondLow = new Polynomial(secondPolynomialCoefficients.subList(0, splitLength));
        Polynomial secondHigh = new Polynomial(secondPolynomialCoefficients.subList(splitLength, second.getDegree() + 1));

        // recursive calls for computing parts of the Karatsuba algorithm
        Polynomial multipliedHighParts = getKaratsubaSequentialProduct(firstHigh, secondHigh);
        Polynomial multipliedLowParts = getKaratsubaSequentialProduct(firstLow, secondLow);
        Polynomial multipliedCombined = getKaratsubaSequentialProduct(Polynomial.addTwoPolynomials(firstLow, firstHigh),
                Polynomial.addTwoPolynomials(secondLow, secondHigh));

        // compute final result using the Karatsuba formula
        Polynomial subtract = Polynomial.subtractTwoPolynomials(
                Polynomial.subtractTwoPolynomials(multipliedCombined, multipliedLowParts), multipliedHighParts);
        Polynomial extendedHighParts = Polynomial.extendDegree(multipliedHighParts, 2 * splitLength);
        Polynomial extendedSubtract = Polynomial.extendDegree(subtract, splitLength);

        return Polynomial.addTwoPolynomials(
                Polynomial.addTwoPolynomials(extendedHighParts, multipliedLowParts), extendedSubtract);
    }

    public static boolean equals(Polynomial first, Polynomial second) {
        // get coefficients of both polynomials
        List<Integer> coefficientsFirst = first.getCoefficients();
        List<Integer> coefficientsSecond = second.getCoefficients();

        // check if the degrees are the same
        if (first.getDegree() != second.getDegree()) {
            return false;
        }

        // check each coefficient for equality
        for (int i = 0; i <= first.getDegree(); i++) {
            if (!Objects.equals(coefficientsFirst.get(i), coefficientsSecond.get(i))) {
                return false;
            }
        }

        // if all coefficients are equal, the polynomials are equal
        return true;
    }

    @Override
    public String toString() {
        StringBuilder toReturn = new StringBuilder();

        for (int index = coefficients.size() - 1; index > 0; index--) {
            toReturn.append(coefficients.get(index)).append("X^").append(index).append(" + ");
        }
        toReturn.append(coefficients.getFirst());

        return toReturn.toString();
    }
}