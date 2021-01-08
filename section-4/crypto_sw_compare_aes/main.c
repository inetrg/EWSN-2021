/*
 * Copyright (C) 2020 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       This application compares SOFTWARE performance metrics of different cryptographic libraries
 *
 * @author      Peter Kietzmann <peter.kietzmann@haw-hamburg.de>
 *
 * @}
 */

#include <stdio.h>
#include <string.h>

#if defined(USE_XTIMER)
#include "xtimer.h"
uint32_t start, stop;
#elif defined(MODE_GPIO)
#include "periph/gpio.h"
#define MODE_GPIO_PIN GPIO_PIN(1, 7)
// gpio_t gpio_aes_key = GPIO_PIN(1, 8);
#endif

#if TEST_STACK
#include "ps.h"
#endif

#if TEST_RIOT
#include "crypto/aes.h"
#endif

#if TEST_RELIC
#include "relic.h"
#include "../src/bc/rijndael-api-fst.h"
#endif

#if TEST_TINYCRYPT
#include "tinycrypt/aes.h"
#include "tinycrypt/constants.h"
#endif

#if TEST_WOLFSSL
#include "wolfssl/wolfcrypt/aes.h"
#endif

#if TEST_CIFRA
#include "aes.h"
#endif

static uint8_t TEST_1_KEY[] = {
    0x23, 0xA0, 0x18, 0x53, 0xFA, 0xB3, 0x89, 0x23,
    0x65, 0x89, 0x2A, 0xBC, 0x43, 0x99, 0xCC, 0x00
};

static uint8_t TEST_1_INP[] = {
    0x11, 0x53, 0x81, 0xE2, 0x5F, 0x33, 0xE7, 0x41,
    0xBB, 0x12, 0x67, 0x38, 0xE9, 0x12, 0x54, 0x23
};

// static uint8_t TEST_1_ENC[] = {
//     0xD7, 0x9A, 0x54, 0x0E, 0x61, 0x33, 0x03, 0x72,
//     0x59, 0x0f, 0x87, 0x91, 0xEF, 0xB0, 0xF8, 0x16
// };

static inline void _start_meas(void) {
#if defined (USE_XTIMER)
    start = xtimer_now_usec();
#elif defined (MODE_GPIO)
    gpio_set(MODE_GPIO_PIN);
#endif
}

static inline void _stop_meas(void) {
#if defined (USE_XTIMER)
    stop = xtimer_now_usec();
    printf("%"PRIu32"\n", (stop - start));
    start = 0;
#elif defined (MODE_GPIO)
    gpio_clear(MODE_GPIO_PIN);
#endif
#if TEST_STACK
    ps();
#endif
}

