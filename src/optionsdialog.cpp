#include "optionsdialog.h"
#include "ui_optionsdialog.h"

OptionsDialog::OptionsDialog(IControls *control, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);

    _control = control;
    _settings = control->GetSettings();

    InitOptionsDialog();

    connect(ui->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()), this, SLOT(OnApplyButton()));
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

void OptionsDialog::OnFontSelect()
{
    bool ok;
    QFont font;

    if (ui->_btnFontsBase == sender())
    {
        font = QFontDialog::getFont(&ok, ui->_txtFontBase->font(), this);
        if (ok)
        {
            ui->_txtFontBase->setFont(font);
            ui->_txtFontBase->setText(font.family());
            ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
        }
    } else if (ui->_btnFontsStatements == sender())
    {
        font = QFontDialog::getFont(&ok, ui->_txtFontStatements->font(), this);
        if (ok)
        {
            ui->_txtFontStatements->setFont(font);
            ui->_txtFontStatements->setText(font.family());
            ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
        }
    } else if (ui->_btnFontsFunctions == sender())
    {
        font = QFontDialog::getFont(&ok, ui->_txtFontFunctions->font(), this);
        if (ok)
        {
            ui->_txtFontFunctions->setFont(font);
            ui->_txtFontFunctions->setText(font.family());
            ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
        }
    } else if (ui->_btnFontsSysVariables == sender())
    {
        font = QFontDialog::getFont(&ok, ui->_txtFontSysVariables->font(), this);
        if (ok)
        {
            ui->_txtFontSysVariables->setFont(font);
            ui->_txtFontSysVariables->setText(font.family());
            ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
        }
    } else if (ui->_btnFontsStrings == sender())
    {
        font = QFontDialog::getFont(&ok, ui->_txtFontStrings->font(), this);
        if (ok)
        {
            ui->_txtFontStrings->setFont(font);
            ui->_txtFontStrings->setText(font.family());
            ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
        }
    } else if (ui->_btnFontsNumbers == sender())
    {
        font = QFontDialog::getFont(&ok, ui->_txtFontNumbers->font(), this);
        if (ok)
        {
            ui->_txtFontNumbers->setFont(font);
            ui->_txtFontNumbers->setText(font.family());
            ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
        }
    } else if (ui->_btnFontsOptsBrts == sender())
    {
        font = QFontDialog::getFont(&ok, ui->_txtFontOptsBrts->font(), this);
        if (ok)
        {
            ui->_txtFontOptsBrts->setFont(font);
            ui->_txtFontOptsBrts->setText(font.family());
            ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
        }
    } else if (ui->_btnFontsMarks == sender())
    {
        font = QFontDialog::getFont(&ok, ui->_txtFontMarks->font(), this);
        if (ok)
        {
            ui->_txtFontMarks->setFont(font);
            ui->_txtFontMarks->setText(font.family());
            ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
        }
    } else if (ui->_btnFontsComments == sender())
    {
        font = QFontDialog::getFont(&ok, ui->_txtFontComments->font(), this);
        if (ok)
        {
            ui->_txtFontComments->setFont(font);
            ui->_txtFontComments->setText(font.family());
            ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
        }
    }
}

