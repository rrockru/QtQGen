#ifndef _SYNTAX_TEXT_BOX_
#define _SYNTAX_TEXT_BOX_

#include "IControls.h"

namespace Ui
{
    enum
    {
        SYNTAX_FOLD_MARGIN = 1,
        SYNTAX_NUM_MARGIN
    };

    enum
    {
        SYNTAX_STYLE_SIMPLE =			0,
        SYNTAX_STYLE_COLORED =			1 << 0,
        SYNTAX_STYLE_NOHOTKEYS =		1 << 1,
        SYNTAX_STYLE_SIMPLEMENU =		1 << 2,
        SYNTAX_STYLE_NOSCROLLBARS =	1 << 3,
        SYNTAX_STYLE_NOMARGINS =		1 << 4,
        SYNTAX_STYLE_NOHELPTIPS =		1 << 5
    };

    class SyntaxTextBox :
        public QPlainTextEdit
	{
        Q_OBJECT

	public:
        SyntaxTextBox(QWidget *parent, IControls *controls, int style);

        bool IsModified() { return _isChanged; }
        void SetModified(bool modified) {_isChanged = modified; }

	private:
		IControls *_controls;

		int _style;
        bool _isChanged;

    private slots:
        void OnTextChange();
	};
}

#endif //_SYNTAX_TEXT_BOX_


