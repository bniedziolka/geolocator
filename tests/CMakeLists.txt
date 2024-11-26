add_executable(geolocator_unit_tests
    SearchBackendTests.cpp
    ../src/SearchBackend.cpp
    ../src/BaseApiClient.cpp
    ../src/ApiClient.cpp
    ../src/GeolocationSerializer.cpp
    ../src/Geolocation.hpp
    ../src/SettingsBackend.cpp
    GeolocationRepositoryTests.cpp
    ../src/GeolocationRepository.cpp
    main.cpp
    GeolocationSerializerTests.cpp
)

target_include_directories(geolocator_unit_tests PRIVATE ../src)
target_link_libraries(geolocator_unit_tests PRIVATE Qt6::Quick Qt6::Test Qt6::Sql gtest gtest_main gmock gmock_main)

add_test(NAME geolocator_unit_tests COMMAND geolocator_unit_tests)
