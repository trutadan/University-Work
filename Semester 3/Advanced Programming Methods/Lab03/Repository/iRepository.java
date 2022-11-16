package Repository;

import Exceptions.MyException;
import Model.ProgramState;

import java.io.IOException;

// done for LAB02
public interface iRepository {
    ProgramState getProgramState();

    String getLogFilePath();

    void logProgramStateExecution() throws MyException, IOException;
}
