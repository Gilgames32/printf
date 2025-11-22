#pragma once

#include <memory>
#include <string>

#include "image_source_view.hpp"

class PDFSourceView : public ImageSourceView {
  protected:
    virtual void load_image(double ppi) override;

  public:
    PDFSourceView();

    virtual std::shared_ptr<ImageSource> get_image_source(const DocumentPreset &preset) override;
};