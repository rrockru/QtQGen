#include "keywordsstore.h"

namespace Ui
{
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
                result << "\\b" + keyword.word + "\\b";
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
}
