#include "itemlist.h"




ItemList::ItemList(QTreeWidget *resourceList, NodeScene *nodeScene)
    :resourceList(resourceList),nodeScene(nodeScene)
{
    resourceList->setIconSize(QSize(100,800));
    resourceList->setColumnCount(1);
    resourceList->setHeaderLabel("");
    resourceList->setSelectionMode(QAbstractItemView::NoSelection);
    resourceList->setFocusPolicy(Qt::NoFocus);
    resourceList->setIndentation(10);
    connect(resourceList,SIGNAL(itemClicked(QTreeWidgetItem*, int)),this,SLOT(itemClicked(QTreeWidgetItem*, int)));
    connect(resourceList,SIGNAL(itemPressed(QTreeWidgetItem*, int)),this,SLOT(itemPressed(QTreeWidgetItem*, int)));

    generateList();
}
void ItemList::generateList()
{
    //ownership of this nodes will be given to myTreeWidgetItem, don't delete!
    nodes << new VisualContextFilter() << new VisualSerialNode() << new VisualFilteredConsole;
    generateCategory<SourceStyle>(nodes, "data source nodes", ":/images/data_source_icon.png");
    generateCategory<ProcessingStyle>(nodes, "processing nodes", ":/images/filtering_icon.png");
    generateCategory<OutputStyle>(nodes, "output nodes", ":/images/output_icon.png");
}
static QPixmap QPixmapFromItem(QGraphicsItem *item){
    QPixmap pixmap(item->boundingRect().size().toSize());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing,QPainter::TextAntialiasing);
    QStyleOptionGraphicsItem opt;
    item->paint(&painter, &opt);
    return pixmap;
}
template<typename T>
void ItemList::generateCategory(QList<VisualNodeBase*>& nodes, QString name, QString iconName)
{
    MyTreeWidgetItem* sources = new MyTreeWidgetItem();
    resourceList->insertTopLevelItem(0,sources);

    QPixmap pixmap(iconName);
    pixmap = pixmap.scaled(40,40);
    QIcon icon(pixmap);
    sources->setIcon(0,icon);
    sources->setSizeHint(0,QSize(100,50));
    sources->setText(0, name);

    QFont font0("Times", 11, QFont::Bold);
    sources->setFont(0,font0);

    QListIterator<VisualNodeBase*> iterator(nodes);
    T *lastT = nullptr;
    while(iterator.hasNext())
    {
        VisualNodeBase * currentNode = iterator.next();
        if(dynamic_cast<T*>(currentNode))
        {
            lastT = dynamic_cast<T*>(currentNode);
            QPixmap pixmap = QPixmapFromItem(currentNode);
            QIcon icon(pixmap);
            MyTreeWidgetItem* item = new MyTreeWidgetItem();
            item->setNode(currentNode);
            sources->addChild(item);
            item->setIcon(0,icon);
            item->setSizeHint(0,QSize(100,70));
            item->setText(0,currentNode->name);
            QFont font1("Times", 11, QFont::Normal);
            item->setFont(0,font1);

        }
    }
    if(lastT != nullptr)
    {
        if(dynamic_cast<NodeStyleBase*>(lastT))
        {
            QColor color(dynamic_cast<NodeStyleBase*>(lastT)->nodeCategoryColor);
            color.setAlpha(150);
            sources->setBackgroundColor(0, color);
        }
    }

}
void ItemList::itemPressed(QTreeWidgetItem *item, int column)
{

}
void ItemList::itemClicked(QTreeWidgetItem *item, int column)
{
    qDebug("[verbose,ItemList] item clicked %d",column);

    if(item->childCount() != 0)
    {
        resourceList->collapseAll();
        item->setExpanded(true);
    }
    else {
        MyTreeWidgetItem* myItem = dynamic_cast<MyTreeWidgetItem*>(item);
        if(myItem)
        {
            nodeScene->insertItem(myItem->getNodeCopy());
        }
        else {
            qDebug("[verbose,ItemList] not inherited from MyTreeWidgetItem",column);
        }
    }

}
