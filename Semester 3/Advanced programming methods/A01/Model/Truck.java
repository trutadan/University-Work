package Model;

public class Truck implements Automobile{
    int repairPrice, weight;

    public Truck(int repairPrice, int weight) {
        this.repairPrice = repairPrice;
        this.weight = weight;
    }

    @Override
    public int getRepairPrice() {
        return this.repairPrice;
    }

    @Override
    public String toString() {
        return "Truck{" +
                "repairPrice=" + repairPrice +
                ", weight=" + weight +
                '}';
    }
}
