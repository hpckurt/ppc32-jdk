/* AUTOMATICALLY GENERATED FILE - DO NOT EDIT */

#ifndef JFRFILES_JFREVENTCLASSES_HPP
#define JFRFILES_JFREVENTCLASSES_HPP

#include "oops/klass.hpp"
#include "jfrfiles/jfrTypes.hpp"
#include "jfr/utilities/jfrTypes.hpp"
#include "utilities/macros.hpp"
#include "utilities/ticks.hpp"
#if INCLUDE_JFR
#include "jfr/recorder/service/jfrEvent.hpp"
/*
 * Each event class has an assert member function verify() which is invoked
 * just before the engine writes the event and its fields to the data stream.
 * The purpose of verify() is to ensure that all fields in the event are initialized
 * and set before attempting to commit.
 *
 * We enforce this requirement because events are generally stack allocated and therefore
 * *not* initialized to default values. This prevents us from inadvertently committing
 * uninitialized values to the data stream.
 *
 * The assert message contains both the index (zero based) as well as the name of the field.
 */

struct JfrStructVirtualSpace
{
 private:
  u8 _start;
  u8 _committedEnd;
  u8 _committedSize;
  u8 _reservedEnd;
  u8 _reservedSize;

 public:
  void set_start(u8 new_value) { this->_start = new_value; }
  void set_committedEnd(u8 new_value) { this->_committedEnd = new_value; }
  void set_committedSize(u8 new_value) { this->_committedSize = new_value; }
  void set_reservedEnd(u8 new_value) { this->_reservedEnd = new_value; }
  void set_reservedSize(u8 new_value) { this->_reservedSize = new_value; }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_start);
    w.write(_committedEnd);
    w.write(_committedSize);
    w.write(_reservedEnd);
    w.write(_reservedSize);
  }
};


struct JfrStructObjectSpace
{
 private:
  u8 _start;
  u8 _end;
  u8 _used;
  u8 _size;

 public:
  void set_start(u8 new_value) { this->_start = new_value; }
  void set_end(u8 new_value) { this->_end = new_value; }
  void set_used(u8 new_value) { this->_used = new_value; }
  void set_size(u8 new_value) { this->_size = new_value; }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_start);
    w.write(_end);
    w.write(_used);
    w.write(_size);
  }
};


struct JfrStructMetaspaceSizes
{
 private:
  u8 _committed;
  u8 _used;
  u8 _reserved;

 public:
  void set_committed(u8 new_value) { this->_committed = new_value; }
  void set_used(u8 new_value) { this->_used = new_value; }
  void set_reserved(u8 new_value) { this->_reserved = new_value; }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_committed);
    w.write(_used);
    w.write(_reserved);
  }
};


struct JfrStructCopyFailed
{
 private:
  u8 _objectCount;
  u8 _firstSize;
  u8 _smallestSize;
  u8 _totalSize;

 public:
  void set_objectCount(u8 new_value) { this->_objectCount = new_value; }
  void set_firstSize(u8 new_value) { this->_firstSize = new_value; }
  void set_smallestSize(u8 new_value) { this->_smallestSize = new_value; }
  void set_totalSize(u8 new_value) { this->_totalSize = new_value; }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_objectCount);
    w.write(_firstSize);
    w.write(_smallestSize);
    w.write(_totalSize);
  }
};


struct JfrStructG1EvacuationStatistics
{
 private:
  unsigned _gcId;
  u8 _allocated;
  u8 _wasted;
  u8 _used;
  u8 _undoWaste;
  u8 _regionEndWaste;
  unsigned _regionsRefilled;
  u8 _directAllocated;
  u8 _failureUsed;
  u8 _failureWaste;

 public:
  void set_gcId(unsigned new_value) { this->_gcId = new_value; }
  void set_allocated(u8 new_value) { this->_allocated = new_value; }
  void set_wasted(u8 new_value) { this->_wasted = new_value; }
  void set_used(u8 new_value) { this->_used = new_value; }
  void set_undoWaste(u8 new_value) { this->_undoWaste = new_value; }
  void set_regionEndWaste(u8 new_value) { this->_regionEndWaste = new_value; }
  void set_regionsRefilled(unsigned new_value) { this->_regionsRefilled = new_value; }
  void set_directAllocated(u8 new_value) { this->_directAllocated = new_value; }
  void set_failureUsed(u8 new_value) { this->_failureUsed = new_value; }
  void set_failureWaste(u8 new_value) { this->_failureWaste = new_value; }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_allocated);
    w.write(_wasted);
    w.write(_used);
    w.write(_undoWaste);
    w.write(_regionEndWaste);
    w.write(_regionsRefilled);
    w.write(_directAllocated);
    w.write(_failureUsed);
    w.write(_failureWaste);
  }
};


struct JfrStructCalleeMethod
{
 private:
  const char* _type;
  const char* _name;
  const char* _descriptor;

 public:
  void set_type(const char* new_value) { this->_type = new_value; }
  void set_name(const char* new_value) { this->_name = new_value; }
  void set_descriptor(const char* new_value) { this->_descriptor = new_value; }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_type);
    w.write(_name);
    w.write(_descriptor);
  }
};


struct JfrStructStackFrame
{
 private:
  const Method* _method;
  s4 _lineNumber;
  s4 _bytecodeIndex;
  u8 _type;

 public:
  void set_method(const Method* new_value) { this->_method = new_value; }
  void set_lineNumber(s4 new_value) { this->_lineNumber = new_value; }
  void set_bytecodeIndex(s4 new_value) { this->_bytecodeIndex = new_value; }
  void set_type(u8 new_value) { this->_type = new_value; }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_method);
    w.write(_lineNumber);
    w.write(_bytecodeIndex);
    w.write(_type);
  }
};


class EventThreadStart : public JfrEvent<EventThreadStart>
{
 private:
  u8 _thread;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrThreadStartEvent;

  EventThreadStart(EventStartTime timing=TIMED) : JfrEvent<EventThreadStart>(timing) {}

  void set_thread(u8 new_value) {
    this->_thread = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_thread);
  }

  using JfrEvent<EventThreadStart>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(u8 thread) {
    EventThreadStart me(UNTIMED);

    if (me.should_commit()) {
      me.set_thread(thread);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: thread");
  }
#endif
};

class EventThreadEnd : public JfrEvent<EventThreadEnd>
{
 private:
  u8 _thread;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrThreadEndEvent;

  EventThreadEnd(EventStartTime timing=TIMED) : JfrEvent<EventThreadEnd>(timing) {}

  void set_thread(u8 new_value) {
    this->_thread = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_thread);
  }

  using JfrEvent<EventThreadEnd>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(u8 thread) {
    EventThreadEnd me(UNTIMED);

    if (me.should_commit()) {
      me.set_thread(thread);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: thread");
  }
#endif
};

class EventThreadSleep : public JfrEvent<EventThreadSleep>
{
 private:
  s8 _time;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrThreadSleepEvent;

  EventThreadSleep(EventStartTime timing=TIMED) : JfrEvent<EventThreadSleep>(timing) {}

  void set_time(s8 new_value) {
    this->_time = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_time);
  }

  using JfrEvent<EventThreadSleep>::commit; // else commit() is hidden by overloaded versions in this class

  EventThreadSleep(
    s8 time) : JfrEvent<EventThreadSleep>(TIMED) {
    if (should_commit()) {
      set_time(time);
    }
  }

  void commit(s8 time) {
    if (should_commit()) {
      set_time(time);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     s8 time) {
    EventThreadSleep me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_time(time);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: time");
  }
#endif
};

class EventThreadPark : public JfrEvent<EventThreadPark>
{
 private:
  const Klass* _parkedClass;
  s8 _timeout;
  s8 _until;
  u8 _address;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrThreadParkEvent;

  EventThreadPark(EventStartTime timing=TIMED) : JfrEvent<EventThreadPark>(timing) {}

  void set_parkedClass(const Klass* new_value) {
    this->_parkedClass = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_timeout(s8 new_value) {
    this->_timeout = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_until(s8 new_value) {
    this->_until = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_address(u8 new_value) {
    this->_address = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_parkedClass);
    w.write(_timeout);
    w.write(_until);
    w.write(_address);
  }

  using JfrEvent<EventThreadPark>::commit; // else commit() is hidden by overloaded versions in this class

  EventThreadPark(
    const Klass* parkedClass,
    s8 timeout,
    s8 until,
    u8 address) : JfrEvent<EventThreadPark>(TIMED) {
    if (should_commit()) {
      set_parkedClass(parkedClass);
      set_timeout(timeout);
      set_until(until);
      set_address(address);
    }
  }

  void commit(const Klass* parkedClass,
              s8 timeout,
              s8 until,
              u8 address) {
    if (should_commit()) {
      set_parkedClass(parkedClass);
      set_timeout(timeout);
      set_until(until);
      set_address(address);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const Klass* parkedClass,
                     s8 timeout,
                     s8 until,
                     u8 address) {
    EventThreadPark me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_parkedClass(parkedClass);
      me.set_timeout(timeout);
      me.set_until(until);
      me.set_address(address);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: parkedClass");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: timeout");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: until");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: address");
  }
#endif
};

class EventJavaMonitorEnter : public JfrEvent<EventJavaMonitorEnter>
{
 private:
  const Klass* _monitorClass;
  u8 _previousOwner;
  u8 _address;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrJavaMonitorEnterEvent;

  EventJavaMonitorEnter(EventStartTime timing=TIMED) : JfrEvent<EventJavaMonitorEnter>(timing) {}

  void set_monitorClass(const Klass* new_value) {
    this->_monitorClass = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_previousOwner(u8 new_value) {
    this->_previousOwner = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_address(u8 new_value) {
    this->_address = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_monitorClass);
    w.write(_previousOwner);
    w.write(_address);
  }

  using JfrEvent<EventJavaMonitorEnter>::commit; // else commit() is hidden by overloaded versions in this class

  EventJavaMonitorEnter(
    const Klass* monitorClass,
    u8 previousOwner,
    u8 address) : JfrEvent<EventJavaMonitorEnter>(TIMED) {
    if (should_commit()) {
      set_monitorClass(monitorClass);
      set_previousOwner(previousOwner);
      set_address(address);
    }
  }

  void commit(const Klass* monitorClass,
              u8 previousOwner,
              u8 address) {
    if (should_commit()) {
      set_monitorClass(monitorClass);
      set_previousOwner(previousOwner);
      set_address(address);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const Klass* monitorClass,
                     u8 previousOwner,
                     u8 address) {
    EventJavaMonitorEnter me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_monitorClass(monitorClass);
      me.set_previousOwner(previousOwner);
      me.set_address(address);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: monitorClass");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: previousOwner");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: address");
  }
#endif
};

class EventJavaMonitorWait : public JfrEvent<EventJavaMonitorWait>
{
 private:
  const Klass* _monitorClass;
  u8 _notifier;
  s8 _timeout;
  bool _timedOut;
  u8 _address;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrJavaMonitorWaitEvent;

  EventJavaMonitorWait(EventStartTime timing=TIMED) : JfrEvent<EventJavaMonitorWait>(timing) {}

  void set_monitorClass(const Klass* new_value) {
    this->_monitorClass = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_notifier(u8 new_value) {
    this->_notifier = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_timeout(s8 new_value) {
    this->_timeout = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_timedOut(bool new_value) {
    this->_timedOut = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_address(u8 new_value) {
    this->_address = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_monitorClass);
    w.write(_notifier);
    w.write(_timeout);
    w.write(_timedOut);
    w.write(_address);
  }

  using JfrEvent<EventJavaMonitorWait>::commit; // else commit() is hidden by overloaded versions in this class

  EventJavaMonitorWait(
    const Klass* monitorClass,
    u8 notifier,
    s8 timeout,
    bool timedOut,
    u8 address) : JfrEvent<EventJavaMonitorWait>(TIMED) {
    if (should_commit()) {
      set_monitorClass(monitorClass);
      set_notifier(notifier);
      set_timeout(timeout);
      set_timedOut(timedOut);
      set_address(address);
    }
  }

  void commit(const Klass* monitorClass,
              u8 notifier,
              s8 timeout,
              bool timedOut,
              u8 address) {
    if (should_commit()) {
      set_monitorClass(monitorClass);
      set_notifier(notifier);
      set_timeout(timeout);
      set_timedOut(timedOut);
      set_address(address);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const Klass* monitorClass,
                     u8 notifier,
                     s8 timeout,
                     bool timedOut,
                     u8 address) {
    EventJavaMonitorWait me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_monitorClass(monitorClass);
      me.set_notifier(notifier);
      me.set_timeout(timeout);
      me.set_timedOut(timedOut);
      me.set_address(address);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: monitorClass");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: notifier");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: timeout");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: timedOut");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: address");
  }
#endif
};

class EventJavaMonitorInflate : public JfrEvent<EventJavaMonitorInflate>
{
 private:
  const Klass* _monitorClass;
  u8 _address;
  u8 _cause;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrJavaMonitorInflateEvent;

  EventJavaMonitorInflate(EventStartTime timing=TIMED) : JfrEvent<EventJavaMonitorInflate>(timing) {}

  void set_monitorClass(const Klass* new_value) {
    this->_monitorClass = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_address(u8 new_value) {
    this->_address = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_cause(u8 new_value) {
    this->_cause = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_monitorClass);
    w.write(_address);
    w.write(_cause);
  }

  using JfrEvent<EventJavaMonitorInflate>::commit; // else commit() is hidden by overloaded versions in this class

  EventJavaMonitorInflate(
    const Klass* monitorClass,
    u8 address,
    u8 cause) : JfrEvent<EventJavaMonitorInflate>(TIMED) {
    if (should_commit()) {
      set_monitorClass(monitorClass);
      set_address(address);
      set_cause(cause);
    }
  }

  void commit(const Klass* monitorClass,
              u8 address,
              u8 cause) {
    if (should_commit()) {
      set_monitorClass(monitorClass);
      set_address(address);
      set_cause(cause);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const Klass* monitorClass,
                     u8 address,
                     u8 cause) {
    EventJavaMonitorInflate me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_monitorClass(monitorClass);
      me.set_address(address);
      me.set_cause(cause);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: monitorClass");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: address");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: cause");
  }
#endif
};

class EventBiasedLockRevocation : public JfrEvent<EventBiasedLockRevocation>
{
 private:
  const Klass* _lockClass;
  s4 _safepointId;
  u8 _previousOwner;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrBiasedLockRevocationEvent;

  EventBiasedLockRevocation(EventStartTime timing=TIMED) : JfrEvent<EventBiasedLockRevocation>(timing) {}

  void set_lockClass(const Klass* new_value) {
    this->_lockClass = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_safepointId(s4 new_value) {
    this->_safepointId = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_previousOwner(u8 new_value) {
    this->_previousOwner = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_lockClass);
    w.write(_safepointId);
    w.write(_previousOwner);
  }

  using JfrEvent<EventBiasedLockRevocation>::commit; // else commit() is hidden by overloaded versions in this class

  EventBiasedLockRevocation(
    const Klass* lockClass,
    s4 safepointId,
    u8 previousOwner) : JfrEvent<EventBiasedLockRevocation>(TIMED) {
    if (should_commit()) {
      set_lockClass(lockClass);
      set_safepointId(safepointId);
      set_previousOwner(previousOwner);
    }
  }

  void commit(const Klass* lockClass,
              s4 safepointId,
              u8 previousOwner) {
    if (should_commit()) {
      set_lockClass(lockClass);
      set_safepointId(safepointId);
      set_previousOwner(previousOwner);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const Klass* lockClass,
                     s4 safepointId,
                     u8 previousOwner) {
    EventBiasedLockRevocation me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_lockClass(lockClass);
      me.set_safepointId(safepointId);
      me.set_previousOwner(previousOwner);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: lockClass");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: safepointId");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: previousOwner");
  }
#endif
};

class EventBiasedLockSelfRevocation : public JfrEvent<EventBiasedLockSelfRevocation>
{
 private:
  const Klass* _lockClass;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrBiasedLockSelfRevocationEvent;

  EventBiasedLockSelfRevocation(EventStartTime timing=TIMED) : JfrEvent<EventBiasedLockSelfRevocation>(timing) {}

  void set_lockClass(const Klass* new_value) {
    this->_lockClass = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_lockClass);
  }

  using JfrEvent<EventBiasedLockSelfRevocation>::commit; // else commit() is hidden by overloaded versions in this class

  EventBiasedLockSelfRevocation(
    const Klass* lockClass) : JfrEvent<EventBiasedLockSelfRevocation>(TIMED) {
    if (should_commit()) {
      set_lockClass(lockClass);
    }
  }

  void commit(const Klass* lockClass) {
    if (should_commit()) {
      set_lockClass(lockClass);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const Klass* lockClass) {
    EventBiasedLockSelfRevocation me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_lockClass(lockClass);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: lockClass");
  }
#endif
};

class EventBiasedLockClassRevocation : public JfrEvent<EventBiasedLockClassRevocation>
{
 private:
  const Klass* _revokedClass;
  bool _disableBiasing;
  s4 _safepointId;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrBiasedLockClassRevocationEvent;

  EventBiasedLockClassRevocation(EventStartTime timing=TIMED) : JfrEvent<EventBiasedLockClassRevocation>(timing) {}

  void set_revokedClass(const Klass* new_value) {
    this->_revokedClass = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_disableBiasing(bool new_value) {
    this->_disableBiasing = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_safepointId(s4 new_value) {
    this->_safepointId = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_revokedClass);
    w.write(_disableBiasing);
    w.write(_safepointId);
  }

  using JfrEvent<EventBiasedLockClassRevocation>::commit; // else commit() is hidden by overloaded versions in this class

  EventBiasedLockClassRevocation(
    const Klass* revokedClass,
    bool disableBiasing,
    s4 safepointId) : JfrEvent<EventBiasedLockClassRevocation>(TIMED) {
    if (should_commit()) {
      set_revokedClass(revokedClass);
      set_disableBiasing(disableBiasing);
      set_safepointId(safepointId);
    }
  }

  void commit(const Klass* revokedClass,
              bool disableBiasing,
              s4 safepointId) {
    if (should_commit()) {
      set_revokedClass(revokedClass);
      set_disableBiasing(disableBiasing);
      set_safepointId(safepointId);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const Klass* revokedClass,
                     bool disableBiasing,
                     s4 safepointId) {
    EventBiasedLockClassRevocation me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_revokedClass(revokedClass);
      me.set_disableBiasing(disableBiasing);
      me.set_safepointId(safepointId);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: revokedClass");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: disableBiasing");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: safepointId");
  }
#endif
};

class EventReservedStackActivation : public JfrEvent<EventReservedStackActivation>
{
 private:
  const Method* _method;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrReservedStackActivationEvent;

  EventReservedStackActivation(EventStartTime timing=TIMED) : JfrEvent<EventReservedStackActivation>(timing) {}

  void set_method(const Method* new_value) {
    this->_method = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_method);
  }

  using JfrEvent<EventReservedStackActivation>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const Method* method) {
    EventReservedStackActivation me(UNTIMED);

    if (me.should_commit()) {
      me.set_method(method);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: method");
  }
#endif
};

class EventClassLoad : public JfrEvent<EventClassLoad>
{
 private:
  const Klass* _loadedClass;
  const ClassLoaderData* _definingClassLoader;
  const ClassLoaderData* _initiatingClassLoader;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrClassLoadEvent;

  EventClassLoad(EventStartTime timing=TIMED) : JfrEvent<EventClassLoad>(timing) {}

  void set_loadedClass(const Klass* new_value) {
    this->_loadedClass = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_definingClassLoader(const ClassLoaderData* new_value) {
    this->_definingClassLoader = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_initiatingClassLoader(const ClassLoaderData* new_value) {
    this->_initiatingClassLoader = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_loadedClass);
    w.write(_definingClassLoader);
    w.write(_initiatingClassLoader);
  }

  using JfrEvent<EventClassLoad>::commit; // else commit() is hidden by overloaded versions in this class

  EventClassLoad(
    const Klass* loadedClass,
    const ClassLoaderData* definingClassLoader,
    const ClassLoaderData* initiatingClassLoader) : JfrEvent<EventClassLoad>(TIMED) {
    if (should_commit()) {
      set_loadedClass(loadedClass);
      set_definingClassLoader(definingClassLoader);
      set_initiatingClassLoader(initiatingClassLoader);
    }
  }

  void commit(const Klass* loadedClass,
              const ClassLoaderData* definingClassLoader,
              const ClassLoaderData* initiatingClassLoader) {
    if (should_commit()) {
      set_loadedClass(loadedClass);
      set_definingClassLoader(definingClassLoader);
      set_initiatingClassLoader(initiatingClassLoader);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const Klass* loadedClass,
                     const ClassLoaderData* definingClassLoader,
                     const ClassLoaderData* initiatingClassLoader) {
    EventClassLoad me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_loadedClass(loadedClass);
      me.set_definingClassLoader(definingClassLoader);
      me.set_initiatingClassLoader(initiatingClassLoader);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: loadedClass");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: definingClassLoader");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: initiatingClassLoader");
  }
#endif
};

class EventClassDefine : public JfrEvent<EventClassDefine>
{
 private:
  const Klass* _definedClass;
  const ClassLoaderData* _definingClassLoader;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrClassDefineEvent;

  EventClassDefine(EventStartTime timing=TIMED) : JfrEvent<EventClassDefine>(timing) {}

  void set_definedClass(const Klass* new_value) {
    this->_definedClass = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_definingClassLoader(const ClassLoaderData* new_value) {
    this->_definingClassLoader = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_definedClass);
    w.write(_definingClassLoader);
  }

  using JfrEvent<EventClassDefine>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const Klass* definedClass,
                     const ClassLoaderData* definingClassLoader) {
    EventClassDefine me(UNTIMED);

    if (me.should_commit()) {
      me.set_definedClass(definedClass);
      me.set_definingClassLoader(definingClassLoader);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: definedClass");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: definingClassLoader");
  }
#endif
};

class EventClassUnload : public JfrEvent<EventClassUnload>
{
 private:
  const Klass* _unloadedClass;
  const ClassLoaderData* _definingClassLoader;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrClassUnloadEvent;

  EventClassUnload(EventStartTime timing=TIMED) : JfrEvent<EventClassUnload>(timing) {}

  void set_unloadedClass(const Klass* new_value) {
    this->_unloadedClass = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_definingClassLoader(const ClassLoaderData* new_value) {
    this->_definingClassLoader = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_unloadedClass);
    w.write(_definingClassLoader);
  }

  using JfrEvent<EventClassUnload>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const Klass* unloadedClass,
                     const ClassLoaderData* definingClassLoader) {
    EventClassUnload me(UNTIMED);

    if (me.should_commit()) {
      me.set_unloadedClass(unloadedClass);
      me.set_definingClassLoader(definingClassLoader);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: unloadedClass");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: definingClassLoader");
  }
#endif
};

class EventIntFlagChanged : public JfrEvent<EventIntFlagChanged>
{
 private:
  const char* _name;
  s4 _oldValue;
  s4 _newValue;
  u8 _origin;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrIntFlagChangedEvent;

  EventIntFlagChanged(EventStartTime timing=TIMED) : JfrEvent<EventIntFlagChanged>(timing) {}

  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_oldValue(s4 new_value) {
    this->_oldValue = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_newValue(s4 new_value) {
    this->_newValue = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_origin(u8 new_value) {
    this->_origin = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_name);
    w.write(_oldValue);
    w.write(_newValue);
    w.write(_origin);
  }

  using JfrEvent<EventIntFlagChanged>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const char* name,
                     s4 oldValue,
                     s4 newValue,
                     u8 origin) {
    EventIntFlagChanged me(UNTIMED);

    if (me.should_commit()) {
      me.set_name(name);
      me.set_oldValue(oldValue);
      me.set_newValue(newValue);
      me.set_origin(origin);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: name");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: oldValue");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: newValue");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: origin");
  }
#endif
};

class EventUnsignedIntFlagChanged : public JfrEvent<EventUnsignedIntFlagChanged>
{
 private:
  const char* _name;
  unsigned _oldValue;
  unsigned _newValue;
  u8 _origin;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrUnsignedIntFlagChangedEvent;

  EventUnsignedIntFlagChanged(EventStartTime timing=TIMED) : JfrEvent<EventUnsignedIntFlagChanged>(timing) {}

  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_oldValue(unsigned new_value) {
    this->_oldValue = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_newValue(unsigned new_value) {
    this->_newValue = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_origin(u8 new_value) {
    this->_origin = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_name);
    w.write(_oldValue);
    w.write(_newValue);
    w.write(_origin);
  }

  using JfrEvent<EventUnsignedIntFlagChanged>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const char* name,
                     unsigned oldValue,
                     unsigned newValue,
                     u8 origin) {
    EventUnsignedIntFlagChanged me(UNTIMED);

    if (me.should_commit()) {
      me.set_name(name);
      me.set_oldValue(oldValue);
      me.set_newValue(newValue);
      me.set_origin(origin);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: name");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: oldValue");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: newValue");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: origin");
  }
#endif
};

class EventLongFlagChanged : public JfrEvent<EventLongFlagChanged>
{
 private:
  const char* _name;
  s8 _oldValue;
  s8 _newValue;
  u8 _origin;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrLongFlagChangedEvent;

  EventLongFlagChanged(EventStartTime timing=TIMED) : JfrEvent<EventLongFlagChanged>(timing) {}

  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_oldValue(s8 new_value) {
    this->_oldValue = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_newValue(s8 new_value) {
    this->_newValue = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_origin(u8 new_value) {
    this->_origin = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_name);
    w.write(_oldValue);
    w.write(_newValue);
    w.write(_origin);
  }

  using JfrEvent<EventLongFlagChanged>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const char* name,
                     s8 oldValue,
                     s8 newValue,
                     u8 origin) {
    EventLongFlagChanged me(UNTIMED);

    if (me.should_commit()) {
      me.set_name(name);
      me.set_oldValue(oldValue);
      me.set_newValue(newValue);
      me.set_origin(origin);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: name");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: oldValue");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: newValue");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: origin");
  }
#endif
};

class EventUnsignedLongFlagChanged : public JfrEvent<EventUnsignedLongFlagChanged>
{
 private:
  const char* _name;
  u8 _oldValue;
  u8 _newValue;
  u8 _origin;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrUnsignedLongFlagChangedEvent;

  EventUnsignedLongFlagChanged(EventStartTime timing=TIMED) : JfrEvent<EventUnsignedLongFlagChanged>(timing) {}

  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_oldValue(u8 new_value) {
    this->_oldValue = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_newValue(u8 new_value) {
    this->_newValue = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_origin(u8 new_value) {
    this->_origin = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_name);
    w.write(_oldValue);
    w.write(_newValue);
    w.write(_origin);
  }

  using JfrEvent<EventUnsignedLongFlagChanged>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const char* name,
                     u8 oldValue,
                     u8 newValue,
                     u8 origin) {
    EventUnsignedLongFlagChanged me(UNTIMED);

    if (me.should_commit()) {
      me.set_name(name);
      me.set_oldValue(oldValue);
      me.set_newValue(newValue);
      me.set_origin(origin);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: name");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: oldValue");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: newValue");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: origin");
  }
#endif
};

class EventDoubleFlagChanged : public JfrEvent<EventDoubleFlagChanged>
{
 private:
  const char* _name;
  double _oldValue;
  double _newValue;
  u8 _origin;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrDoubleFlagChangedEvent;

  EventDoubleFlagChanged(EventStartTime timing=TIMED) : JfrEvent<EventDoubleFlagChanged>(timing) {}

  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_oldValue(double new_value) {
    this->_oldValue = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_newValue(double new_value) {
    this->_newValue = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_origin(u8 new_value) {
    this->_origin = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_name);
    w.write(_oldValue);
    w.write(_newValue);
    w.write(_origin);
  }

  using JfrEvent<EventDoubleFlagChanged>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const char* name,
                     double oldValue,
                     double newValue,
                     u8 origin) {
    EventDoubleFlagChanged me(UNTIMED);

    if (me.should_commit()) {
      me.set_name(name);
      me.set_oldValue(oldValue);
      me.set_newValue(newValue);
      me.set_origin(origin);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: name");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: oldValue");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: newValue");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: origin");
  }
#endif
};

class EventBooleanFlagChanged : public JfrEvent<EventBooleanFlagChanged>
{
 private:
  const char* _name;
  bool _oldValue;
  bool _newValue;
  u8 _origin;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrBooleanFlagChangedEvent;

  EventBooleanFlagChanged(EventStartTime timing=TIMED) : JfrEvent<EventBooleanFlagChanged>(timing) {}

  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_oldValue(bool new_value) {
    this->_oldValue = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_newValue(bool new_value) {
    this->_newValue = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_origin(u8 new_value) {
    this->_origin = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_name);
    w.write(_oldValue);
    w.write(_newValue);
    w.write(_origin);
  }

  using JfrEvent<EventBooleanFlagChanged>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const char* name,
                     bool oldValue,
                     bool newValue,
                     u8 origin) {
    EventBooleanFlagChanged me(UNTIMED);

    if (me.should_commit()) {
      me.set_name(name);
      me.set_oldValue(oldValue);
      me.set_newValue(newValue);
      me.set_origin(origin);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: name");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: oldValue");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: newValue");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: origin");
  }
#endif
};

class EventStringFlagChanged : public JfrEvent<EventStringFlagChanged>
{
 private:
  const char* _name;
  const char* _oldValue;
  const char* _newValue;
  u8 _origin;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrStringFlagChangedEvent;

  EventStringFlagChanged(EventStartTime timing=TIMED) : JfrEvent<EventStringFlagChanged>(timing) {}

  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_oldValue(const char* new_value) {
    this->_oldValue = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_newValue(const char* new_value) {
    this->_newValue = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_origin(u8 new_value) {
    this->_origin = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_name);
    w.write(_oldValue);
    w.write(_newValue);
    w.write(_origin);
  }

  using JfrEvent<EventStringFlagChanged>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const char* name,
                     const char* oldValue,
                     const char* newValue,
                     u8 origin) {
    EventStringFlagChanged me(UNTIMED);

    if (me.should_commit()) {
      me.set_name(name);
      me.set_oldValue(oldValue);
      me.set_newValue(newValue);
      me.set_origin(origin);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: name");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: oldValue");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: newValue");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: origin");
  }
#endif
};

class EventGCHeapSummary : public JfrEvent<EventGCHeapSummary>
{
 private:
  unsigned _gcId;
  u8 _when;
  JfrStructVirtualSpace _heapSpace;
  u8 _heapUsed;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrGCHeapSummaryEvent;

  EventGCHeapSummary(EventStartTime timing=TIMED) : JfrEvent<EventGCHeapSummary>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_when(u8 new_value) {
    this->_when = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_heapSpace(const JfrStructVirtualSpace& value) {
    this->_heapSpace = value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_heapUsed(u8 new_value) {
    this->_heapUsed = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_when);
    _heapSpace.writeData(w);
    w.write(_heapUsed);
  }

  using JfrEvent<EventGCHeapSummary>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     u8 when,
                     const JfrStructVirtualSpace& heapSpace,
                     u8 heapUsed) {
    EventGCHeapSummary me(UNTIMED);

    if (me.should_commit()) {
      me.set_gcId(gcId);
      me.set_when(when);
      me.set_heapSpace(heapSpace);
      me.set_heapUsed(heapUsed);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: when");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: heapSpace");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: heapUsed");
  }
#endif
};

class EventMetaspaceSummary : public JfrEvent<EventMetaspaceSummary>
{
 private:
  unsigned _gcId;
  u8 _when;
  u8 _gcThreshold;
  JfrStructMetaspaceSizes _metaspace;
  JfrStructMetaspaceSizes _dataSpace;
  JfrStructMetaspaceSizes _classSpace;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrMetaspaceSummaryEvent;

  EventMetaspaceSummary(EventStartTime timing=TIMED) : JfrEvent<EventMetaspaceSummary>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_when(u8 new_value) {
    this->_when = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_gcThreshold(u8 new_value) {
    this->_gcThreshold = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_metaspace(const JfrStructMetaspaceSizes& value) {
    this->_metaspace = value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_dataSpace(const JfrStructMetaspaceSizes& value) {
    this->_dataSpace = value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_classSpace(const JfrStructMetaspaceSizes& value) {
    this->_classSpace = value;
    DEBUG_ONLY(set_field_bit(5));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_when);
    w.write(_gcThreshold);
    _metaspace.writeData(w);
    _dataSpace.writeData(w);
    _classSpace.writeData(w);
  }

  using JfrEvent<EventMetaspaceSummary>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     u8 when,
                     u8 gcThreshold,
                     const JfrStructMetaspaceSizes& metaspace,
                     const JfrStructMetaspaceSizes& dataSpace,
                     const JfrStructMetaspaceSizes& classSpace) {
    EventMetaspaceSummary me(UNTIMED);

    if (me.should_commit()) {
      me.set_gcId(gcId);
      me.set_when(when);
      me.set_gcThreshold(gcThreshold);
      me.set_metaspace(metaspace);
      me.set_dataSpace(dataSpace);
      me.set_classSpace(classSpace);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: when");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: gcThreshold");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: metaspace");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: dataSpace");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: classSpace");
  }
#endif
};

class EventMetaspaceGCThreshold : public JfrEvent<EventMetaspaceGCThreshold>
{
 private:
  u8 _oldValue;
  u8 _newValue;
  u8 _updater;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrMetaspaceGCThresholdEvent;

  EventMetaspaceGCThreshold(EventStartTime timing=TIMED) : JfrEvent<EventMetaspaceGCThreshold>(timing) {}

  void set_oldValue(u8 new_value) {
    this->_oldValue = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_newValue(u8 new_value) {
    this->_newValue = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_updater(u8 new_value) {
    this->_updater = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_oldValue);
    w.write(_newValue);
    w.write(_updater);
  }

  using JfrEvent<EventMetaspaceGCThreshold>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(u8 oldValue,
                     u8 newValue,
                     u8 updater) {
    EventMetaspaceGCThreshold me(UNTIMED);

    if (me.should_commit()) {
      me.set_oldValue(oldValue);
      me.set_newValue(newValue);
      me.set_updater(updater);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: oldValue");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: newValue");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: updater");
  }
#endif
};

class EventMetaspaceAllocationFailure : public JfrEvent<EventMetaspaceAllocationFailure>
{
 private:
  const ClassLoaderData* _classLoader;
  bool _anonymousClassLoader;
  u8 _size;
  u8 _metadataType;
  u8 _metaspaceObjectType;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = true;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrMetaspaceAllocationFailureEvent;

  EventMetaspaceAllocationFailure(EventStartTime timing=TIMED) : JfrEvent<EventMetaspaceAllocationFailure>(timing) {}

  void set_classLoader(const ClassLoaderData* new_value) {
    this->_classLoader = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_anonymousClassLoader(bool new_value) {
    this->_anonymousClassLoader = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_size(u8 new_value) {
    this->_size = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_metadataType(u8 new_value) {
    this->_metadataType = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_metaspaceObjectType(u8 new_value) {
    this->_metaspaceObjectType = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_classLoader);
    w.write(_anonymousClassLoader);
    w.write(_size);
    w.write(_metadataType);
    w.write(_metaspaceObjectType);
  }

  using JfrEvent<EventMetaspaceAllocationFailure>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const ClassLoaderData* classLoader,
                     bool anonymousClassLoader,
                     u8 size,
                     u8 metadataType,
                     u8 metaspaceObjectType) {
    EventMetaspaceAllocationFailure me(UNTIMED);

    if (me.should_commit()) {
      me.set_classLoader(classLoader);
      me.set_anonymousClassLoader(anonymousClassLoader);
      me.set_size(size);
      me.set_metadataType(metadataType);
      me.set_metaspaceObjectType(metaspaceObjectType);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: classLoader");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: anonymousClassLoader");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: size");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: metadataType");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: metaspaceObjectType");
  }
#endif
};

class EventMetaspaceOOM : public JfrEvent<EventMetaspaceOOM>
{
 private:
  const ClassLoaderData* _classLoader;
  bool _anonymousClassLoader;
  u8 _size;
  u8 _metadataType;
  u8 _metaspaceObjectType;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = true;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrMetaspaceOOMEvent;

  EventMetaspaceOOM(EventStartTime timing=TIMED) : JfrEvent<EventMetaspaceOOM>(timing) {}

  void set_classLoader(const ClassLoaderData* new_value) {
    this->_classLoader = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_anonymousClassLoader(bool new_value) {
    this->_anonymousClassLoader = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_size(u8 new_value) {
    this->_size = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_metadataType(u8 new_value) {
    this->_metadataType = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_metaspaceObjectType(u8 new_value) {
    this->_metaspaceObjectType = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_classLoader);
    w.write(_anonymousClassLoader);
    w.write(_size);
    w.write(_metadataType);
    w.write(_metaspaceObjectType);
  }

  using JfrEvent<EventMetaspaceOOM>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const ClassLoaderData* classLoader,
                     bool anonymousClassLoader,
                     u8 size,
                     u8 metadataType,
                     u8 metaspaceObjectType) {
    EventMetaspaceOOM me(UNTIMED);

    if (me.should_commit()) {
      me.set_classLoader(classLoader);
      me.set_anonymousClassLoader(anonymousClassLoader);
      me.set_size(size);
      me.set_metadataType(metadataType);
      me.set_metaspaceObjectType(metaspaceObjectType);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: classLoader");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: anonymousClassLoader");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: size");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: metadataType");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: metaspaceObjectType");
  }
#endif
};

class EventMetaspaceChunkFreeListSummary : public JfrEvent<EventMetaspaceChunkFreeListSummary>
{
 private:
  unsigned _gcId;
  u8 _when;
  u8 _metadataType;
  u8 _specializedChunks;
  u8 _specializedChunksTotalSize;
  u8 _smallChunks;
  u8 _smallChunksTotalSize;
  u8 _mediumChunks;
  u8 _mediumChunksTotalSize;
  u8 _humongousChunks;
  u8 _humongousChunksTotalSize;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrMetaspaceChunkFreeListSummaryEvent;

