import Model.ProgramState.ProgramStatesExamples;
import View.ExitCommand;
import View.TextMenu;

// done for LAB06
public class Interpreter {
    public static void main(String[] args) {
        TextMenu menu = new TextMenu();

        menu.addCommand(new ExitCommand("0", "Exit."));

        ProgramStatesExamples menuCreator = new ProgramStatesExamples();
        menuCreator.addAllExamplesToMenu(menu);

        menu.show();
    }
}