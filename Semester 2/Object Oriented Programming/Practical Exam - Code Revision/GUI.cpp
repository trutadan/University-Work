#include "GUI.h"

GUI::GUI(Service& service, Member member, QWidget* parent) : service(service), member(member), QWidget(parent)
{
	this->service.addObserver(this);
	this->initGUI();
	this->connectSignalsAndSlots();
	this->update();
}

void GUI::initGUI()
{
	this->setWindowTitle(this->member.getName().c_str());

	this->mainLayout = new QVBoxLayout(this);
	
	this->allFilesListWidget = new QListWidget();
	this->mainLayout->addWidget(this->allFilesListWidget);

	this->revisedLabel = new QLineEdit();
	this->revisedLabel->setReadOnly(true);
	this->mainLayout->addWidget(this->revisedLabel);
	
	this->unrevisedLabel = new QLineEdit();
	this->unrevisedLabel->setReadOnly(true);
	this->mainLayout->addWidget(this->unrevisedLabel);

	QGridLayout* addFileLayout = new QGridLayout(this);
	this->addLineEdit = new QLineEdit();
	addFileLayout->addWidget(this->addLineEdit, 0, 0);
	this->addButton = new QPushButton("&ADD");
	addFileLayout->addWidget(this->addButton, 0, 1);
	this->mainLayout->addLayout(addFileLayout);

	this->reviseButton = new QPushButton("&REVISE");
	this->mainLayout->addWidget(this->reviseButton);

	this->setLayout(mainLayout);
}

void GUI::connectSignalsAndSlots()
{
	QObject::connect(this->addButton, &QPushButton::clicked, this, &GUI::addSourceFile);
	QObject::connect(this->allFilesListWidget, &QListWidget::clicked, this, &GUI::checkIfReviseAvailable);
	QObject::connect(this->reviseButton, &QPushButton::clicked, this, &GUI::revise);
}

void GUI::populateAllFilesList()
{
	std::vector<SourceFile> sortedSourceFiles = this->service.getSortedSourceFiles();

	QFont font;
	font.setBold(true);

	this->allFilesListWidget->clear();
	for (SourceFile sourceFIle : sortedSourceFiles) {
		QListWidgetItem* item = new QListWidgetItem();
		item->setText(QString::fromStdString(sourceFIle.toString()));
		if (sourceFIle.getStatus() == "not_revised")
			item->setFont(font);
		else
			item->setBackground(Qt::green);

		this->allFilesListWidget->addItem(item);
	}
}

void GUI::populateLabels()
{
	this->unrevisedLabel->clear();
	this->revisedLabel->clear();
	this->revisedLabel->setText(QString::fromStdString("Number of revised files: " + std::to_string(this->member.getNumberOfRevisedFiles())));
	this->unrevisedLabel->setText(QString::fromStdString("Number of unrevised files: " + std::to_string(this->member.getTotalNumberOfFilesToRevise() - this->member.getNumberOfRevisedFiles())));
}

void GUI::addSourceFile()
{
	std::string fileName = this->addLineEdit->text().toStdString();

	std::string name = this->member.getName();
	SourceFile f(fileName, "not_revised", name, "-");
	
	try {
		this->service.addNewSourceFile(f);
	}
	catch (std::exception & error) {
		QMessageBox::critical(this, "Error", "error");
	}
}

int GUI::getSelectedIndex()
{
	auto selectedIndexes = this->allFilesListWidget->selectionModel()->selectedIndexes();

	if (selectedIndexes.isEmpty())
		return -1;

	int selectedIndex = selectedIndexes.at(0).row();

	return selectedIndex;
}

void GUI::checkIfReviseAvailable()
{
	int index = this->getSelectedIndex();

	std::string status = this->service.getSortedSourceFiles()[index].getStatus();
	std::string creator = this->service.getSortedSourceFiles()[index].getCreator();

	if (status == "not_revised" && creator != this->member.getName())
		this->reviseButton->setEnabled(true);
	else
		this->reviseButton->setEnabled(false);
}
	
void GUI::revise()
{
	int index = this->getSelectedIndex();

	SourceFile f = this->service.getSortedSourceFiles()[index];

	std::string name = this->member.getName();
	this->service.setSourceFileRevised(f, name);

	this->service.setOneMoreFileRevised(this->member);

	this->reviseButton->setDisabled(true);

	this->member = this->service.getMemberByName(name);
	if (this->member.getNumberOfRevisedFiles() == this->member.getTotalNumberOfFilesToRevise()) {
		std::string memberName = this->member.getName();
		QMessageBox::information(this, QString::fromStdString("Congratulations " + memberName + "!"), "Congratulations! You've revised all your files!");
	}

	this->update();
}

void GUI::update()
{
	this->populateAllFilesList();
	this->populateLabels();
}
