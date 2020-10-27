// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: common.proto

#ifndef PROTOBUF_INCLUDED_common_2eproto
#define PROTOBUF_INCLUDED_common_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_common_2eproto 

namespace protobuf_common_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[4];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_common_2eproto
namespace fira_message {
class Ball;
class BallDefaultTypeInternal;
extern BallDefaultTypeInternal _Ball_default_instance_;
class Field;
class FieldDefaultTypeInternal;
extern FieldDefaultTypeInternal _Field_default_instance_;
class Frame;
class FrameDefaultTypeInternal;
extern FrameDefaultTypeInternal _Frame_default_instance_;
class Robot;
class RobotDefaultTypeInternal;
extern RobotDefaultTypeInternal _Robot_default_instance_;
}  // namespace fira_message
namespace google {
namespace protobuf {
template<> ::fira_message::Ball* Arena::CreateMaybeMessage<::fira_message::Ball>(Arena*);
template<> ::fira_message::Field* Arena::CreateMaybeMessage<::fira_message::Field>(Arena*);
template<> ::fira_message::Frame* Arena::CreateMaybeMessage<::fira_message::Frame>(Arena*);
template<> ::fira_message::Robot* Arena::CreateMaybeMessage<::fira_message::Robot>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace fira_message {

// ===================================================================

class Ball : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:fira_message.Ball) */ {
 public:
  Ball();
  virtual ~Ball();

  Ball(const Ball& from);

