#pragma once

#include <memory>
#include <string>

#include "object_prototype.h"

struct object_prototype;

struct object_property
{
    std::string name;

    std::shared_ptr<object_prototype> type;
};