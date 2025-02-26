#pragma once

#include "icachable.hpp"

class ICache {
  public:
    virtual void set_dirty() = 0;
};