package Controller;

import Exceptions.MyException;
import Model.DataStructures.MyiStack;
import Model.ProgramState;
import Model.Statements.iStatement;
import Model.Values.ReferenceValue;
import Model.Values.Value;
import Repository.iRepository;

import java.io.IOException;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

// done for LAB04
public class Controller {
    iRepository repository;
    boolean displayFlag;

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

    List<Integer> getAddressFromTable(Collection <Value> symTableValues){
        return symTableValues.stream()
                .filter(v-> v instanceof ReferenceValue)
                .map(v-> {ReferenceValue value1 = (ReferenceValue) v; return value1.getAddress();})
                .collect(Collectors.toList());
    }

    Map<Integer, Value> unsafeGarbageCollector(List<Integer> symbolsTableAddresses, Map<Integer,Value> heapTable) {
        return heapTable.entrySet().stream().filter(e-> symbolsTableAddresses.contains(e.getKey())).
                collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    Map<Integer, Value> safeGarbageCollector(List<Integer> symbolsTableAddresses, List<Integer> heapTableAddresses, Map<Integer,Value> heapTable) {
        return heapTable.entrySet().stream().filter(e-> symbolsTableAddresses.contains(e.getKey()) || heapTableAddresses.contains(e.getKey())).
                collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
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

            // unsafe garbage collector
        /*  programState.getHeapTable().setContent(unsafeGarbageCollector(getAddressFromTable
                    (programState.getSymbolsTable().getContent().values()),
                            programState.getHeapTable().getContent())); */

            // safe garbage collector
            programState.getHeapTable().setContent(safeGarbageCollector(getAddressFromTable(programState.getSymbolsTable().getContent().values()),
                    getAddressFromTable(programState.getHeapTable().getContent().values()), programState.getHeapTable().getContent()));

            repository.logProgramStateExecution();
            }

        programState.resetToOriginalProgram();
    }

    public void displayCurrentProgramState() {
        if (displayFlag)
            System.out.println(repository.getProgramState().toString());
    }
}
