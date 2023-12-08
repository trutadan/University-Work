import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class Polynomial {
    public final List<Integer> coefficients;
    public final int degree;

    public Polynomial(int degree) {
        this.degree = degree;
        this.coefficients = new ArrayList<>(degree + 1);
        for (int index = 0; index <= this.degree; index++) {
            this.coefficients.add(0);
        }
    }

    public Polynomial(List<Integer> coefficients) {
        this.coefficients = coefficients;
        this.degree = coefficients.size() - 1;
    }

    /**
     * Populates the coefficients of the polynomial with random values
     * between 0 and maximumBound for all terms except the constant term,
     * which is populated between 1 and maximumBound+1.
     *
     * @param maximumBound The upper bound for random coefficients.
     */
    public void populateRandomly(int maximumBound) {
        Random random = new Random();
        for (int index = 0; index < this.degree; index++) {
            this.coefficients.set(index, random.nextInt(maximumBound));
        }
        this.coefficients.set(this.degree, random.nextInt(10) + 1);
    }

    /**
     * Adds two polynomials and returns the result as a new polynomial.
     *
     * @param first  The first polynomial.
     * @param second The second polynomial.
     * @return A new polynomial representing the sum of the input polynomials.
     */
    public static Polynomial add(Polynomial first, Polynomial second) {
        int maximDegree = Math.max(first.degree, second.degree);
        List<Integer> coefficients = new ArrayList<>(maximDegree + 1);

        // Add coefficients of corresponding terms
        for (int index = 0; index <= maximDegree; index++) {
            int firstCoefficient = (index <= first.degree) ? first.coefficients.get(index) : 0;
            int secondCoefficient = (index <= second.degree) ? second.coefficients.get(index) : 0;
            coefficients.add(firstCoefficient + secondCoefficient);
        }

        return new Polynomial(coefficients);
    }

    /**
     * Subtracts the second polynomial from the first and returns the result
     * as a new polynomial.
     *
     * @param first  The first polynomial.
     * @param second The second polynomial.
     * @return A new polynomial representing the subtraction of the second
     * polynomial from the first.
     */
    public static Polynomial subtract(Polynomial first, Polynomial second) {
        int maximDegree = Math.max(first.degree, second.degree);
        List<Integer> coefficients = new ArrayList<>(maximDegree + 1);

        // Subtract coefficients of corresponding terms
        for (int index = 0; index <= maximDegree; index++) {
            int firstCoefficient = (index <= first.degree) ? first.coefficients.get(index) : 0;
            int secondCoefficient = (index <= second.degree) ? second.coefficients.get(index) : 0;
            coefficients.add(firstCoefficient - secondCoefficient);
        }

        // Remove trailing zeros
        int index = coefficients.size() - 1;
        while (coefficients.get(index) == 0 && index > 0) {
            coefficients.remove(index);
            index--;
        }

        return new Polynomial(coefficients);
    }

    /**
     * Adds a specified number of zero coefficients to the beginning of the
     * polynomial.
     *
     * @param polynomial The polynomial to which zero coefficients are added.
     * @param offset     The number of zero coefficients to add.
     * @return A new polynomial with the added zero coefficients.
     */
    public static Polynomial addZeroes(Polynomial polynomial, int offset) {
        List<Integer> coefficients = new ArrayList<>(polynomial.coefficients);
        coefficients.addAll(0, Collections.nCopies(offset, 0));
        return new Polynomial(coefficients);
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();

        for (int index = this.degree; index >= 0; --index) {
            int coefficient = this.coefficients.get(index);

            if (coefficient != 0) {
                if (!builder.isEmpty()) {
                    builder.append(coefficient > 0 ? " + " : " - ");
                }

                // Omit the coefficient if it's 1 or -1 and not the constant term
                if (Math.abs(coefficient) != 1 || index == 0) {
                    builder.append(Math.abs(coefficient));
                }

                // Omit x if it's the constant term
                if (index > 0) {
                    builder.append("x");

                    // Omit ^1 for x
                    if (index > 1) {
                        builder.append("^").append(index);
                    }
                }
            }
        }

        return builder.toString();
    }
}
