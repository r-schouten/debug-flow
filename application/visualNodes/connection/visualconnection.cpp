#include "visualconnection.h"

VisualConnection::VisualConnection(FlowObjects *_flowObjects, Connector *connector1)
    :connector1(connector1)
{
    setConnector1(connector1);
    selectionManager = _flowObjects->getSelectionManager();
    style = new ConnectionStyle();

    dbgLogger = _flowObjects->getDbgLogger();

    uniqueId = Utils::getRandom();

}

VisualConnection::VisualConnection(FlowObjects *_flowObjects, Connector *connector1, Connector *_connector2)
    :VisualConnection(_flowObjects, connector1)
{
    connector2 = _connector2;
    setConnector2(connector2);
}

VisualConnection::~VisualConnection()
{
    emit onDelete(this);

    //delete the double links
    if(connection1Set)
    {
        connector1->disconnect(this);
        connection1Set = false;
    }
    if(connection2Set)
    {
        connector2->disconnect(this);
        connection2Set = false;
    }
}

void VisualConnection::draw(QPainter* painter)
{
    if(connection1Set)
    {
        if(point1 != connector1->getScenePos())
        {
            point1 = connector1->getScenePos();
            settingsChanged = true;
        }
    }
    else {
        point1 = mousePos;
        settingsChanged = true;
    }
    if(connection2Set)
    {
        if(point2 != connector2->getScenePos())
        {
            point2 = connector2->getScenePos();
            settingsChanged = true;
        }
    }
    else {
        point2 = mousePos;
        settingsChanged = true;
    }

    painter->setBrush(style->brush);
    painter->setPen(style->linePen);
    if(selectionManager->isSelected(this))
    {
        painter->setPen(style->selectedPen);
    }

    makePainterPath();
    painter->drawPath(painterPath);

    if(connection1Set)
    {
        painter->setPen(style->endsPen);
    }
    else {
        painter->setPen(style->endsPenNotConnected);

    }
    painter->drawEllipse(point1,5,5);
    if(connection2Set)
    {
        painter->setPen(style->endsPen);
    }
    else {
        painter->setPen(style->endsPenNotConnected);
    }
    painter->drawEllipse(point2,5,5);

}
QPointF calculateBezierPoint(QPointF &startPoint, double angle, int distance)
{
    QPointF bezierPoint;
    bezierPoint.rx() = startPoint.x() + cos(angle) * distance;
    bezierPoint.ry() = startPoint.y() + sin(angle) * distance;
    return bezierPoint;
}
int minAbs(int a, int b)
{
    if(abs(a) < abs(b))
        return a;
    return b;
}
int vectorDistanceBetweenPoints(QPointF &point1, double angle1,QPointF &point2)
{
    int deltaX = point2.x() - point1.x();
    int deltaY = point2.y() - point1.y();
    int potentialDistance1,potentialDistance2;
    if(abs(cos(angle1)) < 0.1)
    {
        potentialDistance1 = Utils::distanceBetweenPoints(point1,point2);
    }
    else {
        potentialDistance1 = deltaX/cos(angle1);
    }
    if(abs(sin(angle1)) < 0.1)
    {
        potentialDistance2 = Utils::distanceBetweenPoints(point1,point2);
    }
    else {
        potentialDistance2 = deltaY/sin(angle1);
    }
    int distance = minAbs(potentialDistance1,potentialDistance2);
    if(distance >=0)
    {
        return distance;
    }
    else {
        return abs(distance)*2;
    }
}
double angleDifference(double angle1, double angle2)
{
    double angleDelta = angle1 - angle2;
    if(angleDelta > M_PI)
    {
        angleDelta = angleDelta - 2 * M_PI;
    }
    if(angleDelta < -M_PI)
    {
        angleDelta = angleDelta + 2 * M_PI;
    }
    return angleDelta;
}
double calculateAngleBetweenPoints(QPointF& point1, QPointF& point2)
{
    double deltaX = point2.x() - point1.x();
    double deltaY = point2.y() - point1.y();
    return atan2(deltaY,deltaX);
}
void VisualConnection::makePainterPath()
{
    if(style->pathStyle != oldPathStyle)
    {
        settingsChanged = true;
        oldPathStyle = style->pathStyle;
    }
    if(settingsChanged)
    {
        settingsChanged = false;
        if(style->pathStyle == PathStyle::LINE)
        {
            painterPath = QPainterPath(point1);
            painterPath.lineTo(point2);
        }
        else if((style->pathStyle == PathStyle::BEZIER_STRAIGT)||(style->pathStyle == PathStyle::BEZIER))
        {
            double angle1 = 0;
            double angle2 = 0;
            if(connection1Set){
              angle1 = connector1->angle;
            }
            else if(connection2Set){
              angle1 = connector2->angle + M_PI;
            }
            if(connection2Set){
              angle2 = connector2->angle;
            }
            else if(connection1Set){
              angle2 = connector1->angle + M_PI;
            }
            if(style->pathStyle == PathStyle::BEZIER)
            {
                double angleBetweenPoints = calculateAngleBetweenPoints(point1,point2);
                angle1 += angleDifference(angleBetweenPoints,angle1)/6.0;
                angleBetweenPoints = calculateAngleBetweenPoints(point2,point1);
                angle2 += angleDifference(angleBetweenPoints,angle2)/6.0;
            }

            int distance1 = vectorDistanceBetweenPoints(point1,angle1,point2);
            int distance2 = vectorDistanceBetweenPoints(point2,angle2,point1);
            QPointF c1 = calculateBezierPoint(point1,angle1,distance1 / 2);
            QPointF c2 = calculateBezierPoint(point2,angle2,distance2 / 2);
            //begin line add point1
            painterPath = QPainterPath(point1);
            //cubic to point2
            painterPath.cubicTo(c1, c2, point2);
        }
    }
    else {

    }
}

