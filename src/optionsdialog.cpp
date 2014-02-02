#include "optionsdialog.h"
#include "ui_optionsdialog.h"

OptionsDialog::OptionsDialog(IControls *_control, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);

    m_control = _control;

    UpdateColors();
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

void OptionsDialog::UpdateColors()
{
    QPalette pal = ui->widget->palette();
    pal.setColor(QPalette::Window, m_control->GetSettings()->GetBaseBackColor());
    ui->widget->setPalette(pal);

    pal = ui->widget_2->palette();
    pal.setColor(QPalette::Window, m_control->GetSettings()->GetTextBackColor());
    ui->widget_2->setPalette(pal);

    pal = ui->widget_3->palette();
    pal.setColor(QPalette::Window, m_control->GetSettings()->GetColor(SYNTAX_BASE));
    ui->widget_3->setPalette(pal);

    pal = ui->widget_4->palette();
    pal.setColor(QPalette::Window, m_control->GetSettings()->GetColor(SYNTAX_STATEMENTS));
    ui->widget_4->setPalette(pal);

    pal = ui->widget_5->palette();
    pal.setColor(QPalette::Window, m_control->GetSettings()->GetColor(SYNTAX_FUNCTIONS));
    ui->widget_5->setPalette(pal);

    pal = ui->widget_6->palette();
    pal.setColor(QPalette::Window, m_control->GetSettings()->GetColor(SYNTAX_SYS_VARIABLES));
    ui->widget_6->setPalette(pal);

    pal = ui->widget_7->palette();
    pal.setColor(QPalette::Window, m_control->GetSettings()->GetColor(SYNTAX_STRINGS));
    ui->widget_7->setPalette(pal);

    pal = ui->widget_8->palette();
    pal.setColor(QPalette::Window, m_control->GetSettings()->GetColor(SYNTAX_NUMBERS));
    ui->widget_8->setPalette(pal);

    pal = ui->widget_9->palette();
    pal.setColor(QPalette::Window, m_control->GetSettings()->GetColor(SYNTAX_OPERATIONS));
    ui->widget_9->setPalette(pal);

    pal = ui->widget_10->palette();
    pal.setColor(QPalette::Window, m_control->GetSettings()->GetColor(SYNTAX_LABELS));
    ui->widget_10->setPalette(pal);

    pal = ui->widget_11->palette();
    pal.setColor(QPalette::Window, m_control->GetSettings()->GetColor(SYNTAX_COMMENTS));
    ui->widget_11->setPalette(pal);
}
