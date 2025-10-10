#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <oqs/oqs.h>

int main()
{
    const char *alg = "Kyber512";
    OQS_KEM *kem = OQS_KEM_new(alg);

    std::vector<uint8_t> pk(kem->length_public_key);
    std::vector<uint8_t> sk(kem->length_secret_key);
    std::vector<uint8_t> ct(kem->length_ciphertext);
    std::vector<uint8_t> ss_alice(kem->length_shared_secret);

    using clock = std::chrono::steady_clock;

    // 1. Alice generates keypair
    auto t0 = clock::now();
    OQS_STATUS st_keypair = OQS_KEM_keypair(kem, pk.data(), sk.data());
    auto t1 = clock::now();

    if (st_keypair != OQS_SUCCESS)
    {
        std::cerr << "Keypair generation failed\n";
        return 1;
    }

    std::ofstream("alice_pk.bin", std::ios::binary).write((char *)pk.data(), pk.size());
    std::ofstream("alice_sk.bin", std::ios::binary).write((char *)sk.data(), sk.size());

    std::cout << "Alice: keypair generated and public key saved.\n";
    auto keygen_us = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
    std::cout << "Key generation time: " << keygen_us << " us\n";

    // 3. Alice waits for ciphertext from Bob
    std::ifstream ct_in("ciphertext.bin", std::ios::binary);
    if (ct_in)
    {
        ct_in.read((char *)ct.data(), ct.size());

        auto t4 = clock::now();
        OQS_STATUS st_dec = OQS_KEM_decaps(kem, ss_alice.data(), ct.data(), sk.data());
        auto t5 = clock::now();

        if (st_dec == OQS_SUCCESS)
        {
            std::cout << "Alice recovered shared secret.\n";
            auto decaps_us = std::chrono::duration_cast<std::chrono::microseconds>(t5 - t4).count();
            std::cout << "Decapsulation time: " << decaps_us << " us\n";
        }
        else
        {
            std::cerr << "Decapsulation failed.\n";
        }
    }

    OQS_KEM_free(kem);
    return 0;
}