bool VisualConnection::intersect(QPointF position)
{
    int margin = style->intersectMargin;
    QRectF rect = QRectF(position.x() - margin/2, position.y() - margin/2, margin,margin);
    if(painterPath.intersects(rect))
    {
        return true;
    }
    return false;
}

void VisualConnection::setMousePos(QPoint _mousePos)
{
    mousePos = _mousePos;
}


void VisualConnection::disconnect1()
{
    connector1 = nullptr;
    connection1Set = false;
}
void VisualConnection::disconnect2()
{
    connector2 = nullptr;
    connection2Set = false;
}

Connector *VisualConnection::getConnector1() const
{
    return connector1;
}
Connector *VisualConnection::getConnector2() const
{
    return connector2;
}

void VisualConnection::setConnector1(Connector *value)
{
    connector1 = value;
    connector1->connect(this);
    connection1Set = true;
}
void VisualConnection::setConnector2(Connector *value)
{
    connector2 = value;
    connector2->connect(this);
    connection2Set = true;
}
Connector* VisualConnection::getUnsetConnector()
{
    if(connection1Set)
    {
        return connector1;
    }
    if(connection2Set)
    {
        return connector2;
    }
    dbgLogger->error(CLASSNAME,__FUNCTION__,"getUnsedConnector called while both are connected");
    return nullptr;
}

Connector *VisualConnection::getSetConnector()
{
    if(connection1Set)
    {
        return connector1;
    }
    if(connection2Set)
    {
        return connector2;
    }
    dbgLogger->error(CLASSNAME,__FUNCTION__,"getUnsedConnector called while both are connected");
    return nullptr;
}
void VisualConnection::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(intersect(event->scenePos()))
    {
        if (event->modifiers() == Qt::ControlModifier && event->button() == Qt::LeftButton)
        {
            selectionManager->setSelected(this,false);
        }
        else {
            if(selectionManager->isSelected(this))
            {
                selectionManager->setSelected(this,true);
            }
            else {
                selectionManager->setSelected(this,true);

            }

        }
    }
}

QJsonObject *VisualConnection::serialize(SerializationHandler &handler)
{
    QJsonObject* jsonObject = new QJsonObject;
    if(handler.saveTemp() == false)
    {
        if((connection1Set == false) || (connection2Set == false))
        {
            //this connection is temporary
            return nullptr;
        }
    }

    int64_t connector1Id = 0;
    QString connector1Name = "";
    if(connection1Set){
        connector1Id = connector1->getParent()->getUniqueId();
        connector1Name = connector1->name;
    }
    jsonObject->insert(JSON_CONNECTION_CONNECTOR1_NODE_ID,connector1Id);
    jsonObject->insert(JSON_CONNECTION_CONNECTOR1_NAME,connector1Name);

    int64_t connector2Id = 0;
    QString connector2Name = "";
    if(connection2Set){
        connector2Id = connector2->getParent()->getUniqueId();
        connector2Name = connector2->name;
    }
    jsonObject->insert(JSON_CONNECTION_CONNECTOR2_NODE_ID,connector2Id);
    jsonObject->insert(JSON_CONNECTION_CONNECTOR2_NAME,connector2Name);

    jsonObject->insert(JSON_CONNECTION_UNIQUE_ID,(qint64)uniqueId);
    return jsonObject;
}

uint64_t VisualConnection::getUniqueId() const
{
    return uniqueId;
}

void VisualConnection::setUniqueId(const uint64_t &value)
{
    uniqueId = value;
}

void VisualConnection::setDeleteReason(VisualConnection::DeleteReason _deleteReason)
{
    deleteReason = _deleteReason;
}

