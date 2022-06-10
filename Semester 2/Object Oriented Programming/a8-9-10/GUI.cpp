#include "GUI.h"
#include <QStandardItemModel>

GUI::GUI(Controller& _controller) : controller(_controller)
{
	this->welcomeLabel = new QLabel(this);

	this->adminButton = new QPushButton("&ADMIN", this);
	this->userButton = new QPushButton("&USER", this);

	this->initializeGUI();
}

void GUI::initializeGUI()
{
	this->setWindowTitle("Events Manager");
	this->setWindowIcon(QIcon("icon.jpg"));

	QVBoxLayout* mainLayout = new QVBoxLayout(this);

	// add text to the top of the layout
	this->welcomeLabel->setText("Welcome to Events Manager Application!\nPlease choose the mode from below.");
	this->welcomeLabel->setAlignment(Qt::AlignCenter);
	this->welcomeLabel->setStyleSheet("color: #000000;");
	QFont welcomeFont("Arial");
	welcomeFont.setItalic(true);
	welcomeFont.setPointSize(20);
	this->welcomeLabel->setFont(welcomeFont);

	mainLayout->addWidget(this->welcomeLabel);

	// add the buttons
	this->adminButton->setFont(QFont("Arial", 14));
	this->adminButton->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,stop: 0 #1e847f, stop: 0.4 gray,stop: 1 #1e847f); color: #ffffff;");
	mainLayout->addWidget(this->adminButton);

	this->userButton->setFont(QFont("Arial", 14));
	this->userButton->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,stop: 0 #1e847f, stop: 0.4 gray,stop: 1 #1e847f); color: #ffffff;");
	mainLayout->addWidget(this->userButton);

	// set the main layout
	this->setLayout(mainLayout);

	// set layout background color
	this->setStyleSheet("background-color:#ecc19c");

	// connect signals and slots
	this->connectSignalsAndSlots();
}

void GUI::popAdminWindow()
{
	this->controller.clear_admin_undo_redo_stack();
	AdminGUI* adminGUI = new AdminGUI{ this, controller };
	adminGUI->show();
}

void GUI::popUserWindow()
{
	UserGUI* userGUI = new UserGUI{ this, controller };
	userGUI->show();
}

void GUI::connectSignalsAndSlots()
{
	// connect the mode buttons to the corresponding screens pop-up action
	QObject::connect(this->adminButton, &QPushButton::clicked, this, &GUI::popAdminWindow);
	QObject::connect(this->userButton, &QPushButton::clicked, this, &GUI::popUserWindow);
}

GUI::~GUI()
{
	{}
}

AdminGUI::AdminGUI(QWidget* parent, Controller& _controller) : controller(_controller)
{
	this->entryMessageLabel = new QLabel(this);

	this->eventsListWidget = new QListWidget();

	this->titleLineEdit = new QLineEdit();
	this->descriptionLineEdit = new QLineEdit();
	this->dateLineEdit = new QLineEdit();
	this->timeLineEdit = new QLineEdit();
	this->numberOfPeopleLineEdit = new QLineEdit();
	this->linkLineEdit = new QLineEdit();

	this->addEventButton = new QPushButton("&ADD");
	this->removeEventButton = new QPushButton("&REMOVE");
	this->updateEventButton = new QPushButton("&UPDATE");

	this->chartButton = new QPushButton("&CHART");

	this->undoActionButton = new QPushButton("UNDO");
	this->redoActionButton = new QPushButton("REDO");

	this->undoActionShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
	this->redoActionShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this);

	this->errorBox = new QMessageBox();

	// set the admin gui's parent
	this->setParent(parent);

	// pop-up a new window, in order to stop displaying the admin gui screen on the main gui window
	this->setWindowFlag(Qt::Window);

	this->initializeAdminGUI();
}