  EventMetaspaceChunkFreeListSummary(EventStartTime timing=TIMED) : JfrEvent<EventMetaspaceChunkFreeListSummary>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_when(u8 new_value) {
    this->_when = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_metadataType(u8 new_value) {
    this->_metadataType = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_specializedChunks(u8 new_value) {
    this->_specializedChunks = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_specializedChunksTotalSize(u8 new_value) {
    this->_specializedChunksTotalSize = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_smallChunks(u8 new_value) {
    this->_smallChunks = new_value;
    DEBUG_ONLY(set_field_bit(5));
  }
  void set_smallChunksTotalSize(u8 new_value) {
    this->_smallChunksTotalSize = new_value;
    DEBUG_ONLY(set_field_bit(6));
  }
  void set_mediumChunks(u8 new_value) {
    this->_mediumChunks = new_value;
    DEBUG_ONLY(set_field_bit(7));
  }
  void set_mediumChunksTotalSize(u8 new_value) {
    this->_mediumChunksTotalSize = new_value;
    DEBUG_ONLY(set_field_bit(8));
  }
  void set_humongousChunks(u8 new_value) {
    this->_humongousChunks = new_value;
    DEBUG_ONLY(set_field_bit(9));
  }
  void set_humongousChunksTotalSize(u8 new_value) {
    this->_humongousChunksTotalSize = new_value;
    DEBUG_ONLY(set_field_bit(10));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_when);
    w.write(_metadataType);
    w.write(_specializedChunks);
    w.write(_specializedChunksTotalSize);
    w.write(_smallChunks);
    w.write(_smallChunksTotalSize);
    w.write(_mediumChunks);
    w.write(_mediumChunksTotalSize);
    w.write(_humongousChunks);
    w.write(_humongousChunksTotalSize);
  }

  using JfrEvent<EventMetaspaceChunkFreeListSummary>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     u8 when,
                     u8 metadataType,
                     u8 specializedChunks,
                     u8 specializedChunksTotalSize,
                     u8 smallChunks,
                     u8 smallChunksTotalSize,
                     u8 mediumChunks,
                     u8 mediumChunksTotalSize,
                     u8 humongousChunks,
                     u8 humongousChunksTotalSize) {
    EventMetaspaceChunkFreeListSummary me(UNTIMED);

    if (me.should_commit()) {
      me.set_gcId(gcId);
      me.set_when(when);
      me.set_metadataType(metadataType);
      me.set_specializedChunks(specializedChunks);
      me.set_specializedChunksTotalSize(specializedChunksTotalSize);
      me.set_smallChunks(smallChunks);
      me.set_smallChunksTotalSize(smallChunksTotalSize);
      me.set_mediumChunks(mediumChunks);
      me.set_mediumChunksTotalSize(mediumChunksTotalSize);
      me.set_humongousChunks(humongousChunks);
      me.set_humongousChunksTotalSize(humongousChunksTotalSize);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: when");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: metadataType");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: specializedChunks");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: specializedChunksTotalSize");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: smallChunks");
    assert(verify_field_bit(6), "Attempting to write an uninitialized event field: smallChunksTotalSize");
    assert(verify_field_bit(7), "Attempting to write an uninitialized event field: mediumChunks");
    assert(verify_field_bit(8), "Attempting to write an uninitialized event field: mediumChunksTotalSize");
    assert(verify_field_bit(9), "Attempting to write an uninitialized event field: humongousChunks");
    assert(verify_field_bit(10), "Attempting to write an uninitialized event field: humongousChunksTotalSize");
  }
#endif
};

class EventPSHeapSummary : public JfrEvent<EventPSHeapSummary>
{
 private:
  unsigned _gcId;
  u8 _when;
  JfrStructVirtualSpace _oldSpace;
  JfrStructObjectSpace _oldObjectSpace;
  JfrStructVirtualSpace _youngSpace;
  JfrStructObjectSpace _edenSpace;
  JfrStructObjectSpace _fromSpace;
  JfrStructObjectSpace _toSpace;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrPSHeapSummaryEvent;

  EventPSHeapSummary(EventStartTime timing=TIMED) : JfrEvent<EventPSHeapSummary>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_when(u8 new_value) {
    this->_when = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_oldSpace(const JfrStructVirtualSpace& value) {
    this->_oldSpace = value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_oldObjectSpace(const JfrStructObjectSpace& value) {
    this->_oldObjectSpace = value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_youngSpace(const JfrStructVirtualSpace& value) {
    this->_youngSpace = value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_edenSpace(const JfrStructObjectSpace& value) {
    this->_edenSpace = value;
    DEBUG_ONLY(set_field_bit(5));
  }
  void set_fromSpace(const JfrStructObjectSpace& value) {
    this->_fromSpace = value;
    DEBUG_ONLY(set_field_bit(6));
  }
  void set_toSpace(const JfrStructObjectSpace& value) {
    this->_toSpace = value;
    DEBUG_ONLY(set_field_bit(7));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_when);
    _oldSpace.writeData(w);
    _oldObjectSpace.writeData(w);
    _youngSpace.writeData(w);
    _edenSpace.writeData(w);
    _fromSpace.writeData(w);
    _toSpace.writeData(w);
  }

  using JfrEvent<EventPSHeapSummary>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     u8 when,
                     const JfrStructVirtualSpace& oldSpace,
                     const JfrStructObjectSpace& oldObjectSpace,
                     const JfrStructVirtualSpace& youngSpace,
                     const JfrStructObjectSpace& edenSpace,
                     const JfrStructObjectSpace& fromSpace,
                     const JfrStructObjectSpace& toSpace) {
    EventPSHeapSummary me(UNTIMED);

    if (me.should_commit()) {
      me.set_gcId(gcId);
      me.set_when(when);
      me.set_oldSpace(oldSpace);
      me.set_oldObjectSpace(oldObjectSpace);
      me.set_youngSpace(youngSpace);
      me.set_edenSpace(edenSpace);
      me.set_fromSpace(fromSpace);
      me.set_toSpace(toSpace);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: when");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: oldSpace");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: oldObjectSpace");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: youngSpace");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: edenSpace");
    assert(verify_field_bit(6), "Attempting to write an uninitialized event field: fromSpace");
    assert(verify_field_bit(7), "Attempting to write an uninitialized event field: toSpace");
  }
#endif
};

class EventG1HeapSummary : public JfrEvent<EventG1HeapSummary>
{
 private:
  unsigned _gcId;
  u8 _when;
  u8 _edenUsedSize;
  u8 _edenTotalSize;
  u8 _survivorUsedSize;
  unsigned _numberOfRegions;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrG1HeapSummaryEvent;

  EventG1HeapSummary(EventStartTime timing=TIMED) : JfrEvent<EventG1HeapSummary>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_when(u8 new_value) {
    this->_when = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_edenUsedSize(u8 new_value) {
    this->_edenUsedSize = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_edenTotalSize(u8 new_value) {
    this->_edenTotalSize = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_survivorUsedSize(u8 new_value) {
    this->_survivorUsedSize = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_numberOfRegions(unsigned new_value) {
    this->_numberOfRegions = new_value;
    DEBUG_ONLY(set_field_bit(5));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_when);
    w.write(_edenUsedSize);
    w.write(_edenTotalSize);
    w.write(_survivorUsedSize);
    w.write(_numberOfRegions);
  }

  using JfrEvent<EventG1HeapSummary>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     u8 when,
                     u8 edenUsedSize,
                     u8 edenTotalSize,
                     u8 survivorUsedSize,
                     unsigned numberOfRegions) {
    EventG1HeapSummary me(UNTIMED);

    if (me.should_commit()) {
      me.set_gcId(gcId);
      me.set_when(when);
      me.set_edenUsedSize(edenUsedSize);
      me.set_edenTotalSize(edenTotalSize);
      me.set_survivorUsedSize(survivorUsedSize);
      me.set_numberOfRegions(numberOfRegions);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: when");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: edenUsedSize");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: edenTotalSize");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: survivorUsedSize");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: numberOfRegions");
  }
#endif
};

class EventGarbageCollection : public JfrEvent<EventGarbageCollection>
{
 private:
  unsigned _gcId;
  u8 _name;
  u8 _cause;
  Tickspan _sumOfPauses;
  Tickspan _longestPause;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrGarbageCollectionEvent;

  EventGarbageCollection(EventStartTime timing=TIMED) : JfrEvent<EventGarbageCollection>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_name(u8 new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_cause(u8 new_value) {
    this->_cause = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_sumOfPauses(const Tickspan& new_value) {
    this->_sumOfPauses = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_longestPause(const Tickspan& new_value) {
    this->_longestPause = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_name);
    w.write(_cause);
    w.write(_sumOfPauses);
    w.write(_longestPause);
  }

  using JfrEvent<EventGarbageCollection>::commit; // else commit() is hidden by overloaded versions in this class

  EventGarbageCollection(
    unsigned gcId,
    u8 name,
    u8 cause,
    const Tickspan& sumOfPauses,
    const Tickspan& longestPause) : JfrEvent<EventGarbageCollection>(TIMED) {
    if (should_commit()) {
      set_gcId(gcId);
      set_name(name);
      set_cause(cause);
      set_sumOfPauses(sumOfPauses);
      set_longestPause(longestPause);
    }
  }

  void commit(unsigned gcId,
              u8 name,
              u8 cause,
              const Tickspan& sumOfPauses,
              const Tickspan& longestPause) {
    if (should_commit()) {
      set_gcId(gcId);
      set_name(name);
      set_cause(cause);
      set_sumOfPauses(sumOfPauses);
      set_longestPause(longestPause);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId,
                     u8 name,
                     u8 cause,
                     const Tickspan& sumOfPauses,
                     const Tickspan& longestPause) {
    EventGarbageCollection me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_gcId(gcId);
      me.set_name(name);
      me.set_cause(cause);
      me.set_sumOfPauses(sumOfPauses);
      me.set_longestPause(longestPause);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: name");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: cause");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: sumOfPauses");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: longestPause");
  }
#endif
};

class EventParallelOldGarbageCollection : public JfrEvent<EventParallelOldGarbageCollection>
{
 private:
  unsigned _gcId;
  u8 _densePrefix;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrParallelOldGarbageCollectionEvent;

  EventParallelOldGarbageCollection(EventStartTime timing=TIMED) : JfrEvent<EventParallelOldGarbageCollection>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_densePrefix(u8 new_value) {
    this->_densePrefix = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_densePrefix);
  }

  using JfrEvent<EventParallelOldGarbageCollection>::commit; // else commit() is hidden by overloaded versions in this class

  EventParallelOldGarbageCollection(
    unsigned gcId,
    u8 densePrefix) : JfrEvent<EventParallelOldGarbageCollection>(TIMED) {
    if (should_commit()) {
      set_gcId(gcId);
      set_densePrefix(densePrefix);
    }
  }

  void commit(unsigned gcId,
              u8 densePrefix) {
    if (should_commit()) {
      set_gcId(gcId);
      set_densePrefix(densePrefix);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId,
                     u8 densePrefix) {
    EventParallelOldGarbageCollection me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_gcId(gcId);
      me.set_densePrefix(densePrefix);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: densePrefix");
  }
#endif
};

class EventYoungGarbageCollection : public JfrEvent<EventYoungGarbageCollection>
{
 private:
  unsigned _gcId;
  unsigned _tenuringThreshold;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrYoungGarbageCollectionEvent;

  EventYoungGarbageCollection(EventStartTime timing=TIMED) : JfrEvent<EventYoungGarbageCollection>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_tenuringThreshold(unsigned new_value) {
    this->_tenuringThreshold = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_tenuringThreshold);
  }

  using JfrEvent<EventYoungGarbageCollection>::commit; // else commit() is hidden by overloaded versions in this class

  EventYoungGarbageCollection(
    unsigned gcId,
    unsigned tenuringThreshold) : JfrEvent<EventYoungGarbageCollection>(TIMED) {
    if (should_commit()) {
      set_gcId(gcId);
      set_tenuringThreshold(tenuringThreshold);
    }
  }

  void commit(unsigned gcId,
              unsigned tenuringThreshold) {
    if (should_commit()) {
      set_gcId(gcId);
      set_tenuringThreshold(tenuringThreshold);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId,
                     unsigned tenuringThreshold) {
    EventYoungGarbageCollection me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_gcId(gcId);
      me.set_tenuringThreshold(tenuringThreshold);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: tenuringThreshold");
  }
#endif
};

class EventOldGarbageCollection : public JfrEvent<EventOldGarbageCollection>
{
 private:
  unsigned _gcId;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrOldGarbageCollectionEvent;

  EventOldGarbageCollection(EventStartTime timing=TIMED) : JfrEvent<EventOldGarbageCollection>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
  }

  using JfrEvent<EventOldGarbageCollection>::commit; // else commit() is hidden by overloaded versions in this class

  EventOldGarbageCollection(
    unsigned gcId) : JfrEvent<EventOldGarbageCollection>(TIMED) {
    if (should_commit()) {
      set_gcId(gcId);
    }
  }

  void commit(unsigned gcId) {
    if (should_commit()) {
      set_gcId(gcId);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId) {
    EventOldGarbageCollection me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_gcId(gcId);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
  }
#endif
};

class EventG1GarbageCollection : public JfrEvent<EventG1GarbageCollection>
{
 private:
  unsigned _gcId;
  u8 _type;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrG1GarbageCollectionEvent;

  EventG1GarbageCollection(EventStartTime timing=TIMED) : JfrEvent<EventG1GarbageCollection>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_type(u8 new_value) {
    this->_type = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_type);
  }

  using JfrEvent<EventG1GarbageCollection>::commit; // else commit() is hidden by overloaded versions in this class

  EventG1GarbageCollection(
    unsigned gcId,
    u8 type) : JfrEvent<EventG1GarbageCollection>(TIMED) {
    if (should_commit()) {
      set_gcId(gcId);
      set_type(type);
    }
  }

  void commit(unsigned gcId,
              u8 type) {
    if (should_commit()) {
      set_gcId(gcId);
      set_type(type);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId,
                     u8 type) {
    EventG1GarbageCollection me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_gcId(gcId);
      me.set_type(type);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: type");
  }
#endif
};

class EventG1MMU : public JfrEvent<EventG1MMU>
{
 private:
  unsigned _gcId;
  s8 _timeSlice;
  s8 _gcTime;
  s8 _pauseTarget;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrG1MMUEvent;

  EventG1MMU(EventStartTime timing=TIMED) : JfrEvent<EventG1MMU>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_timeSlice(s8 new_value) {
    this->_timeSlice = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_gcTime(s8 new_value) {
    this->_gcTime = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_pauseTarget(s8 new_value) {
    this->_pauseTarget = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_timeSlice);
    w.write(_gcTime);
    w.write(_pauseTarget);
  }

  using JfrEvent<EventG1MMU>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     s8 timeSlice,
                     s8 gcTime,
                     s8 pauseTarget) {
    EventG1MMU me(UNTIMED);

    if (me.should_commit()) {
      me.set_gcId(gcId);
      me.set_timeSlice(timeSlice);
      me.set_gcTime(gcTime);
      me.set_pauseTarget(pauseTarget);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: timeSlice");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: gcTime");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: pauseTarget");
  }
#endif
};

class EventEvacuationInformation : public JfrEvent<EventEvacuationInformation>
{
 private:
  unsigned _gcId;
  unsigned _cSetRegions;
  u8 _cSetUsedBefore;
  u8 _cSetUsedAfter;
  unsigned _allocationRegions;
  u8 _allocationRegionsUsedBefore;
  u8 _allocationRegionsUsedAfter;
  u8 _bytesCopied;
  unsigned _regionsFreed;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrEvacuationInformationEvent;

  EventEvacuationInformation(EventStartTime timing=TIMED) : JfrEvent<EventEvacuationInformation>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_cSetRegions(unsigned new_value) {
    this->_cSetRegions = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_cSetUsedBefore(u8 new_value) {
    this->_cSetUsedBefore = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_cSetUsedAfter(u8 new_value) {
    this->_cSetUsedAfter = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_allocationRegions(unsigned new_value) {
    this->_allocationRegions = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_allocationRegionsUsedBefore(u8 new_value) {
    this->_allocationRegionsUsedBefore = new_value;
    DEBUG_ONLY(set_field_bit(5));
  }
  void set_allocationRegionsUsedAfter(u8 new_value) {
    this->_allocationRegionsUsedAfter = new_value;
    DEBUG_ONLY(set_field_bit(6));
  }
  void set_bytesCopied(u8 new_value) {
    this->_bytesCopied = new_value;
    DEBUG_ONLY(set_field_bit(7));
  }
  void set_regionsFreed(unsigned new_value) {
    this->_regionsFreed = new_value;
    DEBUG_ONLY(set_field_bit(8));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_cSetRegions);
    w.write(_cSetUsedBefore);
    w.write(_cSetUsedAfter);
    w.write(_allocationRegions);
    w.write(_allocationRegionsUsedBefore);
    w.write(_allocationRegionsUsedAfter);
    w.write(_bytesCopied);
    w.write(_regionsFreed);
  }

  using JfrEvent<EventEvacuationInformation>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     unsigned cSetRegions,
                     u8 cSetUsedBefore,
                     u8 cSetUsedAfter,
                     unsigned allocationRegions,
                     u8 allocationRegionsUsedBefore,
                     u8 allocationRegionsUsedAfter,
                     u8 bytesCopied,
                     unsigned regionsFreed) {
    EventEvacuationInformation me(UNTIMED);

    if (me.should_commit()) {
      me.set_gcId(gcId);
      me.set_cSetRegions(cSetRegions);
      me.set_cSetUsedBefore(cSetUsedBefore);
      me.set_cSetUsedAfter(cSetUsedAfter);
      me.set_allocationRegions(allocationRegions);
      me.set_allocationRegionsUsedBefore(allocationRegionsUsedBefore);
      me.set_allocationRegionsUsedAfter(allocationRegionsUsedAfter);
      me.set_bytesCopied(bytesCopied);
      me.set_regionsFreed(regionsFreed);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: cSetRegions");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: cSetUsedBefore");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: cSetUsedAfter");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: allocationRegions");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: allocationRegionsUsedBefore");
    assert(verify_field_bit(6), "Attempting to write an uninitialized event field: allocationRegionsUsedAfter");
    assert(verify_field_bit(7), "Attempting to write an uninitialized event field: bytesCopied");
    assert(verify_field_bit(8), "Attempting to write an uninitialized event field: regionsFreed");
  }
#endif
};

class EventGCReferenceStatistics : public JfrEvent<EventGCReferenceStatistics>
{
 private:
  unsigned _gcId;
  u8 _type;
  u8 _count;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrGCReferenceStatisticsEvent;

  EventGCReferenceStatistics(EventStartTime timing=TIMED) : JfrEvent<EventGCReferenceStatistics>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_type(u8 new_value) {
    this->_type = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_count(u8 new_value) {
    this->_count = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_type);
    w.write(_count);
  }

  using JfrEvent<EventGCReferenceStatistics>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     u8 type,
                     u8 count) {
    EventGCReferenceStatistics me(UNTIMED);

    if (me.should_commit()) {
      me.set_gcId(gcId);
      me.set_type(type);
      me.set_count(count);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: type");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: count");
  }
#endif
};

class EventObjectCountAfterGC : public JfrEvent<EventObjectCountAfterGC>
{
 private:
  unsigned _gcId;
  const Klass* _objectClass;
  s8 _count;
  u8 _totalSize;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrObjectCountAfterGCEvent;

  EventObjectCountAfterGC(EventStartTime timing=TIMED) : JfrEvent<EventObjectCountAfterGC>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_objectClass(const Klass* new_value) {
    this->_objectClass = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_count(s8 new_value) {
    this->_count = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_totalSize(u8 new_value) {
    this->_totalSize = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_objectClass);
    w.write(_count);
    w.write(_totalSize);
  }

  using JfrEvent<EventObjectCountAfterGC>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     const Klass* objectClass,
                     s8 count,
                     u8 totalSize) {
    EventObjectCountAfterGC me(UNTIMED);

    if (me.should_commit()) {
      me.set_gcId(gcId);
      me.set_objectClass(objectClass);
      me.set_count(count);
      me.set_totalSize(totalSize);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: objectClass");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: count");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: totalSize");
  }
#endif
};

class EventG1EvacuationYoungStatistics : public JfrEvent<EventG1EvacuationYoungStatistics>
{
 private:
  JfrStructG1EvacuationStatistics _statistics;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrG1EvacuationYoungStatisticsEvent;

  EventG1EvacuationYoungStatistics(EventStartTime timing=TIMED) : JfrEvent<EventG1EvacuationYoungStatistics>(timing) {}

  void set_statistics(const JfrStructG1EvacuationStatistics& value) {
    this->_statistics = value;
    DEBUG_ONLY(set_field_bit(0));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    _statistics.writeData(w);
  }

  using JfrEvent<EventG1EvacuationYoungStatistics>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const JfrStructG1EvacuationStatistics& statistics) {
    EventG1EvacuationYoungStatistics me(UNTIMED);

    if (me.should_commit()) {
      me.set_statistics(statistics);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: statistics");
  }
#endif
};

class EventG1EvacuationOldStatistics : public JfrEvent<EventG1EvacuationOldStatistics>
{
 private:
  JfrStructG1EvacuationStatistics _statistics;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrG1EvacuationOldStatisticsEvent;

  EventG1EvacuationOldStatistics(EventStartTime timing=TIMED) : JfrEvent<EventG1EvacuationOldStatistics>(timing) {}

  void set_statistics(const JfrStructG1EvacuationStatistics& value) {
    this->_statistics = value;
    DEBUG_ONLY(set_field_bit(0));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    _statistics.writeData(w);
  }

  using JfrEvent<EventG1EvacuationOldStatistics>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const JfrStructG1EvacuationStatistics& statistics) {
    EventG1EvacuationOldStatistics me(UNTIMED);

    if (me.should_commit()) {
      me.set_statistics(statistics);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: statistics");
  }
#endif
};

class EventG1BasicIHOP : public JfrEvent<EventG1BasicIHOP>
{
 private:
  unsigned _gcId;
  u8 _threshold;
  float _thresholdPercentage;
  u8 _targetOccupancy;
  u8 _currentOccupancy;
  u8 _recentMutatorAllocationSize;
  s8 _recentMutatorDuration;
  double _recentAllocationRate;
  s8 _lastMarkingDuration;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrG1BasicIHOPEvent;

  EventG1BasicIHOP(EventStartTime timing=TIMED) : JfrEvent<EventG1BasicIHOP>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_threshold(u8 new_value) {
    this->_threshold = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_thresholdPercentage(float new_value) {
    this->_thresholdPercentage = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_targetOccupancy(u8 new_value) {
    this->_targetOccupancy = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_currentOccupancy(u8 new_value) {
    this->_currentOccupancy = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_recentMutatorAllocationSize(u8 new_value) {
    this->_recentMutatorAllocationSize = new_value;
    DEBUG_ONLY(set_field_bit(5));
  }
  void set_recentMutatorDuration(s8 new_value) {
    this->_recentMutatorDuration = new_value;
    DEBUG_ONLY(set_field_bit(6));
  }
  void set_recentAllocationRate(double new_value) {
    this->_recentAllocationRate = new_value;
    DEBUG_ONLY(set_field_bit(7));
  }
  void set_lastMarkingDuration(s8 new_value) {
    this->_lastMarkingDuration = new_value;
    DEBUG_ONLY(set_field_bit(8));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_threshold);
    w.write(_thresholdPercentage);
    w.write(_targetOccupancy);
    w.write(_currentOccupancy);
    w.write(_recentMutatorAllocationSize);
    w.write(_recentMutatorDuration);
    w.write(_recentAllocationRate);
    w.write(_lastMarkingDuration);
  }

  using JfrEvent<EventG1BasicIHOP>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     u8 threshold,
                     float thresholdPercentage,
                     u8 targetOccupancy,
                     u8 currentOccupancy,
                     u8 recentMutatorAllocationSize,
                     s8 recentMutatorDuration,
                     double recentAllocationRate,
                     s8 lastMarkingDuration) {
    EventG1BasicIHOP me(UNTIMED);

    if (me.should_commit()) {
      me.set_gcId(gcId);
      me.set_threshold(threshold);
      me.set_thresholdPercentage(thresholdPercentage);
      me.set_targetOccupancy(targetOccupancy);
      me.set_currentOccupancy(currentOccupancy);
      me.set_recentMutatorAllocationSize(recentMutatorAllocationSize);
      me.set_recentMutatorDuration(recentMutatorDuration);
      me.set_recentAllocationRate(recentAllocationRate);
      me.set_lastMarkingDuration(lastMarkingDuration);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: threshold");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: thresholdPercentage");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: targetOccupancy");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: currentOccupancy");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: recentMutatorAllocationSize");
    assert(verify_field_bit(6), "Attempting to write an uninitialized event field: recentMutatorDuration");
    assert(verify_field_bit(7), "Attempting to write an uninitialized event field: recentAllocationRate");
    assert(verify_field_bit(8), "Attempting to write an uninitialized event field: lastMarkingDuration");
  }
#endif
};

class EventG1AdaptiveIHOP : public JfrEvent<EventG1AdaptiveIHOP>
{
 private:
  unsigned _gcId;
  u8 _threshold;
  float _thresholdPercentage;
  u8 _ihopTargetOccupancy;
  u8 _currentOccupancy;
  u8 _additionalBufferSize;
  double _predictedAllocationRate;
  s8 _predictedMarkingDuration;
  bool _predictionActive;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrG1AdaptiveIHOPEvent;

  EventG1AdaptiveIHOP(EventStartTime timing=TIMED) : JfrEvent<EventG1AdaptiveIHOP>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_threshold(u8 new_value) {
    this->_threshold = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_thresholdPercentage(float new_value) {
    this->_thresholdPercentage = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_ihopTargetOccupancy(u8 new_value) {
    this->_ihopTargetOccupancy = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_currentOccupancy(u8 new_value) {
    this->_currentOccupancy = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_additionalBufferSize(u8 new_value) {
    this->_additionalBufferSize = new_value;
    DEBUG_ONLY(set_field_bit(5));
  }
  void set_predictedAllocationRate(double new_value) {
    this->_predictedAllocationRate = new_value;
    DEBUG_ONLY(set_field_bit(6));
  }
  void set_predictedMarkingDuration(s8 new_value) {
    this->_predictedMarkingDuration = new_value;
    DEBUG_ONLY(set_field_bit(7));
  }
  void set_predictionActive(bool new_value) {
    this->_predictionActive = new_value;
    DEBUG_ONLY(set_field_bit(8));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_threshold);
    w.write(_thresholdPercentage);
    w.write(_ihopTargetOccupancy);
    w.write(_currentOccupancy);
    w.write(_additionalBufferSize);
    w.write(_predictedAllocationRate);
    w.write(_predictedMarkingDuration);
    w.write(_predictionActive);
  }

  using JfrEvent<EventG1AdaptiveIHOP>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     u8 threshold,
                     float thresholdPercentage,
                     u8 ihopTargetOccupancy,
                     u8 currentOccupancy,
                     u8 additionalBufferSize,
                     double predictedAllocationRate,
                     s8 predictedMarkingDuration,
                     bool predictionActive) {
    EventG1AdaptiveIHOP me(UNTIMED);

    if (me.should_commit()) {
      me.set_gcId(gcId);
      me.set_threshold(threshold);
      me.set_thresholdPercentage(thresholdPercentage);
      me.set_ihopTargetOccupancy(ihopTargetOccupancy);
      me.set_currentOccupancy(currentOccupancy);
      me.set_additionalBufferSize(additionalBufferSize);
      me.set_predictedAllocationRate(predictedAllocationRate);
      me.set_predictedMarkingDuration(predictedMarkingDuration);
      me.set_predictionActive(predictionActive);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: threshold");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: thresholdPercentage");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: ihopTargetOccupancy");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: currentOccupancy");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: additionalBufferSize");
    assert(verify_field_bit(6), "Attempting to write an uninitialized event field: predictedAllocationRate");
    assert(verify_field_bit(7), "Attempting to write an uninitialized event field: predictedMarkingDuration");
    assert(verify_field_bit(8), "Attempting to write an uninitialized event field: predictionActive");
  }
#endif
};

class EventPromoteObjectInNewPLAB : public JfrEvent<EventPromoteObjectInNewPLAB>
{
 private:
  unsigned _gcId;
  const Klass* _objectClass;
  u8 _objectSize;
  unsigned _tenuringAge;
  bool _tenured;
  u8 _plabSize;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrPromoteObjectInNewPLABEvent;

  EventPromoteObjectInNewPLAB(EventStartTime timing=TIMED) : JfrEvent<EventPromoteObjectInNewPLAB>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_objectClass(const Klass* new_value) {
    this->_objectClass = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_objectSize(u8 new_value) {
    this->_objectSize = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_tenuringAge(unsigned new_value) {
    this->_tenuringAge = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_tenured(bool new_value) {
    this->_tenured = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_plabSize(u8 new_value) {
    this->_plabSize = new_value;
    DEBUG_ONLY(set_field_bit(5));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_objectClass);
    w.write(_objectSize);
    w.write(_tenuringAge);
    w.write(_tenured);
    w.write(_plabSize);
  }

  using JfrEvent<EventPromoteObjectInNewPLAB>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     const Klass* objectClass,
                     u8 objectSize,
                     unsigned tenuringAge,
                     bool tenured,
                     u8 plabSize) {
    EventPromoteObjectInNewPLAB me(UNTIMED);

    if (me.should_commit()) {
      me.set_gcId(gcId);
      me.set_objectClass(objectClass);
      me.set_objectSize(objectSize);
      me.set_tenuringAge(tenuringAge);
      me.set_tenured(tenured);
      me.set_plabSize(plabSize);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: objectClass");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: objectSize");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: tenuringAge");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: tenured");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: plabSize");
  }
#endif
};

class EventPromoteObjectOutsidePLAB : public JfrEvent<EventPromoteObjectOutsidePLAB>
{
 private:
  unsigned _gcId;
  const Klass* _objectClass;
  u8 _objectSize;
  unsigned _tenuringAge;
  bool _tenured;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrPromoteObjectOutsidePLABEvent;

  EventPromoteObjectOutsidePLAB(EventStartTime timing=TIMED) : JfrEvent<EventPromoteObjectOutsidePLAB>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_objectClass(const Klass* new_value) {
    this->_objectClass = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_objectSize(u8 new_value) {
    this->_objectSize = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_tenuringAge(unsigned new_value) {
    this->_tenuringAge = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_tenured(bool new_value) {
    this->_tenured = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_objectClass);
    w.write(_objectSize);
    w.write(_tenuringAge);
    w.write(_tenured);
  }

  using JfrEvent<EventPromoteObjectOutsidePLAB>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     const Klass* objectClass,
                     u8 objectSize,
                     unsigned tenuringAge,
                     bool tenured) {
    EventPromoteObjectOutsidePLAB me(UNTIMED);

    if (me.should_commit()) {
      me.set_gcId(gcId);
      me.set_objectClass(objectClass);
      me.set_objectSize(objectSize);
      me.set_tenuringAge(tenuringAge);
      me.set_tenured(tenured);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: objectClass");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: objectSize");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: tenuringAge");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: tenured");
  }
#endif
};

class EventPromotionFailed : public JfrEvent<EventPromotionFailed>
{
 private:
  unsigned _gcId;
  JfrStructCopyFailed _promotionFailed;
  u8 _thread;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrPromotionFailedEvent;

  EventPromotionFailed(EventStartTime timing=TIMED) : JfrEvent<EventPromotionFailed>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_promotionFailed(const JfrStructCopyFailed& value) {
    this->_promotionFailed = value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_thread(u8 new_value) {
    this->_thread = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    _promotionFailed.writeData(w);
    w.write(_thread);
  }

  using JfrEvent<EventPromotionFailed>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     const JfrStructCopyFailed& promotionFailed,
                     u8 thread) {
    EventPromotionFailed me(UNTIMED);

    if (me.should_commit()) {
      me.set_gcId(gcId);
      me.set_promotionFailed(promotionFailed);
      me.set_thread(thread);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: promotionFailed");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: thread");
  }
#endif
};

class EventEvacuationFailed : public JfrEvent<EventEvacuationFailed>
{
 private:
  unsigned _gcId;
  JfrStructCopyFailed _evacuationFailed;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrEvacuationFailedEvent;

  EventEvacuationFailed(EventStartTime timing=TIMED) : JfrEvent<EventEvacuationFailed>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_evacuationFailed(const JfrStructCopyFailed& value) {
    this->_evacuationFailed = value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    _evacuationFailed.writeData(w);
  }

  using JfrEvent<EventEvacuationFailed>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     const JfrStructCopyFailed& evacuationFailed) {
    EventEvacuationFailed me(UNTIMED);

    if (me.should_commit()) {
      me.set_gcId(gcId);
      me.set_evacuationFailed(evacuationFailed);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: evacuationFailed");
  }
#endif
};

class EventConcurrentModeFailure : public JfrEvent<EventConcurrentModeFailure>
{
 private:
  unsigned _gcId;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrConcurrentModeFailureEvent;

  EventConcurrentModeFailure(EventStartTime timing=TIMED) : JfrEvent<EventConcurrentModeFailure>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
  }

  using JfrEvent<EventConcurrentModeFailure>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId) {
    EventConcurrentModeFailure me(UNTIMED);

    if (me.should_commit()) {
      me.set_gcId(gcId);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
  }
#endif
};

class EventGCPhasePause : public JfrEvent<EventGCPhasePause>
{
 private:
  unsigned _gcId;
  const char* _name;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrGCPhasePauseEvent;

  EventGCPhasePause(EventStartTime timing=TIMED) : JfrEvent<EventGCPhasePause>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_name);
  }

  using JfrEvent<EventGCPhasePause>::commit; // else commit() is hidden by overloaded versions in this class

  EventGCPhasePause(
    unsigned gcId,
    const char* name) : JfrEvent<EventGCPhasePause>(TIMED) {
    if (should_commit()) {
      set_gcId(gcId);
      set_name(name);
    }
  }

  void commit(unsigned gcId,
              const char* name) {
    if (should_commit()) {
      set_gcId(gcId);
      set_name(name);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId,
                     const char* name) {
    EventGCPhasePause me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_gcId(gcId);
      me.set_name(name);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: name");
  }
#endif
};

class EventGCPhasePauseLevel1 : public JfrEvent<EventGCPhasePauseLevel1>
{
 private:
  unsigned _gcId;
  const char* _name;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrGCPhasePauseLevel1Event;

  EventGCPhasePauseLevel1(EventStartTime timing=TIMED) : JfrEvent<EventGCPhasePauseLevel1>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_name);
  }

  using JfrEvent<EventGCPhasePauseLevel1>::commit; // else commit() is hidden by overloaded versions in this class

  EventGCPhasePauseLevel1(
    unsigned gcId,
    const char* name) : JfrEvent<EventGCPhasePauseLevel1>(TIMED) {
    if (should_commit()) {
      set_gcId(gcId);
      set_name(name);
    }
  }

  void commit(unsigned gcId,
              const char* name) {
    if (should_commit()) {
      set_gcId(gcId);
      set_name(name);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId,
                     const char* name) {
    EventGCPhasePauseLevel1 me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_gcId(gcId);
      me.set_name(name);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: name");
  }
#endif
};

class EventGCPhasePauseLevel2 : public JfrEvent<EventGCPhasePauseLevel2>
{
 private:
  unsigned _gcId;
  const char* _name;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrGCPhasePauseLevel2Event;

  EventGCPhasePauseLevel2(EventStartTime timing=TIMED) : JfrEvent<EventGCPhasePauseLevel2>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_name);
  }

  using JfrEvent<EventGCPhasePauseLevel2>::commit; // else commit() is hidden by overloaded versions in this class

  EventGCPhasePauseLevel2(
    unsigned gcId,
    const char* name) : JfrEvent<EventGCPhasePauseLevel2>(TIMED) {
    if (should_commit()) {
      set_gcId(gcId);
      set_name(name);
    }
  }

  void commit(unsigned gcId,
              const char* name) {
    if (should_commit()) {
      set_gcId(gcId);
      set_name(name);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId,
                     const char* name) {
    EventGCPhasePauseLevel2 me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_gcId(gcId);
      me.set_name(name);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: name");
  }
#endif
};

class EventGCPhasePauseLevel3 : public JfrEvent<EventGCPhasePauseLevel3>
{
 private:
  unsigned _gcId;
  const char* _name;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrGCPhasePauseLevel3Event;

