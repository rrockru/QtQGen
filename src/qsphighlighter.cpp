// Copyright (C) 2013
// Shchannikov Dmitry (rrock DOT ru AT gmail DOT com)
// Nex (nex AT otaku DOT ru)
/*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#include "qsphighlighter.h"

QspHighlighter::QspHighlighter(IControls* controls, QTextDocument *parent)
    :QSyntaxHighlighter(parent)
{
    _controls = controls;

    Update();
    _controls->GetSettings()->AddObserver(this);
}

void QspHighlighter::Update(bool isFromObservable)
{
    HighlightingRule rule;
    Settings *settings = _controls->GetSettings();

    highlightingRules.clear();

    // !!! ВАЖЕН ПОРЯДОК ДОБАВЛЕНИЯ ПРАВИЛ (так как идет последовательное перекрашивание)
    // сначала кейворды

    keywordFormat.setForeground(settings->GetColor(SYNTAX_STATEMENTS));
    keywordFormat.setFont(settings->GetFont(SYNTAX_STATEMENTS));
    QStringList keywordPatterns;
    keywordPatterns = _controls->GetKeywordsStore()->GetWords(STATEMENT);
    keywordPatterns << _controls->GetKeywordsStore()->GetWords(EXPRESSION);
    keywordPatterns << _controls->GetKeywordsStore()->GetWords(VARIABLE);

    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // потом числа
    numberFormat.setForeground(settings->GetColor(SYNTAX_NUMBERS));
    numberFormat.setFont(settings->GetFont(SYNTAX_NUMBERS));
    rule.pattern = QRegExp("\\d+");
    rule.format = numberFormat;
    highlightingRules.append(rule);

    // потом строки
    textFormat.setForeground(settings->GetColor(SYNTAX_STRINGS));
    textFormat.setFont(settings->GetFont(SYNTAX_STRINGS));
    rule.pattern = QRegExp("\'[^\']*\'"); // текст ищется только по одинарным ковычкам
    rule.format = textFormat;
    highlightingRules.append(rule);

    // потом комментарии
    commentFormat.setForeground(settings->GetColor(SYNTAX_COMMENTS));
    commentFormat.setFont(settings->GetFont(SYNTAX_COMMENTS));
    rule.pattern = QRegExp("^\\!.*");
    rule.format = commentFormat;
    highlightingRules.append(rule);

    rehighlight();
}

void QspHighlighter::highlightBlock(const QString &text)
{
    QString txt = text.toLower().replace('$', '\\$'); // хак для распознавания слов, начинающихся с $

    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(txt);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(txt, index + length);
        }
    }
    setCurrentBlockState(QSPHIGHTLIGHTDONE);

    // Проверка на многостройный текст
    QRegExp expression("^[^\']*\'[^\']*$"); // сначала ищем строки в которых только один символ '
    int index = expression.indexIn(txt);
    if (index >= 0)
    {
        QRegExp expr("\'"); // а теперь ищем саму ковычку внутри строки
        index = expr.indexIn(expression.capturedTexts().at(0));
        if (previousBlockState() == QSPHIGHTLIGHTMULTILINETEXT)
        {
           setFormat(0, index + 1, textFormat);
        }
        else
        {
            setFormat(index, txt.length(), textFormat);
            setCurrentBlockState(QSPHIGHTLIGHTMULTILINETEXT);
            return;
        }
    }
    else
    {
        if (previousBlockState() == QSPHIGHTLIGHTMULTILINETEXT)
        {
            setCurrentBlockState(QSPHIGHTLIGHTMULTILINETEXT);
            setFormat(0, txt.length(), textFormat);
            return;
        }
    }
    // конец проверки на многострочный текст
}
