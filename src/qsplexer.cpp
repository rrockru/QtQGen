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

    clearStyle(start, end);

    paintKeywords(source, start);
    paintNumbers(source, start);
    paintStrings(source, start);
}

void QSPLexer::clearStyle(int start, int end)
{
    startStyling(start);
    setStyling(end - start, SYNTAX_BASE);
    startStyling(end);
}

void QSPLexer::paintKeywords(const QString &source, int start)
{
    foreach(QString word, _keywordsStore->GetWords(STATEMENT)) {
        if(source.contains(QRegExp("\\b" + word + "\\b", Qt::CaseInsensitive))) {
            int p = source.count(QRegExp("\\b" + word + "\\b", Qt::CaseInsensitive));
            int index = 0;
            while(p != 0) {
                int begin = source.indexOf(QRegExp("\\b" + word + "\\b", Qt::CaseInsensitive), index);
                index = begin+1;

                startStyling(start + begin);
                setStyling(word.length(), SYNTAX_STATEMENTS);
                startStyling(start + begin);

                p--;
            }
        }
    }

    foreach(QString word, _keywordsStore->GetWords(EXPRESSION)) {
        if(source.contains(QRegExp("\\b" + word + "\\b", Qt::CaseInsensitive))) {
            int p = source.count(QRegExp("\\b" + word + "\\b", Qt::CaseInsensitive));
            int index = 0;
            while(p != 0) {
                int begin = source.indexOf(QRegExp("\\b" + word + "\\b", Qt::CaseInsensitive), index);
                index = begin+1;

                startStyling(start + begin);
                setStyling(word.length(), SYNTAX_FUNCTIONS);
                startStyling(start + begin);

                p--;
            }
        }
    }

    foreach(QString word, _keywordsStore->GetWords(VARIABLE)) {
        if(source.contains(QRegExp("\\b" + word + "\\b", Qt::CaseInsensitive))) {
            int p = source.count(QRegExp("\\b" + word + "\\b", Qt::CaseInsensitive));
            int index = 0;
            while(p != 0) {
                int begin = source.indexOf(QRegExp("\\b" + word + "\\b", Qt::CaseInsensitive), index);
                index = begin+1;

                startStyling(start + begin);
                setStyling(word.length(), SYNTAX_SYS_VARIABLES);
                startStyling(start + begin);

                p--;
            }
        }
    }
}

void QSPLexer::paintStrings(const QString &source, int start)
{
    if (source.contains("'"))
    {
        int p = source.count("'");
        int index = 0;
        while (p > 0)
        {
            int begin = source.indexOf("'", index);
            index = begin + 1;

            int end = source.indexOf("'", index);
            if (end == -1)
                end = source.length();
            else
                end++;
            int len = end - begin;

            startStyling(start + begin);
            setStyling(len, SYNTAX_STRINGS);
            startStyling(start + begin);

            p = p - 2;
        }
    }
}

void QSPLexer::paintNumbers(const QString &source, int start)
{
    QRegExp rx("\\d+");
    if (source.contains(rx))
    {
        int p = source.count(rx);
        int index = 0;
        while(p != 0) {
            int begin = source.indexOf(rx, index);
            index = begin + 1;

            startStyling(start + begin);
            setStyling(rx.matchedLength(), SYNTAX_NUMBERS);
            startStyling(start + begin);

            p--;
        }
    }
}

QColor QSPLexer::defaultColor(int style) const
{
    switch(style)
    {
        case SYNTAX_STATEMENTS:
            return _controls->GetSettings()->GetColor(SYNTAX_STATEMENTS);
        case SYNTAX_FUNCTIONS:
            return _controls->GetSettings()->GetColor(SYNTAX_FUNCTIONS);
        case SYNTAX_SYS_VARIABLES:
            return _controls->GetSettings()->GetColor(SYNTAX_SYS_VARIABLES);
        case SYNTAX_STRINGS:
            return _controls->GetSettings()->GetColor(SYNTAX_STRINGS);
        case SYNTAX_NUMBERS:
            return _controls->GetSettings()->GetColor(SYNTAX_NUMBERS);
    }
    return  _controls->GetSettings()->GetColor(SYNTAX_BASE);
}

QColor QSPLexer::defaultPaper(int style) const
{
    return  _controls->GetSettings()->GetTextBackColor();
}

QFont QSPLexer::defaultFont(int style) const
{
    switch(style)
    {
        case SYNTAX_STATEMENTS:
            return _controls->GetSettings()->GetFont(SYNTAX_STATEMENTS);
        case SYNTAX_FUNCTIONS:
            return _controls->GetSettings()->GetFont(SYNTAX_FUNCTIONS);
        case SYNTAX_SYS_VARIABLES:
            return _controls->GetSettings()->GetFont(SYNTAX_SYS_VARIABLES);
        case SYNTAX_STRINGS:
            return _controls->GetSettings()->GetFont(SYNTAX_STRINGS);
        case SYNTAX_NUMBERS:
            return _controls->GetSettings()->GetFont(SYNTAX_NUMBERS);
    }
    return  _controls->GetSettings()->GetFont(SYNTAX_BASE);
}

QString QSPLexer::description(int style) const
{
    switch(style)
    {
        case SYNTAX_BASE:
            return "Base";
        case SYNTAX_STATEMENTS:
            return "Statement";
        case SYNTAX_FUNCTIONS:
            return "Function";
        case SYNTAX_SYS_VARIABLES:
            return "SysVar";
        case SYNTAX_STRINGS:
            return "String";
        case SYNTAX_NUMBERS:
            return "Number";
    }
    return QString();
}

const char * QSPLexer::language() const
{
    return "QSP";
}
