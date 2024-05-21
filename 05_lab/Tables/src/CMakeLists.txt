set(target ${MP2_TABLES_LIBRARY})

file(GLOB hdrs "*.h*" "${MP2_TABLES_INCLUDE}/*.h*")
file(GLOB srcs "*.cpp")

include_directories("${MP2_TABLES_INCLUDE}" "${MP2_POLYNOMS_INCLUDE}")

add_library(${target} STATIC ${srcs} ${hdrs})
target_link_libraries(${target})