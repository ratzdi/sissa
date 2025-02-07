// Copyright (C) 2022 thinkdigital
// Creator: dimitri.ratz@thinkdigital.cc

#include "image_provider.hpp"
#include "live_image.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlProperty>
#include <QTimer>

#include <iostream>
#include <stdexcept>

int main(int argc, char *argv[]) {
    try {
        QGuiApplication app(argc, argv);
        app.setOrganizationName("thinkdigital");
        app.setOrganizationDomain("thinkdigital.cc");
        app.setApplicationName("SISSA");
        qmlRegisterType<thinkdigital::sissa::LiveImage>("com.thinkdigital", 1, 0, "LiveImage");

        QStringList filters {};
        filters << "*.jpg"
                << "*.jpeg"
                << "*.png"
                << "*.tiff"
                << "*.bmp";

        thinkdigital::sissa::ImageProvider provider { filters };
        QQmlApplicationEngine engine;
        engine.rootContext()->setContextProperty("LiveImageProvider", &provider);
        engine.load(QUrl(QLatin1String("qrc:/main.qml")));
        return app.exec();
    } catch (std::exception& ex) {
        std::cout << "Exception occurred. Exception message: " << ex.what() << std::endl;
    } catch (...) {
        std::cout << "Unspecific exception occurred." << std::endl;
    }
    return EXIT_FAILURE;
}
