#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();

private slots:
    void localeChanged(int index);
    void firstDayChanged(int index);
};

#endif // WINDOW_H
