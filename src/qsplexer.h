#ifndef QSPLEXER_H
#define QSPLEXER_H

#include <Qsci/qscilexercustom.h>

#include "icontrols.h"
#include "keywordsstore.h"

class QSPLexer : public QsciLexerCustom
{
    Q_OBJECT

public:
    explicit QSPLexer(IControls *controls, QObject *parent);
    ~QSPLexer();

    void styleText(int start, int end);
    void paintKeywords(const QString &source, int start);
    const char * language() const;
    QColor defaultColor(int style) const;
    QColor defaultPaper(int style) const;
    QFont defaultFont(int style) const;
    QString description(int style) const;

    enum {
        Statement = 1,
        Function,
        SysVariable,
        String,
        Number,
        Operation,
        Label,
        Comment,

        Default = 0
    };

private:
    IControls       *_controls;
    KeywordsStore   *_keywordsStore;

//    QSPLexer(const QSPLexer &);
//    QSPLexer &operator= (const QSPLexer &);
};

#endif // QSPLEXER_H