void AdminGUI::initializeAdminGUI()
{
	QVBoxLayout* mainLayout = new QVBoxLayout(this);

	this->errorBox->setWindowIcon(QIcon("icon.jpg"));
	this->errorBox->setIcon(QMessageBox::Critical);

	// add text to the top of the layout
	this->entryMessageLabel->setText("ADMIN MODE");
	this->entryMessageLabel->setAlignment(Qt::AlignCenter);
	this->entryMessageLabel->setStyleSheet("color: #000000");

	QFont messageFont("Arial");
	messageFont.setItalic(true);
	messageFont.setBold(true);
	messageFont.setPointSize(20);
	this->entryMessageLabel->setFont(messageFont);

	mainLayout->addWidget(this->entryMessageLabel);

	// add the chart button
	QHBoxLayout* chartLayout = new QHBoxLayout();
	this->chartButton->setFont(QFont("Arial", 14));
	this->chartButton->setStyleSheet("background-color :#1e847f; color: #ffffff;");
	chartLayout->addWidget(this->chartButton);

	mainLayout->addLayout(chartLayout);

	// add the list of events
	mainLayout->addWidget(this->eventsListWidget);

	// add the line edits
	QFormLayout* lineEditsLayout = new QFormLayout();

	lineEditsLayout->addRow("Title", this->titleLineEdit);
	lineEditsLayout->addRow("Description", this->descriptionLineEdit);
	lineEditsLayout->addRow("Date", this->dateLineEdit);
	lineEditsLayout->addRow("Time", this->timeLineEdit);
	lineEditsLayout->addRow("Number of people", this->numberOfPeopleLineEdit);
	lineEditsLayout->addRow("Link", this->linkLineEdit);

	mainLayout->addLayout(lineEditsLayout);

	// add the action buttons
	QHBoxLayout* actionButtonsLayout = new QHBoxLayout();
	this->addEventButton->setFont(QFont("Arial", 14));
	this->addEventButton->setStyleSheet("background-color :#1e847f; color: #ffffff;");
	actionButtonsLayout->addWidget(this->addEventButton);

	this->removeEventButton->setFont(QFont("Arial", 14));
	this->removeEventButton->setStyleSheet("background-color :#1e847f; color: #ffffff;");
	actionButtonsLayout->addWidget(this->removeEventButton);

	this->updateEventButton->setFont(QFont("Arial", 14));
	this->updateEventButton->setStyleSheet("background-color :#1e847f; color: #ffffff;");
	actionButtonsLayout->addWidget(this->updateEventButton);

	mainLayout->addLayout(actionButtonsLayout);

	// add the undo/redo buttons
	QHBoxLayout* undoRedoButtonsLayout = new QHBoxLayout();
	this->undoActionButton->setFont(QFont("Arial", 14));
	this->undoActionButton->setStyleSheet("background-color :#1e847f; color: #ffffff;");
	undoRedoButtonsLayout->addWidget(this->undoActionButton);

	this->redoActionButton->setFont(QFont("Arial", 14));
	this->redoActionButton->setStyleSheet("background-color :#1e847f; color: #ffffff;");
	undoRedoButtonsLayout->addWidget(this->redoActionButton);

	mainLayout->addLayout(undoRedoButtonsLayout);

	// set the main layout
	this->setLayout(mainLayout);

	this->setWindowTitle("Admin - Events Manager");

	// populate events list widget and connect signals and slots
	this->populateEventsListWidget();
	this->connectSignalsAndSlots();
}

int AdminGUI::getSelectedEventIndex() const
{
	QModelIndexList selectedIndexes = this->eventsListWidget->selectionModel()->selectedIndexes();

	// check the information from the selected event
	if (selectedIndexes.empty()) {
		this->titleLineEdit->clear();
		this->descriptionLineEdit->clear();
		this->dateLineEdit->clear();
		this->timeLineEdit->clear();
		this->numberOfPeopleLineEdit->clear();
		this->linkLineEdit->clear();

		return -1;
	}

	int selectedIndex = selectedIndexes.at(0).row();

	return selectedIndex;
}

void AdminGUI::populateEventsListWidget()
{
	// remove all the events from the current events list widget
	this->eventsListWidget->clear();

	// get all the events from the repository
	std::vector<Event> events = this->controller.get_all_events_from_repository();

	// add the events from the repository to the current events list widget
	for (Event& event : events)
		this->eventsListWidget->addItem(QString::fromStdString(event.get_title()));
}

void AdminGUI::checkAdminEmptyLineEdits()
{
	if (this->titleLineEdit->text().isEmpty() || this->descriptionLineEdit->text().isEmpty() || this->dateLineEdit->text().isEmpty() || this->timeLineEdit->text().isEmpty() || this->numberOfPeopleLineEdit->text().isEmpty() || this->linkLineEdit->text().isEmpty())
		throw ValueError("No empty fields accepted!");
}

