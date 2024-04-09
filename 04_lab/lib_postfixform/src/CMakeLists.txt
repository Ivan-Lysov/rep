set(target ${MP2_POSTFIXFORM_LIBRARY})

file(GLOB hdrs "*.h*" "${MP2_POSTFIXFORM_INCLUDE}/*.h*")
file(GLOB srcs "*.cpp")

include_directories("${MP2_POSTFIXFORM_INCLUDE}")

add_library(${target} STATIC ${srcs} ${hdrs})