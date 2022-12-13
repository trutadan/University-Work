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

// done for LAB06
public class ProgramStatesExamples {
    public void addAllExamplesToMenu(TextMenu menu) {
        try {
            this.addFirstExampleToMenu(menu);
        } catch (MyException error) {
            System.out.println("FirstProgram -> " + error.getMessage());
        }

        try {
            this.addSecondExampleToMenu(menu);
        } catch (MyException error) {
            System.out.println("SecondProgram -> " + error.getMessage());
        }

        try {
            this.addThirdExampleToMenu(menu);
        } catch (MyException error) {
            System.out.println("ThirdProgram -> " + error.getMessage());
        }

        try {
            this.addFourthExampleToMenu(menu);
        } catch (MyException error) {
            System.out.println("FourthProgram -> " + error.getMessage());
        }

        try {
            this.addFifthExampleToMenu(menu);
        } catch (MyException error) {
            System.out.println("FifthProgram -> " + error.getMessage());
        }

        try {
            this.addSixthExampleToMenu(menu);
        } catch (MyException error) {
            System.out.println("SixthProgram -> " + error.getMessage());
        }

        try {
            this.addSeventhExampleToMenu(menu);
        } catch (MyException error) {
            System.out.println("SeventhProgram -> " + error.getMessage());
        }

        try {
            this.addEighthExampleToMenu(menu);
        } catch (MyException error) {
            System.out.println("EighthProgram -> " + error.getMessage());
        }

        try {
            this.addNinthExampleToMenu(menu);
        } catch (MyException error) {
            System.out.println("NinthProgram -> " + error.getMessage());
        }

        try {
            this.addTenthExampleToMenu(menu);
        } catch (MyException error) {
            System.out.println("TenthProgram -> " + error.getMessage());
        }

        try {
            this.addFirstFaultyTypeCheckerExample(menu);
        } catch (MyException error) {
            System.out.println(error.getMessage());
        }

        try {
            this.addSecondFaultyTypeCheckerExample(menu);
        } catch (MyException error) {
            System.out.println(error.getMessage());
        }

        try {
            this.addThirdFaultyTypeCheckerExample(menu);
        } catch (MyException error) {
            System.out.println(error.getMessage());
        }
    }

