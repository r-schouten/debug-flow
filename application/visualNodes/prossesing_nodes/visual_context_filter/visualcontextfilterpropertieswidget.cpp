#include "visualcontextfilterpropertieswidget.h"


VisualContextFilterPropertiesWidget::VisualContextFilterPropertiesWidget(QWidget *parent, ContextFilterSettings *_settings)
    :PropertyWidgetBase(parent), settings(_settings)
{
    layout = new QVBoxLayout;
    layout->setMargin(5);
    layout->setAlignment(Qt::AlignTop);
    this->setLayout(layout);

    tagsWidget = new TagsAndOptionsWidget(nullptr, &settings->tagAndOptionsSettings->tags);
    layout->addWidget(tagsWidget);

    connect(settings->tagAndOptionsSettings, SIGNAL(optionAdded(Tag*,TagOption*)),tagsWidget,SLOT(optionAdded(Tag*,TagOption*)));
    connect(settings->tagAndOptionsSettings,SIGNAL(tagsChanged()),tagsWidget,SLOT(loadTags()));

    tagsWidget->loadTags();
}

VisualContextFilterPropertiesWidget::~VisualContextFilterPropertiesWidget()
{

}
