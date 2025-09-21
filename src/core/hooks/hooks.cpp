#include "hooks.h"

#include "safetyhook/easy.hpp"
#include "src/core/core.h"
#include "src/core/menu/menu.h"
#include "src/sdk/interfaces/surface.h"
#include "src/sdk/misc/client_frame_stage.h"

#include <d3d9.h>

class hooked_directx_device {
public:
  HRESULT hooked_present(IDirect3DDevice9* device, RECT* source_rect, RECT* dest_rect,
                         HWND dest_window_override, RGNDATA* dirty_region) {
    core::on_present();
    return core::g_hooks.directx_present_hook.fastcall<HRESULT>(
        this, device, source_rect, dest_rect, dest_window_override, dirty_region);
  }

  HRESULT hooked_reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* present_parameters) {
    HRESULT result;

    {
      std::scoped_lock _{core::g_render.imgui_mutex};
      core::g_render.unload();
      result =
          core::g_hooks.directx_reset_hook.fastcall<HRESULT>(this, device, present_parameters);
      core::get_window_handle();
      core::g_render.initialize();
    }

    return result;
  }
};

class hooked_surface {
public:
  HCURSOR hooked_lock_cursor() {
    if (!core::g_globals.attached || core::g_globals.unloading)
      return core::g_hooks.lock_cursor_hook.fastcall<HCURSOR>(this);

    if (menu::open)
      return core::g_interfaces.surface->unlock_cursor();

    return core::g_hooks.lock_cursor_hook.fastcall<HCURSOR>(this);
  }
};

class hooked_base_client {
public:
  void hooked_frame_stage_notify(client_frame_stage_e stage) {
    if (!core::g_globals.attached || core::g_globals.unloading)
      core::g_hooks.frame_stage_notify_hook.fastcall(this, stage);

    core::pre_frame_stage_notify(stage);
    core::g_hooks.frame_stage_notify_hook.fastcall(this, stage);
    core::post_frame_stage_notify(stage);
  }

  void hooked_level_shutdown() { core::g_hooks.level_shutdown_hook.fastcall(this); }
};

bool hooks_t::initialize() {
  this->directx_device_hook  = safetyhook::create_vmt(core::g_interfaces.directx_device);
  this->directx_present_hook = safetyhook::create_vm(this->directx_device_hook, 17,
                                                     &hooked_directx_device::hooked_present);
  this->directx_reset_hook   = safetyhook::create_vm(this->directx_device_hook, 16,
                                                     &hooked_directx_device::hooked_reset);

  this->surface_hook = safetyhook::create_vmt(core::g_interfaces.surface);
  this->lock_cursor_hook =
      safetyhook::create_vm(this->surface_hook, 62, &hooked_surface::hooked_lock_cursor);

  this->base_client_hook        = safetyhook::create_vmt(core::g_interfaces.base_client);
  this->frame_stage_notify_hook = safetyhook::create_vm(
      this->base_client_hook, 35, &hooked_base_client::hooked_frame_stage_notify);
  this->level_shutdown_hook = safetyhook::create_vm(this->base_client_hook, 7,
                                                    &hooked_base_client::hooked_level_shutdown);

  return true;
}

void hooks_t::unload() {
  directx_device_hook = {};
  surface_hook        = {};
  base_client_hook    = {};
}