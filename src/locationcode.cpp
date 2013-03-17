#include "stdafx.h"
#include "locationcode.h"

namespace Ui
{
	LocationCode::LocationCode(QWidget *parent, ILocationPage *locPage, IControls *controls) : QWidget(parent)
	{
		_controls = controls;
		_locPage = locPage;

        _editor = new SyntaxTextBox(this, _controls, SYNTAX_STYLE_COLORED);

		QVBoxLayout *vBox = new QVBoxLayout(this);
		vBox->addWidget(new QLabel(tr("Execute on  visit"), this));
		vBox->addWidget(_editor);

		setLayout(vBox);
	}

	void LocationCode::LoadCode()
	{
        _editor->setPlainText(_controls->GetContainer()->GetLocationCode(_locPage->GetLocationIndex()));
	}

    void LocationCode::SaveCode()
    {
        if (_editor->IsModified())
        {
            _controls->GetContainer()->SetLocationCode( _locPage->GetLocationIndex(), _editor->toPlainText() );
            _editor->SetModified(false);
        }
    }
}
