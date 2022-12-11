package View;

import Controller.Controller;
import Exceptions.MyException;

// done for LAB03
public class RunExample extends Command {
    Controller controller;

    public RunExample(String _key, String _description, Controller _controller) {
        super(_key, _description);
        this.controller = _controller;
    }

    @Override
    public void execute() {
        try {
            this.controller.allStepExecution();
        } catch (MyException exception) {
            //here you must treat the exceptions that can not be solved in the controller
            System.out.println(exception.getMessage());
        }
    }
}