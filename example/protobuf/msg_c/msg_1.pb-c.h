/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: msg_1.proto */

#ifndef PROTOBUF_C_msg_5f1_2eproto__INCLUDED
#define PROTOBUF_C_msg_5f1_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003003 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _Msg1 Msg1;


/* --- enums --- */


/* --- messages --- */

struct  _Msg1
{
  ProtobufCMessage base;
  int32_t id;
  char *name;
  int32_t socre;
};
#define MSG_1__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&msg_1__descriptor) \
    , 0, (char *)protobuf_c_empty_string, 0 }


/* Msg1 methods */
void   msg_1__init
                     (Msg1         *message);
size_t msg_1__get_packed_size
                     (const Msg1   *message);
size_t msg_1__pack
                     (const Msg1   *message,
                      uint8_t             *out);
size_t msg_1__pack_to_buffer
                     (const Msg1   *message,
                      ProtobufCBuffer     *buffer);
Msg1 *
       msg_1__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   msg_1__free_unpacked
                     (Msg1 *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Msg1_Closure)
                 (const Msg1 *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor msg_1__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_msg_5f1_2eproto__INCLUDED */
