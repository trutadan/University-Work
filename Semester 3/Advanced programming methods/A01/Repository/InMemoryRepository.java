package Repository;

import Exceptions.RepositoryException;
import Model.Automobile;

public class InMemoryRepository implements iRepository{
    int size;
    Automobile[] automobiles;

    public InMemoryRepository(int capacity) {
        if (capacity <= 0)
            throw new RepositoryException("Capacity must be a positive number!");

        this.size = 0;
        this.automobiles = new Automobile[capacity];
    }

    @Override
    public void addObject(Automobile automobile) {
        if (this.automobiles.length == size)
            throw new RepositoryException("Repository is full, you can't add more automobiles!");

        this.automobiles[this.size] = automobile;
        this.size++;
    }

    @Override
    public void removeObject(int position) {
        if (position < 0 || position > this.size)
            throw new RepositoryException("Position given was not found in the repository!");

        Automobile[] automobilesAfterRemoval = new Automobile[this.size - 1];
        int automobilesAfterRemovalSize = 0;

        for(int index = 0; index < this.size; index++)
            if (index != position)
                automobilesAfterRemoval[automobilesAfterRemovalSize++] = automobiles[index];

        this.automobiles = automobilesAfterRemoval;
        this.size--;
    }

    @Override
    public Automobile[] getAllAutomobiles() {
        return this.automobiles;
    }

    @Override
    public int getSize() {
        return this.size;
    }
}