void OptionsDialog::OnColorSelect()
{
    QColor color;

    if (ui->_btnClrsBaseBack == sender())
    {
        color = QColorDialog::getColor(ui->_colorBaseBack->GetBackColor(), this);
        if (color.isValid())
        {
            ui->_colorBaseBack->SetBackColor(color);
            ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
        }
    } else if (ui->_btnClrsTextBack == sender())
    {
        color = QColorDialog::getColor(ui->_colorTextBack->GetBackColor(), this);
        if (color.isValid())
        {
            ui->_colorTextBack->SetBackColor(color);
            ui->_txtFontBase->SetBackColor(color);
            ui->_txtFontStatements->SetBackColor(color);
            ui->_txtFontFunctions->SetBackColor(color);
            ui->_txtFontSysVariables->SetBackColor(color);
            ui->_txtFontStrings->SetBackColor(color);
            ui->_txtFontNumbers->SetBackColor(color);
            ui->_txtFontOptsBrts->SetBackColor(color);
            ui->_txtFontMarks->SetBackColor(color);
            ui->_txtFontComments->SetBackColor(color);
            ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
        }
    } else if (ui->_btnClrsBaseFont == sender())
    {
        color = QColorDialog::getColor(ui->_colorBaseFont->GetBackColor(), this);
        if (color.isValid())
        {
            ui->_colorBaseFont->SetBackColor(color);
            ui->_txtFontBase->SetFontColor(color);
            ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
        }
    } else if (ui->_btnClrsStatements == sender())
    {
        color = QColorDialog::getColor(ui->_colorStatements->GetBackColor(), this);
        if (color.isValid())
        {
            ui->_colorStatements->SetBackColor(color);
            ui->_txtFontStatements->SetFontColor(color);
            ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
        }
    } else if (ui->_btnClrsFunctions == sender())
    {
        color = QColorDialog::getColor(ui->_colorFunctions->GetBackColor(), this);
        if (color.isValid())
        {
            ui->_colorFunctions->SetBackColor(color);
            ui->_txtFontFunctions->SetFontColor(color);
            ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
        }
    } else if (ui->_btnClrsSysVariables == sender())
    {
        color = QColorDialog::getColor(ui->_colorSysVariables->GetBackColor(), this);
        if (color.isValid())
        {
            ui->_colorSysVariables->SetBackColor(color);
            ui->_txtFontSysVariables->SetFontColor(color);
            ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
        }
    } else if (ui->_btnClrsStrings == sender())
    {
        color = QColorDialog::getColor(ui->_colorStrings->GetBackColor(), this);
        if (color.isValid())
        {
            ui->_colorStrings->SetBackColor(color);
            ui->_txtFontStrings->SetFontColor(color);
            ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
        }
    } else if (ui->_btnClrsNumbers == sender())
    {
        color = QColorDialog::getColor(ui->_colorNumbers->GetBackColor(), this);
        if (color.isValid())
        {
            ui->_colorNumbers->SetBackColor(color);
            ui->_txtFontNumbers->SetFontColor(color);
            ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
        }
    } else if (ui->_btnClrsOptsBrts == sender())
    {
        color = QColorDialog::getColor(ui->_colorOptsBrts->GetBackColor(), this);
        if (color.isValid())
        {
            ui->_colorOptsBrts->SetBackColor(color);
            ui->_txtFontOptsBrts->SetFontColor(color);
            ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
        }
    } else if (ui->_btnClrsMarks == sender())
    {
        color = QColorDialog::getColor(ui->_colorMarks->GetBackColor(), this);
        if (color.isValid())
        {
            ui->_colorMarks->SetBackColor(color);
            ui->_txtFontMarks->SetFontColor(color);
            ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
        }
    } else if (ui->_btnClrsComments == sender())
    {
        color = QColorDialog::getColor(ui->_colorComments->GetBackColor(), this);
        if (color.isValid())
        {
            ui->_colorComments->SetBackColor(color);
            ui->_txtFontComments->SetFontColor(color);
            ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
        }
    }
}

void OptionsDialog::OnApplyButton()
{
    qDebug("Apply!!");
}

