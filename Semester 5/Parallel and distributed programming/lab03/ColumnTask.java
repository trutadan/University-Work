public class ColumnTask implements Runnable {
    private final Integer[][] result;
    private final Matrix matrix1;
    private final Matrix matrix2;
    private final int left;
    private final int right;

    public ColumnTask(Integer[][] result, Matrix matrix1, Matrix matrix2, int left, int right) {
        this.result = result;
        this.matrix1 = matrix1;
        this.matrix2 = matrix2;
        this.left = left;
        this.right = right;
    }

    @Override
    public void run() {
        int numberOfRows = this.matrix1.getNumberOfRows();

        int rowIndex = this.left % numberOfRows;
        int columnIndex = this.left / numberOfRows;

        int numberOfElementsToCompute = this.right - this.left;
        for (int index = 0; index < numberOfElementsToCompute; index++) {
            this.result[rowIndex][columnIndex] = this.matrix1.getResultingElement(this.matrix2, rowIndex, columnIndex);

            rowIndex++;
            if (rowIndex == numberOfRows) {
                rowIndex = 0;
                columnIndex ++;
            }
        }
    }
}
