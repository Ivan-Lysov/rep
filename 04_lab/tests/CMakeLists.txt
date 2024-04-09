set(target ${MP2_TESTS})

file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

include_directories("${MP2_LISTS_INCLUDE}" "${MP2_POLYNOMS_INCLUDE}" "${MP2_POSTFIXFORM_INCLUDE}" "../gtest")

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} gtest ${MP2_LISTS_LIBRARY} ${MP2_POLYNOMS_LIBRARY} ${MP2_POSTFIXFORM_LIBRARY})
