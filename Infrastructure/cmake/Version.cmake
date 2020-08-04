# Version.cmake
# -----------------------------------------------------------------------------
# Reads a project version.txt file and sets the following cmake variables
# If version.txt file is not found then cmake error is issued
#
# APP_VERSION        : String X.Y
# APP_VERSION_MAJOR  : String X
# APP_VERSION_MINOR  : String Y
# APP_VERSION_NUM    : Intger 
#
# To use create a version.txt file in the top level of your project source
# The first line of the file should be in the form X.Y
# 
# In top level CMakeLsits.txt file include this Version code
#
# INCLUDE(Version)
#
#------------------------------------------------------------------------------


# Check if project version file exists
if(EXISTS "${CMAKE_SOURCE_DIR}/version.txt")

  # Get project version from version.txt file
  FILE(STRINGS "${CMAKE_SOURCE_DIR}/version.txt" "APP_VERSION" LIMIT_COUNT 1 REGEX "^([0-9]*)\\.([0-9]*).*")

  # Get split into major and minor strings
  STRING(REGEX REPLACE "^([0-9]*)\\.([0-9]*).*" "\\1" "APP_VERSION_MAJOR" "${APP_VERSION}")
  STRING(REGEX REPLACE "^([0-9]*)\\.([0-9]*).*" "\\2" "APP_VERSION_MINOR" "${APP_VERSION}")
 
  # Compute the integer version number
  MATH(EXPR "APP_VERSION_NUM" "${APP_VERSION_MAJOR} * 1000000 + ${APP_VERSION_MINOR} * 1000 + 0")

else()

  # Version file not found
  MESSAGE(FATAL_ERROR "Project version.txt file not found!" )

endif()

# Include DispUtils for MSG_HDR and MSG_STR macros
INCLUDE(DispUtils)

# Display version info
MSG_HDR("Version Info")
MSG_STR("APP_VERSION       : ${APP_VERSION}")
MSG_STR("APP_VERSION_MAJOR : ${APP_VERSION_MAJOR}")
MSG_STR("APP_VERSION_MINOR : ${APP_VERSION_MINOR}")
MSG_STR("APP_VERSION_NUM   : ${APP_VERSION_NUM}")

