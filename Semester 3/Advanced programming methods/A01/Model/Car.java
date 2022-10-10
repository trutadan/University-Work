package Model;

public class Car implements Automobile{
    int repairPrice;
    boolean twoDoors;

    public Car(int repairPrice, boolean twoDoors) {
        this.repairPrice = repairPrice;
        this.twoDoors = twoDoors;
    }

    @Override
    public int getRepairPrice() {
        return this.repairPrice;
    }

    @Override
    public String toString() {
        return "Car{" +
                "repairPrice=" + repairPrice +
                ", twoDoors=" + twoDoors +
                '}';
    }
}
