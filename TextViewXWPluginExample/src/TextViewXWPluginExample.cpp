#include "TextViewXWPluginExample.h"

// cumbia-tango
#include <cuserviceprovider.h>
#include <cumacros.h>
// cumbia-tango

#include <QGridLayout>
#include <QVariant>
#include <QCoreApplication>
#include <quxtrawidgetpluginloader.h>

RTPlotXWPluginExample::RTPlotXWPluginExample(CumbiaTango *cut, QWidget *parent) :
    QWidget(parent)
{
    // cumbia-tango
    cu_t = cut;
    m_log = new CuLog(&m_log_impl);
    cu_t->getServiceProvider()->registerService(CuServices::Log, m_log);
    // cumbia-tango

    QGridLayout *lo = new QGridLayout(this);
    QuXtraWidgetPluginLoader xwpl;
    QuXtraWidgetPluginI *pi = xwpl.getPlugin("QuTextView");
    if(pi) {
        QWidget *textViewer = pi->create("QuTextView", parent, cut, this->cu_tango_r_fac);
        lo->addWidget(textViewer);
        textViewer->setObjectName("textViewer");
        // either use the "source" property
        textViewer->setProperty("source", qApp->arguments()[1]);
        // or
        // dynamic_cast<QuXtraWidgetI *>(textViewer)->setLink(qApp->arguments().at(1));
    }

}

RTPlotXWPluginExample::~RTPlotXWPluginExample()
{

}
