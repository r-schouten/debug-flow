#include "filteredconsolepropertieswidget.h"

#include <QCheckBox>

FilteredConsolePropertiesWidget::FilteredConsolePropertiesWidget(QWidget* parent, FilteredNodeSettings* settings)
    :PropertyWidgetBase (parent),settings(settings)
{
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setSizePolicy(sizePolicy);

    layout = new QVBoxLayout;
    layout->setMargin(5);
    layout->setAlignment(Qt::AlignTop);
    this->setLayout(layout);

    container = new QWidget();
    layout->addWidget(container);
    containerLayout = new QFormLayout;
    containerLayout->setMargin(0);
    container->setLayout(containerLayout);


    filterOnWindowCheckbox = new QCheckBox(this);
    filterOnWindowCheckbox->setChecked(settings->nodeSettings.filterOnWindow);
    containerLayout->addRow("show filter",filterOnWindowCheckbox);

    LineNumbersCheckbox = new QCheckBox(this);
    LineNumbersCheckbox->setChecked(settings->nodeSettings.LineNumbersEnabled);
    containerLayout->addRow("show line numbers",LineNumbersCheckbox);

    ANSICheckbox = new QCheckBox(this);
    ANSICheckbox->setChecked(settings->nodeSettings.ANSIEnabled);
    containerLayout->addRow("use ANSI color codes",ANSICheckbox);

    autoScrollCheckbox = new QCheckBox(this);
    autoScrollCheckbox->setChecked(settings->nodeSettings.autoScrollEnabled);
    containerLayout->addRow("auto scroll",autoScrollCheckbox);

    horizontalScrollComboBox = new QComboBox(this);
    containerLayout->addRow("horizontal scroll",horizontalScrollComboBox);
    QStringList list;
    list << "new line" <<"scrollbar" <<"ignore";
    horizontalScrollComboBox->addItems(list);

    maxLinesComboBox = new QComboBox(this);
    containerLayout->addRow("max lines",maxLinesComboBox);
    QStringList linesList;
    linesList << "fitting" <<"100" <<"500"<<"1000"<<"10.000"<<"100.000"<<"1.000.000";
    maxLinesComboBox->addItems(linesList);



    connect(settings, SIGNAL(optionAdded(Tag*)),this,SLOT(optionAdded(Tag*)));

    QListIterator<Tag*> tagIterator(settings->nodeSettings.tags);
    while(tagIterator.hasNext())
    {
        Tag* currentTag = tagIterator.next();
        TagGroupbox* newGroupBox = new TagGroupbox(currentTag);
        tagGroupboxes.append(newGroupBox);
        loadTag(newGroupBox);
        layout->addWidget(newGroupBox);
    }
}

FilteredConsolePropertiesWidget::~FilteredConsolePropertiesWidget()
{
    while(tagGroupboxes.size() > 0) tagGroupboxes.removeAt(0);

}
void FilteredConsolePropertiesWidget::loadTag(TagGroupbox* tagGroupbox)
{
    tagGroupbox->options.clear();

    QListIterator<TagOption*> optionIterator(tagGroupbox->tag->options);
    while(optionIterator.hasNext())
    {
        TagOption* currentOption = optionIterator.next();
        QStandardItem* item = new QStandardItem;
        tagGroupbox->options.append(item);
        item->setText(currentOption->name);
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setData(Qt::Checked, Qt::CheckStateRole);

        tagGroupbox->itemModel->appendRow(item);
    }
}
void FilteredConsolePropertiesWidget::optionAdded(Tag* destinationTag)
{
    qDebug("[debug,FilteredConsolePropertiesWidget::optionAdded]");

    //find in which groupbox the tag is added
    TagGroupbox* destinationGroupbox = nullptr;
    QListIterator<TagGroupbox*> tagIterator(tagGroupboxes);
    while(tagIterator.hasNext())
    {
        TagGroupbox* currentGroupBox = tagIterator.next();
        if(currentGroupBox->tag == destinationTag)
        {
            destinationGroupbox = currentGroupBox;
        }
    }
    //the tag groupbox don't exist, add it
    if(destinationGroupbox == nullptr)
    {
        destinationGroupbox = new TagGroupbox(destinationTag);
        tagGroupboxes.append(destinationGroupbox);
        layout->addWidget(destinationGroupbox);
        destinationGroupbox->show();
    }

    loadTag(destinationGroupbox);
}