void AdminGUI::addEvent()
{
	// get all information about the event from the line edits
	std::string title = this->titleLineEdit->text().toStdString();
	std::string description = this->descriptionLineEdit->text().toStdString();
	std::string date = this->dateLineEdit->text().toStdString();
	std::string time = this->timeLineEdit->text().toStdString();
	std::string stringNumberOfPeople = this->numberOfPeopleLineEdit->text().toStdString();
	int numberOfPeople;
	std::string link = this->linkLineEdit->text().toStdString();

	// validate the event information, add it to the repository and populate the list widget
	try {
		this->checkAdminEmptyLineEdits();

		std::vector<std::string> date_split = split(date, '/');
		std::string day, month, year;
		day = date_split[0], month = date_split[1], year = date_split[2];

		std::vector<std::string> time_split = split(time, ':');
		std::string hour, minutes;
		hour = time_split[0], minutes = time_split[1];

		int day_integer = std::stoi(day), month_integer = std::stoi(month), year_integer = std::stoi(year);
		int hour_integer = std::stoi(hour), minutes_integer = std::stoi(minutes);

		Datetime datetime = Datetime(year_integer, month_integer, day_integer, hour_integer, minutes_integer);

		numberOfPeople = std::stoi(stringNumberOfPeople);

		this->controller.add_event_to_repository(title, description, datetime, numberOfPeople, link);
		this->populateEventsListWidget();
	}

	// raise an error box based on bad user input
	catch (ValueError& validation_error) {
		this->errorBox->setText(validation_error.what());
		this->errorBox->setWindowTitle("Invalid input");
		this->errorBox->exec();
	}

	// raise an error box because the given title already exists in the repository
	catch (RepositoryError& repository_error) {
		this->errorBox->setText(repository_error.what());
		this->errorBox->setWindowTitle("Adding event error");
		this->errorBox->exec();
	}
}

void AdminGUI::removeEvent()
{
	// validate the event title from the line edit and remove the corresponding event from the repository and repopulate the repository list widget
	try {
		std::string title = this->titleLineEdit->text().toStdString();
		this->controller.remove_event_from_repository(title);
		this->populateEventsListWidget();
	}

	// raise an error box based on bad user input
	catch (ValueError& validation_error) {
		this->errorBox->setText(validation_error.what());
		this->errorBox->setWindowTitle("Invalid input");
		this->errorBox->exec();
	}

	// raise an error box because the given title does not exist in the repository
	catch (RepositoryError& repository_error) {
		this->errorBox->setText(repository_error.what());
		this->errorBox->setWindowTitle("Removing event error");
		this->errorBox->exec();
	}
}

void AdminGUI::updateEvent()
{
	// get all information about the event from the line edits
	try {
		this->checkAdminEmptyLineEdits();

		std::string old_title = this->titleLineEdit->text().toStdString();
		std::string new_description = this->descriptionLineEdit->text().toStdString();
		std::string new_date = this->dateLineEdit->text().toStdString();
		std::string new_time = this->timeLineEdit->text().toStdString();
		std::string stringNumberOfPeople = this->numberOfPeopleLineEdit->text().toStdString();

		int numberOfPeople;
		std::string new_link = this->linkLineEdit->text().toStdString();

		std::vector<std::string> date_split = split(new_date, '/');
		std::string day, month, year;
		day = date_split[0], month = date_split[1], year = date_split[2];

		std::vector<std::string> time_split = split(new_time, ':');
		std::string hour, minutes;
		hour = time_split[0], minutes = time_split[1];

		int day_integer = std::stoi(day), month_integer = std::stoi(month), year_integer = std::stoi(year);
		int hour_integer = std::stoi(hour), minutes_integer = std::stoi(minutes);

		Datetime new_datetime = Datetime(year_integer, month_integer, day_integer, hour_integer, minutes_integer);

		numberOfPeople = std::stoi(stringNumberOfPeople);

		this->controller.update_event_from_repository(old_title, new_description, new_datetime, numberOfPeople, new_link);
		this->populateEventsListWidget();
	}

	// raise an error box based on bad user input
	catch (ValueError& validation_error) {
		this->errorBox->setText(validation_error.what());
		this->errorBox->setWindowTitle("Invalid input");
		this->errorBox->exec();
	}

	// raise an error box because the given title does not exist in the repository
	catch (RepositoryError& repository_error) {
		this->errorBox->setText(repository_error.what());
		this->errorBox->setWindowTitle("Updating event error");
		this->errorBox->exec();
	}
}

