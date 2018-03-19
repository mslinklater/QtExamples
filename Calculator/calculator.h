#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include "button.h"

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = 0);
    ~Calculator();

private slots:
    void digitClicked();
    void unaryOperatorClicked();
    void additiveOperatorClicked();
    void multiplicativeOperatorClicked();
    void equalClicked();
    void pointClicked();
    void changeSignClicked();
    void backspaceClicked();
    void clear();
    void clearAll();
    void clearMemory();
    void setMemory();
    void addToMemory();
    void readMemory();

private:
    Button* createButton(const QString& text, const char* member);
    void abortOperation();
    bool calculate(double rightOperand, const QString& pendingOperator);

    double sumInMemory;
    double sumSoFar;
    double factorSoFar;
    QString pendingAdditiveOperator;
    QString pendingMultiplicativeOperator;
    bool waitingForOperand;

    QLineEdit* display;
    enum { NumDigitButtons = 10 };
    Button* digitButtons[NumDigitButtons];
};

#endif // CALCULATOR_H