void OptionsDialog::InitOptionsDialog()
{
    ui->_chkAutoSave->setChecked(_settings->GetAutoSave());
    ui->_spnAutoSaveMin->setValue(_settings->GetAutoSaveInterval());
    ui->_chkFirstLoc->setChecked(_settings->GetCreateFirstLoc());
    ui->_txtNameFirsLoc->setText(_settings->GetFirstLocName());
    ui->_chkDescOfLoc->setChecked(_settings->GetShowShortLocsDescs());
    ui->_chkOpeningLoc->setChecked(_settings->GetOpenNewLoc());
    ui->_chkOpeningAct->setChecked(_settings->GetOpenNewAct());
    ui->_chkOnLocActIcons->setChecked(_settings->GetShowLocsIcons());
    ui->_chkLocDescVisible->setChecked(_settings->GetLocDescVisible());
    ui->_chkLocActsVisible->setChecked(_settings->GetLocActsVisible());
    ui->_chkOpenLastGame->setChecked(_settings->GetOpenLastGame());


    ui->_txtFontBase->setText(_settings->GetFont(SYNTAX_BASE).family());
    ui->_txtFontBase->setFont(_settings->GetFont(SYNTAX_BASE));
    ui->_txtFontBase->SetBackColor(_settings->GetTextBackColor());
    ui->_txtFontBase->SetFontColor(_settings->GetColor(SYNTAX_BASE));
    ui->_txtFontStatements->setText(_settings->GetFont(SYNTAX_STATEMENTS).family());
    ui->_txtFontStatements->setFont(_settings->GetFont(SYNTAX_STATEMENTS));
    ui->_txtFontStatements->SetBackColor(_settings->GetTextBackColor());
    ui->_txtFontStatements->SetFontColor(_settings->GetColor(SYNTAX_STATEMENTS));
    ui->_txtFontFunctions->setText(_settings->GetFont(SYNTAX_FUNCTIONS).family());
    ui->_txtFontFunctions->setFont(_settings->GetFont(SYNTAX_FUNCTIONS));
    ui->_txtFontFunctions->SetBackColor(_settings->GetTextBackColor());
    ui->_txtFontFunctions->SetFontColor(_settings->GetColor(SYNTAX_FUNCTIONS));
    ui->_txtFontSysVariables->setText(_settings->GetFont(SYNTAX_SYS_VARIABLES).family());
    ui->_txtFontSysVariables->setFont(_settings->GetFont(SYNTAX_SYS_VARIABLES));
    ui->_txtFontSysVariables->SetBackColor(_settings->GetTextBackColor());
    ui->_txtFontSysVariables->SetFontColor(_settings->GetColor(SYNTAX_SYS_VARIABLES));
    ui->_txtFontStrings->setText(_settings->GetFont(SYNTAX_STRINGS).family());
    ui->_txtFontStrings->setFont(_settings->GetFont(SYNTAX_STRINGS));
    ui->_txtFontStrings->SetBackColor(_settings->GetTextBackColor());
    ui->_txtFontStrings->SetFontColor(_settings->GetColor(SYNTAX_STRINGS));
    ui->_txtFontNumbers->setText(_settings->GetFont(SYNTAX_NUMBERS).family());
    ui->_txtFontNumbers->setFont(_settings->GetFont(SYNTAX_NUMBERS));
    ui->_txtFontNumbers->SetBackColor(_settings->GetTextBackColor());
    ui->_txtFontNumbers->SetFontColor(_settings->GetColor(SYNTAX_NUMBERS));
    ui->_txtFontOptsBrts->setText(_settings->GetFont(SYNTAX_OPERATIONS).family());
    ui->_txtFontOptsBrts->setFont(_settings->GetFont(SYNTAX_OPERATIONS));
    ui->_txtFontOptsBrts->SetBackColor(_settings->GetTextBackColor());
    ui->_txtFontOptsBrts->SetFontColor(_settings->GetColor(SYNTAX_OPERATIONS));
    ui->_txtFontMarks->setText(_settings->GetFont(SYNTAX_LABELS).family());
    ui->_txtFontMarks->setFont(_settings->GetFont(SYNTAX_LABELS));
    ui->_txtFontMarks->SetBackColor(_settings->GetTextBackColor());
    ui->_txtFontMarks->SetFontColor(_settings->GetColor(SYNTAX_LABELS));
    ui->_txtFontComments->setText(_settings->GetFont(SYNTAX_COMMENTS).family());
    ui->_txtFontComments->setFont(_settings->GetFont(SYNTAX_COMMENTS));
    ui->_txtFontComments->SetBackColor(_settings->GetTextBackColor());
    ui->_txtFontComments->SetFontColor(_settings->GetColor(SYNTAX_COMMENTS));

    ui->_colorBaseBack->SetBackColor(_settings->GetBaseBackColor());
    ui->_colorTextBack->SetBackColor(_settings->GetTextBackColor());
    ui->_colorBaseFont->SetBackColor(_settings->GetColor(SYNTAX_BASE));
    ui->_colorStatements->SetBackColor(_settings->GetColor(SYNTAX_STATEMENTS));
    ui->_colorFunctions->SetBackColor(_settings->GetColor(SYNTAX_FUNCTIONS));
    ui->_colorSysVariables->SetBackColor(_settings->GetColor(SYNTAX_SYS_VARIABLES));
    ui->_colorStrings->SetBackColor(_settings->GetColor(SYNTAX_STRINGS));
    ui->_colorNumbers->SetBackColor(_settings->GetColor(SYNTAX_NUMBERS));
    ui->_colorOptsBrts->SetBackColor(_settings->GetColor(SYNTAX_OPERATIONS));
    ui->_colorMarks->SetBackColor(_settings->GetColor(SYNTAX_LABELS));
    ui->_colorComments->SetBackColor(_settings->GetColor(SYNTAX_COMMENTS));

    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);
}