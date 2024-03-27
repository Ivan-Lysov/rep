set(target ${MP2_POLYNOMS_LIBRARY})

file(GLOB hdrs "*.h*" "${MP2_POLYNOMS_INCLUDE}/*.h*")
file(GLOB srcs "*.cpp")

include_directories("${MP2_POLYNOMS_INCLUDE}" "${MP2_LISTS_INCLUDE}" "${MP2_POSTFIXFORM_INCLUDE}")

add_library(${target} STATIC ${srcs} ${hdrs})
target_link_libraries(${target} ${MP2_LISTS_LIBRARY} ${MP2_POSTFIXFORM_LIBRARY})