  EventGCPhasePauseLevel3(EventStartTime timing=TIMED) : JfrEvent<EventGCPhasePauseLevel3>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_name);
  }

  using JfrEvent<EventGCPhasePauseLevel3>::commit; // else commit() is hidden by overloaded versions in this class

  EventGCPhasePauseLevel3(
    unsigned gcId,
    const char* name) : JfrEvent<EventGCPhasePauseLevel3>(TIMED) {
    if (should_commit()) {
      set_gcId(gcId);
      set_name(name);
    }
  }

  void commit(unsigned gcId,
              const char* name) {
    if (should_commit()) {
      set_gcId(gcId);
      set_name(name);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId,
                     const char* name) {
    EventGCPhasePauseLevel3 me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_gcId(gcId);
      me.set_name(name);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: name");
  }
#endif
};

class EventGCPhasePauseLevel4 : public JfrEvent<EventGCPhasePauseLevel4>
{
 private:
  unsigned _gcId;
  const char* _name;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrGCPhasePauseLevel4Event;

  EventGCPhasePauseLevel4(EventStartTime timing=TIMED) : JfrEvent<EventGCPhasePauseLevel4>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_name);
  }

  using JfrEvent<EventGCPhasePauseLevel4>::commit; // else commit() is hidden by overloaded versions in this class

  EventGCPhasePauseLevel4(
    unsigned gcId,
    const char* name) : JfrEvent<EventGCPhasePauseLevel4>(TIMED) {
    if (should_commit()) {
      set_gcId(gcId);
      set_name(name);
    }
  }

  void commit(unsigned gcId,
              const char* name) {
    if (should_commit()) {
      set_gcId(gcId);
      set_name(name);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId,
                     const char* name) {
    EventGCPhasePauseLevel4 me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_gcId(gcId);
      me.set_name(name);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: name");
  }
#endif
};

class EventGCPhaseConcurrent : public JfrEvent<EventGCPhaseConcurrent>
{
 private:
  unsigned _gcId;
  const char* _name;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrGCPhaseConcurrentEvent;

  EventGCPhaseConcurrent(EventStartTime timing=TIMED) : JfrEvent<EventGCPhaseConcurrent>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_name);
  }

  using JfrEvent<EventGCPhaseConcurrent>::commit; // else commit() is hidden by overloaded versions in this class

  EventGCPhaseConcurrent(
    unsigned gcId,
    const char* name) : JfrEvent<EventGCPhaseConcurrent>(TIMED) {
    if (should_commit()) {
      set_gcId(gcId);
      set_name(name);
    }
  }

  void commit(unsigned gcId,
              const char* name) {
    if (should_commit()) {
      set_gcId(gcId);
      set_name(name);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId,
                     const char* name) {
    EventGCPhaseConcurrent me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_gcId(gcId);
      me.set_name(name);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: name");
  }
#endif
};

class EventAllocationRequiringGC : public JfrEvent<EventAllocationRequiringGC>
{
 private:
  unsigned _gcId;
  u8 _size;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrAllocationRequiringGCEvent;

  EventAllocationRequiringGC(EventStartTime timing=TIMED) : JfrEvent<EventAllocationRequiringGC>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_size(u8 new_value) {
    this->_size = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_size);
  }

  using JfrEvent<EventAllocationRequiringGC>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     u8 size) {
    EventAllocationRequiringGC me(UNTIMED);

    if (me.should_commit()) {
      me.set_gcId(gcId);
      me.set_size(size);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: size");
  }
#endif
};

class EventTenuringDistribution : public JfrEvent<EventTenuringDistribution>
{
 private:
  unsigned _gcId;
  unsigned _age;
  u8 _size;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrTenuringDistributionEvent;

  EventTenuringDistribution(EventStartTime timing=TIMED) : JfrEvent<EventTenuringDistribution>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_age(unsigned new_value) {
    this->_age = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_size(u8 new_value) {
    this->_size = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_age);
    w.write(_size);
  }

  using JfrEvent<EventTenuringDistribution>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     unsigned age,
                     u8 size) {
    EventTenuringDistribution me(UNTIMED);

    if (me.should_commit()) {
      me.set_gcId(gcId);
      me.set_age(age);
      me.set_size(size);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: age");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: size");
  }
#endif
};

class EventG1HeapRegionTypeChange : public JfrEvent<EventG1HeapRegionTypeChange>
{
 private:
  unsigned _index;
  u8 _from;
  u8 _to;
  u8 _start;
  u8 _used;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrG1HeapRegionTypeChangeEvent;

  EventG1HeapRegionTypeChange(EventStartTime timing=TIMED) : JfrEvent<EventG1HeapRegionTypeChange>(timing) {}

  void set_index(unsigned new_value) {
    this->_index = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_from(u8 new_value) {
    this->_from = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_to(u8 new_value) {
    this->_to = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_start(u8 new_value) {
    this->_start = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_used(u8 new_value) {
    this->_used = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_index);
    w.write(_from);
    w.write(_to);
    w.write(_start);
    w.write(_used);
  }

  using JfrEvent<EventG1HeapRegionTypeChange>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned index,
                     u8 from,
                     u8 to,
                     u8 start,
                     u8 used) {
    EventG1HeapRegionTypeChange me(UNTIMED);

    if (me.should_commit()) {
      me.set_index(index);
      me.set_from(from);
      me.set_to(to);
      me.set_start(start);
      me.set_used(used);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: index");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: from");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: to");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: start");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: used");
  }
#endif
};

class EventCompilation : public JfrEvent<EventCompilation>
{
 private:
  const Method* _method;
  unsigned _compileId;
  u2 _compileLevel;
  bool _succeded;
  bool _isOsr;
  u8 _codeSize;
  u8 _inlinedBytes;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrCompilationEvent;

  EventCompilation(EventStartTime timing=TIMED) : JfrEvent<EventCompilation>(timing) {}

