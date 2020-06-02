#pragma once
#include "visualnodebase.h"
#include "contextfilternode.h"
#include "processingstyle.h"
#include "contextfiltersettings.h"
#include "visualcontextfilterpropertieswidget.h"
#include "globalconfig.h"
class VisualContextFilter : public VisualNodeBase, public ProcessingStyle
{
    Q_OBJECT
public:
    VisualContextFilter(FlowObjects *_flowObjects);
    VisualContextFilter(FlowObjects *_flowObjects,QJsonObject &baseJson, QJsonObject &derivedJson, QJsonObject &settingsJson, DeserializationHandler &handler);
    ~VisualContextFilter();

    QJsonObject* serialize(SerializationHandler &handler);

protected:
    PropertyWidgetBase* loadPropertiesWidget(QWidget* parent);
    void releasePropertiesWidget();

    ContextFilterNode* node = nullptr;
    ContextFilterSettings* settings = nullptr;
    void activate();
    VisualNodeBase *clone();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    void construct();
    bool activated = false;
    VisualContextFilterPropertiesWidget *propertyWidget = nullptr;
};

