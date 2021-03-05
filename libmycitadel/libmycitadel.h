#ifndef libmycitadel_h
#define libmycitadel_h

/* Generated with cbindgen:0.16.0 */

/* Warning, this file is autogenerated by cbindgen. Don't modify this manually. */

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define BECH32_OK 0

#define BECH32_ERR_HRP 1

#define BECH32_ERR_CHECKSUM 2

#define BECH32_ERR_ENCODING 3

#define BECH32_ERR_PAYLOAD 4

#define BECH32_ERR_UNSUPPORTED 5

#define BECH32_ERR_INTERNAL 6

#define BECH32_ERR_NULL 7

#define BECH32_UNKNOWN 0

#define BECH32_URL 1

#define BECH32_BC_ADDRESS 256

#define BECH32_LN_BOLT11 257

#define BECH32_LNPBP_ID 512

#define BECH32_LNPBP_DATA 513

#define BECH32_LNPBP_ZDATA 514

#define BECH32_LNPBP_INVOICE 528

#define BECH32_RGB_SCHEMA_ID 768

#define BECH32_RGB_CONTRACT_ID 769

#define BECH32_RGB_SCHEMA 784

#define BECH32_RGB_GENESIS 785

#define BECH32_RGB_CONSIGNMENT 800

#define BECH32_RGB20_ASSET 800

#define SUCCESS 0

#define ERRNO_IO 1

#define ERRNO_RPC 2

#define ERRNO_NET 3

#define ERRNO_TRANSPORT 4

#define ERRNO_NOTSUPPORTED 5

#define ERRNO_STORAGE 6

#define ERRNO_SERVERFAIL 7

#define ERRNO_EMBEDDEDFAIL 8

#define ERRNO_UNINIT 100

#define ERRNO_CHAIN 101

#define ERRNO_JSON 102

#define ERRNO_BECH32 103

#define ERRNO_PARSE 104

#define ERRNO_NULL 105

typedef enum bip39_mnemonic_type {
        BIP39_MNEMONIC_TYPE_WORDS_12,
        BIP39_MNEMONIC_TYPE_WORDS_15,
        BIP39_MNEMONIC_TYPE_WORDS_18,
        BIP39_MNEMONIC_TYPE_WORDS_21,
        BIP39_MNEMONIC_TYPE_WORDS_24,
} bip39_mnemonic_type;

typedef enum descriptor_type {
        DESCRIPTOR_TYPE_BARE,
        DESCRIPTOR_TYPE_HASHED,
        DESCRIPTOR_TYPE_SEGWIT,
        DESCRIPTOR_TYPE_TAPROOT,
} descriptor_type;

typedef enum err_type {
        ERR_TYPE_SUCCESS = 0,
        /**
         * general parse error
         */
        ERR_TYPE_PARSE_ERROR,
        /**
         * JSON encoding error
         */
        ERR_TYPE_ENCODING_ERROR,
        /**
         * got a null pointer as one of the function arguments
         */
        ERR_TYPE_NULL_POINTER,
        /**
         * result data must be a valid string which does not contain zero bytes
         */
        ERR_TYPE_INVALID_RESULT_DATA,
        /**
         * invalid mnemonic string
         */
        ERR_TYPE_INVALID_MNEMONIC,
        /**
         * invalid UTF-8 string
         */
        ERR_TYPE_INVALID_UTF8_STRING,
        /**
         * wrong BIP32 extended public or private key data
         */
        ERR_TYPE_WRONG_EXTENDED_KEY,
        /**
         * unable to derive hardened path from a public key
         */
        ERR_TYPE_UNABLE_TO_DERIVE_HARDENED,
        /**
         * invalid derivation path
         */
        ERR_TYPE_INVALID_DERIVATION_PATH,
        /**
         * general BIP32-specific failure
         */
        ERR_TYPE_BIP32_FAILURE,
        /**
         * error in encoding of PSBT data
         */
        ERR_TYPE_PSBT_FAILURE,
        /**
         * signature error
         */
        ERR_TYPE_SIGNATURE,
} err_type;

typedef enum invoice_type {
        INVOICE_TYPE_ADDRESS_UTXO,
        INVOICE_TYPE_DESCRIPTOR,
        INVOICE_TYPE_PSBT,
} invoice_type;

typedef struct bech32_info_t {
        int status;
        int category;
        bool bech32m;
        const char *details;
} bech32_info_t;

