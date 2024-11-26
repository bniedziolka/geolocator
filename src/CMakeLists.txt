
qt_add_executable(appgeolocator
    main.cpp
    Geolocation.hpp
    GeolocationRepository.hpp GeolocationRepository.cpp
    BaseApiClient.hpp BaseApiClient.cpp
    ApiClient.hpp ApiClient.cpp
    GeolocationSerializer.hpp GeolocationSerializer.cpp
    SettingsBackend.hpp SettingsBackend.cpp
)

qt_add_qml_module(appgeolocator
    URI geolocator
    VERSION 1.0
    QML_FILES
        Main.qml
        SearchDialog.qml
        GeolocationTable.qml
        GeolocationMap.qml
        GeolocationDialog.qml
        SettingsDialog.qml
        SOURCES
            SearchBackend.hpp SearchBackend.cpp
            GeolocationListModel.hpp GeolocationListModel.cpp
            SettingsBackend.hpp SettingsBackend.cpp
    )

target_link_libraries(appgeolocator
    PRIVATE Qt6::Quick Qt6::Sql Qt6::Location
)

set_target_properties(appgeolocator PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
