cmake_minimum_required(VERSION 3.0)
include_directories("../")

if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/bin)
	file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
endif()

function(addTest name)
        add_executable(test_${name} ${name}.cpp)
        target_link_libraries(test_${name} ${LIBRARIES})
        add_test(test_${name} test_${name})
endfunction()

addTest(MasterTest)
addTest(UnitTest)
addTest(Execution)
addTest(Variable)
addTest(Names)
addTest(Session)
addTest(Language)


