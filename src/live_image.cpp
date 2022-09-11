// Copyright (C) 2022 thinkdigital
// Creator: dimitri.ratz@thinkdigital.cc

#include "live_image.hpp"

namespace thinkdigital::sissa {

LiveImage::LiveImage(QQuickItem *parent)
    : QQuickPaintedItem(parent), m_image{} {}

void LiveImage::paint(QPainter *painter) { painter->drawImage(0, 0, m_image); }

void LiveImage::set_image(const QImage &image) {
  m_image = image;
  update();
}

} // namespace thinkdigital::sissa
