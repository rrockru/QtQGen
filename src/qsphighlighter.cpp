#include "qsphighlighter.h"

namespace Ui
{
    QspHighlighter::QspHighlighter(IControls* controls, QTextDocument *parent)
        :QSyntaxHighlighter(parent)
    {
        _controls = controls;

        HighlightingRule rule;

        keywordFormat.setForeground(Qt::blue);
        keywordFormat.setFontWeight(QFont::Bold);
        QStringList keywordPatterns;
        keywordPatterns = _controls->GetKeywordsStore()->GetWords(STATEMENT);
        keywordPatterns << _controls->GetKeywordsStore()->GetWords(EXPRESSION);
        keywordPatterns << _controls->GetKeywordsStore()->GetWords(VARIABLE);

        foreach (const QString &pattern, keywordPatterns) {
            rule.pattern = QRegExp(pattern);
            rule.format = keywordFormat;
            highlightingRules.append(rule);
        }

        numberFormat.setForeground(Qt::darkMagenta);
        numberFormat.setFontWeight(QFont::Bold);
        rule.pattern = QRegExp("\\d+");
        rule.format = numberFormat;
        highlightingRules.append(rule);

        textFormat.setForeground(Qt::darkGreen);
        rule.pattern = QRegExp("\'[^\']*\'");
        rule.format = textFormat;
        highlightingRules.append(rule);

        commentFormat.setForeground(Qt::gray);
        rule.pattern = QRegExp("^\\!.*");
        rule.format = commentFormat;
        highlightingRules.append(rule);
    }

    void QspHighlighter::highlightBlock(const QString &text)
    {
        QString txt = text.toLower().replace('$', '\\$');
        foreach (const HighlightingRule &rule, highlightingRules) {
            QRegExp expression(rule.pattern);
            int index = expression.indexIn(txt);
            while (index >= 0) {
                int length = expression.matchedLength();
                setFormat(index, length, rule.format);
                index = expression.indexIn(txt, index + length);
            }
        }
        setCurrentBlockState(0);
    }
}
