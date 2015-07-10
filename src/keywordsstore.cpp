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

#include "keywordsstore.h"

bool KeywordsStore::Load(const QString &filename)
{
    QDomDocument keywordsFile;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return false;
    if (!keywordsFile.setContent(file.readAll())) {
        file.close();
        return false;
    }
    file.close();

    QDomElement root = keywordsFile.documentElement();
    if (root.nodeName() != "QGen-keywords") return false;

    QDomNode node = root.firstChild();
    while(!node.isNull()) {
        QDomElement element = node.toElement();
        if(!element.isNull()) {
            if (element.nodeName() == "Statements")
            {
                ParseKeywords(element, STATEMENT);
            }
            else if (element.nodeName() == "Expressions")
            {
                ParseKeywords(element, EXPRESSION);
            }
            else if (element.nodeName() == "Variables")
            {
                ParseKeywords(element, VARIABLE);
            }
        }
        node = node.nextSibling();
    }
    return true;
}

void KeywordsStore::ParseKeywords(const QDomElement &node, KeywordType type)
{
    QDomElement keywordElement = node.firstChildElement("Keyword");
    while (!keywordElement.isNull()) {
        Keyword keyword;
        keyword.word = keywordElement.attribute("name");
        keyword.desc = keywordElement.attribute("desc");
        keyword.type = type;
        _keywords << keyword;
        keywordElement = keywordElement.nextSiblingElement("Keyword");
    }
}

QStringList KeywordsStore::GetWords(KeywordType type) const
{
    QStringList result;

    QListIterator<Keyword> iter(_keywords);
    while (iter.hasNext())
    {
        Keyword keyword = iter.next();
        if (keyword.type == type)
        {
            if (keyword.word.contains('$'))
                keyword.word.replace('$', '\\$');
            result << keyword.word;
        }
    }
    return result;
}

QString KeywordsStore::FindTip( const QString &word ) const
{
    QString result;
    QString w = word.toLower();

    QListIterator<Keyword> iter(_keywords);
    while (iter.hasNext())
    {
        Keyword keyword = iter.next();
        if (keyword.word == w)
        {
            result = keyword.desc;
        }
    }

    return result;
}

QStringList KeywordsStore::GetWordsForCompletion() const
{
    QStringList result;

    QListIterator<Keyword> iter(_keywords);
    while (iter.hasNext())
    {
        Keyword keyword = iter.next();
        if (keyword.type == EXPRESSION || keyword.type == VARIABLE || keyword.type == STATEMENT)
        {
            result << keyword.word;
        }
    }
    return result;
}

bool KeywordsStore::ContainsPrefix(const QString text)
{
    QListIterator<Keyword> iter(_keywords);
    while (iter.hasNext())
    {
        Keyword keyword = iter.next();
        if (keyword.word.startsWith(text, Qt::CaseInsensitive))
        {
            return true;
        }
    }
    return false;
}
