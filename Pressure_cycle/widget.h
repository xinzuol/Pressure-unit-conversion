#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void Init();
private slots:
    void updateValue();
    void decimalChange(const QString & select);

private:
    Ui::Widget *ui;
    QMap<QString,double> PMap;
    QList<QLineEdit*> LineList;
    int decimalNum;
};
#endif // WIDGET_H
