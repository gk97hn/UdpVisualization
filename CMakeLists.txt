cmake_minimum_required(VERSION 3.16)
project(UdpVisualization LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Core Network SerialBus)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(SOURCES
    main.cpp
    backend/BackendManager.cpp
    backend/XmlParser.cpp
    backend/UdpHandler.cpp
    backend/SocketCanHandler.cpp
    backend/Logger.cpp
    backend/models/ShapeModel.cpp
    backend/models/UdpSocketModel.cpp
)
set(HEADERS
    backend/BackendManager.h
    backend/XmlParser.h
    backend/UdpHandler.h
    backend/SocketCanHandler.h
    backend/Logger.h
    backend/models/ShapeModel.h
    backend/models/UdpSocketModel.h
)
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)
set(RESOURCE_FILES
    resources.qrc
)
qt_add_resources(${PROJECT_NAME} "qml_resources"
    PREFIX "/"
    FILES
        qml/main.qml
        qml/components/ShapeViewer.qml
        qml/components/UdpListView.qml
        qml/components/ConnectionPanel.qml
        qml/components/CanBusPanel.qml
        qml/components/StatusIndicator.qml
        qml/dialogs/ErrorDialog.qml
        qml/components/shapes/Rectangle.qml
        qml/components/shapes/Circle.qml
        qml/components/shapes/Image.qml
        qml/components/shapes/Line.qml
        qml/components/shapes/Text.qml
        qml/components/shapes/image.png
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Quick
    Qt6::Core
    Qt6::Network
    Qt6::SerialBus
)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/qml DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
