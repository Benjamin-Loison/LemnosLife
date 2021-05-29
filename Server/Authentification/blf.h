#ifdef __linux__

    #ifndef _BLF_H_
    #define _BLF_H_
    #ifdef __cplusplus
        extern "C" {
    #endif
    /* Schneier states the maximum key length to be 56 bytes.
     * The way how the subkeys are initialized by the key up
     * to (N+2)*4 i.e. 72 bytes are utilized.
     * Warning: For normal blowfish encryption only 56 bytes
     * of the key affect all cipherbits.
     */

    #define BLF_N	16			/* Number of Subkeys */
    #define BLF_MAXKEYLEN ((BLF_N-2)*4)	/* 448 bits */
    #define BLF_MAXUTILIZED ((BLF_N+2)*4)	/* 576 bits */

    /* Blowfish context */
    typedef struct BlowfishContext {
        u_int32_t S[4][256];	/* S-Boxes */
        u_int32_t P[BLF_N + 2];	/* Subkeys */
    } blf_ctx;

    /* Raw access to customized Blowfish
     *	blf_key is just:
     *	Blowfish_initstate( state )
     *	Blowfish_expand0state( state, key, keylen )
     */

    //void Blowfish_encipher(blf_ctx *, u_int32_t *);
    //void Blowfish_decipher(blf_ctx *, u_int32_t *);
    void Blowfish_initstate(blf_ctx *);
    void Blowfish_expand0state(blf_ctx *, const u_int8_t *, u_int16_t);
    void Blowfish_expandstate(blf_ctx *, const u_int8_t *, u_int16_t, const u_int8_t *, u_int16_t);

    /* Standard Blowfish */

    void blf_key(blf_ctx *, const u_int8_t *, u_int16_t);
    void blf_enc(blf_ctx *, u_int32_t *, u_int16_t);
    void blf_dec(blf_ctx *, u_int32_t *, u_int16_t);

    /* Converts u_int8_t to u_int32_t */
    u_int32_t Blowfish_stream2word(const u_int8_t *, u_int16_t ,
                        u_int16_t *);

    void blf_ecb_encrypt(blf_ctx *, u_int8_t *, u_int32_t);
    void blf_ecb_decrypt(blf_ctx *, u_int8_t *, u_int32_t);

    void blf_cbc_encrypt(blf_ctx *, u_int8_t *, u_int8_t *, u_int32_t);
    void blf_cbc_decrypt(blf_ctx *, u_int8_t *, u_int8_t *, u_int32_t);
    #ifdef __cplusplus
        }
    #endif
    #endif

#endif
