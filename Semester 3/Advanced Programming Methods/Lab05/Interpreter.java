import Controller.Controller;
import Model.Expressions.*;
import Model.ProgramState.ProgramState;
import Model.Statements.*;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Types.ReferenceType;
import Model.Types.StringType;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Repository.iRepository;
import Repository.Repository;
import View.ExitCommand;
import View.RunExample;
import View.TextMenu;

// done for LAB05
public class Interpreter {
    public static void main(String[] args) {
        iStatement firstStatement = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(2))),
                    new PrintStatement(new VariableExpression("v"))));

        ProgramState firstState = new ProgramState(firstStatement);
        iRepository firstRepository = new Repository(firstState, "log1.txt");
        Controller firstController = new Controller(firstRepository, true);


        iStatement secondStatement = new CompoundStatement(new VariableDeclarationStatement("a", new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("b", new IntType()),
                    new CompoundStatement(new AssignStatement("a", new ArithmeticExpression('+', new ValueExpression(new IntValue(2)),
                        new ArithmeticExpression('*', new ValueExpression(new IntValue(3)), new ValueExpression(new IntValue(5))))),
                            new CompoundStatement(new AssignStatement("b", new ArithmeticExpression('+', new VariableExpression("a"),
                                new ValueExpression(new IntValue(1)))), new PrintStatement(new VariableExpression("b"))))));

        ProgramState secondState = new ProgramState(secondStatement);
        iRepository secondRepository = new Repository(secondState, "log2.txt");
        Controller secondController = new Controller(secondRepository, true);


        iStatement thirdStatement = new CompoundStatement(new VariableDeclarationStatement("a", new BoolType()),
                new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                    new CompoundStatement(new AssignStatement("a", new ValueExpression(new BoolValue(true))),
                        new CompoundStatement(new IfStatement(new VariableExpression("a"),
                            new AssignStatement("v", new ValueExpression(new IntValue(2))),
                                new AssignStatement("v", new ValueExpression(new IntValue(3)))),
                                    new PrintStatement(new VariableExpression("v"))))));

        ProgramState thirdState = new ProgramState(thirdStatement);
        iRepository thirdRepository = new Repository(thirdState, "log3.txt");
        Controller thirdController = new Controller(thirdRepository, true);


        iStatement fourthStatement = new CompoundStatement(new VariableDeclarationStatement("varf", new StringType()),
                new CompoundStatement(new AssignStatement("varf", new ValueExpression(new StringValue("test.in"))),
                    new CompoundStatement(new OpenReadFileStatement(new VariableExpression("varf")),
                        new CompoundStatement(new VariableDeclarationStatement("varc", new IntType()),
                            new CompoundStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"),
                                new CompoundStatement(new PrintStatement(new VariableExpression("varc")),
                                    new CompoundStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"),
                                        new CompoundStatement(new PrintStatement(new VariableExpression("varc")),
                                            new CloseReadFileStatement(new VariableExpression("varf"))))))))));

        ProgramState fourthState = new ProgramState(fourthStatement);
        iRepository fourthRepository = new Repository(fourthState, "log4.txt");
        Controller fourthController = new Controller(fourthRepository, true);


        iStatement fifthStatement = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                    new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                        new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                            new CompoundStatement(new PrintStatement(new VariableExpression("v")),
                                (new PrintStatement(new VariableExpression("a"))))))));

        ProgramState fifthState = new ProgramState(fifthStatement);
        iRepository fifthRepository = new Repository(fifthState, "log5.txt");
        Controller fifthController = new Controller(fifthRepository, true);


        iStatement sixthStatement = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                    new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                        new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                            new CompoundStatement(new PrintStatement(new HeapReadingExpression(new VariableExpression("v"))),
                                (new PrintStatement(new ArithmeticExpression('+',
                                    new HeapReadingExpression(new HeapReadingExpression(new VariableExpression("a"))),
                                        new ValueExpression(new IntValue(5))))))))));

        ProgramState sixthState = new ProgramState(sixthStatement);
        iRepository sixthRepository = new Repository(sixthState, "log6.txt");
        Controller sixthController = new Controller(sixthRepository, true);


        iStatement seventhStatement = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                    new CompoundStatement(new PrintStatement(new HeapReadingExpression(new VariableExpression("v"))),
                        new CompoundStatement(new HeapWritingStatement("v", new ValueExpression(new IntValue(30))),
                            new PrintStatement(new ArithmeticExpression('+', new HeapReadingExpression(new VariableExpression("v")),
                                new ValueExpression(new IntValue(5))))))));

        ProgramState seventhState = new ProgramState(seventhStatement);
        iRepository seventhRepository = new Repository(seventhState, "log7.txt");
        Controller seventhController = new Controller(seventhRepository, true);


        iStatement eighthStatement = new CompoundStatement(new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                    new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                        new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                            new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(30))),
                                (new PrintStatement(new HeapReadingExpression(new HeapReadingExpression(new VariableExpression("a"))))))))));

        ProgramState eighthState = new ProgramState(eighthStatement);
        iRepository eighthRepository = new Repository(eighthState, "log8.txt");
        Controller eighthController = new Controller(eighthRepository, true);


        iStatement ninthStatement = new CompoundStatement(new VariableDeclarationStatement("v",new IntType()),
                new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(4))),
                    new WhileStatement(new RelationalExpression(">", new VariableExpression("v"),
                        new ValueExpression(new IntValue(0))), new CompoundStatement(new PrintStatement(new VariableExpression("v")),
                            new AssignStatement( "v", new ArithmeticExpression('-', new VariableExpression("v"),
                                new ValueExpression(new IntValue(1))))))));

        ProgramState ninthState = new ProgramState(ninthStatement);
        iRepository ninthRepository = new Repository(ninthState, "log9.txt");
        Controller ninthController = new Controller(ninthRepository, true);

        iStatement tenthStatement = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("a", new ReferenceType(new IntType())),
                    new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(10))),
                        new CompoundStatement(new HeapAllocationStatement("a", new ValueExpression(new IntValue(22))),
                            new CompoundStatement(new CreateThreadStatement(new CompoundStatement(new HeapWritingStatement("a", new ValueExpression(new IntValue(30))),
                                new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(32))),
                                    new CompoundStatement(new PrintStatement(new VariableExpression("v")),
                                        new PrintStatement(new HeapReadingExpression(new VariableExpression("a"))))))),
                                            new CompoundStatement(new PrintStatement(new VariableExpression("v")),
                                                new PrintStatement(new HeapReadingExpression(new VariableExpression("a")))))))));

        ProgramState tenthState = new ProgramState(tenthStatement);
        iRepository tenthRepository = new Repository(tenthState, "log10.txt");
        Controller tenthController = new Controller(tenthRepository, true);


        TextMenu menu = new TextMenu();

        menu.addCommand(new ExitCommand("0", "Exit."));
        menu.addCommand(new RunExample("1", firstStatement.toString(), firstController));
        menu.addCommand(new RunExample("2", secondStatement.toString(), secondController));
        menu.addCommand(new RunExample("3", thirdStatement.toString(), thirdController));
        menu.addCommand(new RunExample("4", fourthStatement.toString(), fourthController));
        menu.addCommand(new RunExample("5", fifthStatement.toString(), fifthController));
        menu.addCommand(new RunExample("6", sixthStatement.toString(), sixthController));
        menu.addCommand(new RunExample("7", seventhStatement.toString(), seventhController));
        menu.addCommand(new RunExample("8", eighthStatement.toString(), eighthController));
        menu.addCommand(new RunExample("9", ninthStatement.toString(), ninthController));
        menu.addCommand(new RunExample("10", tenthStatement.toString(), tenthController));

        menu.show();
    }
}