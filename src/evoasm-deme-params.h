/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2016, Julian Aron Prenner <jap@polyadic.com>
 */

#pragma once

#include "evoasm-domain.h"
#include "evoasm-param.h"
#include "evoasm.h"

typedef double evoasm_loss_t;

#define EVOASM_DEME_PARAMS_MAX_PARAMS 32

struct evoasm_deme_params_s;

typedef bool (*evoasm_deme_params_valid_func_t)(struct evoasm_deme_params_s *deme_params);

typedef struct {
  evoasm_deme_params_valid_func_t valid_func;
} evoasm_deme_params_cls_t;

typedef struct evoasm_deme_params_s {
  evoasm_param_id_t param_ids[EVOASM_DEME_PARAMS_MAX_PARAMS];
  evoasm_domain_t *domains[EVOASM_DEME_PARAMS_MAX_PARAMS];
  uint8_t n_params;
  uint32_t size;
  uint32_t mut_rate;
  evoasm_prng_state_t seed;
  const evoasm_deme_params_cls_t *cls;
} evoasm_deme_params_t;


void
evoasm_deme_params_init(evoasm_deme_params_t *deme_params, const evoasm_deme_params_cls_t *cls);

bool
evoasm_deme_params_valid(evoasm_deme_params_t *deme_params);