  void set_method(const Method* new_value) {
    this->_method = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_compileId(unsigned new_value) {
    this->_compileId = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_compileLevel(u2 new_value) {
    this->_compileLevel = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_succeded(bool new_value) {
    this->_succeded = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_isOsr(bool new_value) {
    this->_isOsr = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_codeSize(u8 new_value) {
    this->_codeSize = new_value;
    DEBUG_ONLY(set_field_bit(5));
  }
  void set_inlinedBytes(u8 new_value) {
    this->_inlinedBytes = new_value;
    DEBUG_ONLY(set_field_bit(6));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_method);
    w.write(_compileId);
    w.write(_compileLevel);
    w.write(_succeded);
    w.write(_isOsr);
    w.write(_codeSize);
    w.write(_inlinedBytes);
  }

  using JfrEvent<EventCompilation>::commit; // else commit() is hidden by overloaded versions in this class

  EventCompilation(
    const Method* method,
    unsigned compileId,
    u2 compileLevel,
    bool succeded,
    bool isOsr,
    u8 codeSize,
    u8 inlinedBytes) : JfrEvent<EventCompilation>(TIMED) {
    if (should_commit()) {
      set_method(method);
      set_compileId(compileId);
      set_compileLevel(compileLevel);
      set_succeded(succeded);
      set_isOsr(isOsr);
      set_codeSize(codeSize);
      set_inlinedBytes(inlinedBytes);
    }
  }

  void commit(const Method* method,
              unsigned compileId,
              u2 compileLevel,
              bool succeded,
              bool isOsr,
              u8 codeSize,
              u8 inlinedBytes) {
    if (should_commit()) {
      set_method(method);
      set_compileId(compileId);
      set_compileLevel(compileLevel);
      set_succeded(succeded);
      set_isOsr(isOsr);
      set_codeSize(codeSize);
      set_inlinedBytes(inlinedBytes);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const Method* method,
                     unsigned compileId,
                     u2 compileLevel,
                     bool succeded,
                     bool isOsr,
                     u8 codeSize,
                     u8 inlinedBytes) {
    EventCompilation me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_method(method);
      me.set_compileId(compileId);
      me.set_compileLevel(compileLevel);
      me.set_succeded(succeded);
      me.set_isOsr(isOsr);
      me.set_codeSize(codeSize);
      me.set_inlinedBytes(inlinedBytes);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: method");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: compileId");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: compileLevel");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: succeded");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: isOsr");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: codeSize");
    assert(verify_field_bit(6), "Attempting to write an uninitialized event field: inlinedBytes");
  }
#endif
};

class EventCompilerPhase : public JfrEvent<EventCompilerPhase>
{
 private:
  u8 _phase;
  unsigned _compileId;
  u2 _phaseLevel;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrCompilerPhaseEvent;

  EventCompilerPhase(EventStartTime timing=TIMED) : JfrEvent<EventCompilerPhase>(timing) {}

  void set_phase(u8 new_value) {
    this->_phase = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_compileId(unsigned new_value) {
    this->_compileId = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_phaseLevel(u2 new_value) {
    this->_phaseLevel = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_phase);
    w.write(_compileId);
    w.write(_phaseLevel);
  }

  using JfrEvent<EventCompilerPhase>::commit; // else commit() is hidden by overloaded versions in this class

  EventCompilerPhase(
    u8 phase,
    unsigned compileId,
    u2 phaseLevel) : JfrEvent<EventCompilerPhase>(TIMED) {
    if (should_commit()) {
      set_phase(phase);
      set_compileId(compileId);
      set_phaseLevel(phaseLevel);
    }
  }

  void commit(u8 phase,
              unsigned compileId,
              u2 phaseLevel) {
    if (should_commit()) {
      set_phase(phase);
      set_compileId(compileId);
      set_phaseLevel(phaseLevel);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 phase,
                     unsigned compileId,
                     u2 phaseLevel) {
    EventCompilerPhase me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_phase(phase);
      me.set_compileId(compileId);
      me.set_phaseLevel(phaseLevel);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: phase");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: compileId");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: phaseLevel");
  }
#endif
};

class EventCompilationFailure : public JfrEvent<EventCompilationFailure>
{
 private:
  const char* _failureMessage;
  unsigned _compileId;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrCompilationFailureEvent;

  EventCompilationFailure(EventStartTime timing=TIMED) : JfrEvent<EventCompilationFailure>(timing) {}

  void set_failureMessage(const char* new_value) {
    this->_failureMessage = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_compileId(unsigned new_value) {
    this->_compileId = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_failureMessage);
    w.write(_compileId);
  }

  using JfrEvent<EventCompilationFailure>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const char* failureMessage,
                     unsigned compileId) {
    EventCompilationFailure me(UNTIMED);

    if (me.should_commit()) {
      me.set_failureMessage(failureMessage);
      me.set_compileId(compileId);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: failureMessage");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: compileId");
  }
#endif
};

class EventCompilerInlining : public JfrEvent<EventCompilerInlining>
{
 private:
  unsigned _compileId;
  const Method* _caller;
  JfrStructCalleeMethod _callee;
  bool _succeeded;
  const char* _message;
  s4 _bci;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrCompilerInliningEvent;

  EventCompilerInlining(EventStartTime timing=TIMED) : JfrEvent<EventCompilerInlining>(timing) {}

  void set_compileId(unsigned new_value) {
    this->_compileId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_caller(const Method* new_value) {
    this->_caller = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_callee(const JfrStructCalleeMethod& value) {
    this->_callee = value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_succeeded(bool new_value) {
    this->_succeeded = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_message(const char* new_value) {
    this->_message = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_bci(s4 new_value) {
    this->_bci = new_value;
    DEBUG_ONLY(set_field_bit(5));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_compileId);
    w.write(_caller);
    _callee.writeData(w);
    w.write(_succeeded);
    w.write(_message);
    w.write(_bci);
  }

  using JfrEvent<EventCompilerInlining>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned compileId,
                     const Method* caller,
                     const JfrStructCalleeMethod& callee,
                     bool succeeded,
                     const char* message,
                     s4 bci) {
    EventCompilerInlining me(UNTIMED);

    if (me.should_commit()) {
      me.set_compileId(compileId);
      me.set_caller(caller);
      me.set_callee(callee);
      me.set_succeeded(succeeded);
      me.set_message(message);
      me.set_bci(bci);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: compileId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: caller");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: callee");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: succeeded");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: message");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: bci");
  }
#endif
};

class EventSweepCodeCache : public JfrEvent<EventSweepCodeCache>
{
 private:
  s4 _sweepId;
  unsigned _sweptCount;
  unsigned _flushedCount;
  unsigned _zombifiedCount;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrSweepCodeCacheEvent;

  EventSweepCodeCache(EventStartTime timing=TIMED) : JfrEvent<EventSweepCodeCache>(timing) {}

  void set_sweepId(s4 new_value) {
    this->_sweepId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_sweptCount(unsigned new_value) {
    this->_sweptCount = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_flushedCount(unsigned new_value) {
    this->_flushedCount = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_zombifiedCount(unsigned new_value) {
    this->_zombifiedCount = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_sweepId);
    w.write(_sweptCount);
    w.write(_flushedCount);
    w.write(_zombifiedCount);
  }

  using JfrEvent<EventSweepCodeCache>::commit; // else commit() is hidden by overloaded versions in this class

  EventSweepCodeCache(
    s4 sweepId,
    unsigned sweptCount,
    unsigned flushedCount,
    unsigned zombifiedCount) : JfrEvent<EventSweepCodeCache>(TIMED) {
    if (should_commit()) {
      set_sweepId(sweepId);
      set_sweptCount(sweptCount);
      set_flushedCount(flushedCount);
      set_zombifiedCount(zombifiedCount);
    }
  }

  void commit(s4 sweepId,
              unsigned sweptCount,
              unsigned flushedCount,
              unsigned zombifiedCount) {
    if (should_commit()) {
      set_sweepId(sweepId);
      set_sweptCount(sweptCount);
      set_flushedCount(flushedCount);
      set_zombifiedCount(zombifiedCount);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     s4 sweepId,
                     unsigned sweptCount,
                     unsigned flushedCount,
                     unsigned zombifiedCount) {
    EventSweepCodeCache me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_sweepId(sweepId);
      me.set_sweptCount(sweptCount);
      me.set_flushedCount(flushedCount);
      me.set_zombifiedCount(zombifiedCount);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: sweepId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: sweptCount");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: flushedCount");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: zombifiedCount");
  }
#endif
};

class EventCodeCacheFull : public JfrEvent<EventCodeCacheFull>
{
 private:
  u8 _codeBlobType;
  u8 _startAddress;
  u8 _commitedTopAddress;
  u8 _reservedTopAddress;
  s4 _entryCount;
  s4 _methodCount;
  s4 _adaptorCount;
  u8 _unallocatedCapacity;
  s4 _fullCount;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrCodeCacheFullEvent;

  EventCodeCacheFull(EventStartTime timing=TIMED) : JfrEvent<EventCodeCacheFull>(timing) {}

  void set_codeBlobType(u8 new_value) {
    this->_codeBlobType = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_startAddress(u8 new_value) {
    this->_startAddress = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_commitedTopAddress(u8 new_value) {
    this->_commitedTopAddress = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_reservedTopAddress(u8 new_value) {
    this->_reservedTopAddress = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_entryCount(s4 new_value) {
    this->_entryCount = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_methodCount(s4 new_value) {
    this->_methodCount = new_value;
    DEBUG_ONLY(set_field_bit(5));
  }
  void set_adaptorCount(s4 new_value) {
    this->_adaptorCount = new_value;
    DEBUG_ONLY(set_field_bit(6));
  }
  void set_unallocatedCapacity(u8 new_value) {
    this->_unallocatedCapacity = new_value;
    DEBUG_ONLY(set_field_bit(7));
  }
  void set_fullCount(s4 new_value) {
    this->_fullCount = new_value;
    DEBUG_ONLY(set_field_bit(8));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_codeBlobType);
    w.write(_startAddress);
    w.write(_commitedTopAddress);
    w.write(_reservedTopAddress);
    w.write(_entryCount);
    w.write(_methodCount);
    w.write(_adaptorCount);
    w.write(_unallocatedCapacity);
    w.write(_fullCount);
  }

  using JfrEvent<EventCodeCacheFull>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(u8 codeBlobType,
                     u8 startAddress,
                     u8 commitedTopAddress,
                     u8 reservedTopAddress,
                     s4 entryCount,
                     s4 methodCount,
                     s4 adaptorCount,
                     u8 unallocatedCapacity,
                     s4 fullCount) {
    EventCodeCacheFull me(UNTIMED);

    if (me.should_commit()) {
      me.set_codeBlobType(codeBlobType);
      me.set_startAddress(startAddress);
      me.set_commitedTopAddress(commitedTopAddress);
      me.set_reservedTopAddress(reservedTopAddress);
      me.set_entryCount(entryCount);
      me.set_methodCount(methodCount);
      me.set_adaptorCount(adaptorCount);
      me.set_unallocatedCapacity(unallocatedCapacity);
      me.set_fullCount(fullCount);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: codeBlobType");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: startAddress");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: commitedTopAddress");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: reservedTopAddress");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: entryCount");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: methodCount");
    assert(verify_field_bit(6), "Attempting to write an uninitialized event field: adaptorCount");
    assert(verify_field_bit(7), "Attempting to write an uninitialized event field: unallocatedCapacity");
    assert(verify_field_bit(8), "Attempting to write an uninitialized event field: fullCount");
  }
#endif
};

class EventSafepointBegin : public JfrEvent<EventSafepointBegin>
{
 private:
  s4 _safepointId;
  s4 _totalThreadCount;
  s4 _jniCriticalThreadCount;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrSafepointBeginEvent;

  EventSafepointBegin(EventStartTime timing=TIMED) : JfrEvent<EventSafepointBegin>(timing) {}

  void set_safepointId(s4 new_value) {
    this->_safepointId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_totalThreadCount(s4 new_value) {
    this->_totalThreadCount = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_jniCriticalThreadCount(s4 new_value) {
    this->_jniCriticalThreadCount = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_safepointId);
    w.write(_totalThreadCount);
    w.write(_jniCriticalThreadCount);
  }

  using JfrEvent<EventSafepointBegin>::commit; // else commit() is hidden by overloaded versions in this class

  EventSafepointBegin(
    s4 safepointId,
    s4 totalThreadCount,
    s4 jniCriticalThreadCount) : JfrEvent<EventSafepointBegin>(TIMED) {
    if (should_commit()) {
      set_safepointId(safepointId);
      set_totalThreadCount(totalThreadCount);
      set_jniCriticalThreadCount(jniCriticalThreadCount);
    }
  }

  void commit(s4 safepointId,
              s4 totalThreadCount,
              s4 jniCriticalThreadCount) {
    if (should_commit()) {
      set_safepointId(safepointId);
      set_totalThreadCount(totalThreadCount);
      set_jniCriticalThreadCount(jniCriticalThreadCount);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     s4 safepointId,
                     s4 totalThreadCount,
                     s4 jniCriticalThreadCount) {
    EventSafepointBegin me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_safepointId(safepointId);
      me.set_totalThreadCount(totalThreadCount);
      me.set_jniCriticalThreadCount(jniCriticalThreadCount);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: safepointId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: totalThreadCount");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: jniCriticalThreadCount");
  }
#endif
};

class EventSafepointStateSynchronization : public JfrEvent<EventSafepointStateSynchronization>
{
 private:
  s4 _safepointId;
  s4 _initialThreadCount;
  s4 _runningThreadCount;
  s4 _iterations;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrSafepointStateSynchronizationEvent;

  EventSafepointStateSynchronization(EventStartTime timing=TIMED) : JfrEvent<EventSafepointStateSynchronization>(timing) {}

  void set_safepointId(s4 new_value) {
    this->_safepointId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_initialThreadCount(s4 new_value) {
    this->_initialThreadCount = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_runningThreadCount(s4 new_value) {
    this->_runningThreadCount = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_iterations(s4 new_value) {
    this->_iterations = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_safepointId);
    w.write(_initialThreadCount);
    w.write(_runningThreadCount);
    w.write(_iterations);
  }

  using JfrEvent<EventSafepointStateSynchronization>::commit; // else commit() is hidden by overloaded versions in this class

  EventSafepointStateSynchronization(
    s4 safepointId,
    s4 initialThreadCount,
    s4 runningThreadCount,
    s4 iterations) : JfrEvent<EventSafepointStateSynchronization>(TIMED) {
    if (should_commit()) {
      set_safepointId(safepointId);
      set_initialThreadCount(initialThreadCount);
      set_runningThreadCount(runningThreadCount);
      set_iterations(iterations);
    }
  }

  void commit(s4 safepointId,
              s4 initialThreadCount,
              s4 runningThreadCount,
              s4 iterations) {
    if (should_commit()) {
      set_safepointId(safepointId);
      set_initialThreadCount(initialThreadCount);
      set_runningThreadCount(runningThreadCount);
      set_iterations(iterations);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     s4 safepointId,
                     s4 initialThreadCount,
                     s4 runningThreadCount,
                     s4 iterations) {
    EventSafepointStateSynchronization me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_safepointId(safepointId);
      me.set_initialThreadCount(initialThreadCount);
      me.set_runningThreadCount(runningThreadCount);
      me.set_iterations(iterations);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: safepointId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: initialThreadCount");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: runningThreadCount");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: iterations");
  }
#endif
};

class EventSafepointWaitBlocked : public JfrEvent<EventSafepointWaitBlocked>
{
 private:
  s4 _safepointId;
  s4 _runningThreadCount;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrSafepointWaitBlockedEvent;

  EventSafepointWaitBlocked(EventStartTime timing=TIMED) : JfrEvent<EventSafepointWaitBlocked>(timing) {}

  void set_safepointId(s4 new_value) {
    this->_safepointId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_runningThreadCount(s4 new_value) {
    this->_runningThreadCount = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_safepointId);
    w.write(_runningThreadCount);
  }

  using JfrEvent<EventSafepointWaitBlocked>::commit; // else commit() is hidden by overloaded versions in this class

  EventSafepointWaitBlocked(
    s4 safepointId,
    s4 runningThreadCount) : JfrEvent<EventSafepointWaitBlocked>(TIMED) {
    if (should_commit()) {
      set_safepointId(safepointId);
      set_runningThreadCount(runningThreadCount);
    }
  }

  void commit(s4 safepointId,
              s4 runningThreadCount) {
    if (should_commit()) {
      set_safepointId(safepointId);
      set_runningThreadCount(runningThreadCount);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     s4 safepointId,
                     s4 runningThreadCount) {
    EventSafepointWaitBlocked me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_safepointId(safepointId);
      me.set_runningThreadCount(runningThreadCount);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: safepointId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: runningThreadCount");
  }
#endif
};

class EventSafepointCleanup : public JfrEvent<EventSafepointCleanup>
{
 private:
  s4 _safepointId;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrSafepointCleanupEvent;

  EventSafepointCleanup(EventStartTime timing=TIMED) : JfrEvent<EventSafepointCleanup>(timing) {}

  void set_safepointId(s4 new_value) {
    this->_safepointId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_safepointId);
  }

  using JfrEvent<EventSafepointCleanup>::commit; // else commit() is hidden by overloaded versions in this class

  EventSafepointCleanup(
    s4 safepointId) : JfrEvent<EventSafepointCleanup>(TIMED) {
    if (should_commit()) {
      set_safepointId(safepointId);
    }
  }

  void commit(s4 safepointId) {
    if (should_commit()) {
      set_safepointId(safepointId);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     s4 safepointId) {
    EventSafepointCleanup me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_safepointId(safepointId);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: safepointId");
  }
#endif
};

class EventSafepointCleanupTask : public JfrEvent<EventSafepointCleanupTask>
{
 private:
  s4 _safepointId;
  const char* _name;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrSafepointCleanupTaskEvent;

  EventSafepointCleanupTask(EventStartTime timing=TIMED) : JfrEvent<EventSafepointCleanupTask>(timing) {}

  void set_safepointId(s4 new_value) {
    this->_safepointId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_safepointId);
    w.write(_name);
  }

  using JfrEvent<EventSafepointCleanupTask>::commit; // else commit() is hidden by overloaded versions in this class

  EventSafepointCleanupTask(
    s4 safepointId,
    const char* name) : JfrEvent<EventSafepointCleanupTask>(TIMED) {
    if (should_commit()) {
      set_safepointId(safepointId);
      set_name(name);
    }
  }

  void commit(s4 safepointId,
              const char* name) {
    if (should_commit()) {
      set_safepointId(safepointId);
      set_name(name);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     s4 safepointId,
                     const char* name) {
    EventSafepointCleanupTask me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_safepointId(safepointId);
      me.set_name(name);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: safepointId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: name");
  }
#endif
};

class EventSafepointEnd : public JfrEvent<EventSafepointEnd>
{
 private:
  s4 _safepointId;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrSafepointEndEvent;

  EventSafepointEnd(EventStartTime timing=TIMED) : JfrEvent<EventSafepointEnd>(timing) {}

  void set_safepointId(s4 new_value) {
    this->_safepointId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_safepointId);
  }

  using JfrEvent<EventSafepointEnd>::commit; // else commit() is hidden by overloaded versions in this class

  EventSafepointEnd(
    s4 safepointId) : JfrEvent<EventSafepointEnd>(TIMED) {
    if (should_commit()) {
      set_safepointId(safepointId);
    }
  }

  void commit(s4 safepointId) {
    if (should_commit()) {
      set_safepointId(safepointId);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     s4 safepointId) {
    EventSafepointEnd me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_safepointId(safepointId);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: safepointId");
  }
#endif
};

class EventExecuteVMOperation : public JfrEvent<EventExecuteVMOperation>
{
 private:
  u8 _operation;
  bool _safepoint;
  bool _blocking;
  u8 _caller;
  s4 _safepointId;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrExecuteVMOperationEvent;

  EventExecuteVMOperation(EventStartTime timing=TIMED) : JfrEvent<EventExecuteVMOperation>(timing) {}

  void set_operation(u8 new_value) {
    this->_operation = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_safepoint(bool new_value) {
    this->_safepoint = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_blocking(bool new_value) {
    this->_blocking = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_caller(u8 new_value) {
    this->_caller = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_safepointId(s4 new_value) {
    this->_safepointId = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_operation);
    w.write(_safepoint);
    w.write(_blocking);
    w.write(_caller);
    w.write(_safepointId);
  }

  using JfrEvent<EventExecuteVMOperation>::commit; // else commit() is hidden by overloaded versions in this class

  EventExecuteVMOperation(
    u8 operation,
    bool safepoint,
    bool blocking,
    u8 caller,
    s4 safepointId) : JfrEvent<EventExecuteVMOperation>(TIMED) {
    if (should_commit()) {
      set_operation(operation);
      set_safepoint(safepoint);
      set_blocking(blocking);
      set_caller(caller);
      set_safepointId(safepointId);
    }
  }

  void commit(u8 operation,
              bool safepoint,
              bool blocking,
              u8 caller,
              s4 safepointId) {
    if (should_commit()) {
      set_operation(operation);
      set_safepoint(safepoint);
      set_blocking(blocking);
      set_caller(caller);
      set_safepointId(safepointId);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 operation,
                     bool safepoint,
                     bool blocking,
                     u8 caller,
                     s4 safepointId) {
    EventExecuteVMOperation me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_operation(operation);
      me.set_safepoint(safepoint);
      me.set_blocking(blocking);
      me.set_caller(caller);
      me.set_safepointId(safepointId);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: operation");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: safepoint");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: blocking");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: caller");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: safepointId");
  }
#endif
};

class EventShutdown : public JfrEvent<EventShutdown>
{
 private:
  const char* _reason;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrShutdownEvent;

  EventShutdown(EventStartTime timing=TIMED) : JfrEvent<EventShutdown>(timing) {}

  void set_reason(const char* new_value) {
    this->_reason = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_reason);
  }

  using JfrEvent<EventShutdown>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const char* reason) {
    EventShutdown me(UNTIMED);

    if (me.should_commit()) {
      me.set_reason(reason);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: reason");
  }
#endif
};

class EventObjectAllocationInNewTLAB : public JfrEvent<EventObjectAllocationInNewTLAB>
{
 private:
  const Klass* _objectClass;
  u8 _allocationSize;
  u8 _tlabSize;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrObjectAllocationInNewTLABEvent;

  EventObjectAllocationInNewTLAB(EventStartTime timing=TIMED) : JfrEvent<EventObjectAllocationInNewTLAB>(timing) {}

  void set_objectClass(const Klass* new_value) {
    this->_objectClass = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_allocationSize(u8 new_value) {
    this->_allocationSize = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_tlabSize(u8 new_value) {
    this->_tlabSize = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_objectClass);
    w.write(_allocationSize);
    w.write(_tlabSize);
  }

  using JfrEvent<EventObjectAllocationInNewTLAB>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const Klass* objectClass,
                     u8 allocationSize,
                     u8 tlabSize) {
    EventObjectAllocationInNewTLAB me(UNTIMED);

    if (me.should_commit()) {
      me.set_objectClass(objectClass);
      me.set_allocationSize(allocationSize);
      me.set_tlabSize(tlabSize);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: objectClass");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: allocationSize");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: tlabSize");
  }
#endif
};

class EventObjectAllocationOutsideTLAB : public JfrEvent<EventObjectAllocationOutsideTLAB>
{
 private:
  const Klass* _objectClass;
  u8 _allocationSize;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrObjectAllocationOutsideTLABEvent;

  EventObjectAllocationOutsideTLAB(EventStartTime timing=TIMED) : JfrEvent<EventObjectAllocationOutsideTLAB>(timing) {}

  void set_objectClass(const Klass* new_value) {
    this->_objectClass = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_allocationSize(u8 new_value) {
    this->_allocationSize = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_objectClass);
    w.write(_allocationSize);
  }

  using JfrEvent<EventObjectAllocationOutsideTLAB>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const Klass* objectClass,
                     u8 allocationSize) {
    EventObjectAllocationOutsideTLAB me(UNTIMED);

    if (me.should_commit()) {
      me.set_objectClass(objectClass);
      me.set_allocationSize(allocationSize);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: objectClass");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: allocationSize");
  }
#endif
};

class EventOldObjectSample : public JfrEvent<EventOldObjectSample>
{
 private:
  Ticks _allocationTime;
  u8 _lastKnownHeapUsage;
  u8 _object;
  s4 _arrayElements;
  u8 _root;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = true;
  static const bool hasCutoff = true;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrOldObjectSampleEvent;

  EventOldObjectSample(EventStartTime timing=TIMED) : JfrEvent<EventOldObjectSample>(timing) {}

  void set_allocationTime(const Ticks& new_value) {
    this->_allocationTime = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_lastKnownHeapUsage(u8 new_value) {
    this->_lastKnownHeapUsage = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_object(u8 new_value) {
    this->_object = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_arrayElements(s4 new_value) {
    this->_arrayElements = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_root(u8 new_value) {
    this->_root = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_allocationTime);
    w.write(_lastKnownHeapUsage);
    w.write(_object);
    w.write(_arrayElements);
    w.write(_root);
  }

  using JfrEvent<EventOldObjectSample>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const Ticks& allocationTime,
                     u8 lastKnownHeapUsage,
                     u8 object,
                     s4 arrayElements,
                     u8 root) {
    EventOldObjectSample me(UNTIMED);

    if (me.should_commit()) {
      me.set_allocationTime(allocationTime);
      me.set_lastKnownHeapUsage(lastKnownHeapUsage);
      me.set_object(object);
      me.set_arrayElements(arrayElements);
      me.set_root(root);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: allocationTime");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: lastKnownHeapUsage");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: object");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: arrayElements");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: root");
  }
#endif
};

class EventDumpReason : public JfrEvent<EventDumpReason>
{
 private:
  const char* _reason;
  s4 _recordingId;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrDumpReasonEvent;

  EventDumpReason(EventStartTime timing=TIMED) : JfrEvent<EventDumpReason>(timing) {}

  void set_reason(const char* new_value) {
    this->_reason = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_recordingId(s4 new_value) {
    this->_recordingId = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_reason);
    w.write(_recordingId);
  }

  using JfrEvent<EventDumpReason>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const char* reason,
                     s4 recordingId) {
    EventDumpReason me(UNTIMED);

    if (me.should_commit()) {
      me.set_reason(reason);
      me.set_recordingId(recordingId);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: reason");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: recordingId");
  }
#endif
};

class EventDataLoss : public JfrEvent<EventDataLoss>
{
 private:
  u8 _amount;
  u8 _total;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrDataLossEvent;

  EventDataLoss(EventStartTime timing=TIMED) : JfrEvent<EventDataLoss>(timing) {}

  void set_amount(u8 new_value) {
    this->_amount = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_total(u8 new_value) {
    this->_total = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_amount);
    w.write(_total);
  }

  using JfrEvent<EventDataLoss>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(u8 amount,
                     u8 total) {
    EventDataLoss me(UNTIMED);

    if (me.should_commit()) {
      me.set_amount(amount);
      me.set_total(total);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: amount");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: total");
  }
#endif
};

class EventJVMInformation : public JfrEvent<EventJVMInformation>
{
 private:
  const char* _jvmName;
  const char* _jvmVersion;
  const char* _jvmArguments;
  const char* _jvmFlags;
  const char* _javaArguments;
  s8 _jvmStartTime;
  s8 _pid;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrJVMInformationEvent;

  EventJVMInformation(EventStartTime timing=TIMED) : JfrEvent<EventJVMInformation>(timing) {}

  void set_jvmName(const char* new_value) {
    this->_jvmName = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_jvmVersion(const char* new_value) {
    this->_jvmVersion = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_jvmArguments(const char* new_value) {
    this->_jvmArguments = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_jvmFlags(const char* new_value) {
    this->_jvmFlags = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_javaArguments(const char* new_value) {
    this->_javaArguments = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_jvmStartTime(s8 new_value) {
    this->_jvmStartTime = new_value;
    DEBUG_ONLY(set_field_bit(5));
  }
  void set_pid(s8 new_value) {
    this->_pid = new_value;
    DEBUG_ONLY(set_field_bit(6));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_jvmName);
    w.write(_jvmVersion);
    w.write(_jvmArguments);
    w.write(_jvmFlags);
    w.write(_javaArguments);
    w.write(_jvmStartTime);
    w.write(_pid);
  }

  using JfrEvent<EventJVMInformation>::commit; // else commit() is hidden by overloaded versions in this class

  EventJVMInformation(
    const char* jvmName,
    const char* jvmVersion,
    const char* jvmArguments,
    const char* jvmFlags,
    const char* javaArguments,
    s8 jvmStartTime,
    s8 pid) : JfrEvent<EventJVMInformation>(TIMED) {
    if (should_commit()) {
      set_jvmName(jvmName);
      set_jvmVersion(jvmVersion);
      set_jvmArguments(jvmArguments);
      set_jvmFlags(jvmFlags);
      set_javaArguments(javaArguments);
      set_jvmStartTime(jvmStartTime);
      set_pid(pid);
    }
  }

  void commit(const char* jvmName,
              const char* jvmVersion,
              const char* jvmArguments,
              const char* jvmFlags,
              const char* javaArguments,
              s8 jvmStartTime,
              s8 pid) {
    if (should_commit()) {
      set_jvmName(jvmName);
      set_jvmVersion(jvmVersion);
      set_jvmArguments(jvmArguments);
      set_jvmFlags(jvmFlags);
      set_javaArguments(javaArguments);
      set_jvmStartTime(jvmStartTime);
      set_pid(pid);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* jvmName,
                     const char* jvmVersion,
                     const char* jvmArguments,
                     const char* jvmFlags,
                     const char* javaArguments,
                     s8 jvmStartTime,
                     s8 pid) {
    EventJVMInformation me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_jvmName(jvmName);
      me.set_jvmVersion(jvmVersion);
      me.set_jvmArguments(jvmArguments);
      me.set_jvmFlags(jvmFlags);
      me.set_javaArguments(javaArguments);
      me.set_jvmStartTime(jvmStartTime);
      me.set_pid(pid);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: jvmName");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: jvmVersion");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: jvmArguments");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: jvmFlags");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: javaArguments");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: jvmStartTime");
    assert(verify_field_bit(6), "Attempting to write an uninitialized event field: pid");
  }
#endif
};

class EventOSInformation : public JfrEvent<EventOSInformation>
{
 private:
  const char* _osVersion;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrOSInformationEvent;

  EventOSInformation(EventStartTime timing=TIMED) : JfrEvent<EventOSInformation>(timing) {}

  void set_osVersion(const char* new_value) {
    this->_osVersion = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_osVersion);
  }

  using JfrEvent<EventOSInformation>::commit; // else commit() is hidden by overloaded versions in this class

  EventOSInformation(
    const char* osVersion) : JfrEvent<EventOSInformation>(TIMED) {
    if (should_commit()) {
      set_osVersion(osVersion);
    }
  }

  void commit(const char* osVersion) {
    if (should_commit()) {
      set_osVersion(osVersion);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* osVersion) {
    EventOSInformation me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_osVersion(osVersion);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: osVersion");
  }
#endif
};

class EventVirtualizationInformation : public JfrEvent<EventVirtualizationInformation>
{
 private:
  const char* _name;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrVirtualizationInformationEvent;

  EventVirtualizationInformation(EventStartTime timing=TIMED) : JfrEvent<EventVirtualizationInformation>(timing) {}

  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_name);
  }

  using JfrEvent<EventVirtualizationInformation>::commit; // else commit() is hidden by overloaded versions in this class

  EventVirtualizationInformation(
    const char* name) : JfrEvent<EventVirtualizationInformation>(TIMED) {
    if (should_commit()) {
      set_name(name);
    }
  }

  void commit(const char* name) {
    if (should_commit()) {
      set_name(name);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* name) {
    EventVirtualizationInformation me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_name(name);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: name");
  }
#endif
};

class EventInitialSystemProperty : public JfrEvent<EventInitialSystemProperty>
{
 private:
  const char* _key;
  const char* _value;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrInitialSystemPropertyEvent;

  EventInitialSystemProperty(EventStartTime timing=TIMED) : JfrEvent<EventInitialSystemProperty>(timing) {}

  void set_key(const char* new_value) {
    this->_key = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_value(const char* new_value) {
    this->_value = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_key);
    w.write(_value);
  }

  using JfrEvent<EventInitialSystemProperty>::commit; // else commit() is hidden by overloaded versions in this class

  EventInitialSystemProperty(
    const char* key,
    const char* value) : JfrEvent<EventInitialSystemProperty>(TIMED) {
    if (should_commit()) {
      set_key(key);
      set_value(value);
    }
  }

  void commit(const char* key,
              const char* value) {
    if (should_commit()) {
      set_key(key);
      set_value(value);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* key,
                     const char* value) {
    EventInitialSystemProperty me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_key(key);
      me.set_value(value);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: key");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: value");
  }
#endif
};

class EventInitialEnvironmentVariable : public JfrEvent<EventInitialEnvironmentVariable>
{
 private:
  const char* _key;
  const char* _value;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrInitialEnvironmentVariableEvent;

  EventInitialEnvironmentVariable(EventStartTime timing=TIMED) : JfrEvent<EventInitialEnvironmentVariable>(timing) {}

  void set_key(const char* new_value) {
    this->_key = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_value(const char* new_value) {
    this->_value = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_key);
    w.write(_value);
  }

  using JfrEvent<EventInitialEnvironmentVariable>::commit; // else commit() is hidden by overloaded versions in this class

  EventInitialEnvironmentVariable(
    const char* key,
    const char* value) : JfrEvent<EventInitialEnvironmentVariable>(TIMED) {
    if (should_commit()) {
      set_key(key);
      set_value(value);
    }
  }

  void commit(const char* key,
              const char* value) {
    if (should_commit()) {
      set_key(key);
      set_value(value);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* key,
                     const char* value) {
    EventInitialEnvironmentVariable me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_key(key);
      me.set_value(value);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: key");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: value");
  }
#endif
};

class EventSystemProcess : public JfrEvent<EventSystemProcess>
{
 private:
  const char* _pid;
  const char* _commandLine;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrSystemProcessEvent;

  EventSystemProcess(EventStartTime timing=TIMED) : JfrEvent<EventSystemProcess>(timing) {}

  void set_pid(const char* new_value) {
    this->_pid = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_commandLine(const char* new_value) {
    this->_commandLine = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_pid);
    w.write(_commandLine);
  }

  using JfrEvent<EventSystemProcess>::commit; // else commit() is hidden by overloaded versions in this class

  EventSystemProcess(
    const char* pid,
    const char* commandLine) : JfrEvent<EventSystemProcess>(TIMED) {
    if (should_commit()) {
      set_pid(pid);
      set_commandLine(commandLine);
    }
  }

  void commit(const char* pid,
              const char* commandLine) {
    if (should_commit()) {
      set_pid(pid);
      set_commandLine(commandLine);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* pid,
                     const char* commandLine) {
    EventSystemProcess me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_pid(pid);
      me.set_commandLine(commandLine);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: pid");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: commandLine");
  }
#endif
};

class EventCPUInformation : public JfrEvent<EventCPUInformation>
{
 private:
  const char* _cpu;
  const char* _description;
  unsigned _sockets;
  unsigned _cores;
  unsigned _hwThreads;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrCPUInformationEvent;

  EventCPUInformation(EventStartTime timing=TIMED) : JfrEvent<EventCPUInformation>(timing) {}

  void set_cpu(const char* new_value) {
    this->_cpu = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_description(const char* new_value) {
    this->_description = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_sockets(unsigned new_value) {
    this->_sockets = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_cores(unsigned new_value) {
    this->_cores = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_hwThreads(unsigned new_value) {
    this->_hwThreads = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_cpu);
    w.write(_description);
    w.write(_sockets);
    w.write(_cores);
    w.write(_hwThreads);
  }

  using JfrEvent<EventCPUInformation>::commit; // else commit() is hidden by overloaded versions in this class

  EventCPUInformation(
    const char* cpu,
    const char* description,
    unsigned sockets,
    unsigned cores,
    unsigned hwThreads) : JfrEvent<EventCPUInformation>(TIMED) {
    if (should_commit()) {
      set_cpu(cpu);
      set_description(description);
      set_sockets(sockets);
      set_cores(cores);
      set_hwThreads(hwThreads);
    }
  }

  void commit(const char* cpu,
              const char* description,
              unsigned sockets,
              unsigned cores,
              unsigned hwThreads) {
    if (should_commit()) {
      set_cpu(cpu);
      set_description(description);
      set_sockets(sockets);
      set_cores(cores);
      set_hwThreads(hwThreads);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* cpu,
                     const char* description,
                     unsigned sockets,
                     unsigned cores,
                     unsigned hwThreads) {
    EventCPUInformation me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_cpu(cpu);
      me.set_description(description);
      me.set_sockets(sockets);
      me.set_cores(cores);
      me.set_hwThreads(hwThreads);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: cpu");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: description");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: sockets");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: cores");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: hwThreads");
  }
#endif
};

class EventCPUTimeStampCounter : public JfrEvent<EventCPUTimeStampCounter>
{
 private:
  bool _fastTimeEnabled;
  bool _fastTimeAutoEnabled;
  s8 _osFrequency;
  s8 _fastTimeFrequency;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrCPUTimeStampCounterEvent;

  EventCPUTimeStampCounter(EventStartTime timing=TIMED) : JfrEvent<EventCPUTimeStampCounter>(timing) {}

  void set_fastTimeEnabled(bool new_value) {
    this->_fastTimeEnabled = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_fastTimeAutoEnabled(bool new_value) {
    this->_fastTimeAutoEnabled = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_osFrequency(s8 new_value) {
    this->_osFrequency = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_fastTimeFrequency(s8 new_value) {
    this->_fastTimeFrequency = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_fastTimeEnabled);
    w.write(_fastTimeAutoEnabled);
    w.write(_osFrequency);
    w.write(_fastTimeFrequency);
  }

  using JfrEvent<EventCPUTimeStampCounter>::commit; // else commit() is hidden by overloaded versions in this class

  EventCPUTimeStampCounter(
    bool fastTimeEnabled,
    bool fastTimeAutoEnabled,
    s8 osFrequency,
    s8 fastTimeFrequency) : JfrEvent<EventCPUTimeStampCounter>(TIMED) {
    if (should_commit()) {
      set_fastTimeEnabled(fastTimeEnabled);
      set_fastTimeAutoEnabled(fastTimeAutoEnabled);
      set_osFrequency(osFrequency);
      set_fastTimeFrequency(fastTimeFrequency);
    }
  }

  void commit(bool fastTimeEnabled,
              bool fastTimeAutoEnabled,
              s8 osFrequency,
              s8 fastTimeFrequency) {
    if (should_commit()) {
      set_fastTimeEnabled(fastTimeEnabled);
      set_fastTimeAutoEnabled(fastTimeAutoEnabled);
      set_osFrequency(osFrequency);
      set_fastTimeFrequency(fastTimeFrequency);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     bool fastTimeEnabled,
                     bool fastTimeAutoEnabled,
                     s8 osFrequency,
                     s8 fastTimeFrequency) {
    EventCPUTimeStampCounter me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_fastTimeEnabled(fastTimeEnabled);
      me.set_fastTimeAutoEnabled(fastTimeAutoEnabled);
      me.set_osFrequency(osFrequency);
      me.set_fastTimeFrequency(fastTimeFrequency);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: fastTimeEnabled");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: fastTimeAutoEnabled");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: osFrequency");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: fastTimeFrequency");
  }
#endif
};

class EventCPULoad : public JfrEvent<EventCPULoad>
{
 private:
  float _jvmUser;
  float _jvmSystem;
  float _machineTotal;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrCPULoadEvent;

  EventCPULoad(EventStartTime timing=TIMED) : JfrEvent<EventCPULoad>(timing) {}

  void set_jvmUser(float new_value) {
    this->_jvmUser = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_jvmSystem(float new_value) {
    this->_jvmSystem = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_machineTotal(float new_value) {
    this->_machineTotal = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_jvmUser);
    w.write(_jvmSystem);
    w.write(_machineTotal);
  }

  using JfrEvent<EventCPULoad>::commit; // else commit() is hidden by overloaded versions in this class

  EventCPULoad(
    float jvmUser,
    float jvmSystem,
    float machineTotal) : JfrEvent<EventCPULoad>(TIMED) {
    if (should_commit()) {
      set_jvmUser(jvmUser);
      set_jvmSystem(jvmSystem);
      set_machineTotal(machineTotal);
    }
  }

  void commit(float jvmUser,
              float jvmSystem,
              float machineTotal) {
    if (should_commit()) {
      set_jvmUser(jvmUser);
      set_jvmSystem(jvmSystem);
      set_machineTotal(machineTotal);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     float jvmUser,
                     float jvmSystem,
                     float machineTotal) {
    EventCPULoad me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_jvmUser(jvmUser);
      me.set_jvmSystem(jvmSystem);
      me.set_machineTotal(machineTotal);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: jvmUser");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: jvmSystem");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: machineTotal");
  }
#endif
};

class EventThreadCPULoad : public JfrEvent<EventThreadCPULoad>
{
 private:
  float _user;
  float _system;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrThreadCPULoadEvent;

  EventThreadCPULoad(EventStartTime timing=TIMED) : JfrEvent<EventThreadCPULoad>(timing) {}

  void set_user(float new_value) {
    this->_user = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_system(float new_value) {
    this->_system = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_user);
    w.write(_system);
  }

  using JfrEvent<EventThreadCPULoad>::commit; // else commit() is hidden by overloaded versions in this class

  EventThreadCPULoad(
    float user,
    float system) : JfrEvent<EventThreadCPULoad>(TIMED) {
    if (should_commit()) {
      set_user(user);
      set_system(system);
    }
  }

  void commit(float user,
              float system) {
    if (should_commit()) {
      set_user(user);
      set_system(system);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     float user,
                     float system) {
    EventThreadCPULoad me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_user(user);
      me.set_system(system);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: user");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: system");
  }
#endif
};

class EventThreadContextSwitchRate : public JfrEvent<EventThreadContextSwitchRate>
{
 private:
  float _switchRate;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrThreadContextSwitchRateEvent;

  EventThreadContextSwitchRate(EventStartTime timing=TIMED) : JfrEvent<EventThreadContextSwitchRate>(timing) {}

  void set_switchRate(float new_value) {
    this->_switchRate = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_switchRate);
  }

  using JfrEvent<EventThreadContextSwitchRate>::commit; // else commit() is hidden by overloaded versions in this class

  EventThreadContextSwitchRate(
    float switchRate) : JfrEvent<EventThreadContextSwitchRate>(TIMED) {
    if (should_commit()) {
      set_switchRate(switchRate);
    }
  }

  void commit(float switchRate) {
    if (should_commit()) {
      set_switchRate(switchRate);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     float switchRate) {
    EventThreadContextSwitchRate me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_switchRate(switchRate);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: switchRate");
  }
#endif
};

class EventNetworkUtilization : public JfrEvent<EventNetworkUtilization>
{
 private:
  u8 _networkInterface;
  s8 _readRate;
  s8 _writeRate;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrNetworkUtilizationEvent;

  EventNetworkUtilization(EventStartTime timing=TIMED) : JfrEvent<EventNetworkUtilization>(timing) {}

  void set_networkInterface(u8 new_value) {
    this->_networkInterface = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_readRate(s8 new_value) {
    this->_readRate = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_writeRate(s8 new_value) {
    this->_writeRate = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_networkInterface);
    w.write(_readRate);
    w.write(_writeRate);
  }

  using JfrEvent<EventNetworkUtilization>::commit; // else commit() is hidden by overloaded versions in this class

  EventNetworkUtilization(
    u8 networkInterface,
    s8 readRate,
    s8 writeRate) : JfrEvent<EventNetworkUtilization>(TIMED) {
    if (should_commit()) {
      set_networkInterface(networkInterface);
      set_readRate(readRate);
      set_writeRate(writeRate);
    }
  }

  void commit(u8 networkInterface,
              s8 readRate,
              s8 writeRate) {
    if (should_commit()) {
      set_networkInterface(networkInterface);
      set_readRate(readRate);
      set_writeRate(writeRate);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 networkInterface,
                     s8 readRate,
                     s8 writeRate) {
    EventNetworkUtilization me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_networkInterface(networkInterface);
      me.set_readRate(readRate);
      me.set_writeRate(writeRate);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: networkInterface");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: readRate");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: writeRate");
  }
#endif
};

class EventJavaThreadStatistics : public JfrEvent<EventJavaThreadStatistics>
{
 private:
  s8 _activeCount;
  s8 _daemonCount;
  s8 _accumulatedCount;
  s8 _peakCount;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrJavaThreadStatisticsEvent;

  EventJavaThreadStatistics(EventStartTime timing=TIMED) : JfrEvent<EventJavaThreadStatistics>(timing) {}

  void set_activeCount(s8 new_value) {
    this->_activeCount = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_daemonCount(s8 new_value) {
    this->_daemonCount = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_accumulatedCount(s8 new_value) {
    this->_accumulatedCount = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_peakCount(s8 new_value) {
    this->_peakCount = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_activeCount);
    w.write(_daemonCount);
    w.write(_accumulatedCount);
    w.write(_peakCount);
  }

  using JfrEvent<EventJavaThreadStatistics>::commit; // else commit() is hidden by overloaded versions in this class

  EventJavaThreadStatistics(
    s8 activeCount,
    s8 daemonCount,
    s8 accumulatedCount,
    s8 peakCount) : JfrEvent<EventJavaThreadStatistics>(TIMED) {
    if (should_commit()) {
      set_activeCount(activeCount);
      set_daemonCount(daemonCount);
      set_accumulatedCount(accumulatedCount);
      set_peakCount(peakCount);
    }
  }

  void commit(s8 activeCount,
              s8 daemonCount,
              s8 accumulatedCount,
              s8 peakCount) {
    if (should_commit()) {
      set_activeCount(activeCount);
      set_daemonCount(daemonCount);
      set_accumulatedCount(accumulatedCount);
      set_peakCount(peakCount);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     s8 activeCount,
                     s8 daemonCount,
                     s8 accumulatedCount,
                     s8 peakCount) {
    EventJavaThreadStatistics me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_activeCount(activeCount);
      me.set_daemonCount(daemonCount);
      me.set_accumulatedCount(accumulatedCount);
      me.set_peakCount(peakCount);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: activeCount");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: daemonCount");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: accumulatedCount");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: peakCount");
  }
#endif
};

class EventClassLoadingStatistics : public JfrEvent<EventClassLoadingStatistics>
{
 private:
  s8 _loadedClassCount;
  s8 _unloadedClassCount;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrClassLoadingStatisticsEvent;

  EventClassLoadingStatistics(EventStartTime timing=TIMED) : JfrEvent<EventClassLoadingStatistics>(timing) {}

  void set_loadedClassCount(s8 new_value) {
    this->_loadedClassCount = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_unloadedClassCount(s8 new_value) {
    this->_unloadedClassCount = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_loadedClassCount);
    w.write(_unloadedClassCount);
  }

  using JfrEvent<EventClassLoadingStatistics>::commit; // else commit() is hidden by overloaded versions in this class

  EventClassLoadingStatistics(
    s8 loadedClassCount,
    s8 unloadedClassCount) : JfrEvent<EventClassLoadingStatistics>(TIMED) {
    if (should_commit()) {
      set_loadedClassCount(loadedClassCount);
      set_unloadedClassCount(unloadedClassCount);
    }
  }

  void commit(s8 loadedClassCount,
              s8 unloadedClassCount) {
    if (should_commit()) {
      set_loadedClassCount(loadedClassCount);
      set_unloadedClassCount(unloadedClassCount);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     s8 loadedClassCount,
                     s8 unloadedClassCount) {
    EventClassLoadingStatistics me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_loadedClassCount(loadedClassCount);
      me.set_unloadedClassCount(unloadedClassCount);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: loadedClassCount");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: unloadedClassCount");
  }
#endif
};

class EventClassLoaderStatistics : public JfrEvent<EventClassLoaderStatistics>
{
 private:
  const ClassLoaderData* _classLoader;
  const ClassLoaderData* _parentClassLoader;
  u8 _classLoaderData;
  s8 _classCount;
  u8 _chunkSize;
  u8 _blockSize;
  s8 _anonymousClassCount;
  u8 _anonymousChunkSize;
  u8 _anonymousBlockSize;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrClassLoaderStatisticsEvent;

  EventClassLoaderStatistics(EventStartTime timing=TIMED) : JfrEvent<EventClassLoaderStatistics>(timing) {}

  void set_classLoader(const ClassLoaderData* new_value) {
    this->_classLoader = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_parentClassLoader(const ClassLoaderData* new_value) {
    this->_parentClassLoader = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_classLoaderData(u8 new_value) {
    this->_classLoaderData = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_classCount(s8 new_value) {
    this->_classCount = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_chunkSize(u8 new_value) {
    this->_chunkSize = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_blockSize(u8 new_value) {
    this->_blockSize = new_value;
    DEBUG_ONLY(set_field_bit(5));
  }
  void set_anonymousClassCount(s8 new_value) {
    this->_anonymousClassCount = new_value;
    DEBUG_ONLY(set_field_bit(6));
  }
  void set_anonymousChunkSize(u8 new_value) {
    this->_anonymousChunkSize = new_value;
    DEBUG_ONLY(set_field_bit(7));
  }
  void set_anonymousBlockSize(u8 new_value) {
    this->_anonymousBlockSize = new_value;
    DEBUG_ONLY(set_field_bit(8));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_classLoader);
    w.write(_parentClassLoader);
    w.write(_classLoaderData);
    w.write(_classCount);
    w.write(_chunkSize);
    w.write(_blockSize);
    w.write(_anonymousClassCount);
    w.write(_anonymousChunkSize);
    w.write(_anonymousBlockSize);
  }

  using JfrEvent<EventClassLoaderStatistics>::commit; // else commit() is hidden by overloaded versions in this class

  EventClassLoaderStatistics(
    const ClassLoaderData* classLoader,
    const ClassLoaderData* parentClassLoader,
    u8 classLoaderData,
    s8 classCount,
    u8 chunkSize,
    u8 blockSize,
    s8 anonymousClassCount,
    u8 anonymousChunkSize,
    u8 anonymousBlockSize) : JfrEvent<EventClassLoaderStatistics>(TIMED) {
    if (should_commit()) {
      set_classLoader(classLoader);
      set_parentClassLoader(parentClassLoader);
      set_classLoaderData(classLoaderData);
      set_classCount(classCount);
      set_chunkSize(chunkSize);
      set_blockSize(blockSize);
      set_anonymousClassCount(anonymousClassCount);
      set_anonymousChunkSize(anonymousChunkSize);
      set_anonymousBlockSize(anonymousBlockSize);
    }
  }

  void commit(const ClassLoaderData* classLoader,
              const ClassLoaderData* parentClassLoader,
              u8 classLoaderData,
              s8 classCount,
              u8 chunkSize,
              u8 blockSize,
              s8 anonymousClassCount,
              u8 anonymousChunkSize,
              u8 anonymousBlockSize) {
    if (should_commit()) {
      set_classLoader(classLoader);
      set_parentClassLoader(parentClassLoader);
      set_classLoaderData(classLoaderData);
      set_classCount(classCount);
      set_chunkSize(chunkSize);
      set_blockSize(blockSize);
      set_anonymousClassCount(anonymousClassCount);
      set_anonymousChunkSize(anonymousChunkSize);
      set_anonymousBlockSize(anonymousBlockSize);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const ClassLoaderData* classLoader,
                     const ClassLoaderData* parentClassLoader,
                     u8 classLoaderData,
                     s8 classCount,
                     u8 chunkSize,
                     u8 blockSize,
                     s8 anonymousClassCount,
                     u8 anonymousChunkSize,
                     u8 anonymousBlockSize) {
    EventClassLoaderStatistics me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_classLoader(classLoader);
      me.set_parentClassLoader(parentClassLoader);
      me.set_classLoaderData(classLoaderData);
      me.set_classCount(classCount);
      me.set_chunkSize(chunkSize);
      me.set_blockSize(blockSize);
      me.set_anonymousClassCount(anonymousClassCount);
      me.set_anonymousChunkSize(anonymousChunkSize);
      me.set_anonymousBlockSize(anonymousBlockSize);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: classLoader");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: parentClassLoader");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: classLoaderData");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: classCount");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: chunkSize");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: blockSize");
    assert(verify_field_bit(6), "Attempting to write an uninitialized event field: anonymousClassCount");
    assert(verify_field_bit(7), "Attempting to write an uninitialized event field: anonymousChunkSize");
    assert(verify_field_bit(8), "Attempting to write an uninitialized event field: anonymousBlockSize");
  }
#endif
};

class EventSymbolTableStatistics : public JfrEvent<EventSymbolTableStatistics>
{
 private:
  u8 _bucketCount;
  u8 _entryCount;
  u8 _totalFootprint;
  u8 _bucketCountMaximum;
  float _bucketCountAverage;
  float _bucketCountVariance;
  float _bucketCountStandardDeviation;
  float _insertionRate;
  float _removalRate;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrSymbolTableStatisticsEvent;

  EventSymbolTableStatistics(EventStartTime timing=TIMED) : JfrEvent<EventSymbolTableStatistics>(timing) {}

  void set_bucketCount(u8 new_value) {
    this->_bucketCount = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_entryCount(u8 new_value) {
    this->_entryCount = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_totalFootprint(u8 new_value) {
    this->_totalFootprint = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_bucketCountMaximum(u8 new_value) {
    this->_bucketCountMaximum = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_bucketCountAverage(float new_value) {
    this->_bucketCountAverage = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_bucketCountVariance(float new_value) {
    this->_bucketCountVariance = new_value;
    DEBUG_ONLY(set_field_bit(5));
  }
  void set_bucketCountStandardDeviation(float new_value) {
    this->_bucketCountStandardDeviation = new_value;
    DEBUG_ONLY(set_field_bit(6));
  }
  void set_insertionRate(float new_value) {
    this->_insertionRate = new_value;
    DEBUG_ONLY(set_field_bit(7));
  }
  void set_removalRate(float new_value) {
    this->_removalRate = new_value;
    DEBUG_ONLY(set_field_bit(8));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_bucketCount);
    w.write(_entryCount);
    w.write(_totalFootprint);
    w.write(_bucketCountMaximum);
    w.write(_bucketCountAverage);
    w.write(_bucketCountVariance);
    w.write(_bucketCountStandardDeviation);
    w.write(_insertionRate);
    w.write(_removalRate);
  }

  using JfrEvent<EventSymbolTableStatistics>::commit; // else commit() is hidden by overloaded versions in this class

  EventSymbolTableStatistics(
    u8 bucketCount,
    u8 entryCount,
    u8 totalFootprint,
    u8 bucketCountMaximum,
    float bucketCountAverage,
    float bucketCountVariance,
    float bucketCountStandardDeviation,
    float insertionRate,
    float removalRate) : JfrEvent<EventSymbolTableStatistics>(TIMED) {
    if (should_commit()) {
      set_bucketCount(bucketCount);
      set_entryCount(entryCount);
      set_totalFootprint(totalFootprint);
      set_bucketCountMaximum(bucketCountMaximum);
      set_bucketCountAverage(bucketCountAverage);
      set_bucketCountVariance(bucketCountVariance);
      set_bucketCountStandardDeviation(bucketCountStandardDeviation);
      set_insertionRate(insertionRate);
      set_removalRate(removalRate);
    }
  }

  void commit(u8 bucketCount,
              u8 entryCount,
              u8 totalFootprint,
              u8 bucketCountMaximum,
              float bucketCountAverage,
              float bucketCountVariance,
              float bucketCountStandardDeviation,
              float insertionRate,
              float removalRate) {
    if (should_commit()) {
      set_bucketCount(bucketCount);
      set_entryCount(entryCount);
      set_totalFootprint(totalFootprint);
      set_bucketCountMaximum(bucketCountMaximum);
      set_bucketCountAverage(bucketCountAverage);
      set_bucketCountVariance(bucketCountVariance);
      set_bucketCountStandardDeviation(bucketCountStandardDeviation);
      set_insertionRate(insertionRate);
      set_removalRate(removalRate);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 bucketCount,
                     u8 entryCount,
                     u8 totalFootprint,
                     u8 bucketCountMaximum,
                     float bucketCountAverage,
                     float bucketCountVariance,
                     float bucketCountStandardDeviation,
                     float insertionRate,
                     float removalRate) {
    EventSymbolTableStatistics me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_bucketCount(bucketCount);
      me.set_entryCount(entryCount);
      me.set_totalFootprint(totalFootprint);
      me.set_bucketCountMaximum(bucketCountMaximum);
      me.set_bucketCountAverage(bucketCountAverage);
      me.set_bucketCountVariance(bucketCountVariance);
      me.set_bucketCountStandardDeviation(bucketCountStandardDeviation);
      me.set_insertionRate(insertionRate);
      me.set_removalRate(removalRate);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: bucketCount");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: entryCount");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: totalFootprint");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: bucketCountMaximum");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: bucketCountAverage");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: bucketCountVariance");
    assert(verify_field_bit(6), "Attempting to write an uninitialized event field: bucketCountStandardDeviation");
    assert(verify_field_bit(7), "Attempting to write an uninitialized event field: insertionRate");
    assert(verify_field_bit(8), "Attempting to write an uninitialized event field: removalRate");
  }
#endif
};

class EventStringTableStatistics : public JfrEvent<EventStringTableStatistics>
{
 private:
  u8 _bucketCount;
  u8 _entryCount;
  u8 _totalFootprint;
  u8 _bucketCountMaximum;
  float _bucketCountAverage;
  float _bucketCountVariance;
  float _bucketCountStandardDeviation;
  float _insertionRate;
  float _removalRate;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrStringTableStatisticsEvent;

  EventStringTableStatistics(EventStartTime timing=TIMED) : JfrEvent<EventStringTableStatistics>(timing) {}

  void set_bucketCount(u8 new_value) {
    this->_bucketCount = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_entryCount(u8 new_value) {
    this->_entryCount = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_totalFootprint(u8 new_value) {
    this->_totalFootprint = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_bucketCountMaximum(u8 new_value) {
    this->_bucketCountMaximum = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_bucketCountAverage(float new_value) {
    this->_bucketCountAverage = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_bucketCountVariance(float new_value) {
    this->_bucketCountVariance = new_value;
    DEBUG_ONLY(set_field_bit(5));
  }
  void set_bucketCountStandardDeviation(float new_value) {
    this->_bucketCountStandardDeviation = new_value;
    DEBUG_ONLY(set_field_bit(6));
  }
  void set_insertionRate(float new_value) {
    this->_insertionRate = new_value;
    DEBUG_ONLY(set_field_bit(7));
  }
  void set_removalRate(float new_value) {
    this->_removalRate = new_value;
    DEBUG_ONLY(set_field_bit(8));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_bucketCount);
    w.write(_entryCount);
    w.write(_totalFootprint);
    w.write(_bucketCountMaximum);
    w.write(_bucketCountAverage);
    w.write(_bucketCountVariance);
    w.write(_bucketCountStandardDeviation);
    w.write(_insertionRate);
    w.write(_removalRate);
  }

  using JfrEvent<EventStringTableStatistics>::commit; // else commit() is hidden by overloaded versions in this class

  EventStringTableStatistics(
    u8 bucketCount,
    u8 entryCount,
    u8 totalFootprint,
    u8 bucketCountMaximum,
    float bucketCountAverage,
    float bucketCountVariance,
    float bucketCountStandardDeviation,
    float insertionRate,
    float removalRate) : JfrEvent<EventStringTableStatistics>(TIMED) {
    if (should_commit()) {
      set_bucketCount(bucketCount);
      set_entryCount(entryCount);
      set_totalFootprint(totalFootprint);
      set_bucketCountMaximum(bucketCountMaximum);
      set_bucketCountAverage(bucketCountAverage);
      set_bucketCountVariance(bucketCountVariance);
      set_bucketCountStandardDeviation(bucketCountStandardDeviation);
      set_insertionRate(insertionRate);
      set_removalRate(removalRate);
    }
  }

  void commit(u8 bucketCount,
              u8 entryCount,
              u8 totalFootprint,
              u8 bucketCountMaximum,
              float bucketCountAverage,
              float bucketCountVariance,
              float bucketCountStandardDeviation,
              float insertionRate,
              float removalRate) {
    if (should_commit()) {
      set_bucketCount(bucketCount);
      set_entryCount(entryCount);
      set_totalFootprint(totalFootprint);
      set_bucketCountMaximum(bucketCountMaximum);
      set_bucketCountAverage(bucketCountAverage);
      set_bucketCountVariance(bucketCountVariance);
      set_bucketCountStandardDeviation(bucketCountStandardDeviation);
      set_insertionRate(insertionRate);
      set_removalRate(removalRate);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 bucketCount,
                     u8 entryCount,
                     u8 totalFootprint,
                     u8 bucketCountMaximum,
                     float bucketCountAverage,
                     float bucketCountVariance,
                     float bucketCountStandardDeviation,
                     float insertionRate,
                     float removalRate) {
    EventStringTableStatistics me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_bucketCount(bucketCount);
      me.set_entryCount(entryCount);
      me.set_totalFootprint(totalFootprint);
      me.set_bucketCountMaximum(bucketCountMaximum);
      me.set_bucketCountAverage(bucketCountAverage);
      me.set_bucketCountVariance(bucketCountVariance);
      me.set_bucketCountStandardDeviation(bucketCountStandardDeviation);
      me.set_insertionRate(insertionRate);
      me.set_removalRate(removalRate);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: bucketCount");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: entryCount");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: totalFootprint");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: bucketCountMaximum");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: bucketCountAverage");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: bucketCountVariance");
    assert(verify_field_bit(6), "Attempting to write an uninitialized event field: bucketCountStandardDeviation");
    assert(verify_field_bit(7), "Attempting to write an uninitialized event field: insertionRate");
    assert(verify_field_bit(8), "Attempting to write an uninitialized event field: removalRate");
  }
#endif
};

class EventPlaceholderTableStatistics : public JfrEvent<EventPlaceholderTableStatistics>
{
 private:
  u8 _bucketCount;
  u8 _entryCount;
  u8 _totalFootprint;
  u8 _bucketCountMaximum;
  float _bucketCountAverage;
  float _bucketCountVariance;
  float _bucketCountStandardDeviation;
  float _insertionRate;
  float _removalRate;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrPlaceholderTableStatisticsEvent;

  EventPlaceholderTableStatistics(EventStartTime timing=TIMED) : JfrEvent<EventPlaceholderTableStatistics>(timing) {}

  void set_bucketCount(u8 new_value) {
    this->_bucketCount = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_entryCount(u8 new_value) {
    this->_entryCount = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_totalFootprint(u8 new_value) {
    this->_totalFootprint = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_bucketCountMaximum(u8 new_value) {
    this->_bucketCountMaximum = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_bucketCountAverage(float new_value) {
    this->_bucketCountAverage = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_bucketCountVariance(float new_value) {
    this->_bucketCountVariance = new_value;
    DEBUG_ONLY(set_field_bit(5));
  }
  void set_bucketCountStandardDeviation(float new_value) {
    this->_bucketCountStandardDeviation = new_value;
    DEBUG_ONLY(set_field_bit(6));
  }
  void set_insertionRate(float new_value) {
    this->_insertionRate = new_value;
    DEBUG_ONLY(set_field_bit(7));
  }
  void set_removalRate(float new_value) {
    this->_removalRate = new_value;
    DEBUG_ONLY(set_field_bit(8));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_bucketCount);
    w.write(_entryCount);
    w.write(_totalFootprint);
    w.write(_bucketCountMaximum);
    w.write(_bucketCountAverage);
    w.write(_bucketCountVariance);
    w.write(_bucketCountStandardDeviation);
    w.write(_insertionRate);
    w.write(_removalRate);
  }

  using JfrEvent<EventPlaceholderTableStatistics>::commit; // else commit() is hidden by overloaded versions in this class

  EventPlaceholderTableStatistics(
    u8 bucketCount,
    u8 entryCount,
    u8 totalFootprint,
    u8 bucketCountMaximum,
    float bucketCountAverage,
    float bucketCountVariance,
    float bucketCountStandardDeviation,
    float insertionRate,
    float removalRate) : JfrEvent<EventPlaceholderTableStatistics>(TIMED) {
    if (should_commit()) {
      set_bucketCount(bucketCount);
      set_entryCount(entryCount);
      set_totalFootprint(totalFootprint);
      set_bucketCountMaximum(bucketCountMaximum);
      set_bucketCountAverage(bucketCountAverage);
      set_bucketCountVariance(bucketCountVariance);
      set_bucketCountStandardDeviation(bucketCountStandardDeviation);
      set_insertionRate(insertionRate);
      set_removalRate(removalRate);
    }
  }

  void commit(u8 bucketCount,
              u8 entryCount,
              u8 totalFootprint,
              u8 bucketCountMaximum,
              float bucketCountAverage,
              float bucketCountVariance,
              float bucketCountStandardDeviation,
              float insertionRate,
              float removalRate) {
    if (should_commit()) {
      set_bucketCount(bucketCount);
      set_entryCount(entryCount);
      set_totalFootprint(totalFootprint);
      set_bucketCountMaximum(bucketCountMaximum);
      set_bucketCountAverage(bucketCountAverage);
      set_bucketCountVariance(bucketCountVariance);
      set_bucketCountStandardDeviation(bucketCountStandardDeviation);
      set_insertionRate(insertionRate);
      set_removalRate(removalRate);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 bucketCount,
                     u8 entryCount,
                     u8 totalFootprint,
                     u8 bucketCountMaximum,
                     float bucketCountAverage,
                     float bucketCountVariance,
                     float bucketCountStandardDeviation,
                     float insertionRate,
                     float removalRate) {
    EventPlaceholderTableStatistics me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_bucketCount(bucketCount);
      me.set_entryCount(entryCount);
      me.set_totalFootprint(totalFootprint);
      me.set_bucketCountMaximum(bucketCountMaximum);
      me.set_bucketCountAverage(bucketCountAverage);
      me.set_bucketCountVariance(bucketCountVariance);
      me.set_bucketCountStandardDeviation(bucketCountStandardDeviation);
      me.set_insertionRate(insertionRate);
      me.set_removalRate(removalRate);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: bucketCount");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: entryCount");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: totalFootprint");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: bucketCountMaximum");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: bucketCountAverage");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: bucketCountVariance");
    assert(verify_field_bit(6), "Attempting to write an uninitialized event field: bucketCountStandardDeviation");
    assert(verify_field_bit(7), "Attempting to write an uninitialized event field: insertionRate");
    assert(verify_field_bit(8), "Attempting to write an uninitialized event field: removalRate");
  }
#endif
};

class EventLoaderConstraintsTableStatistics : public JfrEvent<EventLoaderConstraintsTableStatistics>
{
 private:
  u8 _bucketCount;
  u8 _entryCount;
  u8 _totalFootprint;
  u8 _bucketCountMaximum;
  float _bucketCountAverage;
  float _bucketCountVariance;
  float _bucketCountStandardDeviation;
  float _insertionRate;
  float _removalRate;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrLoaderConstraintsTableStatisticsEvent;

  EventLoaderConstraintsTableStatistics(EventStartTime timing=TIMED) : JfrEvent<EventLoaderConstraintsTableStatistics>(timing) {}

  void set_bucketCount(u8 new_value) {
    this->_bucketCount = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_entryCount(u8 new_value) {
    this->_entryCount = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_totalFootprint(u8 new_value) {
    this->_totalFootprint = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_bucketCountMaximum(u8 new_value) {
    this->_bucketCountMaximum = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_bucketCountAverage(float new_value) {
    this->_bucketCountAverage = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_bucketCountVariance(float new_value) {
    this->_bucketCountVariance = new_value;
    DEBUG_ONLY(set_field_bit(5));
  }
  void set_bucketCountStandardDeviation(float new_value) {
    this->_bucketCountStandardDeviation = new_value;
    DEBUG_ONLY(set_field_bit(6));
  }
  void set_insertionRate(float new_value) {
    this->_insertionRate = new_value;
    DEBUG_ONLY(set_field_bit(7));
  }
  void set_removalRate(float new_value) {
    this->_removalRate = new_value;
    DEBUG_ONLY(set_field_bit(8));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_bucketCount);
    w.write(_entryCount);
    w.write(_totalFootprint);
    w.write(_bucketCountMaximum);
    w.write(_bucketCountAverage);
    w.write(_bucketCountVariance);
    w.write(_bucketCountStandardDeviation);
    w.write(_insertionRate);
    w.write(_removalRate);
  }

  using JfrEvent<EventLoaderConstraintsTableStatistics>::commit; // else commit() is hidden by overloaded versions in this class

  EventLoaderConstraintsTableStatistics(
    u8 bucketCount,
    u8 entryCount,
    u8 totalFootprint,
    u8 bucketCountMaximum,
    float bucketCountAverage,
    float bucketCountVariance,
    float bucketCountStandardDeviation,
    float insertionRate,
    float removalRate) : JfrEvent<EventLoaderConstraintsTableStatistics>(TIMED) {
    if (should_commit()) {
      set_bucketCount(bucketCount);
      set_entryCount(entryCount);
      set_totalFootprint(totalFootprint);
      set_bucketCountMaximum(bucketCountMaximum);
      set_bucketCountAverage(bucketCountAverage);
      set_bucketCountVariance(bucketCountVariance);
      set_bucketCountStandardDeviation(bucketCountStandardDeviation);
      set_insertionRate(insertionRate);
      set_removalRate(removalRate);
    }
  }

  void commit(u8 bucketCount,
              u8 entryCount,
              u8 totalFootprint,
              u8 bucketCountMaximum,
              float bucketCountAverage,
              float bucketCountVariance,
              float bucketCountStandardDeviation,
              float insertionRate,
              float removalRate) {
    if (should_commit()) {
      set_bucketCount(bucketCount);
      set_entryCount(entryCount);
      set_totalFootprint(totalFootprint);
      set_bucketCountMaximum(bucketCountMaximum);
      set_bucketCountAverage(bucketCountAverage);
      set_bucketCountVariance(bucketCountVariance);
      set_bucketCountStandardDeviation(bucketCountStandardDeviation);
      set_insertionRate(insertionRate);
      set_removalRate(removalRate);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 bucketCount,
                     u8 entryCount,
                     u8 totalFootprint,
                     u8 bucketCountMaximum,
                     float bucketCountAverage,
                     float bucketCountVariance,
                     float bucketCountStandardDeviation,
                     float insertionRate,
                     float removalRate) {
    EventLoaderConstraintsTableStatistics me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_bucketCount(bucketCount);
      me.set_entryCount(entryCount);
      me.set_totalFootprint(totalFootprint);
      me.set_bucketCountMaximum(bucketCountMaximum);
      me.set_bucketCountAverage(bucketCountAverage);
      me.set_bucketCountVariance(bucketCountVariance);
      me.set_bucketCountStandardDeviation(bucketCountStandardDeviation);
      me.set_insertionRate(insertionRate);
      me.set_removalRate(removalRate);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: bucketCount");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: entryCount");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: totalFootprint");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: bucketCountMaximum");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: bucketCountAverage");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: bucketCountVariance");
    assert(verify_field_bit(6), "Attempting to write an uninitialized event field: bucketCountStandardDeviation");
    assert(verify_field_bit(7), "Attempting to write an uninitialized event field: insertionRate");
    assert(verify_field_bit(8), "Attempting to write an uninitialized event field: removalRate");
  }
#endif
};

class EventProtectionDomainCacheTableStatistics : public JfrEvent<EventProtectionDomainCacheTableStatistics>
{
 private:
  u8 _bucketCount;
  u8 _entryCount;
  u8 _totalFootprint;
  u8 _bucketCountMaximum;
  float _bucketCountAverage;
  float _bucketCountVariance;
  float _bucketCountStandardDeviation;
  float _insertionRate;
  float _removalRate;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrProtectionDomainCacheTableStatisticsEvent;

  EventProtectionDomainCacheTableStatistics(EventStartTime timing=TIMED) : JfrEvent<EventProtectionDomainCacheTableStatistics>(timing) {}

  void set_bucketCount(u8 new_value) {
    this->_bucketCount = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_entryCount(u8 new_value) {
    this->_entryCount = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_totalFootprint(u8 new_value) {
    this->_totalFootprint = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_bucketCountMaximum(u8 new_value) {
    this->_bucketCountMaximum = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_bucketCountAverage(float new_value) {
    this->_bucketCountAverage = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_bucketCountVariance(float new_value) {
    this->_bucketCountVariance = new_value;
    DEBUG_ONLY(set_field_bit(5));
  }
  void set_bucketCountStandardDeviation(float new_value) {
    this->_bucketCountStandardDeviation = new_value;
    DEBUG_ONLY(set_field_bit(6));
  }
  void set_insertionRate(float new_value) {
    this->_insertionRate = new_value;
    DEBUG_ONLY(set_field_bit(7));
  }
  void set_removalRate(float new_value) {
    this->_removalRate = new_value;
    DEBUG_ONLY(set_field_bit(8));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_bucketCount);
    w.write(_entryCount);
    w.write(_totalFootprint);
    w.write(_bucketCountMaximum);
    w.write(_bucketCountAverage);
    w.write(_bucketCountVariance);
    w.write(_bucketCountStandardDeviation);
    w.write(_insertionRate);
    w.write(_removalRate);
  }

  using JfrEvent<EventProtectionDomainCacheTableStatistics>::commit; // else commit() is hidden by overloaded versions in this class

  EventProtectionDomainCacheTableStatistics(
    u8 bucketCount,
    u8 entryCount,
    u8 totalFootprint,
    u8 bucketCountMaximum,
    float bucketCountAverage,
    float bucketCountVariance,
    float bucketCountStandardDeviation,
    float insertionRate,
    float removalRate) : JfrEvent<EventProtectionDomainCacheTableStatistics>(TIMED) {
    if (should_commit()) {
      set_bucketCount(bucketCount);
      set_entryCount(entryCount);
      set_totalFootprint(totalFootprint);
      set_bucketCountMaximum(bucketCountMaximum);
      set_bucketCountAverage(bucketCountAverage);
      set_bucketCountVariance(bucketCountVariance);
      set_bucketCountStandardDeviation(bucketCountStandardDeviation);
      set_insertionRate(insertionRate);
      set_removalRate(removalRate);
    }
  }

  void commit(u8 bucketCount,
              u8 entryCount,
              u8 totalFootprint,
              u8 bucketCountMaximum,
              float bucketCountAverage,
              float bucketCountVariance,
              float bucketCountStandardDeviation,
              float insertionRate,
              float removalRate) {
    if (should_commit()) {
      set_bucketCount(bucketCount);
      set_entryCount(entryCount);
      set_totalFootprint(totalFootprint);
      set_bucketCountMaximum(bucketCountMaximum);
      set_bucketCountAverage(bucketCountAverage);
      set_bucketCountVariance(bucketCountVariance);
      set_bucketCountStandardDeviation(bucketCountStandardDeviation);
      set_insertionRate(insertionRate);
      set_removalRate(removalRate);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 bucketCount,
                     u8 entryCount,
                     u8 totalFootprint,
                     u8 bucketCountMaximum,
                     float bucketCountAverage,
                     float bucketCountVariance,
                     float bucketCountStandardDeviation,
                     float insertionRate,
                     float removalRate) {
    EventProtectionDomainCacheTableStatistics me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_bucketCount(bucketCount);
      me.set_entryCount(entryCount);
      me.set_totalFootprint(totalFootprint);
      me.set_bucketCountMaximum(bucketCountMaximum);
      me.set_bucketCountAverage(bucketCountAverage);
      me.set_bucketCountVariance(bucketCountVariance);
      me.set_bucketCountStandardDeviation(bucketCountStandardDeviation);
      me.set_insertionRate(insertionRate);
      me.set_removalRate(removalRate);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: bucketCount");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: entryCount");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: totalFootprint");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: bucketCountMaximum");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: bucketCountAverage");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: bucketCountVariance");
    assert(verify_field_bit(6), "Attempting to write an uninitialized event field: bucketCountStandardDeviation");
    assert(verify_field_bit(7), "Attempting to write an uninitialized event field: insertionRate");
    assert(verify_field_bit(8), "Attempting to write an uninitialized event field: removalRate");
  }
#endif
};

class EventThreadAllocationStatistics : public JfrEvent<EventThreadAllocationStatistics>
{
 private:
  u8 _allocated;
  u8 _thread;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrThreadAllocationStatisticsEvent;

  EventThreadAllocationStatistics(EventStartTime timing=TIMED) : JfrEvent<EventThreadAllocationStatistics>(timing) {}

  void set_allocated(u8 new_value) {
    this->_allocated = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_thread(u8 new_value) {
    this->_thread = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_allocated);
    w.write(_thread);
  }

  using JfrEvent<EventThreadAllocationStatistics>::commit; // else commit() is hidden by overloaded versions in this class

  EventThreadAllocationStatistics(
    u8 allocated,
    u8 thread) : JfrEvent<EventThreadAllocationStatistics>(TIMED) {
    if (should_commit()) {
      set_allocated(allocated);
      set_thread(thread);
    }
  }

  void commit(u8 allocated,
              u8 thread) {
    if (should_commit()) {
      set_allocated(allocated);
      set_thread(thread);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 allocated,
                     u8 thread) {
    EventThreadAllocationStatistics me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_allocated(allocated);
      me.set_thread(thread);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: allocated");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: thread");
  }
#endif
};

class EventPhysicalMemory : public JfrEvent<EventPhysicalMemory>
{
 private:
  u8 _totalSize;
  u8 _usedSize;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrPhysicalMemoryEvent;

  EventPhysicalMemory(EventStartTime timing=TIMED) : JfrEvent<EventPhysicalMemory>(timing) {}

  void set_totalSize(u8 new_value) {
    this->_totalSize = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_usedSize(u8 new_value) {
    this->_usedSize = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_totalSize);
    w.write(_usedSize);
  }

  using JfrEvent<EventPhysicalMemory>::commit; // else commit() is hidden by overloaded versions in this class

  EventPhysicalMemory(
    u8 totalSize,
    u8 usedSize) : JfrEvent<EventPhysicalMemory>(TIMED) {
    if (should_commit()) {
      set_totalSize(totalSize);
      set_usedSize(usedSize);
    }
  }

  void commit(u8 totalSize,
              u8 usedSize) {
    if (should_commit()) {
      set_totalSize(totalSize);
      set_usedSize(usedSize);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 totalSize,
                     u8 usedSize) {
    EventPhysicalMemory me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_totalSize(totalSize);
      me.set_usedSize(usedSize);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: totalSize");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: usedSize");
  }
#endif
};

class EventExecutionSample : public JfrEvent<EventExecutionSample>
{
 private:
  u8 _sampledThread;
  u8 _stackTrace;
  u8 _state;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrExecutionSampleEvent;

  EventExecutionSample(EventStartTime timing=TIMED) : JfrEvent<EventExecutionSample>(timing) {}

  void set_sampledThread(u8 new_value) {
    this->_sampledThread = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_stackTrace(u8 new_value) {
    this->_stackTrace = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_state(u8 new_value) {
    this->_state = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_sampledThread);
    w.write(_stackTrace);
    w.write(_state);
  }

  using JfrEvent<EventExecutionSample>::commit; // else commit() is hidden by overloaded versions in this class

  EventExecutionSample(
    u8 sampledThread,
    u8 stackTrace,
    u8 state) : JfrEvent<EventExecutionSample>(TIMED) {
    if (should_commit()) {
      set_sampledThread(sampledThread);
      set_stackTrace(stackTrace);
      set_state(state);
    }
  }

  void commit(u8 sampledThread,
              u8 stackTrace,
              u8 state) {
    if (should_commit()) {
      set_sampledThread(sampledThread);
      set_stackTrace(stackTrace);
      set_state(state);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 sampledThread,
                     u8 stackTrace,
                     u8 state) {
    EventExecutionSample me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_sampledThread(sampledThread);
      me.set_stackTrace(stackTrace);
      me.set_state(state);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: sampledThread");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: stackTrace");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: state");
  }
#endif
};

class EventNativeMethodSample : public JfrEvent<EventNativeMethodSample>
{
 private:
  u8 _sampledThread;
  u8 _stackTrace;
  u8 _state;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrNativeMethodSampleEvent;

  EventNativeMethodSample(EventStartTime timing=TIMED) : JfrEvent<EventNativeMethodSample>(timing) {}

  void set_sampledThread(u8 new_value) {
    this->_sampledThread = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_stackTrace(u8 new_value) {
    this->_stackTrace = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_state(u8 new_value) {
    this->_state = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_sampledThread);
    w.write(_stackTrace);
    w.write(_state);
  }

  using JfrEvent<EventNativeMethodSample>::commit; // else commit() is hidden by overloaded versions in this class

  EventNativeMethodSample(
    u8 sampledThread,
    u8 stackTrace,
    u8 state) : JfrEvent<EventNativeMethodSample>(TIMED) {
    if (should_commit()) {
      set_sampledThread(sampledThread);
      set_stackTrace(stackTrace);
      set_state(state);
    }
  }

  void commit(u8 sampledThread,
              u8 stackTrace,
              u8 state) {
    if (should_commit()) {
      set_sampledThread(sampledThread);
      set_stackTrace(stackTrace);
      set_state(state);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 sampledThread,
                     u8 stackTrace,
                     u8 state) {
    EventNativeMethodSample me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_sampledThread(sampledThread);
      me.set_stackTrace(stackTrace);
      me.set_state(state);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: sampledThread");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: stackTrace");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: state");
  }
#endif
};

class EventThreadDump : public JfrEvent<EventThreadDump>
{
 private:
  const char* _result;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrThreadDumpEvent;

  EventThreadDump(EventStartTime timing=TIMED) : JfrEvent<EventThreadDump>(timing) {}

  void set_result(const char* new_value) {
    this->_result = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_result);
  }

  using JfrEvent<EventThreadDump>::commit; // else commit() is hidden by overloaded versions in this class

  EventThreadDump(
    const char* result) : JfrEvent<EventThreadDump>(TIMED) {
    if (should_commit()) {
      set_result(result);
    }
  }

  void commit(const char* result) {
    if (should_commit()) {
      set_result(result);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* result) {
    EventThreadDump me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_result(result);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: result");
  }
#endif
};

class EventNativeLibrary : public JfrEvent<EventNativeLibrary>
{
 private:
  const char* _name;
  u8 _baseAddress;
  u8 _topAddress;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrNativeLibraryEvent;

  EventNativeLibrary(EventStartTime timing=TIMED) : JfrEvent<EventNativeLibrary>(timing) {}

  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_baseAddress(u8 new_value) {
    this->_baseAddress = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_topAddress(u8 new_value) {
    this->_topAddress = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_name);
    w.write(_baseAddress);
    w.write(_topAddress);
  }

  using JfrEvent<EventNativeLibrary>::commit; // else commit() is hidden by overloaded versions in this class

  EventNativeLibrary(
    const char* name,
    u8 baseAddress,
    u8 topAddress) : JfrEvent<EventNativeLibrary>(TIMED) {
    if (should_commit()) {
      set_name(name);
      set_baseAddress(baseAddress);
      set_topAddress(topAddress);
    }
  }

  void commit(const char* name,
              u8 baseAddress,
              u8 topAddress) {
    if (should_commit()) {
      set_name(name);
      set_baseAddress(baseAddress);
      set_topAddress(topAddress);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* name,
                     u8 baseAddress,
                     u8 topAddress) {
    EventNativeLibrary me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_name(name);
      me.set_baseAddress(baseAddress);
      me.set_topAddress(topAddress);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: name");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: baseAddress");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: topAddress");
  }
#endif
};

class EventCompilerStatistics : public JfrEvent<EventCompilerStatistics>
{
 private:
  s4 _compileCount;
  s4 _bailoutCount;
  s4 _invalidatedCount;
  s4 _osrCompileCount;
  s4 _standardCompileCount;
  u8 _osrBytesCompiled;
  u8 _standardBytesCompiled;
  u8 _nmetodsSize;
  u8 _nmetodCodeSize;
  s8 _peakTimeSpent;
  s8 _totalTimeSpent;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrCompilerStatisticsEvent;

  EventCompilerStatistics(EventStartTime timing=TIMED) : JfrEvent<EventCompilerStatistics>(timing) {}

  void set_compileCount(s4 new_value) {
    this->_compileCount = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_bailoutCount(s4 new_value) {
    this->_bailoutCount = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_invalidatedCount(s4 new_value) {
    this->_invalidatedCount = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_osrCompileCount(s4 new_value) {
    this->_osrCompileCount = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_standardCompileCount(s4 new_value) {
    this->_standardCompileCount = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_osrBytesCompiled(u8 new_value) {
    this->_osrBytesCompiled = new_value;
    DEBUG_ONLY(set_field_bit(5));
  }
  void set_standardBytesCompiled(u8 new_value) {
    this->_standardBytesCompiled = new_value;
    DEBUG_ONLY(set_field_bit(6));
  }
  void set_nmetodsSize(u8 new_value) {
    this->_nmetodsSize = new_value;
    DEBUG_ONLY(set_field_bit(7));
  }
  void set_nmetodCodeSize(u8 new_value) {
    this->_nmetodCodeSize = new_value;
    DEBUG_ONLY(set_field_bit(8));
  }
  void set_peakTimeSpent(s8 new_value) {
    this->_peakTimeSpent = new_value;
    DEBUG_ONLY(set_field_bit(9));
  }
  void set_totalTimeSpent(s8 new_value) {
    this->_totalTimeSpent = new_value;
    DEBUG_ONLY(set_field_bit(10));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_compileCount);
    w.write(_bailoutCount);
    w.write(_invalidatedCount);
    w.write(_osrCompileCount);
    w.write(_standardCompileCount);
    w.write(_osrBytesCompiled);
    w.write(_standardBytesCompiled);
    w.write(_nmetodsSize);
    w.write(_nmetodCodeSize);
    w.write(_peakTimeSpent);
    w.write(_totalTimeSpent);
  }

  using JfrEvent<EventCompilerStatistics>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(s4 compileCount,
                     s4 bailoutCount,
                     s4 invalidatedCount,
                     s4 osrCompileCount,
                     s4 standardCompileCount,
                     u8 osrBytesCompiled,
                     u8 standardBytesCompiled,
                     u8 nmetodsSize,
                     u8 nmetodCodeSize,
                     s8 peakTimeSpent,
                     s8 totalTimeSpent) {
    EventCompilerStatistics me(UNTIMED);

    if (me.should_commit()) {
      me.set_compileCount(compileCount);
      me.set_bailoutCount(bailoutCount);
      me.set_invalidatedCount(invalidatedCount);
      me.set_osrCompileCount(osrCompileCount);
      me.set_standardCompileCount(standardCompileCount);
      me.set_osrBytesCompiled(osrBytesCompiled);
      me.set_standardBytesCompiled(standardBytesCompiled);
      me.set_nmetodsSize(nmetodsSize);
      me.set_nmetodCodeSize(nmetodCodeSize);
      me.set_peakTimeSpent(peakTimeSpent);
      me.set_totalTimeSpent(totalTimeSpent);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: compileCount");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: bailoutCount");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: invalidatedCount");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: osrCompileCount");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: standardCompileCount");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: osrBytesCompiled");
    assert(verify_field_bit(6), "Attempting to write an uninitialized event field: standardBytesCompiled");
    assert(verify_field_bit(7), "Attempting to write an uninitialized event field: nmetodsSize");
    assert(verify_field_bit(8), "Attempting to write an uninitialized event field: nmetodCodeSize");
    assert(verify_field_bit(9), "Attempting to write an uninitialized event field: peakTimeSpent");
    assert(verify_field_bit(10), "Attempting to write an uninitialized event field: totalTimeSpent");
  }
#endif
};

class EventCompilerConfiguration : public JfrEvent<EventCompilerConfiguration>
{
 private:
  s4 _threadCount;
  bool _tieredCompilation;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrCompilerConfigurationEvent;

  EventCompilerConfiguration(EventStartTime timing=TIMED) : JfrEvent<EventCompilerConfiguration>(timing) {}

  void set_threadCount(s4 new_value) {
    this->_threadCount = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_tieredCompilation(bool new_value) {
    this->_tieredCompilation = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_threadCount);
    w.write(_tieredCompilation);
  }

  using JfrEvent<EventCompilerConfiguration>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(s4 threadCount,
                     bool tieredCompilation) {
    EventCompilerConfiguration me(UNTIMED);

    if (me.should_commit()) {
      me.set_threadCount(threadCount);
      me.set_tieredCompilation(tieredCompilation);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: threadCount");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: tieredCompilation");
  }
#endif
};

class EventCodeCacheStatistics : public JfrEvent<EventCodeCacheStatistics>
{
 private:
  u8 _codeBlobType;
  u8 _startAddress;
  u8 _reservedTopAddress;
  s4 _entryCount;
  s4 _methodCount;
  s4 _adaptorCount;
  u8 _unallocatedCapacity;
  s4 _fullCount;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrCodeCacheStatisticsEvent;

  EventCodeCacheStatistics(EventStartTime timing=TIMED) : JfrEvent<EventCodeCacheStatistics>(timing) {}

  void set_codeBlobType(u8 new_value) {
    this->_codeBlobType = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_startAddress(u8 new_value) {
    this->_startAddress = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_reservedTopAddress(u8 new_value) {
    this->_reservedTopAddress = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_entryCount(s4 new_value) {
    this->_entryCount = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_methodCount(s4 new_value) {
    this->_methodCount = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_adaptorCount(s4 new_value) {
    this->_adaptorCount = new_value;
    DEBUG_ONLY(set_field_bit(5));
  }
  void set_unallocatedCapacity(u8 new_value) {
    this->_unallocatedCapacity = new_value;
    DEBUG_ONLY(set_field_bit(6));
  }
  void set_fullCount(s4 new_value) {
    this->_fullCount = new_value;
    DEBUG_ONLY(set_field_bit(7));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_codeBlobType);
    w.write(_startAddress);
    w.write(_reservedTopAddress);
    w.write(_entryCount);
    w.write(_methodCount);
    w.write(_adaptorCount);
    w.write(_unallocatedCapacity);
    w.write(_fullCount);
  }

  using JfrEvent<EventCodeCacheStatistics>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(u8 codeBlobType,
                     u8 startAddress,
                     u8 reservedTopAddress,
                     s4 entryCount,
                     s4 methodCount,
                     s4 adaptorCount,
                     u8 unallocatedCapacity,
                     s4 fullCount) {
    EventCodeCacheStatistics me(UNTIMED);

    if (me.should_commit()) {
      me.set_codeBlobType(codeBlobType);
      me.set_startAddress(startAddress);
      me.set_reservedTopAddress(reservedTopAddress);
      me.set_entryCount(entryCount);
      me.set_methodCount(methodCount);
      me.set_adaptorCount(adaptorCount);
      me.set_unallocatedCapacity(unallocatedCapacity);
      me.set_fullCount(fullCount);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: codeBlobType");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: startAddress");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: reservedTopAddress");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: entryCount");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: methodCount");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: adaptorCount");
    assert(verify_field_bit(6), "Attempting to write an uninitialized event field: unallocatedCapacity");
    assert(verify_field_bit(7), "Attempting to write an uninitialized event field: fullCount");
  }
#endif
};

class EventCodeCacheConfiguration : public JfrEvent<EventCodeCacheConfiguration>
{
 private:
  u8 _initialSize;
  u8 _reservedSize;
  u8 _nonNMethodSize;
  u8 _profiledSize;
  u8 _nonProfiledSize;
  u8 _expansionSize;
  u8 _minBlockLength;
  u8 _startAddress;
  u8 _reservedTopAddress;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrCodeCacheConfigurationEvent;

  EventCodeCacheConfiguration(EventStartTime timing=TIMED) : JfrEvent<EventCodeCacheConfiguration>(timing) {}

  void set_initialSize(u8 new_value) {
    this->_initialSize = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_reservedSize(u8 new_value) {
    this->_reservedSize = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_nonNMethodSize(u8 new_value) {
    this->_nonNMethodSize = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_profiledSize(u8 new_value) {
    this->_profiledSize = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_nonProfiledSize(u8 new_value) {
    this->_nonProfiledSize = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_expansionSize(u8 new_value) {
    this->_expansionSize = new_value;
    DEBUG_ONLY(set_field_bit(5));
  }
  void set_minBlockLength(u8 new_value) {
    this->_minBlockLength = new_value;
    DEBUG_ONLY(set_field_bit(6));
  }
  void set_startAddress(u8 new_value) {
    this->_startAddress = new_value;
    DEBUG_ONLY(set_field_bit(7));
  }
  void set_reservedTopAddress(u8 new_value) {
    this->_reservedTopAddress = new_value;
    DEBUG_ONLY(set_field_bit(8));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_initialSize);
    w.write(_reservedSize);
    w.write(_nonNMethodSize);
    w.write(_profiledSize);
    w.write(_nonProfiledSize);
    w.write(_expansionSize);
    w.write(_minBlockLength);
    w.write(_startAddress);
    w.write(_reservedTopAddress);
  }

  using JfrEvent<EventCodeCacheConfiguration>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(u8 initialSize,
                     u8 reservedSize,
                     u8 nonNMethodSize,
                     u8 profiledSize,
                     u8 nonProfiledSize,
                     u8 expansionSize,
                     u8 minBlockLength,
                     u8 startAddress,
                     u8 reservedTopAddress) {
    EventCodeCacheConfiguration me(UNTIMED);

    if (me.should_commit()) {
      me.set_initialSize(initialSize);
      me.set_reservedSize(reservedSize);
      me.set_nonNMethodSize(nonNMethodSize);
      me.set_profiledSize(profiledSize);
      me.set_nonProfiledSize(nonProfiledSize);
      me.set_expansionSize(expansionSize);
      me.set_minBlockLength(minBlockLength);
      me.set_startAddress(startAddress);
      me.set_reservedTopAddress(reservedTopAddress);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: initialSize");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: reservedSize");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: nonNMethodSize");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: profiledSize");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: nonProfiledSize");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: expansionSize");
    assert(verify_field_bit(6), "Attempting to write an uninitialized event field: minBlockLength");
    assert(verify_field_bit(7), "Attempting to write an uninitialized event field: startAddress");
    assert(verify_field_bit(8), "Attempting to write an uninitialized event field: reservedTopAddress");
  }
#endif
};

class EventCodeSweeperStatistics : public JfrEvent<EventCodeSweeperStatistics>
{
 private:
  s4 _sweepCount;
  s4 _methodReclaimedCount;
  Tickspan _totalSweepTime;
  Tickspan _peakFractionTime;
  Tickspan _peakSweepTime;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrCodeSweeperStatisticsEvent;

  EventCodeSweeperStatistics(EventStartTime timing=TIMED) : JfrEvent<EventCodeSweeperStatistics>(timing) {}

  void set_sweepCount(s4 new_value) {
    this->_sweepCount = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_methodReclaimedCount(s4 new_value) {
    this->_methodReclaimedCount = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_totalSweepTime(const Tickspan& new_value) {
    this->_totalSweepTime = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_peakFractionTime(const Tickspan& new_value) {
    this->_peakFractionTime = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_peakSweepTime(const Tickspan& new_value) {
    this->_peakSweepTime = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_sweepCount);
    w.write(_methodReclaimedCount);
    w.write(_totalSweepTime);
    w.write(_peakFractionTime);
    w.write(_peakSweepTime);
  }

  using JfrEvent<EventCodeSweeperStatistics>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(s4 sweepCount,
                     s4 methodReclaimedCount,
                     const Tickspan& totalSweepTime,
                     const Tickspan& peakFractionTime,
                     const Tickspan& peakSweepTime) {
    EventCodeSweeperStatistics me(UNTIMED);

    if (me.should_commit()) {
      me.set_sweepCount(sweepCount);
      me.set_methodReclaimedCount(methodReclaimedCount);
      me.set_totalSweepTime(totalSweepTime);
      me.set_peakFractionTime(peakFractionTime);
      me.set_peakSweepTime(peakSweepTime);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: sweepCount");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: methodReclaimedCount");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: totalSweepTime");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: peakFractionTime");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: peakSweepTime");
  }
#endif
};

class EventCodeSweeperConfiguration : public JfrEvent<EventCodeSweeperConfiguration>
{
 private:
  bool _sweeperEnabled;
  bool _flushingEnabled;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrCodeSweeperConfigurationEvent;

  EventCodeSweeperConfiguration(EventStartTime timing=TIMED) : JfrEvent<EventCodeSweeperConfiguration>(timing) {}

  void set_sweeperEnabled(bool new_value) {
    this->_sweeperEnabled = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_flushingEnabled(bool new_value) {
    this->_flushingEnabled = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_sweeperEnabled);
    w.write(_flushingEnabled);
  }

  using JfrEvent<EventCodeSweeperConfiguration>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(bool sweeperEnabled,
                     bool flushingEnabled) {
    EventCodeSweeperConfiguration me(UNTIMED);

    if (me.should_commit()) {
      me.set_sweeperEnabled(sweeperEnabled);
      me.set_flushingEnabled(flushingEnabled);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: sweeperEnabled");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: flushingEnabled");
  }
#endif
};

class EventIntFlag : public JfrEvent<EventIntFlag>
{
 private:
  const char* _name;
  s4 _value;
  u8 _origin;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrIntFlagEvent;

  EventIntFlag(EventStartTime timing=TIMED) : JfrEvent<EventIntFlag>(timing) {}

  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_value(s4 new_value) {
    this->_value = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_origin(u8 new_value) {
    this->_origin = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_name);
    w.write(_value);
    w.write(_origin);
  }

  using JfrEvent<EventIntFlag>::commit; // else commit() is hidden by overloaded versions in this class

  EventIntFlag(
    const char* name,
    s4 value,
    u8 origin) : JfrEvent<EventIntFlag>(TIMED) {
    if (should_commit()) {
      set_name(name);
      set_value(value);
      set_origin(origin);
    }
  }

  void commit(const char* name,
              s4 value,
              u8 origin) {
    if (should_commit()) {
      set_name(name);
      set_value(value);
      set_origin(origin);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* name,
                     s4 value,
                     u8 origin) {
    EventIntFlag me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_name(name);
      me.set_value(value);
      me.set_origin(origin);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: name");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: value");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: origin");
  }
#endif
};

class EventUnsignedIntFlag : public JfrEvent<EventUnsignedIntFlag>
{
 private:
  const char* _name;
  unsigned _value;
  u8 _origin;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrUnsignedIntFlagEvent;

  EventUnsignedIntFlag(EventStartTime timing=TIMED) : JfrEvent<EventUnsignedIntFlag>(timing) {}

  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_value(unsigned new_value) {
    this->_value = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_origin(u8 new_value) {
    this->_origin = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_name);
    w.write(_value);
    w.write(_origin);
  }

  using JfrEvent<EventUnsignedIntFlag>::commit; // else commit() is hidden by overloaded versions in this class

  EventUnsignedIntFlag(
    const char* name,
    unsigned value,
    u8 origin) : JfrEvent<EventUnsignedIntFlag>(TIMED) {
    if (should_commit()) {
      set_name(name);
      set_value(value);
      set_origin(origin);
    }
  }

  void commit(const char* name,
              unsigned value,
              u8 origin) {
    if (should_commit()) {
      set_name(name);
      set_value(value);
      set_origin(origin);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* name,
                     unsigned value,
                     u8 origin) {
    EventUnsignedIntFlag me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_name(name);
      me.set_value(value);
      me.set_origin(origin);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: name");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: value");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: origin");
  }
#endif
};

class EventLongFlag : public JfrEvent<EventLongFlag>
{
 private:
  const char* _name;
  s8 _value;
  u8 _origin;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrLongFlagEvent;

  EventLongFlag(EventStartTime timing=TIMED) : JfrEvent<EventLongFlag>(timing) {}

  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_value(s8 new_value) {
    this->_value = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_origin(u8 new_value) {
    this->_origin = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_name);
    w.write(_value);
    w.write(_origin);
  }

  using JfrEvent<EventLongFlag>::commit; // else commit() is hidden by overloaded versions in this class

  EventLongFlag(
    const char* name,
    s8 value,
    u8 origin) : JfrEvent<EventLongFlag>(TIMED) {
    if (should_commit()) {
      set_name(name);
      set_value(value);
      set_origin(origin);
    }
  }

  void commit(const char* name,
              s8 value,
              u8 origin) {
    if (should_commit()) {
      set_name(name);
      set_value(value);
      set_origin(origin);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* name,
                     s8 value,
                     u8 origin) {
    EventLongFlag me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_name(name);
      me.set_value(value);
      me.set_origin(origin);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: name");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: value");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: origin");
  }
#endif
};

class EventUnsignedLongFlag : public JfrEvent<EventUnsignedLongFlag>
{
 private:
  const char* _name;
  u8 _value;
  u8 _origin;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrUnsignedLongFlagEvent;

  EventUnsignedLongFlag(EventStartTime timing=TIMED) : JfrEvent<EventUnsignedLongFlag>(timing) {}

  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_value(u8 new_value) {
    this->_value = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_origin(u8 new_value) {
    this->_origin = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_name);
    w.write(_value);
    w.write(_origin);
  }

  using JfrEvent<EventUnsignedLongFlag>::commit; // else commit() is hidden by overloaded versions in this class

  EventUnsignedLongFlag(
    const char* name,
    u8 value,
    u8 origin) : JfrEvent<EventUnsignedLongFlag>(TIMED) {
    if (should_commit()) {
      set_name(name);
      set_value(value);
      set_origin(origin);
    }
  }

  void commit(const char* name,
              u8 value,
              u8 origin) {
    if (should_commit()) {
      set_name(name);
      set_value(value);
      set_origin(origin);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* name,
                     u8 value,
                     u8 origin) {
    EventUnsignedLongFlag me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_name(name);
      me.set_value(value);
      me.set_origin(origin);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: name");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: value");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: origin");
  }
#endif
};

class EventDoubleFlag : public JfrEvent<EventDoubleFlag>
{
 private:
  const char* _name;
  double _value;
  u8 _origin;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrDoubleFlagEvent;

  EventDoubleFlag(EventStartTime timing=TIMED) : JfrEvent<EventDoubleFlag>(timing) {}

  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_value(double new_value) {
    this->_value = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_origin(u8 new_value) {
    this->_origin = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_name);
    w.write(_value);
    w.write(_origin);
  }

  using JfrEvent<EventDoubleFlag>::commit; // else commit() is hidden by overloaded versions in this class

  EventDoubleFlag(
    const char* name,
    double value,
    u8 origin) : JfrEvent<EventDoubleFlag>(TIMED) {
    if (should_commit()) {
      set_name(name);
      set_value(value);
      set_origin(origin);
    }
  }

  void commit(const char* name,
              double value,
              u8 origin) {
    if (should_commit()) {
      set_name(name);
      set_value(value);
      set_origin(origin);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* name,
                     double value,
                     u8 origin) {
    EventDoubleFlag me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_name(name);
      me.set_value(value);
      me.set_origin(origin);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: name");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: value");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: origin");
  }
#endif
};

class EventBooleanFlag : public JfrEvent<EventBooleanFlag>
{
 private:
  const char* _name;
  bool _value;
  u8 _origin;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrBooleanFlagEvent;

  EventBooleanFlag(EventStartTime timing=TIMED) : JfrEvent<EventBooleanFlag>(timing) {}

  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_value(bool new_value) {
    this->_value = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_origin(u8 new_value) {
    this->_origin = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_name);
    w.write(_value);
    w.write(_origin);
  }

  using JfrEvent<EventBooleanFlag>::commit; // else commit() is hidden by overloaded versions in this class

  EventBooleanFlag(
    const char* name,
    bool value,
    u8 origin) : JfrEvent<EventBooleanFlag>(TIMED) {
    if (should_commit()) {
      set_name(name);
      set_value(value);
      set_origin(origin);
    }
  }

  void commit(const char* name,
              bool value,
              u8 origin) {
    if (should_commit()) {
      set_name(name);
      set_value(value);
      set_origin(origin);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* name,
                     bool value,
                     u8 origin) {
    EventBooleanFlag me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_name(name);
      me.set_value(value);
      me.set_origin(origin);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: name");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: value");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: origin");
  }
#endif
};

class EventStringFlag : public JfrEvent<EventStringFlag>
{
 private:
  const char* _name;
  const char* _value;
  u8 _origin;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrStringFlagEvent;

  EventStringFlag(EventStartTime timing=TIMED) : JfrEvent<EventStringFlag>(timing) {}

  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_value(const char* new_value) {
    this->_value = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_origin(u8 new_value) {
    this->_origin = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_name);
    w.write(_value);
    w.write(_origin);
  }

  using JfrEvent<EventStringFlag>::commit; // else commit() is hidden by overloaded versions in this class

  EventStringFlag(
    const char* name,
    const char* value,
    u8 origin) : JfrEvent<EventStringFlag>(TIMED) {
    if (should_commit()) {
      set_name(name);
      set_value(value);
      set_origin(origin);
    }
  }

  void commit(const char* name,
              const char* value,
              u8 origin) {
    if (should_commit()) {
      set_name(name);
      set_value(value);
      set_origin(origin);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* name,
                     const char* value,
                     u8 origin) {
    EventStringFlag me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_name(name);
      me.set_value(value);
      me.set_origin(origin);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: name");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: value");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: origin");
  }
#endif
};

class EventObjectCount : public JfrEvent<EventObjectCount>
{
 private:
  unsigned _gcId;
  const Klass* _objectClass;
  s8 _count;
  u8 _totalSize;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrObjectCountEvent;

  EventObjectCount(EventStartTime timing=TIMED) : JfrEvent<EventObjectCount>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_objectClass(const Klass* new_value) {
    this->_objectClass = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_count(s8 new_value) {
    this->_count = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_totalSize(u8 new_value) {
    this->_totalSize = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_objectClass);
    w.write(_count);
    w.write(_totalSize);
  }

  using JfrEvent<EventObjectCount>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     const Klass* objectClass,
                     s8 count,
                     u8 totalSize) {
    EventObjectCount me(UNTIMED);

    if (me.should_commit()) {
      me.set_gcId(gcId);
      me.set_objectClass(objectClass);
      me.set_count(count);
      me.set_totalSize(totalSize);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: objectClass");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: count");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: totalSize");
  }
#endif
};

class EventG1HeapRegionInformation : public JfrEvent<EventG1HeapRegionInformation>
{
 private:
  unsigned _index;
  u8 _type;
  u8 _start;
  u8 _used;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrG1HeapRegionInformationEvent;

  EventG1HeapRegionInformation(EventStartTime timing=TIMED) : JfrEvent<EventG1HeapRegionInformation>(timing) {}

  void set_index(unsigned new_value) {
    this->_index = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_type(u8 new_value) {
    this->_type = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_start(u8 new_value) {
    this->_start = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_used(u8 new_value) {
    this->_used = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_index);
    w.write(_type);
    w.write(_start);
    w.write(_used);
  }

  using JfrEvent<EventG1HeapRegionInformation>::commit; // else commit() is hidden by overloaded versions in this class

  EventG1HeapRegionInformation(
    unsigned index,
    u8 type,
    u8 start,
    u8 used) : JfrEvent<EventG1HeapRegionInformation>(TIMED) {
    if (should_commit()) {
      set_index(index);
      set_type(type);
      set_start(start);
      set_used(used);
    }
  }

  void commit(unsigned index,
              u8 type,
              u8 start,
              u8 used) {
    if (should_commit()) {
      set_index(index);
      set_type(type);
      set_start(start);
      set_used(used);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned index,
                     u8 type,
                     u8 start,
                     u8 used) {
    EventG1HeapRegionInformation me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_index(index);
      me.set_type(type);
      me.set_start(start);
      me.set_used(used);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: index");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: type");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: start");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: used");
  }
#endif
};

class EventGCConfiguration : public JfrEvent<EventGCConfiguration>
{
 private:
  u8 _youngCollector;
  u8 _oldCollector;
  unsigned _parallelGCThreads;
  unsigned _concurrentGCThreads;
  bool _usesDynamicGCThreads;
  bool _isExplicitGCConcurrent;
  bool _isExplicitGCDisabled;
  s8 _pauseTarget;
  unsigned _gcTimeRatio;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrGCConfigurationEvent;

  EventGCConfiguration(EventStartTime timing=TIMED) : JfrEvent<EventGCConfiguration>(timing) {}

  void set_youngCollector(u8 new_value) {
    this->_youngCollector = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_oldCollector(u8 new_value) {
    this->_oldCollector = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_parallelGCThreads(unsigned new_value) {
    this->_parallelGCThreads = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_concurrentGCThreads(unsigned new_value) {
    this->_concurrentGCThreads = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_usesDynamicGCThreads(bool new_value) {
    this->_usesDynamicGCThreads = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_isExplicitGCConcurrent(bool new_value) {
    this->_isExplicitGCConcurrent = new_value;
    DEBUG_ONLY(set_field_bit(5));
  }
  void set_isExplicitGCDisabled(bool new_value) {
    this->_isExplicitGCDisabled = new_value;
    DEBUG_ONLY(set_field_bit(6));
  }
  void set_pauseTarget(s8 new_value) {
    this->_pauseTarget = new_value;
    DEBUG_ONLY(set_field_bit(7));
  }
  void set_gcTimeRatio(unsigned new_value) {
    this->_gcTimeRatio = new_value;
    DEBUG_ONLY(set_field_bit(8));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_youngCollector);
    w.write(_oldCollector);
    w.write(_parallelGCThreads);
    w.write(_concurrentGCThreads);
    w.write(_usesDynamicGCThreads);
    w.write(_isExplicitGCConcurrent);
    w.write(_isExplicitGCDisabled);
    w.write(_pauseTarget);
    w.write(_gcTimeRatio);
  }

  using JfrEvent<EventGCConfiguration>::commit; // else commit() is hidden by overloaded versions in this class

  EventGCConfiguration(
    u8 youngCollector,
    u8 oldCollector,
    unsigned parallelGCThreads,
    unsigned concurrentGCThreads,
    bool usesDynamicGCThreads,
    bool isExplicitGCConcurrent,
    bool isExplicitGCDisabled,
    s8 pauseTarget,
    unsigned gcTimeRatio) : JfrEvent<EventGCConfiguration>(TIMED) {
    if (should_commit()) {
      set_youngCollector(youngCollector);
      set_oldCollector(oldCollector);
      set_parallelGCThreads(parallelGCThreads);
      set_concurrentGCThreads(concurrentGCThreads);
      set_usesDynamicGCThreads(usesDynamicGCThreads);
      set_isExplicitGCConcurrent(isExplicitGCConcurrent);
      set_isExplicitGCDisabled(isExplicitGCDisabled);
      set_pauseTarget(pauseTarget);
      set_gcTimeRatio(gcTimeRatio);
    }
  }

  void commit(u8 youngCollector,
              u8 oldCollector,
              unsigned parallelGCThreads,
              unsigned concurrentGCThreads,
              bool usesDynamicGCThreads,
              bool isExplicitGCConcurrent,
              bool isExplicitGCDisabled,
              s8 pauseTarget,
              unsigned gcTimeRatio) {
    if (should_commit()) {
      set_youngCollector(youngCollector);
      set_oldCollector(oldCollector);
      set_parallelGCThreads(parallelGCThreads);
      set_concurrentGCThreads(concurrentGCThreads);
      set_usesDynamicGCThreads(usesDynamicGCThreads);
      set_isExplicitGCConcurrent(isExplicitGCConcurrent);
      set_isExplicitGCDisabled(isExplicitGCDisabled);
      set_pauseTarget(pauseTarget);
      set_gcTimeRatio(gcTimeRatio);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 youngCollector,
                     u8 oldCollector,
                     unsigned parallelGCThreads,
                     unsigned concurrentGCThreads,
                     bool usesDynamicGCThreads,
                     bool isExplicitGCConcurrent,
                     bool isExplicitGCDisabled,
                     s8 pauseTarget,
                     unsigned gcTimeRatio) {
    EventGCConfiguration me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_youngCollector(youngCollector);
      me.set_oldCollector(oldCollector);
      me.set_parallelGCThreads(parallelGCThreads);
      me.set_concurrentGCThreads(concurrentGCThreads);
      me.set_usesDynamicGCThreads(usesDynamicGCThreads);
      me.set_isExplicitGCConcurrent(isExplicitGCConcurrent);
      me.set_isExplicitGCDisabled(isExplicitGCDisabled);
      me.set_pauseTarget(pauseTarget);
      me.set_gcTimeRatio(gcTimeRatio);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: youngCollector");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: oldCollector");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: parallelGCThreads");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: concurrentGCThreads");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: usesDynamicGCThreads");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: isExplicitGCConcurrent");
    assert(verify_field_bit(6), "Attempting to write an uninitialized event field: isExplicitGCDisabled");
    assert(verify_field_bit(7), "Attempting to write an uninitialized event field: pauseTarget");
    assert(verify_field_bit(8), "Attempting to write an uninitialized event field: gcTimeRatio");
  }
#endif
};

class EventGCSurvivorConfiguration : public JfrEvent<EventGCSurvivorConfiguration>
{
 private:
  u1 _maxTenuringThreshold;
  u1 _initialTenuringThreshold;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrGCSurvivorConfigurationEvent;

  EventGCSurvivorConfiguration(EventStartTime timing=TIMED) : JfrEvent<EventGCSurvivorConfiguration>(timing) {}

  void set_maxTenuringThreshold(u1 new_value) {
    this->_maxTenuringThreshold = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_initialTenuringThreshold(u1 new_value) {
    this->_initialTenuringThreshold = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_maxTenuringThreshold);
    w.write(_initialTenuringThreshold);
  }

  using JfrEvent<EventGCSurvivorConfiguration>::commit; // else commit() is hidden by overloaded versions in this class

  EventGCSurvivorConfiguration(
    u1 maxTenuringThreshold,
    u1 initialTenuringThreshold) : JfrEvent<EventGCSurvivorConfiguration>(TIMED) {
    if (should_commit()) {
      set_maxTenuringThreshold(maxTenuringThreshold);
      set_initialTenuringThreshold(initialTenuringThreshold);
    }
  }

  void commit(u1 maxTenuringThreshold,
              u1 initialTenuringThreshold) {
    if (should_commit()) {
      set_maxTenuringThreshold(maxTenuringThreshold);
      set_initialTenuringThreshold(initialTenuringThreshold);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u1 maxTenuringThreshold,
                     u1 initialTenuringThreshold) {
    EventGCSurvivorConfiguration me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_maxTenuringThreshold(maxTenuringThreshold);
      me.set_initialTenuringThreshold(initialTenuringThreshold);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: maxTenuringThreshold");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: initialTenuringThreshold");
  }
#endif
};

class EventGCTLABConfiguration : public JfrEvent<EventGCTLABConfiguration>
{
 private:
  bool _usesTLABs;
  u8 _minTLABSize;
  u8 _tlabRefillWasteLimit;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrGCTLABConfigurationEvent;

  EventGCTLABConfiguration(EventStartTime timing=TIMED) : JfrEvent<EventGCTLABConfiguration>(timing) {}

  void set_usesTLABs(bool new_value) {
    this->_usesTLABs = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_minTLABSize(u8 new_value) {
    this->_minTLABSize = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_tlabRefillWasteLimit(u8 new_value) {
    this->_tlabRefillWasteLimit = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_usesTLABs);
    w.write(_minTLABSize);
    w.write(_tlabRefillWasteLimit);
  }

  using JfrEvent<EventGCTLABConfiguration>::commit; // else commit() is hidden by overloaded versions in this class

  EventGCTLABConfiguration(
    bool usesTLABs,
    u8 minTLABSize,
    u8 tlabRefillWasteLimit) : JfrEvent<EventGCTLABConfiguration>(TIMED) {
    if (should_commit()) {
      set_usesTLABs(usesTLABs);
      set_minTLABSize(minTLABSize);
      set_tlabRefillWasteLimit(tlabRefillWasteLimit);
    }
  }

  void commit(bool usesTLABs,
              u8 minTLABSize,
              u8 tlabRefillWasteLimit) {
    if (should_commit()) {
      set_usesTLABs(usesTLABs);
      set_minTLABSize(minTLABSize);
      set_tlabRefillWasteLimit(tlabRefillWasteLimit);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     bool usesTLABs,
                     u8 minTLABSize,
                     u8 tlabRefillWasteLimit) {
    EventGCTLABConfiguration me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_usesTLABs(usesTLABs);
      me.set_minTLABSize(minTLABSize);
      me.set_tlabRefillWasteLimit(tlabRefillWasteLimit);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: usesTLABs");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: minTLABSize");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: tlabRefillWasteLimit");
  }
#endif
};

class EventGCHeapConfiguration : public JfrEvent<EventGCHeapConfiguration>
{
 private:
  u8 _minSize;
  u8 _maxSize;
  u8 _initialSize;
  bool _usesCompressedOops;
  u8 _compressedOopsMode;
  u8 _objectAlignment;
  u1 _heapAddressBits;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrGCHeapConfigurationEvent;

  EventGCHeapConfiguration(EventStartTime timing=TIMED) : JfrEvent<EventGCHeapConfiguration>(timing) {}

  void set_minSize(u8 new_value) {
    this->_minSize = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_maxSize(u8 new_value) {
    this->_maxSize = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_initialSize(u8 new_value) {
    this->_initialSize = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_usesCompressedOops(bool new_value) {
    this->_usesCompressedOops = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_compressedOopsMode(u8 new_value) {
    this->_compressedOopsMode = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_objectAlignment(u8 new_value) {
    this->_objectAlignment = new_value;
    DEBUG_ONLY(set_field_bit(5));
  }
  void set_heapAddressBits(u1 new_value) {
    this->_heapAddressBits = new_value;
    DEBUG_ONLY(set_field_bit(6));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_minSize);
    w.write(_maxSize);
    w.write(_initialSize);
    w.write(_usesCompressedOops);
    w.write(_compressedOopsMode);
    w.write(_objectAlignment);
    w.write(_heapAddressBits);
  }

  using JfrEvent<EventGCHeapConfiguration>::commit; // else commit() is hidden by overloaded versions in this class

  EventGCHeapConfiguration(
    u8 minSize,
    u8 maxSize,
    u8 initialSize,
    bool usesCompressedOops,
    u8 compressedOopsMode,
    u8 objectAlignment,
    u1 heapAddressBits) : JfrEvent<EventGCHeapConfiguration>(TIMED) {
    if (should_commit()) {
      set_minSize(minSize);
      set_maxSize(maxSize);
      set_initialSize(initialSize);
      set_usesCompressedOops(usesCompressedOops);
      set_compressedOopsMode(compressedOopsMode);
      set_objectAlignment(objectAlignment);
      set_heapAddressBits(heapAddressBits);
    }
  }

  void commit(u8 minSize,
              u8 maxSize,
              u8 initialSize,
              bool usesCompressedOops,
              u8 compressedOopsMode,
              u8 objectAlignment,
              u1 heapAddressBits) {
    if (should_commit()) {
      set_minSize(minSize);
      set_maxSize(maxSize);
      set_initialSize(initialSize);
      set_usesCompressedOops(usesCompressedOops);
      set_compressedOopsMode(compressedOopsMode);
      set_objectAlignment(objectAlignment);
      set_heapAddressBits(heapAddressBits);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 minSize,
                     u8 maxSize,
                     u8 initialSize,
                     bool usesCompressedOops,
                     u8 compressedOopsMode,
                     u8 objectAlignment,
                     u1 heapAddressBits) {
    EventGCHeapConfiguration me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_minSize(minSize);
      me.set_maxSize(maxSize);
      me.set_initialSize(initialSize);
      me.set_usesCompressedOops(usesCompressedOops);
      me.set_compressedOopsMode(compressedOopsMode);
      me.set_objectAlignment(objectAlignment);
      me.set_heapAddressBits(heapAddressBits);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: minSize");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: maxSize");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: initialSize");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: usesCompressedOops");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: compressedOopsMode");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: objectAlignment");
    assert(verify_field_bit(6), "Attempting to write an uninitialized event field: heapAddressBits");
  }
#endif
};

class EventYoungGenerationConfiguration : public JfrEvent<EventYoungGenerationConfiguration>
{
 private:
  u8 _minSize;
  u8 _maxSize;
  unsigned _newRatio;

 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = true;
  static const JfrEventId eventId = JfrYoungGenerationConfigurationEvent;

  EventYoungGenerationConfiguration(EventStartTime timing=TIMED) : JfrEvent<EventYoungGenerationConfiguration>(timing) {}

  void set_minSize(u8 new_value) {
    this->_minSize = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_maxSize(u8 new_value) {
    this->_maxSize = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_newRatio(unsigned new_value) {
    this->_newRatio = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_minSize);
    w.write(_maxSize);
    w.write(_newRatio);
  }

  using JfrEvent<EventYoungGenerationConfiguration>::commit; // else commit() is hidden by overloaded versions in this class

  EventYoungGenerationConfiguration(
    u8 minSize,
    u8 maxSize,
    unsigned newRatio) : JfrEvent<EventYoungGenerationConfiguration>(TIMED) {
    if (should_commit()) {
      set_minSize(minSize);
      set_maxSize(maxSize);
      set_newRatio(newRatio);
    }
  }

  void commit(u8 minSize,
              u8 maxSize,
              unsigned newRatio) {
    if (should_commit()) {
      set_minSize(minSize);
      set_maxSize(maxSize);
      set_newRatio(newRatio);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 minSize,
                     u8 maxSize,
                     unsigned newRatio) {
    EventYoungGenerationConfiguration me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_minSize(minSize);
      me.set_maxSize(maxSize);
      me.set_newRatio(newRatio);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: minSize");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: maxSize");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: newRatio");
  }
#endif
};

class EventZPageAllocation : public JfrEvent<EventZPageAllocation>
{
 private:
  u8 _pageSize;
  u8 _usedAfter;
  u8 _freeAfter;
  u8 _inCacheAfter;
  bool _nonBlocking;
  bool _noReserve;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrZPageAllocationEvent;

  EventZPageAllocation(EventStartTime timing=TIMED) : JfrEvent<EventZPageAllocation>(timing) {}

  void set_pageSize(u8 new_value) {
    this->_pageSize = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_usedAfter(u8 new_value) {
    this->_usedAfter = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_freeAfter(u8 new_value) {
    this->_freeAfter = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }
  void set_inCacheAfter(u8 new_value) {
    this->_inCacheAfter = new_value;
    DEBUG_ONLY(set_field_bit(3));
  }
  void set_nonBlocking(bool new_value) {
    this->_nonBlocking = new_value;
    DEBUG_ONLY(set_field_bit(4));
  }
  void set_noReserve(bool new_value) {
    this->_noReserve = new_value;
    DEBUG_ONLY(set_field_bit(5));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_pageSize);
    w.write(_usedAfter);
    w.write(_freeAfter);
    w.write(_inCacheAfter);
    w.write(_nonBlocking);
    w.write(_noReserve);
  }

  using JfrEvent<EventZPageAllocation>::commit; // else commit() is hidden by overloaded versions in this class

  EventZPageAllocation(
    u8 pageSize,
    u8 usedAfter,
    u8 freeAfter,
    u8 inCacheAfter,
    bool nonBlocking,
    bool noReserve) : JfrEvent<EventZPageAllocation>(TIMED) {
    if (should_commit()) {
      set_pageSize(pageSize);
      set_usedAfter(usedAfter);
      set_freeAfter(freeAfter);
      set_inCacheAfter(inCacheAfter);
      set_nonBlocking(nonBlocking);
      set_noReserve(noReserve);
    }
  }

  void commit(u8 pageSize,
              u8 usedAfter,
              u8 freeAfter,
              u8 inCacheAfter,
              bool nonBlocking,
              bool noReserve) {
    if (should_commit()) {
      set_pageSize(pageSize);
      set_usedAfter(usedAfter);
      set_freeAfter(freeAfter);
      set_inCacheAfter(inCacheAfter);
      set_nonBlocking(nonBlocking);
      set_noReserve(noReserve);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 pageSize,
                     u8 usedAfter,
                     u8 freeAfter,
                     u8 inCacheAfter,
                     bool nonBlocking,
                     bool noReserve) {
    EventZPageAllocation me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_pageSize(pageSize);
      me.set_usedAfter(usedAfter);
      me.set_freeAfter(freeAfter);
      me.set_inCacheAfter(inCacheAfter);
      me.set_nonBlocking(nonBlocking);
      me.set_noReserve(noReserve);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: pageSize");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: usedAfter");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: freeAfter");
    assert(verify_field_bit(3), "Attempting to write an uninitialized event field: inCacheAfter");
    assert(verify_field_bit(4), "Attempting to write an uninitialized event field: nonBlocking");
    assert(verify_field_bit(5), "Attempting to write an uninitialized event field: noReserve");
  }
#endif
};

class EventZThreadPhase : public JfrEvent<EventZThreadPhase>
{
 private:
  unsigned _gcId;
  const char* _name;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrZThreadPhaseEvent;

  EventZThreadPhase(EventStartTime timing=TIMED) : JfrEvent<EventZThreadPhase>(timing) {}

  void set_gcId(unsigned new_value) {
    this->_gcId = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_name(const char* new_value) {
    this->_name = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_gcId);
    w.write(_name);
  }

  using JfrEvent<EventZThreadPhase>::commit; // else commit() is hidden by overloaded versions in this class

  EventZThreadPhase(
    unsigned gcId,
    const char* name) : JfrEvent<EventZThreadPhase>(TIMED) {
    if (should_commit()) {
      set_gcId(gcId);
      set_name(name);
    }
  }

  void commit(unsigned gcId,
              const char* name) {
    if (should_commit()) {
      set_gcId(gcId);
      set_name(name);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId,
                     const char* name) {
    EventZThreadPhase me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_gcId(gcId);
      me.set_name(name);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: gcId");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: name");
  }
#endif
};

class EventZStatisticsCounter : public JfrEvent<EventZStatisticsCounter>
{
 private:
  u8 _id;
  u8 _increment;
  u8 _value;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrZStatisticsCounterEvent;

  EventZStatisticsCounter(EventStartTime timing=TIMED) : JfrEvent<EventZStatisticsCounter>(timing) {}

  void set_id(u8 new_value) {
    this->_id = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_increment(u8 new_value) {
    this->_increment = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }
  void set_value(u8 new_value) {
    this->_value = new_value;
    DEBUG_ONLY(set_field_bit(2));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_id);
    w.write(_increment);
    w.write(_value);
  }

  using JfrEvent<EventZStatisticsCounter>::commit; // else commit() is hidden by overloaded versions in this class

  EventZStatisticsCounter(
    u8 id,
    u8 increment,
    u8 value) : JfrEvent<EventZStatisticsCounter>(TIMED) {
    if (should_commit()) {
      set_id(id);
      set_increment(increment);
      set_value(value);
    }
  }

  void commit(u8 id,
              u8 increment,
              u8 value) {
    if (should_commit()) {
      set_id(id);
      set_increment(increment);
      set_value(value);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 id,
                     u8 increment,
                     u8 value) {
    EventZStatisticsCounter me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_id(id);
      me.set_increment(increment);
      me.set_value(value);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: id");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: increment");
    assert(verify_field_bit(2), "Attempting to write an uninitialized event field: value");
  }
#endif
};

class EventZStatisticsSampler : public JfrEvent<EventZStatisticsSampler>
{
 private:
  u8 _id;
  u8 _value;

 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool hasCutoff = false;
  static const bool isRequestable = false;
  static const JfrEventId eventId = JfrZStatisticsSamplerEvent;

  EventZStatisticsSampler(EventStartTime timing=TIMED) : JfrEvent<EventZStatisticsSampler>(timing) {}

  void set_id(u8 new_value) {
    this->_id = new_value;
    DEBUG_ONLY(set_field_bit(0));
  }
  void set_value(u8 new_value) {
    this->_value = new_value;
    DEBUG_ONLY(set_field_bit(1));
  }

  template <typename Writer>
  void writeData(Writer& w) {
    w.write(_id);
    w.write(_value);
  }

  using JfrEvent<EventZStatisticsSampler>::commit; // else commit() is hidden by overloaded versions in this class

  EventZStatisticsSampler(
    u8 id,
    u8 value) : JfrEvent<EventZStatisticsSampler>(TIMED) {
    if (should_commit()) {
      set_id(id);
      set_value(value);
    }
  }

  void commit(u8 id,
              u8 value) {
    if (should_commit()) {
      set_id(id);
      set_value(value);
      commit();
    }
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 id,
                     u8 value) {
    EventZStatisticsSampler me(UNTIMED);

    if (me.should_commit()) {
      me.set_starttime(startTicks);
      me.set_endtime(endTicks);
      me.set_id(id);
      me.set_value(value);
      me.commit();
    }
  }

#ifdef ASSERT
  void verify() const {
    assert(verify_field_bit(0), "Attempting to write an uninitialized event field: id");
    assert(verify_field_bit(1), "Attempting to write an uninitialized event field: value");
  }
#endif
};



#else // !INCLUDE_JFR

template <typename T>
class JfrEvent {
 public:
  JfrEvent() {}
  void set_starttime(const Ticks&) const {}
  void set_endtime(const Ticks&) const {}
  bool should_commit() const { return false; }
  static bool is_enabled() { return false; }
  void commit() {}
};

struct JfrStructVirtualSpace
{
 public:
  void set_start(u8 new_value) { }
  void set_committedEnd(u8 new_value) { }
  void set_committedSize(u8 new_value) { }
  void set_reservedEnd(u8 new_value) { }
  void set_reservedSize(u8 new_value) { }

};


struct JfrStructObjectSpace
{
 public:
  void set_start(u8 new_value) { }
  void set_end(u8 new_value) { }
  void set_used(u8 new_value) { }
  void set_size(u8 new_value) { }

};


struct JfrStructMetaspaceSizes
{
 public:
  void set_committed(u8 new_value) { }
  void set_used(u8 new_value) { }
  void set_reserved(u8 new_value) { }

};


struct JfrStructCopyFailed
{
 public:
  void set_objectCount(u8 new_value) { }
  void set_firstSize(u8 new_value) { }
  void set_smallestSize(u8 new_value) { }
  void set_totalSize(u8 new_value) { }

};


struct JfrStructG1EvacuationStatistics
{
 public:
  void set_gcId(unsigned new_value) { }
  void set_allocated(u8 new_value) { }
  void set_wasted(u8 new_value) { }
  void set_used(u8 new_value) { }
  void set_undoWaste(u8 new_value) { }
  void set_regionEndWaste(u8 new_value) { }
  void set_regionsRefilled(unsigned new_value) { }
  void set_directAllocated(u8 new_value) { }
  void set_failureUsed(u8 new_value) { }
  void set_failureWaste(u8 new_value) { }

};


struct JfrStructCalleeMethod
{
 public:
  void set_type(const char* new_value) { }
  void set_name(const char* new_value) { }
  void set_descriptor(const char* new_value) { }

};


struct JfrStructStackFrame
{
 public:
  void set_method(const Method* new_value) { }
  void set_lineNumber(s4 new_value) { }
  void set_bytecodeIndex(s4 new_value) { }
  void set_type(u8 new_value) { }

};


class EventThreadStart : public JfrEvent<EventThreadStart>
{
 public:
  EventThreadStart(EventStartTime timing=TIMED) {}

  void set_thread(u8 new_value) {
  }

  using JfrEvent<EventThreadStart>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(u8 thread) {
  }
};

class EventThreadEnd : public JfrEvent<EventThreadEnd>
{
 public:
  EventThreadEnd(EventStartTime timing=TIMED) {}

  void set_thread(u8 new_value) {
  }

  using JfrEvent<EventThreadEnd>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(u8 thread) {
  }
};

class EventThreadSleep : public JfrEvent<EventThreadSleep>
{
 public:
  EventThreadSleep(EventStartTime timing=TIMED) {}

  void set_time(s8 new_value) {
  }

  using JfrEvent<EventThreadSleep>::commit; // else commit() is hidden by overloaded versions in this class

  EventThreadSleep(
    s8 time) {
  }

  void commit(s8 time) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     s8 time) {
  }
};

class EventThreadPark : public JfrEvent<EventThreadPark>
{
 public:
  EventThreadPark(EventStartTime timing=TIMED) {}

  void set_parkedClass(const Klass* new_value) {
  }
  void set_timeout(s8 new_value) {
  }
  void set_until(s8 new_value) {
  }
  void set_address(u8 new_value) {
  }

  using JfrEvent<EventThreadPark>::commit; // else commit() is hidden by overloaded versions in this class

  EventThreadPark(
    const Klass* parkedClass,
    s8 timeout,
    s8 until,
    u8 address) {
  }

  void commit(const Klass* parkedClass,
              s8 timeout,
              s8 until,
              u8 address) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const Klass* parkedClass,
                     s8 timeout,
                     s8 until,
                     u8 address) {
  }
};

class EventJavaMonitorEnter : public JfrEvent<EventJavaMonitorEnter>
{
 public:
  EventJavaMonitorEnter(EventStartTime timing=TIMED) {}

  void set_monitorClass(const Klass* new_value) {
  }
  void set_previousOwner(u8 new_value) {
  }
  void set_address(u8 new_value) {
  }

  using JfrEvent<EventJavaMonitorEnter>::commit; // else commit() is hidden by overloaded versions in this class

  EventJavaMonitorEnter(
    const Klass* monitorClass,
    u8 previousOwner,
    u8 address) {
  }

  void commit(const Klass* monitorClass,
              u8 previousOwner,
              u8 address) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const Klass* monitorClass,
                     u8 previousOwner,
                     u8 address) {
  }
};

class EventJavaMonitorWait : public JfrEvent<EventJavaMonitorWait>
{
 public:
  EventJavaMonitorWait(EventStartTime timing=TIMED) {}

  void set_monitorClass(const Klass* new_value) {
  }
  void set_notifier(u8 new_value) {
  }
  void set_timeout(s8 new_value) {
  }
  void set_timedOut(bool new_value) {
  }
  void set_address(u8 new_value) {
  }

  using JfrEvent<EventJavaMonitorWait>::commit; // else commit() is hidden by overloaded versions in this class

  EventJavaMonitorWait(
    const Klass* monitorClass,
    u8 notifier,
    s8 timeout,
    bool timedOut,
    u8 address) {
  }

  void commit(const Klass* monitorClass,
              u8 notifier,
              s8 timeout,
              bool timedOut,
              u8 address) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const Klass* monitorClass,
                     u8 notifier,
                     s8 timeout,
                     bool timedOut,
                     u8 address) {
  }
};

class EventJavaMonitorInflate : public JfrEvent<EventJavaMonitorInflate>
{
 public:
  EventJavaMonitorInflate(EventStartTime timing=TIMED) {}

  void set_monitorClass(const Klass* new_value) {
  }
  void set_address(u8 new_value) {
  }
  void set_cause(u8 new_value) {
  }

  using JfrEvent<EventJavaMonitorInflate>::commit; // else commit() is hidden by overloaded versions in this class

  EventJavaMonitorInflate(
    const Klass* monitorClass,
    u8 address,
    u8 cause) {
  }

  void commit(const Klass* monitorClass,
              u8 address,
              u8 cause) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const Klass* monitorClass,
                     u8 address,
                     u8 cause) {
  }
};

class EventBiasedLockRevocation : public JfrEvent<EventBiasedLockRevocation>
{
 public:
  EventBiasedLockRevocation(EventStartTime timing=TIMED) {}

  void set_lockClass(const Klass* new_value) {
  }
  void set_safepointId(s4 new_value) {
  }
  void set_previousOwner(u8 new_value) {
  }

  using JfrEvent<EventBiasedLockRevocation>::commit; // else commit() is hidden by overloaded versions in this class

  EventBiasedLockRevocation(
    const Klass* lockClass,
    s4 safepointId,
    u8 previousOwner) {
  }

  void commit(const Klass* lockClass,
              s4 safepointId,
              u8 previousOwner) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const Klass* lockClass,
                     s4 safepointId,
                     u8 previousOwner) {
  }
};

class EventBiasedLockSelfRevocation : public JfrEvent<EventBiasedLockSelfRevocation>
{
 public:
  EventBiasedLockSelfRevocation(EventStartTime timing=TIMED) {}

  void set_lockClass(const Klass* new_value) {
  }

  using JfrEvent<EventBiasedLockSelfRevocation>::commit; // else commit() is hidden by overloaded versions in this class

  EventBiasedLockSelfRevocation(
    const Klass* lockClass) {
  }

  void commit(const Klass* lockClass) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const Klass* lockClass) {
  }
};

class EventBiasedLockClassRevocation : public JfrEvent<EventBiasedLockClassRevocation>
{
 public:
  EventBiasedLockClassRevocation(EventStartTime timing=TIMED) {}

  void set_revokedClass(const Klass* new_value) {
  }
  void set_disableBiasing(bool new_value) {
  }
  void set_safepointId(s4 new_value) {
  }

  using JfrEvent<EventBiasedLockClassRevocation>::commit; // else commit() is hidden by overloaded versions in this class

  EventBiasedLockClassRevocation(
    const Klass* revokedClass,
    bool disableBiasing,
    s4 safepointId) {
  }

  void commit(const Klass* revokedClass,
              bool disableBiasing,
              s4 safepointId) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const Klass* revokedClass,
                     bool disableBiasing,
                     s4 safepointId) {
  }
};

class EventReservedStackActivation : public JfrEvent<EventReservedStackActivation>
{
 public:
  EventReservedStackActivation(EventStartTime timing=TIMED) {}

  void set_method(const Method* new_value) {
  }

  using JfrEvent<EventReservedStackActivation>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const Method* method) {
  }
};

class EventClassLoad : public JfrEvent<EventClassLoad>
{
 public:
  EventClassLoad(EventStartTime timing=TIMED) {}

  void set_loadedClass(const Klass* new_value) {
  }
  void set_definingClassLoader(const ClassLoaderData* new_value) {
  }
  void set_initiatingClassLoader(const ClassLoaderData* new_value) {
  }

  using JfrEvent<EventClassLoad>::commit; // else commit() is hidden by overloaded versions in this class

  EventClassLoad(
    const Klass* loadedClass,
    const ClassLoaderData* definingClassLoader,
    const ClassLoaderData* initiatingClassLoader) {
  }

  void commit(const Klass* loadedClass,
              const ClassLoaderData* definingClassLoader,
              const ClassLoaderData* initiatingClassLoader) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const Klass* loadedClass,
                     const ClassLoaderData* definingClassLoader,
                     const ClassLoaderData* initiatingClassLoader) {
  }
};

class EventClassDefine : public JfrEvent<EventClassDefine>
{
 public:
  EventClassDefine(EventStartTime timing=TIMED) {}

  void set_definedClass(const Klass* new_value) {
  }
  void set_definingClassLoader(const ClassLoaderData* new_value) {
  }

  using JfrEvent<EventClassDefine>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const Klass* definedClass,
                     const ClassLoaderData* definingClassLoader) {
  }
};

class EventClassUnload : public JfrEvent<EventClassUnload>
{
 public:
  EventClassUnload(EventStartTime timing=TIMED) {}

  void set_unloadedClass(const Klass* new_value) {
  }
  void set_definingClassLoader(const ClassLoaderData* new_value) {
  }

  using JfrEvent<EventClassUnload>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const Klass* unloadedClass,
                     const ClassLoaderData* definingClassLoader) {
  }
};

class EventIntFlagChanged : public JfrEvent<EventIntFlagChanged>
{
 public:
  EventIntFlagChanged(EventStartTime timing=TIMED) {}

  void set_name(const char* new_value) {
  }
  void set_oldValue(s4 new_value) {
  }
  void set_newValue(s4 new_value) {
  }
  void set_origin(u8 new_value) {
  }

  using JfrEvent<EventIntFlagChanged>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const char* name,
                     s4 oldValue,
                     s4 newValue,
                     u8 origin) {
  }
};

class EventUnsignedIntFlagChanged : public JfrEvent<EventUnsignedIntFlagChanged>
{
 public:
  EventUnsignedIntFlagChanged(EventStartTime timing=TIMED) {}

  void set_name(const char* new_value) {
  }
  void set_oldValue(unsigned new_value) {
  }
  void set_newValue(unsigned new_value) {
  }
  void set_origin(u8 new_value) {
  }

  using JfrEvent<EventUnsignedIntFlagChanged>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const char* name,
                     unsigned oldValue,
                     unsigned newValue,
                     u8 origin) {
  }
};

class EventLongFlagChanged : public JfrEvent<EventLongFlagChanged>
{
 public:
  EventLongFlagChanged(EventStartTime timing=TIMED) {}

  void set_name(const char* new_value) {
  }
  void set_oldValue(s8 new_value) {
  }
  void set_newValue(s8 new_value) {
  }
  void set_origin(u8 new_value) {
  }

  using JfrEvent<EventLongFlagChanged>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const char* name,
                     s8 oldValue,
                     s8 newValue,
                     u8 origin) {
  }
};

class EventUnsignedLongFlagChanged : public JfrEvent<EventUnsignedLongFlagChanged>
{
 public:
  EventUnsignedLongFlagChanged(EventStartTime timing=TIMED) {}

  void set_name(const char* new_value) {
  }
  void set_oldValue(u8 new_value) {
  }
  void set_newValue(u8 new_value) {
  }
  void set_origin(u8 new_value) {
  }

  using JfrEvent<EventUnsignedLongFlagChanged>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const char* name,
                     u8 oldValue,
                     u8 newValue,
                     u8 origin) {
  }
};

class EventDoubleFlagChanged : public JfrEvent<EventDoubleFlagChanged>
{
 public:
  EventDoubleFlagChanged(EventStartTime timing=TIMED) {}

  void set_name(const char* new_value) {
  }
  void set_oldValue(double new_value) {
  }
  void set_newValue(double new_value) {
  }
  void set_origin(u8 new_value) {
  }

  using JfrEvent<EventDoubleFlagChanged>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const char* name,
                     double oldValue,
                     double newValue,
                     u8 origin) {
  }
};

class EventBooleanFlagChanged : public JfrEvent<EventBooleanFlagChanged>
{
 public:
  EventBooleanFlagChanged(EventStartTime timing=TIMED) {}

  void set_name(const char* new_value) {
  }
  void set_oldValue(bool new_value) {
  }
  void set_newValue(bool new_value) {
  }
  void set_origin(u8 new_value) {
  }

  using JfrEvent<EventBooleanFlagChanged>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const char* name,
                     bool oldValue,
                     bool newValue,
                     u8 origin) {
  }
};

class EventStringFlagChanged : public JfrEvent<EventStringFlagChanged>
{
 public:
  EventStringFlagChanged(EventStartTime timing=TIMED) {}

  void set_name(const char* new_value) {
  }
  void set_oldValue(const char* new_value) {
  }
  void set_newValue(const char* new_value) {
  }
  void set_origin(u8 new_value) {
  }

  using JfrEvent<EventStringFlagChanged>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const char* name,
                     const char* oldValue,
                     const char* newValue,
                     u8 origin) {
  }
};

class EventGCHeapSummary : public JfrEvent<EventGCHeapSummary>
{
 public:
  EventGCHeapSummary(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_when(u8 new_value) {
  }
  void set_heapSpace(const JfrStructVirtualSpace& value) {
  }
  void set_heapUsed(u8 new_value) {
  }

  using JfrEvent<EventGCHeapSummary>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     u8 when,
                     const JfrStructVirtualSpace& heapSpace,
                     u8 heapUsed) {
  }
};

class EventMetaspaceSummary : public JfrEvent<EventMetaspaceSummary>
{
 public:
  EventMetaspaceSummary(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_when(u8 new_value) {
  }
  void set_gcThreshold(u8 new_value) {
  }
  void set_metaspace(const JfrStructMetaspaceSizes& value) {
  }
  void set_dataSpace(const JfrStructMetaspaceSizes& value) {
  }
  void set_classSpace(const JfrStructMetaspaceSizes& value) {
  }

  using JfrEvent<EventMetaspaceSummary>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     u8 when,
                     u8 gcThreshold,
                     const JfrStructMetaspaceSizes& metaspace,
                     const JfrStructMetaspaceSizes& dataSpace,
                     const JfrStructMetaspaceSizes& classSpace) {
  }
};

class EventMetaspaceGCThreshold : public JfrEvent<EventMetaspaceGCThreshold>
{
 public:
  EventMetaspaceGCThreshold(EventStartTime timing=TIMED) {}

  void set_oldValue(u8 new_value) {
  }
  void set_newValue(u8 new_value) {
  }
  void set_updater(u8 new_value) {
  }

  using JfrEvent<EventMetaspaceGCThreshold>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(u8 oldValue,
                     u8 newValue,
                     u8 updater) {
  }
};

class EventMetaspaceAllocationFailure : public JfrEvent<EventMetaspaceAllocationFailure>
{
 public:
  EventMetaspaceAllocationFailure(EventStartTime timing=TIMED) {}

  void set_classLoader(const ClassLoaderData* new_value) {
  }
  void set_anonymousClassLoader(bool new_value) {
  }
  void set_size(u8 new_value) {
  }
  void set_metadataType(u8 new_value) {
  }
  void set_metaspaceObjectType(u8 new_value) {
  }

  using JfrEvent<EventMetaspaceAllocationFailure>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const ClassLoaderData* classLoader,
                     bool anonymousClassLoader,
                     u8 size,
                     u8 metadataType,
                     u8 metaspaceObjectType) {
  }
};

class EventMetaspaceOOM : public JfrEvent<EventMetaspaceOOM>
{
 public:
  EventMetaspaceOOM(EventStartTime timing=TIMED) {}

  void set_classLoader(const ClassLoaderData* new_value) {
  }
  void set_anonymousClassLoader(bool new_value) {
  }
  void set_size(u8 new_value) {
  }
  void set_metadataType(u8 new_value) {
  }
  void set_metaspaceObjectType(u8 new_value) {
  }

  using JfrEvent<EventMetaspaceOOM>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const ClassLoaderData* classLoader,
                     bool anonymousClassLoader,
                     u8 size,
                     u8 metadataType,
                     u8 metaspaceObjectType) {
  }
};

class EventMetaspaceChunkFreeListSummary : public JfrEvent<EventMetaspaceChunkFreeListSummary>
{
 public:
  EventMetaspaceChunkFreeListSummary(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_when(u8 new_value) {
  }
  void set_metadataType(u8 new_value) {
  }
  void set_specializedChunks(u8 new_value) {
  }
  void set_specializedChunksTotalSize(u8 new_value) {
  }
  void set_smallChunks(u8 new_value) {
  }
  void set_smallChunksTotalSize(u8 new_value) {
  }
  void set_mediumChunks(u8 new_value) {
  }
  void set_mediumChunksTotalSize(u8 new_value) {
  }
  void set_humongousChunks(u8 new_value) {
  }
  void set_humongousChunksTotalSize(u8 new_value) {
  }

  using JfrEvent<EventMetaspaceChunkFreeListSummary>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     u8 when,
                     u8 metadataType,
                     u8 specializedChunks,
                     u8 specializedChunksTotalSize,
                     u8 smallChunks,
                     u8 smallChunksTotalSize,
                     u8 mediumChunks,
                     u8 mediumChunksTotalSize,
                     u8 humongousChunks,
                     u8 humongousChunksTotalSize) {
  }
};

class EventPSHeapSummary : public JfrEvent<EventPSHeapSummary>
{
 public:
  EventPSHeapSummary(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_when(u8 new_value) {
  }
  void set_oldSpace(const JfrStructVirtualSpace& value) {
  }
  void set_oldObjectSpace(const JfrStructObjectSpace& value) {
  }
  void set_youngSpace(const JfrStructVirtualSpace& value) {
  }
  void set_edenSpace(const JfrStructObjectSpace& value) {
  }
  void set_fromSpace(const JfrStructObjectSpace& value) {
  }
  void set_toSpace(const JfrStructObjectSpace& value) {
  }

  using JfrEvent<EventPSHeapSummary>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     u8 when,
                     const JfrStructVirtualSpace& oldSpace,
                     const JfrStructObjectSpace& oldObjectSpace,
                     const JfrStructVirtualSpace& youngSpace,
                     const JfrStructObjectSpace& edenSpace,
                     const JfrStructObjectSpace& fromSpace,
                     const JfrStructObjectSpace& toSpace) {
  }
};

class EventG1HeapSummary : public JfrEvent<EventG1HeapSummary>
{
 public:
  EventG1HeapSummary(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_when(u8 new_value) {
  }
  void set_edenUsedSize(u8 new_value) {
  }
  void set_edenTotalSize(u8 new_value) {
  }
  void set_survivorUsedSize(u8 new_value) {
  }
  void set_numberOfRegions(unsigned new_value) {
  }

  using JfrEvent<EventG1HeapSummary>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     u8 when,
                     u8 edenUsedSize,
                     u8 edenTotalSize,
                     u8 survivorUsedSize,
                     unsigned numberOfRegions) {
  }
};

class EventGarbageCollection : public JfrEvent<EventGarbageCollection>
{
 public:
  EventGarbageCollection(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_name(u8 new_value) {
  }
  void set_cause(u8 new_value) {
  }
  void set_sumOfPauses(const Tickspan& new_value) {
  }
  void set_longestPause(const Tickspan& new_value) {
  }

  using JfrEvent<EventGarbageCollection>::commit; // else commit() is hidden by overloaded versions in this class

  EventGarbageCollection(
    unsigned gcId,
    u8 name,
    u8 cause,
    const Tickspan& sumOfPauses,
    const Tickspan& longestPause) {
  }

  void commit(unsigned gcId,
              u8 name,
              u8 cause,
              const Tickspan& sumOfPauses,
              const Tickspan& longestPause) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId,
                     u8 name,
                     u8 cause,
                     const Tickspan& sumOfPauses,
                     const Tickspan& longestPause) {
  }
};

class EventParallelOldGarbageCollection : public JfrEvent<EventParallelOldGarbageCollection>
{
 public:
  EventParallelOldGarbageCollection(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_densePrefix(u8 new_value) {
  }

  using JfrEvent<EventParallelOldGarbageCollection>::commit; // else commit() is hidden by overloaded versions in this class

  EventParallelOldGarbageCollection(
    unsigned gcId,
    u8 densePrefix) {
  }

  void commit(unsigned gcId,
              u8 densePrefix) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId,
                     u8 densePrefix) {
  }
};

class EventYoungGarbageCollection : public JfrEvent<EventYoungGarbageCollection>
{
 public:
  EventYoungGarbageCollection(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_tenuringThreshold(unsigned new_value) {
  }

  using JfrEvent<EventYoungGarbageCollection>::commit; // else commit() is hidden by overloaded versions in this class

  EventYoungGarbageCollection(
    unsigned gcId,
    unsigned tenuringThreshold) {
  }

  void commit(unsigned gcId,
              unsigned tenuringThreshold) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId,
                     unsigned tenuringThreshold) {
  }
};

class EventOldGarbageCollection : public JfrEvent<EventOldGarbageCollection>
{
 public:
  EventOldGarbageCollection(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }

  using JfrEvent<EventOldGarbageCollection>::commit; // else commit() is hidden by overloaded versions in this class

  EventOldGarbageCollection(
    unsigned gcId) {
  }

  void commit(unsigned gcId) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId) {
  }
};

class EventG1GarbageCollection : public JfrEvent<EventG1GarbageCollection>
{
 public:
  EventG1GarbageCollection(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_type(u8 new_value) {
  }

  using JfrEvent<EventG1GarbageCollection>::commit; // else commit() is hidden by overloaded versions in this class

  EventG1GarbageCollection(
    unsigned gcId,
    u8 type) {
  }

  void commit(unsigned gcId,
              u8 type) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId,
                     u8 type) {
  }
};

class EventG1MMU : public JfrEvent<EventG1MMU>
{
 public:
  EventG1MMU(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_timeSlice(s8 new_value) {
  }
  void set_gcTime(s8 new_value) {
  }
  void set_pauseTarget(s8 new_value) {
  }

  using JfrEvent<EventG1MMU>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     s8 timeSlice,
                     s8 gcTime,
                     s8 pauseTarget) {
  }
};

class EventEvacuationInformation : public JfrEvent<EventEvacuationInformation>
{
 public:
  EventEvacuationInformation(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_cSetRegions(unsigned new_value) {
  }
  void set_cSetUsedBefore(u8 new_value) {
  }
  void set_cSetUsedAfter(u8 new_value) {
  }
  void set_allocationRegions(unsigned new_value) {
  }
  void set_allocationRegionsUsedBefore(u8 new_value) {
  }
  void set_allocationRegionsUsedAfter(u8 new_value) {
  }
  void set_bytesCopied(u8 new_value) {
  }
  void set_regionsFreed(unsigned new_value) {
  }

  using JfrEvent<EventEvacuationInformation>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     unsigned cSetRegions,
                     u8 cSetUsedBefore,
                     u8 cSetUsedAfter,
                     unsigned allocationRegions,
                     u8 allocationRegionsUsedBefore,
                     u8 allocationRegionsUsedAfter,
                     u8 bytesCopied,
                     unsigned regionsFreed) {
  }
};

class EventGCReferenceStatistics : public JfrEvent<EventGCReferenceStatistics>
{
 public:
  EventGCReferenceStatistics(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_type(u8 new_value) {
  }
  void set_count(u8 new_value) {
  }

  using JfrEvent<EventGCReferenceStatistics>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     u8 type,
                     u8 count) {
  }
};

class EventObjectCountAfterGC : public JfrEvent<EventObjectCountAfterGC>
{
 public:
  EventObjectCountAfterGC(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_objectClass(const Klass* new_value) {
  }
  void set_count(s8 new_value) {
  }
  void set_totalSize(u8 new_value) {
  }

  using JfrEvent<EventObjectCountAfterGC>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     const Klass* objectClass,
                     s8 count,
                     u8 totalSize) {
  }
};

class EventG1EvacuationYoungStatistics : public JfrEvent<EventG1EvacuationYoungStatistics>
{
 public:
  EventG1EvacuationYoungStatistics(EventStartTime timing=TIMED) {}

  void set_statistics(const JfrStructG1EvacuationStatistics& value) {
  }

  using JfrEvent<EventG1EvacuationYoungStatistics>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const JfrStructG1EvacuationStatistics& statistics) {
  }
};

class EventG1EvacuationOldStatistics : public JfrEvent<EventG1EvacuationOldStatistics>
{
 public:
  EventG1EvacuationOldStatistics(EventStartTime timing=TIMED) {}

  void set_statistics(const JfrStructG1EvacuationStatistics& value) {
  }

  using JfrEvent<EventG1EvacuationOldStatistics>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const JfrStructG1EvacuationStatistics& statistics) {
  }
};

class EventG1BasicIHOP : public JfrEvent<EventG1BasicIHOP>
{
 public:
  EventG1BasicIHOP(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_threshold(u8 new_value) {
  }
  void set_thresholdPercentage(float new_value) {
  }
  void set_targetOccupancy(u8 new_value) {
  }
  void set_currentOccupancy(u8 new_value) {
  }
  void set_recentMutatorAllocationSize(u8 new_value) {
  }
  void set_recentMutatorDuration(s8 new_value) {
  }
  void set_recentAllocationRate(double new_value) {
  }
  void set_lastMarkingDuration(s8 new_value) {
  }

  using JfrEvent<EventG1BasicIHOP>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     u8 threshold,
                     float thresholdPercentage,
                     u8 targetOccupancy,
                     u8 currentOccupancy,
                     u8 recentMutatorAllocationSize,
                     s8 recentMutatorDuration,
                     double recentAllocationRate,
                     s8 lastMarkingDuration) {
  }
};

class EventG1AdaptiveIHOP : public JfrEvent<EventG1AdaptiveIHOP>
{
 public:
  EventG1AdaptiveIHOP(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_threshold(u8 new_value) {
  }
  void set_thresholdPercentage(float new_value) {
  }
  void set_ihopTargetOccupancy(u8 new_value) {
  }
  void set_currentOccupancy(u8 new_value) {
  }
  void set_additionalBufferSize(u8 new_value) {
  }
  void set_predictedAllocationRate(double new_value) {
  }
  void set_predictedMarkingDuration(s8 new_value) {
  }
  void set_predictionActive(bool new_value) {
  }

  using JfrEvent<EventG1AdaptiveIHOP>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     u8 threshold,
                     float thresholdPercentage,
                     u8 ihopTargetOccupancy,
                     u8 currentOccupancy,
                     u8 additionalBufferSize,
                     double predictedAllocationRate,
                     s8 predictedMarkingDuration,
                     bool predictionActive) {
  }
};

class EventPromoteObjectInNewPLAB : public JfrEvent<EventPromoteObjectInNewPLAB>
{
 public:
  EventPromoteObjectInNewPLAB(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_objectClass(const Klass* new_value) {
  }
  void set_objectSize(u8 new_value) {
  }
  void set_tenuringAge(unsigned new_value) {
  }
  void set_tenured(bool new_value) {
  }
  void set_plabSize(u8 new_value) {
  }

  using JfrEvent<EventPromoteObjectInNewPLAB>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     const Klass* objectClass,
                     u8 objectSize,
                     unsigned tenuringAge,
                     bool tenured,
                     u8 plabSize) {
  }
};

class EventPromoteObjectOutsidePLAB : public JfrEvent<EventPromoteObjectOutsidePLAB>
{
 public:
  EventPromoteObjectOutsidePLAB(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_objectClass(const Klass* new_value) {
  }
  void set_objectSize(u8 new_value) {
  }
  void set_tenuringAge(unsigned new_value) {
  }
  void set_tenured(bool new_value) {
  }

  using JfrEvent<EventPromoteObjectOutsidePLAB>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     const Klass* objectClass,
                     u8 objectSize,
                     unsigned tenuringAge,
                     bool tenured) {
  }
};

class EventPromotionFailed : public JfrEvent<EventPromotionFailed>
{
 public:
  EventPromotionFailed(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_promotionFailed(const JfrStructCopyFailed& value) {
  }
  void set_thread(u8 new_value) {
  }

  using JfrEvent<EventPromotionFailed>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     const JfrStructCopyFailed& promotionFailed,
                     u8 thread) {
  }
};

class EventEvacuationFailed : public JfrEvent<EventEvacuationFailed>
{
 public:
  EventEvacuationFailed(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_evacuationFailed(const JfrStructCopyFailed& value) {
  }

  using JfrEvent<EventEvacuationFailed>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     const JfrStructCopyFailed& evacuationFailed) {
  }
};

class EventConcurrentModeFailure : public JfrEvent<EventConcurrentModeFailure>
{
 public:
  EventConcurrentModeFailure(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }

  using JfrEvent<EventConcurrentModeFailure>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId) {
  }
};

class EventGCPhasePause : public JfrEvent<EventGCPhasePause>
{
 public:
  EventGCPhasePause(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_name(const char* new_value) {
  }

  using JfrEvent<EventGCPhasePause>::commit; // else commit() is hidden by overloaded versions in this class

  EventGCPhasePause(
    unsigned gcId,
    const char* name) {
  }

  void commit(unsigned gcId,
              const char* name) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId,
                     const char* name) {
  }
};

class EventGCPhasePauseLevel1 : public JfrEvent<EventGCPhasePauseLevel1>
{
 public:
  EventGCPhasePauseLevel1(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_name(const char* new_value) {
  }

  using JfrEvent<EventGCPhasePauseLevel1>::commit; // else commit() is hidden by overloaded versions in this class

  EventGCPhasePauseLevel1(
    unsigned gcId,
    const char* name) {
  }

  void commit(unsigned gcId,
              const char* name) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId,
                     const char* name) {
  }
};

class EventGCPhasePauseLevel2 : public JfrEvent<EventGCPhasePauseLevel2>
{
 public:
  EventGCPhasePauseLevel2(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_name(const char* new_value) {
  }

  using JfrEvent<EventGCPhasePauseLevel2>::commit; // else commit() is hidden by overloaded versions in this class

  EventGCPhasePauseLevel2(
    unsigned gcId,
    const char* name) {
  }

  void commit(unsigned gcId,
              const char* name) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId,
                     const char* name) {
  }
};

class EventGCPhasePauseLevel3 : public JfrEvent<EventGCPhasePauseLevel3>
{
 public:
  EventGCPhasePauseLevel3(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_name(const char* new_value) {
  }

  using JfrEvent<EventGCPhasePauseLevel3>::commit; // else commit() is hidden by overloaded versions in this class

  EventGCPhasePauseLevel3(
    unsigned gcId,
    const char* name) {
  }

  void commit(unsigned gcId,
              const char* name) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId,
                     const char* name) {
  }
};

class EventGCPhasePauseLevel4 : public JfrEvent<EventGCPhasePauseLevel4>
{
 public:
  EventGCPhasePauseLevel4(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_name(const char* new_value) {
  }

  using JfrEvent<EventGCPhasePauseLevel4>::commit; // else commit() is hidden by overloaded versions in this class

  EventGCPhasePauseLevel4(
    unsigned gcId,
    const char* name) {
  }

  void commit(unsigned gcId,
              const char* name) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId,
                     const char* name) {
  }
};

class EventGCPhaseConcurrent : public JfrEvent<EventGCPhaseConcurrent>
{
 public:
  EventGCPhaseConcurrent(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_name(const char* new_value) {
  }

  using JfrEvent<EventGCPhaseConcurrent>::commit; // else commit() is hidden by overloaded versions in this class

  EventGCPhaseConcurrent(
    unsigned gcId,
    const char* name) {
  }

  void commit(unsigned gcId,
              const char* name) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId,
                     const char* name) {
  }
};

class EventAllocationRequiringGC : public JfrEvent<EventAllocationRequiringGC>
{
 public:
  EventAllocationRequiringGC(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_size(u8 new_value) {
  }

  using JfrEvent<EventAllocationRequiringGC>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     u8 size) {
  }
};

class EventTenuringDistribution : public JfrEvent<EventTenuringDistribution>
{
 public:
  EventTenuringDistribution(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_age(unsigned new_value) {
  }
  void set_size(u8 new_value) {
  }

  using JfrEvent<EventTenuringDistribution>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     unsigned age,
                     u8 size) {
  }
};

class EventG1HeapRegionTypeChange : public JfrEvent<EventG1HeapRegionTypeChange>
{
 public:
  EventG1HeapRegionTypeChange(EventStartTime timing=TIMED) {}

  void set_index(unsigned new_value) {
  }
  void set_from(u8 new_value) {
  }
  void set_to(u8 new_value) {
  }
  void set_start(u8 new_value) {
  }
  void set_used(u8 new_value) {
  }

  using JfrEvent<EventG1HeapRegionTypeChange>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned index,
                     u8 from,
                     u8 to,
                     u8 start,
                     u8 used) {
  }
};

class EventCompilation : public JfrEvent<EventCompilation>
{
 public:
  EventCompilation(EventStartTime timing=TIMED) {}

  void set_method(const Method* new_value) {
  }
  void set_compileId(unsigned new_value) {
  }
  void set_compileLevel(u2 new_value) {
  }
  void set_succeded(bool new_value) {
  }
  void set_isOsr(bool new_value) {
  }
  void set_codeSize(u8 new_value) {
  }
  void set_inlinedBytes(u8 new_value) {
  }

  using JfrEvent<EventCompilation>::commit; // else commit() is hidden by overloaded versions in this class

  EventCompilation(
    const Method* method,
    unsigned compileId,
    u2 compileLevel,
    bool succeded,
    bool isOsr,
    u8 codeSize,
    u8 inlinedBytes) {
  }

  void commit(const Method* method,
              unsigned compileId,
              u2 compileLevel,
              bool succeded,
              bool isOsr,
              u8 codeSize,
              u8 inlinedBytes) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const Method* method,
                     unsigned compileId,
                     u2 compileLevel,
                     bool succeded,
                     bool isOsr,
                     u8 codeSize,
                     u8 inlinedBytes) {
  }
};

class EventCompilerPhase : public JfrEvent<EventCompilerPhase>
{
 public:
  EventCompilerPhase(EventStartTime timing=TIMED) {}

  void set_phase(u8 new_value) {
  }
  void set_compileId(unsigned new_value) {
  }
  void set_phaseLevel(u2 new_value) {
  }

  using JfrEvent<EventCompilerPhase>::commit; // else commit() is hidden by overloaded versions in this class

  EventCompilerPhase(
    u8 phase,
    unsigned compileId,
    u2 phaseLevel) {
  }

  void commit(u8 phase,
              unsigned compileId,
              u2 phaseLevel) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 phase,
                     unsigned compileId,
                     u2 phaseLevel) {
  }
};

class EventCompilationFailure : public JfrEvent<EventCompilationFailure>
{
 public:
  EventCompilationFailure(EventStartTime timing=TIMED) {}

  void set_failureMessage(const char* new_value) {
  }
  void set_compileId(unsigned new_value) {
  }

  using JfrEvent<EventCompilationFailure>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const char* failureMessage,
                     unsigned compileId) {
  }
};

class EventCompilerInlining : public JfrEvent<EventCompilerInlining>
{
 public:
  EventCompilerInlining(EventStartTime timing=TIMED) {}

  void set_compileId(unsigned new_value) {
  }
  void set_caller(const Method* new_value) {
  }
  void set_callee(const JfrStructCalleeMethod& value) {
  }
  void set_succeeded(bool new_value) {
  }
  void set_message(const char* new_value) {
  }
  void set_bci(s4 new_value) {
  }

  using JfrEvent<EventCompilerInlining>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned compileId,
                     const Method* caller,
                     const JfrStructCalleeMethod& callee,
                     bool succeeded,
                     const char* message,
                     s4 bci) {
  }
};

class EventSweepCodeCache : public JfrEvent<EventSweepCodeCache>
{
 public:
  EventSweepCodeCache(EventStartTime timing=TIMED) {}

  void set_sweepId(s4 new_value) {
  }
  void set_sweptCount(unsigned new_value) {
  }
  void set_flushedCount(unsigned new_value) {
  }
  void set_zombifiedCount(unsigned new_value) {
  }

  using JfrEvent<EventSweepCodeCache>::commit; // else commit() is hidden by overloaded versions in this class

  EventSweepCodeCache(
    s4 sweepId,
    unsigned sweptCount,
    unsigned flushedCount,
    unsigned zombifiedCount) {
  }

  void commit(s4 sweepId,
              unsigned sweptCount,
              unsigned flushedCount,
              unsigned zombifiedCount) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     s4 sweepId,
                     unsigned sweptCount,
                     unsigned flushedCount,
                     unsigned zombifiedCount) {
  }
};

class EventCodeCacheFull : public JfrEvent<EventCodeCacheFull>
{
 public:
  EventCodeCacheFull(EventStartTime timing=TIMED) {}

  void set_codeBlobType(u8 new_value) {
  }
  void set_startAddress(u8 new_value) {
  }
  void set_commitedTopAddress(u8 new_value) {
  }
  void set_reservedTopAddress(u8 new_value) {
  }
  void set_entryCount(s4 new_value) {
  }
  void set_methodCount(s4 new_value) {
  }
  void set_adaptorCount(s4 new_value) {
  }
  void set_unallocatedCapacity(u8 new_value) {
  }
  void set_fullCount(s4 new_value) {
  }

  using JfrEvent<EventCodeCacheFull>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(u8 codeBlobType,
                     u8 startAddress,
                     u8 commitedTopAddress,
                     u8 reservedTopAddress,
                     s4 entryCount,
                     s4 methodCount,
                     s4 adaptorCount,
                     u8 unallocatedCapacity,
                     s4 fullCount) {
  }
};

class EventSafepointBegin : public JfrEvent<EventSafepointBegin>
{
 public:
  EventSafepointBegin(EventStartTime timing=TIMED) {}

  void set_safepointId(s4 new_value) {
  }
  void set_totalThreadCount(s4 new_value) {
  }
  void set_jniCriticalThreadCount(s4 new_value) {
  }

  using JfrEvent<EventSafepointBegin>::commit; // else commit() is hidden by overloaded versions in this class

  EventSafepointBegin(
    s4 safepointId,
    s4 totalThreadCount,
    s4 jniCriticalThreadCount) {
  }

  void commit(s4 safepointId,
              s4 totalThreadCount,
              s4 jniCriticalThreadCount) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     s4 safepointId,
                     s4 totalThreadCount,
                     s4 jniCriticalThreadCount) {
  }
};

class EventSafepointStateSynchronization : public JfrEvent<EventSafepointStateSynchronization>
{
 public:
  EventSafepointStateSynchronization(EventStartTime timing=TIMED) {}

  void set_safepointId(s4 new_value) {
  }
  void set_initialThreadCount(s4 new_value) {
  }
  void set_runningThreadCount(s4 new_value) {
  }
  void set_iterations(s4 new_value) {
  }

  using JfrEvent<EventSafepointStateSynchronization>::commit; // else commit() is hidden by overloaded versions in this class

  EventSafepointStateSynchronization(
    s4 safepointId,
    s4 initialThreadCount,
    s4 runningThreadCount,
    s4 iterations) {
  }

  void commit(s4 safepointId,
              s4 initialThreadCount,
              s4 runningThreadCount,
              s4 iterations) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     s4 safepointId,
                     s4 initialThreadCount,
                     s4 runningThreadCount,
                     s4 iterations) {
  }
};

class EventSafepointWaitBlocked : public JfrEvent<EventSafepointWaitBlocked>
{
 public:
  EventSafepointWaitBlocked(EventStartTime timing=TIMED) {}

  void set_safepointId(s4 new_value) {
  }
  void set_runningThreadCount(s4 new_value) {
  }

  using JfrEvent<EventSafepointWaitBlocked>::commit; // else commit() is hidden by overloaded versions in this class

  EventSafepointWaitBlocked(
    s4 safepointId,
    s4 runningThreadCount) {
  }

  void commit(s4 safepointId,
              s4 runningThreadCount) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     s4 safepointId,
                     s4 runningThreadCount) {
  }
};

class EventSafepointCleanup : public JfrEvent<EventSafepointCleanup>
{
 public:
  EventSafepointCleanup(EventStartTime timing=TIMED) {}

  void set_safepointId(s4 new_value) {
  }

  using JfrEvent<EventSafepointCleanup>::commit; // else commit() is hidden by overloaded versions in this class

  EventSafepointCleanup(
    s4 safepointId) {
  }

  void commit(s4 safepointId) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     s4 safepointId) {
  }
};

class EventSafepointCleanupTask : public JfrEvent<EventSafepointCleanupTask>
{
 public:
  EventSafepointCleanupTask(EventStartTime timing=TIMED) {}

  void set_safepointId(s4 new_value) {
  }
  void set_name(const char* new_value) {
  }

  using JfrEvent<EventSafepointCleanupTask>::commit; // else commit() is hidden by overloaded versions in this class

  EventSafepointCleanupTask(
    s4 safepointId,
    const char* name) {
  }

  void commit(s4 safepointId,
              const char* name) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     s4 safepointId,
                     const char* name) {
  }
};

class EventSafepointEnd : public JfrEvent<EventSafepointEnd>
{
 public:
  EventSafepointEnd(EventStartTime timing=TIMED) {}

  void set_safepointId(s4 new_value) {
  }

  using JfrEvent<EventSafepointEnd>::commit; // else commit() is hidden by overloaded versions in this class

  EventSafepointEnd(
    s4 safepointId) {
  }

  void commit(s4 safepointId) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     s4 safepointId) {
  }
};

class EventExecuteVMOperation : public JfrEvent<EventExecuteVMOperation>
{
 public:
  EventExecuteVMOperation(EventStartTime timing=TIMED) {}

  void set_operation(u8 new_value) {
  }
  void set_safepoint(bool new_value) {
  }
  void set_blocking(bool new_value) {
  }
  void set_caller(u8 new_value) {
  }
  void set_safepointId(s4 new_value) {
  }

  using JfrEvent<EventExecuteVMOperation>::commit; // else commit() is hidden by overloaded versions in this class

  EventExecuteVMOperation(
    u8 operation,
    bool safepoint,
    bool blocking,
    u8 caller,
    s4 safepointId) {
  }

  void commit(u8 operation,
              bool safepoint,
              bool blocking,
              u8 caller,
              s4 safepointId) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 operation,
                     bool safepoint,
                     bool blocking,
                     u8 caller,
                     s4 safepointId) {
  }
};

class EventShutdown : public JfrEvent<EventShutdown>
{
 public:
  EventShutdown(EventStartTime timing=TIMED) {}

  void set_reason(const char* new_value) {
  }

  using JfrEvent<EventShutdown>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const char* reason) {
  }
};

class EventObjectAllocationInNewTLAB : public JfrEvent<EventObjectAllocationInNewTLAB>
{
 public:
  EventObjectAllocationInNewTLAB(EventStartTime timing=TIMED) {}

  void set_objectClass(const Klass* new_value) {
  }
  void set_allocationSize(u8 new_value) {
  }
  void set_tlabSize(u8 new_value) {
  }

  using JfrEvent<EventObjectAllocationInNewTLAB>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const Klass* objectClass,
                     u8 allocationSize,
                     u8 tlabSize) {
  }
};

class EventObjectAllocationOutsideTLAB : public JfrEvent<EventObjectAllocationOutsideTLAB>
{
 public:
  EventObjectAllocationOutsideTLAB(EventStartTime timing=TIMED) {}

  void set_objectClass(const Klass* new_value) {
  }
  void set_allocationSize(u8 new_value) {
  }

  using JfrEvent<EventObjectAllocationOutsideTLAB>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const Klass* objectClass,
                     u8 allocationSize) {
  }
};

class EventOldObjectSample : public JfrEvent<EventOldObjectSample>
{
 public:
  EventOldObjectSample(EventStartTime timing=TIMED) {}

  void set_allocationTime(const Ticks& new_value) {
  }
  void set_lastKnownHeapUsage(u8 new_value) {
  }
  void set_object(u8 new_value) {
  }
  void set_arrayElements(s4 new_value) {
  }
  void set_root(u8 new_value) {
  }

  using JfrEvent<EventOldObjectSample>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const Ticks& allocationTime,
                     u8 lastKnownHeapUsage,
                     u8 object,
                     s4 arrayElements,
                     u8 root) {
  }
};

class EventDumpReason : public JfrEvent<EventDumpReason>
{
 public:
  EventDumpReason(EventStartTime timing=TIMED) {}

  void set_reason(const char* new_value) {
  }
  void set_recordingId(s4 new_value) {
  }

  using JfrEvent<EventDumpReason>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(const char* reason,
                     s4 recordingId) {
  }
};

class EventDataLoss : public JfrEvent<EventDataLoss>
{
 public:
  EventDataLoss(EventStartTime timing=TIMED) {}

  void set_amount(u8 new_value) {
  }
  void set_total(u8 new_value) {
  }

  using JfrEvent<EventDataLoss>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(u8 amount,
                     u8 total) {
  }
};

class EventJVMInformation : public JfrEvent<EventJVMInformation>
{
 public:
  EventJVMInformation(EventStartTime timing=TIMED) {}

  void set_jvmName(const char* new_value) {
  }
  void set_jvmVersion(const char* new_value) {
  }
  void set_jvmArguments(const char* new_value) {
  }
  void set_jvmFlags(const char* new_value) {
  }
  void set_javaArguments(const char* new_value) {
  }
  void set_jvmStartTime(s8 new_value) {
  }
  void set_pid(s8 new_value) {
  }

  using JfrEvent<EventJVMInformation>::commit; // else commit() is hidden by overloaded versions in this class

  EventJVMInformation(
    const char* jvmName,
    const char* jvmVersion,
    const char* jvmArguments,
    const char* jvmFlags,
    const char* javaArguments,
    s8 jvmStartTime,
    s8 pid) {
  }

  void commit(const char* jvmName,
              const char* jvmVersion,
              const char* jvmArguments,
              const char* jvmFlags,
              const char* javaArguments,
              s8 jvmStartTime,
              s8 pid) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* jvmName,
                     const char* jvmVersion,
                     const char* jvmArguments,
                     const char* jvmFlags,
                     const char* javaArguments,
                     s8 jvmStartTime,
                     s8 pid) {
  }
};

class EventOSInformation : public JfrEvent<EventOSInformation>
{
 public:
  EventOSInformation(EventStartTime timing=TIMED) {}

  void set_osVersion(const char* new_value) {
  }

  using JfrEvent<EventOSInformation>::commit; // else commit() is hidden by overloaded versions in this class

  EventOSInformation(
    const char* osVersion) {
  }

  void commit(const char* osVersion) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* osVersion) {
  }
};

class EventVirtualizationInformation : public JfrEvent<EventVirtualizationInformation>
{
 public:
  EventVirtualizationInformation(EventStartTime timing=TIMED) {}

  void set_name(const char* new_value) {
  }

  using JfrEvent<EventVirtualizationInformation>::commit; // else commit() is hidden by overloaded versions in this class

  EventVirtualizationInformation(
    const char* name) {
  }

  void commit(const char* name) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* name) {
  }
};

class EventInitialSystemProperty : public JfrEvent<EventInitialSystemProperty>
{
 public:
  EventInitialSystemProperty(EventStartTime timing=TIMED) {}

  void set_key(const char* new_value) {
  }
  void set_value(const char* new_value) {
  }

  using JfrEvent<EventInitialSystemProperty>::commit; // else commit() is hidden by overloaded versions in this class

  EventInitialSystemProperty(
    const char* key,
    const char* value) {
  }

  void commit(const char* key,
              const char* value) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* key,
                     const char* value) {
  }
};

class EventInitialEnvironmentVariable : public JfrEvent<EventInitialEnvironmentVariable>
{
 public:
  EventInitialEnvironmentVariable(EventStartTime timing=TIMED) {}

  void set_key(const char* new_value) {
  }
  void set_value(const char* new_value) {
  }

  using JfrEvent<EventInitialEnvironmentVariable>::commit; // else commit() is hidden by overloaded versions in this class

  EventInitialEnvironmentVariable(
    const char* key,
    const char* value) {
  }

  void commit(const char* key,
              const char* value) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* key,
                     const char* value) {
  }
};

class EventSystemProcess : public JfrEvent<EventSystemProcess>
{
 public:
  EventSystemProcess(EventStartTime timing=TIMED) {}

  void set_pid(const char* new_value) {
  }
  void set_commandLine(const char* new_value) {
  }

  using JfrEvent<EventSystemProcess>::commit; // else commit() is hidden by overloaded versions in this class

  EventSystemProcess(
    const char* pid,
    const char* commandLine) {
  }

  void commit(const char* pid,
              const char* commandLine) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* pid,
                     const char* commandLine) {
  }
};

class EventCPUInformation : public JfrEvent<EventCPUInformation>
{
 public:
  EventCPUInformation(EventStartTime timing=TIMED) {}

