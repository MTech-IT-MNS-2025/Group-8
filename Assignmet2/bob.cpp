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
    std::vector<uint8_t> ct(kem->length_ciphertext);
    std::vector<uint8_t> ss_bob(kem->length_shared_secret);

    // Load Alice's public key
    std::ifstream pk_in("alice_pk.bin", std::ios::binary);
    if (!pk_in)
    {
        std::cerr << "Could not open Alice's public key file.\n";
        return 1;
    }
    pk_in.read((char *)pk.data(), pk.size());

    using clock = std::chrono::steady_clock;

    // 2. Bob encapsulates
    auto t2 = clock::now();
    OQS_STATUS st_enc = OQS_KEM_encaps(kem, ct.data(), ss_bob.data(), pk.data());
    auto t3 = clock::now();

    if (st_enc != OQS_SUCCESS)
    {
        std::cerr << "Encapsulation failed\n";
        return 1;
    }

    std::ofstream("ciphertext.bin", std::ios::binary).write((char *)ct.data(), ct.size());

    std::cout << "Bob: encapsulated and saved ciphertext.\n";
    auto encaps_us = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count();
    std::cout << "Encapsulation time: " << encaps_us << " us\n";

    OQS_KEM_free(kem);
    return 0;
}
