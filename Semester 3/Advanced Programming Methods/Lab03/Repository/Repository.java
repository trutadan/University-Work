package Repository;

import Exceptions.MyException;
import Model.ProgramState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

// done for LAB02
public class Repository implements iRepository {
    ProgramState programState;
    String logFilePath;

    public Repository(ProgramState _programState, String _logFilePath) {
        this.programState = _programState;
        this.logFilePath = _logFilePath;
    }

    public ProgramState getProgramState() {
        return programState;
    }

    void setProgramState(ProgramState newProgramState) {
        programState = newProgramState;
    }

    public String getLogFilePath() {
        return logFilePath;
    }

    void setLogFilePath(String newLogFilePath) {
        logFilePath = newLogFilePath;
    }

    public void logProgramStateExecution() throws MyException, IOException {
        PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)));

        logFile.println(this.programState.toString());
        logFile.close();
    }
}
