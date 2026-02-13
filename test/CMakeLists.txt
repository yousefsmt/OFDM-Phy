# =========================
# Collect test sources
# =========================
file(GLOB TEST_SOURCES
    *.c
)

foreach(test_src ${TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)

    add_executable(${test_name}
        ${test_src}
        ${PROJECT_SOURCE_DIR}/src/fft.c
        ${PROJECT_SOURCE_DIR}/src/ifft.c
        ${PROJECT_SOURCE_DIR}/src/qam.c
        ${PROJECT_SOURCE_DIR}/src/ofdm.c
        ${PROJECT_SOURCE_DIR}/src/libcfg.c
    )

    target_include_directories(${test_name}
        PRIVATE
            ${PROJECT_SOURCE_DIR}/include
            ${FFTW3_INCLUDE_DIRS}
    )

    target_link_libraries(${test_name}
        PRIVATE
            ${FFTW3_LIBRARIES}
            m
    )

    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
