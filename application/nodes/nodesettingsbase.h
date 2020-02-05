#pragma once
#include <QObject>
#include <serializable.h>

#include "nodebase.h"

class NodeSettingsBase : public QObject, public Serializable
{
    Q_OBJECT
public:
    NodeSettingsBase();
};

