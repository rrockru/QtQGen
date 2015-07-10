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

#ifndef KEYWORDSTORE_H
#define KEYWORDSTORE_H

#include <QString>

enum KeywordType
{
    DEFAULT = 0,
    STATEMENT,
    EXPRESSION,
    VARIABLE
};

struct Keyword
{
    QString	word;
    QString	desc;
    KeywordType type;

    Keyword() { }
    Keyword(const QString &word, const QString &desc, KeywordType type)
    {
        this->word = word;
        this->desc = desc;
        this->type = type;
    }
};

class KeywordsStore
{
public:
    KeywordsStore() { }
    bool Load(const QString &filename);
    void ParseKeywords(const QDomElement &node, KeywordType type);
    QStringList GetWords(KeywordType type) const;
    QString FindTip( const QString &word ) const;
    QStringList GetWordsForCompletion() const;
    bool ContainsPrefix(const QString text);

    QList<Keyword> _keywords;
};

#endif // KEYWORDSTORE_H
