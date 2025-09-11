cmake_minimum_required(VERSION 3.20)

project(css-sdk LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(CPM_DOWNLOAD_VERSION 0.38.7)
set(CPM_HASH_SUM "83e5eb71b2bbb8b1f2ad38f1950287a057624e385c238f6087f94cdfc44af9c5")

if (CPM_SOURCE_CACHE)
    set(CPM_DOWNLOAD_LOCATION "${CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
elseif (DEFINED ENV{CPM_SOURCE_CACHE})
    set(CPM_DOWNLOAD_LOCATION "$ENV{CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
else ()
    set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
endif ()

get_filename_component(CPM_DOWNLOAD_LOCATION ${CPM_DOWNLOAD_LOCATION} ABSOLUTE)

if (NOT EXISTS ${CPM_DOWNLOAD_LOCATION})
    message(STATUS "Downloading CPM.cmake to: ${CPM_DOWNLOAD_LOCATION}")

    file(DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
        ${CPM_DOWNLOAD_LOCATION} EXPECTED_HASH SHA256=${CPM_HASH_SUM}
    )
endif ()

include(${CPM_DOWNLOAD_LOCATION})

CPMAddPackage(
    NAME fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG e69e5f977d458f2650bb346dadf2ad30c5320281 # 10.2.1
)

CPMAddPackage(
    NAME safetyhook
    GIT_REPOSITORY https://github.com/cursey/safetyhook.git
    GIT_TAG main
    OPTIONS "SAFETYHOOK_FETCH_ZYDIS ON"
)

CPMAddPackage("gh:ocornut/imgui@1.91.9-docking")
CPMAddPackage("gh:freetype/freetype#d41a855aab6d8ce131c465ce01f0f536e0fb2269")
CPMAddPackage("gh:epezent/implot@0.16")
CPMAddPackage("gh:brenocq/implot3d@0.2")

add_library(css-sdk SHARED
    src/main.cpp
    src/core/core.cpp
    src/core/interfaces/interfaces.cpp
    src/core/netvars/netvars.cpp
    src/core/addresses/addresses.cpp
    src/core/hooks/hooks.cpp
    src/core/render/render.cpp
    src/core/menu/menu.cpp
    src/library/utils.cpp
    src/library/math.cpp
    src/sdk/main/base_animating.cpp
)

set_target_properties(css-sdk PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output
)

if (imgui_ADDED)
    target_sources(css-sdk PRIVATE
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/misc/freetype/imgui_freetype.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_dx9.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
    )

    target_include_directories(css-sdk PUBLIC
        $<BUILD_INTERFACE:${imgui_SOURCE_DIR}>
        $<BUILD_INTERFACE:${imgui_SOURCE_DIR}/backends>
        )

    target_compile_definitions(css-sdk PUBLIC
        IMGUI_IMPL_WIN32_DISABLE_GAMEPAD
    )
endif ()

if (implot_ADDED)
    target_sources(css-sdk PRIVATE
        ${implot_SOURCE_DIR}/implot.cpp
        ${implot_SOURCE_DIR}/implot_items.cpp
        ${implot_SOURCE_DIR}/implot_demo.cpp
    )

    target_include_directories(css-sdk PUBLIC
        $<BUILD_INTERFACE:${implot_SOURCE_DIR}>
    )
endif ()

if (implot3d_ADDED)
    target_sources(css-sdk PRIVATE
        ${implot3d_SOURCE_DIR}/implot3d.cpp
        ${implot3d_SOURCE_DIR}/implot3d_items.cpp
        ${implot3d_SOURCE_DIR}/implot3d_demo.cpp
        ${implot3d_SOURCE_DIR}/implot3d_meshes.cpp
    )

    target_include_directories(css-sdk PUBLIC
        $<BUILD_INTERFACE:${implot3d_SOURCE_DIR}>
    )
endif ()

target_include_directories(css-sdk PRIVATE /)
target_compile_features(css-sdk PUBLIC cxx_std_23)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(css-sdk PRIVATE
        NDEBUG
        NOMINMAX
        _HAS_EXCEPTIONS=0
        _ITERATOR_DEBUG_LEVEL=0
        WINVER=0x0A00
        _WIN32_WINNT=0x0A00
        JSON_NOEXCEPTION
        INSECURE_CHECK
        _CONFIGURATION="Release"
        SDK_FONTS
    )

    target_compile_options(css-sdk PRIVATE
        /O2
        /fp:precise
        /Ob2
        /GR-
        /GS-
        /EHsc
        /guard:cf-
        /clang:-mfpmath=sse
        /clang:-march=haswell # Haswell minimum.
        /clang:-mtune=generic
        /clang:-fno-ident
        /clang:-fno-unwind-tables
        /clang:-fno-asynchronous-unwind-tables
        /clang:-g0
    )
elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(css-sdk PRIVATE
        NOMINMAX
        DEBUG
        INSECURE_CHECK
        _CONFIGURATION="Debug"
        # LIST_INTERFACE_VERSIONS
        # SDK_FONTS
    )

    target_compile_options(css-sdk PRIVATE
        /Od
        /fp:precise
        /Ob2
        /GR-
        /GS-
        /EHsc
        /guard:cf-
        /clang:-mfpmath=sse
        /clang:-march=haswell # Haswell minimum.
        /clang:-mtune=generic
        /clang:-fno-ident
        /clang:-fno-unwind-tables
        /clang:-fno-asynchronous-unwind-tables
        /clang:-g
    )
endif ()

target_link_libraries(css-sdk PRIVATE 
    freetype
    d3d9
    safetyhook
    fmt::fmt
)