#include "calculator.h"
#include <QGridLayout>
#include <math.h>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    sumInMemory = 0.0;
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    waitingForOperand = true;

    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);

    for(int i=0 ; i<NumDigitButtons ; ++i)
    {
        QString buttonString = QString::number(i);
        digitButtons[i] = createButton(buttonString, SLOT(digitClicked()));
    }
    Button* pointButton = createButton(tr("."), SLOT(pointSignClicked()));
    Button* changeSignButton = createButton(tr("\302\261"), SLOT(backspaceClicked()));

    Button* backspaceButton = createButton(tr("Backspace"), SLOT(backspaceClicked()));
    Button* clearButton = createButton(tr("Clear"), SLOT(clear()));
    Button* clearAllButton = createButton(tr("Clear All"), SLOT(clearAll()));

    Button* clearMemoryButton = createButton(tr("MC"), SLOT(clearMemory()));
    Button* readMemoryButton = createButton(tr("MR"), SLOT(readMemory()));
    Button* setMemoryButton = createButton(tr("MS"), SLOT(setMemory()));
    Button* addToMemoryButton = createButton(tr("M+"), SLOT(addToMemory()));

    Button* divisionButton = createButton(tr("\303\267"), SLOT(multiplicativeOperatorClicked()));
    Button* timesButton = createButton(tr("\303\227"), SLOT(multiplicativeOperatorClicked()));
    Button* minusButton = createButton(tr("-"), SLOT(additiveOperatorClocked()));
    Button* plusButton = createButton(tr("+"), SLOT(additiveOperatorClocked()));

    Button* squareRootButton = createButton(tr("Sqrt"), SLOT(unaryOperatorClicked()));
    Button* powerButton = createButton(tr("x\302\262"), SLOT(unaryOperatorClicked()));
    Button* reciprocalButton = createButton(tr("1/x"), SLOT(unaryOperatorClicked()));
    Button* equalButton = createButton(tr("="), SLOT(equalClicked()));

    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(display, 0, 0, 1, 6);
    mainLayout->addWidget(backspaceButton, 1, 0, 1, 2);
    mainLayout->addWidget(clearButton, 1, 2, 1, 2);
    mainLayout->addWidget(clearAllButton, 1, 4, 1, 2);

    mainLayout->addWidget(clearMemoryButton, 2, 0);
    mainLayout->addWidget(readMemoryButton, 3, 0);
    mainLayout->addWidget(setMemoryButton, 4, 0);
    mainLayout->addWidget(addToMemoryButton, 5, 0);

    for(int i=0; i<NumDigitButtons ; ++i)
    {
        int row = ((9-i)/3)+2;
        int column = ((i-1)%3)+1;
        mainLayout->addWidget(digitButtons[i], row, column);
    }

    mainLayout->addWidget(digitButtons[0], 5, 1);
    mainLayout->addWidget(pointButton, 5, 2);
    mainLayout->addWidget(changeSignButton, 5, 3);

    mainLayout->addWidget(divisionButton, 2, 4);
    mainLayout->addWidget(timesButton, 3, 4);
    mainLayout->addWidget(minusButton, 4, 4);
    mainLayout->addWidget(plusButton, 5, 4);

    mainLayout->addWidget(squareRootButton, 2, 5);
    mainLayout->addWidget(powerButton, 3, 5);
    mainLayout->addWidget(reciprocalButton, 4, 5);
    mainLayout->addWidget(equalButton, 5, 5);

    setLayout(mainLayout);

    setWindowTitle(tr("Calculator"));
}

Calculator::~Calculator()
{

}

void Calculator::digitClicked()
{
    Button* clickedButton = qobject_cast<Button *>(sender());
    QString digitString = clickedButton->text();
    digitString.remove(QChar('&'), Qt::CaseInsensitive);
    int digitValue = digitString.toInt();
    if(display->text() == "0" && digitValue == 0)
        return;
    if(waitingForOperand)
    {
        display->clear();
        waitingForOperand = false;
    }
    display->setText(display->text() + QString::number(digitValue));
}

void Calculator::unaryOperatorClicked()
{
    Button* clickedButton = qobject_cast<Button*>(sender());
    QString clickedOperator = clickedButton->text().remove(QChar('&'), Qt::CaseInsensitive);
    double operand = display->text().toDouble();
    double result = 0.0;

    if(clickedOperator == tr("Sqrt"))
    {
        if(operand < 0.0)
        {
            abortOperation();
            return;
        }
        result = std::sqrt(operand);
    }
    else if (clickedOperator == tr("x\302\262"))
    {
        result = std::pow(operand, 2.0);
    }
    else if (clickedOperator == tr("1/x"))
    {
        if(operand == 0.0)
        {
            abortOperation();
            return;
        }
        result = 1.0 / operand;
    }
    display->setText(QString::number(result));
    waitingForOperand = true;
}

void Calculator::additiveOperatorClicked()
{
    Button* clickedButton = qobject_cast<Button*>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    if(!pendingMultiplicativeOperator.isEmpty())
    {
        if(!calculate(operand, pendingMultiplicativeOperator))
        {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }
    if(!pendingAdditiveOperator.isEmpty())
    {
        if(!calculate(operand, pendingAdditiveOperator))
        {
            abortOperation();
            return;
        }
        display->setText(QString::number(sumSoFar));
    }
    else
    {
        sumSoFar = operand;
    }
    pendingAdditiveOperator = clickedOperator;
    waitingForOperand = true;
}

void Calculator::multiplicativeOperatorClicked()
{
    Button* clickedButton = qobject_cast<Button*>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();


}

void Calculator::equalClicked()
{

}

void Calculator::pointClicked()
{

}

void Calculator::changeSignClicked()
{

}

void Calculator::backspaceClicked()
{

}

void Calculator::clear()
{

}

void Calculator::clearAll()
{

}

void Calculator::clearMemory()
{

}

void Calculator::readMemory()
{

}

void Calculator::setMemory()
{

}

void Calculator::addToMemory()
{

}

Button* Calculator::createButton(const QString &text, const char *member)
{
    Button* button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

void Calculator::abortOperation()
{

}

bool Calculator::calculate(double rightOperand, const QString &pendingOperator)
{
    return true;
}