void AdminGUI::displayChart() {
	this->chartWindow = new QWidget();
	QVBoxLayout* chartLayout = new QVBoxLayout(this->chartWindow);

	this->chartWindow->setStyleSheet("background-color: #ecc19c");
	std::vector<std::string> event_names = this->controller.get_all_event_names_from_repository();

	QChart* chart = new QChart();

	QBarCategoryAxis* axis_x = new QBarCategoryAxis();
	axis_x->setTitleText("Events");

	QStringList categories;
	for (int index = 1; index <= event_names.size(); index++)
		categories << QString::fromStdString(std::to_string(index));

	axis_x->append(categories);
	chart->addAxis(axis_x, Qt::AlignBottom);

	QValueAxis* axis_y = new QValueAxis();
	chart->addAxis(axis_y, Qt::AlignLeft);

	axis_y->setRange(0, 1500);
	axis_y->setTitleText("Number of people");
	axis_y->setLabelFormat("%d");

	for (std::string& event_name : event_names) {
		QBarSeries* series = new QBarSeries();
		QBarSet* set = new QBarSet(QString::fromStdString(event_name));
		int number_of_people = this->controller.get_number_of_people_by_event_name(event_name);
		*set << number_of_people;
		series->append(set);
		chart->addSeries(series);
		series->attachAxis(axis_y);
	}

	chart->setTitle("Number of people per event");
	chart->setAnimationOptions(QChart::SeriesAnimations);

	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignLeft);
	chart->legend()->setBackgroundVisible(true);
	chart->legend()->setBorderColor(QColor::fromRgb(12, 52, 50));
	chart->legend()->setFont(QFont("Arial", 10));

	QChartView* chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	chartLayout->addWidget(chartView);

	this->chartWindow->setWindowTitle("Events Chart");
	this->chartWindow->setWindowIcon(QIcon("icon.jpg"));

	this->chartWindow->resize(840, 720);
	this->chartWindow->show();
}

void AdminGUI::undo()
{
	try {
		this->controller.undo_admin_last_action();
		this->populateEventsListWidget();
	}
	catch (RepositoryError& repository_error) {
		this->errorBox->setText(repository_error.what());
		this->errorBox->setWindowTitle("Undo error");
		this->errorBox->exec();
	}
}

void AdminGUI::redo()
{
	try {
		this->controller.redo_admin_last_action();
		this->populateEventsListWidget();
	}
	catch (RepositoryError& repository_error) {
		this->errorBox->setText(repository_error.what());
		this->errorBox->setWindowTitle("Redo error");
		this->errorBox->exec();
	}
}

void AdminGUI::connectSignalsAndSlots()
{
	// connect the line edits to their corresponding information from the events list widget
	QObject::connect(this->eventsListWidget, &QListWidget::itemSelectionChanged, [this]() {
		int eventIndex = this->getSelectedEventIndex();

		if (eventIndex < 0)
			return;

		Event event = this->controller.get_all_events_from_repository()[eventIndex];
		this->titleLineEdit->setText(QString::fromStdString(event.get_title()));
		this->descriptionLineEdit->setText(QString::fromStdString(event.get_description()));
		this->dateLineEdit->setText(QString::fromStdString(event.get_datetime().date_to_string()));
		this->timeLineEdit->setText(QString::fromStdString(event.get_datetime().time_to_string()));
		this->numberOfPeopleLineEdit->setText(QString::fromStdString(std::to_string(event.get_number_of_people())));
		this->linkLineEdit->setText(QString::fromStdString(event.get_link()));
	});

	// connect the action buttons
	QObject::connect(this->addEventButton, &QPushButton::clicked, this, &AdminGUI::addEvent);
	QObject::connect(this->removeEventButton, &QPushButton::clicked, this, &AdminGUI::removeEvent);
	QObject::connect(this->updateEventButton, &QPushButton::clicked, this, &AdminGUI::updateEvent);

	// connect the chart button
	QObject::connect(this->chartButton, &QPushButton::clicked, this, &AdminGUI::displayChart);

	// connect the undo/redo buttons and shortcuts
	QObject::connect(this->undoActionButton, &QPushButton::clicked, this, &AdminGUI::undo);
	QObject::connect(this->redoActionButton, &QPushButton::clicked, this, &AdminGUI::redo);
	QObject::connect(this->undoActionShortcut, &QShortcut::activated, this, &AdminGUI::undo);
	QObject::connect(this->redoActionShortcut, &QShortcut::activated, this, &AdminGUI::redo);
}

AdminGUI::~AdminGUI()
{
	{}
}

EventsTableModel::EventsTableModel(Controller& _controller) : controller(_controller)
{
}

int EventsTableModel::rowCount(const QModelIndex& parent) const
{
	return this->controller.get_list_length();
}

int EventsTableModel::columnCount(const QModelIndex& parent) const
{
	return 6;
}

QVariant EventsTableModel::data(const QModelIndex& elementIndex, int role) const
{
	int row = elementIndex.row();
	int column = elementIndex.column();

	Event currentEvent = this->controller.get_all_events_from_list()[row];

	if (role == Qt::EditRole || role == Qt::DisplayRole) {
		switch (column) {

		case 0:
			return QString::fromStdString(currentEvent.get_title());

		case 1:
			return QString::fromStdString(currentEvent.get_description());

		case 2:
			return QString::fromStdString(currentEvent.get_datetime().date_to_string());

		case 3:
			return QString::fromStdString(currentEvent.get_datetime().time_to_string());

		case 4:
			return QString::fromStdString(std::to_string(currentEvent.get_number_of_people()));

		case 5:
			return QString::fromStdString(currentEvent.get_link());
			
		default:
			break;
		}
	}

	return QVariant();
}

