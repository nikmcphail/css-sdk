#include "hooks.h"

#include "src/core/core.h"
#include "src/core/menu/menu.h"
#include "src/sdk/interfaces/surface.h"

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

bool hooks_t::initialize() {
  this->directx_device_hook  = safetyhook::create_vmt(core::g_interfaces.directx_device);
  this->directx_present_hook = safetyhook::create_vm(this->directx_device_hook, 17,
                                                     &hooked_directx_device::hooked_present);
  this->directx_reset_hook   = safetyhook::create_vm(this->directx_device_hook, 16,
                                                     &hooked_directx_device::hooked_reset);

  this->surface_hook = safetyhook::create_vmt(core::g_interfaces.surface);
  this->lock_cursor_hook =
      safetyhook::create_vm(this->surface_hook, 62, &hooked_surface::hooked_lock_cursor);

  return true;
}

void hooks_t::unload() {
  directx_device_hook = {};
  surface_hook        = {};
}