  void set_cpu(const char* new_value) {
  }
  void set_description(const char* new_value) {
  }
  void set_sockets(unsigned new_value) {
  }
  void set_cores(unsigned new_value) {
  }
  void set_hwThreads(unsigned new_value) {
  }

  using JfrEvent<EventCPUInformation>::commit; // else commit() is hidden by overloaded versions in this class

  EventCPUInformation(
    const char* cpu,
    const char* description,
    unsigned sockets,
    unsigned cores,
    unsigned hwThreads) {
  }

  void commit(const char* cpu,
              const char* description,
              unsigned sockets,
              unsigned cores,
              unsigned hwThreads) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* cpu,
                     const char* description,
                     unsigned sockets,
                     unsigned cores,
                     unsigned hwThreads) {
  }
};

class EventCPUTimeStampCounter : public JfrEvent<EventCPUTimeStampCounter>
{
 public:
  EventCPUTimeStampCounter(EventStartTime timing=TIMED) {}

  void set_fastTimeEnabled(bool new_value) {
  }
  void set_fastTimeAutoEnabled(bool new_value) {
  }
  void set_osFrequency(s8 new_value) {
  }
  void set_fastTimeFrequency(s8 new_value) {
  }

  using JfrEvent<EventCPUTimeStampCounter>::commit; // else commit() is hidden by overloaded versions in this class