    private void addFirstExampleToMenu(TextMenu menu) throws MyException {
        iStatement firstStatement = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(2))),
                    new PrintStatement(new VariableExpression("v"))));

        firstStatement.typeCheck(new MyDictionary<>());

        ProgramState firstState = new ProgramState(firstStatement);
        iRepository firstRepository = new Repository(firstState, "log1.txt");
        Controller firstController = new Controller(firstRepository, true);

        menu.addCommand(new RunExample("1", firstStatement.toString(), firstController));
    }

    private void addSecondExampleToMenu(TextMenu menu) throws MyException {
        iStatement secondStatement = new CompoundStatement(new VariableDeclarationStatement("a", new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("b", new IntType()),
                    new CompoundStatement(new AssignStatement("a", new ArithmeticExpression('+', new ValueExpression(new IntValue(2)),
                        new ArithmeticExpression('*', new ValueExpression(new IntValue(3)), new ValueExpression(new IntValue(5))))),
                            new CompoundStatement(new AssignStatement("b", new ArithmeticExpression('+', new VariableExpression("a"),
                                new ValueExpression(new IntValue(1)))), new PrintStatement(new VariableExpression("b"))))));

        secondStatement.typeCheck(new MyDictionary<>());

        ProgramState secondState = new ProgramState(secondStatement);
        iRepository secondRepository = new Repository(secondState, "log2.txt");
        Controller secondController = new Controller(secondRepository, true);

        menu.addCommand(new RunExample("2", secondStatement.toString(), secondController));
    }

    private void addThirdExampleToMenu(TextMenu menu) throws MyException {
        iStatement thirdStatement = new CompoundStatement(new VariableDeclarationStatement("a", new BoolType()),
                new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                    new CompoundStatement(new AssignStatement("a", new ValueExpression(new BoolValue(true))),
                        new CompoundStatement(new IfStatement(new VariableExpression("a"),
                            new AssignStatement("v", new ValueExpression(new IntValue(2))),
                                new AssignStatement("v", new ValueExpression(new IntValue(3)))),
                                    new PrintStatement(new VariableExpression("v"))))));

        thirdStatement.typeCheck(new MyDictionary<>());

        ProgramState thirdState = new ProgramState(thirdStatement);
        iRepository thirdRepository = new Repository(thirdState, "log3.txt");
        Controller thirdController = new Controller(thirdRepository, true);

        menu.addCommand(new RunExample("3", thirdStatement.toString(), thirdController));
    }

    private void addFourthExampleToMenu(TextMenu menu) throws MyException {
        iStatement fourthStatement = new CompoundStatement(new VariableDeclarationStatement("varf", new StringType()),
                new CompoundStatement(new AssignStatement("varf", new ValueExpression(new StringValue("test.in"))),
                    new CompoundStatement(new OpenReadFileStatement(new VariableExpression("varf")),
                        new CompoundStatement(new VariableDeclarationStatement("varc", new IntType()),
                            new CompoundStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"),
                                new CompoundStatement(new PrintStatement(new VariableExpression("varc")),
                                    new CompoundStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"),
                                        new CompoundStatement(new PrintStatement(new VariableExpression("varc")),
                                            new CloseReadFileStatement(new VariableExpression("varf"))))))))));

        fourthStatement.typeCheck(new MyDictionary<>());

        ProgramState fourthState = new ProgramState(fourthStatement);
        iRepository fourthRepository = new Repository(fourthState, "log4.txt");
        Controller fourthController = new Controller(fourthRepository, true);

        menu.addCommand(new RunExample("4", fourthStatement.toString(), fourthController));
    }

    private void addFifthExampleToMenu(TextMenu menu) throws MyException {
        iStatement fifthStatement = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                    new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                        new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                            new CompoundStatement(new PrintStatement(new VariableExpression("v")),
                                (new PrintStatement(new VariableExpression("a"))))))));

        fifthStatement.typeCheck(new MyDictionary<>());

        ProgramState fifthState = new ProgramState(fifthStatement);
        iRepository fifthRepository = new Repository(fifthState, "log5.txt");
        Controller fifthController = new Controller(fifthRepository, true);

        menu.addCommand(new RunExample("5", fifthStatement.toString(), fifthController));
    }

    private void addSixthExampleToMenu(TextMenu menu) throws MyException {
        iStatement sixthStatement = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                    new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                        new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                            new CompoundStatement(new PrintStatement(new HeapReadingExpression(new VariableExpression("v"))),
                                (new PrintStatement(new ArithmeticExpression('+',
                                    new HeapReadingExpression(new HeapReadingExpression(new VariableExpression("a"))),
                                        new ValueExpression(new IntValue(5))))))))));

        sixthStatement.typeCheck(new MyDictionary<>());

        ProgramState sixthState = new ProgramState(sixthStatement);
        iRepository sixthRepository = new Repository(sixthState, "log6.txt");
        Controller sixthController = new Controller(sixthRepository, true);

        menu.addCommand(new RunExample("6", sixthStatement.toString(), sixthController));
    }

    private void addSeventhExampleToMenu(TextMenu menu) throws MyException {
        iStatement seventhStatement = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                    new CompoundStatement(new PrintStatement(new HeapReadingExpression(new VariableExpression("v"))),
                        new CompoundStatement(new HeapWritingStatement("v", new ValueExpression(new IntValue(30))),
                            new PrintStatement(new ArithmeticExpression('+', new HeapReadingExpression(new VariableExpression("v")),
                                new ValueExpression(new IntValue(5))))))));

        seventhStatement.typeCheck(new MyDictionary<>());

        ProgramState seventhState = new ProgramState(seventhStatement);
        iRepository seventhRepository = new Repository(seventhState, "log7.txt");
        Controller seventhController = new Controller(seventhRepository, true);

        menu.addCommand(new RunExample("7", seventhStatement.toString(), seventhController));
    }

    private void addEighthExampleToMenu(TextMenu menu) throws MyException {
        iStatement eighthStatement = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                    new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                        new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                            new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(30))),
                                (new PrintStatement(new HeapReadingExpression(new HeapReadingExpression(new VariableExpression("a"))))))))));

        eighthStatement.typeCheck(new MyDictionary<>());

        ProgramState eighthState = new ProgramState(eighthStatement);
        iRepository eighthRepository = new Repository(eighthState, "log8.txt");
        Controller eighthController = new Controller(eighthRepository, true);

        menu.addCommand(new RunExample("8", eighthStatement.toString(), eighthController));
    }

    private void addNinthExampleToMenu(TextMenu menu) throws MyException {
        iStatement ninthStatement = new CompoundStatement(new VariableDeclarationStatement("v",new IntType()),
                new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(4))),
                    new WhileStatement(new RelationalExpression(">", new VariableExpression("v"),
                        new ValueExpression(new IntValue(0))), new CompoundStatement(new PrintStatement(new VariableExpression("v")),
                            new AssignStatement( "v", new ArithmeticExpression('-', new VariableExpression("v"),
                                new ValueExpression(new IntValue(1))))))));

        ninthStatement.typeCheck(new MyDictionary<>());

        ProgramState ninthState = new ProgramState(ninthStatement);
        iRepository ninthRepository = new Repository(ninthState, "log9.txt");
        Controller ninthController = new Controller(ninthRepository, true);

        menu.addCommand(new RunExample("9", ninthStatement.toString(), ninthController));
    }

    private void addTenthExampleToMenu(TextMenu menu) throws MyException {
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

        tenthStatement.typeCheck(new MyDictionary<>());

        ProgramState tenthState = new ProgramState(tenthStatement);
        iRepository tenthRepository = new Repository(tenthState, "log10.txt");
        Controller tenthController = new Controller(tenthRepository, true);

        menu.addCommand(new RunExample("10", tenthStatement.toString(), tenthController));
    }

    private void addFirstFaultyTypeCheckerExample(TextMenu menu) throws MyException {
        // int v; v=5; if (v==5), then (int a; a=7;), else (print(v)); print(a)
        iStatement faultyStatement = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(5))),
                    new CompoundStatement(new IfStatement(new RelationalExpression("==", new VariableExpression("v"),
                        new ValueExpression(new IntValue(5))), new CompoundStatement(
                            new VariableDeclarationStatement("a", new IntType()), new AssignStatement("a", new ValueExpression(new IntValue(7)))),
                                new PrintStatement(new VariableExpression("v"))), new PrintStatement(new VariableExpression("a")))));

        try {
            faultyStatement.typeCheck(new MyDictionary<>());
        } catch (MyException error) {
            throw new MyException(faultyStatement + " statement not created -> " + error.getMessage());
        }

        ProgramState state = new ProgramState(faultyStatement);
        iRepository repository = new Repository(state, "log_1.txt");
        Controller controller = new Controller(repository, true);

        menu.addCommand(new RunExample("_1", faultyStatement.toString(), controller));
    }

    private void addSecondFaultyTypeCheckerExample(TextMenu menu) throws MyException {
        // int v; v=6; while (v > 1) {int a; a=v; print(a); v=v-1; }; print(a);
        iStatement faultyStatement = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(6))),
                    new CompoundStatement(new WhileStatement(new RelationalExpression(">", new VariableExpression("v"), new ValueExpression(new IntValue(1))),
                        new CompoundStatement(new VariableDeclarationStatement("a", new IntType()),
                            new CompoundStatement(new AssignStatement("a", new VariableExpression("v")),
                                new CompoundStatement(new PrintStatement(new VariableExpression("a")),
                                    new AssignStatement( "v", new ArithmeticExpression('-',
                                        new VariableExpression("v"), new ValueExpression(new IntValue(1)))))))),
                                            new PrintStatement(new VariableExpression("a")))));

        try {
            faultyStatement.typeCheck(new MyDictionary<>());
        } catch (MyException error) {
            throw new MyException(faultyStatement + " statement not created -> " + error.getMessage());
        }

        ProgramState state = new ProgramState(faultyStatement);
        iRepository repository = new Repository(state, "log_2.txt");
        Controller controller = new Controller(repository, true);

        menu.addCommand(new RunExample("_2", faultyStatement.toString(), controller));
    }

    private void addThirdFaultyTypeCheckerExample(TextMenu menu) throws MyException {
        // int v; v=7; createThread(int a; a=v;); print(a);
        iStatement faultyStatement = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(7))),
                    new CompoundStatement(new CreateThreadStatement(new CompoundStatement(
                        new VariableDeclarationStatement("a", new IntType()), new AssignStatement("a",
                            new VariableExpression("v")))), new PrintStatement(new VariableExpression("a")))));

        try {
            faultyStatement.typeCheck(new MyDictionary<>());
        } catch (MyException error) {
            throw new MyException(faultyStatement + " statement not created -> " + error.getMessage());
        }

        ProgramState state = new ProgramState(faultyStatement);
        iRepository repository = new Repository(state, "log_3.txt");
        Controller controller = new Controller(repository, true);

        menu.addCommand(new RunExample("_3", faultyStatement.toString(), controller));
    }
}
