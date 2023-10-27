public class KthTask implements Runnable {
    private final Integer[][] result;
    private final Matrix matrix1;
    private final Matrix matrix2;
    private final int k;
    private final int stepSize;

    public KthTask(Integer[][] result, Matrix matrix1, Matrix matrix2, int k, int stepSize) {
        this.result = result;
        this.matrix1 = matrix1;
        this.matrix2 = matrix2;
        this.k = k;
        this.stepSize = stepSize;
    }

    @Override
    public void run() {
        int rowsNumber = this.matrix1.getNumberOfRows();
        int columnsNumber = this.matrix2.getNumberOfColumns();

        int rowIndex = 0;
        int columnIndex = k;

        while (true) {
            int columnOvershoot = columnIndex / columnsNumber;
            rowIndex += columnOvershoot;
            columnIndex -= columnOvershoot * columnsNumber;

            if (rowIndex >= rowsNumber)
                break;

            this.result[rowIndex][columnIndex] = this.matrix1.getResultingElement(this.matrix2, rowIndex, columnIndex);
            columnIndex += this.stepSize;
        }
    }
}