  EventCPUTimeStampCounter(
    bool fastTimeEnabled,
    bool fastTimeAutoEnabled,
    s8 osFrequency,
    s8 fastTimeFrequency) {
  }

  void commit(bool fastTimeEnabled,
              bool fastTimeAutoEnabled,
              s8 osFrequency,
              s8 fastTimeFrequency) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     bool fastTimeEnabled,
                     bool fastTimeAutoEnabled,
                     s8 osFrequency,
                     s8 fastTimeFrequency) {
  }
};

class EventCPULoad : public JfrEvent<EventCPULoad>
{
 public:
  EventCPULoad(EventStartTime timing=TIMED) {}

  void set_jvmUser(float new_value) {
  }
  void set_jvmSystem(float new_value) {
  }
  void set_machineTotal(float new_value) {
  }

  using JfrEvent<EventCPULoad>::commit; // else commit() is hidden by overloaded versions in this class

  EventCPULoad(
    float jvmUser,
    float jvmSystem,
    float machineTotal) {
  }

  void commit(float jvmUser,
              float jvmSystem,
              float machineTotal) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     float jvmUser,
                     float jvmSystem,
                     float machineTotal) {
  }
};

class EventThreadCPULoad : public JfrEvent<EventThreadCPULoad>
{
 public:
  EventThreadCPULoad(EventStartTime timing=TIMED) {}

