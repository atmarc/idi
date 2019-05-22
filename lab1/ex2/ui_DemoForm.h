/********************************************************************************
** Form generated from reading UI file 'DemoForm.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEMOFORM_H
#define UI_DEMOFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(385, 404);
        verticalLayout = new QVBoxLayout(Form);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, -1, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        radioButton_2 = new QRadioButton(Form);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setMouseTracking(true);

        verticalLayout_3->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(Form);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));

        verticalLayout_3->addWidget(radioButton_3);

        radioButton = new QRadioButton(Form);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        verticalLayout_3->addWidget(radioButton);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(Form);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QLatin1String("color:rgb(255, 255, 255);\n"
"background-color:rgb(255, 0, 0);"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(Form);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QLatin1String("color:rgb(255, 255, 255);\n"
"background-color:rgb(0, 0, 255);"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(Form);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(0, 0));
        label_3->setStyleSheet(QLatin1String("color:rgb(255, 255, 255);\n"
"background-color:rgb(0, 255, 0);"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_3);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalSpacer = new QSpacerItem(370, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton = new QPushButton(Form);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(Form);
        QObject::connect(radioButton_2, SIGNAL(clicked()), label, SLOT(show()));
        QObject::connect(radioButton_3, SIGNAL(clicked()), label_2, SLOT(show()));
        QObject::connect(radioButton, SIGNAL(clicked()), label_3, SLOT(show()));
        QObject::connect(radioButton_2, SIGNAL(clicked()), label_2, SLOT(hide()));
        QObject::connect(radioButton_2, SIGNAL(clicked()), label_3, SLOT(hide()));
        QObject::connect(radioButton_3, SIGNAL(clicked()), label, SLOT(hide()));
        QObject::connect(radioButton_3, SIGNAL(clicked()), label_3, SLOT(hide()));
        QObject::connect(radioButton, SIGNAL(clicked()), label_2, SLOT(hide()));
        QObject::connect(radioButton, SIGNAL(clicked()), label, SLOT(hide()));
        QObject::connect(pushButton, SIGNAL(clicked()), Form, SLOT(close()));

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
        radioButton_2->setText(QApplication::translate("Form", "Verme&ll", 0));
        radioButton_3->setText(QApplication::translate("Form", "Bla&u", 0));
        radioButton->setText(QApplication::translate("Form", "Verd", 0));
        label->setText(QApplication::translate("Form", "VERMELL", 0));
        label_2->setText(QApplication::translate("Form", "BLAU", 0));
        label_3->setText(QApplication::translate("Form", "VERD", 0));
        pushButton->setText(QApplication::translate("Form", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEMOFORM_H
