import java.util.TimerTask;

public class CheckerTask extends TimerTask {

    // from time to time, a consistency check shall be performed
    @Override
    public void run() {
        var checker = new Checker(Main.primaryNodes);

        System.out.println("Preparing to run consistency checker...");
        var result = checker.runChecker();

        if (result)
            System.out.println("Successfully passed the checker!");
        else
            System.out.println("Checker detected that something went wrong!");
    }
}