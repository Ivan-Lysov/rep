set(target ${MP2_LISTS_LIBRARY})

file(GLOB hdrs "*.h*" "${MP2_LISTS_INCLUDE}/*.h*")
file(GLOB srcs "*.cpp")

include_directories("${MP2_LISTS_INCLUDE}")

add_library(${target} STATIC ${srcs} ${hdrs})