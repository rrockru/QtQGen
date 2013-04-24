#ifndef QSPHIGHLIGHTER_H
#define QSPHIGHLIGHTER_H

#include "IControls.h"

namespace Ui
{
    class QspHighlighter : public QSyntaxHighlighter
    {
        Q_OBJECT

    public:
        QspHighlighter(IControls* controls, QTextDocument *parent = 0);

    private:
        struct HighlightingRule
        {
            QRegExp pattern;
            QTextCharFormat format;
        };
        QVector<HighlightingRule> highlightingRules;

        QTextCharFormat keywordFormat;
        QTextCharFormat textFormat;
        QTextCharFormat numberFormat;
        QTextCharFormat commentFormat;

        IControls* _controls;

    protected:
        void highlightBlock(const QString &text);
    };
} // namespace Ui

#endif // QSPHIGHLIGHTER_H
