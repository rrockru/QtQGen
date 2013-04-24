#ifndef KEYWORDSTORE_H
#define KEYWORDSTORE_H

namespace Ui
{
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


        QList<Keyword> _keywords;
    };
} // namespace Ui

#endif // KEYWORDSTORE_H
