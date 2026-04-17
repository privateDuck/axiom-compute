set(UI_SOURCES
        mainwindow.cpp mainwindow.hpp
        # mainwindow.ui # If using Qt Designer
)

# Create the UI library
add_library(atlas_ui STATIC ${UI_SOURCES})

# Turn on Qt's magic ONLY for this library
set_target_properties(atlas_ui PROPERTIES
        AUTOMOC ON
        AUTOUIC ON
        AUTORCC ON
)

# Link Qt to this library
target_link_libraries(atlas_ui PRIVATE Qt6::Widgets)

# Allow other projects to include the UI headers
target_include_directories(atlas_ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})