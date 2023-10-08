set(HEADERS
        "${PROJECT_SOURCE_DIR}/include/Lab2/Array.hpp"
        "${PROJECT_SOURCE_DIR}/include/Lab2/Array.inl")

add_library(lab2 INTERFACE ${HEADERS})
target_include_directories(lab2 INTERFACE "${PROJECT_SOURCE_DIR}/include")
target_compile_features(lab2 INTERFACE cxx_std_20)
