#include "textview-xwidgetplugin.h"
#include <QClipboard>
#include <cucontrolsreader_abs.h>
#include <cucontrolswriter_abs.h>
#include <QApplication>
#include <cucontext.h>
#include "qutextview.h"
#include <cumacros.h>

TextViewXWidgetPlugin::TextViewXWidgetPlugin(QObject *parent)
    : QObject (parent)
{

}

TextViewXWidgetPlugin::~TextViewXWidgetPlugin()
{

}

QWidget *TextViewXWidgetPlugin::create(const QString &name, QWidget *parent, Cumbia *cumbia, const CuControlsReaderFactoryI &r_fac)
{
    if(name == "QuTextView")
        return new QuTextView(parent, cumbia, r_fac);
    perr("TextViewXWidgetPlugin.create: TextViewXWidgetPlugin does not provide the widget \"%s\"", qstoc(name));
    return nullptr;
}

QWidget *TextViewXWidgetPlugin::create(const QString &name, QWidget *parent, CumbiaPool *cumbia_pool,
                                                const CuControlsFactoryPool &fpool)
{
    if(name == "QuTextView")
        return new QuTextView(parent, cumbia_pool, fpool);
    perr("TextViewXWidgetPlugin.create: TextViewXWidgetPlugin does not provide the widget \"%s\"", qstoc(name));
    return nullptr;
}

QString TextViewXWidgetPlugin::name() const
{
    return "TextViewXWidgetPlugin";
}

QStringList TextViewXWidgetPlugin::catalogue() const
{
    return QStringList() << "QuTextView";
}
