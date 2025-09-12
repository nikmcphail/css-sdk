#pragma once

#define FLOW_OUTGOING 0
#define FLOW_INCOMING 1
#define MAX_FLOWS     2

class i_net_channel_info_t {
public:
  virtual const char* get_name(void) const                                               = 0;
  virtual const char* get_address(void) const                                            = 0;
  virtual float       get_time(void) const                                               = 0;
  virtual float       get_time_connected(void) const                                     = 0;
  virtual int         get_buffer_size(void) const                                        = 0;
  virtual int         get_data_rate(void) const                                          = 0;
  virtual bool        is_loopback(void) const                                            = 0;
  virtual bool        is_timing_out(void) const                                          = 0;
  virtual bool        is_playback(void) const                                            = 0;
  virtual float       get_latency(int flow) const                                        = 0;
  virtual float       get_avg_latency(int flow) const                                    = 0;
  virtual float       get_avg_loss(int flow) const                                       = 0;
  virtual float       get_avg_choke(int flow) const                                      = 0;
  virtual float       get_avg_data(int flow) const                                       = 0;
  virtual float       get_avg_packets(int flow) const                                    = 0;
  virtual int         get_total_data(int flow) const                                     = 0;
  virtual int         get_sequence_number(int flow) const                                = 0;
  virtual bool        is_valid_packet(int flow, int frame_number) const                  = 0;
  virtual float       get_packet_time(int flow, int frame_number) const                  = 0;
  virtual int         get_packet_bytes(int flow, int frame_number, int group) const      = 0;
  virtual bool        get_stream_progress(int flow, int* received, int* total) const     = 0;
  virtual float       get_time_since_last_received(void) const                           = 0;
  virtual float       get_command_interpolation_amount(int flow, int frame_number) const = 0;
  virtual void        get_packet_response_latency(int flow, int frame_number, int* latency_ms,
                                                  int* choke) const                      = 0;
  virtual void        get_remote_framerate(float* frame_time,
                                           float* frame_time_standard_deviation) const   = 0;
  virtual float       get_timeout_seconds() const                                        = 0;
};