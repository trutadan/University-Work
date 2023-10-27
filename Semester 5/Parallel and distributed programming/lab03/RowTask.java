public class RowTask implements Runnable {
    private final Integer[][] result;
    private final Matrix matrix1;
    private final Matrix matrix2;
    private final int left;
    private final int right;

    public RowTask(Integer[][] result, Matrix matrix1, Matrix matrix2, int left, int right) {
        this.result = result;
        this.matrix1 = matrix1;
        this.matrix2 = matrix2;
        this.left = left;
        this.right = right;
    }

    @Override
    public void run() {
        int numberOfColumns = this.matrix2.getNumberOfColumns();

        int rowIndex = this.left / numberOfColumns;
        int columnIndex = this.left % numberOfColumns;

        int limit = this.right - this.left;
        for (int index = 0; index < limit; index++) {
            this.result[rowIndex][columnIndex] = this.matrix1.getResultingElement(this.matrix2, rowIndex , columnIndex);

            columnIndex ++;
            if (columnIndex == numberOfColumns) {
                columnIndex = 0;
                rowIndex ++;
            }
        }
    }
}