  void set_user(float new_value) {
  }
  void set_system(float new_value) {
  }

  using JfrEvent<EventThreadCPULoad>::commit; // else commit() is hidden by overloaded versions in this class

  EventThreadCPULoad(
    float user,
    float system) {
  }

  void commit(float user,
              float system) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     float user,
                     float system) {
  }
};

class EventThreadContextSwitchRate : public JfrEvent<EventThreadContextSwitchRate>
{
 public:
  EventThreadContextSwitchRate(EventStartTime timing=TIMED) {}

  void set_switchRate(float new_value) {
  }

  using JfrEvent<EventThreadContextSwitchRate>::commit; // else commit() is hidden by overloaded versions in this class

  EventThreadContextSwitchRate(
    float switchRate) {
  }

  void commit(float switchRate) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     float switchRate) {
  }
};

class EventNetworkUtilization : public JfrEvent<EventNetworkUtilization>
{
 public:
  EventNetworkUtilization(EventStartTime timing=TIMED) {}

  void set_networkInterface(u8 new_value) {
  }
  void set_readRate(s8 new_value) {
  }
  void set_writeRate(s8 new_value) {
  }

  using JfrEvent<EventNetworkUtilization>::commit; // else commit() is hidden by overloaded versions in this class

  EventNetworkUtilization(
    u8 networkInterface,
    s8 readRate,
    s8 writeRate) {
  }

