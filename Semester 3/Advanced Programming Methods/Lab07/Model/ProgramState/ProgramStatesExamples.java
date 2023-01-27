package Model.ProgramState;

import Controller.Controller;
import Exceptions.MyException;
import Model.DataStructures.MyDictionary;
import Model.Expressions.*;
import Model.Statements.*;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Types.ReferenceType;
import Model.Types.StringType;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Repository.Repository;
import Repository.iRepository;
import View.RunExample;
import View.TextMenu;

import java.util.ArrayList;
import java.util.List;

// done for LAB07
public class ProgramStatesExamples {
    List<iStatement> programStatesList;

    public ProgramStatesExamples() {
        this.programStatesList = new ArrayList<>();
        this.addProgramStatesExamplesToList();
    }

    private void addProgramStatesExamplesToList() {
        iStatement firstStatement = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(2))),
                        new PrintStatement(new VariableExpression("v"))));
        this.programStatesList.add(firstStatement);

        iStatement secondStatement = new CompoundStatement(new VariableDeclarationStatement("a", new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("b", new IntType()),
                    new CompoundStatement(new AssignStatement("a", new ArithmeticExpression('+', new ValueExpression(new IntValue(2)),
                        new ArithmeticExpression('*', new ValueExpression(new IntValue(3)), new ValueExpression(new IntValue(5))))),
                            new CompoundStatement(new AssignStatement("b", new ArithmeticExpression('+', new VariableExpression("a"),
                                new ValueExpression(new IntValue(1)))), new PrintStatement(new VariableExpression("b"))))));
        this.programStatesList.add(secondStatement);

        iStatement thirdStatement = new CompoundStatement(new VariableDeclarationStatement("a", new BoolType()),
                new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                    new CompoundStatement(new AssignStatement("a", new ValueExpression(new BoolValue(true))),
                        new CompoundStatement(new IfStatement(new VariableExpression("a"),
                            new AssignStatement("v", new ValueExpression(new IntValue(2))),
                                new AssignStatement("v", new ValueExpression(new IntValue(3)))),
                                    new PrintStatement(new VariableExpression("v"))))));
        this.programStatesList.add(thirdStatement);

        iStatement fourthStatement = new CompoundStatement(new VariableDeclarationStatement("varf", new StringType()),
                new CompoundStatement(new AssignStatement("varf", new ValueExpression(new StringValue("test.in"))),
                    new CompoundStatement(new OpenReadFileStatement(new VariableExpression("varf")),
                        new CompoundStatement(new VariableDeclarationStatement("varc", new IntType()),
                            new CompoundStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"),
                                new CompoundStatement(new PrintStatement(new VariableExpression("varc")),
                                    new CompoundStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"),
                                        new CompoundStatement(new PrintStatement(new VariableExpression("varc")),
                                            new CloseReadFileStatement(new VariableExpression("varf"))))))))));
        this.programStatesList.add(fourthStatement);

        iStatement fifthStatement = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                    new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                        new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                            new CompoundStatement(new PrintStatement(new VariableExpression("v")),
                                (new PrintStatement(new VariableExpression("a"))))))));
        this.programStatesList.add(fifthStatement);

        iStatement sixthStatement = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                    new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                        new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                            new CompoundStatement(new PrintStatement(new HeapReadingExpression(new VariableExpression("v"))),
                                (new PrintStatement(new ArithmeticExpression('+',
                                    new HeapReadingExpression(new HeapReadingExpression(new VariableExpression("a"))),
                                        new ValueExpression(new IntValue(5))))))))));
        this.programStatesList.add(sixthStatement);

        iStatement seventhStatement = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                    new CompoundStatement(new PrintStatement(new HeapReadingExpression(new VariableExpression("v"))),
                        new CompoundStatement(new HeapWritingStatement("v", new ValueExpression(new IntValue(30))),
                            new PrintStatement(new ArithmeticExpression('+', new HeapReadingExpression(new VariableExpression("v")),
                                new ValueExpression(new IntValue(5))))))));
        this.programStatesList.add(seventhStatement);

        iStatement eighthStatement = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                    new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                        new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                            new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(30))),
                                (new PrintStatement(new HeapReadingExpression(new HeapReadingExpression(new VariableExpression("a"))))))))));
        this.programStatesList.add(eighthStatement);

        iStatement ninthStatement = new CompoundStatement(new VariableDeclarationStatement("v",new IntType()),
                new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(4))),
                    new WhileStatement(new RelationalExpression(">", new VariableExpression("v"),
                        new ValueExpression(new IntValue(0))), new CompoundStatement(new PrintStatement(new VariableExpression("v")),
                            new AssignStatement( "v", new ArithmeticExpression('-', new VariableExpression("v"),
                                new ValueExpression(new IntValue(1))))))));
        this.programStatesList.add(ninthStatement);

        iStatement tenthStatement = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new IntType())),
                    new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(10))),
                        new CompoundStatement(new HeapAllocationStatement("a", new ValueExpression(new IntValue(22))),
                            new CompoundStatement(new CreateThreadStatement(new CompoundStatement(new HeapWritingStatement("a",
                                new ValueExpression(new IntValue(30))), new CompoundStatement(
                                    new AssignStatement("v", new ValueExpression(new IntValue(32))),
                                        new CompoundStatement(new PrintStatement(new VariableExpression("v")),
                                            new PrintStatement(new HeapReadingExpression(new VariableExpression("a"))))))),
                                                new CompoundStatement(new PrintStatement(new VariableExpression("v")),
                                                    new PrintStatement(new HeapReadingExpression(new VariableExpression("a")))))))));
        this.programStatesList.add(tenthStatement);

        // int v; v=5; if (v==5), then (int a; a=7;), else (print(v)); print(a)
        iStatement firstFaultyStatement = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(5))),
                    new CompoundStatement(new IfStatement(new RelationalExpression("==", new VariableExpression("v"),
                        new ValueExpression(new IntValue(5))), new CompoundStatement(
                            new VariableDeclarationStatement("a", new IntType()), new AssignStatement("a", new ValueExpression(new IntValue(7)))),
                                new PrintStatement(new VariableExpression("v"))), new PrintStatement(new VariableExpression("a")))));
        this.programStatesList.add(firstFaultyStatement);

        // int v; v=6; while (v > 1) {int a; a=v; print(a); v=v-1; }; print(a);
        iStatement secondFaultyStatement = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(6))),
                    new CompoundStatement(new WhileStatement(new RelationalExpression(">", new VariableExpression("v"), new ValueExpression(new IntValue(1))),
                        new CompoundStatement(new VariableDeclarationStatement("a", new IntType()),
                            new CompoundStatement(new AssignStatement("a", new VariableExpression("v")),
                                new CompoundStatement(new PrintStatement(new VariableExpression("a")),
                                    new AssignStatement( "v", new ArithmeticExpression('-',
                                        new VariableExpression("v"), new ValueExpression(new IntValue(1)))))))),
                                            new PrintStatement(new VariableExpression("a")))));
        this.programStatesList.add(secondFaultyStatement);

        // int v; v=7; createThread(int a; a=v;); print(a);
        iStatement thirdFaultyStatement = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(7))),
                    new CompoundStatement(new CreateThreadStatement(new CompoundStatement(
                        new VariableDeclarationStatement("a", new IntType()), new AssignStatement("a",
                            new VariableExpression("v")))), new PrintStatement(new VariableExpression("a")))));
        this.programStatesList.add(thirdFaultyStatement);
    }

    public List<iStatement> getProgramStatesList() {
        return this.programStatesList;
    }

    public void addAllExamplesToMenu(TextMenu menu) {
        for (int index = 0; index < this.programStatesList.size(); index++) {
            iStatement eachStatement = this.programStatesList.get(index);

            try {
                eachStatement.typeCheck(new MyDictionary<>());

                ProgramState state = new ProgramState(eachStatement);
                iRepository repository = new Repository(state, "log" + (index + 1) + ".txt");
                Controller controller = new Controller(repository, true);

                menu.addCommand(new RunExample(String.valueOf(index + 1), eachStatement.toString(), controller));
            } catch (MyException error) {
                System.out.println(eachStatement + " has not been created -> " + error.getMessage());
            }
        }
    }
}
