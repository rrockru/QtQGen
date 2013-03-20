#include "stdafx.h"
#include "updaterdescriptiondlg.h"
#include "game.h"

namespace Ui
{

    UpdaterDescriptionDlg::UpdaterDescriptionDlg(QWidget *parent) :
        QDialog(parent)
    {
        QVBoxLayout *vbox = new QVBoxLayout;
        setWindowTitle(tr("Update ") + QString::fromWCharArray(QGEN_VER));
        QLabel *label = new QLabel(tr("Input description for update:"));
        text = new QTextEdit(this);
        QHBoxLayout *hbox = new QHBoxLayout;

        QPushButton *okButton = new QPushButton("OK", this);
        connect(okButton, SIGNAL(clicked()), this, SLOT(OnOkButton()));

        QPushButton *cancelButton = new QPushButton(tr("Cancel"), this);
        connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

        hbox->addWidget(okButton);
        hbox->addWidget(cancelButton);

        vbox->addWidget(label);
        vbox->addWidget(text);
        vbox->addLayout(hbox);

        setLayout(vbox);

        resize(300, 300);
        QRect _defRect = geometry();
        _defRect.moveCenter(QApplication::desktop()->availableGeometry().center());
        setGeometry(_defRect);
    }

    void UpdaterDescriptionDlg::OnOkButton()
    {
        _resText = text->toPlainText().replace("\n", "<br/>");
        accept();
    }

} // namespace Ui
