/********************************************************************************
** Form generated from reading UI file 'optionsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONSDIALOG_H
#define UI_OPTIONSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OptionsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox_6;
    QSpinBox *spinBox;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox_7;
    QLineEdit *lineEdit;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *comboBox;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QWidget *widget;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_3;
    QWidget *widget_2;
    QPushButton *pushButton_2;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_4;
    QWidget *widget_3;
    QPushButton *pushButton_3;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_5;
    QWidget *widget_4;
    QPushButton *pushButton_4;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_6;
    QWidget *widget_5;
    QPushButton *pushButton_5;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_7;
    QWidget *widget_6;
    QPushButton *pushButton_6;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    QWidget *widget_7;
    QPushButton *pushButton_7;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_9;
    QWidget *widget_8;
    QPushButton *pushButton_8;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_10;
    QWidget *widget_9;
    QPushButton *pushButton_9;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_11;
    QWidget *widget_10;
    QPushButton *pushButton_10;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_12;
    QWidget *widget_11;
    QPushButton *pushButton_11;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *OptionsDialog)
    {
        if (OptionsDialog->objectName().isEmpty())
            OptionsDialog->setObjectName(QStringLiteral("OptionsDialog"));
        OptionsDialog->setWindowModality(Qt::NonModal);
        OptionsDialog->resize(414, 428);
        OptionsDialog->setAutoFillBackground(false);
        OptionsDialog->setSizeGripEnabled(false);
        verticalLayout = new QVBoxLayout(OptionsDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(OptionsDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(0, 321));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_3 = new QVBoxLayout(tab);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        checkBox_6 = new QCheckBox(tab);
        checkBox_6->setObjectName(QStringLiteral("checkBox_6"));

        horizontalLayout->addWidget(checkBox_6);

        spinBox = new QSpinBox(tab);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setEnabled(false);
        spinBox->setMinimum(1);
        spinBox->setMaximum(60);
        spinBox->setValue(5);

        horizontalLayout->addWidget(spinBox);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);

        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        checkBox_7 = new QCheckBox(tab);
        checkBox_7->setObjectName(QStringLiteral("checkBox_7"));

        horizontalLayout_2->addWidget(checkBox_7);

        lineEdit = new QLineEdit(tab);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setEnabled(false);

        horizontalLayout_2->addWidget(lineEdit);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 1);

        verticalLayout_3->addLayout(horizontalLayout_2);

        checkBox_2 = new QCheckBox(tab);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        verticalLayout_3->addWidget(checkBox_2);

        checkBox_4 = new QCheckBox(tab);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));

        verticalLayout_3->addWidget(checkBox_4);

        checkBox_5 = new QCheckBox(tab);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));

        verticalLayout_3->addWidget(checkBox_5);

        checkBox_9 = new QCheckBox(tab);
        checkBox_9->setObjectName(QStringLiteral("checkBox_9"));

        verticalLayout_3->addWidget(checkBox_9);

        checkBox_8 = new QCheckBox(tab);
        checkBox_8->setObjectName(QStringLiteral("checkBox_8"));

        verticalLayout_3->addWidget(checkBox_8);

        checkBox_3 = new QCheckBox(tab);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        verticalLayout_3->addWidget(checkBox_3);

        checkBox = new QCheckBox(tab);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        verticalLayout_3->addWidget(checkBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        comboBox = new QComboBox(tab);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_3->addWidget(comboBox);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 1);

        verticalLayout_3->addLayout(horizontalLayout_3);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_2 = new QVBoxLayout(tab_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_5->addWidget(label_2);

        widget = new QWidget(tab_2);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setAutoFillBackground(true);

        horizontalLayout_5->addWidget(widget);

        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_5->addWidget(pushButton);

        horizontalLayout_5->setStretch(0, 4);
        horizontalLayout_5->setStretch(1, 1);
        horizontalLayout_5->setStretch(2, 2);

        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_14->addWidget(label_3);

        widget_2 = new QWidget(tab_2);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setAutoFillBackground(true);

        horizontalLayout_14->addWidget(widget_2);

        pushButton_2 = new QPushButton(tab_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_14->addWidget(pushButton_2);

        horizontalLayout_14->setStretch(0, 4);
        horizontalLayout_14->setStretch(1, 1);
        horizontalLayout_14->setStretch(2, 2);

        verticalLayout_4->addLayout(horizontalLayout_14);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_13->addWidget(label_4);

        widget_3 = new QWidget(tab_2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setAutoFillBackground(true);

        horizontalLayout_13->addWidget(widget_3);

        pushButton_3 = new QPushButton(tab_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_13->addWidget(pushButton_3);

        horizontalLayout_13->setStretch(0, 4);
        horizontalLayout_13->setStretch(1, 1);
        horizontalLayout_13->setStretch(2, 2);

        verticalLayout_4->addLayout(horizontalLayout_13);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_12->addWidget(label_5);

        widget_4 = new QWidget(tab_2);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setAutoFillBackground(true);

        horizontalLayout_12->addWidget(widget_4);

        pushButton_4 = new QPushButton(tab_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_12->addWidget(pushButton_4);

        horizontalLayout_12->setStretch(0, 4);
        horizontalLayout_12->setStretch(1, 1);
        horizontalLayout_12->setStretch(2, 2);

        verticalLayout_4->addLayout(horizontalLayout_12);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_11->addWidget(label_6);

        widget_5 = new QWidget(tab_2);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        widget_5->setAutoFillBackground(true);

        horizontalLayout_11->addWidget(widget_5);

        pushButton_5 = new QPushButton(tab_2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        horizontalLayout_11->addWidget(pushButton_5);

        horizontalLayout_11->setStretch(0, 4);
        horizontalLayout_11->setStretch(1, 1);
        horizontalLayout_11->setStretch(2, 2);

        verticalLayout_4->addLayout(horizontalLayout_11);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_10->addWidget(label_7);

        widget_6 = new QWidget(tab_2);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        widget_6->setAutoFillBackground(true);

        horizontalLayout_10->addWidget(widget_6);

        pushButton_6 = new QPushButton(tab_2);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        horizontalLayout_10->addWidget(pushButton_6);

        horizontalLayout_10->setStretch(0, 4);
        horizontalLayout_10->setStretch(1, 1);
        horizontalLayout_10->setStretch(2, 2);

        verticalLayout_4->addLayout(horizontalLayout_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_8 = new QLabel(tab_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_9->addWidget(label_8);

        widget_7 = new QWidget(tab_2);
        widget_7->setObjectName(QStringLiteral("widget_7"));
        widget_7->setAutoFillBackground(true);

        horizontalLayout_9->addWidget(widget_7);

        pushButton_7 = new QPushButton(tab_2);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        horizontalLayout_9->addWidget(pushButton_7);

        horizontalLayout_9->setStretch(0, 4);
        horizontalLayout_9->setStretch(1, 1);
        horizontalLayout_9->setStretch(2, 2);

        verticalLayout_4->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_9 = new QLabel(tab_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_8->addWidget(label_9);

        widget_8 = new QWidget(tab_2);
        widget_8->setObjectName(QStringLiteral("widget_8"));
        widget_8->setAutoFillBackground(true);

        horizontalLayout_8->addWidget(widget_8);

        pushButton_8 = new QPushButton(tab_2);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        horizontalLayout_8->addWidget(pushButton_8);

        horizontalLayout_8->setStretch(0, 4);
        horizontalLayout_8->setStretch(1, 1);
        horizontalLayout_8->setStretch(2, 2);

        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_10 = new QLabel(tab_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_7->addWidget(label_10);

        widget_9 = new QWidget(tab_2);
        widget_9->setObjectName(QStringLiteral("widget_9"));
        widget_9->setAutoFillBackground(true);

        horizontalLayout_7->addWidget(widget_9);

        pushButton_9 = new QPushButton(tab_2);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));

        horizontalLayout_7->addWidget(pushButton_9);

        horizontalLayout_7->setStretch(0, 4);
        horizontalLayout_7->setStretch(1, 1);
        horizontalLayout_7->setStretch(2, 2);

        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_11 = new QLabel(tab_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_6->addWidget(label_11);

        widget_10 = new QWidget(tab_2);
        widget_10->setObjectName(QStringLiteral("widget_10"));
        widget_10->setAutoFillBackground(true);

        horizontalLayout_6->addWidget(widget_10);

        pushButton_10 = new QPushButton(tab_2);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));

        horizontalLayout_6->addWidget(pushButton_10);

        horizontalLayout_6->setStretch(0, 4);
        horizontalLayout_6->setStretch(1, 1);
        horizontalLayout_6->setStretch(2, 2);

        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_12 = new QLabel(tab_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_4->addWidget(label_12);

        widget_11 = new QWidget(tab_2);
        widget_11->setObjectName(QStringLiteral("widget_11"));
        widget_11->setAutoFillBackground(true);

        horizontalLayout_4->addWidget(widget_11);

        pushButton_11 = new QPushButton(tab_2);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));

        horizontalLayout_4->addWidget(pushButton_11);

        horizontalLayout_4->setStretch(0, 4);
        horizontalLayout_4->setStretch(1, 1);
        horizontalLayout_4->setStretch(2, 2);

        verticalLayout_4->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(verticalLayout_4);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(OptionsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Cancel|QDialogButtonBox::Ok|QDialogButtonBox::Reset);
        buttonBox->setCenterButtons(false);

        verticalLayout->addWidget(buttonBox);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(comboBox);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(tabWidget, checkBox_6);
        QWidget::setTabOrder(checkBox_6, spinBox);
        QWidget::setTabOrder(spinBox, checkBox_7);
        QWidget::setTabOrder(checkBox_7, lineEdit);
        QWidget::setTabOrder(lineEdit, checkBox_2);
        QWidget::setTabOrder(checkBox_2, checkBox_4);
        QWidget::setTabOrder(checkBox_4, checkBox_5);
        QWidget::setTabOrder(checkBox_5, checkBox_9);
        QWidget::setTabOrder(checkBox_9, checkBox_8);
        QWidget::setTabOrder(checkBox_8, checkBox_3);
        QWidget::setTabOrder(checkBox_3, checkBox);
        QWidget::setTabOrder(checkBox, comboBox);
        QWidget::setTabOrder(comboBox, buttonBox);

        retranslateUi(OptionsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), OptionsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), OptionsDialog, SLOT(reject()));
        QObject::connect(checkBox_6, SIGNAL(toggled(bool)), spinBox, SLOT(setEnabled(bool)));
        QObject::connect(checkBox_7, SIGNAL(toggled(bool)), lineEdit, SLOT(setEnabled(bool)));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(OptionsDialog);
    } // setupUi

    void retranslateUi(QDialog *OptionsDialog)
    {
        OptionsDialog->setWindowTitle(QApplication::translate("OptionsDialog", "Settings", 0));
        checkBox_6->setText(QApplication::translate("OptionsDialog", "CheckBox", 0));
        checkBox_7->setText(QApplication::translate("OptionsDialog", "CheckBox", 0));
        checkBox_2->setText(QApplication::translate("OptionsDialog", "CheckBox", 0));
        checkBox_4->setText(QApplication::translate("OptionsDialog", "CheckBox", 0));
        checkBox_5->setText(QApplication::translate("OptionsDialog", "CheckBox", 0));
        checkBox_9->setText(QApplication::translate("OptionsDialog", "CheckBox", 0));
        checkBox_8->setText(QApplication::translate("OptionsDialog", "CheckBox", 0));
        checkBox_3->setText(QApplication::translate("OptionsDialog", "CheckBox", 0));
        checkBox->setText(QApplication::translate("OptionsDialog", "CheckBox", 0));
        label->setText(QApplication::translate("OptionsDialog", "TextLabel", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("OptionsDialog", "Tab 1", 0));
        label_2->setText(QApplication::translate("OptionsDialog", "TextLabel", 0));
        pushButton->setText(QApplication::translate("OptionsDialog", "PushButton", 0));
        label_3->setText(QApplication::translate("OptionsDialog", "TextLabel", 0));
        pushButton_2->setText(QApplication::translate("OptionsDialog", "PushButton", 0));
        label_4->setText(QApplication::translate("OptionsDialog", "TextLabel", 0));
        pushButton_3->setText(QApplication::translate("OptionsDialog", "PushButton", 0));
        label_5->setText(QApplication::translate("OptionsDialog", "TextLabel", 0));
        pushButton_4->setText(QApplication::translate("OptionsDialog", "PushButton", 0));
        label_6->setText(QApplication::translate("OptionsDialog", "TextLabel", 0));
        pushButton_5->setText(QApplication::translate("OptionsDialog", "PushButton", 0));
        label_7->setText(QApplication::translate("OptionsDialog", "TextLabel", 0));
        pushButton_6->setText(QApplication::translate("OptionsDialog", "PushButton", 0));
        label_8->setText(QApplication::translate("OptionsDialog", "TextLabel", 0));
        pushButton_7->setText(QApplication::translate("OptionsDialog", "PushButton", 0));
        label_9->setText(QApplication::translate("OptionsDialog", "TextLabel", 0));
        pushButton_8->setText(QApplication::translate("OptionsDialog", "PushButton", 0));
        label_10->setText(QApplication::translate("OptionsDialog", "TextLabel", 0));
        pushButton_9->setText(QApplication::translate("OptionsDialog", "PushButton", 0));
        label_11->setText(QApplication::translate("OptionsDialog", "TextLabel", 0));
        pushButton_10->setText(QApplication::translate("OptionsDialog", "PushButton", 0));
        label_12->setText(QApplication::translate("OptionsDialog", "TextLabel", 0));
        pushButton_11->setText(QApplication::translate("OptionsDialog", "PushButton", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("OptionsDialog", "Tab 2", 0));
    } // retranslateUi

};

namespace Ui {
    class OptionsDialog: public Ui_OptionsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSDIALOG_H
