package Repository;

import Exceptions.RepositoryException;
import Model.Automobile;

public interface iRepository {
    void addObject(Automobile automobile) throws RepositoryException;

    void removeObject(int position) throws RepositoryException;

    Automobile[] getAllAutomobiles();

    int getSize();
}