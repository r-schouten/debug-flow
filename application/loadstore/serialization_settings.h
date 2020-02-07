#pragma once

struct SerializationSettings_t
{
public:
    bool serializeContext = true;
    bool serializeData = false; //if supported
    bool returnOnError = true;
};
