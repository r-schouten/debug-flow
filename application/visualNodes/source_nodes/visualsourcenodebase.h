#pragma once

#include <QPainter>

#include "sourcestyle.h"
#include "visualnodebase.h"

class VisualSourceNodeBase : public VisualNodeBase, public SourceStyle
{
    Q_OBJECT
public:
    VisualSourceNodeBase();
    VisualSourceNodeBase(QJsonObject &baseJson, DeserializationHandler &handler);
protected:
    void drawStartStop(QPainter *painter, bool running);
    bool startStopClicked(QPointF mousepos);
private:
    void drawStartStop(QPainter *painter, int x, int y, bool running);

};
