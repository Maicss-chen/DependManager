add_library(bsparser
  BSParser.h
  XMakeBSParser.h)
target_link_libraries(bsparser
  cjson)