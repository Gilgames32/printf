#pragma once

#include <QtCore>
#include "ifilter.hpp"
#include <memory>

class IFilterView : public QObject {
  Q_OBJECT
  public:
    virtual std::shared_ptr<IFilter> get_filter() const = 0; // TODO: shared pointer
    virtual bool is_enabled() const = 0;
};