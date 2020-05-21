import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
    id: button

    implicitWidth: 16
    implicitHeight: 14

    contentItem: Image {
        anchors.fill: parent
        source: button.down
                || button.hovered ? "qrc:/images/previous_blue_light.png" : "qrc:/images/previous_blue.png"
    }

    background: Item {}
}
