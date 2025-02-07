// Copyright (C) 2022 thinkdigital
// Creator: dimitri.ratz@thinkdigital.cc

#include "live_image.hpp"

namespace thinkdigital::sissa {

LiveImage::LiveImage(QQuickItem* parent)
    : QQuickPaintedItem(parent)
    , m_image {}
    , m_width { 0 }
    , m_height { 0 }
{
}

void LiveImage::paint(QPainter *painter) { painter->drawImage(0, 0, m_image); }

void LiveImage::set_image(const QImage& image)
{
    if (not image.isNull()) {
        m_image = image.scaled(m_width, m_height, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);
        update();
    }
}

void LiveImage::resize(const int w, const int h)
{
    m_width = w;
    m_height = h;

    if (not m_image.isNull()) {
        m_image = m_image.scaled(w, h, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);
        update();
    }
}

} // namespace thinkdigital::sissa
