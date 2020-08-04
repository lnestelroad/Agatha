# Package.cmake
# -----------------------------------------------------------------------------
# Setup project zip package
#
# Uses OUI_VERSION to set the package version name
# So must include version before including this file
#
# SYS_NAME, SYS_VER, SYS_ARCH 
# env vars are set on build agent machines
# They are cached so they show up in the CMake gui
# The cached values take precedence; if not defined
# in the cache then they are set from the environment.
#------------------------------------------------------------------------------

IF(NOT DEFINED APP_VERSION)
  MESSAGE(FATAL_ERROR "APP_VERSION is defined!")
ENDIF()

IF(NOT DEFINED SYS_NAME)
  SET(SYS_NAME  $ENV{SYS_NAME} CACHE STRING "System OS name" FORCE)
ENDIF()

IF(NOT DEFINED SYS_VER)
  SET(SYS_VER   $ENV{SYS_VER}  CACHE STRING "System OS version")
ENDIF()

IF(NOT DEFINED SYS_ARCH)
  SET(SYS_ARCH  $ENV{SYS_ARCH} CACHE STRING "System processor type")
ENDIF()


# Setup package stuff
SET(CPACK_GENERATOR "ZIP")
# Force all components into one zip
SET(CPACK_MONOLITHIC_INSTALL 1)
# So zips do not contain toplevel PACKAGE_FILE_NAME dir
SET(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0) 
SET(CPACK_PACKAGE_NAME    "${CMAKE_PROJECT_NAME}")
SET(CPACK_PACKAGE_VERSION "${APP_VERSION}")
SET(CPACK_SYSTEM_NAME     "${SYS_NAME}-${SYS_VER}-${SYS_ARCH}")

# Include DispUtils for MSG_HDR and MSG_STR macros
INCLUDE(DispUtils)

MSG_HDR("Package Info")
MSG_STR("CPACK_GENERATOR          : ${CPACK_GENERATOR}")
MSG_STR("CPACK_PACKAGE_NAME       : ${CPACK_PACKAGE_NAME}")
MSG_STR("CPACK_PACKAGE_VERSION    : ${CPACK_PACKAGE_VERSION}")
MSG_STR("CPACK_SYSTEM_NAME        : ${CPACK_SYSTEM_NAME}")
MSG_STR("CPACK_PACKAGE_FILE_NAME  : ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_SYSTEM_NAME}")


# This include sets up the cpack config files
# Note: Also resets cpack variables for internal use so don't attempt to 
#       print them after this include.
INCLUDE(CPack)

