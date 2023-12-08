public class Task implements Runnable {
    private final int start;
    private final int end;
    private final Polynomial first;
    private final Polynomial second;
    private final Polynomial result;

    public Task(int start, int end, Polynomial first, Polynomial second, Polynomial result) {
        this.start = start;
        this.end = end;
        this.first = first;
        this.second = second;
        this.result = result;
    }

    @Override
    public void run() {
        for (int i = this.start; i < this.end; i++) {
            if (i > this.result.coefficients.size()) {
                return;
            }

            for (int j = 0; j <= i; j++) {
                if (j < this.first.coefficients.size() && (i - j) < this.second.coefficients.size()) {
                    // i - j in order to get all positions (0, 1, 2 etc.)
                    int value = this.first.coefficients.get(j) * this.second.coefficients.get(i - j);
                    this.result.coefficients.set(i, this.result.coefficients.get(i) + value);
                }
            }
        }
    }
}
