#pragma once

#include "collision_property.h"
#include "base_handle.h"
#include "client_entity.h"
#include "color.h"

#include "src/core/netvars/netvars.h"

typedef handle_t<base_entity_t> ehandle;

class base_entity_t : public i_client_entity_t {
public:
  NETVAR(anim_time, float, "CBaseEntity", "m_flAnimTime");
  NETVAR(simulation_time, float, "CBaseEntity", "m_flSimulationTime");
  NETVAR(interpolation_frame, int, "CBaseEntity", "m_ubInterpolationFrame");
  NETVAR(origin, vector3_t, "CBaseEntity", "m_vecOrigin");
  NETVAR(rotation, vector3_t, "CBaseEntity", "m_angRotation");
  NETVAR(model_index, int, "CBaseEntity", "m_nModelIndex");
  NETVAR(effects, int, "CBaseEntity", "m_fEffects");
  NETVAR(render_mode, int, "CBaseEntity", "m_nRenderMode");
  NETVAR(render_fx, int, "CBaseEntity", "m_nRenderFX");
  NETVAR(color_render, color_t, "CBaseEntity", "m_clrRender");
  NETVAR(team, int, "CBaseEntity", "m_iTeamNum");
  NETVAR(collision_group, int, "CBaseEntity", "m_CollisionGroup");
  NETVAR(elasticity, float, "CBaseEntity", "m_flElasticity");
  NETVAR(shadow_cast_distance, float, "CBaseEntity", "m_flShadowCastDistance");
  NETVAR(owner_entity, ehandle, "CBaseEntity", "m_hOwnerEntity");
  NETVAR(effect_entity, ehandle, "CBaseEntity", "m_hEffectEntity");
  NETVAR(move_parent, int, "CBaseEntity", "moveparent");
  NETVAR(parent_attachment, int, "CBaseEntity", "m_iParentAttachment");
  NETVAR(collision, collision_property_t*, "CBaseEntity", "m_Collision");
  NETVAR(mins_pre_scaled, vector3_t, "CBaseEntity", "m_vecMinsPreScaled");
  NETVAR(maxs_pre_scaled, vector3_t, "CBaseEntity", "m_vecMaxsPreScaled");
  NETVAR(mins, vector3_t, "CBaseEntity", "m_vecMins");
  NETVAR(maxs, vector3_t, "CBaseEntity", "m_vecMaxs");
  NETVAR(solid_type, int, "CBaseEntity", "m_nSolidType");
  NETVAR(solid_flags, int, "CBaseEntity", "m_usSolidFlags");
  NETVAR(surround_type, int, "CBaseEntity", "m_nSurroundType");
  NETVAR(trigger_bloat, int, "CBaseEntity", "m_triggerBloat");
  NETVAR(uniform_trigger_bloat, bool, "CBaseEntity", "m_bUniformTriggerBloat");
  NETVAR(specified_surrounding_mins_pre_scaled, vector3_t, "CBaseEntity",
         "m_vecSpecifiedSurroundingMinsPreScaled");
  NETVAR(specified_surrounding_maxs_pre_scaled, vector3_t, "CBaseEntity",
         "m_vecSpecifiedSurroundingMaxsPreScaled");
  NETVAR(specified_surrounding_mins, vector3_t, "CBaseEntity", "m_vecSpecifiedSurroundingMins");
  NETVAR(specified_surrounding_maxs, vector3_t, "CBaseEntity", "m_vecSpecifiedSurroundingMaxs");
  NETVAR(texture_frame_index, int, "CBaseEntity", "m_iTextureFrameIndex");
  NETVAR(predictable_id, int, "CBaseEntity", "m_PredictableID");
  NETVAR(player_simulated, bool, "CBaseEntity", "m_bIsPlayerSimulated");
  NETVAR(simulated_every_tick, bool, "CBaseEntity", "m_bSimulatedEveryTick");
  NETVAR(animated_every_tick, bool, "CBaseEntity", "m_bAnimatedEveryTick");
  NETVAR(alternate_sorting, bool, "CBaseEntity", "m_bAlternateSorting");
  NETVAR(move_type, int, "CBaseEntity", "movetype");

  inline bool is_player() { return get_class_id() == cs_class_id_e::CCSPlayer; }
};