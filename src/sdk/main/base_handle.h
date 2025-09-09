#pragma once

#define INVALID_EHANDLE_INDEX     0xFFFFFFFF
#define NUM_SERIAL_NUM_BITS       16
#define NUM_SERIAL_NUM_SHIFT_BITS (32 - NUM_SERIAL_NUM_BITS)
#define ENT_ENTRY_MASK            ((1 << NUM_SERIAL_NUM_BITS) - 1)

class i_handle_entity_t;

class base_handle_t {
public:
  base_handle_t();
  base_handle_t(const base_handle_t& other);
  base_handle_t(unsigned long value);
  base_handle_t(int entry, int serial_number);
  void                 initialize(int entry, int serial_number);
  void                 term();
  bool                 is_valid() const;
  int                  get_entry_index() const;
  int                  get_serial_number() const;
  int                  to_int() const;
  bool                 operator!=(const base_handle_t& other) const;
  bool                 operator==(const base_handle_t& other) const;
  bool                 operator==(const i_handle_entity_t* ent) const;
  bool                 operator!=(const i_handle_entity_t* ent) const;
  bool                 operator<(const base_handle_t& other) const;
  bool                 operator<(const i_handle_entity_t* ent) const;
  const base_handle_t& operator=(const i_handle_entity_t* ent);
  const base_handle_t& set(const i_handle_entity_t* entity);
  i_handle_entity_t*   get() const;

protected:
  unsigned long index;
};

#include "handle_entity.h"

inline base_handle_t::base_handle_t() { index = INVALID_EHANDLE_INDEX; }

inline base_handle_t::base_handle_t(const base_handle_t& other) { index = other.index; }

inline base_handle_t::base_handle_t(unsigned long value) { index = value; }

inline base_handle_t::base_handle_t(int entry, int serial_number) {
  initialize(entry, serial_number);
}

inline void base_handle_t::initialize(int entry, int serial_number) {
  index = entry | (serial_number << NUM_SERIAL_NUM_SHIFT_BITS);
}

inline void base_handle_t::term() { index = INVALID_EHANDLE_INDEX; }

inline bool base_handle_t::is_valid() const { return index != INVALID_EHANDLE_INDEX; }

inline int base_handle_t::get_entry_index() const { return index & ENT_ENTRY_MASK; }

inline int base_handle_t::get_serial_number() const {
  return index >> NUM_SERIAL_NUM_SHIFT_BITS;
}

inline int base_handle_t::to_int() const { return (int)index; }

inline bool base_handle_t::operator!=(const base_handle_t& other) const {
  return index != other.index;
}

inline bool base_handle_t::operator==(const base_handle_t& other) const {
  return index == other.index;
}

inline bool base_handle_t::operator==(const i_handle_entity_t* ent) const {
  return get() == ent;
}

inline bool base_handle_t::operator!=(const i_handle_entity_t* ent) const {
  return get() != ent;
}

inline bool base_handle_t::operator<(const base_handle_t& other) const {
  return index < other.index;
}

inline bool base_handle_t::operator<(const i_handle_entity_t* ent) const {
  unsigned long other_index = (ent) ? ent->get_ref_e_handle().index : INVALID_EHANDLE_INDEX;
  return index < other_index;
}

inline const base_handle_t& base_handle_t::operator=(const i_handle_entity_t* ent) {
  return set(ent);
}

inline const base_handle_t& base_handle_t::set(const i_handle_entity_t* ent) {
  if (ent) {
    *this = ent->get_ref_e_handle();
  } else {
    index = INVALID_EHANDLE_INDEX;
  }

  return *this;
}

template <class t> class handle_t : public base_handle_t {
public:
  handle_t();
  handle_t(int entry, int serial_number);
  handle_t(const base_handle_t& handle);
  handle_t(t* val);

  static handle_t<t> from_index(int index);

  t*   get() const;
  void set(const t* val);

  operator t*();
  operator t*() const;

  bool                 operator!() const;
  bool                 operator==(t* val) const;
  bool                 operator!=(t* val) const;
  const base_handle_t& operator=(const t* val);

  t* operator->() const;
};

template <class t> handle_t<t>::handle_t() {}

template <class t> handle_t<t>::handle_t(int entry, int serial_number) {
  initialize(entry, serial_number);
}

template <class t> handle_t<t>::handle_t(const base_handle_t& handle) : base_handle_t(handle) {}

template <class t> handle_t<t>::handle_t(t* val) {
  term();
  set(val);
}

template <class t> handle_t<t> handle_t<t>::from_index(int index) {
  handle_t<t> ret;
  ret.index = index;
  return ret;
}

template <class t> t* handle_t<t>::get() const {
  return reinterpret_cast<t*>(base_handle_t::get());
}

template <class t> handle_t<t>::operator t*() { return get(); }

template <class t> handle_t<t>::operator t*() const { return get(); }

template <class t> bool handle_t<t>::operator!() const { return !get(); }

template <class t> bool handle_t<t>::operator==(t* val) const { return get() == val; }

template <class t> bool handle_t<t>::operator!=(t* val) const { return get() != val; }

template <class t> void handle_t<t>::set(const t* val) {
  base_handle_t::set(reinterpret_cast<const i_handle_entity_t*>(val));
}

template <class t> const base_handle_t& handle_t<t>::operator=(const t* val) {
  set(val);
  return *this;
}

template <class t> t* handle_t<t>::operator->() const { return get(); }