typedef union result_details_t {
        const char *data;
        const char *error;
} result_details_t;

typedef struct string_result_t {
        enum err_type code;
        union result_details_t details;
} string_result_t;

typedef struct mycitadel_client_t {
        void *opaque;
        const char *message;
        int err_no;
} mycitadel_client_t;

typedef struct prepared_transfer_t {
        bool success;
        const char *consignment_bech32;
        const char *psbt_base64;
} prepared_transfer_t;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void lnpbp_bech32_release(struct bech32_info_t info);

struct bech32_info_t lnpbp_bech32_info(const char *bech_str);

struct string_result_t lnpbp_descriptor_parse(const char *descriptor);

struct mycitadel_client_t *mycitadel_run_embedded(const char *chain,
                                                  const char *data_dir,
                                                  const char *electrum_server);

const char *mycitadel_contract_list(struct mycitadel_client_t *client);

const char *mycitadel_single_sig_create(struct mycitadel_client_t *client,
                                        const char *name,
                                        const char *keychain,
                                        enum descriptor_type category);

const char *mycitadel_contract_rename(struct mycitadel_client_t *client,
                                      const char *contract_id,
                                      const char *new_name);

const char *mycitadel_contract_delete(struct mycitadel_client_t *client,
                                      const char *contract_id);

const char *mycitadel_contract_balance(struct mycitadel_client_t *client,
                                       const char *contract_id,
                                       bool rescan,
                                       uint8_t lookup_depth);

const char *mycitadel_address_list(struct mycitadel_client_t *client,
                                   const char *contract_id,
                                   bool rescan,
                                   uint8_t lookup_depth);

const char *mycitadel_address_create(struct mycitadel_client_t *client,
                                     const char *contract_id,
                                     bool mark_used,
                                     bool legacy);

const char *mycitadel_invoice_create(struct mycitadel_client_t *client,
                                     enum invoice_type category,
                                     const char *contract_id,
                                     const char *asset_id,
                                     uint64_t amount,
                                     const char *merchant,
                                     const char *purpose,
                                     bool mark_used,
                                     bool legacy);

const char *mycitadel_invoice_list(struct mycitadel_client_t *client,
                                   const char *contract_id);

const char *mycitadel_address_pay(struct mycitadel_client_t *client,
                                  const char *address,
                                  uint64_t amount,
                                  uint64_t fee);

struct prepared_transfer_t mycitadel_invoice_pay(struct mycitadel_client_t *client,
                                                 const char *contract_id,
                                                 const char *invoice,
                                                 uint64_t fee,
                                                 uint64_t giveaway);

const char *mycitadel_psbt_publish(struct mycitadel_client_t *client,
                                   const char *psbt);

const char *mycitadel_invoice_accept(struct mycitadel_client_t *client,
                                     const char *consignment);

const char *mycitadel_asset_list(struct mycitadel_client_t *client);

const char *mycitadel_asset_import(struct mycitadel_client_t *client,
                                   const char *genesis_b32);

bool is_success(struct string_result_t result);

void result_destroy(struct string_result_t result);

/**
 * Creates a rust-owned mnemonic string. You MUSt always call
 * [`string_destroy`] right after storing the mnemonic string and
 * do not call other methods from this library on that mnemonic. If you need
 * to call [`bip39_master_xpriv`] you MUST read mnemonic again and provide
 * unowned string to the rust.
 */
struct string_result_t bip39_mnemonic_create(const uint8_t *entropy,
                                             enum bip39_mnemonic_type mnemonic_type);

struct string_result_t bip39_master_xpriv(char *seed_phrase,
                                          char *passwd,
                                          bool wipe,
                                          bool testnet);

struct string_result_t bip32_scoped_xpriv(const char *master,
                                          bool clean,
                                          const char *derivation);

struct string_result_t bip32_xpriv_to_xpub(char *xpriv, bool wipe);

struct string_result_t bip32_pubkey_chain_create(char *master_xpriv,
                                                 bool clean,
                                                 const char *derivation);

struct string_result_t psbt_sign(const char *psbt,
                                 const char *master_xpriv_str,
                                 bool wipe);

void release_string(char *s);

bool mycitadel_is_ok(struct mycitadel_client_t *client);

bool mycitadel_has_err(struct mycitadel_client_t *client);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif /* libmycitadel_h */
