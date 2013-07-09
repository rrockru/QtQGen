#include "optionsdialog.h"

OptionsDialog::OptionsDialog(IControls *controls, QString caption, QWidget *parent) :
    QDialog(parent)
{
    _controls = controls;
    setWindowTitle(caption);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    QPushButton *resetButton = new QPushButton(tr("Reset"), this);
    QPushButton *okButton = new QPushButton(tr("OK"), this);
    QPushButton *cancelButton = new QPushButton(tr("Cancel"), this);
    QPushButton *applyButton = new QPushButton(tr("Apply"), this);
    btnLayout->addWidget(resetButton);
    btnLayout->addStretch();
    btnLayout->addWidget(okButton);
    btnLayout->addWidget(cancelButton);
    btnLayout->addWidget(applyButton);

    QVBoxLayout *vbox = new QVBoxLayout;

    QTabWidget *tabs = new QTabWidget(this);

    _general = new QWidget(tabs);

    _editor = new QWidget(tabs);

    _sizes = new QWidget(tabs);

    _colors = new QWidget(tabs);

    _fonts = new QWidget(tabs);

    _paths = new QWidget(tabs);

    _hotkeys = new QWidget(tabs);


    tabs->addTab(_general, tr("General"));
    tabs->addTab(_editor, tr("Code editor"));
    tabs->addTab(_sizes, tr("Sizes"));
    tabs->addTab(_colors, tr("Colors"));
    tabs->addTab(_fonts, tr("Fonts"));
    tabs->addTab(_paths, tr("Paths"));
    tabs->addTab(_hotkeys, tr("Hotkeys"));

    vbox->addWidget(tabs);
    vbox->addLayout(btnLayout);

    setLayout(vbox);
}
