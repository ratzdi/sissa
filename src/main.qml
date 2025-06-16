// Copyright (C) 2022 thinkdigital.cc
// Creator: dimitri.ratz@thinkdigital.cc

import QtQuick.Layouts 1.15
import QtQuick 2.15
import QtQml 2.15
import QtQuick.Dialogs
import QtQuick.Controls 2.15

import com.thinkdigital 1.0

ApplicationWindow {
    id: window
    visible: true
    title: "SISSA: simple slide-show app"
    visibility: Qt.WindowFullScreen
    minimumWidth: 1024
    minimumHeight: 800
    onWidthChanged: {
        live_image.resize(rect_image.width, rect_image.height)
    }

    ColumnLayout {
        anchors.fill: parent

        Rectangle {
            id: rect_image
            Layout.margins: 20
            Layout.fillHeight: true
            Layout.fillWidth: true

            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

            LiveImage {
                id: live_image
                image: LiveImageProvider.image
                width: rect_image.width
                height: rect_image.height
            }

            Connections {
                target: LiveImageProvider
                function onSlide_show_finished() {
                    bt_open_dialog.enabled = true
                    bt_start_slide_show.enabled = true
                    bt_stop_slide_show.enabled = false
                    slider_interval.enabled = true
                    cbx_img_mirror_type.enabled = true
                }
            }

            Connections {
                target: LiveImageProvider
                function onSlide_show_started() {
                    bt_open_dialog.enabled = false
                    bt_start_slide_show.enabled = false
                    bt_stop_slide_show.enabled = true
                    slider_interval.enabled = false
                    cbx_img_mirror_type.enabled = false
                }
            }
        }

        RowLayout {
            Layout.margins: 20
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

            Button {
                id: bt_open_dialog
                text:"Choose directory"
                onClicked: fdialog_path_selector.open()
            }

            FileDialog {
                id: fdialog_path_selector
                title: "Choose a directory"
                currentFolder: "./"

                onAccepted: {
                    LiveImageProvider.set_image_directory_path(fdialog_path_selector.currentFolder)
                    bt_start_slide_show.enabled = true
                    cbx_img_mirror_type.enabled = true
                }
            }

            Button {
                id: bt_start_slide_show
                text:"Start"
                onClicked: LiveImageProvider.start_slide_show()
                enabled: false
            }

            Button {
                id: bt_stop_slide_show
                text:"Stop"
                onClicked: LiveImageProvider.stop_slide_show()
                enabled: false
            }

            Text {
                id: txt_mirror_type
                text: qsTr("Mirror mode")
            }

            ComboBox {
                id: cbx_img_mirror_type
                editable: false
                enabled: false
                model: ListModel {
                   id: cbx_model
                   ListElement { text: "None" }
                   ListElement { text: "Horizontal" }
                   ListElement { text: "Vertical" }
                   ListElement { text: "Both" }
                }

                onCurrentIndexChanged: {
                    LiveImageProvider.set_mirror_type(cbx_model.get(currentIndex).text)
                }
            }

            Text {
                id: txt_interval_value
                text: "Interval: " + Math.round(slider_interval.value)
            }

            Slider {
                id: slider_interval
                enabled: false
                from: 1
                value: 2
                to: 60
                onValueChanged: LiveImageProvider.set_timer_interval(value)
            }
        }
    }
}
