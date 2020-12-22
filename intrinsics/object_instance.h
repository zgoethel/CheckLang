#pragma once

#include <memory>

#include "structures/collection.h"

#include "object_prototype.h"
#include "object_method.h"
#include "object_property.h"

struct object_instance
{
    std::shared_ptr<object_prototype> type;

    //TODO Keyed collection of field values
};