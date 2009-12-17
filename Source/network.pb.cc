// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "network.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>

namespace network {

namespace {

const ::google::protobuf::Descriptor* Player_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Player_reflection_ = NULL;
const ::google::protobuf::Descriptor* Player_Pet_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Player_Pet_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* Player_ClassType_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* Player_PetType_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_network_2eproto() {
  protobuf_AddDesc_network_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "network.proto");
  GOOGLE_CHECK(file != NULL);
  Player_descriptor_ = file->message_type(0);
  static const int Player_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Player, name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Player, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Player, type_),
  };
  Player_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Player_descriptor_,
      Player::default_instance_,
      Player_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Player, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Player, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Player));
  Player_Pet_descriptor_ = Player_descriptor_->nested_type(0);
  static const int Player_Pet_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Player_Pet, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Player_Pet, type_),
  };
  Player_Pet_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Player_Pet_descriptor_,
      Player_Pet::default_instance_,
      Player_Pet_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Player_Pet, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Player_Pet, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Player_Pet));
  Player_ClassType_descriptor_ = Player_descriptor_->enum_type(0);
  Player_PetType_descriptor_ = Player_descriptor_->enum_type(1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_network_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Player_descriptor_, &Player::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Player_Pet_descriptor_, &Player_Pet::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_network_2eproto() {
  delete Player::default_instance_;
  delete Player_reflection_;
  delete Player_Pet::default_instance_;
  delete Player_Pet_reflection_;
}

void protobuf_AddDesc_network_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\rnetwork.proto\022\007network\"\335\001\n\006Player\022\014\n\004n"
    "ame\030\001 \002(\t\022\n\n\002id\030\002 \002(\003\022\'\n\004type\030\003 \002(\0162\031.ne"
    "twork.Player.ClassType\0328\n\003Pet\022\n\n\002id\030\001 \002("
    "\003\022%\n\004type\030\002 \002(\0162\027.network.Player.PetType"
    "\"9\n\tClassType\022\r\n\tALCHEMIST\020\000\022\016\n\nVANQUISH"
    "ER\020\001\022\r\n\tDESTROYER\020\002\"\033\n\007PetType\022\007\n\003DOG\020\000\022"
    "\007\n\003CAT\020\001", 248);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "network.proto", &protobuf_RegisterTypes);
  Player::default_instance_ = new Player();
  Player_Pet::default_instance_ = new Player_Pet();
  Player::default_instance_->InitAsDefaultInstance();
  Player_Pet::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_network_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_network_2eproto {
  StaticDescriptorInitializer_network_2eproto() {
    protobuf_AddDesc_network_2eproto();
  }
} static_descriptor_initializer_network_2eproto_;


// ===================================================================

const ::google::protobuf::EnumDescriptor* Player_ClassType_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Player_ClassType_descriptor_;
}
bool Player_ClassType_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const Player_ClassType Player::ALCHEMIST;
const Player_ClassType Player::VANQUISHER;
const Player_ClassType Player::DESTROYER;
const Player_ClassType Player::ClassType_MIN;
const Player_ClassType Player::ClassType_MAX;
#endif  // _MSC_VER
const ::google::protobuf::EnumDescriptor* Player_PetType_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Player_PetType_descriptor_;
}
bool Player_PetType_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const Player_PetType Player::DOG;
const Player_PetType Player::CAT;
const Player_PetType Player::PetType_MIN;
const Player_PetType Player::PetType_MAX;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int Player_Pet::kIdFieldNumber;
const int Player_Pet::kTypeFieldNumber;
#endif  // !_MSC_VER

Player_Pet::Player_Pet() {
  SharedCtor();
}

void Player_Pet::InitAsDefaultInstance() {
}

Player_Pet::Player_Pet(const Player_Pet& from) {
  SharedCtor();
  MergeFrom(from);
}

void Player_Pet::SharedCtor() {
  _cached_size_ = 0;
  id_ = GOOGLE_LONGLONG(0);
  type_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Player_Pet::~Player_Pet() {
  SharedDtor();
}

void Player_Pet::SharedDtor() {
  if (this != default_instance_) {
  }
}

const ::google::protobuf::Descriptor* Player_Pet::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Player_Pet_descriptor_;
}

const Player_Pet& Player_Pet::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_network_2eproto();  return *default_instance_;
}

Player_Pet* Player_Pet::default_instance_ = NULL;

Player_Pet* Player_Pet::New() const {
  return new Player_Pet;
}

void Player_Pet::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    id_ = GOOGLE_LONGLONG(0);
    type_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Player_Pet::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int64 id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) !=
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          goto handle_uninterpreted;
        }
        DO_(::google::protobuf::internal::WireFormatLite::ReadInt64(
              input, &id_));
        _set_bit(0);
        if (input->ExpectTag(16)) goto parse_type;
        break;
      }
      
      // required .network.Player.PetType type = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) !=
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          goto handle_uninterpreted;
        }
       parse_type:
        int value;
        DO_(::google::protobuf::internal::WireFormatLite::ReadEnum(input, &value));
        if (::network::Player_PetType_IsValid(value)) {
          set_type(static_cast< ::network::Player_PetType >(value));
        } else {
          mutable_unknown_fields()->AddVarint(2, value);
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Player_Pet::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  ::google::protobuf::uint8* raw_buffer = output->GetDirectBufferForNBytesAndAdvance(_cached_size_);
  if (raw_buffer != NULL) {
    Player_Pet::SerializeWithCachedSizesToArray(raw_buffer);
    return;
  }
  
  // required int64 id = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->id(), output);
  }
  
  // required .network.Player.PetType type = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      2, this->type(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Player_Pet::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required int64 id = 1;
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(1, this->id(), target);
  }
  
  // required .network.Player.PetType type = 2;
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      2, this->type(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Player_Pet::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int64 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int64Size(
          this->id());
    }
    
    // required .network.Player.PetType type = 2;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->type());
    }
    
  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  _cached_size_ = total_size;
  return total_size;
}

