package Controller;

import Exceptions.MyException;
import Model.ProgramState.ProgramState;
import Model.Statements.iStatement;
import Model.Values.ReferenceValue;
import Model.Values.Value;
import Repository.iRepository;

import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

// done for LAB07
public class Controller {
    iRepository repository;
    boolean displayFlag;

    // threads pool
    ExecutorService executor;

    public Controller(iRepository _repository, boolean _displayFlag) {
        this.repository = _repository;
        this.displayFlag = _displayFlag;
    }

    public boolean getDisplayFlag() {
        return this.displayFlag;
    }

    public void setDisplayFlag(boolean newDisplayFlag) {
        this.displayFlag = newDisplayFlag;
    }

    public List<ProgramState> getProgramStates() {
        return this.repository.getProgramStatesList();
    }

    List<Integer> getAddressFromTable(Collection <Value> tableValues){
        return tableValues.stream()
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

    void conservativeGarbageCollector(List<ProgramState> programStatesList) {
        // there is one heap shared by multiple ProgramStates, but multiple SymbolsTables(one for each ProgramState)
        programStatesList.forEach(programState -> {programState.getHeapTable().setContent(safeGarbageCollector(getAddressFromTable(programState.getSymbolsTable().getContent().values()),
                getAddressFromTable(programState.getHeapTable().getContent().values()), programState.getHeapTable().getContent()));});
    }

    public void oneStepForAllProgramStates(List<ProgramState> programStatesList) throws MyException {
        // before the execution, print the ProgramStatesList into the log file and system output
        programStatesList.forEach(programState -> {
            this.repository.logProgramStateExecution(programState);

            displayProgramState(programState);
        });

        // prepare the list of callables which will run concurrently oneStepExecution for each of the existing ProgramStates
        List<Callable<ProgramState>> callList = programStatesList.stream()
                .map((ProgramState programState) -> (Callable<ProgramState>) (programState::oneStepExecution)).
                collect(Collectors.toList());

        try {
            // start the execution of the callables; it returns the list of new created ProgramStates (namely threads)
            List<ProgramState> newProgramStatesList = this.executor.invokeAll(callList).stream()
                    .map(future -> {
                        try {
                            return future.get(); // get the results of the execution
                        } catch (InterruptedException | ExecutionException error) {
                            System.out.println(error.getMessage());
                            return null;
                        }
                    }).filter(Objects::nonNull)
                    .collect(Collectors.toList());

            // add the new created threads to the list of existing threads
            programStatesList.addAll(newProgramStatesList);

            // after the execution, print the ProgramStatesList into the log file and system output
            programStatesList.forEach(programState -> {
                this.repository.logProgramStateExecution(programState);

                displayProgramState(programState);
            });

            // save the current programs in the repository
            this.repository.setProgramStates(programStatesList);

        } catch (InterruptedException error) {
            throw new MyException(error.getMessage());
        }
    }

    public void oneStepExecution() throws MyException {
        // thread pool with 2 threads
        this.executor = Executors.newFixedThreadPool(2);

        // remove the completed programs
        List<ProgramState> programStatesList = removeCompletedProgramStates(this.repository.getProgramStatesList());

        conservativeGarbageCollector(programStatesList);
        oneStepForAllProgramStates(programStatesList);

        // prevents sending more work to the executor service, but all the existing tasks will still run to completion
        this.executor.shutdownNow();
    }

    public void allStepExecution() throws MyException {
        // thread pool with 2 threads
        this.executor = Executors.newFixedThreadPool(2);

        // remove the completed programs
        List<ProgramState> programStatesList = removeCompletedProgramStates(this.repository.getProgramStatesList());

        // get the initial statement
        iStatement initialStatement = repository.getProgramStatesList().get(0).getOriginalProgram();

        while(programStatesList.size() > 0) {
            conservativeGarbageCollector(programStatesList);
            oneStepForAllProgramStates(programStatesList);

            //remove the completed programs
            programStatesList = removeCompletedProgramStates(this.repository.getProgramStatesList());
        }

        // prevents sending more work to the executor service, but all the existing tasks will still run to completion
        this.executor.shutdownNow();

        // reset program state
        programStatesList.add(new ProgramState(initialStatement));

        // here the repository still contains at least one completed ProgramState and its List<ProgramStates> is not empty
        this.repository.setProgramStates(programStatesList);
    }

    public List<ProgramState> removeCompletedProgramStates(List<ProgramState> programsInProgressList) {
        return programsInProgressList.stream().
                filter(ProgramState::isNotCompleted).
                collect(Collectors.toList());
    }

    public void displayProgramState(ProgramState programState) {
        if (this.displayFlag)
            System.out.println(programState.toString());
    }
}
