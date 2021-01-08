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
#include "hashes/sha256.h"
#endif

#if TEST_RELIC
#include "relic.h"
#include "../src/md/sha.h"
#endif

#if TEST_TINYCRYPT
#include "tinycrypt/sha256.h"
#include "tinycrypt/constants.h"
#endif

#if TEST_WOLFSSL
#include "wolfssl/wolfcrypt/sha256.h"
#endif

#if TEST_CIFRA
#include "sha2.h"
#endif

// char teststring[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";

// uint8_t expected_result_sha256[] = {0x24, 0x8d, 0x6a, 0x61, 0xd2, 0x06, 0x38, 0xb8,
//                                     0xe5, 0xc0, 0x26, 0x93, 0x0c, 0x3e, 0x60, 0x39,
//                                     0xa3, 0x3c, 0xe4, 0x59, 0x64, 0xff, 0x21, 0x67,
//                                     0xf6, 0xec, 0xed, 0xd4, 0x19, 0xdb, 0x06, 0xc1};

// char teststring[] = "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus elementum semper nisi. Aenean vulputate eleifend tellus. Aenean leo ligula, porttitor eu, consequat vitae, eleifend ac, enim. Aliquam lorem ante, dapibus in, viverra quis, feugiat a, tellus. Phasellus viverra nulla ut metus varius laoreet. Quisque rutrum. Aenean imperdiet. Etiam ultricies nisi vel augue";

// uint8_t expected_result_sha256[] = {0xfc, 0xbd, 0x7f, 0xe5, 0x12, 0x31, 0x1d, 0x1a,
//                                     0x19, 0x33, 0x87, 0x9a, 0x81, 0xe3, 0x42, 0x2e,
//                                     0x47, 0x4d, 0xf3, 0xd2, 0x46, 0xdf, 0x82, 0xdf,
//                                     0x3f, 0x63, 0x4a, 0xe1, 0x39, 0xd3, 0xb0, 0xa6};

char teststring[] = "This is a teststring fore sha256";
static uint8_t expected_result_sha256[] = {
        0x65, 0x0C, 0x3A, 0xC7, 0xF9, 0x33, 0x17, 0xD3,
        0x96, 0x31, 0xD3, 0xF5, 0xC5, 0x5B, 0x0A, 0x1E,
        0x96, 0x68, 0x04, 0xE2, 0x73, 0xC3, 0x8F, 0x93,
        0x9C, 0xB1, 0x45, 0x4D, 0xC2, 0x69, 0x7D, 0x20
    };

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
    uint8_t sha256_hash[32];

#if MODE_GPIO
    gpio_init(MODE_GPIO_PIN, GPIO_OUT);
    gpio_clear(MODE_GPIO_PIN);
#endif

#if TEST_RIOT
    puts("RIOT");

    sha256_context_t ctx_riot;
#ifdef TEST_TIM
    printf("sizeof(ctx_riot): %i\n", sizeof(ctx_riot));
#endif

    _start_meas();
    sha256_init(&ctx_riot);
    _stop_meas();

    _start_meas();
    sha256_update(&ctx_riot, teststring, strlen(teststring));
    _stop_meas();

    _start_meas();
    sha256_final(&ctx_riot, sha256_hash);
    _stop_meas();

    if(memcmp(expected_result_sha256, sha256_hash, sizeof(sha256_hash)) != 0) {
        puts("ERROR");
    }
#endif

#if TEST_RELIC
    puts("RELIC");

    SHA256Context ctx_relic;
#ifdef TEST_TIM
    printf("sizeof(ctx_relic): %i\n", sizeof(ctx_relic));
#endif

    core_init();

    _start_meas();
    SHA256Reset(&ctx_relic);
    _stop_meas();

    _start_meas();
    SHA256Input(&ctx_relic, (unsigned char *)teststring, strlen(teststring));
    _stop_meas();

    _start_meas();
    SHA256Result(&ctx_relic, sha256_hash);
    _stop_meas();

    core_clean();

    if(memcmp(expected_result_sha256, sha256_hash, sizeof(sha256_hash)) != 0) {
        puts("ERROR");
    }
#endif

#if TEST_TINYCRYPT
    puts("TINYCRYPT");

    struct tc_sha256_state_struct ctx_tinycrypt;
#ifdef TEST_TIM
    printf("sizeof(ctx_tinycrypt): %i\n", sizeof(ctx_tinycrypt));
#endif

    _start_meas();
    tc_sha256_init(&ctx_tinycrypt);
    _stop_meas();

    _start_meas();
    tc_sha256_update (&ctx_tinycrypt, (const uint8_t *)teststring, strlen(teststring));
    _stop_meas();

    _start_meas();
    tc_sha256_final(sha256_hash, &ctx_tinycrypt);
    _stop_meas();

    if(memcmp(expected_result_sha256, sha256_hash, sizeof(sha256_hash)) != 0) {
        puts("ERROR");
    }
#endif

#if TEST_WOLFSSL
    puts("WOLFSSL");

    wc_Sha256 ctx_wolfssl;
#ifdef TEST_TIM
    printf("sizeof(ctx_wolfssl): %i\n", sizeof(ctx_wolfssl));
#endif

    _start_meas();
    wc_InitSha256(&ctx_wolfssl);
    _stop_meas();

    _start_meas();
    wc_Sha256Update(&ctx_wolfssl, (unsigned char *)teststring, strlen(teststring));
    _stop_meas();

    _start_meas();
    wc_Sha256Final(&ctx_wolfssl, sha256_hash);
    _stop_meas();

    wc_Sha256Free(&ctx_wolfssl);

    if(memcmp(expected_result_sha256, sha256_hash, sizeof(sha256_hash)) != 0) {
        puts("ERROR");
    }
#endif

#if TEST_CIFRA
    puts("CIFRA");

    cf_sha256_context ctx_cifra;
#ifdef TEST_TIM
    printf("sizeof(ctx_cifra): %i\n", sizeof(ctx_cifra));
#endif

    _start_meas();
    cf_sha256_init(&ctx_cifra);
    _stop_meas();

    _start_meas();
    cf_sha256_update(&ctx_cifra, (unsigned char *)teststring, strlen(teststring));
    _stop_meas();

    _start_meas();
    cf_sha256_digest(&ctx_cifra, sha256_hash);
    _stop_meas();

    if(memcmp(expected_result_sha256, sha256_hash, sizeof(sha256_hash)) != 0) {
        puts("ERROR");
    }
#endif
    puts("DONE");

    // for(unsigned i=0;i<sizeof(sha256_hash);i++) {
    //     printf("%x %x \n", expected_result_sha256[i], sha256_hash[i]);
    // }

    return 0;
}
