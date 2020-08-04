# DispUtils.cmake
# -----------------------------------------------------------------------------
# This file contains cmake macros to used to display status message
# headers and strings as well as macros to display system
# build information.
#
# To use these macros include this file in your CMakeLists.txt file:
# INCLUDE(DispUtils)
#
#------------------------------------------------------------------------------


# Print a section separator line
MACRO(MSG_SEP)
  MESSAGE(STATUS "----------------------------------------------------------------------")
ENDMACRO()

# Print a message info header line
MACRO(MSG_HDR title)
  MESSAGE(STATUS "")
  MESSAGE(STATUS ${title})
  MESSAGE(STATUS "----------------------------------------------------------------------")
ENDMACRO()


# Print a message info line
MACRO(MSG_STR str)
  MESSAGE(STATUS ${str})
ENDMACRO()


# Print each list item on new line
MACRO(MSG_LIST l)
  SET(_l_len 0)
  FOREACH(v ${l})
    MESSAGE(STATUS "${v}")
    MATH(EXPR _l_len "${_l_len}+1")
  ENDFOREACH()
  MESSAGE(STATUS "Size:${_l_len}")
ENDMACRO()








