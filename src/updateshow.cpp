#include "updateshow.h"

namespace Ui
{

    UpdateShow::UpdateShow(const QString &ver, const QString &desc, bool repair, QWidget *parent) :
        QDialog(parent)
    {
        QLabel *label;
        QVBoxLayout *vbox = new QVBoxLayout;
        setWindowTitle(tr("Update ") + ver);
        if(!repair)
        {
            label = new QLabel(tr("Available new version. Changes:"));
        }
        else
        {
            label = new QLabel(tr("Need to repair"));
        }
        QTextEdit *text = new QTextEdit(this);
        text->setHtml(desc);
        text->setReadOnly(true);
        QHBoxLayout *hbox = new QHBoxLayout;

        QPushButton *okButton = new QPushButton(tr("Install"), this);
        connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));

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

}
