package Repository;

import Exceptions.MyException;
import Model.ProgramState;

import java.util.ArrayList;
import java.util.List;

// done for LAB02
public class Repository implements iRepository {
    List<ProgramState> programStates;
    int currentPosition;

    public Repository() {
        this.programStates = new ArrayList<>();
        this.currentPosition = 0;
    }

    public ProgramState getCurrentProgramState() {
        return programStates.get(currentPosition);
    }

    public void setCurrentPosition(int newPosition) throws MyException {
        if (newPosition < 0 || newPosition >= programStates.size())
            throw new MyException("Not a valid program state position!");

        this.currentPosition = newPosition;
    }

    public void addProgramState(ProgramState newProgramState) { programStates.add(newProgramState); }
}
