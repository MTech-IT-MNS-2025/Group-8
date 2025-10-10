#include <iostream>
#include <fstream>
#include <vector>
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>

static std::vector<uint8_t> read_file(const std::string &path)
{
    std::ifstream f(path, std::ios::binary);
    return std::vector<uint8_t>((std::istreambuf_iterator<char>(f)),
                                std::istreambuf_iterator<char>());
}

int main()
{
    // Read message
    std::vector<uint8_t> msg = read_file("message.txt");
    if (msg.empty())
    {
        std::cerr << "message.txt missing.\n";
        return 1;
    }
    std::string msg_str(msg.begin(), msg.end());

    // Generate RSA-2048 keypair
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::InvertibleRSAFunction params;
    params.GenerateRandomWithKeySize(rng, 2048);
    CryptoPP::RSA::PrivateKey priv(params);
    CryptoPP::RSA::PublicKey pub(params);

    // Signer and verifier
    CryptoPP::RSASS<CryptoPP::PKCS1v15, CryptoPP::SHA256>::Signer signer(priv);
    CryptoPP::RSASS<CryptoPP::PKCS1v15, CryptoPP::SHA256>::Verifier verifier(pub);

    // Sign
    std::string sig;
    CryptoPP::StringSource ss1(msg_str, true,
                               new CryptoPP::SignerFilter(rng, signer,
                                                          new CryptoPP::StringSink(sig)));

    // Verify (fixed: use VerifyMessage directly)
    bool ok = verifier.VerifyMessage(
        (const CryptoPP::byte *)msg_str.data(), msg_str.size(),
        (const CryptoPP::byte *)sig.data(), sig.size());

    std::cout << "[RSA-2048] Verify: " << (ok ? "SUCCESS" : "FAIL") << "\n";

    // Print sizes for assignment comparison
    std::cout << "Public key size: " << pub.GetModulus().ByteCount() << " bytes\n";
    std::cout << "Signature size: " << sig.size() << " bytes\n";

    // Save public key and signature
    pub.Save(CryptoPP::FileSink("rsa_pub.bin").Ref());
    CryptoPP::FileSink sink("rsa_sig.bin");
    sink.Put((const CryptoPP::byte *)sig.data(), sig.size());

    return 0;
}
