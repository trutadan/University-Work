#include "GUI.h"
#include <QMessageBox>

GUI::GUI(Controller& controller, QWidget* parent)
{
	this->controller = controller;
	this->controller.readFromFile("equations.txt");

	initGUI();
	populateList();
	connectSignalsAndSlots();
}

void GUI::initGUI()
{
	this->mainLayout = new QVBoxLayout(this);

	this->equationsWidgetList = new QListWidget();
	this->mainLayout->addWidget(this->equationsWidgetList);

	this->aLine = new QLineEdit();
	this->bLine = new QLineEdit();
	this->cLine = new QLineEdit();
	this->addButton = new QPushButton("Add");

	QHBoxLayout* addSection = new QHBoxLayout(this);
	addSection->addWidget(this->aLine);
	addSection->addWidget(this->bLine);
	addSection->addWidget(this->cLine);
	addSection->addWidget(this->addButton);

	this->mainLayout->addLayout(addSection);

	this->computeButton = new QPushButton("Compute solutions");
	this->mainLayout->addWidget(this->computeButton);

	this->resultLine = new QLineEdit();
	this->resultLine->setReadOnly(true);

	this->mainLayout->addWidget(resultLine);

	this->setLayout(this->mainLayout);

}

void GUI::addEquation()
{
	std::string aString = this->aLine->text().toStdString();
	std::string bString = this->bLine->text().toStdString();
	std::string cString = this->cLine->text().toStdString();

	try {
		double a, b, c;
		a = std::stod(aString);
		b = std::stod(bString);
		c = std::stod(cString);

		this->controller.addEquation(a, b, c);
	}

	catch (std::exception& e) {
		QMessageBox* error = new QMessageBox();
		error->setText(e.what());
		error->show();
	}

	this->populateList();
}

void GUI::populateList()
{
	this->equationsWidgetList->clear();
	for (Equation equation : this->controller.getAll()) {
		QListWidgetItem* item = new QListWidgetItem();
		item->setText(QString::fromStdString(equation.toString()));
		if (equation.isReal())
			item->setBackground(Qt::green);
		this->equationsWidgetList->addItem(item);
	}
}

void GUI::connectSignalsAndSlots()
{
	QObject::connect(this->addButton, &QPushButton::clicked, this, &GUI::addEquation);
	QObject::connect(this->computeButton, &QPushButton::clicked, this, &GUI::computeSolution);
}

void GUI::computeSolution()
{
	QModelIndexList positionL = this->equationsWidgetList->selectionModel()->selectedIndexes();
	int position = positionL.at(0).row();
	std::string result;
	result = this->controller.getSolutionOfEquation(this->controller.getAll()[position].getA(), this->controller.getAll()[position].getB(), this->controller.getAll()[position].getC());
	this->resultLine->setText(QString::fromStdString(result));
}

GUI::~GUI()
{
}
