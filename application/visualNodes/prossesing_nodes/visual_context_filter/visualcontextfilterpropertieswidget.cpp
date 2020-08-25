#include "visualcontextfilterpropertieswidget.h"


VisualContextFilterPropertiesWidget::VisualContextFilterPropertiesWidget(QWidget *parent, DbgLogger* dbgLogger, ContextFilterSettings *_settings)
    :PropertyWidgetBase(parent,dbgLogger), settings(_settings)
{
    layout = new QVBoxLayout;
    layout->setMargin(5);
    layout->setAlignment(Qt::AlignTop);
    this->setLayout(layout);

    tagsWidget = new TagsAndOptionsWidget(nullptr, &settings->tagAndOptionsSettings->tags);
    layout->addWidget(tagsWidget);

    mergeModeComboBox = new QComboBox(this);
    layout->addWidget(mergeModeComboBox);
    for(int i=0;i<settings->mergeModeString.length();i++)
    {
        mergeModeComboBox->addItem(settings->mergeModeString.at(i),(MergeMode_t)i);
    }
    mergeModeComboBox->setCurrentIndex(settings->getMergeMode());

    connect(mergeModeComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(mergeModeChanged(int)));

    connect(settings->tagAndOptionsSettings, SIGNAL(optionAdded(Tag*,TagOption*)),tagsWidget,SLOT(optionAdded(Tag*,TagOption*)));
    connect(settings->tagAndOptionsSettings,SIGNAL(tagsChanged()),tagsWidget,SLOT(loadTags()));

    connect(tagsWidget, SIGNAL(DataChanged()), this, SLOT(contextSettingsChanged()));

    tagsWidget->loadTags();
}

VisualContextFilterPropertiesWidget::~VisualContextFilterPropertiesWidget()
{

}
void VisualContextFilterPropertiesWidget::mergeModeChanged(int index)
{
    settings->setMergeMode((MergeMode_t)index);
}
void VisualContextFilterPropertiesWidget::contextSettingsChanged()
{
    settings->notifySettingsChanged(DATA_INVALID, DONT_SAVE, PROPERIES);
}
