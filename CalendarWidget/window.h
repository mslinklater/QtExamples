#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QComboBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QCalendarWidget>
#include <QLabel>
#include <QCheckBox>
#include <QDateEdit>

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();

private slots:
    void localeChanged(int index);
    void firstDayChanged(int index);
    void selectionModeChanged(int index);
    void horizontalHeaderChanged(int index);
    void verticalHeaderChanged(int index);
    void selectedDateChanged();
    void minimumDateChanged(const QDate& date);
    void MaximumDateChanged(const QDate& date);
    void weekdayFormatChanged();
    void weekendFormatChanged();
    void reformatHeaders();
    void reformatCalendarPage();

private:
    void createPreviewGroupBox();
    void createGeneralOptionsGroupBox();
    void createDatesGroupBox();
    void createTextFormatsGroupBox();

    QComboBox* createColorComboBox;

    // Preview
    QGroupBox* previewGroupBox;
    QGridLayout* previewLayout;
    QCalendarWidget* calendar;

    // General Options
    QGroupBox* generalOptionsGroupBox;
    QLabel* localeLabel;
    QLabel* firstDayLabel;
    QLabel* selectionModeLabel;
    QLabel* horizontalHeaderLabel;
    QLabel* verticalHeaderLabel;
    QComboBox* localeCombo;
    QComboBox* firstDayCombo;
    QComboBox* selectionModeCombo;
    QCheckBox* gridCheckBox;
    QCheckBox* navigationCheckBox;
    QComboBox* horizontalHeaderCombo;
    QComboBox* verticalHeaderCombo;

    // Dates
    QGroupBox* datesGroupBox;
    QLabel* currentDateLabel;
    QLabel* minimumDateLabel;
    QLabel* maximumDateLabel;
    QDateEdit* currentDateEdit;
    QDateEdit* minimumDateEdit;
    QDateEdit* maximumDateEdit;

    // Text Formats
    QGroupBox* textFormatsGroupBox;
    QLabel* weekdayColorLabel;
    QLabel* weekendColorLabel;
    QLabel* headerTextFormatLabel;
    QComboBox* weekdayColorCombo;
    QComboBox* weekendColorCombo;
    QComboBox* headerTextFormatCombo;

    QCheckBox* firstFridayCheckBox;
    QCheckBox* mayFirstCheckBox;
};

#endif // WINDOW_H
