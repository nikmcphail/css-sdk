#pragma once

#include <Windows.h>

#include "i_net_channel_info.h"
#include "../misc/net_address.h"

enum connection_status_e {
  CONNECTION_STATE_DISCONNECTED = 0,
  CONNECTION_STATE_CONNECTING,
  CONNECTION_STATE_CONNECTION_FAILED,
  CONNECTION_STATE_CONNECTED
};

#define NET_MAX_DATAGRAM_PAYLOAD 1400

class i_net_channel_t : public i_net_channel_info_t {
public:
  virtual ~i_net_channel_t(void) {};
  virtual void set_data_rate(float rate) = 0;
  virtual bool
  register_message(void* msg) = 0; // maybe implement INetMessage later, maybe this is useful
  virtual void set_timeout(float seconds)                                  = 0;
  virtual void set_demo_recorder(void* recorder)                           = 0;
  virtual void set_challenge_number(unsigned int chnr)                     = 0;
  virtual void reset(void)                                                 = 0;
  virtual void clear(void)                                                 = 0;
  virtual void shutdown(const char* reason)                                = 0;
  virtual void process_playback(void)                                      = 0;
  virtual void process_packet(struct netpacket_s* packet, bool has_header) = 0;
  virtual bool sent_net_message(void*& msg, bool force_reliable = false,
                                bool voice = false)                        = 0;
  virtual bool send_data(void*& msg,
                         bool   reliable = true) = 0; // Also maybe implement bf_write
  virtual bool send_file(const char* file_name, unsigned int transfer_id)                  = 0;
  virtual void deny_file(const char* file_name, unsigned int transfer_id)                  = 0;
  virtual void request_file_old(const char* file_name, unsigned int transfer_id)           = 0;
  virtual void set_choked(void)                                                            = 0;
  virtual int  send_datagram(void* data)                                                   = 0;
  virtual bool transmit(bool only_reliable = false)                                        = 0;
  virtual const net_address_t& get_remote_address(void) const                              = 0;
  virtual void*                get_message_handler(void) const                             = 0;
  virtual int                  get_drop_number(void) const                                 = 0;
  virtual int                  get_socket(void) const                                      = 0;
  virtual unsigned int         get_challenge_number(void) const                            = 0;
  virtual void         get_sequence_data(int& out_sequence_number, int& in_sequence_number,
                                         int& out_sequence_number_ack)                     = 0;
  virtual void         set_sequence_data(int out_sequence_number, int in_sequence_number,
                                         int out_sequence_number_ack)                      = 0;
  virtual void         update_message_stats(int msg_group, int bits)                       = 0;
  virtual bool         can_packet(void) const                                              = 0;
  virtual bool         is_overflowed(void) const                                           = 0;
  virtual bool         is_timed_out(void) const                                            = 0;
  virtual bool         has_pending_reliable_data(void)                                     = 0;
  virtual void         set_file_transmission_mode(bool background_mode)                    = 0;
  virtual void         set_compression_mode(bool use_compression)                          = 0;
  virtual unsigned int request_file(const char* file_name)                                 = 0;
  virtual float        get_time_since_last_received(void) const                            = 0;
  virtual void         set_max_buffer_size(bool reliable, int bytes, bool voice = false)   = 0;
  virtual bool         is_null() const                                                     = 0;
  virtual int          get_num_bits_written(bool reliable)                                 = 0;
  virtual void         set_interpolation_amount(float interpolation_amount)                = 0;
  virtual void set_remote_framerate(float frame_time, float frame_time_standard_deviation) = 0;
  virtual void set_max_routable_payload_size(int split_size)                               = 0;
  virtual int  get_max_routable_payload_size()                                             = 0;
  virtual int  get_protocol_version()                                                      = 0;
};

#
class net_channel_t : public i_net_channel_t {
public:
  char pad_0[0x4];

public:
  int out_sequence_number;        // 0xc
  int in_sequence_number;         // 0x10
  int out_sequence_number_nr_ack; // 0x14
  int out_reliable_state;         // 0x18
  int in_reliable_state;          // 0x1c
  int choked_packets;             // 0x20
private:
  char pad_24[0x94];

public:
  int socket;                    // 0xb8
  int stream_socket;             // 0xbc
  int max_reliable_payload_size; // 0xc0
private:
  char pad_c4[0x44];

public:
  float last_received; // 0x108
  float connect_time;  // 0x10c
private:
  char pad_110[0x8];

public:
  int rate; // 0x118
private:
  char pad_11c[0x2240];

public:
  int  packet_drop; // 0x235c
  char name[32];    // 0x2360
private:
  char pad_2380[0x3c];

public:
  float interpolation_amount;            // 0x23bc
  float remote_frame_time;               // 0x23c0
  float remote_frame_time_std_deviation; // 0x23c4
  int   max_routable_payload_size;       // 0x23c8
  int   split_packet_sequence;           // 0x23cc
};