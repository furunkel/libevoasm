//
// Created by jap on 9/9/16.
//

#include "evoasm-program-pop-params.h"
#include "evoasm-alloc.h"
#include "evoasm-program-pop.h"

_EVOASM_DEF_ALLOC_FREE_FUNCS(program_pop_params)
_EVOASM_DEF_ZERO_INIT_FUNC(program_pop_params)

#define _EVOASM_POP_PARAMS_DEF_GETTER_SETTER(field, type) _EVOASM_DEF_GETTER_SETTER(program_pop_params, field, type)

_EVOASM_POP_PARAMS_DEF_GETTER_SETTER(min_kernel_count, evoasm_kernel_count_t)
_EVOASM_POP_PARAMS_DEF_GETTER_SETTER(max_kernel_count, evoasm_kernel_count_t)
_EVOASM_POP_PARAMS_DEF_GETTER_SETTER(min_kernel_size, uint16_t)
_EVOASM_POP_PARAMS_DEF_GETTER_SETTER(max_kernel_size, uint16_t)
_EVOASM_POP_PARAMS_DEF_GETTER_SETTER(recur_limit, uint32_t)
_EVOASM_POP_PARAMS_DEF_GETTER_SETTER(inst_count, uint16_t)
_EVOASM_DEF_GETTER(program_pop_params, program_input, evoasm_program_io_t *)
_EVOASM_DEF_GETTER(program_pop_params, program_output, evoasm_program_io_t *)

void
evoasm_program_pop_params_set_inst(evoasm_program_pop_params_t *program_pop_params, unsigned index, evoasm_inst_id_t inst_id) {
  program_pop_params->inst_ids[index] = inst_id;
}

evoasm_inst_id_t
evoasm_program_pop_params_get_inst(evoasm_program_pop_params_t *program_pop_params, unsigned index) {
  return program_pop_params->inst_ids[index];
}

bool
evoasm_program_pop_params_valid(evoasm_program_pop_params_t *program_pop_params) {
  if(!evoasm_pop_params_valid(&program_pop_params->pop_params)) goto fail;

  if(program_pop_params->max_kernel_count > EVOASM_PROGRAM_MAX_SIZE) {
    evoasm_error(EVOASM_ERROR_TYPE_ARG, EVOASM_ERROR_CODE_NONE,
                 NULL, "Program size cannot exceed %d", EVOASM_PROGRAM_MAX_SIZE);
    goto fail;
  }

  if(program_pop_params->inst_count == 0) {
    evoasm_error(EVOASM_ERROR_TYPE_ARG, EVOASM_ERROR_CODE_NONE,
                 NULL, "No instructions given");
    goto fail;
  }

  if(program_pop_params->program_input == NULL || program_pop_params->program_input->len == 0) {
    evoasm_error(EVOASM_ERROR_TYPE_ARG, EVOASM_ERROR_CODE_NONE,
                 NULL, "No input values given");
    goto fail;
  }

  if(program_pop_params->program_output == NULL || program_pop_params->program_output->len == 0) {
    evoasm_error(EVOASM_ERROR_TYPE_ARG, EVOASM_ERROR_CODE_NONE,
                 NULL, "No output values given");
    goto fail;
  }

  if(program_pop_params->min_kernel_count == 0 || program_pop_params->min_kernel_count > program_pop_params->max_kernel_count) {
    evoasm_error(EVOASM_ERROR_TYPE_ARG, EVOASM_ERROR_CODE_NONE,
                 NULL, "Invalid kernel count");
    goto fail;
  }

  if(program_pop_params->min_kernel_size == 0 || program_pop_params->min_kernel_size > program_pop_params->max_kernel_size) {
    evoasm_error(EVOASM_ERROR_TYPE_ARG, EVOASM_ERROR_CODE_NONE,
                 NULL, "Invalid kernel size");
    goto fail;
  }

  return true;

fail:
  return false;
}

void
evoasm_program_pop_params_destroy(evoasm_program_pop_params_t *program_pop_params) {
}

void
evoasm_program_pop_params_set_program_input(evoasm_program_pop_params_t *program_pop_params, evoasm_program_io_t *program_io) {
  program_pop_params->program_input = program_io;
}

void
evoasm_program_pop_params_set_program_output(evoasm_program_pop_params_t *program_pop_params, evoasm_program_io_t *program_io) {
  program_pop_params->program_output = program_io;
}
