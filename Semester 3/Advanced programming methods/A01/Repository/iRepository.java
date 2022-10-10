package Repository;

import Model.Automobile;

public interface iRepository {
    void addObject(Automobile automobile);

    void removeObject(int position);

    Automobile[] getAllAutomobiles();

    int getSize();
}
