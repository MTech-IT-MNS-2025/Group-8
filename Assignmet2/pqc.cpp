#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <oqs/oqs.h>

static std::vector<uint8_t> read_file(const std::string &path)
{
    std::ifstream f(path, std::ios::binary);
    return std::vector<uint8_t>((std::istreambuf_iterator<char>(f)),
                                std::istreambuf_iterator<char>());
}

int main()
{
    std::vector<uint8_t> msg = read_file("message.txt");
    if (msg.empty())
    {
        std::cerr << "message.txt missing.\n";
        return 1;
    }

    // Use ML-DSA-44 (Dilithium2 equivalent)
    OQS_SIG *sig = OQS_SIG_new("ML-DSA-44");
    if (!sig)
    {
        std::cerr << "Dilithium2 not enabled.\n";
        return 1;
    }

    std::vector<uint8_t> pk(sig->length_public_key);
    std::vector<uint8_t> sk(sig->length_secret_key);
    std::vector<uint8_t> signature(sig->length_signature);
    size_t sig_len = 0;

    // Generate keypair
    OQS_SIG_keypair(sig, pk.data(), sk.data());

    // Sign
    OQS_SIG_sign(sig, signature.data(), &sig_len,
                 msg.data(), msg.size(), sk.data());

    // Verify
    OQS_STATUS ok = OQS_SIG_verify(sig,
                                   msg.data(), msg.size(),
                                   signature.data(), sig_len,
                                   pk.data());

    std::cout << "[Dilithium2] Verify: "
              << (ok == OQS_SUCCESS ? "SUCCESS" : "FAIL") << "\n";

    // Print sizes for assignment comparison
    std::cout << "Public key size: " << pk.size() << " bytes\n";
    std::cout << "Secret key size: " << sk.size() << " bytes\n";
    std::cout << "Signature size: " << sig_len << " bytes\n";

    // Save artifacts
    std::ofstream("dilithium_pk.bin", std::ios::binary)
        .write((char *)pk.data(), pk.size());
    std::ofstream("dilithium_sig.bin", std::ios::binary)
        .write((char *)signature.data(), sig_len);

    OQS_SIG_free(sig);
    return 0;
}
