#pragma once

#include <QtCore>
#include <memory>

#include "ifilter.hpp"

class IFilterView : public QObject {
    Q_OBJECT
  public:
    virtual std::shared_ptr<IFilter> get_filter() const = 0;  // TODO: shared pointer
    virtual bool is_enabled() const = 0;
};