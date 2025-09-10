#pragma once

#include "base_combat_character.h"

#define LIFE_ALIVE       0 // alive
#define LIFE_DYING       1 // playing death animation, falling waiting to hit ground
#define LIFE_DEAD        2
#define LIFE_RESPAWNABLE 3
#define LIFE_DISCARDBODY 4

class base_player_t : public base_combat_character_t {
public:
  NETVAR(local, void*, "CBasePlayer", "m_Local");
  NETVAR(area_bits, void*, "CBasePlayer", "m_chAreaBits");
  NETVAR(area_portal_bits, void*, "CBasePlayer", "m_chAreaPortalBits");
  NETVAR(hide_hud, int, "CBasePlayer", "m_iHideHUD");
  NETVAR(fov_rate, float, "CBasePlayer", "m_flFOVRate");
  NETVAR(ducked, bool, "CBasePlayer", "m_bDucked");
  NETVAR(ducking, bool, "CBasePlayer", "m_bDucking");
  NETVAR(in_duck_jump, bool, "CBasePlayer", "m_bInDuckJump");
  NETVAR(duck_time, float, "CBasePlayer", "m_flDucktime");
  NETVAR(duck_jump_time, float, "CBasePlayer", "m_flDuckJumpTime");
  NETVAR(jump_time, float, "CBasePlayer", "m_flJumpTime");
  NETVAR(fall_velocity, float, "CBasePlayer", "m_flFallVelocity");
  NETVAR(punch_angle, vector3_t, "CBasePlayer", "m_vecPunchAngle");
  NETVAR(punch_angle_vel, vector3_t, "CBasePlayer", "m_vecPunchAngleVel");
  NETVAR(draw_viewmodel, bool, "CBasePlayer", "m_bDrawViewmodel");
  NETVAR(wearing_suit, bool, "CBasePlayer", "m_bWearingSuit");
  NETVAR(poisoned, bool, "CBasePlayer", "m_bPoisoned");
  NETVAR(step_size, float, "CBasePlayer", "m_flStepSize");
  NETVAR(allow_auto_movement, bool, "CBasePlayer", "m_bAllowAutoMovement");
  NETVAR(view_offset, vector3_t, "CBasePlayer", "m_vecViewOffset[0]");
  NETVAR(friction, float, "CBasePlayer", "m_flFriction");
  NETVAR(ammo, void*, "CBasePlayer", "m_iAmmo");
  NETVAR(on_target, int, "CBasePlayer", "m_fOnTarget");
  NETVAR(tick_base, int, "CBasePlayer", "m_nTickBase");
  NETVAR(next_think_tick, int, "CBasePlayer", "m_nNextThinkTick");
  NETVAR(last_weapon, ehandle, "CBasePlayer", "m_hLastWeapon");
  NETVAR(ground_entity, ehandle, "CBasePlayer", "m_hGroundEntity");
  NETVAR(velocity, vector3_t, "CBasePlayer", "m_vecVelocity[0]");
  NETVAR(base_velocity, vector3_t, "CBasePlayer", "m_vecBaseVelocity");
  NETVAR(constraint_entity, ehandle, "CBasePlayer", "m_hConstraintEntity");
  NETVAR(constraint_center, vector3_t, "CBasePlayer", "m_vecConstraintCenter");
  NETVAR(constraint_radius, float, "CBasePlayer", "m_flConstraintRadius");
  NETVAR(constraint_width, float, "CBasePlayer", "m_flConstraintWidth");
  NETVAR(constraint_speed_factor, float, "CBasePlayer", "m_flConstraintSpeedFactor");
  NETVAR(death_time, float, "CBasePlayer", "m_flDeathTime");
  NETVAR(water_level, byte, "CBasePlayer", "m_nWaterLevel");
  NETVAR(lagged_movement_value, float, "CBasePlayer", "m_flLaggedMovementValue");
  NETVAR(pl, void*, "CBasePlayer", "pl");
  NETVAR(dead_flag, int, "CBasePlayer", "deadflag");
  NETVAR(fov, int, "CBasePlayer", "m_iFOV");
  NETVAR(fov_start, int, "CBasePlayer", "m_iFOVStart");
  NETVAR(fov_time, float, "CBasePlayer", "m_flFOVTime");
  NETVAR(default_fov, int, "CBasePlayer", "m_iDefaultFOV");
  NETVAR(zoom_owner, ehandle, "CBasePlayer", "m_hZoomOwner");
  NETVAR(vehicle, ehandle, "CBasePlayer", "m_hVehicle");
  NETVAR(use_entity, ehandle, "CBasePlayer", "m_hUseEntity");
  NETVAR(health, int, "CBasePlayer", "m_iHealth");
  NETVAR(life_state, byte, "CBasePlayer", "m_lifeState");
  NETVAR(bonus_progress, int, "CBasePlayer", "m_iBonusProgress");
  NETVAR(bonus_challenge, int, "CBasePlayer", "m_iBonusChallenge");
  NETVAR(max_speed, float, "CBasePlayer", "m_flMaxspeed");
  NETVAR(flags, int, "CBasePlayer", "m_fFlags");
  NETVAR(observer_mode, int, "CBasePlayer", "m_iObserverMode");
  NETVAR(observer_target, ehandle, "CBasePlayer", "m_hObserverTarget");
  NETVAR(view_model, ehandle, "CBasePlayer", "m_hViewModel[0]");
  NETVAR(last_place_name, const char*, "CBasePlayer", "m_szLastPlaceName");
};