void Player_Pet::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Player_Pet* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Player_Pet*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Player_Pet::MergeFrom(const Player_Pet& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_id(from.id());
    }
    if (from._has_bit(1)) {
      set_type(from.type());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Player_Pet::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Player_Pet::CopyFrom(const Player_Pet& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Player_Pet::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  
  return true;
}

void Player_Pet::Swap(Player_Pet* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(type_, other->type_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Player_Pet::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Player_Pet_descriptor_;
  metadata.reflection = Player_Pet_reflection_;
  return metadata;
}


// -------------------------------------------------------------------

const ::std::string Player::_default_name_;
#ifndef _MSC_VER
const int Player::kNameFieldNumber;
const int Player::kIdFieldNumber;
const int Player::kTypeFieldNumber;
#endif  // !_MSC_VER

Player::Player() {
  SharedCtor();
}

void Player::InitAsDefaultInstance() {
}

Player::Player(const Player& from) {
  SharedCtor();
  MergeFrom(from);
}

void Player::SharedCtor() {
  _cached_size_ = 0;
  name_ = const_cast< ::std::string*>(&_default_name_);
  id_ = GOOGLE_LONGLONG(0);
  type_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Player::~Player() {
  SharedDtor();
}

void Player::SharedDtor() {
  if (name_ != &_default_name_) {
    delete name_;
  }
  if (this != default_instance_) {
  }
}

const ::google::protobuf::Descriptor* Player::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Player_descriptor_;
}

const Player& Player::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_network_2eproto();  return *default_instance_;
}

Player* Player::default_instance_ = NULL;

Player* Player::New() const {
  return new Player;
}

void Player::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (_has_bit(0)) {
      if (name_ != &_default_name_) {
        name_->clear();
      }
    }
    id_ = GOOGLE_LONGLONG(0);
    type_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Player::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string name = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) !=
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          goto handle_uninterpreted;
        }
        DO_(::google::protobuf::internal::WireFormatLite::ReadString(
              input, this->mutable_name()));
        ::google::protobuf::internal::WireFormat::VerifyUTF8String(
          this->name().data(), this->name().length(),
          ::google::protobuf::internal::WireFormat::PARSE);
        if (input->ExpectTag(16)) goto parse_id;
        break;
      }
      
      // required int64 id = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) !=
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          goto handle_uninterpreted;
        }
       parse_id:
        DO_(::google::protobuf::internal::WireFormatLite::ReadInt64(
              input, &id_));
        _set_bit(1);
        if (input->ExpectTag(24)) goto parse_type;
        break;
      }
      
      // required .network.Player.ClassType type = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) !=
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          goto handle_uninterpreted;
        }
       parse_type:
        int value;
        DO_(::google::protobuf::internal::WireFormatLite::ReadEnum(input, &value));
        if (::network::Player_ClassType_IsValid(value)) {
          set_type(static_cast< ::network::Player_ClassType >(value));
        } else {
          mutable_unknown_fields()->AddVarint(3, value);
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Player::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  ::google::protobuf::uint8* raw_buffer = output->GetDirectBufferForNBytesAndAdvance(_cached_size_);
  if (raw_buffer != NULL) {
    Player::SerializeWithCachedSizesToArray(raw_buffer);
    return;
  }
  
  // required string name = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->name(), output);
  }
  
  // required int64 id = 2;
  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(2, this->id(), output);
  }
  
  // required .network.Player.ClassType type = 3;
  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      3, this->type(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Player::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required string name = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->name(), target);
  }
  
  // required int64 id = 2;
  if (_has_bit(1)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(2, this->id(), target);
  }
  
  // required .network.Player.ClassType type = 3;
  if (_has_bit(2)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      3, this->type(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Player::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string name = 1;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }
    
    // required int64 id = 2;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int64Size(
          this->id());
    }
    
    // required .network.Player.ClassType type = 3;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->type());
    }
    
  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  _cached_size_ = total_size;
  return total_size;
}

void Player::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Player* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Player*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Player::MergeFrom(const Player& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_name(from.name());
    }
    if (from._has_bit(1)) {
      set_id(from.id());
    }
    if (from._has_bit(2)) {
      set_type(from.type());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Player::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Player::CopyFrom(const Player& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Player::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;
  
  return true;
}

void Player::Swap(Player* other) {
  if (other != this) {
    std::swap(name_, other->name_);
    std::swap(id_, other->id_);
    std::swap(type_, other->type_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Player::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Player_descriptor_;
  metadata.reflection = Player_reflection_;
  return metadata;
}


}  // namespace network
