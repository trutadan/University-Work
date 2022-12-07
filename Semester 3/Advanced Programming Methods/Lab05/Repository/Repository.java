package Repository;

import Exceptions.MyException;
import Model.ProgramState.ProgramState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

// done for LAB05
public class Repository implements iRepository {
    List<ProgramState> programStates;
    String logFilePath;

    public Repository(ProgramState _programState, String _logFilePath) {
        this.programStates = new ArrayList<>();
        this.programStates.add(_programState);
        this.logFilePath = _logFilePath;

        this.clearLogFile();
    }

    public List<ProgramState> getProgramStatesList() {
        return this.programStates;
    }

    public void setProgramStates(List<ProgramState> newProgramState) {
        this.programStates = newProgramState;
    }

    public String getLogFilePath() {
        return this.logFilePath;
    }

    public void setLogFilePath(String newLogFilePath) {
        this.logFilePath = newLogFilePath;
    }

    public void addProgramState(ProgramState newProgramState) {
        this.programStates.add(newProgramState);
    }

    public void logProgramStateExecution(ProgramState programState) throws MyException {
        try {
            PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(this.logFilePath, true)));

            logFile.println(programState.toString());
            logFile.close();
        } catch (IOException error) {
            throw new MyException(error.getMessage());
        }
    }

    public void clearLogFile() throws MyException {
        try {
            PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(this.logFilePath, false)));
            logFile.close();
        } catch (IOException error) {
            throw new MyException(error.getMessage());
        }
    }
}