int main(void)
{
    uint8_t data_enc[16]={0};
    uint8_t data_dec[16]={0};

#if MODE_GPIO
    gpio_init(MODE_GPIO_PIN, GPIO_OUT);
    gpio_clear(MODE_GPIO_PIN);
#endif

#if TEST_RIOT
    puts("RIOT");

    cipher_context_t ctx_riot;
#ifdef TEST_TIM
    printf("sizeof(ctx_riot): %i\n", sizeof(ctx_riot));
#endif

    _start_meas();
    aes_init(&ctx_riot, TEST_1_KEY, sizeof(TEST_1_KEY));
    _stop_meas();

    _start_meas();
    aes_encrypt(&ctx_riot, TEST_1_INP, data_enc);
    _stop_meas();

    _start_meas();
    aes_decrypt(&ctx_riot, data_enc, data_dec);
    _stop_meas();

    if (memcmp(TEST_1_INP, data_dec, sizeof(data_dec)) != 0) {
        printf("ERROR\n");
    }
#endif

#if TEST_RELIC
    puts("RELIC");

    cipherInstance ctx_relic;
    keyInstance key_inst;

#ifdef TEST_TIM
    printf("sizeof(ctx_relic): %i\n", sizeof(ctx_relic));
    printf("sizeof(key_inst): %i\n", sizeof(key_inst));
#endif

    core_init();

    _start_meas();
	cipherInit(&ctx_relic, MODE_ECB, NULL);
    _stop_meas();

    _start_meas();
	makeKey2(&key_inst, DIR_ENCRYPT, 8 * sizeof(TEST_1_KEY), (char *)TEST_1_KEY);
    blockEncrypt(&ctx_relic, &key_inst, TEST_1_INP, 8 * sizeof(TEST_1_INP), data_enc);
    _stop_meas();

    _start_meas();
	makeKey2(&key_inst, DIR_DECRYPT, 8 * sizeof(TEST_1_KEY), (char *)TEST_1_KEY);
    blockDecrypt(&ctx_relic, &key_inst,data_enc, 8 * sizeof(data_enc), data_dec);
    _stop_meas();

    if (memcmp(TEST_1_INP, data_dec, sizeof(data_enc)) != 0) {
        puts("ERROR");
    }

    core_clean();
#endif

#if TEST_TINYCRYPT
    puts("TINYCRYPT");

    struct tc_aes_key_sched_struct ctx_tinycrypt;
#ifdef TEST_TIM
    printf("sizeof(ctx_tinycrypt): %i\n", sizeof(ctx_tinycrypt));
#endif

    _start_meas();
    _stop_meas();

    _start_meas();
    tc_aes128_set_encrypt_key(&ctx_tinycrypt, TEST_1_KEY);
    tc_aes_encrypt(data_enc, TEST_1_INP, &ctx_tinycrypt);
    _stop_meas();

    _start_meas();
    tc_aes128_set_decrypt_key(&ctx_tinycrypt, TEST_1_KEY);
    tc_aes_decrypt(data_dec, data_enc, &ctx_tinycrypt);
    _stop_meas();

    if (memcmp(TEST_1_INP, data_dec, sizeof(data_dec)) != 0) {
        puts("ERROR");
    }
#endif

#if TEST_WOLFSSL
    puts("WOLFSSL");

    Aes ctx_wolfssl;

#ifdef TEST_TIM
    printf("sizeof(ctx_wolfssl): %i\n", sizeof(ctx_wolfssl));
#endif

    _start_meas();
    wc_AesInit(&ctx_wolfssl, NULL, INVALID_DEVID);

    wc_AesSetKey(&ctx_wolfssl, TEST_1_KEY, sizeof(TEST_1_KEY), NULL, AES_ENCRYPTION);
    _stop_meas();

    _start_meas();
    wc_AesEncryptDirect(&ctx_wolfssl, data_enc, TEST_1_INP);
    _stop_meas();

    _start_meas();
    wc_AesSetKey(&ctx_wolfssl, TEST_1_KEY, sizeof(TEST_1_KEY), NULL, AES_DECRYPTION);
    wc_AesDecryptDirect(&ctx_wolfssl, data_dec, data_enc);
    _stop_meas();

    if (memcmp(TEST_1_INP, data_dec, sizeof(data_dec)) != 0) {
        puts("ERROR");
    }
#endif

#if TEST_CIFRA
    puts("CIFRA");

    cf_aes_context ctx_cifra;

#ifdef TEST_TIM
    printf("sizeof(ctx_cifra): %i\n", sizeof(ctx_cifra));
#endif

    _start_meas();
    cf_aes_init(&ctx_cifra, TEST_1_KEY, sizeof(TEST_1_KEY));
    _stop_meas();

    _start_meas();
    cf_aes_encrypt(&ctx_cifra, TEST_1_INP, data_enc);
    _stop_meas();

    _start_meas();
    cf_aes_decrypt(&ctx_cifra, data_enc, data_dec);
    _stop_meas();

    if (memcmp(TEST_1_INP, data_dec, sizeof(data_dec)) != 0) {
        puts("ERROR");
    }
#endif
    puts("DONE");

    // for(unsigned i=0;i<sizeof(sha256_hash);i++) {
    //     printf("%x %x \n", expected_result_sha256[i], sha256_hash[i]);
    // }

    return 0;
}
