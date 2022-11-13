package View;

// done for LAB03
public abstract class Command {
    String key, description;

    public Command(String _key, String _description) {
        this.key = _key;
        this.description = _description;
    }

    public abstract void execute();

    public String getKey() {
        return key;
    }

    public String getDescription() {
        return description;
    }
}