QVariant EventsTableModel::headerData(int tableSection, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole) {

		if (orientation == Qt::Horizontal) {
			switch (tableSection) {

			case 0:
				return QString("Title");

			case 1:
				return QString("Description");

			case 2:
				return QString("Date");

			case 3:
				return QString("Time");

			case 4:
				return QString("Number of people");

			case 5:
				return QString("Link");

			default:
				break;
			}
		}
	}

	return QVariant();
}

void EventsTableModel::update()
{
	QModelIndex topLeft = this->index(1, 1);
	QModelIndex bottomRight = this->index(this->rowCount(), this->columnCount());

	emit layoutChanged();
	emit dataChanged(topLeft, bottomRight);
}

UserGUI::UserGUI(QWidget* parent, Controller& _controller) : controller(_controller)
{
	this->isRepositoryTypeSet = false;

	this->entryMessageLabel = new QLabel(this);

	this->repositoryTypeMessageLabel = new QLabel(this);
	this->repositoryNameMessageLabel = new QLabel(this);

	this->eventsListTitleLabel = new QLabel(this);
	this->userEventsListTitleLabel = new QLabel(this);

	this->csvDatabaseButton = new QRadioButton("CSV");
	this->htmlDatabaseButton = new QRadioButton("HTML");
	this->sqlDatabaseButton = new QRadioButton("SQL");

	this->repositoryTypeLineEdit = new QLineEdit();

	this->monthFilterLineEdit = new QLineEdit();
	this->titleFilterLineEdit = new QLineEdit();

	this->eventsListWidget = new QListWidget();
	this->userEventsListWidget = new QListWidget();

	this->titleLineEdit = new QLineEdit();
	this->descriptionLineEdit = new QLineEdit();
	this->dateLineEdit = new QLineEdit();
	this->timeLineEdit = new QLineEdit();
	this->numberOfPeopleLineEdit = new QLineEdit();
	this->linkLineEdit = new QLineEdit();

	this->saveListToFileButton = new QPushButton("&USE");

	this->addEventButton = new QPushButton("&ADD");

	this->undoActionButton = new QPushButton("UNDO");
	this->redoActionButton = new QPushButton("REDO");
	this->undoActionShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
	this->redoActionShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this);


	this->openUserListOfEventsFileButton = new QPushButton("&OPEN FILE");

	this->tableViewMessageLabel = new QLabel(this);
	this->openTableViewButton = new QPushButton("&TABLE VIEW");
	this->eventsListTableModel = new EventsTableModel(this->controller);

	this->errorBox = new QMessageBox();
	
	// set gui the parent
	this->setParent(parent);

	// pop on a new window, not on the main gui window
	this->setWindowFlag(Qt::Window);

	this->initializeUserGUI();
}

