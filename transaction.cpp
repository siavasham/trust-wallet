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

#include <iostream>
#include <string>
#include <map>
#include <cstdlib>

using json = nlohmann::json;
using namespace std;
using namespace TW::Tron;
using namespace TW::Hash;

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

     string transaction = "{"
                "\",\"toAddress\":\"" + dest +
                "\",\"transaction\":{\"transfer\":{\"amount\":\"" + 5 +
                "\"}}}";            
            cout << "transaction: " << transaction << endl;

            cout << "signing transaction ... ";

            auto json = TWStringCreateWithUTF8Bytes(transaction.c_str());
            auto result = TWAnySignerSignJSON(json, secretPrivKey, coinType);
            auto signedTransaction = string(TWStringUTF8Bytes(result));
            cout << "done" << endl;
            cout << "Signed transaction data (to be broadcast to network):  (len " << signedTransaction.length() << ") '" << signedTransaction << "'" << endl;
            // see e.g. https://github.com/flightwallet/decode-eth-tx for checking binary output content
            cout << endl;
            TWStringDelete(json);
            TWStringDelete(result);
    
}

