#include "entities.h"
#include "src/core/core.h"

#include "src/sdk/main/cs_player.h"
#include "src/sdk/interfaces/engine_client.h"
#include "src/sdk/interfaces/client_entity_list.h"

// TODO: Store more than just local player, local weapon, and player resource
void entities_t::store() {
  auto local = core::get_local_player();
  if (!local)
    return;

  local_player = local;
  local_weapon = local->active_weapon()->as<void>();

  for (int i = core::g_interfaces.engine_client->get_max_clients() + 1;
       i <= core::g_interfaces.entity_list->get_highest_entity_index(); i++) {
    auto entity = core::g_interfaces.entity_list->get_client_entity(i)->as<base_entity_t>();
    if (!entity)
      continue;

    auto class_id = entity->get_class_id();

    switch (class_id) {
      case cs_class_id_e::CCSPlayerResource:
        player_resource = entity->as<player_resource_t>();
        break;

      default:
        break;
    }
  }
}

// May need to have LevelShutdown specific additions in the future.
void entities_t::clear() {
  local_player    = nullptr;
  local_weapon    = nullptr;
  player_resource = nullptr;
}