void UserGUI::initializeUserGUI()
{
	QVBoxLayout* mainLayout = new QVBoxLayout(this);

	this->errorBox->setWindowIcon(QIcon("icon.jpg"));
	this->errorBox->setIcon(QMessageBox::Critical);

	// add text to the top of the layout
	this->entryMessageLabel->setText("USER MODE");
	this->entryMessageLabel->setAlignment(Qt::AlignCenter);
	this->entryMessageLabel->setStyleSheet("color: #000000");

	QFont messageFont("Arial");
	messageFont.setItalic(true);
	messageFont.setBold(true);
	messageFont.setPointSize(20);
	this->entryMessageLabel->setFont(messageFont);

	mainLayout->addWidget(this->entryMessageLabel);

	// add the text for choosing the repository type
	QHBoxLayout* fileRadioButtonsLayout = new QHBoxLayout(this);

	messageFont.setItalic(false);
	messageFont.setBold(false);
	messageFont.setPointSize(10);

	this->repositoryTypeMessageLabel->setText("Choose the type of the file: ");
	this->repositoryTypeMessageLabel->setFont(messageFont);
	fileRadioButtonsLayout->addWidget(this->repositoryTypeMessageLabel);

	// add the radio buttons for file
	fileRadioButtonsLayout->addWidget(this->htmlDatabaseButton);
	fileRadioButtonsLayout->addWidget(this->csvDatabaseButton);
	fileRadioButtonsLayout->addWidget(this->sqlDatabaseButton);

	mainLayout->addLayout(fileRadioButtonsLayout);

	// add the text for choosing the repository name
	QHBoxLayout* fileNameLayout = new QHBoxLayout(this);

	this->repositoryNameMessageLabel->setText("Enter the name of the file: ");
	this->repositoryNameMessageLabel->setFont(messageFont);
	fileNameLayout->addWidget(this->repositoryNameMessageLabel);

	// add the line edit and the button for entering  the name of the file
	this->repositoryTypeLineEdit->setPlaceholderText("my_list");
	fileNameLayout->addWidget(this->repositoryTypeLineEdit);

	this->saveListToFileButton->setFont(QFont("Arial", 10));
	this->saveListToFileButton->setStyleSheet("background-color :#1e847f; color: #ffffff;");
	fileNameLayout->addWidget(saveListToFileButton);

	mainLayout->addLayout(fileNameLayout);

	// add the lists of events
	QVBoxLayout* listsLayout = new QVBoxLayout(this);

	// title of the lists
	messageFont.setItalic(true);
	messageFont.setBold(true);
	messageFont.setPointSize(14);

	this->eventsListTitleLabel->setText("Available Events");
	this->eventsListTitleLabel->setAlignment(Qt::AlignCenter);
	this->eventsListTitleLabel->setStyleSheet("color: #000000");
	this->eventsListTitleLabel->setFont(messageFont);

	listsLayout->addWidget(this->eventsListTitleLabel);

	// the filter line edits
	QFormLayout* monthFilterLineEditsLayout = new QFormLayout;
	this->monthFilterLineEdit->setPlaceholderText("empty...");
	monthFilterLineEditsLayout->addRow("Filter by month ", this->monthFilterLineEdit);
	listsLayout->addItem(monthFilterLineEditsLayout);

	// the list of events
	listsLayout->addWidget(this->eventsListWidget);

	mainLayout->addLayout(listsLayout);

	// add the line edits
	QFormLayout* lineEditsLayout = new QFormLayout;

	lineEditsLayout->addRow("Title", this->titleLineEdit);
	lineEditsLayout->addRow("Description", this->descriptionLineEdit);
	lineEditsLayout->addRow("Date", this->dateLineEdit);
	lineEditsLayout->addRow("Time", this->timeLineEdit);
	lineEditsLayout->addRow("Number of people", this->numberOfPeopleLineEdit);
	lineEditsLayout->addRow("Link", this->linkLineEdit);

	mainLayout->addLayout(lineEditsLayout);

	// add the push buttons for actions
	QHBoxLayout* buttonsLayout = new QHBoxLayout;
	this->addEventButton->setFont(QFont("Arial", 14));
	this->addEventButton->setStyleSheet("background-color :#1e847f; color: #ffffff;");
	buttonsLayout->addWidget(this->addEventButton);

	this->undoActionButton->setFont(QFont("Arial", 14));
	this->undoActionButton->setStyleSheet("background-color :#1e847f; color: #ffffff;");
	buttonsLayout->addWidget(this->undoActionButton);

	this->redoActionButton->setFont(QFont("Arial", 14));
	this->redoActionButton->setStyleSheet("background-color :#1e847f; color: #ffffff;");
	buttonsLayout->addWidget(this->redoActionButton);

	mainLayout->addLayout(buttonsLayout);

	// add the open file button
	this->openUserListOfEventsFileButton->setFont(QFont("Arial", 14));
	this->openUserListOfEventsFileButton->setStyleSheet("background-color :#1e847f; color: #ffffff;");
	mainLayout->addWidget(this->openUserListOfEventsFileButton);

	// add the text for the table view
	this->tableViewMessageLabel->setText("User's current list");
	this->tableViewMessageLabel->setAlignment(Qt::AlignCenter);
	this->tableViewMessageLabel->setStyleSheet("color: #000000");

	messageFont.setItalic(true);
	messageFont.setBold(true);
	messageFont.setPointSize(14);
	this->tableViewMessageLabel->setFont(messageFont);

	mainLayout->addWidget(this->tableViewMessageLabel);

	// add the button for the table view
	this->openTableViewButton->setFont(QFont("Arial", 14));
	this->openTableViewButton->setStyleSheet("background-color :#1e847f; color: #ffffff;");
	mainLayout->addWidget(this->openTableViewButton);
	
	// set the main layout
	this->setLayout(mainLayout);

	this->setWindowTitle("User - Events Manager");

	// populate events list widget, user events list and connect signals and slots
	this->populateEventsListWidget();
	this->connectSignalsAndSlots();
}

