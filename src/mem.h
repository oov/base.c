#pragma once
#include "ovbase.h"

bool mem_core_(void *const pp, size_t const sz MEM_FILEPOS_PARAMS);
void *ov_hm_malloc(size_t const s, void *const udata);
void ov_hm_free(void *const p, void *const udata);