  void commit(u8 networkInterface,
              s8 readRate,
              s8 writeRate) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 networkInterface,
                     s8 readRate,
                     s8 writeRate) {
  }
};

class EventJavaThreadStatistics : public JfrEvent<EventJavaThreadStatistics>
{
 public:
  EventJavaThreadStatistics(EventStartTime timing=TIMED) {}

  void set_activeCount(s8 new_value) {
  }
  void set_daemonCount(s8 new_value) {
  }
  void set_accumulatedCount(s8 new_value) {
  }
  void set_peakCount(s8 new_value) {
  }

  using JfrEvent<EventJavaThreadStatistics>::commit; // else commit() is hidden by overloaded versions in this class

  EventJavaThreadStatistics(
    s8 activeCount,
    s8 daemonCount,
    s8 accumulatedCount,
    s8 peakCount) {
  }

  void commit(s8 activeCount,
              s8 daemonCount,
              s8 accumulatedCount,
              s8 peakCount) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     s8 activeCount,
                     s8 daemonCount,
                     s8 accumulatedCount,
                     s8 peakCount) {
  }
};

class EventClassLoadingStatistics : public JfrEvent<EventClassLoadingStatistics>
{
 public:
  EventClassLoadingStatistics(EventStartTime timing=TIMED) {}

  void set_loadedClassCount(s8 new_value) {
  }
  void set_unloadedClassCount(s8 new_value) {
  }

  using JfrEvent<EventClassLoadingStatistics>::commit; // else commit() is hidden by overloaded versions in this class

  EventClassLoadingStatistics(
    s8 loadedClassCount,
    s8 unloadedClassCount) {
  }

  void commit(s8 loadedClassCount,
              s8 unloadedClassCount) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     s8 loadedClassCount,
                     s8 unloadedClassCount) {
  }
};

class EventClassLoaderStatistics : public JfrEvent<EventClassLoaderStatistics>
{
 public:
  EventClassLoaderStatistics(EventStartTime timing=TIMED) {}

  void set_classLoader(const ClassLoaderData* new_value) {
  }
  void set_parentClassLoader(const ClassLoaderData* new_value) {
  }
  void set_classLoaderData(u8 new_value) {
  }
  void set_classCount(s8 new_value) {
  }
  void set_chunkSize(u8 new_value) {
  }
  void set_blockSize(u8 new_value) {
  }
  void set_anonymousClassCount(s8 new_value) {
  }
  void set_anonymousChunkSize(u8 new_value) {
  }
  void set_anonymousBlockSize(u8 new_value) {
  }

  using JfrEvent<EventClassLoaderStatistics>::commit; // else commit() is hidden by overloaded versions in this class

  EventClassLoaderStatistics(
    const ClassLoaderData* classLoader,
    const ClassLoaderData* parentClassLoader,
    u8 classLoaderData,
    s8 classCount,
    u8 chunkSize,
    u8 blockSize,
    s8 anonymousClassCount,
    u8 anonymousChunkSize,
    u8 anonymousBlockSize) {
  }

  void commit(const ClassLoaderData* classLoader,
              const ClassLoaderData* parentClassLoader,
              u8 classLoaderData,
              s8 classCount,
              u8 chunkSize,
              u8 blockSize,
              s8 anonymousClassCount,
              u8 anonymousChunkSize,
              u8 anonymousBlockSize) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const ClassLoaderData* classLoader,
                     const ClassLoaderData* parentClassLoader,
                     u8 classLoaderData,
                     s8 classCount,
                     u8 chunkSize,
                     u8 blockSize,
                     s8 anonymousClassCount,
                     u8 anonymousChunkSize,
                     u8 anonymousBlockSize) {
  }
};

class EventSymbolTableStatistics : public JfrEvent<EventSymbolTableStatistics>
{
 public:
  EventSymbolTableStatistics(EventStartTime timing=TIMED) {}

  void set_bucketCount(u8 new_value) {
  }
  void set_entryCount(u8 new_value) {
  }
  void set_totalFootprint(u8 new_value) {
  }
  void set_bucketCountMaximum(u8 new_value) {
  }
  void set_bucketCountAverage(float new_value) {
  }
  void set_bucketCountVariance(float new_value) {
  }
  void set_bucketCountStandardDeviation(float new_value) {
  }
  void set_insertionRate(float new_value) {
  }
  void set_removalRate(float new_value) {
  }

  using JfrEvent<EventSymbolTableStatistics>::commit; // else commit() is hidden by overloaded versions in this class

  EventSymbolTableStatistics(
    u8 bucketCount,
    u8 entryCount,
    u8 totalFootprint,
    u8 bucketCountMaximum,
    float bucketCountAverage,
    float bucketCountVariance,
    float bucketCountStandardDeviation,
    float insertionRate,
    float removalRate) {
  }

  void commit(u8 bucketCount,
              u8 entryCount,
              u8 totalFootprint,
              u8 bucketCountMaximum,
              float bucketCountAverage,
              float bucketCountVariance,
              float bucketCountStandardDeviation,
              float insertionRate,
              float removalRate) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 bucketCount,
                     u8 entryCount,
                     u8 totalFootprint,
                     u8 bucketCountMaximum,
                     float bucketCountAverage,
                     float bucketCountVariance,
                     float bucketCountStandardDeviation,
                     float insertionRate,
                     float removalRate) {
  }
};

class EventStringTableStatistics : public JfrEvent<EventStringTableStatistics>
{
 public:
  EventStringTableStatistics(EventStartTime timing=TIMED) {}

  void set_bucketCount(u8 new_value) {
  }
  void set_entryCount(u8 new_value) {
  }
  void set_totalFootprint(u8 new_value) {
  }
  void set_bucketCountMaximum(u8 new_value) {
  }
  void set_bucketCountAverage(float new_value) {
  }
  void set_bucketCountVariance(float new_value) {
  }
  void set_bucketCountStandardDeviation(float new_value) {
  }
  void set_insertionRate(float new_value) {
  }
  void set_removalRate(float new_value) {
  }

  using JfrEvent<EventStringTableStatistics>::commit; // else commit() is hidden by overloaded versions in this class

  EventStringTableStatistics(
    u8 bucketCount,
    u8 entryCount,
    u8 totalFootprint,
    u8 bucketCountMaximum,
    float bucketCountAverage,
    float bucketCountVariance,
    float bucketCountStandardDeviation,
    float insertionRate,
    float removalRate) {
  }

  void commit(u8 bucketCount,
              u8 entryCount,
              u8 totalFootprint,
              u8 bucketCountMaximum,
              float bucketCountAverage,
              float bucketCountVariance,
              float bucketCountStandardDeviation,
              float insertionRate,
              float removalRate) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 bucketCount,
                     u8 entryCount,
                     u8 totalFootprint,
                     u8 bucketCountMaximum,
                     float bucketCountAverage,
                     float bucketCountVariance,
                     float bucketCountStandardDeviation,
                     float insertionRate,
                     float removalRate) {
  }
};

class EventPlaceholderTableStatistics : public JfrEvent<EventPlaceholderTableStatistics>
{
 public:
  EventPlaceholderTableStatistics(EventStartTime timing=TIMED) {}

  void set_bucketCount(u8 new_value) {
  }
  void set_entryCount(u8 new_value) {
  }
  void set_totalFootprint(u8 new_value) {
  }
  void set_bucketCountMaximum(u8 new_value) {
  }
  void set_bucketCountAverage(float new_value) {
  }
  void set_bucketCountVariance(float new_value) {
  }
  void set_bucketCountStandardDeviation(float new_value) {
  }
  void set_insertionRate(float new_value) {
  }
  void set_removalRate(float new_value) {
  }

  using JfrEvent<EventPlaceholderTableStatistics>::commit; // else commit() is hidden by overloaded versions in this class

  EventPlaceholderTableStatistics(
    u8 bucketCount,
    u8 entryCount,
    u8 totalFootprint,
    u8 bucketCountMaximum,
    float bucketCountAverage,
    float bucketCountVariance,
    float bucketCountStandardDeviation,
    float insertionRate,
    float removalRate) {
  }

  void commit(u8 bucketCount,
              u8 entryCount,
              u8 totalFootprint,
              u8 bucketCountMaximum,
              float bucketCountAverage,
              float bucketCountVariance,
              float bucketCountStandardDeviation,
              float insertionRate,
              float removalRate) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 bucketCount,
                     u8 entryCount,
                     u8 totalFootprint,
                     u8 bucketCountMaximum,
                     float bucketCountAverage,
                     float bucketCountVariance,
                     float bucketCountStandardDeviation,
                     float insertionRate,
                     float removalRate) {
  }
};

class EventLoaderConstraintsTableStatistics : public JfrEvent<EventLoaderConstraintsTableStatistics>
{
 public:
  EventLoaderConstraintsTableStatistics(EventStartTime timing=TIMED) {}

  void set_bucketCount(u8 new_value) {
  }
  void set_entryCount(u8 new_value) {
  }
  void set_totalFootprint(u8 new_value) {
  }
  void set_bucketCountMaximum(u8 new_value) {
  }
  void set_bucketCountAverage(float new_value) {
  }
  void set_bucketCountVariance(float new_value) {
  }
  void set_bucketCountStandardDeviation(float new_value) {
  }
  void set_insertionRate(float new_value) {
  }
  void set_removalRate(float new_value) {
  }

  using JfrEvent<EventLoaderConstraintsTableStatistics>::commit; // else commit() is hidden by overloaded versions in this class

  EventLoaderConstraintsTableStatistics(
    u8 bucketCount,
    u8 entryCount,
    u8 totalFootprint,
    u8 bucketCountMaximum,
    float bucketCountAverage,
    float bucketCountVariance,
    float bucketCountStandardDeviation,
    float insertionRate,
    float removalRate) {
  }

  void commit(u8 bucketCount,
              u8 entryCount,
              u8 totalFootprint,
              u8 bucketCountMaximum,
              float bucketCountAverage,
              float bucketCountVariance,
              float bucketCountStandardDeviation,
              float insertionRate,
              float removalRate) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 bucketCount,
                     u8 entryCount,
                     u8 totalFootprint,
                     u8 bucketCountMaximum,
                     float bucketCountAverage,
                     float bucketCountVariance,
                     float bucketCountStandardDeviation,
                     float insertionRate,
                     float removalRate) {
  }
};

class EventProtectionDomainCacheTableStatistics : public JfrEvent<EventProtectionDomainCacheTableStatistics>
{
 public:
  EventProtectionDomainCacheTableStatistics(EventStartTime timing=TIMED) {}

  void set_bucketCount(u8 new_value) {
  }
  void set_entryCount(u8 new_value) {
  }
  void set_totalFootprint(u8 new_value) {
  }
  void set_bucketCountMaximum(u8 new_value) {
  }
  void set_bucketCountAverage(float new_value) {
  }
  void set_bucketCountVariance(float new_value) {
  }
  void set_bucketCountStandardDeviation(float new_value) {
  }
  void set_insertionRate(float new_value) {
  }
  void set_removalRate(float new_value) {
  }

  using JfrEvent<EventProtectionDomainCacheTableStatistics>::commit; // else commit() is hidden by overloaded versions in this class

  EventProtectionDomainCacheTableStatistics(
    u8 bucketCount,
    u8 entryCount,
    u8 totalFootprint,
    u8 bucketCountMaximum,
    float bucketCountAverage,
    float bucketCountVariance,
    float bucketCountStandardDeviation,
    float insertionRate,
    float removalRate) {
  }

  void commit(u8 bucketCount,
              u8 entryCount,
              u8 totalFootprint,
              u8 bucketCountMaximum,
              float bucketCountAverage,
              float bucketCountVariance,
              float bucketCountStandardDeviation,
              float insertionRate,
              float removalRate) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 bucketCount,
                     u8 entryCount,
                     u8 totalFootprint,
                     u8 bucketCountMaximum,
                     float bucketCountAverage,
                     float bucketCountVariance,
                     float bucketCountStandardDeviation,
                     float insertionRate,
                     float removalRate) {
  }
};

class EventThreadAllocationStatistics : public JfrEvent<EventThreadAllocationStatistics>
{
 public:
  EventThreadAllocationStatistics(EventStartTime timing=TIMED) {}

  void set_allocated(u8 new_value) {
  }
  void set_thread(u8 new_value) {
  }

  using JfrEvent<EventThreadAllocationStatistics>::commit; // else commit() is hidden by overloaded versions in this class

  EventThreadAllocationStatistics(
    u8 allocated,
    u8 thread) {
  }

  void commit(u8 allocated,
              u8 thread) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 allocated,
                     u8 thread) {
  }
};

class EventPhysicalMemory : public JfrEvent<EventPhysicalMemory>
{
 public:
  EventPhysicalMemory(EventStartTime timing=TIMED) {}

  void set_totalSize(u8 new_value) {
  }
  void set_usedSize(u8 new_value) {
  }

  using JfrEvent<EventPhysicalMemory>::commit; // else commit() is hidden by overloaded versions in this class

  EventPhysicalMemory(
    u8 totalSize,
    u8 usedSize) {
  }

  void commit(u8 totalSize,
              u8 usedSize) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 totalSize,
                     u8 usedSize) {
  }
};

class EventExecutionSample : public JfrEvent<EventExecutionSample>
{
 public:
  EventExecutionSample(EventStartTime timing=TIMED) {}

  void set_sampledThread(u8 new_value) {
  }
  void set_stackTrace(u8 new_value) {
  }
  void set_state(u8 new_value) {
  }

  using JfrEvent<EventExecutionSample>::commit; // else commit() is hidden by overloaded versions in this class

  EventExecutionSample(
    u8 sampledThread,
    u8 stackTrace,
    u8 state) {
  }

  void commit(u8 sampledThread,
              u8 stackTrace,
              u8 state) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 sampledThread,
                     u8 stackTrace,
                     u8 state) {
  }
};

class EventNativeMethodSample : public JfrEvent<EventNativeMethodSample>
{
 public:
  EventNativeMethodSample(EventStartTime timing=TIMED) {}

  void set_sampledThread(u8 new_value) {
  }
  void set_stackTrace(u8 new_value) {
  }
  void set_state(u8 new_value) {
  }

  using JfrEvent<EventNativeMethodSample>::commit; // else commit() is hidden by overloaded versions in this class

  EventNativeMethodSample(
    u8 sampledThread,
    u8 stackTrace,
    u8 state) {
  }

  void commit(u8 sampledThread,
              u8 stackTrace,
              u8 state) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 sampledThread,
                     u8 stackTrace,
                     u8 state) {
  }
};

class EventThreadDump : public JfrEvent<EventThreadDump>
{
 public:
  EventThreadDump(EventStartTime timing=TIMED) {}

  void set_result(const char* new_value) {
  }

  using JfrEvent<EventThreadDump>::commit; // else commit() is hidden by overloaded versions in this class

  EventThreadDump(
    const char* result) {
  }

  void commit(const char* result) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* result) {
  }
};

class EventNativeLibrary : public JfrEvent<EventNativeLibrary>
{
 public:
  EventNativeLibrary(EventStartTime timing=TIMED) {}

  void set_name(const char* new_value) {
  }
  void set_baseAddress(u8 new_value) {
  }
  void set_topAddress(u8 new_value) {
  }

  using JfrEvent<EventNativeLibrary>::commit; // else commit() is hidden by overloaded versions in this class

  EventNativeLibrary(
    const char* name,
    u8 baseAddress,
    u8 topAddress) {
  }

  void commit(const char* name,
              u8 baseAddress,
              u8 topAddress) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* name,
                     u8 baseAddress,
                     u8 topAddress) {
  }
};

class EventCompilerStatistics : public JfrEvent<EventCompilerStatistics>
{
 public:
  EventCompilerStatistics(EventStartTime timing=TIMED) {}

  void set_compileCount(s4 new_value) {
  }
  void set_bailoutCount(s4 new_value) {
  }
  void set_invalidatedCount(s4 new_value) {
  }
  void set_osrCompileCount(s4 new_value) {
  }
  void set_standardCompileCount(s4 new_value) {
  }
  void set_osrBytesCompiled(u8 new_value) {
  }
  void set_standardBytesCompiled(u8 new_value) {
  }
  void set_nmetodsSize(u8 new_value) {
  }
  void set_nmetodCodeSize(u8 new_value) {
  }
  void set_peakTimeSpent(s8 new_value) {
  }
  void set_totalTimeSpent(s8 new_value) {
  }

  using JfrEvent<EventCompilerStatistics>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(s4 compileCount,
                     s4 bailoutCount,
                     s4 invalidatedCount,
                     s4 osrCompileCount,
                     s4 standardCompileCount,
                     u8 osrBytesCompiled,
                     u8 standardBytesCompiled,
                     u8 nmetodsSize,
                     u8 nmetodCodeSize,
                     s8 peakTimeSpent,
                     s8 totalTimeSpent) {
  }
};

class EventCompilerConfiguration : public JfrEvent<EventCompilerConfiguration>
{
 public:
  EventCompilerConfiguration(EventStartTime timing=TIMED) {}

  void set_threadCount(s4 new_value) {
  }
  void set_tieredCompilation(bool new_value) {
  }

  using JfrEvent<EventCompilerConfiguration>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(s4 threadCount,
                     bool tieredCompilation) {
  }
};

class EventCodeCacheStatistics : public JfrEvent<EventCodeCacheStatistics>
{
 public:
  EventCodeCacheStatistics(EventStartTime timing=TIMED) {}

  void set_codeBlobType(u8 new_value) {
  }
  void set_startAddress(u8 new_value) {
  }
  void set_reservedTopAddress(u8 new_value) {
  }
  void set_entryCount(s4 new_value) {
  }
  void set_methodCount(s4 new_value) {
  }
  void set_adaptorCount(s4 new_value) {
  }
  void set_unallocatedCapacity(u8 new_value) {
  }
  void set_fullCount(s4 new_value) {
  }

  using JfrEvent<EventCodeCacheStatistics>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(u8 codeBlobType,
                     u8 startAddress,
                     u8 reservedTopAddress,
                     s4 entryCount,
                     s4 methodCount,
                     s4 adaptorCount,
                     u8 unallocatedCapacity,
                     s4 fullCount) {
  }
};

class EventCodeCacheConfiguration : public JfrEvent<EventCodeCacheConfiguration>
{
 public:
  EventCodeCacheConfiguration(EventStartTime timing=TIMED) {}

  void set_initialSize(u8 new_value) {
  }
  void set_reservedSize(u8 new_value) {
  }
  void set_nonNMethodSize(u8 new_value) {
  }
  void set_profiledSize(u8 new_value) {
  }
  void set_nonProfiledSize(u8 new_value) {
  }
  void set_expansionSize(u8 new_value) {
  }
  void set_minBlockLength(u8 new_value) {
  }
  void set_startAddress(u8 new_value) {
  }
  void set_reservedTopAddress(u8 new_value) {
  }

  using JfrEvent<EventCodeCacheConfiguration>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(u8 initialSize,
                     u8 reservedSize,
                     u8 nonNMethodSize,
                     u8 profiledSize,
                     u8 nonProfiledSize,
                     u8 expansionSize,
                     u8 minBlockLength,
                     u8 startAddress,
                     u8 reservedTopAddress) {
  }
};

class EventCodeSweeperStatistics : public JfrEvent<EventCodeSweeperStatistics>
{
 public:
  EventCodeSweeperStatistics(EventStartTime timing=TIMED) {}

  void set_sweepCount(s4 new_value) {
  }
  void set_methodReclaimedCount(s4 new_value) {
  }
  void set_totalSweepTime(const Tickspan& new_value) {
  }
  void set_peakFractionTime(const Tickspan& new_value) {
  }
  void set_peakSweepTime(const Tickspan& new_value) {
  }

  using JfrEvent<EventCodeSweeperStatistics>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(s4 sweepCount,
                     s4 methodReclaimedCount,
                     const Tickspan& totalSweepTime,
                     const Tickspan& peakFractionTime,
                     const Tickspan& peakSweepTime) {
  }
};

class EventCodeSweeperConfiguration : public JfrEvent<EventCodeSweeperConfiguration>
{
 public:
  EventCodeSweeperConfiguration(EventStartTime timing=TIMED) {}

  void set_sweeperEnabled(bool new_value) {
  }
  void set_flushingEnabled(bool new_value) {
  }

  using JfrEvent<EventCodeSweeperConfiguration>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(bool sweeperEnabled,
                     bool flushingEnabled) {
  }
};

class EventIntFlag : public JfrEvent<EventIntFlag>
{
 public:
  EventIntFlag(EventStartTime timing=TIMED) {}

  void set_name(const char* new_value) {
  }
  void set_value(s4 new_value) {
  }
  void set_origin(u8 new_value) {
  }

  using JfrEvent<EventIntFlag>::commit; // else commit() is hidden by overloaded versions in this class

  EventIntFlag(
    const char* name,
    s4 value,
    u8 origin) {
  }

  void commit(const char* name,
              s4 value,
              u8 origin) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* name,
                     s4 value,
                     u8 origin) {
  }
};

class EventUnsignedIntFlag : public JfrEvent<EventUnsignedIntFlag>
{
 public:
  EventUnsignedIntFlag(EventStartTime timing=TIMED) {}

  void set_name(const char* new_value) {
  }
  void set_value(unsigned new_value) {
  }
  void set_origin(u8 new_value) {
  }

  using JfrEvent<EventUnsignedIntFlag>::commit; // else commit() is hidden by overloaded versions in this class

  EventUnsignedIntFlag(
    const char* name,
    unsigned value,
    u8 origin) {
  }

  void commit(const char* name,
              unsigned value,
              u8 origin) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* name,
                     unsigned value,
                     u8 origin) {
  }
};

class EventLongFlag : public JfrEvent<EventLongFlag>
{
 public:
  EventLongFlag(EventStartTime timing=TIMED) {}

  void set_name(const char* new_value) {
  }
  void set_value(s8 new_value) {
  }
  void set_origin(u8 new_value) {
  }

  using JfrEvent<EventLongFlag>::commit; // else commit() is hidden by overloaded versions in this class

  EventLongFlag(
    const char* name,
    s8 value,
    u8 origin) {
  }

  void commit(const char* name,
              s8 value,
              u8 origin) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* name,
                     s8 value,
                     u8 origin) {
  }
};

class EventUnsignedLongFlag : public JfrEvent<EventUnsignedLongFlag>
{
 public:
  EventUnsignedLongFlag(EventStartTime timing=TIMED) {}

  void set_name(const char* new_value) {
  }
  void set_value(u8 new_value) {
  }
  void set_origin(u8 new_value) {
  }

  using JfrEvent<EventUnsignedLongFlag>::commit; // else commit() is hidden by overloaded versions in this class

  EventUnsignedLongFlag(
    const char* name,
    u8 value,
    u8 origin) {
  }

  void commit(const char* name,
              u8 value,
              u8 origin) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* name,
                     u8 value,
                     u8 origin) {
  }
};

class EventDoubleFlag : public JfrEvent<EventDoubleFlag>
{
 public:
  EventDoubleFlag(EventStartTime timing=TIMED) {}

  void set_name(const char* new_value) {
  }
  void set_value(double new_value) {
  }
  void set_origin(u8 new_value) {
  }

  using JfrEvent<EventDoubleFlag>::commit; // else commit() is hidden by overloaded versions in this class

  EventDoubleFlag(
    const char* name,
    double value,
    u8 origin) {
  }

  void commit(const char* name,
              double value,
              u8 origin) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* name,
                     double value,
                     u8 origin) {
  }
};

class EventBooleanFlag : public JfrEvent<EventBooleanFlag>
{
 public:
  EventBooleanFlag(EventStartTime timing=TIMED) {}

  void set_name(const char* new_value) {
  }
  void set_value(bool new_value) {
  }
  void set_origin(u8 new_value) {
  }

  using JfrEvent<EventBooleanFlag>::commit; // else commit() is hidden by overloaded versions in this class

  EventBooleanFlag(
    const char* name,
    bool value,
    u8 origin) {
  }

  void commit(const char* name,
              bool value,
              u8 origin) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* name,
                     bool value,
                     u8 origin) {
  }
};

class EventStringFlag : public JfrEvent<EventStringFlag>
{
 public:
  EventStringFlag(EventStartTime timing=TIMED) {}

  void set_name(const char* new_value) {
  }
  void set_value(const char* new_value) {
  }
  void set_origin(u8 new_value) {
  }

  using JfrEvent<EventStringFlag>::commit; // else commit() is hidden by overloaded versions in this class

  EventStringFlag(
    const char* name,
    const char* value,
    u8 origin) {
  }

  void commit(const char* name,
              const char* value,
              u8 origin) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     const char* name,
                     const char* value,
                     u8 origin) {
  }
};

class EventObjectCount : public JfrEvent<EventObjectCount>
{
 public:
  EventObjectCount(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_objectClass(const Klass* new_value) {
  }
  void set_count(s8 new_value) {
  }
  void set_totalSize(u8 new_value) {
  }

  using JfrEvent<EventObjectCount>::commit; // else commit() is hidden by overloaded versions in this class



  static void commit(unsigned gcId,
                     const Klass* objectClass,
                     s8 count,
                     u8 totalSize) {
  }
};

class EventG1HeapRegionInformation : public JfrEvent<EventG1HeapRegionInformation>
{
 public:
  EventG1HeapRegionInformation(EventStartTime timing=TIMED) {}

  void set_index(unsigned new_value) {
  }
  void set_type(u8 new_value) {
  }
  void set_start(u8 new_value) {
  }
  void set_used(u8 new_value) {
  }

  using JfrEvent<EventG1HeapRegionInformation>::commit; // else commit() is hidden by overloaded versions in this class

  EventG1HeapRegionInformation(
    unsigned index,
    u8 type,
    u8 start,
    u8 used) {
  }

  void commit(unsigned index,
              u8 type,
              u8 start,
              u8 used) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned index,
                     u8 type,
                     u8 start,
                     u8 used) {
  }
};

class EventGCConfiguration : public JfrEvent<EventGCConfiguration>
{
 public:
  EventGCConfiguration(EventStartTime timing=TIMED) {}

  void set_youngCollector(u8 new_value) {
  }
  void set_oldCollector(u8 new_value) {
  }
  void set_parallelGCThreads(unsigned new_value) {
  }
  void set_concurrentGCThreads(unsigned new_value) {
  }
  void set_usesDynamicGCThreads(bool new_value) {
  }
  void set_isExplicitGCConcurrent(bool new_value) {
  }
  void set_isExplicitGCDisabled(bool new_value) {
  }
  void set_pauseTarget(s8 new_value) {
  }
  void set_gcTimeRatio(unsigned new_value) {
  }

  using JfrEvent<EventGCConfiguration>::commit; // else commit() is hidden by overloaded versions in this class

  EventGCConfiguration(
    u8 youngCollector,
    u8 oldCollector,
    unsigned parallelGCThreads,
    unsigned concurrentGCThreads,
    bool usesDynamicGCThreads,
    bool isExplicitGCConcurrent,
    bool isExplicitGCDisabled,
    s8 pauseTarget,
    unsigned gcTimeRatio) {
  }

  void commit(u8 youngCollector,
              u8 oldCollector,
              unsigned parallelGCThreads,
              unsigned concurrentGCThreads,
              bool usesDynamicGCThreads,
              bool isExplicitGCConcurrent,
              bool isExplicitGCDisabled,
              s8 pauseTarget,
              unsigned gcTimeRatio) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 youngCollector,
                     u8 oldCollector,
                     unsigned parallelGCThreads,
                     unsigned concurrentGCThreads,
                     bool usesDynamicGCThreads,
                     bool isExplicitGCConcurrent,
                     bool isExplicitGCDisabled,
                     s8 pauseTarget,
                     unsigned gcTimeRatio) {
  }
};

class EventGCSurvivorConfiguration : public JfrEvent<EventGCSurvivorConfiguration>
{
 public:
  EventGCSurvivorConfiguration(EventStartTime timing=TIMED) {}

  void set_maxTenuringThreshold(u1 new_value) {
  }
  void set_initialTenuringThreshold(u1 new_value) {
  }

  using JfrEvent<EventGCSurvivorConfiguration>::commit; // else commit() is hidden by overloaded versions in this class

  EventGCSurvivorConfiguration(
    u1 maxTenuringThreshold,
    u1 initialTenuringThreshold) {
  }

  void commit(u1 maxTenuringThreshold,
              u1 initialTenuringThreshold) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u1 maxTenuringThreshold,
                     u1 initialTenuringThreshold) {
  }
};

class EventGCTLABConfiguration : public JfrEvent<EventGCTLABConfiguration>
{
 public:
  EventGCTLABConfiguration(EventStartTime timing=TIMED) {}

  void set_usesTLABs(bool new_value) {
  }
  void set_minTLABSize(u8 new_value) {
  }
  void set_tlabRefillWasteLimit(u8 new_value) {
  }

  using JfrEvent<EventGCTLABConfiguration>::commit; // else commit() is hidden by overloaded versions in this class

  EventGCTLABConfiguration(
    bool usesTLABs,
    u8 minTLABSize,
    u8 tlabRefillWasteLimit) {
  }

  void commit(bool usesTLABs,
              u8 minTLABSize,
              u8 tlabRefillWasteLimit) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     bool usesTLABs,
                     u8 minTLABSize,
                     u8 tlabRefillWasteLimit) {
  }
};

class EventGCHeapConfiguration : public JfrEvent<EventGCHeapConfiguration>
{
 public:
  EventGCHeapConfiguration(EventStartTime timing=TIMED) {}

  void set_minSize(u8 new_value) {
  }
  void set_maxSize(u8 new_value) {
  }
  void set_initialSize(u8 new_value) {
  }
  void set_usesCompressedOops(bool new_value) {
  }
  void set_compressedOopsMode(u8 new_value) {
  }
  void set_objectAlignment(u8 new_value) {
  }
  void set_heapAddressBits(u1 new_value) {
  }

  using JfrEvent<EventGCHeapConfiguration>::commit; // else commit() is hidden by overloaded versions in this class

  EventGCHeapConfiguration(
    u8 minSize,
    u8 maxSize,
    u8 initialSize,
    bool usesCompressedOops,
    u8 compressedOopsMode,
    u8 objectAlignment,
    u1 heapAddressBits) {
  }

  void commit(u8 minSize,
              u8 maxSize,
              u8 initialSize,
              bool usesCompressedOops,
              u8 compressedOopsMode,
              u8 objectAlignment,
              u1 heapAddressBits) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 minSize,
                     u8 maxSize,
                     u8 initialSize,
                     bool usesCompressedOops,
                     u8 compressedOopsMode,
                     u8 objectAlignment,
                     u1 heapAddressBits) {
  }
};

class EventYoungGenerationConfiguration : public JfrEvent<EventYoungGenerationConfiguration>
{
 public:
  EventYoungGenerationConfiguration(EventStartTime timing=TIMED) {}

  void set_minSize(u8 new_value) {
  }
  void set_maxSize(u8 new_value) {
  }
  void set_newRatio(unsigned new_value) {
  }

  using JfrEvent<EventYoungGenerationConfiguration>::commit; // else commit() is hidden by overloaded versions in this class

  EventYoungGenerationConfiguration(
    u8 minSize,
    u8 maxSize,
    unsigned newRatio) {
  }

  void commit(u8 minSize,
              u8 maxSize,
              unsigned newRatio) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 minSize,
                     u8 maxSize,
                     unsigned newRatio) {
  }
};

class EventZPageAllocation : public JfrEvent<EventZPageAllocation>
{
 public:
  EventZPageAllocation(EventStartTime timing=TIMED) {}

  void set_pageSize(u8 new_value) {
  }
  void set_usedAfter(u8 new_value) {
  }
  void set_freeAfter(u8 new_value) {
  }
  void set_inCacheAfter(u8 new_value) {
  }
  void set_nonBlocking(bool new_value) {
  }
  void set_noReserve(bool new_value) {
  }

  using JfrEvent<EventZPageAllocation>::commit; // else commit() is hidden by overloaded versions in this class

  EventZPageAllocation(
    u8 pageSize,
    u8 usedAfter,
    u8 freeAfter,
    u8 inCacheAfter,
    bool nonBlocking,
    bool noReserve) {
  }

  void commit(u8 pageSize,
              u8 usedAfter,
              u8 freeAfter,
              u8 inCacheAfter,
              bool nonBlocking,
              bool noReserve) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 pageSize,
                     u8 usedAfter,
                     u8 freeAfter,
                     u8 inCacheAfter,
                     bool nonBlocking,
                     bool noReserve) {
  }
};

class EventZThreadPhase : public JfrEvent<EventZThreadPhase>
{
 public:
  EventZThreadPhase(EventStartTime timing=TIMED) {}

  void set_gcId(unsigned new_value) {
  }
  void set_name(const char* new_value) {
  }

  using JfrEvent<EventZThreadPhase>::commit; // else commit() is hidden by overloaded versions in this class

  EventZThreadPhase(
    unsigned gcId,
    const char* name) {
  }

  void commit(unsigned gcId,
              const char* name) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     unsigned gcId,
                     const char* name) {
  }
};

class EventZStatisticsCounter : public JfrEvent<EventZStatisticsCounter>
{
 public:
  EventZStatisticsCounter(EventStartTime timing=TIMED) {}

  void set_id(u8 new_value) {
  }
  void set_increment(u8 new_value) {
  }
  void set_value(u8 new_value) {
  }

  using JfrEvent<EventZStatisticsCounter>::commit; // else commit() is hidden by overloaded versions in this class

  EventZStatisticsCounter(
    u8 id,
    u8 increment,
    u8 value) {
  }

  void commit(u8 id,
              u8 increment,
              u8 value) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 id,
                     u8 increment,
                     u8 value) {
  }
};

class EventZStatisticsSampler : public JfrEvent<EventZStatisticsSampler>
{
 public:
  EventZStatisticsSampler(EventStartTime timing=TIMED) {}

  void set_id(u8 new_value) {
  }
  void set_value(u8 new_value) {
  }

  using JfrEvent<EventZStatisticsSampler>::commit; // else commit() is hidden by overloaded versions in this class

  EventZStatisticsSampler(
    u8 id,
    u8 value) {
  }

  void commit(u8 id,
              u8 value) {
  }

  static void commit(const Ticks& startTicks,
                     const Ticks& endTicks,
                     u8 id,
                     u8 value) {
  }
};



#endif // INCLUDE_JFR
#endif // JFRFILES_JFREVENTCLASSES_HPP
