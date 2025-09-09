#pragma once

#include "src/core/core.h"
#include "src/sdk/main/base_entity.h"
#include "src/sdk/main/base_handle.h"
#include "src/sdk/interfaces/client_entity_list.h"
#include "src/sdk/misc/cs_class_ids.h"

enum class trace_type_t {
  TRACE_EVERYTHING = 0,
  TRACE_WORLD_ONLY,
  TRACE_ENTITIES_ONLY,
  TRACE_EVERYTHING_FILTER_PROPS
};

class i_trace_filter_t {
  virtual bool should_hit_entity(base_entity_t* ent, int contents_mask) = 0;

  virtual trace_type_t get_type() const = 0;
};

class trace_filter_t : public i_trace_filter_t {
  virtual bool should_hit_entity(base_entity_t* ent, int contents_mask) {
    return ent != skip_entity;
  }

  virtual trace_type_t get_type() const { return trace_type_t::TRACE_EVERYTHING; }

public:
  trace_filter_t(base_entity_t* skip) : skip_entity(skip) {}

  base_entity_t* skip_entity;
};

class trace_filter_world_and_props_t : public i_trace_filter_t {
  virtual bool should_hit_entity(base_entity_t* ent, int contents_mask) {
    if (!ent || ent == skip_entity)
      return false;

    if (ent->get_ref_e_handle().get_serial_number() == (1 << 15))
      return core::g_interfaces.entity_list->get_client_entity(0) != skip_entity;

    if (team == -1)
      team = skip_entity ? skip_entity->team() : 0;

    switch (ent->get_client_networkable()->get_class_id()) {
      case cs_class_id_e::CBaseEntity:
      case cs_class_id_e::CBaseDoor:
      case cs_class_id_e::CDynamicProp:
      case cs_class_id_e::CPhysicsProp:
      case cs_class_id_e::CPhysicsPropMultiplayer:
      case cs_class_id_e::CFunc_LOD:
      case cs_class_id_e::CFuncTrackTrain:
      case cs_class_id_e::CFuncConveyor:
        return true;
      default:
        return false;
    }

    return false;
  }

  virtual trace_type_t get_type() const { return trace_type_t::TRACE_EVERYTHING_FILTER_PROPS; }

public:
  base_entity_t* skip_entity;
  int            team = -1;
};