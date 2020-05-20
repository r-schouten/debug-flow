#include "filteredconsolepropertieswidget.h"


FilteredConsolePropertiesWidget::FilteredConsolePropertiesWidget(QWidget* parent, FilteredNodeSettings* settings)
    :PropertyWidgetBase (parent),settings(settings)
{
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
    filterOnWindowCheckbox->setChecked(settings->getFilterOnWindow());
    containerLayout->addRow("show filter",filterOnWindowCheckbox);

    lineNumbersCheckbox = new QCheckBox(this);
    lineNumbersCheckbox->setChecked(settings->getLineNumbersEnabled());
    containerLayout->addRow("show line numbers",lineNumbersCheckbox);

    hideContextCheckbox = new QCheckBox(this);
    hideContextCheckbox->setChecked(settings->getHideContext());
    containerLayout->addRow("hide context",hideContextCheckbox);

    ANSICheckbox = new QCheckBox(this);
    ANSICheckbox->setChecked(settings->getANSIEnabled());
    containerLayout->addRow("use ANSI color codes",ANSICheckbox);

    autoScrollCheckbox = new QCheckBox(this);
    autoScrollCheckbox->setChecked(settings->getAutoScrollEnabled());
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
    maxLinesComboBox->addItem("100",100);
    maxLinesComboBox->addItem("1,000",1000);
    maxLinesComboBox->addItem("10,000",10000);
    maxLinesComboBox->addItem("100,000",100000);
    maxLinesComboBox->addItem("1,000,000",1000000);

    for(int i = 0;i<maxLinesComboBox->count();i++)
    {
        if(maxLinesComboBox->itemData(i) == settings->getMaxLines())
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
    connect(hideContextCheckbox,SIGNAL(stateChanged(int)),this,SLOT(hideContextStateChanged()));

    connect(lineNumbersCheckbox,SIGNAL(stateChanged(int)),this,SLOT(lineNumbersStateChanged()));
    connect(ANSICheckbox,SIGNAL(stateChanged(int)),this,SLOT(ANSIStateChanged()));
    connect(autoScrollCheckbox,SIGNAL(stateChanged(int)),this,SLOT(autoScrollStateChanged()));

    connect(clearButton,SIGNAL(clicked(bool)),settings,SLOT(clearConsoleClicked()));
    connect(clearContextButton,SIGNAL(clicked(bool)),settings,SLOT(clearContextClicked()));

    connect(settings, SIGNAL(optionAdded(Tag*,TagOption*)),this,SLOT(optionAdded(Tag*,TagOption*)));
    connect(settings,SIGNAL(tagsChanged()),this,SLOT(loadTags()));

    loadTags();
}

FilteredConsolePropertiesWidget::~FilteredConsolePropertiesWidget()
{
    while(tagGroupboxes.size() > 0) delete tagGroupboxes.takeAt(0);

}
void FilteredConsolePropertiesWidget::loadTags()
{
    while(tagGroupboxes.size() > 0) delete tagGroupboxes.takeAt(0);


    QListIterator<Tag*> tagIterator(settings->tags);
    while(tagIterator.hasNext())
    {
        Tag* currentTag = tagIterator.next();
        TagGroupbox* newGroupBox = new TagGroupbox(currentTag);
        tagGroupboxes.append(newGroupBox);
        newGroupBox->loadTag();
        layout->addWidget(newGroupBox);
        this->update();
    }
}
void FilteredConsolePropertiesWidget::optionAdded(Tag* destinationTag, TagOption* option)
{

    TagGroupbox* destinationGroupbox = nullptr;
    if(tagGroupboxes.size() <= destinationTag->tagIndex)
    {
        destinationGroupbox = new TagGroupbox(destinationTag);
        tagGroupboxes.append(destinationGroupbox);
        layout->addWidget(destinationGroupbox);
    }
    else {
        destinationGroupbox = tagGroupboxes.at(destinationTag->tagIndex);
    }

    TagOptionItem* item = new TagOptionItem(option);
    item->setText(option->name);
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setData(item->tagOption->enabled? Qt::Checked:Qt::Unchecked, Qt::CheckStateRole);

    destinationGroupbox->itemModel->appendRow(item);
}
//---public slots
void FilteredConsolePropertiesWidget::hideContextStateChanged()
{
    settings->setHideContext(hideContextCheckbox->checkState());
}
void FilteredConsolePropertiesWidget::horizontalScrollIndexChanged(int index)
{
    Q_UNUSED(index);
    settings->setHorizontalScroll((HorizontalScrollOptions)horizontalScrollComboBox->currentData().toInt());
}
void FilteredConsolePropertiesWidget::maxLinesIndexChanged(int index)
{
    Q_UNUSED(index);
    settings->setMaxLinesComboBox(maxLinesComboBox->currentData().toInt());
}
void FilteredConsolePropertiesWidget::filterOnWindowStateChanged()
{
    settings->setFilterOnWindow(filterOnWindowCheckbox->checkState());
}
void FilteredConsolePropertiesWidget::lineNumbersStateChanged()
{
    settings->setLineNumbersEnabled(lineNumbersCheckbox->checkState());
}
void FilteredConsolePropertiesWidget::ANSIStateChanged()
{
    settings->setANSIEnabled(ANSICheckbox->checkState());
}
void FilteredConsolePropertiesWidget::autoScrollStateChanged()
{
    settings->setAutoScrollEnabled(autoScrollCheckbox->checkState());
}
