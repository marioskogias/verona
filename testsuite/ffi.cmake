include(${CMAKE_CURRENT_LIST_DIR}/common.cmake)

set(ACTUAL_DUMP ${CMAKE_CURRENT_BINARY_DIR}/${TEST_NAME})

PrepareTest(VERONAF_FLAGS EXPECTED_DUMP ACTUAL_DUMP)

CheckStatus(
  COMMAND ${VERONA_FFI} --config ${TEST_FILE}
  OUTPUT_FILE ${ACTUAL_DUMP}/output.txt
  EXPECTED_STATUS 0)

if(EXPECTED_DUMP)
  CheckDump(${EXPECTED_DUMP} ${ACTUAL_DUMP})
endif()