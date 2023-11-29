#include "widget.h"
#include "ui_widget.h"
#include <QDoubleValidator>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    Init ();
    this->setWindowTitle ("压力单位转换工具");
    decimalNum=2;

}

Widget::~Widget()
{
    delete ui;
}

void Widget::Init()
{
//    添加信息
        PMap.insert("帕斯卡 (Pascal)", 1.0);
        PMap.insert("千帕 (kPa)", 0.001);
        PMap.insert("气压 (atm)", 0.0000098692);
        PMap.insert("标准大气压 (atm)", 0.00001);
        PMap.insert("毫米汞柱 (mmHg)", 0.00750062);
        PMap.insert("英寸汞柱 (inHg)", 0.0002953);
        PMap.insert("条 (bar)", 0.00001);
        PMap.insert("兆帕 (MPa)", 0.00001);
        PMap.insert("公斤力/平方厘米 (kgf/cm²)", 0.0001);
        PMap.insert("公斤力/平方米 (kgf/m²)", 0.001);
        PMap.insert("磅力/平方英寸 (psi)", 0.00001);
//     添加控件
        QVBoxLayout* vlayout = new QVBoxLayout(this);
        for(const auto &unit: PMap.keys ())
        {
            QHBoxLayout* hlayout = new QHBoxLayout(this);
            QLineEdit *line = new QLineEdit(this);
            line->setValidator (new QDoubleValidator(this));
            line->setToolTip (unit);
            hlayout->addWidget (line);
            LineList.append (line);
            QLabel *label = new QLabel(unit ,this);
            hlayout->addWidget (label);
            vlayout->addLayout (hlayout);
        }
//      保留小数变化
        QHBoxLayout* hlayout = new QHBoxLayout(this);
        QLabel *decimalLabel = new QLabel("小数点位数:",this);
        QComboBox *decimal= new QComboBox(this);
        decimal->addItems (QStringList()<<"1"<<"2"<<"3"<<"4"<<"6"<<"7"<<"8"<<"9"<<"10");
        decimal->setCurrentText ("2");
        hlayout->addWidget (decimalLabel);
        hlayout->addWidget (decimal);
        vlayout->addLayout (hlayout);
//      添加信号槽
        for(QLineEdit* lineEdit:LineList)
        {
            connect (lineEdit,&QLineEdit::textEdited,this,&Widget::updateValue);
        }
        connect (decimal,&QComboBox::currentTextChanged,this,&Widget::decimalChange);
}
//槽函数
void Widget::updateValue()
{
        QLineEdit* curentLine = ((QLineEdit*)sender ());
        double inputNum = curentLine->text ().toDouble ();
        QString currentUnit =curentLine->toolTip ();
        for(QLineEdit* lineEdit:LineList)
        {
            if(lineEdit==curentLine)
                continue;
            lineEdit->setText (QString::number (inputNum*PMap.value (currentUnit)/PMap.value (lineEdit->toolTip ()),'f',decimalNum));
        }
}

void Widget::decimalChange(const QString &select)
{
        decimalNum=select.toInt ();
}

