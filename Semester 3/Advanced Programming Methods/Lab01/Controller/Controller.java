package Controller;

import Exceptions.RepositoryException;
import Model.Automobile;
import Repository.iRepository;

import java.util.Arrays;

public class Controller {
    iRepository repository;

    public Controller(iRepository repository) {
        this.repository = repository;
    }

    public void addAutomobile(Automobile automobile) throws RepositoryException {
        this.repository.addObject(automobile);
    }

    public void removeAutomobile(int position) throws RepositoryException {
        this.repository.removeObject(position);
    }

    public Automobile[] getAllAutomobilesFromRepository() {
        return this.repository.getAllAutomobiles();
    }

    public int getAutomobilesSize() { return this.repository.getSize(); }

    public Automobile[] getFilteredAutomobilesByRepairPrice(int repairPrice) {
        Automobile[] filteredAutomobiles = new Automobile[this.repository.getSize()];

        int filteredArraySize = 0;
        for(Automobile automobile : this.repository.getAllAutomobiles())
            if (automobile != null)
                if (automobile.getRepairPrice() > repairPrice)
                    filteredAutomobiles[filteredArraySize++] = automobile;

        Automobile[] automobilesToReturn = new Automobile[filteredArraySize];
        System.arraycopy(filteredAutomobiles, 0, automobilesToReturn, 0, filteredArraySize);

        return automobilesToReturn;
    }
}