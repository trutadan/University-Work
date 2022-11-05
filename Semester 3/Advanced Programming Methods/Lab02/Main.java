import Controller.Controller;
import Repository.iRepository;
import Repository.Repository;
import View.View;

// done for LAB02
public class Main {
    public static void main(String[] args) {
        // repository/controller/view implementation will be changed for LAB03...
        iRepository repository = new Repository();
        Controller controller = new Controller(repository, true);
        View view = new View(controller);

        view.runInterpreter();
    }
}