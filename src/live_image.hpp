// Copyright (C) 2022 thinkdigital
// Creator: dimitri.ratz@thinkdigital.cc

#ifndef LIVEIMAGE_HPP
#define LIVEIMAGE_HPP

#include <QImage>
#include <QPainter>
#include <QQuickPaintedItem>

namespace thinkdigital::sissa {

class LiveImage : public QQuickPaintedItem {
  Q_OBJECT
  Q_PROPERTY(QImage image MEMBER m_image WRITE set_image)

public:
  explicit LiveImage(QQuickItem *parent = nullptr);
  void set_image(const QImage &image);
  void paint(QPainter *painter) override;

private:
  QImage m_image;
};
} // namespace thinkdigital::sissa

#endif // LIVEIMAGE_HPP
