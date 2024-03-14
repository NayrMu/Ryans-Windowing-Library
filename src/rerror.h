#pragma once

#define EXIT(location, code) \
        printf("::%s ERROR:: CODE: %d\n", location, code); \
        exit(code);

enum RERROR {
  ERROR_NONE = 0,
  NULL_AFTER_CREATION = 101,
  NULL_PARAM,
  
};