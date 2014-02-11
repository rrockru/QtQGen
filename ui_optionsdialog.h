/********************************************************************************
** Form generated from reading UI file 'optionsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
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
#include "src/colorwidget.h"
#include "src/fontwidget.h"

QT_BEGIN_NAMESPACE

class Ui_OptionsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *_general;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QCheckBox *_chkAutoSave;
    QSpinBox *_spnAutoSaveMin;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *_chkFirstLoc;
    QLineEdit *_txtNameFirsLoc;
    QCheckBox *_chkDescOfLoc;
    QCheckBox *_chkOpeningLoc;
    QCheckBox *_chkOpeningAct;
    QCheckBox *_chkOnLocActIcons;
    QCheckBox *_chkLocDescVisible;
    QCheckBox *_chkLocActsVisible;
    QCheckBox *_chkOpenLastGame;
    QHBoxLayout *horizontalLayout_3;
    QLabel *_stTextCmbLang;
    QComboBox *_cmbLang;
    QWidget *_colors;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *_stText11;
    ColorWidget *_colorBaseBack;
    QPushButton *_btnClrsBaseBack;
    QHBoxLayout *horizontalLayout_6;
    QLabel *_stText10;
    ColorWidget *_colorTextBack;
    QPushButton *_btnClrsTextBack;
    QHBoxLayout *horizontalLayout_7;
    QLabel *_stText9;
    ColorWidget *_colorBaseFont;
    QPushButton *_btnClrsBaseFont;
    QHBoxLayout *horizontalLayout_5;
    QLabel *_stText1;
    ColorWidget *_colorStatements;
    QPushButton *_btnClrsStatements;
    QHBoxLayout *horizontalLayout_14;
    QLabel *_stText2;
    ColorWidget *_colorFunctions;
    QPushButton *_btnClrsFunctions;
    QHBoxLayout *horizontalLayout_13;
    QLabel *_stText3;
    ColorWidget *_colorSysVariables;
    QPushButton *_btnClrsSysVariables;
    QHBoxLayout *horizontalLayout_12;
    QLabel *_stText4;
    ColorWidget *_colorStrings;
    QPushButton *_btnClrsStrings;
    QHBoxLayout *horizontalLayout_11;
    QLabel *_stText5;
    ColorWidget *_colorNumbers;
    QPushButton *_btnClrsNumbers;
    QHBoxLayout *horizontalLayout_10;
    QLabel *_stText6;
    ColorWidget *_colorOptsBrts;
    QPushButton *_btnClrsOptsBrts;
    QHBoxLayout *horizontalLayout_9;
    QLabel *_stText7;
    ColorWidget *_colorMarks;
    QPushButton *_btnClrsMarks;
    QHBoxLayout *horizontalLayout_8;
    QLabel *_stText8;
    ColorWidget *_colorComments;
    QPushButton *_btnClrsComments;
    QWidget *_fonts;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_15;
    QLabel *_stText01;
    FontWidget *_txtFontBase;
    QPushButton *_btnFontsBase;
    QHBoxLayout *horizontalLayout_25;
    QLabel *_stText02;
    FontWidget *_txtFontStatements;
    QPushButton *_btnFontsStatements;
    QHBoxLayout *horizontalLayout_24;
    QLabel *_stText03;
    FontWidget *_txtFontFunctions;
    QPushButton *_btnFontsFunctions;
    QHBoxLayout *horizontalLayout_23;
    QLabel *_stText04;
    FontWidget *_txtFontSysVariables;
    QPushButton *_btnFontsSysVariables;
    QHBoxLayout *horizontalLayout_22;
    QLabel *_stText05;
    FontWidget *_txtFontStrings;
    QPushButton *_btnFontsStrings;
    QHBoxLayout *horizontalLayout_21;
    QLabel *_stText06;
    FontWidget *_txtFontNumbers;
    QPushButton *_btnFontsNumbers;
    QHBoxLayout *horizontalLayout_20;
    QLabel *_stText07;
    FontWidget *_txtFontOptsBrts;
    QPushButton *_btnFontsOptsBrts;
    QHBoxLayout *horizontalLayout_18;
    QLabel *_stText08;
    FontWidget *_txtFontMarks;
    QPushButton *_btnFontsMarks;
    QHBoxLayout *horizontalLayout_16;
    QLabel *_stText09;
    FontWidget *_txtFontComments;
    QPushButton *_btnFontsComments;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *OptionsDialog)
    {
        if (OptionsDialog->objectName().isEmpty())
            OptionsDialog->setObjectName(QStringLiteral("OptionsDialog"));
        OptionsDialog->setWindowModality(Qt::NonModal);
        OptionsDialog->resize(414, 428);
        OptionsDialog->setAutoFillBackground(false);
        OptionsDialog->setSizeGripEnabled(false);
        OptionsDialog->setModal(true);
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
        _general = new QWidget();
        _general->setObjectName(QStringLiteral("_general"));
        _general->setEnabled(true);
        verticalLayout_3 = new QVBoxLayout(_general);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        _chkAutoSave = new QCheckBox(_general);
        _chkAutoSave->setObjectName(QStringLiteral("_chkAutoSave"));

        horizontalLayout->addWidget(_chkAutoSave);

        _spnAutoSaveMin = new QSpinBox(_general);
        _spnAutoSaveMin->setObjectName(QStringLiteral("_spnAutoSaveMin"));
        _spnAutoSaveMin->setEnabled(false);
        _spnAutoSaveMin->setMinimum(1);
        _spnAutoSaveMin->setMaximum(60);
        _spnAutoSaveMin->setValue(1);

        horizontalLayout->addWidget(_spnAutoSaveMin);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);

        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        _chkFirstLoc = new QCheckBox(_general);
        _chkFirstLoc->setObjectName(QStringLiteral("_chkFirstLoc"));

        horizontalLayout_2->addWidget(_chkFirstLoc);

        _txtNameFirsLoc = new QLineEdit(_general);
        _txtNameFirsLoc->setObjectName(QStringLiteral("_txtNameFirsLoc"));
        _txtNameFirsLoc->setEnabled(false);

        horizontalLayout_2->addWidget(_txtNameFirsLoc);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 1);

        verticalLayout_3->addLayout(horizontalLayout_2);

        _chkDescOfLoc = new QCheckBox(_general);
        _chkDescOfLoc->setObjectName(QStringLiteral("_chkDescOfLoc"));

        verticalLayout_3->addWidget(_chkDescOfLoc);

        _chkOpeningLoc = new QCheckBox(_general);
        _chkOpeningLoc->setObjectName(QStringLiteral("_chkOpeningLoc"));

        verticalLayout_3->addWidget(_chkOpeningLoc);

        _chkOpeningAct = new QCheckBox(_general);
        _chkOpeningAct->setObjectName(QStringLiteral("_chkOpeningAct"));

        verticalLayout_3->addWidget(_chkOpeningAct);

        _chkOnLocActIcons = new QCheckBox(_general);
        _chkOnLocActIcons->setObjectName(QStringLiteral("_chkOnLocActIcons"));

        verticalLayout_3->addWidget(_chkOnLocActIcons);

        _chkLocDescVisible = new QCheckBox(_general);
        _chkLocDescVisible->setObjectName(QStringLiteral("_chkLocDescVisible"));

        verticalLayout_3->addWidget(_chkLocDescVisible);

        _chkLocActsVisible = new QCheckBox(_general);
        _chkLocActsVisible->setObjectName(QStringLiteral("_chkLocActsVisible"));

        verticalLayout_3->addWidget(_chkLocActsVisible);

        _chkOpenLastGame = new QCheckBox(_general);
        _chkOpenLastGame->setObjectName(QStringLiteral("_chkOpenLastGame"));

        verticalLayout_3->addWidget(_chkOpenLastGame);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        _stTextCmbLang = new QLabel(_general);
        _stTextCmbLang->setObjectName(QStringLiteral("_stTextCmbLang"));

        horizontalLayout_3->addWidget(_stTextCmbLang);

        _cmbLang = new QComboBox(_general);
        _cmbLang->setObjectName(QStringLiteral("_cmbLang"));

        horizontalLayout_3->addWidget(_cmbLang);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 1);

        verticalLayout_3->addLayout(horizontalLayout_3);

        tabWidget->addTab(_general, QString());
        _colors = new QWidget();
        _colors->setObjectName(QStringLiteral("_colors"));
        verticalLayout_2 = new QVBoxLayout(_colors);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        _stText11 = new QLabel(_colors);
        _stText11->setObjectName(QStringLiteral("_stText11"));

        horizontalLayout_4->addWidget(_stText11);

        _colorBaseBack = new ColorWidget(_colors);
        _colorBaseBack->setObjectName(QStringLiteral("_colorBaseBack"));
        _colorBaseBack->setAutoFillBackground(true);

        horizontalLayout_4->addWidget(_colorBaseBack);

        _btnClrsBaseBack = new QPushButton(_colors);
        _btnClrsBaseBack->setObjectName(QStringLiteral("_btnClrsBaseBack"));

        horizontalLayout_4->addWidget(_btnClrsBaseBack);

        horizontalLayout_4->setStretch(0, 4);
        horizontalLayout_4->setStretch(1, 1);
        horizontalLayout_4->setStretch(2, 2);

        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        _stText10 = new QLabel(_colors);
        _stText10->setObjectName(QStringLiteral("_stText10"));

        horizontalLayout_6->addWidget(_stText10);

        _colorTextBack = new ColorWidget(_colors);
        _colorTextBack->setObjectName(QStringLiteral("_colorTextBack"));
        _colorTextBack->setAutoFillBackground(true);

        horizontalLayout_6->addWidget(_colorTextBack);

        _btnClrsTextBack = new QPushButton(_colors);
        _btnClrsTextBack->setObjectName(QStringLiteral("_btnClrsTextBack"));

        horizontalLayout_6->addWidget(_btnClrsTextBack);

        horizontalLayout_6->setStretch(0, 4);
        horizontalLayout_6->setStretch(1, 1);
        horizontalLayout_6->setStretch(2, 2);

        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        _stText9 = new QLabel(_colors);
        _stText9->setObjectName(QStringLiteral("_stText9"));

        horizontalLayout_7->addWidget(_stText9);

        _colorBaseFont = new ColorWidget(_colors);
        _colorBaseFont->setObjectName(QStringLiteral("_colorBaseFont"));
        _colorBaseFont->setAutoFillBackground(true);

        horizontalLayout_7->addWidget(_colorBaseFont);

        _btnClrsBaseFont = new QPushButton(_colors);
        _btnClrsBaseFont->setObjectName(QStringLiteral("_btnClrsBaseFont"));

        horizontalLayout_7->addWidget(_btnClrsBaseFont);

        horizontalLayout_7->setStretch(0, 4);
        horizontalLayout_7->setStretch(1, 1);
        horizontalLayout_7->setStretch(2, 2);

        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        _stText1 = new QLabel(_colors);
        _stText1->setObjectName(QStringLiteral("_stText1"));

        horizontalLayout_5->addWidget(_stText1);

        _colorStatements = new ColorWidget(_colors);
        _colorStatements->setObjectName(QStringLiteral("_colorStatements"));
        _colorStatements->setAutoFillBackground(true);

        horizontalLayout_5->addWidget(_colorStatements);

        _btnClrsStatements = new QPushButton(_colors);
        _btnClrsStatements->setObjectName(QStringLiteral("_btnClrsStatements"));

        horizontalLayout_5->addWidget(_btnClrsStatements);

        horizontalLayout_5->setStretch(0, 4);
        horizontalLayout_5->setStretch(1, 1);
        horizontalLayout_5->setStretch(2, 2);

        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        _stText2 = new QLabel(_colors);
        _stText2->setObjectName(QStringLiteral("_stText2"));

        horizontalLayout_14->addWidget(_stText2);

        _colorFunctions = new ColorWidget(_colors);
        _colorFunctions->setObjectName(QStringLiteral("_colorFunctions"));
        _colorFunctions->setAutoFillBackground(true);

        horizontalLayout_14->addWidget(_colorFunctions);

        _btnClrsFunctions = new QPushButton(_colors);
        _btnClrsFunctions->setObjectName(QStringLiteral("_btnClrsFunctions"));

        horizontalLayout_14->addWidget(_btnClrsFunctions);

        horizontalLayout_14->setStretch(0, 4);
        horizontalLayout_14->setStretch(1, 1);
        horizontalLayout_14->setStretch(2, 2);

        verticalLayout_2->addLayout(horizontalLayout_14);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        _stText3 = new QLabel(_colors);
        _stText3->setObjectName(QStringLiteral("_stText3"));

        horizontalLayout_13->addWidget(_stText3);

        _colorSysVariables = new ColorWidget(_colors);
        _colorSysVariables->setObjectName(QStringLiteral("_colorSysVariables"));
        _colorSysVariables->setAutoFillBackground(true);

        horizontalLayout_13->addWidget(_colorSysVariables);

        _btnClrsSysVariables = new QPushButton(_colors);
        _btnClrsSysVariables->setObjectName(QStringLiteral("_btnClrsSysVariables"));

        horizontalLayout_13->addWidget(_btnClrsSysVariables);

        horizontalLayout_13->setStretch(0, 4);
        horizontalLayout_13->setStretch(1, 1);
        horizontalLayout_13->setStretch(2, 2);

        verticalLayout_2->addLayout(horizontalLayout_13);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        _stText4 = new QLabel(_colors);
        _stText4->setObjectName(QStringLiteral("_stText4"));

        horizontalLayout_12->addWidget(_stText4);

        _colorStrings = new ColorWidget(_colors);
        _colorStrings->setObjectName(QStringLiteral("_colorStrings"));
        _colorStrings->setAutoFillBackground(true);

        horizontalLayout_12->addWidget(_colorStrings);

        _btnClrsStrings = new QPushButton(_colors);
        _btnClrsStrings->setObjectName(QStringLiteral("_btnClrsStrings"));

        horizontalLayout_12->addWidget(_btnClrsStrings);

        horizontalLayout_12->setStretch(0, 4);
        horizontalLayout_12->setStretch(1, 1);
        horizontalLayout_12->setStretch(2, 2);

        verticalLayout_2->addLayout(horizontalLayout_12);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        _stText5 = new QLabel(_colors);
        _stText5->setObjectName(QStringLiteral("_stText5"));

        horizontalLayout_11->addWidget(_stText5);

        _colorNumbers = new ColorWidget(_colors);
        _colorNumbers->setObjectName(QStringLiteral("_colorNumbers"));
        _colorNumbers->setAutoFillBackground(true);

        horizontalLayout_11->addWidget(_colorNumbers);

        _btnClrsNumbers = new QPushButton(_colors);
        _btnClrsNumbers->setObjectName(QStringLiteral("_btnClrsNumbers"));

        horizontalLayout_11->addWidget(_btnClrsNumbers);

        horizontalLayout_11->setStretch(0, 4);
        horizontalLayout_11->setStretch(1, 1);
        horizontalLayout_11->setStretch(2, 2);

        verticalLayout_2->addLayout(horizontalLayout_11);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        _stText6 = new QLabel(_colors);
        _stText6->setObjectName(QStringLiteral("_stText6"));

        horizontalLayout_10->addWidget(_stText6);

        _colorOptsBrts = new ColorWidget(_colors);
        _colorOptsBrts->setObjectName(QStringLiteral("_colorOptsBrts"));
        _colorOptsBrts->setAutoFillBackground(true);

        horizontalLayout_10->addWidget(_colorOptsBrts);

        _btnClrsOptsBrts = new QPushButton(_colors);
        _btnClrsOptsBrts->setObjectName(QStringLiteral("_btnClrsOptsBrts"));

        horizontalLayout_10->addWidget(_btnClrsOptsBrts);

        horizontalLayout_10->setStretch(0, 4);
        horizontalLayout_10->setStretch(1, 1);
        horizontalLayout_10->setStretch(2, 2);

        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        _stText7 = new QLabel(_colors);
        _stText7->setObjectName(QStringLiteral("_stText7"));

        horizontalLayout_9->addWidget(_stText7);

        _colorMarks = new ColorWidget(_colors);
        _colorMarks->setObjectName(QStringLiteral("_colorMarks"));
        _colorMarks->setAutoFillBackground(true);

        horizontalLayout_9->addWidget(_colorMarks);

        _btnClrsMarks = new QPushButton(_colors);
        _btnClrsMarks->setObjectName(QStringLiteral("_btnClrsMarks"));

        horizontalLayout_9->addWidget(_btnClrsMarks);

        horizontalLayout_9->setStretch(0, 4);
        horizontalLayout_9->setStretch(1, 1);
        horizontalLayout_9->setStretch(2, 2);

        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        _stText8 = new QLabel(_colors);
        _stText8->setObjectName(QStringLiteral("_stText8"));

        horizontalLayout_8->addWidget(_stText8);

        _colorComments = new ColorWidget(_colors);
        _colorComments->setObjectName(QStringLiteral("_colorComments"));
        _colorComments->setAutoFillBackground(true);

        horizontalLayout_8->addWidget(_colorComments);

        _btnClrsComments = new QPushButton(_colors);
        _btnClrsComments->setObjectName(QStringLiteral("_btnClrsComments"));

        horizontalLayout_8->addWidget(_btnClrsComments);

        horizontalLayout_8->setStretch(0, 4);
        horizontalLayout_8->setStretch(1, 1);
        horizontalLayout_8->setStretch(2, 2);

        verticalLayout_2->addLayout(horizontalLayout_8);

        tabWidget->addTab(_colors, QString());
        _fonts = new QWidget();
        _fonts->setObjectName(QStringLiteral("_fonts"));
        verticalLayout_6 = new QVBoxLayout(_fonts);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        _stText01 = new QLabel(_fonts);
        _stText01->setObjectName(QStringLiteral("_stText01"));
        _stText01->setTextFormat(Qt::AutoText);

        horizontalLayout_15->addWidget(_stText01);

        _txtFontBase = new FontWidget(_fonts);
        _txtFontBase->setObjectName(QStringLiteral("_txtFontBase"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(_txtFontBase->sizePolicy().hasHeightForWidth());
        _txtFontBase->setSizePolicy(sizePolicy1);
        _txtFontBase->setAutoFillBackground(true);
        _txtFontBase->setAlignment(Qt::AlignCenter);
        _txtFontBase->setWordWrap(false);

        horizontalLayout_15->addWidget(_txtFontBase);

        _btnFontsBase = new QPushButton(_fonts);
        _btnFontsBase->setObjectName(QStringLiteral("_btnFontsBase"));

        horizontalLayout_15->addWidget(_btnFontsBase);

        horizontalLayout_15->setStretch(0, 3);
        horizontalLayout_15->setStretch(1, 2);
        horizontalLayout_15->setStretch(2, 2);

        verticalLayout_6->addLayout(horizontalLayout_15);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setObjectName(QStringLiteral("horizontalLayout_25"));
        _stText02 = new QLabel(_fonts);
        _stText02->setObjectName(QStringLiteral("_stText02"));

        horizontalLayout_25->addWidget(_stText02);

        _txtFontStatements = new FontWidget(_fonts);
        _txtFontStatements->setObjectName(QStringLiteral("_txtFontStatements"));
        sizePolicy1.setHeightForWidth(_txtFontStatements->sizePolicy().hasHeightForWidth());
        _txtFontStatements->setSizePolicy(sizePolicy1);
        _txtFontStatements->setAutoFillBackground(true);
        _txtFontStatements->setAlignment(Qt::AlignCenter);

        horizontalLayout_25->addWidget(_txtFontStatements);

        _btnFontsStatements = new QPushButton(_fonts);
        _btnFontsStatements->setObjectName(QStringLiteral("_btnFontsStatements"));

        horizontalLayout_25->addWidget(_btnFontsStatements);

        horizontalLayout_25->setStretch(0, 3);
        horizontalLayout_25->setStretch(1, 2);
        horizontalLayout_25->setStretch(2, 2);

        verticalLayout_6->addLayout(horizontalLayout_25);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName(QStringLiteral("horizontalLayout_24"));
        _stText03 = new QLabel(_fonts);
        _stText03->setObjectName(QStringLiteral("_stText03"));

        horizontalLayout_24->addWidget(_stText03);

        _txtFontFunctions = new FontWidget(_fonts);
        _txtFontFunctions->setObjectName(QStringLiteral("_txtFontFunctions"));
        sizePolicy1.setHeightForWidth(_txtFontFunctions->sizePolicy().hasHeightForWidth());
        _txtFontFunctions->setSizePolicy(sizePolicy1);
        _txtFontFunctions->setAutoFillBackground(true);
        _txtFontFunctions->setAlignment(Qt::AlignCenter);

        horizontalLayout_24->addWidget(_txtFontFunctions);

        _btnFontsFunctions = new QPushButton(_fonts);
        _btnFontsFunctions->setObjectName(QStringLiteral("_btnFontsFunctions"));

        horizontalLayout_24->addWidget(_btnFontsFunctions);

        horizontalLayout_24->setStretch(0, 3);
        horizontalLayout_24->setStretch(1, 2);
        horizontalLayout_24->setStretch(2, 2);

        verticalLayout_6->addLayout(horizontalLayout_24);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        _stText04 = new QLabel(_fonts);
        _stText04->setObjectName(QStringLiteral("_stText04"));

        horizontalLayout_23->addWidget(_stText04);

        _txtFontSysVariables = new FontWidget(_fonts);
        _txtFontSysVariables->setObjectName(QStringLiteral("_txtFontSysVariables"));
        sizePolicy1.setHeightForWidth(_txtFontSysVariables->sizePolicy().hasHeightForWidth());
        _txtFontSysVariables->setSizePolicy(sizePolicy1);
        _txtFontSysVariables->setAutoFillBackground(true);
        _txtFontSysVariables->setAlignment(Qt::AlignCenter);

        horizontalLayout_23->addWidget(_txtFontSysVariables);

        _btnFontsSysVariables = new QPushButton(_fonts);
        _btnFontsSysVariables->setObjectName(QStringLiteral("_btnFontsSysVariables"));

        horizontalLayout_23->addWidget(_btnFontsSysVariables);

        horizontalLayout_23->setStretch(0, 3);
        horizontalLayout_23->setStretch(1, 2);
        horizontalLayout_23->setStretch(2, 2);

        verticalLayout_6->addLayout(horizontalLayout_23);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        _stText05 = new QLabel(_fonts);
        _stText05->setObjectName(QStringLiteral("_stText05"));

        horizontalLayout_22->addWidget(_stText05);

        _txtFontStrings = new FontWidget(_fonts);
        _txtFontStrings->setObjectName(QStringLiteral("_txtFontStrings"));
        sizePolicy1.setHeightForWidth(_txtFontStrings->sizePolicy().hasHeightForWidth());
        _txtFontStrings->setSizePolicy(sizePolicy1);
        _txtFontStrings->setAutoFillBackground(true);
        _txtFontStrings->setAlignment(Qt::AlignCenter);

        horizontalLayout_22->addWidget(_txtFontStrings);

        _btnFontsStrings = new QPushButton(_fonts);
        _btnFontsStrings->setObjectName(QStringLiteral("_btnFontsStrings"));

        horizontalLayout_22->addWidget(_btnFontsStrings);

        horizontalLayout_22->setStretch(0, 3);
        horizontalLayout_22->setStretch(1, 2);
        horizontalLayout_22->setStretch(2, 2);

        verticalLayout_6->addLayout(horizontalLayout_22);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        _stText06 = new QLabel(_fonts);
        _stText06->setObjectName(QStringLiteral("_stText06"));

        horizontalLayout_21->addWidget(_stText06);

        _txtFontNumbers = new FontWidget(_fonts);
        _txtFontNumbers->setObjectName(QStringLiteral("_txtFontNumbers"));
        sizePolicy1.setHeightForWidth(_txtFontNumbers->sizePolicy().hasHeightForWidth());
        _txtFontNumbers->setSizePolicy(sizePolicy1);
        _txtFontNumbers->setAutoFillBackground(true);
        _txtFontNumbers->setAlignment(Qt::AlignCenter);

        horizontalLayout_21->addWidget(_txtFontNumbers);

        _btnFontsNumbers = new QPushButton(_fonts);
        _btnFontsNumbers->setObjectName(QStringLiteral("_btnFontsNumbers"));

        horizontalLayout_21->addWidget(_btnFontsNumbers);

        horizontalLayout_21->setStretch(0, 3);
        horizontalLayout_21->setStretch(1, 2);
        horizontalLayout_21->setStretch(2, 2);

        verticalLayout_6->addLayout(horizontalLayout_21);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        _stText07 = new QLabel(_fonts);
        _stText07->setObjectName(QStringLiteral("_stText07"));

        horizontalLayout_20->addWidget(_stText07);

        _txtFontOptsBrts = new FontWidget(_fonts);
        _txtFontOptsBrts->setObjectName(QStringLiteral("_txtFontOptsBrts"));
        sizePolicy1.setHeightForWidth(_txtFontOptsBrts->sizePolicy().hasHeightForWidth());
        _txtFontOptsBrts->setSizePolicy(sizePolicy1);
        _txtFontOptsBrts->setAutoFillBackground(true);
        _txtFontOptsBrts->setAlignment(Qt::AlignCenter);

        horizontalLayout_20->addWidget(_txtFontOptsBrts);

        _btnFontsOptsBrts = new QPushButton(_fonts);
        _btnFontsOptsBrts->setObjectName(QStringLiteral("_btnFontsOptsBrts"));

        horizontalLayout_20->addWidget(_btnFontsOptsBrts);

        horizontalLayout_20->setStretch(0, 3);
        horizontalLayout_20->setStretch(1, 2);
        horizontalLayout_20->setStretch(2, 2);

        verticalLayout_6->addLayout(horizontalLayout_20);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        _stText08 = new QLabel(_fonts);
        _stText08->setObjectName(QStringLiteral("_stText08"));

        horizontalLayout_18->addWidget(_stText08);

        _txtFontMarks = new FontWidget(_fonts);
        _txtFontMarks->setObjectName(QStringLiteral("_txtFontMarks"));
        sizePolicy1.setHeightForWidth(_txtFontMarks->sizePolicy().hasHeightForWidth());
        _txtFontMarks->setSizePolicy(sizePolicy1);
        _txtFontMarks->setAutoFillBackground(true);
        _txtFontMarks->setAlignment(Qt::AlignCenter);

        horizontalLayout_18->addWidget(_txtFontMarks);

        _btnFontsMarks = new QPushButton(_fonts);
        _btnFontsMarks->setObjectName(QStringLiteral("_btnFontsMarks"));

        horizontalLayout_18->addWidget(_btnFontsMarks);

        horizontalLayout_18->setStretch(0, 3);
        horizontalLayout_18->setStretch(1, 2);
        horizontalLayout_18->setStretch(2, 2);

        verticalLayout_6->addLayout(horizontalLayout_18);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        _stText09 = new QLabel(_fonts);
        _stText09->setObjectName(QStringLiteral("_stText09"));

        horizontalLayout_16->addWidget(_stText09);

        _txtFontComments = new FontWidget(_fonts);
        _txtFontComments->setObjectName(QStringLiteral("_txtFontComments"));
        sizePolicy1.setHeightForWidth(_txtFontComments->sizePolicy().hasHeightForWidth());
        _txtFontComments->setSizePolicy(sizePolicy1);
        _txtFontComments->setAutoFillBackground(true);
        _txtFontComments->setAlignment(Qt::AlignCenter);

        horizontalLayout_16->addWidget(_txtFontComments);

        _btnFontsComments = new QPushButton(_fonts);
        _btnFontsComments->setObjectName(QStringLiteral("_btnFontsComments"));

        horizontalLayout_16->addWidget(_btnFontsComments);

        horizontalLayout_16->setStretch(0, 3);
        horizontalLayout_16->setStretch(1, 2);
        horizontalLayout_16->setStretch(2, 2);

        verticalLayout_6->addLayout(horizontalLayout_16);

        tabWidget->addTab(_fonts, QString());

        verticalLayout->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(OptionsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Cancel|QDialogButtonBox::Ok|QDialogButtonBox::Reset);
        buttonBox->setCenterButtons(false);

        verticalLayout->addWidget(buttonBox);

#ifndef QT_NO_SHORTCUT
        _stTextCmbLang->setBuddy(_cmbLang);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(tabWidget, _chkAutoSave);
        QWidget::setTabOrder(_chkAutoSave, _spnAutoSaveMin);
        QWidget::setTabOrder(_spnAutoSaveMin, _chkFirstLoc);
        QWidget::setTabOrder(_chkFirstLoc, _txtNameFirsLoc);
        QWidget::setTabOrder(_txtNameFirsLoc, _chkDescOfLoc);
        QWidget::setTabOrder(_chkDescOfLoc, _chkOpeningLoc);
        QWidget::setTabOrder(_chkOpeningLoc, _chkOpeningAct);
        QWidget::setTabOrder(_chkOpeningAct, _chkOnLocActIcons);
        QWidget::setTabOrder(_chkOnLocActIcons, _chkLocDescVisible);
        QWidget::setTabOrder(_chkLocDescVisible, _chkLocActsVisible);
        QWidget::setTabOrder(_chkLocActsVisible, _chkOpenLastGame);
        QWidget::setTabOrder(_chkOpenLastGame, _cmbLang);
        QWidget::setTabOrder(_cmbLang, buttonBox);

        retranslateUi(OptionsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), OptionsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), OptionsDialog, SLOT(reject()));
        QObject::connect(_chkAutoSave, SIGNAL(toggled(bool)), _spnAutoSaveMin, SLOT(setEnabled(bool)));
        QObject::connect(_chkFirstLoc, SIGNAL(toggled(bool)), _txtNameFirsLoc, SLOT(setEnabled(bool)));
        QObject::connect(_btnClrsBaseBack, SIGNAL(clicked()), OptionsDialog, SLOT(OnColorSelect()));
        QObject::connect(_btnClrsTextBack, SIGNAL(clicked()), OptionsDialog, SLOT(OnColorSelect()));
        QObject::connect(_btnClrsBaseFont, SIGNAL(clicked()), OptionsDialog, SLOT(OnColorSelect()));
        QObject::connect(_btnClrsStatements, SIGNAL(clicked()), OptionsDialog, SLOT(OnColorSelect()));
        QObject::connect(_btnClrsFunctions, SIGNAL(clicked()), OptionsDialog, SLOT(OnColorSelect()));
        QObject::connect(_btnClrsSysVariables, SIGNAL(clicked()), OptionsDialog, SLOT(OnColorSelect()));
        QObject::connect(_btnClrsStrings, SIGNAL(clicked()), OptionsDialog, SLOT(OnColorSelect()));
        QObject::connect(_btnClrsNumbers, SIGNAL(clicked()), OptionsDialog, SLOT(OnColorSelect()));
        QObject::connect(_btnClrsOptsBrts, SIGNAL(clicked()), OptionsDialog, SLOT(OnColorSelect()));
        QObject::connect(_btnClrsMarks, SIGNAL(clicked()), OptionsDialog, SLOT(OnColorSelect()));
        QObject::connect(_btnClrsComments, SIGNAL(clicked()), OptionsDialog, SLOT(OnColorSelect()));
        QObject::connect(_btnFontsBase, SIGNAL(clicked()), OptionsDialog, SLOT(OnFontSelect()));
        QObject::connect(_btnFontsFunctions, SIGNAL(clicked()), OptionsDialog, SLOT(OnFontSelect()));
        QObject::connect(_btnFontsSysVariables, SIGNAL(clicked()), OptionsDialog, SLOT(OnFontSelect()));
        QObject::connect(_btnFontsStrings, SIGNAL(clicked()), OptionsDialog, SLOT(OnFontSelect()));
        QObject::connect(_btnFontsNumbers, SIGNAL(clicked()), OptionsDialog, SLOT(OnFontSelect()));
        QObject::connect(_btnFontsMarks, SIGNAL(clicked()), OptionsDialog, SLOT(OnFontSelect()));
        QObject::connect(_btnFontsComments, SIGNAL(clicked()), OptionsDialog, SLOT(OnFontSelect()));
        QObject::connect(_btnFontsOptsBrts, SIGNAL(clicked()), OptionsDialog, SLOT(OnFontSelect()));
        QObject::connect(_btnFontsStatements, SIGNAL(clicked()), OptionsDialog, SLOT(OnFontSelect()));

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(OptionsDialog);
    } // setupUi

    void retranslateUi(QDialog *OptionsDialog)
    {
        OptionsDialog->setWindowTitle(QApplication::translate("OptionsDialog", "Settings", 0));
        _chkAutoSave->setText(QApplication::translate("OptionsDialog", "Auto save every", 0));
        _chkFirstLoc->setText(QApplication::translate("OptionsDialog", "Auto create first location:", 0));
        _chkDescOfLoc->setText(QApplication::translate("OptionsDialog", "Show short locations descriptions", 0));
        _chkOpeningLoc->setText(QApplication::translate("OptionsDialog", "Open location after creation", 0));
        _chkOpeningAct->setText(QApplication::translate("OptionsDialog", "Open action after creation", 0));
        _chkOnLocActIcons->setText(QApplication::translate("OptionsDialog", "Show locations icons", 0));
        _chkLocDescVisible->setText(QApplication::translate("OptionsDialog", "Show base description on location's tab", 0));
        _chkLocActsVisible->setText(QApplication::translate("OptionsDialog", "Show base actions on location's tab", 0));
        _chkOpenLastGame->setText(QApplication::translate("OptionsDialog", "Remember game file on exit", 0));
        _stTextCmbLang->setText(QApplication::translate("OptionsDialog", "UI language", 0));
        tabWidget->setTabText(tabWidget->indexOf(_general), QApplication::translate("OptionsDialog", "General", 0));
        _stText11->setText(QApplication::translate("OptionsDialog", "Main background color:", 0));
        _btnClrsBaseBack->setText(QApplication::translate("OptionsDialog", "Select color...", 0));
        _stText10->setText(QApplication::translate("OptionsDialog", "Tabs background color:", 0));
        _btnClrsTextBack->setText(QApplication::translate("OptionsDialog", "Select color...", 0));
        _stText9->setText(QApplication::translate("OptionsDialog", "Base font's color:", 0));
        _btnClrsBaseFont->setText(QApplication::translate("OptionsDialog", "Select color...", 0));
        _stText1->setText(QApplication::translate("OptionsDialog", "Statements color:", 0));
        _btnClrsStatements->setText(QApplication::translate("OptionsDialog", "Select color...", 0));
        _stText2->setText(QApplication::translate("OptionsDialog", "Functions color:", 0));
        _btnClrsFunctions->setText(QApplication::translate("OptionsDialog", "Select color...", 0));
        _stText3->setText(QApplication::translate("OptionsDialog", "System variables color:", 0));
        _btnClrsSysVariables->setText(QApplication::translate("OptionsDialog", "Select color...", 0));
        _stText4->setText(QApplication::translate("OptionsDialog", "Strings color:", 0));
        _btnClrsStrings->setText(QApplication::translate("OptionsDialog", "Select color...", 0));
        _stText5->setText(QApplication::translate("OptionsDialog", "Numbers color:", 0));
        _btnClrsNumbers->setText(QApplication::translate("OptionsDialog", "Select color...", 0));
        _stText6->setText(QApplication::translate("OptionsDialog", "Operations color:", 0));
        _btnClrsOptsBrts->setText(QApplication::translate("OptionsDialog", "Select color...", 0));
        _stText7->setText(QApplication::translate("OptionsDialog", "Labels color:", 0));
        _btnClrsMarks->setText(QApplication::translate("OptionsDialog", "Select color...", 0));
        _stText8->setText(QApplication::translate("OptionsDialog", "Comments color:", 0));
        _btnClrsComments->setText(QApplication::translate("OptionsDialog", "Select color...", 0));
        tabWidget->setTabText(tabWidget->indexOf(_colors), QApplication::translate("OptionsDialog", "Colors", 0));
        _stText01->setText(QApplication::translate("OptionsDialog", "Main font:", 0));
        _txtFontBase->setText(QString());
        _btnFontsBase->setText(QApplication::translate("OptionsDialog", "Select font...", 0));
        _stText02->setText(QApplication::translate("OptionsDialog", "Statements font:", 0));
        _txtFontStatements->setText(QString());
        _btnFontsStatements->setText(QApplication::translate("OptionsDialog", "Select font...", 0));
        _stText03->setText(QApplication::translate("OptionsDialog", "Functions font:", 0));
        _txtFontFunctions->setText(QString());
        _btnFontsFunctions->setText(QApplication::translate("OptionsDialog", "Select font...", 0));
        _stText04->setText(QApplication::translate("OptionsDialog", "System variables font:", 0));
        _txtFontSysVariables->setText(QString());
        _btnFontsSysVariables->setText(QApplication::translate("OptionsDialog", "Select font...", 0));
        _stText05->setText(QApplication::translate("OptionsDialog", "Strings font:", 0));
        _txtFontStrings->setText(QString());
        _btnFontsStrings->setText(QApplication::translate("OptionsDialog", "Select font...", 0));
        _stText06->setText(QApplication::translate("OptionsDialog", "Numbers font:", 0));
        _txtFontNumbers->setText(QString());
        _btnFontsNumbers->setText(QApplication::translate("OptionsDialog", "Select font...", 0));
        _stText07->setText(QApplication::translate("OptionsDialog", "Operations font:", 0));
        _txtFontOptsBrts->setText(QString());
        _btnFontsOptsBrts->setText(QApplication::translate("OptionsDialog", "Select font...", 0));
        _stText08->setText(QApplication::translate("OptionsDialog", "Labels font:", 0));
        _txtFontMarks->setText(QString());
        _btnFontsMarks->setText(QApplication::translate("OptionsDialog", "Select font...", 0));
        _stText09->setText(QApplication::translate("OptionsDialog", "Comments font:", 0));
        _txtFontComments->setText(QString());
        _btnFontsComments->setText(QApplication::translate("OptionsDialog", "Select font...", 0));
        tabWidget->setTabText(tabWidget->indexOf(_fonts), QApplication::translate("OptionsDialog", "Fonts", 0));
    } // retranslateUi

};

namespace Ui {
    class OptionsDialog: public Ui_OptionsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSDIALOG_H
