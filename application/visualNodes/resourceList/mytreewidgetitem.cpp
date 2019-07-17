#include "mytreewidgetitem.h"

MyTreeWidgetItem::MyTreeWidgetItem()
{

}
MyTreeWidgetItem::~MyTreeWidgetItem()
{
    if(node!=nullptr)
    {
        delete node;
    }
}
void MyTreeWidgetItem::setNode(VisualNodeBase* _node)
{
    node = _node;
}

VisualNodeBase *MyTreeWidgetItem::getNodeCopy()
{
    return node->clone();
}
