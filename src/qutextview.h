#ifndef TINTERVALSLIDER_H
#define TINTERVALSLIDER_H

#include <QTextEdit>
#include <cudata.h>
#include <cudatalistener.h>
#include <quxtrawidgetplugininterface.h>

class Cumbia;
class CuControlsReaderFactoryI;
class QuTextViewPrivate;

class QuTextView : public QTextEdit, public QuXtraWidgetI, public CuDataListener
{
    Q_OBJECT
    Q_PROPERTY(QString source READ link WRITE setLink)

public:
    QuTextView(QWidget *parent, Cumbia *cumbia, const CuControlsReaderFactoryI &r_fac);
    QuTextView(QWidget *parent, CumbiaPool *cumbia_pool, const CuControlsFactoryPool &fpool);

    ~QuTextView();

    // QuXtraWidgetI interface
    CuContext *getContext() const;
    QString link() const;
    void setLink(const QString &s);
    void unsetLink();
    QuXtraWidgetI::Type getType() const;

    // CuDataListener interface
    void onUpdate(const CuData &data);

protected:
    void contextMenuEvent(QContextMenuEvent* e);

protected slots:

private:
    void m_init();

    QuTextViewPrivate *d;
};















#endif // TINTERVALSLIDER_H
