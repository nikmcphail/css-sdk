#pragma once

#include "../main/vector3.h"

class base_entity_t;
class i_trace_filter_t;

struct beam_trail_t {
  beam_trail_t* next;
  float         die;
  vector3_t     org;
  vector3_t     vel;
};

struct beam_t {
  unsigned char    default_client_renderable[8];
  unsigned __int16 render_handle;
  vector3_t        mins;
  vector3_t        maxs;
  int*             query_handle_halo;
  float            halo_proxy_size;
  beam_t*          next;
  int              type;
  int              flags;
  int              num_attachments;
  vector3_t        attachment[10];
  vector3_t        delta;
  float            t;
  float            freq;
  float            die;
  float            width;
  float            end_width;
  float            fade_length;
  float            amplitude;
  float            life;
  float            r;
  float            g;
  float            b;
  float            brightness;
  float            speed;
  float            frame_rate;
  float            frame;
  int              segments;
  unsigned int     entity[10];
  int              attachment_index[10];
  int              model_index;
  int              halo_index;
  float            halo_scale;
  int              frame_count;
  float            rgb_noise[129];
  beam_trail_t*    trail;
  float            start_radius;
  float            end_radius;
  bool             calculated_noise;
  float            hdr_color_scale;
};

enum {
  FBEAM_STARTENTITY   = 0x00000001,
  FBEAM_ENDENTITY     = 0x00000002,
  FBEAM_FADEIN        = 0x00000004,
  FBEAM_FADEOUT       = 0x00000008,
  FBEAM_SINENOISE     = 0x00000010,
  FBEAM_SOLID         = 0x00000020,
  FBEAM_SHADEIN       = 0x00000040,
  FBEAM_SHADEOUT      = 0x00000080,
  FBEAM_ONLYNOISEONCE = 0x00000100, // Only calculate our noise once
  FBEAM_NOTILE        = 0x00000200,
  FBEAM_USE_HITBOXES =
      0x00000400, // Attachment indices represent hitbox indices instead when this is set.
  FBEAM_STARTVISIBLE =
      0x00000800,                // Has this client actually seen this beam's start entity yet?
  FBEAM_ENDVISIBLE = 0x00001000, // Has this client actually seen this beam's end entity yet?
  FBEAM_ISACTIVE   = 0x00002000,
  FBEAM_FOREVER    = 0x00004000,
  FBEAM_HALOBEAM =
      0x00008000, // When drawing a beam with a halo, don't ignore the segments and endwidth
  FBEAM_REVERSED = 0x00010000,
  NUM_BEAM_FLAGS = 17 // KEEP THIS UPDATED!
};

struct beam_info_t {
  int            type;
  base_entity_t* start_ent;
  int            start_attachment;
  base_entity_t* end_ent;
  int            end_attachment;
  vector3_t      start;
  vector3_t      end;
  int            model_index;
  const char*    model_name;
  int            halo_index;
  const char*    halo_name;
  float          halo_scale;
  float          life;
  float          width;
  float          end_width;
  float          fade_length;
  float          amplitude;
  float          brightness;
  float          speed;
  int            start_frame;
  float          frame_rate;
  float          red;
  float          green;
  float          blue;
  bool           renderable;
  int            segments;
  int            flags;
  vector3_t      center;
  float          start_radius;
  float          end_radius;

  beam_info_t() {
    type        = 0;
    segments    = -1;
    model_name  = NULL;
    halo_name   = NULL;
    model_index = -1;
    halo_index  = -1;
    renderable  = true;
    flags       = 0;
  }
};