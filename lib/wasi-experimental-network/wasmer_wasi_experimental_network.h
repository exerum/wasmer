#ifndef WASMER_WASI_EXPERIMENTAL_NETWORK
#define WASMER_WASI_EXPERIMENTAL_NETWORK

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint32_t __wasi_errno_t;

typedef uint32_t __wasi_poll_t;

typedef uint32_t __wasi_fd_t;

typedef uint32_t __wasi_poll_token_t;

typedef struct __wasi_poll_event_t {
  __wasi_poll_token_t token;
  bool readable;
  bool writable;
} __wasi_poll_event_t;

/**
 * The _domain_ specifies a communication domain; this selects the
 * protocol family which will be used for communication.
 *
 * It uses `i32` which is the equivalent of `int` in C, which is the
 * typed used by `socket(2)` for the `domain` argument.
 */
typedef int32_t __wasi_socket_domain_t;

/**
 * The `sockaddr_in` struct.
 */
typedef struct __wasi_socket_address_in_t {
  __wasi_socket_domain_t family;
  uint8_t address[4];
  uint16_t port;
} __wasi_socket_address_in_t;

/**
 * The `sockaddr_in6` struct.
 */
typedef struct __wasi_socket_address_in6_t {
  uint16_t sin6_family;
  uint16_t sin6_port;
  uint32_t sin6_flowinfo;
  uint8_t sin6_addr[16];
  uint32_t sin6_scope_id;
} __wasi_socket_address_in6_t;

/**
 * A type with the same memory layout as `libc::sockaddr`.
 * An union around `sockaddr_in` and `sockaddr_in6`.
 */
typedef union __wasi_socket_address_t {
  struct __wasi_socket_address_in_t v4;
  struct __wasi_socket_address_in6_t v6;
} __wasi_socket_address_t;

/**
 * A socket has an indicated _type_, which specifies the
 * communication semantics.
 *
 * It uses `i32` which is the equivalent of `int` in C, which is the
 * typed used by `socket(2)` for the `type` argument.
 */
typedef int32_t __wasi_socket_type_t;

/**
 * The _protocol_ specified a particular protocol to be used with the
 * socket. Normally only a single protocol exists to support a
 * particular socket type within a given protocol family, in which
 * case _protocol_ can be specified as 0 (or [`DEFAULT_PROTOCOL`]
 * here). However, it is possible that many protocols may exist, in
 * which case a particular protocol must be specified in this
 * manner. The protocol number to use is specific to the
 * “communication domain” in which communication is to take place.
 *
 * It uses `i32` which is the equivalent of `int` in C, which is the
 * typed used by `socket(2)` for the `domain` argument.
 */
typedef int32_t __wasi_socket_protocol_t;

typedef struct __wasi_ciovec_t {
  uint32_t buf;
  uint32_t buf_len;
} __wasi_ciovec_t;

typedef uint16_t __wasi_siflags_t;

typedef int32_t __wasi_shutdown_t;

/**
 * IPv4 Internet protocols.
 */
#define AF_INET 1

/**
 * IPv6 Internet protocols.
 */
#define AF_INET6 2

#define AF_PACKET 4

#define AF_UNIX 3

#define AF_VSOCK 5

/**
 * Represents the default protocol, i.e. `0`. See
 * [`__wasi_socket_protocol_t`] to learn more.
 */
#define DEFAULT_PROTOCOL 0

#define ICMPv4 1

#define ICMPv6 2

#define SHUT_RD 1

#define SHUT_RDWR 3

#define SHUT_WR 2

/**
 * Supports datagrams (connectionless, unreliable messages of a fixed
 * maximum length).
 *
 * Implies UDP when used with an IP socket.
 */
#define SOCK_DGRAM 2

#define SOCK_RAW 4

#define SOCK_SEQPACKET 3

/**
 * Provides sequenced, reliable, two-way, connection-based byte
 * streams.
 *
 * Implies TCP when used with an IP socket.
 */
#define SOCK_STREAM 1

#define TCP 3

#define UDP 4

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

extern __wasi_errno_t poller_add(__wasi_poll_t poll,
                                 __wasi_fd_t fd,
                                 struct __wasi_poll_event_t event);

extern __wasi_errno_t poller_create(__wasi_poll_t *poll_out);

extern __wasi_errno_t poller_delete(__wasi_poll_t poll, __wasi_fd_t fd);

extern __wasi_errno_t poller_modify(__wasi_poll_t poll,
                                    __wasi_fd_t fd,
                                    struct __wasi_poll_event_t event);

extern __wasi_errno_t poller_wait(__wasi_poll_t poll,
                                  struct __wasi_poll_event_t *events,
                                  uint32_t events_size,
                                  uint32_t *events_size_out);