int UserGUI::getSelectedEventIndexFromList() const
{
	QModelIndexList selectedIndexes = this->eventsListWidget->selectionModel()->selectedIndexes();

	// check the information from the selected event
	if (selectedIndexes.empty()) {
		this->titleLineEdit->clear();
		this->descriptionLineEdit->clear();
		this->dateLineEdit->clear();
		this->timeLineEdit->clear();
		this->numberOfPeopleLineEdit->clear();
		this->linkLineEdit->clear();

		return -1;
	}

	int selectedIndex = selectedIndexes.at(0).row();

	return selectedIndex;
}

void UserGUI::populateEventsListWidget()
{
	// remove all the events from the current events list widget
	this->eventsListWidget->clear();

	// get the month filter value
	std::string month_string = this->monthFilterLineEdit->text().toStdString();
	int month;

	try {
		month = std::stoi(month_string);
	}

	catch (std::exception) {
		month = 0;
	}

	// get all the events from the repository
	std::vector<Event> events = this->controller.get_all_unadded_events_for_given_month(month);
	if (month_string.empty())
		events = this->controller.get_all_unadded_events();

	// add the events from the repository to the current events list widget
	for (Event& event : events)
		this->eventsListWidget->addItem(QString::fromStdString(event.get_title()));
}

void UserGUI::checkUserEmptyLineEdits()
{
	if (this->titleLineEdit->text().isEmpty() || this->descriptionLineEdit->text().isEmpty() || this->dateLineEdit->text().isEmpty() || this->timeLineEdit->text().isEmpty() || this->numberOfPeopleLineEdit->text().isEmpty() || this->linkLineEdit->text().isEmpty())
		throw ValueError("No empty fields accepted!");
}

void UserGUI::setUserListFile()
{
	std::string fileType;

	if (this->csvDatabaseButton->isChecked()) {
		fileType = ".csv";
	}

	else if (this->sqlDatabaseButton->isChecked()) {
		fileType = ".sql";
	}

	else if (this->htmlDatabaseButton->isChecked()) {
		fileType = ".html";
	}

	else {
		this->errorBox->setText("Please select the type of file you want!");
		this->errorBox->setWindowTitle("File type warning");
		this->errorBox->exec();
		return;
	}

	std::string fileName = this->repositoryTypeLineEdit->text().toStdString();

	if (fileName.empty()) {
		this->errorBox->setText("Please enter the name of file!");
		this->errorBox->setWindowTitle("File name warning");
		this->errorBox->exec();
		return;
	}

	std::string fullNameFile = fileName + fileType;

	this->controller.change_user_repository_type(fullNameFile);
	this->isRepositoryTypeSet = true;

	this->populateEventsListWidget();
	this->eventsListTableModel->update();
}

void UserGUI::addEvent()
{
	if (!this->isRepositoryTypeSet) {
		this->errorBox->setText("Please use a file for your list first!");
		this->errorBox->setWindowTitle("File format warning");
		this->errorBox->exec();
		return;
	}

	// get all information about the event from the line edits
	std::string title = this->titleLineEdit->text().toStdString();
	std::string description = this->descriptionLineEdit->text().toStdString();
	std::string date = this->dateLineEdit->text().toStdString();
	std::string time = this->timeLineEdit->text().toStdString();
	std::string stringNumberOfPeople = this->numberOfPeopleLineEdit->text().toStdString();
	int numberOfPeople;
	std::string link = this->linkLineEdit->text().toStdString();

	// validate the event information, add it to the repository and populate the list widget
	try {
		this->checkUserEmptyLineEdits();

		std::vector<std::string> date_split = split(date, '/');
		std::string day, month, year;
		day = date_split[0], month = date_split[1], year = date_split[2];

		std::vector<std::string> time_split = split(time, ':');
		std::string hour, minutes;
		hour = time_split[0], minutes = time_split[1];

		int day_integer = std::stoi(day), month_integer = std::stoi(month), year_integer = std::stoi(year);
		int hour_integer = std::stoi(hour), minutes_integer = std::stoi(minutes);

		Datetime datetime = Datetime(year_integer, month_integer, day_integer, hour_integer, minutes_integer);

		numberOfPeople = std::stoi(stringNumberOfPeople);

		Event event{ title, description, datetime, numberOfPeople, link };
		this->controller.add_event_to_list(event);

		this->populateEventsListWidget();
		this->eventsListTableModel->update();
	}

	// raise an error box based on bad user input
	catch (ValueError& validation_error) {
		this->errorBox->setText(validation_error.what());
		this->errorBox->setWindowTitle("Invalid input");
		this->errorBox->exec();
	}

	// raise an error box because the given title already exists in the repository
	catch (ListError& repository_error) {
		this->errorBox->setText(repository_error.what());
		this->errorBox->setWindowTitle("Adding event error");
		this->errorBox->exec();
	}

	catch (FileError& file_error) {
		this->errorBox->setText(file_error.what());
		this->errorBox->setWindowTitle("File error");
		this->errorBox->exec();
	}
}

