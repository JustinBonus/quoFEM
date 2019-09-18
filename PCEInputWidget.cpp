
#include "PCEInputWidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QJsonObject>

PCEInputWidget::PCEInputWidget(QWidget *parent) : UQ_MethodInputWidget(parent)
{
    layout = new QGridLayout();

    // specify method to generate training data
    layout->addWidget(new QLabel("Method for Data Generation"), 0, 0);
    dataMethod = new QComboBox();
    dataMethod->addItem("LHS");
    dataMethod->addItem("Monte Carlo");
    dataMethod->addItem("Sparse Grid Quadrature");
    connect(dataMethod,SIGNAL(currentIndexChanged(int)),this,SLOT(dataMethodChanged(int)));
    layout->addWidget(dataMethod, 0, 1);

    // create layout label and entry for # samples
    numSamples = new QLineEdit();
    numSamples->setText(tr("10"));
    numSamples->setValidator(new QIntValidator);
    numSamples->setToolTip("Specify the number of samples");
    layout->addWidget(new QLabel("# Samples"), 1, 0);
    layout->addWidget(numSamples, 1, 1);


    // create label and entry for seed to layout
    srand(time(NULL));
    int randomNumber = rand() % 1000 + 1;
    randomSeed = new QLineEdit();
    randomSeed->setText(QString::number(randomNumber));
    randomSeed->setValidator(new QIntValidator);
    randomSeed->setToolTip("Set the seed");
    layout->addWidget(new QLabel("Seed"), 2, 0);
    layout->addWidget(randomSeed, 2, 1);

    // create layout label and entry for level
    level = new QLineEdit();
    level->setText(tr("5"));
    level->setValidator(new QIntValidator);
    level->setToolTip("Specify the quadrature levels");
    layout->addWidget(new QLabel("Quadrature Level"), 3, 0);
    layout->addWidget(level, 3, 1);

    layout->itemAtPosition(3,0)->widget()->hide();
    layout->itemAtPosition(3,1)->widget()->hide();

    layout->setRowStretch(4, 1);
    layout->setColumnStretch(2, 1);

    this->setLayout(layout);
}


bool PCEInputWidget::outputToJSON(QJsonObject &jsonObject)
{
    bool result = true;
    jsonObject["samples"]=numSamples->text().toInt();
    jsonObject["seed"]=randomSeed->text().toDouble();
    jsonObject["dataMethod"]=dataMethod->currentText();
    jsonObject["level"]=level->text().toInt();
    return result;
}

bool PCEInputWidget::inputFromJSON(QJsonObject &jsonObject)
{
}

int PCEInputWidget::getNumberTasks()
{
}

void PCEInputWidget::dataMethodChanged(int method) {

    if (method == 0 || method == 1) {
        layout->itemAtPosition(1,0)->widget()->show();
        layout->itemAtPosition(1,1)->widget()->show();
        layout->itemAtPosition(2,0)->widget()->show();
        layout->itemAtPosition(2,1)->widget()->show();
        layout->itemAtPosition(3,0)->widget()->hide();
        layout->itemAtPosition(3,1)->widget()->hide();
    } else {
        layout->itemAtPosition(1,0)->widget()->hide();
        layout->itemAtPosition(1,1)->widget()->hide();
        layout->itemAtPosition(2,0)->widget()->hide();
        layout->itemAtPosition(2,1)->widget()->hide();
        layout->itemAtPosition(3,0)->widget()->show();
        layout->itemAtPosition(3,1)->widget()->show();
    }
}

