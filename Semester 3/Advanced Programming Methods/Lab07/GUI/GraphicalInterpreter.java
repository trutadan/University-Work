package GUI;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

// done for LAB07
public class GraphicalInterpreter extends Application {
    @Override
    public void start(Stage firstStage) throws IOException {
        FXMLLoader fxmlLoaderList = new FXMLLoader();
        fxmlLoaderList.setLocation(getClass().getResource("program-states-list-view.fxml"));
        Parent listRoot = fxmlLoaderList.load();

        ListController listController = fxmlLoaderList.getController();

        Scene listScene = new Scene(listRoot, 320, 240);

        firstStage.setTitle("Program States List");
        firstStage.setScene(listScene);
        firstStage.show();


        FXMLLoader fxmlLoaderProgram = new FXMLLoader();
        fxmlLoaderProgram.setLocation(getClass().getResource("program-state-view.fxml"));
        Parent programRoot = fxmlLoaderProgram.load();

        ProgramController programController = fxmlLoaderProgram.getController();
        listController.setProgramController(programController);

        Scene programScene = new Scene(programRoot, 600, 560);

        Stage secondStage = new Stage();
        secondStage.setTitle("Program Interpreter");
        secondStage.setScene(programScene);
        secondStage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}