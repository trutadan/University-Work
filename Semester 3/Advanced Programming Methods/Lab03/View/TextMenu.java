package View;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

// done for LAB03
public class TextMenu {
    Map<String, Command> commands;

    public TextMenu() {
        commands = new HashMap<>();
    }

    public void addCommand(Command newCommand) {
        commands.put(newCommand.getKey(), newCommand);
    }

    private void printMenu() {
        for(Command eachCommand : commands.values()) {
            String line = String.format("[%s] %s", eachCommand.getKey(), eachCommand.getDescription());
            System.out.println(line);
        }
    }

    public void show(){
        Scanner scanner = new Scanner(System.in);
        while (true) {
            printMenu();
            System.out.print("Input the option: ");

            String key = scanner.nextLine();
            Command command = commands.get(key);

            if (command == null) {
                System.out.println("Invalid option!");
                continue;
            }

            command.execute();
        }
    }
}