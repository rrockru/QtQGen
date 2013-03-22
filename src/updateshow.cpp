#include "updateshow.h"

namespace Ui
{

    UpdateShow::UpdateShow(const QString &ver, const QString &desc, QWidget *parent) :
        QDialog(parent)
    {
        QVBoxLayout *vbox = new QVBoxLayout;
        setWindowTitle(tr("Update ") + ver);
        QLabel *label = new QLabel(tr("Available new version. Changes:"));
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
