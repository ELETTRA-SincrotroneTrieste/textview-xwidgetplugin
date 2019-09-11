#ifndef INTERVALSLIDERXTRAWIDGETPLUGIN_H
#define INTERVALSLIDERXTRAWIDGETPLUGIN_H

#include <quxtrawidgetplugininterface.h>
#include <QAction>
#include <QList>
#include <QObject>

class TextViewXWidgetPlugin : public QObject, public QuXtraWidgetPluginI
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "textview-xwidgetplugin.json")

public:
    explicit TextViewXWidgetPlugin(QObject *parent = nullptr);
    ~TextViewXWidgetPlugin();

    Q_INTERFACES(QuXtraWidgetPluginI)


private:


    // QuXtraWidgetPluginI interface
public:
    QWidget *create(const QString &name, QWidget *parent, Cumbia *cumbia, const CuControlsReaderFactoryI &r_fac);
    QWidget *create(const QString &name, QWidget *parent, CumbiaPool *cumbia_pool, const CuControlsFactoryPool &fpool);
    QString name() const;
    QStringList catalogue() const;
};














#endif // CUMBIACOPYSOURCECTXMENUACTION_H
