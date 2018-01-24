/** i2cp public api */
#ifndef LIBI2CP_H_
#define LIBI2CP_H_

#include <sys/types.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

  struct i2cp_client;

  struct i2cp_client * new_i2cp_client(struct sockaddr * addr);
  void free_i2cp_client(struct i2cp_client * cl);

  struct i2cp_message
  {
    uint16_t srcport;
    uint16_t dstport;
    uint16_t protocol;
    uint8_t * payload_ptr;
    size_t payload_sz;
  };



  struct i2cp_session_config;

  struct i2cp_session_config * new_i2cp_session_config();
  void free_i2cp_session_config(struct i2cp_session_config * conf);

  void i2cp_session_config_set(struct i2cp_session_config * conf, const char * key, const char * val);
  bool i2cp_session_config_get(struct i2cp_session_config * conf, const char * key, char ** val);

  struct i2cp_session_config * copy_i2cp_session_config(struct i2cp_session_config * conf);
  
  struct i2cp_session;

  struct i2cp_session * i2cp_new_session(struct i2cp_client * cl, struct i2cp_session_config * config);

/** caller must free result */
  char * i2cp_session_addr(struct i2cp_session * s);
/** caller must free result */
  char * i2cp_session_addr_b32(struct i2cp_session * s);

  typedef void (*i2cp_msg_sendhandler)(struct i2cp_session *, void *);

/** send an i2cp message */
  int i2cp_sendmsg(struct i2cp_session * s, struct i2cp_message msg, void * user, i2cp_msg_sendhandler handler);

  typedef void (*i2cp_msg_recvhandler)(struct i2cp_session *, struct i2cp_message *, void *);

  int i2cp_set_recv_handler(struct i2cp_session * s, void * user, i2cp_msg_recvhandler hanadler);

  typedef void (*i2cp_lookup_handler)(struct i2cp_session *, void *, const char *);

  void i2cp_lookup_async(struct i2cp_session * s, const char * name, void * user, i2cp_lookup_handler handler);

  void i2cp_mainloop(struct i2cp_client * cl);

  void free_i2cp_session(struct i2cp_session * s);

#ifdef __cplusplus
}
#endif

#endif
