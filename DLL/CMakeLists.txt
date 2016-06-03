add_library(MemBrainDll64 SHARED IMPORTED)
set_target_properties(MemBrainDll64 PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/MemBrainDll64.dll")
set_target_properties(MemBrainDll64 PROPERTIES IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/MemBrainDll64.lib")
