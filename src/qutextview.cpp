#include "qutextview.h"
#include <QHBoxLayout>
#include <quwatcher.h>
#include <quwriter.h>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <elettracolors.h>
#include <cucontrolsreader_abs.h>
#include <qustring.h>
#include <qustringlist.h>
#include <cucontextmenu.h>
#include <culinkstats.h>

class QuTextViewPrivate {
public:
    CuContext *ctx;
};

QuTextView::QuTextView(QWidget *parent, Cumbia *cumbia, const CuControlsReaderFactoryI &r_fac ) :
    QTextEdit(parent)
{
    d = new QuTextViewPrivate();
    d->ctx = new CuContext(cumbia, r_fac);
    m_init();
}

QuTextView::QuTextView(QWidget *parent, CumbiaPool *cumbia_pool, const CuControlsFactoryPool &fpool) :
    QTextEdit(parent)
{
    d = new QuTextViewPrivate();
    d->ctx = new CuContext(cumbia_pool, fpool);
    m_init();
}

QuTextView::~QuTextView()
{
    if(d->ctx)
        delete d->ctx;
    delete d;
}

void QuTextView::m_init()
{
    setReadOnly(true);
}

CuContext *QuTextView::getContext() const
{
    return d->ctx;
}

QString QuTextView::link() const
{
    if(CuControlsReaderA* r = d->ctx->getReader())
        return r->source();
    return "";
}

void QuTextView::setLink(const QString &s)
{
    CuControlsReaderA * r = d->ctx->replace_reader(s.toStdString(), this);
    if(r)
        r->setSource(s);
}

void QuTextView::unsetLink()
{
    d->ctx->disposeReader();
}

QuXtraWidgetI::Type QuTextView::getType() const
{
    return QuXtraWidgetI::Reader;
}

void QuTextView::onUpdate(const CuData &data)
{
    setDisabled(data["err"].toBool());
    // update link statistics
    d->ctx->getLinkStats()->addOperation();
    if(!isEnabled()) {
        setHtml(QuString(data["msg"].toString()));
        d->ctx->getLinkStats()->addError(data["msg"].toString());
    }
    else {
        const CuVariant& va = data["value"];
        if(va.isValid() && va.getFormat() == CuVariant::Scalar)
            setHtml(QuString(data, "value"));
        else if(va.isValid() && va.getFormat() == CuVariant::Vector) {
            QString html = "<ol>\n";
            foreach(QString s, QuStringList(va))
                html += "<li>" + s + "</li>\n";
            html += "</ol>";
            setHtml(html);
        }
    }
    setToolTip(QuString(data, "msg"));
}

void QuTextView::contextMenuEvent(QContextMenuEvent *e)
{
    CuContextMenu* m = findChild<CuContextMenu *>();
    if(!m)
        m = new CuContextMenu(this, d->ctx);
    m->popup(e->globalPos());
}


