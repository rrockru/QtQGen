#include "stdafx.h"
#include "actioncode.h"

namespace Ui
{
	ActionCode::ActionCode(QWidget *parent, ILocationPage *locPage, IControls *controls) : QWidget(parent)
	{
		_controls = controls;
		_locPage = locPage;

        _editor = new SyntaxTextBox(this, _controls, SYNTAX_STYLE_COLORED);
		_pathPicTxtCtrl = new QLineEdit(this);

		QVBoxLayout *vBox = new QVBoxLayout;
		
		QHBoxLayout *hBox = new QHBoxLayout;		
		hBox->addWidget(_pathPicTxtCtrl);
		hBox->addWidget(new QPushButton(tr("Image...")));
		vBox->addLayout(hBox);

		vBox->addWidget(_editor);

		setLayout(vBox);

		setContentsMargins(0, 0, 0, 0);
		vBox->setContentsMargins(0, 0, 0, 0);
	}

	void ActionCode::ClearAction()
	{
		_pathPicTxtCtrl->clear();
		_editor->clear();
		setEnabled(false);
	}

	void ActionCode::LoadAction( size_t actIndex )
	{
		DataContainer *container = _controls->GetContainer();
		size_t locIndex = _locPage->GetLocationIndex();
		_pathPicTxtCtrl->setText(container->GetActionPicturePath(locIndex, actIndex));
        _editor->setPlainText(container->GetActionCode(locIndex, actIndex));
		setEnabled(true);
	}

    void ActionCode::SaveAction( size_t actIndex )
    {
        DataContainer *container = _controls->GetContainer();
        size_t locIndex = _locPage->GetLocationIndex();
//        if (_pathPicTxtCtrl->IsModified())
//        {
//            container->SetActionPicturePath(locIndex, actIndex, _pathPicTxtCtrl->GetValue());
//            _pathPicTxtCtrl->SetModified(false);
//        }
        if (_editor->IsModified())
        {
            container->SetActionCode(locIndex, actIndex, _editor->toPlainText());
            _editor->SetModified(false);
        }
    }

    void ActionCode::SetFocusOnActionCode()
    {
        _editor->setFocus();
    }

}
