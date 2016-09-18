//
// Created by jap on 9/9/16.
//

#include "evoasm-deme-params.h"

_EVOASM_DEF_ALLOC_FREE_FUNCS(deme_params)
_EVOASM_DEF_ZERO_INIT_FUNC(deme_params)

#define _EVOASM_DEME_PARAMS_DEF_FIELD_ACCESSOR(field, type) _EVOASM_DEF_FIELD_ACCESSOR(deme_params, field, type)

_EVOASM_DEME_PARAMS_DEF_FIELD_ACCESSOR(size, uint32_t)
_EVOASM_DEME_PARAMS_DEF_FIELD_ACCESSOR(mut_rate, uint32_t)
_EVOASM_DEME_PARAMS_DEF_FIELD_ACCESSOR(max_loss, evoasm_loss_t)
_EVOASM_DEME_PARAMS_DEF_FIELD_ACCESSOR(n_params, uint8_t)


static evoasm_domain_t **
evoasm_deme_params_find_domain(evoasm_deme_params_t *deme_params, evoasm_param_id_t param_id) {
  unsigned i;
  for(i = 0; i < deme_params->n_params; i++) {
    if(deme_params->param_ids[i] == param_id) {
      return &deme_params->domains[i];
    }
  }
  return NULL;
}

bool
evoasm_deme_params_set_domain(evoasm_deme_params_t *deme_params, evoasm_param_id_t param_id, evoasm_domain_t *domain) {
  evoasm_domain_t **domain_ptr = evoasm_deme_params_find_domain(deme_params, param_id);
  if(domain_ptr) {
    *domain_ptr = domain;
    return true;
  }
  else {
    return false;
  }
}

evoasm_domain_t *
evoasm_deme_params_domain(evoasm_deme_params_t *deme_params, evoasm_param_id_t param_id) {
  evoasm_domain_t **domain_ptr = evoasm_deme_params_find_domain(deme_params, param_id);
  if(domain_ptr) {
    return *domain_ptr;
  } else {
    return NULL;
  }
}

evoasm_param_id_t
evoasm_deme_params_param(evoasm_deme_params_t *deme_params, unsigned index) {
  return deme_params->param_ids[index];
}

void
evoasm_deme_params_set_param(evoasm_deme_params_t *deme_params, unsigned index, evoasm_param_id_t param) {
  deme_params->param_ids[index] = param;
}

uint8_t
evoasm_search_n_params(evoasm_deme_params_t *deme_params) {
  return deme_params->n_params;
}

uint64_t
evoasm_deme_params_seed(evoasm_deme_params_t *deme_params, unsigned index) {
  return deme_params->seed.data[index];
}

void
evoasm_deme_params_set_seed(evoasm_deme_params_t *deme_params, unsigned index, uint64_t seed) {
  deme_params->param_ids[index] = seed;
}

void
evoasm_deme_params_destroy(evoasm_deme_params_t *deme_params) {
}


bool
evoasm_deme_params_valid(evoasm_deme_params_t *deme_params) {

  if(deme_params->n_params == 0) {
    evoasm_set_error(EVOASM_ERROR_TYPE_ARG, EVOASM_N_ERROR_CODES,
                     NULL, "No parameters given");
    goto fail;
  }

  if(deme_params->size == 0) {
    evoasm_set_error(EVOASM_ERROR_TYPE_ARG, EVOASM_N_ERROR_CODES,
                     NULL, "Population size cannot be zero");
    goto fail;
  }

  return true;

fail:
  return false;
}
