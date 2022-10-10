package Model;

public class Motorcycle implements Automobile{
    int repairPrice, housePowerUnits;

    public Motorcycle(int repairPrice, int housePowerUnits) {
        this.repairPrice = repairPrice;
        this.housePowerUnits = housePowerUnits;
    }

    @Override
    public int getRepairPrice() {
        return this.repairPrice;
    }

    @Override
    public String toString() {
        return "Motorcycle{" +
                "repairPrice=" + repairPrice +
                ", housePowerUnits=" + housePowerUnits +
                '}';
    }
}
