#include "wstr.h"

#ifdef USE_WSTR

#  include "ovprintf.h"

NODISCARD error wstr_sprintf_(struct wstr *const dest MEM_FILEPOS_PARAMS, wchar_t const *const format, ...) {
  va_list valist;
  va_start(valist, format);
  error err = wstr_vsprintf_(dest MEM_FILEPOS_VALUES_PASSTHRU, format, valist);
  if (efailed(err)) {
    err = ethru(err);
  }
  va_end(valist);
  return err;
}

NODISCARD error wstr_vsprintf_(struct wstr *const dest MEM_FILEPOS_PARAMS,
                               wchar_t const *const format,
                               va_list valist) {
  if (!dest || !format) {
    return errg(err_invalid_arugment);
  }
  error err = eok();
  va_list valist2;
  va_copy(valist2, valist);
  int r = ov_vsnprintf(dest->ptr, dest->cap, format, valist2);
  va_end(valist2);
  if (r < 0) {
    err = errg(err_unexpected);
    goto cleanup;
  }
  if (dest->cap > (size_t)r) {
    goto cleanup;
  }
  err = wstr_grow(dest, (size_t)r + 1 MEM_FILEPOS_VALUES_PASSTHRU);
  if (efailed(err)) {
    err = ethru(err);
    goto cleanup;
  }
  r = ov_vsnprintf(dest->ptr, dest->cap, format, valist);
  if (r < 0) {
    err = errg(err_unexpected);
    goto cleanup;
  }
cleanup:
  if (esucceeded(err)) {
    dest->len = (size_t)r;
  }
  return err;
}

#endif
