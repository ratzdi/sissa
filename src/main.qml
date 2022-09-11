// Copyright (C) 2022 thinkdigital.cc
// Creator: dimitri.ratz@thinkdigital.cc

import QtQuick.Layouts 1.3
import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQml 2.3
import QtQuick.Dialogs 1.2

import com.thinkdigital 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: "SISSA: Simple slide-show app"

    GridLayout
    {
        anchors.fill: parent
        rows:1
        columns: 2

        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true

            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            Layout.minimumWidth: parent.width * 0.7

            LiveImage {
                anchors.fill: parent
                image: LiveImageProvider.image
            }

            Connections{
                target: LiveImageProvider
                onSlide_show_finished: {
                    bt_open_dialog.enabled = true
                    bt_start_slide_show.enabled = true
                    bt_stop_slide_show.enabled = false
                }
            }

            Connections{
                target: LiveImageProvider
                onSlide_show_started: {
                    bt_open_dialog.enabled = false
                    bt_start_slide_show.enabled = false
                    bt_stop_slide_show.enabled = true
                }
            }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

            Button {
                id: bt_open_dialog
                text:"Choose directory"
                onClicked: fdialog_path_selector.open()
            }

            FileDialog {
                id: fdialog_path_selector
                title: "Choose a directory"
                folder: shortcuts.home
                selectFolder: true

                onAccepted: {
                    console.log("You chose: " + fdialog_path_selector.folder)
                    LiveImageProvider.set_image_directory_path(fdialog_path_selector.folder)
                    bt_start_slide_show.enabled = true
                }

                Component.onCompleted: visible = false
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

            ComboBox {
                id: img_mirror_type
                editable: false
                model: ListModel {
                   id: model
                   ListElement { text: "None" }
                   ListElement { text: "Horizontal" }
                   ListElement { text: "Vertical" }
                   ListElement { text: "Both" }
                }
                onAccepted: {
                   if (find(editText) === -1) {
                       model.append({text: editText})
                   }
                }
                onCurrentIndexChanged: {
                    LiveImageProvider.set_mirror_type(model.get(currentIndex).text)
                }
            }

            Text {
                id: txt_interval_value
                text: Math.round(slider_intreval.value)
            }

            Slider {
                id: slider_intreval
                from: 1
                value: 2
                to: 60
                onValueChanged: LiveImageProvider.set_timer_interval(value)
            }
        }
    }
}
