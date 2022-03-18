// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.
#include "json.hpp"

#include <TrustWalletCore/TWCoinType.h>
#include <TrustWalletCore/TWCoinTypeConfiguration.h>
#include <TrustWalletCore/TWHDWallet.h>
#include <TrustWalletCore/TWPrivateKey.h>
#include <TrustWalletCore/TWString.h>

#include <TrustWalletCore/TWAnySigner.h>
#include <../../src/Tron/Signer.cpp>

#include <iostream>
#include <string>
#include <map>
#include <cstdlib>

using json = nlohmann::json;
using namespace std;

int main(int argc,char* argv[]) {
     TWHDWallet* walletImp = nullptr;
    auto menomic =  argv[1];
    replace( menomic, menomic+strlen(menomic), '-', ' ' );
    auto secretMnemonic = TWStringCreateWithUTF8Bytes(menomic);
    walletImp = TWHDWalletCreateWithMnemonic(secretMnemonic, TWStringCreateWithUTF8Bytes(""));
    TWStringDelete(secretMnemonic);
    
    const TWCoinType coinType = TWCoinType::TWCoinTypeTron;
    int userId = 9;
    TWPrivateKey* privateKey = TWHDWalletGetKeyBIP44(walletImp, coinType, 0, 0,0);
    string source = TWStringUTF8Bytes(TWCoinTypeDeriveAddress(coinType, privateKey));

    TWPrivateKey* privateKey2 = TWHDWalletGetKeyBIP44(walletImp, coinType, 0, 0,userId);
    string dest = TWStringUTF8Bytes(TWCoinTypeDeriveAddress(coinType, privateKey2));

    TWHDWalletDelete(walletImp);

    auto secretPrivKey = TWPrivateKeyData(privateKey);

    auto input = Proto::SigningInput();
    auto& transaction = *input.mutable_transaction();

    auto& transfer = *transaction.mutable_transfer_asset();
    transfer.set_owner_address(source);
    transfer.set_to_address(dest);
    transfer.set_amount(5);

    input.set_private_key(secretPrivKey.bytes.data(), secretPrivKey.bytes.size());

    const auto output = Signer::sign(input);

    auto signedTransaction = string(TWStringUTF8Bytes(output));
    cout  << signedTransaction << endl;
    
}
