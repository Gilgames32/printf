#pragma once

#include <memory>
#include <string>

#include "image_source_view.hpp"

class PDFSourceView : public ImageSourceView {
  protected:
    virtual void load_image() override;

  public:
    PDFSourceView();
};