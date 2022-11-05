package Repository;

import Model.ProgramState;

import java.util.List;

// done for LAB02
public interface iRepository {
    ProgramState getCurrentProgramState();

    void setCurrentPosition(int newPosition);

    void addProgramState(ProgramState newProgramState);
}
