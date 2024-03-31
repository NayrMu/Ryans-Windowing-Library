#pragma once

#define EXIT(location, code) \
        printf("::%s ERROR:: CODE: %d\n", location, code); \
        exit(code);

#define SOFT_EXIT(location, code) \
        printf("::%s ERROR:: CODE: %d\n", location, code); \
        return;

enum RERROR {
  ERROR_NONE = 0,
  NULL_AFTER_CREATION = 101,
  NULL_PARAM,
  INVALID_INPUT

};