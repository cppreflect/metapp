set(JSON_URL "https://github.com/nlohmann/json/releases/download/v3.7.0/json.hpp")
set(JSON_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include/")
set(JSON_FILE "${JSON_INCLUDE_DIR}/nlohmann/json.hpp")

if (NOT EXISTS "${JSON_FILE}")
  file(DOWNLOAD "${JSON_URL}" "${JSON_FILE}")
endif()

set(INJA_URL "https://github.com/pantor/inja/releases/download/v2.1.0/inja.hpp")
set(INJA_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include/")
set(INJA_FILE "${INJA_INCLUDE_DIR}/inja/inja.hpp")

if (NOT EXISTS "${INJA_FILE}")
  file(DOWNLOAD "${INJA_URL}" "${INJA_FILE}")
endif()


add_library(templatingLib INTERFACE) 
target_include_directories(templatingLib INTERFACE "${JSON_INCLUDE_DIR}")
