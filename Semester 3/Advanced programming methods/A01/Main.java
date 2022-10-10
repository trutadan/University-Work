// 3. Intr-un service se afla in reparatie mai multe
// masini, camioane si motociclete. Sa se afiseze
// toate autovehiculele ce au costul de reparatie
// mai mare de 1000Ron.

import Controller.Controller;
import Repository.InMemoryRepository;
import Repository.iRepository;
import View.View;

public class Main {
    public static void main(String[] args) {
        iRepository repository = new InMemoryRepository(3);
        Controller controller = new Controller(repository);
        View view = new View(controller);

        view.runProgram();
    }
}
