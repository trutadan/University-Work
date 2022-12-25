package GUI;

import Controller.Controller;
import Exceptions.MyException;
import Model.DataStructures.MyDictionary;
import Model.ProgramState.ProgramState;
import Model.ProgramState.ProgramStatesExamples;
import Model.Statements.iStatement;
import Repository.Repository;
import Repository.iRepository;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.ListView;
import javafx.scene.layout.Region;

import java.util.List;

public class ListController {
    private ProgramController programController;

    public void setProgramController(ProgramController programController) {
        this.programController = programController;
    }

    @FXML
    private ListView<iStatement> statementsListView;

    @FXML
    private Button selectButton;

    @FXML
    private Button exitButton;

    @FXML
    public void initialize() {
        ProgramStatesExamples menuCreator = new ProgramStatesExamples();
        List<iStatement> statements = menuCreator.getProgramStatesList();
        this.statementsListView.setItems(FXCollections.observableArrayList(statements));

        this.selectButton.setOnAction((ActionEvent event) -> {
            int selectedIndex = this.statementsListView.getSelectionModel().getSelectedIndex();
            if (selectedIndex < 0 || selectedIndex >= statements.size())
                return;

            iStatement statement = statements.get(selectedIndex);

            try {
                statement.typeCheck(new MyDictionary<>());

                ProgramState state = new ProgramState(statement);
                iRepository repository = new Repository(state, "log" + (selectedIndex + 1) + ".txt");
                Controller controller = new Controller(repository, true);

                programController.setController(controller);

            } catch (MyException error) {
                Alert alert = new Alert(Alert.AlertType.ERROR, error.getMessage(), ButtonType.OK);
                alert.getDialogPane().setMinHeight(Region.USE_PREF_SIZE);
                alert.setTitle("Statement not created!");

                alert.showAndWait();
            }
        });

        this.exitButton.setOnAction((ActionEvent event) -> {
            Platform.exit();
        });
    }
}
