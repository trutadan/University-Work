package Controller;

import Exceptions.MyException;
import Model.DataStructures.MyiStack;
import Model.ProgramState;
import Model.Statements.iStatement;
import Repository.iRepository;

import java.io.IOException;

// done for LAB02
public class Controller {
    iRepository repository;
    boolean displayFlag = false;

    public Controller(iRepository _repository, boolean _displayFlag) {
        this.repository = _repository;
        this.displayFlag = _displayFlag;
    }

    public boolean getDisplayFlag() {
        return displayFlag;
    }

    public void setDisplayFlag(boolean newDisplayFlag) {
        displayFlag = newDisplayFlag;
    }

    public ProgramState oneStepExecution(ProgramState state) throws MyException {
        MyiStack<iStatement> executionStack = state.getExecutionStack();
        if(executionStack.isEmpty())
            throw new MyException("ProgramState's stack is empty!");

        iStatement currentStatement = executionStack.pop();

        state.setExecutionStack(executionStack);

        return currentStatement.execute(state);
    }

    public void allStepExecution() throws IOException {
        ProgramState programState = repository.getProgramState();
        displayCurrentProgramState();
        repository.logProgramStateExecution();

        while (!programState.getExecutionStack().isEmpty()) {
            oneStepExecution(programState);
            displayCurrentProgramState();
            repository.logProgramStateExecution();
            }

        programState.resetToOriginalProgram();
    }

    public void displayCurrentProgramState() {
        if (displayFlag)
            System.out.println(repository.getProgramState().toString());
    }
}
