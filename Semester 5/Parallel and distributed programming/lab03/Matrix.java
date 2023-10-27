import java.util.Random;

public class Matrix {
    private Integer[][] matrix;
    private final Integer rowCounter, columnCounter;

    public Matrix(Integer[][] matrix) {
        this.matrix = matrix;
        this.rowCounter = matrix.length;
        this.columnCounter = this.rowCounter > 0 ? matrix[0].length : 0;
    }

    public Matrix(int rowCounter, int columnCounter) {
        this.rowCounter = rowCounter;
        this.columnCounter = columnCounter;
        this.matrix = new Integer[rowCounter][columnCounter];
    }

    public Integer getNumberOfRows() {
        return this.rowCounter;
    }

    public Integer getNumberOfColumns() {
        return this.columnCounter;
    }

    public void populateMatrix(int min, int max) {
        Random random = new Random();

        for(int row = 0; row < this.rowCounter; row++)
           for(int column = 0; column < this.columnCounter; column++)
               this.matrix[row][column] = random.nextInt((max - min) + 1) + min;
    }

    public Integer getElement(int row, int column) throws IndexOutOfBoundsException {
        if (row < 0 || row >= this.rowCounter)
            throw new IndexOutOfBoundsException("Invalid row value!");

        if (column < 0 || column >= this.columnCounter)
            throw new IndexOutOfBoundsException("Invalid column value!");

        return this.matrix[row][column];
    }

    public void setElement(int row, int column, int element) throws IndexOutOfBoundsException {
        if (row < 0 || row >= this.rowCounter)
            throw new IndexOutOfBoundsException("Invalid row value!");

        if (column < 0 || column >= this.columnCounter)
            throw new IndexOutOfBoundsException("Invalid column value!");

        this.matrix[row][column] = element;
    }

    public Integer getResultingElement(Matrix anotherMatrix, int row, int column) throws IndexOutOfBoundsException, IllegalArgumentException {
        if (row < 0 || row >= this.rowCounter)
            throw new IndexOutOfBoundsException("Invalid row value!");

        if (!this.columnCounter.equals(anotherMatrix.rowCounter))
            throw new IllegalArgumentException("Matrix dimensions are not suitable for multiplication.");

        if (column < 0 || column >= anotherMatrix.columnCounter)
            throw new IndexOutOfBoundsException("Invalid column value!");

        int sum = 0;
        for(int index = 0; index < this.columnCounter; index++)
            sum += this.getElement(row, index) * anotherMatrix.getElement(index, column);

        return sum;
    }

    public Matrix multiply(Matrix anotherMatrix) throws IllegalArgumentException {
        if (!this.columnCounter.equals(anotherMatrix.rowCounter))
            throw new IllegalArgumentException("Matrix dimensions are not suitable for multiplication.");

        Matrix resultMatrix = new Matrix(this.rowCounter, anotherMatrix.columnCounter);

        for (int row = 0; row < this.rowCounter; row++) {
            for (int column = 0; column < anotherMatrix.columnCounter; column++) {
                resultMatrix.setElement(row, column, getResultingElement(anotherMatrix, row, column));
            }
        }

        return resultMatrix;
    }

    public boolean equals(Matrix anotherMatrix) {
        if (!this.rowCounter.equals(anotherMatrix.getNumberOfRows()) || !this.columnCounter.equals(anotherMatrix.getNumberOfColumns())) {
            return false;
        }

        for (int row = 0; row < this.rowCounter; row++) {
            for (int column = 0; column < this.columnCounter; column++) {
                if (!this.matrix[row][column].equals(anotherMatrix.getElement(row, column))) {
                    return false;
                }
            }
        }
        return true;
    }

    @Override
    public String toString() {
        StringBuilder matrixString = new StringBuilder();
        for(int row = 0; row < this.rowCounter; row++) {
            for(int column = 0; column < this.columnCounter; column++)
                matrixString.append(this.matrix[row][column]).append(" ");
            matrixString.append("\n");
        }

        return matrixString.toString();
    }
}
