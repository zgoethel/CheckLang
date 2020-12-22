#pragma once

#include <memory>
#include <string>

#include "structures/collection.h"

#include "object_prototype.h"

struct object_prototype;

struct object_method
{
    std::string name;

    //TODO Keyed collection of parameter types

    std::shared_ptr<object_prototype> return_type;

    //TODO Pointer(s) to instruction address(es)
};