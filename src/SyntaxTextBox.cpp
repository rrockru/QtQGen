#include "stdafx.h"
#include "SyntaxTextBox.h"

namespace Ui
{
	SyntaxTextBox::SyntaxTextBox(QWidget *parent, IControls *controls, int style) : QsciScintilla(parent)
	{
		_controls = controls;
		_style = style;

		setEolMode(QsciScintilla::EolUnix);
		setWrapMode(WrapMode::WrapWord);
		setUtf8(true);
		setMarginWidth(1, 0);

		if (_style & SYNTAX_STYLE_NOSCROLLBARS)
		{
			SendScintilla(SCI_SETHSCROLLBAR, 0);
			SendScintilla(SCI_SETVSCROLLBAR, 0);
		}
		/*if (!(_style & SYNTAX_STYLE_SIMPLEMENU))
		{
			UsePopUp(false);
		}*/
		if (_style & SYNTAX_STYLE_COLORED)
		{
			SendScintilla(SCI_SETLEXER, SCLEX_VB);
			SendScintilla(SCI_SETSCROLLWIDTH, -1);
			SendScintilla(SCI_SETSCROLLWIDTHTRACKING, true);

			setIndentationGuides(true);

			if (!(_style & SYNTAX_STYLE_NOMARGINS))
			{
				SendScintilla(SCI_SETFOLDFLAGS, SC_FOLDLEVELBASE);

				setMarginType(SYNTAX_FOLD_MARGIN, QsciScintilla::SymbolMargin);
				setMarginMarkerMask(SYNTAX_FOLD_MARGIN, SC_MASK_FOLDERS);
				setMarginWidth(SYNTAX_FOLD_MARGIN, 20);

				setMarginType(SYNTAX_NUM_MARGIN, QsciScintilla::NumberMargin);
				setMarginWidth(SYNTAX_NUM_MARGIN, 40);

				markerDefine(SC_MARKNUM_FOLDER, SC_MARK_PLUS);
				markerDefine(SC_MARKNUM_FOLDEROPEN, SC_MARK_MINUS);
				markerDefine(SC_MARKNUM_FOLDEREND, SC_MARK_EMPTY);
				markerDefine(SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_EMPTY);
				markerDefine(SC_MARKNUM_FOLDEROPENMID, SC_MARK_EMPTY);
				markerDefine(SC_MARKNUM_FOLDERSUB, SC_MARK_EMPTY);
				markerDefine(SC_MARKNUM_FOLDERTAIL, SC_MARK_EMPTY);

				SendScintilla(SCI_SETFOLDFLAGS, SC_FOLDFLAG_LINEAFTER_CONTRACTED);
				setMarginSensitivity(SYNTAX_FOLD_MARGIN, true);
			}

			SendScintilla(SCI_AUTOCSETCHOOSESINGLE, true);
			SendScintilla(SCI_AUTOCSETIGNORECASE, true);
			SendScintilla(SCI_AUTOCSETDROPRESTOFWORD, true);
		}
	}
}