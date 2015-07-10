#include <Qsci/qsciscintilla.h>
#include "qsplexer.h"

QSPLexer::QSPLexer(IControls *controls, QObject *parent) :
    QsciLexerCustom(parent)
{
    _controls = controls;
    _keywordsStore = _controls->GetKeywordsStore();
}

QSPLexer::~QSPLexer()
{
    ;
}

void QSPLexer::styleText(int start, int end)
{
    if(!editor())
        return;

    char * data = new char[end - start + 1];

    editor()->SendScintilla(QsciScintilla::SCI_GETTEXTRANGE, start, end, data);
    QString source(data);
    delete [] data;
    if(source.isEmpty())
        return;

    paintKeywords(source, start);
}

void QSPLexer::paintKeywords(const QString &source, int start)
{
    foreach(QString word, _keywordsStore->GetWords(STATEMENT)) {
        if(source.contains(word)) {
            int p = source.count(word);
            int index = 0;
            while(p != 0) {
                int begin = source.indexOf(word, index);
                index = begin+1;

                startStyling(start + begin);
                setStyling(word.length(), Statement);
                startStyling(start + begin);

                p--;
            }
        }
    }

    foreach(QString word, _keywordsStore->GetWords(EXPRESSION)) {
        if(source.contains(word)) {
            int p = source.count(word);
            int index = 0;
            while(p != 0) {
                int begin = source.indexOf(word, index);
                index = begin+1;

                startStyling(start + begin);
                setStyling(word.length(), Function);
                startStyling(start + begin);

                p--;
            }
        }
    }

    foreach(QString word, _keywordsStore->GetWords(VARIABLE)) {
        if(source.contains(word)) {
            int p = source.count(word);
            int index = 0;
            while(p != 0) {
                int begin = source.indexOf(word, index);
                index = begin+1;

                startStyling(start + begin);
                setStyling(word.length(), SysVariable);
                startStyling(start + begin);

                p--;
            }
        }
    }
}

QColor QSPLexer::defaultColor(int style) const
{
    switch(style) {
        case Statement:
            return _controls->GetSettings()->GetColor(SYNTAX_STATEMENTS);
        case Function:
            return _controls->GetSettings()->GetColor(SYNTAX_FUNCTIONS);
        case SysVariable:
            return _controls->GetSettings()->GetColor(SYNTAX_SYS_VARIABLES);
    }
    return  _controls->GetSettings()->GetColor(SYNTAX_BASE);
}

QColor QSPLexer::defaultPaper(int style) const
{
    return  _controls->GetSettings()->GetTextBackColor();
}

QFont QSPLexer::defaultFont(int style) const
{
    switch(style) {
        case Statement:
            return _controls->GetSettings()->GetFont(SYNTAX_STATEMENTS);
        case Function:
            return _controls->GetSettings()->GetFont(SYNTAX_FUNCTIONS);
        case SysVariable:
            return _controls->GetSettings()->GetFont(SYNTAX_SYS_VARIABLES);
    }
    return  _controls->GetSettings()->GetFont(SYNTAX_BASE);
}

QString QSPLexer::description(int style) const
{
    switch(style) {
        case Default:
            return "Default";
        case Statement:
            return "Statement";
    }
    return QString(style);
}

const char * QSPLexer::language() const
{
    return "QSP";
}
