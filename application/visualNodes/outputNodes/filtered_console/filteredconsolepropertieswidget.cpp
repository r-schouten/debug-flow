#include "filteredconsolepropertieswidget.h"


FilteredConsolePropertiesWidget::FilteredConsolePropertiesWidget(QWidget* parent, FilteredNodeSettings* settings)
    :PropertyWidgetBase (parent),settings(settings)
{
    layout = new QVBoxLayout;
    layout->setMargin(5);
    layout->setAlignment(Qt::AlignTop);
    this->setLayout(layout);

    formContainer = new QWidget();
    layout->addWidget(formContainer);
    containerLayout = new QFormLayout;
    containerLayout->setMargin(0);
    formContainer->setLayout(containerLayout);

    tagContainer = new TagsAndOptionsWidget(nullptr, &settings->tagAndOptionSettings->tags);
    layout->addWidget(tagContainer);

    filterOnWindowCheckbox = new QCheckBox(this);
    filterOnWindowCheckbox->setChecked(settings->getFilterOnWindow());
    containerLayout->addRow("show filter",filterOnWindowCheckbox);

    lineNumbersCheckbox = new QCheckBox(this);
    lineNumbersCheckbox->setChecked(settings->getLineNumbersEnabled ());
    containerLayout->addRow("show line numbers",lineNumbersCheckbox);

    hideContextCheckbox = new QCheckBox(this);
    hideContextCheckbox->setChecked(settings->tagAndOptionSettings->getHideContext());
    containerLayout->addRow("hide context",hideContextCheckbox);

    ANSICheckbox = new QCheckBox(this);
    ANSICheckbox->setChecked(settings->tagAndOptionSettings->getANSIEnabled());
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

    connect(settings->tagAndOptionSettings, SIGNAL(optionAdded(Tag*,TagOption*)),tagContainer,SLOT(optionAdded(Tag*,TagOption*)));
    connect(settings->tagAndOptionSettings,SIGNAL(tagsChanged()),tagContainer,SLOT(loadTags()));

    tagContainer->loadTags();
}

FilteredConsolePropertiesWidget::~FilteredConsolePropertiesWidget()
{

}
//---public slots
void FilteredConsolePropertiesWidget::hideContextStateChanged()
{
    settings->tagAndOptionSettings->setHideContext(hideContextCheckbox->checkState());
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
    settings->tagAndOptionSettings->setANSIEnabled(ANSICheckbox->checkState());
}
void FilteredConsolePropertiesWidget::autoScrollStateChanged()
{
    settings->setAutoScrollEnabled(autoScrollCheckbox->checkState());
}
