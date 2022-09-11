// Copyright (C) 2022 thinkdigital
// Creator: dimitri.ratz@thinkdigital.cc

#ifndef IMAGEPROVIDER_HPP
#define IMAGEPROVIDER_HPP

#include <QImage>
#include <QObject>
#include <QTimer>

namespace thinkdigital::sissa {

class ImageProvider : public QObject {
  Q_OBJECT
  Q_PROPERTY(QImage image MEMBER m_image READ image WRITE set_image NOTIFY imageChanged)

  public:
  ImageProvider(QObject *parent = nullptr);
  QImage load_image();
  void set_image(QImage const& image);

  QImage image() const;
  Q_INVOKABLE void set_image_directory_path(const QString &value);
  Q_INVOKABLE void start_slide_show();
  Q_INVOKABLE void stop_slide_show();
  Q_INVOKABLE void set_mirror_type(const QString& value);
  Q_INVOKABLE void set_timer_interval(int sec);

  signals:
  void imageChanged();
  void slide_show_finished();
  void slide_show_started();

  private:
  QString m_image_directory_path;
  QStringList m_image_path_list;
  int32_t m_timer_interval_msecs;
  QTimer m_timer;
  QString m_mirror_type;
  QImage m_image;

  QString get_next_image_path();
  QImage mirror_image(QImage& image);
  void process_image();
};

} // namespace thinkdigital::sissa
#endif // IMAGEPROVIDER_HPP
