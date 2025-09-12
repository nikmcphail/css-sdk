#pragma once

typedef enum {
  BITBUFERROR_VALUE_OUT_OF_RANGE = 0, // Tried to write a value with too few bits.
  BITBUFERROR_BUFFER_OVERRUN,         // Was about to overrun a buffer.

  BITBUFERROR_NUM_ERRORS
} bitbuf_error_type_e;