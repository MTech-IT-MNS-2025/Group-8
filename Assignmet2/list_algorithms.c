#include <stdio.h>
#include <oqs/oqs.h>

int main() {
    printf("=== Supported KEM Algorithms ===\n\n");

    // Loop over all KEM algorithms
    for (size_t i = 0; i < OQS_KEM_alg_count(); i++) {
        const char *alg_name = OQS_KEM_alg_identifier(i);

        OQS_KEM *kem = OQS_KEM_new(alg_name);
        if (kem == NULL) {
            printf("Failed to initialize KEM: %s\n", alg_name);
            continue;
        }

        printf("Algorithm: %s\n", alg_name);
        printf("  Public Key Length : %zu bytes\n", kem->length_public_key);
        printf("  Secret Key Length : %zu bytes\n", kem->length_secret_key);
        printf("  Ciphertext Length : %zu bytes\n\n", kem->length_ciphertext);

        OQS_KEM_free(kem);
    }

    printf("=== Supported Signature (SIG) Algorithms ===\n\n");

    // Loop over all Signature algorithms
    for (size_t i = 0; i < OQS_SIG_alg_count(); i++) {
        const char *alg_name = OQS_SIG_alg_identifier(i);

        OQS_SIG *sig = OQS_SIG_new(alg_name);
        if (sig == NULL) {
            printf("Failed to initialize SIG: %s\n", alg_name);
            continue;
        }

        printf("Algorithm: %s\n", alg_name);
        printf("  Public Key Length : %zu bytes\n", sig->length_public_key);
        printf("  Secret Key Length : %zu bytes\n", sig->length_secret_key);
        printf("  Signature Length  : %zu bytes\n\n", sig->length_signature);

        OQS_SIG_free(sig);
    }

    return 0;
}
