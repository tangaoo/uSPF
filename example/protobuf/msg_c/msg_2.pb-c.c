/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: msg_2.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "msg_2.pb-c.h"
void   msg_2__init
                     (Msg2         *message)
{
  static const Msg2 init_value = MSG_2__INIT;
  *message = init_value;
}
size_t msg_2__get_packed_size
                     (const Msg2 *message)
{
  assert(message->base.descriptor == &msg_2__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t msg_2__pack
                     (const Msg2 *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &msg_2__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t msg_2__pack_to_buffer
                     (const Msg2 *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &msg_2__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Msg2 *
       msg_2__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Msg2 *)
     protobuf_c_message_unpack (&msg_2__descriptor,
                                allocator, len, data);
}
void   msg_2__free_unpacked
                     (Msg2 *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &msg_2__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor msg_2__field_descriptors[3] =
{
  {
    "id",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Msg2, id),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "name",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Msg2, name),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "socre",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Msg2, socre),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned msg_2__field_indices_by_name[] = {
  0,   /* field[0] = id */
  1,   /* field[1] = name */
  2,   /* field[2] = socre */
};
static const ProtobufCIntRange msg_2__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor msg_2__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "msg_2",
  "Msg2",
  "Msg2",
  "",
  sizeof(Msg2),
  3,
  msg_2__field_descriptors,
  msg_2__field_indices_by_name,
  1,  msg_2__number_ranges,
  (ProtobufCMessageInit) msg_2__init,
  NULL,NULL,NULL    /* reserved[123] */
};
