package View;

import Controller.Controller;
import Exceptions.MyException;
import Model.DataStructures.*;
import Model.Expressions.ArithmeticExpression;
import Model.Expressions.ValueExpression;
import Model.Expressions.VariableExpression;
import Model.ProgramState;
import Model.Statements.*;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.Value;

import java.util.Scanner;

// done for LAB02
public class View {
    Controller controller;

    public View(Controller _controller) {
        controller = _controller;
    }

    private void displayAllPrograms() {
        System.out.println("\n-------------------------------------------------------------");
        System.out.println("[1] int v; v=2; Print(v)");
        System.out.println("[2] int a; int b; a=2+3*5; b=a+1; Print(b)");
        System.out.println("[3] bool a; int v; a=true; (IF a THEN v=2 ELSE v=3); Print(v)");
        System.out.println("-------------------------------------------------------------\n");
    }

    private void displayMenu() {
        System.out.println("[0] Display all programs.");
        System.out.println("[1] Run first program.");
        System.out.println("[2] Run second program.");
        System.out.println("[3] Run third program.");
        System.out.println("[4] Exit.");
    }

    private void addFirstProgramState() {
        iStatement firstStatement = new CompoundStatement(new VariableDeclarationStatement("v",new IntType()),
                new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(2))),
                        new PrintStatement(new VariableExpression("v"))));

        MyiStack<iStatement> executionStack = new MyStack<>();
        MyiDictionary<String, Value> symbolTable = new MyDictionary<>();
        MyiList<Value> outputValues = new MyList<>();

        ProgramState state = new ProgramState(executionStack, symbolTable, outputValues, firstStatement);

        controller.addNewProgramState(state);
    }

    private void addSecondProgramState() {
        iStatement secondStatement = new CompoundStatement(new VariableDeclarationStatement("a",new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("b",new IntType()),
                        new CompoundStatement(new AssignStatement("a", new ArithmeticExpression('+',new ValueExpression(new IntValue(2)),new
                                ArithmeticExpression('*', new ValueExpression(new IntValue(3)), new ValueExpression(new IntValue(5))))),
                                new CompoundStatement(new AssignStatement("b",new ArithmeticExpression('+',new VariableExpression("a"), new ValueExpression(new
                                        IntValue(1)))), new PrintStatement(new VariableExpression("b"))))));

        MyiStack<iStatement> executionStack = new MyStack<>();
        MyiDictionary<String, Value> symbolTable = new MyDictionary<>();
        MyiList<Value> outputValues = new MyList<>();

        ProgramState state = new ProgramState(executionStack, symbolTable, outputValues, secondStatement);

        controller.addNewProgramState(state);

    }

    private void addThirdProgramState() {
        iStatement thirdStatement = new CompoundStatement(new VariableDeclarationStatement("a", new BoolType()),
                new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                        new CompoundStatement(new AssignStatement("a", new ValueExpression(new BoolValue(true))),
                                new CompoundStatement(new IfStatement(new VariableExpression("a"),
                                        new AssignStatement("v", new ValueExpression(new IntValue(2))),
                                        new AssignStatement("v", new ValueExpression(new IntValue(3)))),
                                        new PrintStatement(new VariableExpression("v"))))));

        MyiStack<iStatement> executionStack = new MyStack<>();
        MyiDictionary<String, Value> symbolTable = new MyDictionary<>();
        MyiList<Value> outputValues = new MyList<>();

        ProgramState state = new ProgramState(executionStack, symbolTable, outputValues, thirdStatement);

        controller.addNewProgramState(state);
    }


    private void setAndRunProgramState(int position) throws MyException {
        controller.setProgramStatePosition(position);
        controller.allStepExecution();
    }

    public void runInterpreter() {
        Scanner scanner = new Scanner(System.in);

        this.addFirstProgramState();
        this.addSecondProgramState();
        this.addThirdProgramState();

        try {

            while (true) {
                displayMenu();
                System.out.print("Choose an option: ");

                String command = scanner.next();
                char option = command.charAt(0);

                if (option == '0')
                    this.displayAllPrograms();

                else if (option == '1')
                    this.setAndRunProgramState(0);

                else if (option == '2')
                    this.setAndRunProgramState(1);

                else if (option == '3')
                    this.setAndRunProgramState(2);

                else if (option == '4')
                    break;

                else
                    System.out.println("Not a valid option!");
            }

        } catch (MyException exception) {
            System.out.println(exception.getMessage());
        }

        System.out.println("Thank you for using the interpreter! See you soon.");
    }
}
