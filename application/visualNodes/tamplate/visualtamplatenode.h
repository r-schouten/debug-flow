#pragma once

#include <QJsonObject>
#include "selectionmanager.h"
#include "tamplatenode.h"
#include "tamplatenodepropertieswidget.h"
#include "tamplatenodesettings.h"

#ifdef SOURCE_NODE
    #include "sourcestyle.h"
    #include "visualsourcenodebase.h"
#endif
#ifdef PROCESSING_NODE
    #include "visualnodebase.h"
    #include "processingstyle.h"
#endif
#ifdef OUTPUT_NODE
    #include "outputstyle.h"
    #include "visualoutputnodebase.h"
#endif



#ifdef SOURCE_NODE
    class VisualTamplateNode : public VisualSourceNodeBase
#endif
#ifdef PROCESSING_NODE
    class VisualTamplateNode : public VisualNodeBase
#endif
#ifdef OUTPUT_NODE
    class VisualTamplateNode : public VisualOutputNodeBase
#endif
{
    Q_OBJECT
public:
    VisualTamplateNode(FlowObjects *_flowObjects);
    VisualTamplateNode(FlowObjects *_flowObjects, QJsonObject &baseJson, QJsonObject &derivedJson, QJsonObject &settingsJson, DeserializationHandler &handler);
    VisualNodeBase *clone();

    virtual ~VisualTamplateNode();
    void activate();

    QJsonObject *serialize(SerializationHandler &handler);

    //used by loadStore to check if node is this specific node type, its implemented in the class so its possible to make json files backward compatible when a className change
    static bool classNameEquals(QString name);
protected:
    PropertyWidgetBase *loadPropertiesWidget(QWidget *parent);
    void releasePropertiesWidget();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);


    bool activated = false;
    TamplateNode *node = nullptr;
    TamplateNodeSettings* settings = nullptr;

private:
    void construct();

};

