add_executable(atlas_runner main.cpp)

# Turn on AUTOMOC here too, in case your main.cpp uses Qt features directly
set_target_properties(atlas_runner PROPERTIES AUTOMOC ON)

# Link EVERYTHING together here
target_link_libraries(atlas_runner PRIVATE
        atlas_core   # Your library from the src/ folder
        atlas_ui     # Your library from the ui/ folder
        Qt6::Widgets # Qt itself
)