void UserGUI::undo()
{
	try {
		this->controller.undo_user_last_action();
		this->populateEventsListWidget();
		this->eventsListTableModel->update();
	}
	catch (RepositoryError& repository_error) {
		this->errorBox->setText(repository_error.what());
		this->errorBox->setWindowTitle("Undo error");
		this->errorBox->exec();
	}
}

void UserGUI::redo()
{
	try {
		this->controller.redo_user_last_action();
		this->populateEventsListWidget();
		this->eventsListTableModel->update();
	}
	catch (RepositoryError& repository_error) {
		this->errorBox->setText(repository_error.what());
		this->errorBox->setWindowTitle("Redo error");
		this->errorBox->exec();
	}
}

void UserGUI::openFile()
{
	if (!this->isRepositoryTypeSet) {
		this->errorBox->setText("Please use a file for your list first!");
		this->errorBox->setWindowTitle("File format warning");
		this->errorBox->exec();
		return;
	}

	std::string listType = this->controller.get_list_type();

	if (listType.substr(listType.size() - 4) == ".csv" || listType.substr(listType.size() - 5) == ".html") {
		this->controller.open_list_file();
	}

	else {
		this->errorBox->setText("You can only open html/csv list files!");
		this->errorBox->setWindowTitle("File format warning");
		this->errorBox->exec();
	}
}

void UserGUI::createTable()
{
	QWidget* tableWindow = new QWidget();

	tableWindow->setWindowTitle("User List - Table View");
	tableWindow->setWindowIcon(QIcon("icon.jpg"));
	tableWindow->setStyleSheet("background-color: #ecc19c");

	QTableView* tableView = new QTableView();
	tableView->setModel(this->eventsListTableModel);

	tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	tableView->setItemDelegate(new ModelDelegate());
	tableWindow->setMinimumWidth(tableView->width());

	QVBoxLayout* tableViewLayout = new QVBoxLayout{ tableWindow };
	tableViewLayout->addWidget(tableView);

	tableWindow->show();
}

void UserGUI::connectSignalsAndSlots()
{
	// connect the line edits to their corresponding information from the events list widget
	QObject::connect(this->eventsListWidget, &QListWidget::itemSelectionChanged, [this]() {
		int eventIndex = this->getSelectedEventIndexFromList();

		if (eventIndex < 0)
			return;

		std::string month_string = this->monthFilterLineEdit->text().toStdString();
		int month;
		try {
			month = std::stoi(month_string);
		}
		catch (std::exception) {
			month = 0;
		}
		std::vector<Event> events = this->controller.get_all_unadded_events_for_given_month(month);
		if (month_string.empty())
			events = this->controller.get_all_unadded_events();

		Event event = events[eventIndex];
		this->titleLineEdit->setText(QString::fromStdString(event.get_title()));
		this->descriptionLineEdit->setText(QString::fromStdString(event.get_description()));
		this->dateLineEdit->setText(QString::fromStdString(event.get_datetime().date_to_string()));
		this->timeLineEdit->setText(QString::fromStdString(event.get_datetime().time_to_string()));
		this->numberOfPeopleLineEdit->setText(QString::fromStdString(std::to_string(event.get_number_of_people())));
		this->linkLineEdit->setText(QString::fromStdString(event.get_link()));
		event.open();
	});

	// connect the buttons
	QObject::connect(this->addEventButton, &QPushButton::clicked, this, &UserGUI::addEvent);
	QObject::connect(this->saveListToFileButton, &QPushButton::clicked, this, &UserGUI::setUserListFile);
	QObject::connect(this->openUserListOfEventsFileButton, &QPushButton::clicked, this, &UserGUI::openFile);

	// connect filter line edits
	QObject::connect(this->monthFilterLineEdit, &QLineEdit::textChanged, this, &UserGUI::populateEventsListWidget);

	// connect the table view button
	QObject::connect(this->openTableViewButton, &QPushButton::clicked, this, &UserGUI::createTable);

	// connect the undo/redo buttons and shortcuts
	QObject::connect(this->undoActionButton, &QPushButton::clicked, this, &UserGUI::undo);
	QObject::connect(this->redoActionButton, &QPushButton::clicked, this, &UserGUI::redo);
	QObject::connect(this->undoActionShortcut, &QShortcut::activated, this, &UserGUI::undo);
	QObject::connect(this->redoActionShortcut, &QShortcut::activated, this, &UserGUI::redo);
}

UserGUI::~UserGUI()
{
	{}
}
