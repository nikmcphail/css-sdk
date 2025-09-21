#pragma once

class vector3_t;
class qangle_t;

class i_prediction_t {
public:
  virtual ~i_prediction_t(void) {};

  virtual void init(void)     = 0;
  virtual void shutdown(void) = 0;

  virtual void update(int start_frame, bool valid_frame, int incoming_acknowledged,
                      int outgoing_command) = 0;

  virtual void pre_entity_packet_received(int commands_acknowledged,
                                          int current_world_update_packet) = 0;
  virtual void post_entity_packet_received(void)                           = 0;
  virtual void post_network_data_received(int commands_acknowledged)       = 0;

  virtual void on_received_uncompressed_packet(void) = 0;

  virtual void get_view_origin(vector3_t& origin)      = 0;
  virtual void set_view_origin(vector3_t& origin)      = 0;
  virtual void get_view_angles(qangle_t& angles)       = 0;
  virtual void set_view_angles(qangle_t& angles)       = 0;
  virtual void get_local_view_angles(qangle_t& angles) = 0;
  virtual void set_local_view_angles(qangle_t& angles) = 0;
};