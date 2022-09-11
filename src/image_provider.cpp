// Copyright (C) 2022 thinkdigital
// Creator: dimitri.ratz@thinkdigital.cc

#include "image_provider.hpp"

#include <QDir>
#include <QTimer>
#include <QUrl>
#include <QtConcurrent>

#include <iostream>
#include <stdexcept>
#include <string>

namespace thinkdigital::sissa {

ImageProvider::ImageProvider(QObject* parent)
    : QObject(parent)
    , m_timer_interval_msecs(2000)
{
}

void ImageProvider::process_image()
{
    auto future { QtConcurrent::run([=]() {
        try {
            auto image { load_image() };
            image = mirror_image(image);
            set_image(image);
        } catch (std::exception& ex) {
            std::cerr << ex.what() << std::endl;
        }
    }) };
}

QImage ImageProvider::load_image()
{
    const auto next_image_path { get_next_image_path() };

    if (QImage image {}; not next_image_path.isEmpty() && image.load(next_image_path)) {
        return image;
    } else {
        emit slide_show_finished();
        throw std::logic_error { std::string("No image file found on path " + next_image_path.toStdString()) };
    }
}

QString ImageProvider::get_next_image_path() {
    if (m_image_path_list.empty())
        return QString();
    else
        return QDir(m_image_directory_path).filePath(m_image_path_list.takeLast());
}

QImage ImageProvider::mirror_image(QImage& image)
{
    if (m_mirror_type == QString("Horizontal"))
        return image.mirrored(true, false);
    else if (m_mirror_type == QString("Vertical"))
        return image.mirrored();
    else if (m_mirror_type == QString("Both"))
        return image.mirrored(true, true);
    else if (m_mirror_type == QString("None"))
        return image;
    else {
        std::cout << "Warning: mirror mode not supported." << std::endl;
        return image;
    }
}

void ImageProvider::set_image(QImage const& image)
{
    m_image = image;
    emit imageChanged();
}

void ImageProvider::set_timer_interval(int sec) { m_timer_interval_msecs = sec * 1000; }

QImage ImageProvider::image() const { return m_image; }

void ImageProvider::set_image_directory_path(const QString& value)
{

    const QUrl url { value };
    if (url.isLocalFile()) {
        m_image_directory_path = QDir::toNativeSeparators(url.toLocalFile());
    } else {
        m_image_directory_path = value;
    }
}

void ImageProvider::start_slide_show()
{
    if (m_timer.isActive())
        return;

    QDir directory { m_image_directory_path };

    if (not directory.exists())
        return;

    directory.setNameFilters(QStringList() << "*.png");
    m_image_path_list = directory.entryList();

    if (m_image_path_list.empty())
        return;

    process_image();

    connect(&m_timer, &QTimer::timeout, this, &ImageProvider::process_image);
    m_timer.start(m_timer_interval_msecs);
    emit slide_show_started();
}

void ImageProvider::stop_slide_show()
{
    if (not m_timer.isActive())
        return;

    m_timer.stop();
    disconnect(&m_timer, &QTimer::timeout, this, &ImageProvider::process_image);
    emit slide_show_finished();
}

void ImageProvider::set_mirror_type(const QString& value)
{
    m_mirror_type = value;
}

} // namespace thinkdigital::sissa