  inline Ball& operator=(const Ball& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Ball(Ball&& from) noexcept
    : Ball() {
    *this = ::std::move(from);
  }

  inline Ball& operator=(Ball&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Ball& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Ball* internal_default_instance() {
    return reinterpret_cast<const Ball*>(
               &_Ball_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Ball* other);
  friend void swap(Ball& a, Ball& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Ball* New() const final {
    return CreateMaybeMessage<Ball>(NULL);
  }

  Ball* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Ball>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Ball& from);
  void MergeFrom(const Ball& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Ball* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // double x = 1;
  void clear_x();
  static const int kXFieldNumber = 1;
  double x() const;
  void set_x(double value);

  // double y = 2;
  void clear_y();
  static const int kYFieldNumber = 2;
  double y() const;
  void set_y(double value);

  // double z = 3;
  void clear_z();
  static const int kZFieldNumber = 3;
  double z() const;
  void set_z(double value);

  // double vx = 4;
  void clear_vx();
  static const int kVxFieldNumber = 4;
  double vx() const;
  void set_vx(double value);

  // double vy = 5;
  void clear_vy();
  static const int kVyFieldNumber = 5;
  double vy() const;
  void set_vy(double value);

  // double vz = 6;
  void clear_vz();
  static const int kVzFieldNumber = 6;
  double vz() const;
  void set_vz(double value);

  // @@protoc_insertion_point(class_scope:fira_message.Ball)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  double x_;
  double y_;
  double z_;
  double vx_;
  double vy_;
  double vz_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_common_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Robot : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:fira_message.Robot) */ {
 public:
  Robot();
  virtual ~Robot();

  Robot(const Robot& from);

  inline Robot& operator=(const Robot& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Robot(Robot&& from) noexcept
    : Robot() {
    *this = ::std::move(from);
  }

  inline Robot& operator=(Robot&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Robot& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Robot* internal_default_instance() {
    return reinterpret_cast<const Robot*>(
               &_Robot_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(Robot* other);
  friend void swap(Robot& a, Robot& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Robot* New() const final {
    return CreateMaybeMessage<Robot>(NULL);
  }

  Robot* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Robot>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Robot& from);
  void MergeFrom(const Robot& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Robot* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // double x = 2;
  void clear_x();
  static const int kXFieldNumber = 2;
  double x() const;
  void set_x(double value);

  // double y = 3;
  void clear_y();
  static const int kYFieldNumber = 3;
  double y() const;
  void set_y(double value);

  // double orientation = 4;
  void clear_orientation();
  static const int kOrientationFieldNumber = 4;
  double orientation() const;
  void set_orientation(double value);

  // double vx = 5;
  void clear_vx();
  static const int kVxFieldNumber = 5;
  double vx() const;
  void set_vx(double value);

  // double vy = 6;
  void clear_vy();
  static const int kVyFieldNumber = 6;
  double vy() const;
  void set_vy(double value);

  // double vorientation = 7;
  void clear_vorientation();
  static const int kVorientationFieldNumber = 7;
  double vorientation() const;
  void set_vorientation(double value);

  // uint32 robot_id = 1;
  void clear_robot_id();
  static const int kRobotIdFieldNumber = 1;
  ::google::protobuf::uint32 robot_id() const;
  void set_robot_id(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:fira_message.Robot)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  double x_;
  double y_;
  double orientation_;
  double vx_;
  double vy_;
  double vorientation_;
  ::google::protobuf::uint32 robot_id_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_common_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Field : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:fira_message.Field) */ {
 public:
  Field();
  virtual ~Field();

  Field(const Field& from);

  inline Field& operator=(const Field& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Field(Field&& from) noexcept
    : Field() {
    *this = ::std::move(from);
  }

  inline Field& operator=(Field&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Field& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Field* internal_default_instance() {
    return reinterpret_cast<const Field*>(
               &_Field_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void Swap(Field* other);
  friend void swap(Field& a, Field& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Field* New() const final {
    return CreateMaybeMessage<Field>(NULL);
  }

  Field* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Field>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Field& from);
  void MergeFrom(const Field& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Field* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // double width = 1;
  void clear_width();
  static const int kWidthFieldNumber = 1;
  double width() const;
  void set_width(double value);

  // double length = 2;
  void clear_length();
  static const int kLengthFieldNumber = 2;
  double length() const;
  void set_length(double value);

  // double goal_width = 3;
  void clear_goal_width();
  static const int kGoalWidthFieldNumber = 3;
  double goal_width() const;
  void set_goal_width(double value);

  // double goal_depth = 4;
  void clear_goal_depth();
  static const int kGoalDepthFieldNumber = 4;
  double goal_depth() const;
  void set_goal_depth(double value);

  // @@protoc_insertion_point(class_scope:fira_message.Field)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  double width_;
  double length_;
  double goal_width_;
  double goal_depth_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_common_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Frame : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:fira_message.Frame) */ {
 public:
  Frame();
  virtual ~Frame();

  Frame(const Frame& from);

  inline Frame& operator=(const Frame& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Frame(Frame&& from) noexcept
    : Frame() {
    *this = ::std::move(from);
  }

  inline Frame& operator=(Frame&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Frame& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Frame* internal_default_instance() {
    return reinterpret_cast<const Frame*>(
               &_Frame_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  void Swap(Frame* other);
  friend void swap(Frame& a, Frame& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Frame* New() const final {
    return CreateMaybeMessage<Frame>(NULL);
  }

  Frame* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Frame>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Frame& from);
  void MergeFrom(const Frame& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Frame* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .fira_message.Robot robots_yellow = 2;
  int robots_yellow_size() const;
  void clear_robots_yellow();
  static const int kRobotsYellowFieldNumber = 2;
  ::fira_message::Robot* mutable_robots_yellow(int index);
  ::google::protobuf::RepeatedPtrField< ::fira_message::Robot >*
      mutable_robots_yellow();
  const ::fira_message::Robot& robots_yellow(int index) const;
  ::fira_message::Robot* add_robots_yellow();
  const ::google::protobuf::RepeatedPtrField< ::fira_message::Robot >&
      robots_yellow() const;

  // repeated .fira_message.Robot robots_blue = 3;
  int robots_blue_size() const;
  void clear_robots_blue();
  static const int kRobotsBlueFieldNumber = 3;
  ::fira_message::Robot* mutable_robots_blue(int index);
  ::google::protobuf::RepeatedPtrField< ::fira_message::Robot >*
      mutable_robots_blue();
  const ::fira_message::Robot& robots_blue(int index) const;
  ::fira_message::Robot* add_robots_blue();
  const ::google::protobuf::RepeatedPtrField< ::fira_message::Robot >&
      robots_blue() const;

  // .fira_message.Ball ball = 1;
  bool has_ball() const;
  void clear_ball();
  static const int kBallFieldNumber = 1;
  private:
  const ::fira_message::Ball& _internal_ball() const;
  public:
  const ::fira_message::Ball& ball() const;
  ::fira_message::Ball* release_ball();
  ::fira_message::Ball* mutable_ball();
  void set_allocated_ball(::fira_message::Ball* ball);

  // @@protoc_insertion_point(class_scope:fira_message.Frame)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::fira_message::Robot > robots_yellow_;
  ::google::protobuf::RepeatedPtrField< ::fira_message::Robot > robots_blue_;
  ::fira_message::Ball* ball_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_common_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Ball

// double x = 1;
inline void Ball::clear_x() {
  x_ = 0;
}
inline double Ball::x() const {
  // @@protoc_insertion_point(field_get:fira_message.Ball.x)
  return x_;
}
inline void Ball::set_x(double value) {
  
  x_ = value;
  // @@protoc_insertion_point(field_set:fira_message.Ball.x)
}

// double y = 2;
inline void Ball::clear_y() {
  y_ = 0;
}
inline double Ball::y() const {
  // @@protoc_insertion_point(field_get:fira_message.Ball.y)
  return y_;
}
inline void Ball::set_y(double value) {
  
  y_ = value;
  // @@protoc_insertion_point(field_set:fira_message.Ball.y)
}

// double z = 3;
inline void Ball::clear_z() {
  z_ = 0;
}
inline double Ball::z() const {
  // @@protoc_insertion_point(field_get:fira_message.Ball.z)
  return z_;
}
inline void Ball::set_z(double value) {
  
  z_ = value;
  // @@protoc_insertion_point(field_set:fira_message.Ball.z)
}

// double vx = 4;
inline void Ball::clear_vx() {
  vx_ = 0;
}
inline double Ball::vx() const {
  // @@protoc_insertion_point(field_get:fira_message.Ball.vx)
  return vx_;
}
inline void Ball::set_vx(double value) {
  
  vx_ = value;
  // @@protoc_insertion_point(field_set:fira_message.Ball.vx)
}

// double vy = 5;
inline void Ball::clear_vy() {
  vy_ = 0;
}
inline double Ball::vy() const {
  // @@protoc_insertion_point(field_get:fira_message.Ball.vy)
  return vy_;
}
inline void Ball::set_vy(double value) {
  
  vy_ = value;
  // @@protoc_insertion_point(field_set:fira_message.Ball.vy)
}

// double vz = 6;
inline void Ball::clear_vz() {
  vz_ = 0;
}
inline double Ball::vz() const {
  // @@protoc_insertion_point(field_get:fira_message.Ball.vz)
  return vz_;
}
inline void Ball::set_vz(double value) {
  
  vz_ = value;
  // @@protoc_insertion_point(field_set:fira_message.Ball.vz)
}

// -------------------------------------------------------------------

// Robot

// uint32 robot_id = 1;
inline void Robot::clear_robot_id() {
  robot_id_ = 0u;
}
inline ::google::protobuf::uint32 Robot::robot_id() const {
  // @@protoc_insertion_point(field_get:fira_message.Robot.robot_id)
  return robot_id_;
}
inline void Robot::set_robot_id(::google::protobuf::uint32 value) {
  
  robot_id_ = value;
  // @@protoc_insertion_point(field_set:fira_message.Robot.robot_id)
}

// double x = 2;
inline void Robot::clear_x() {
  x_ = 0;
}
inline double Robot::x() const {
  // @@protoc_insertion_point(field_get:fira_message.Robot.x)
  return x_;
}
inline void Robot::set_x(double value) {
  
  x_ = value;
  // @@protoc_insertion_point(field_set:fira_message.Robot.x)
}

// double y = 3;
inline void Robot::clear_y() {
  y_ = 0;
}
inline double Robot::y() const {
  // @@protoc_insertion_point(field_get:fira_message.Robot.y)
  return y_;
}
inline void Robot::set_y(double value) {
  
  y_ = value;
  // @@protoc_insertion_point(field_set:fira_message.Robot.y)
}

// double orientation = 4;
inline void Robot::clear_orientation() {
  orientation_ = 0;
}
inline double Robot::orientation() const {
  // @@protoc_insertion_point(field_get:fira_message.Robot.orientation)
  return orientation_;
}
inline void Robot::set_orientation(double value) {
  
  orientation_ = value;
  // @@protoc_insertion_point(field_set:fira_message.Robot.orientation)
}

// double vx = 5;
inline void Robot::clear_vx() {
  vx_ = 0;
}
inline double Robot::vx() const {
  // @@protoc_insertion_point(field_get:fira_message.Robot.vx)
  return vx_;
}
inline void Robot::set_vx(double value) {
  
  vx_ = value;
  // @@protoc_insertion_point(field_set:fira_message.Robot.vx)
}

// double vy = 6;
inline void Robot::clear_vy() {
  vy_ = 0;
}
inline double Robot::vy() const {
  // @@protoc_insertion_point(field_get:fira_message.Robot.vy)
  return vy_;
}
inline void Robot::set_vy(double value) {
  
  vy_ = value;
  // @@protoc_insertion_point(field_set:fira_message.Robot.vy)
}

// double vorientation = 7;
inline void Robot::clear_vorientation() {
  vorientation_ = 0;
}
inline double Robot::vorientation() const {
  // @@protoc_insertion_point(field_get:fira_message.Robot.vorientation)
  return vorientation_;
}
inline void Robot::set_vorientation(double value) {
  
  vorientation_ = value;
  // @@protoc_insertion_point(field_set:fira_message.Robot.vorientation)
}

// -------------------------------------------------------------------

// Field

// double width = 1;
inline void Field::clear_width() {
  width_ = 0;
}
inline double Field::width() const {
  // @@protoc_insertion_point(field_get:fira_message.Field.width)
  return width_;
}
inline void Field::set_width(double value) {
  
  width_ = value;
  // @@protoc_insertion_point(field_set:fira_message.Field.width)
}

// double length = 2;
inline void Field::clear_length() {
  length_ = 0;
}
inline double Field::length() const {
  // @@protoc_insertion_point(field_get:fira_message.Field.length)
  return length_;
}
inline void Field::set_length(double value) {
  
  length_ = value;
  // @@protoc_insertion_point(field_set:fira_message.Field.length)
}

// double goal_width = 3;
inline void Field::clear_goal_width() {
  goal_width_ = 0;
}
inline double Field::goal_width() const {
  // @@protoc_insertion_point(field_get:fira_message.Field.goal_width)
  return goal_width_;
}
inline void Field::set_goal_width(double value) {
  
  goal_width_ = value;
  // @@protoc_insertion_point(field_set:fira_message.Field.goal_width)
}

// double goal_depth = 4;
inline void Field::clear_goal_depth() {
  goal_depth_ = 0;
}
inline double Field::goal_depth() const {
  // @@protoc_insertion_point(field_get:fira_message.Field.goal_depth)
  return goal_depth_;
}
inline void Field::set_goal_depth(double value) {
  
  goal_depth_ = value;
  // @@protoc_insertion_point(field_set:fira_message.Field.goal_depth)
}

// -------------------------------------------------------------------

// Frame

// .fira_message.Ball ball = 1;
inline bool Frame::has_ball() const {
  return this != internal_default_instance() && ball_ != NULL;
}
inline void Frame::clear_ball() {
  if (GetArenaNoVirtual() == NULL && ball_ != NULL) {
    delete ball_;
  }
  ball_ = NULL;
}
inline const ::fira_message::Ball& Frame::_internal_ball() const {
  return *ball_;
}
inline const ::fira_message::Ball& Frame::ball() const {
  const ::fira_message::Ball* p = ball_;
  // @@protoc_insertion_point(field_get:fira_message.Frame.ball)
  return p != NULL ? *p : *reinterpret_cast<const ::fira_message::Ball*>(
      &::fira_message::_Ball_default_instance_);
}
inline ::fira_message::Ball* Frame::release_ball() {
  // @@protoc_insertion_point(field_release:fira_message.Frame.ball)
  
  ::fira_message::Ball* temp = ball_;
  ball_ = NULL;
  return temp;
}
inline ::fira_message::Ball* Frame::mutable_ball() {
  
  if (ball_ == NULL) {
    auto* p = CreateMaybeMessage<::fira_message::Ball>(GetArenaNoVirtual());
    ball_ = p;
  }
  // @@protoc_insertion_point(field_mutable:fira_message.Frame.ball)
  return ball_;
}
inline void Frame::set_allocated_ball(::fira_message::Ball* ball) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete ball_;
  }
  if (ball) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      ball = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, ball, submessage_arena);
    }
    
  } else {
    
  }
  ball_ = ball;
  // @@protoc_insertion_point(field_set_allocated:fira_message.Frame.ball)
}

// repeated .fira_message.Robot robots_yellow = 2;
inline int Frame::robots_yellow_size() const {
  return robots_yellow_.size();
}
inline void Frame::clear_robots_yellow() {
  robots_yellow_.Clear();
}
inline ::fira_message::Robot* Frame::mutable_robots_yellow(int index) {
  // @@protoc_insertion_point(field_mutable:fira_message.Frame.robots_yellow)
  return robots_yellow_.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField< ::fira_message::Robot >*
Frame::mutable_robots_yellow() {
  // @@protoc_insertion_point(field_mutable_list:fira_message.Frame.robots_yellow)
  return &robots_yellow_;
}
inline const ::fira_message::Robot& Frame::robots_yellow(int index) const {
  // @@protoc_insertion_point(field_get:fira_message.Frame.robots_yellow)
  return robots_yellow_.Get(index);
}
inline ::fira_message::Robot* Frame::add_robots_yellow() {
  // @@protoc_insertion_point(field_add:fira_message.Frame.robots_yellow)
  return robots_yellow_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::fira_message::Robot >&
Frame::robots_yellow() const {
  // @@protoc_insertion_point(field_list:fira_message.Frame.robots_yellow)
  return robots_yellow_;
}

// repeated .fira_message.Robot robots_blue = 3;
inline int Frame::robots_blue_size() const {
  return robots_blue_.size();
}
inline void Frame::clear_robots_blue() {
  robots_blue_.Clear();
}
inline ::fira_message::Robot* Frame::mutable_robots_blue(int index) {
  // @@protoc_insertion_point(field_mutable:fira_message.Frame.robots_blue)
  return robots_blue_.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField< ::fira_message::Robot >*
Frame::mutable_robots_blue() {
  // @@protoc_insertion_point(field_mutable_list:fira_message.Frame.robots_blue)
  return &robots_blue_;
}
inline const ::fira_message::Robot& Frame::robots_blue(int index) const {
  // @@protoc_insertion_point(field_get:fira_message.Frame.robots_blue)
  return robots_blue_.Get(index);
}
inline ::fira_message::Robot* Frame::add_robots_blue() {
  // @@protoc_insertion_point(field_add:fira_message.Frame.robots_blue)
  return robots_blue_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::fira_message::Robot >&
Frame::robots_blue() const {
  // @@protoc_insertion_point(field_list:fira_message.Frame.robots_blue)
  return robots_blue_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace fira_message

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_common_2eproto
