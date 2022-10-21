package View;

import Controller.Controller;
import Exceptions.RepositoryException;
import Model.Automobile;
import Model.Car;
import Model.Motorcycle;
import Model.Truck;

import java.util.Scanner;

public class View {
    Controller controller;

    public View(Controller controller) {
        this.controller = controller;
    }

    private void addCarOption() throws RepositoryException {
        System.out.println("Is it a two-doors car?");
        Scanner inputBooleanScanner = new Scanner(System.in);
        boolean twoDoors = inputBooleanScanner.nextBoolean();

        System.out.println("Enter the repair price: ");
        Scanner inputPriceScanner = new Scanner(System.in);
        int repairPrice = inputPriceScanner.nextInt();

        Automobile newAutomobile = new Car(repairPrice, twoDoors);

        this.controller.addAutomobile(newAutomobile);

        System.out.println("The car has been successfully added!");
    }

    private void addTruckOption() throws RepositoryException {
        System.out.println("Enter the weight of the truck: ");
        Scanner inputWeightScanner = new Scanner(System.in);
        int weight = inputWeightScanner.nextInt();

        System.out.println("Enter the repair price: ");
        Scanner inputPriceScanner = new Scanner(System.in);
        int repairPrice = inputPriceScanner.nextInt();

        Automobile newAutomobile = new Truck(repairPrice, weight);

        this.controller.addAutomobile(newAutomobile);

        System.out.println("The truck has been successfully added!");
    }

    private void addMotorcycleOption() throws RepositoryException {
        System.out.println("Enter the HP of the motorcycle: ");
        Scanner inputHorsePowerScanner = new Scanner(System.in);
        int horsePower = inputHorsePowerScanner.nextInt();

        System.out.println("Enter the repair price: ");
        Scanner inputPriceScanner = new Scanner(System.in);
        int repairPrice = inputPriceScanner.nextInt();

        Automobile newAutomobile = new Motorcycle(repairPrice, horsePower);

        this.controller.addAutomobile(newAutomobile);

        System.out.println("The motorcycle has been successfully added!");
    }

    private void removeAutomobileOption() throws RepositoryException {
        System.out.println("Enter the position of the automobile you want to remove: ");
        Scanner inputPositionScanner = new Scanner(System.in);
        int positionToRemove = inputPositionScanner.nextInt();

        this.controller.removeAutomobile(positionToRemove);

        System.out.println("The automobile has been successfully removed!");
    }

    private void displayAllAutomobilesOption() {
        if (this.controller.getAutomobilesSize() == 0)
            System.out.println("No automobiles left.");

        else {
            System.out.println("All automobiles: ");

            Automobile[] automobiles = this.controller.getAllAutomobilesFromRepository();

            for (int index = 0; index < this.controller.getAutomobilesSize(); index++)
                System.out.println(index + ". " + automobiles[index]);
        }
    }

    private void displayFilteredAutomobilesOption() {
        Automobile[] filteredAutomobiles = this.controller.getFilteredAutomobilesByRepairPrice(1000);

        if (filteredAutomobiles.length == 0)
            System.out.println("No automobile meets the filter requirements.");

        else {
            System.out.println("Filtered automobiles: ");

            for (int index = 0; index < filteredAutomobiles.length; index++)
                System.out.println(index + ". " + filteredAutomobiles[index]);
        }
    }

    public void runProgram() {
        System.out.println("Welcome to our program!");

        while (true) {
            this.printMenu();
            Scanner scanner = new Scanner(System.in);
            int option = scanner.nextInt();

            try {

                if (option == 1) {
                    this.addCarOption();

                } else if (option == 2) {
                    this.addTruckOption();

                } else if (option == 3) {
                    this.addMotorcycleOption();

                } else if (option == 4) {
                    this.removeAutomobileOption();

                } else if (option == 5) {
                    this.displayAllAutomobilesOption();

                } else if (option == 6) {
                    this.displayFilteredAutomobilesOption();

                } else if (option == 7) {
                    break;
                } else {
                    System.out.println("Unknown command.");
                }

            } catch (RepositoryException errorMessage) {
                System.out.println(errorMessage.getMessage());
            }
        }

        System.out.println("\nThank you for using the app! See you next time.");
    }

    public void printMenu() {
        System.out.println("\nChoose one of the following commands:");
        System.out.println("[1] Add a car.");
        System.out.println("[2] Add a truck.");
        System.out.println("[3] Add a motorcycle.");
        System.out.println("[4] Remove an automobile.");
        System.out.println("[5] Print all automobiles.");
        System.out.println("[6] Print filtered automobiles.");
        System.out.println("[7] Exit.");
    }
}