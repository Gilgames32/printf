#pragma once

#include <QtCore>
#include "ifilter.hpp"

class IFilterView : public QObject {
  Q_OBJECT
  public:
    virtual IFilter* get_filter() const = 0;
    virtual bool is_enabled() const = 0;
};