#include <QJsonObject>

class Serializable
{
public:
    virtual QJsonObject* serialize()=0;
    virtual void deserialize(QJsonObject* jsonObject)=0;
};

