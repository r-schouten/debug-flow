#include "filteredconsolepropertieswidget.h"

#include <QPushButton>

#define etype(x) F_##x
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
    filterOnWindowCheckbox->setChecked(settings->filterOnWindow);
    containerLayout->addRow("show filter",filterOnWindowCheckbox);

    lineNumbersCheckbox = new QCheckBox(this);
    lineNumbersCheckbox->setChecked(settings->LineNumbersEnabled);
    containerLayout->addRow("show line numbers",lineNumbersCheckbox);

    ANSICheckbox = new QCheckBox(this);
    ANSICheckbox->setChecked(settings->ANSIEnabled);
    containerLayout->addRow("use ANSI color codes",ANSICheckbox);

    autoScrollCheckbox = new QCheckBox(this);
    autoScrollCheckbox->setChecked(settings->autoScrollEnabled);
    containerLayout->addRow("auto scroll",autoScrollCheckbox);

    horizontalScrollComboBox = new QComboBox(this);
    containerLayout->addRow("horizontal scroll",horizontalScrollComboBox);
    horizontalScrollComboBox->addItem("scrollbar",(int)HorizontalScrollOptions::scrollbar);
    horizontalScrollComboBox->addItem("ignore",(int)HorizontalScrollOptions::ignore);
    horizontalScrollComboBox->addItem("new line",(int)HorizontalScrollOptions::newline);
    for(int i = 0;i<horizontalScrollComboBox->count();i++)
    {
        if(horizontalScrollComboBox->itemData(i).toInt() == (int)settings->getHorizontalScroll())
        {
            horizontalScrollComboBox->setCurrentIndex(i);
            break;
        }
    }

    maxLinesComboBox = new QComboBox(this);
    containerLayout->addRow("max lines",maxLinesComboBox);
    maxLinesComboBox->addItem("fit",0);
    maxLinesComboBox->addItem("100",100);
    maxLinesComboBox->addItem("1,000",1000);
    maxLinesComboBox->addItem("10,000",10000);
    maxLinesComboBox->addItem("100,000",100000);
    maxLinesComboBox->addItem("1,000,000",1000000);

    for(int i = 0;i<maxLinesComboBox->count();i++)
    {
        if(maxLinesComboBox->itemData(i) == settings->getMaxLinesComboBox())
        {
            maxLinesComboBox->setCurrentIndex(i);
            break;
        }
    }
    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    layout->addWidget(line);

    QPushButton* clearButton = new QPushButton("clear console");
    QPushButton* clearContextButton = new QPushButton("clear context");
    containerLayout->addRow(clearButton, clearContextButton);

    connect(horizontalScrollComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(horizontalScrollIndexChanged(int)));
    connect(maxLinesComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(maxLinesIndexChanged(int)));
    connect(filterOnWindowCheckbox,SIGNAL(stateChanged(int)),this,SLOT(filterOnWindowStateChanged()));
    connect(lineNumbersCheckbox,SIGNAL(stateChanged(int)),this,SLOT(lineNumbersStateChanged()));
    connect(ANSICheckbox,SIGNAL(stateChanged(int)),this,SLOT(ANSIStateChanged()));
    connect(autoScrollCheckbox,SIGNAL(stateChanged(int)),this,SLOT(autoScrollStateChanged()));

    connect(settings, SIGNAL(optionAdded(Tag*)),this,SLOT(optionAdded(Tag*)));

    QListIterator<Tag*> tagIterator(settings->tags);
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
//---public slots
void FilteredConsolePropertiesWidget::horizontalScrollIndexChanged(int index)
{
    settings->setHorizontalScroll((HorizontalScrollOptions)horizontalScrollComboBox->currentData().toInt());
}
void FilteredConsolePropertiesWidget::maxLinesIndexChanged(int index)
{
    settings->setMaxLinesComboBox(maxLinesComboBox->currentData().toInt());
}
void FilteredConsolePropertiesWidget::filterOnWindowStateChanged()
{
    settings->filterOnWindow = filterOnWindowCheckbox->checkState();
}
void FilteredConsolePropertiesWidget::lineNumbersStateChanged()
{
    settings->LineNumbersEnabled = lineNumbersCheckbox->checkState();
}
void FilteredConsolePropertiesWidget::ANSIStateChanged()
{
    settings->ANSIEnabled = ANSICheckbox->checkState();
}
void FilteredConsolePropertiesWidget::autoScrollStateChanged()
{
    settings->autoScrollEnabled = autoScrollCheckbox->checkState();
}
