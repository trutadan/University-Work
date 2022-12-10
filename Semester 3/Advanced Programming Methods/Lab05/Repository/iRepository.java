package Repository;

import Exceptions.MyException;
import Model.ProgramState.ProgramState;

import java.util.List;

// done for LAB05
public interface iRepository {
    List<ProgramState> getProgramStatesList();

    void setProgramStates(List<ProgramState> newProgramState);

    void logProgramStateExecution(ProgramState programState) throws MyException;

    void clearLogFile() throws MyException;
}