/**
 * The `socket_accept` function is used with connection-based
 * socket types (e.g. [`SOCK_STREAM`]). It extracts the first
 * connection request on the queue of pending connections for the
 * listening socket, `fd`, creates a new connected socket, and
 * returns a new file descriptor referring to that socket in
 * `remote_fd`. The newly created socket is not in the listening
 * state. The original socket `fd` is unaffected by this call.
 *
 * The argument `fd` is a socket that has been created with
 * [`socket_create`], bound to a local address with
 * [`socket_bind`], and is listening for connections after a
 * [`socket_listen`].
 *
 * The argument `address` is a pointer to an address (see
 * [`SocketAddress`] and [`SocketAddress6`]). This structure is
 * filled in with the address of the peer socket, as known to the
 * communications layer. The exact format of the address returned
 * `address` is determined by the socket's address family (see
 * [`socket_create`]). When `address` is `null`, nothing is
 * filled in; in this case, `address_size` is not used, and
 * should also be `null`.
 */
extern __wasi_errno_t socket_accept(__wasi_fd_t fd,
                                    union __wasi_socket_address_t *remote_address,
                                    __wasi_fd_t *remote_fd);

/**
 * When a socket is created (with [`socket_create`]), it exists
 * in a name space (address family) but has no address assigned
 * to it. `socket_bind` assigns the address specified by
 * `address` (see [`SockAddrIn`] and [`SockAddrIn6`]) to the
 * socket referred to by the file descriptor `fd`. `address_size`
 * specifies the size, in bytes, of the address structure pointed
 * to by `address`. Traditionnaly, this operation is called
 * “assigning a name to a socket”.
 */
extern __wasi_errno_t socket_bind(__wasi_fd_t fd, const union __wasi_socket_address_t *address);

extern __wasi_errno_t socket_close(__wasi_fd_t fd);

/**
 * `socket_create` creates an endpoint for communication.
 */
extern __wasi_errno_t socket_create(__wasi_socket_domain_t domain,
                                    __wasi_socket_type_t ty,
                                    __wasi_socket_protocol_t protocol,
                                    __wasi_fd_t *fd_out);

/**
 * `socket_listen` marks the socket referred to by `fd` as a
 * passive socket, that is, a socket that will be used to accept
 * incoming connection requests using [`socket_accept`].
 *
 * The `backlog` argument defines the maximum length to which the
 * queue of pending connections for `fd` may grow. If a
 * connection request arrives when the queue is full, the client
 * may receive an error or, if the underlying protocol supports
 * retransmission, the request may be ignored so that a later
 * reattempt at connection succeeds.
 */
extern __wasi_errno_t socket_listen(__wasi_fd_t fd, uint32_t backlog);

/**
 * The `socket_recv` function is used to receive messages from a
 * socket referred to by the file descriptor `fd`. This function
 * works like `readv(2)`. It reads `iov_size` buffers from the
 * file associated with the file descriptor `fd` into buffers
 * described by `iov` (“scatter input”).
 *
 * The `iov_flags` represents the “read flags”, represented by
 * `__wasi_siflags_t`.
 *
 * `io_size_out` is filled in by the number of bytes actually
 * read.
 */
extern __wasi_errno_t socket_recv(__wasi_fd_t fd,
                                  struct __wasi_ciovec_t *iov,
                                  uint32_t iov_size,
                                  __wasi_siflags_t iov_flags,
                                  uint32_t *io_size_out);

/**
 * The `socket_send` function is used to transmit a message to
 * another socket referred to by the file descriptor `fd`. This
 * function works like `writev(2)`. It writes `iov_size` buffers
 * of data described by `iov` (I/O vector) to the file associated
 * with the file descriptor `fd` (“gather output”).
 *
 * The `iov_flags` represents the “write flags”, represented by
 * `__wasi_siflags_t`.
 *
 * `io_size_out` is filled in by the number of bytes actually
 * written.
 */
extern __wasi_errno_t socket_send(__wasi_fd_t fd,
                                  const struct __wasi_ciovec_t *iov,
                                  uint32_t iov_size,
                                  __wasi_siflags_t iov_flags,
                                  uint32_t *io_size_out);

extern __wasi_errno_t socket_set_nonblocking(__wasi_fd_t fd, bool nonblocking);

/**
 * The `shutdown` function causes all or part of a full-duplex
 * connection on the socket with `fd` to be shut down.
 */
extern __wasi_errno_t socket_shutdown(__wasi_fd_t fd, __wasi_shutdown_t how);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif /* WASMER_WASI_EXPERIMENTAL_NETWORK */
