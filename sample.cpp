// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <TrustWalletCore/TWCoinType.h>
#include <TrustWalletCore/TWAnySigner.h>
#include <TrustWalletCore/TWCoinTypeConfiguration.h>
#include <TrustWalletCore/TWHDWallet.h>
#include <TrustWalletCore/TWPrivateKey.h>
#include <TrustWalletCore/TWString.h>

#include <iostream>
#include <string>
#include <map>
#include <cstdlib>

using namespace std;

int main(int argc,char* argv[]) {
    const std::map<std::string, int> coins
    {
        {"btc", TWCoinType::TWCoinTypeBitcoin}, {"eth", TWCoinType::TWCoinTypeEthereum}
    };
    TWHDWallet* walletImp = nullptr;
    auto secretMnemonic = TWStringCreateWithUTF8Bytes("prefer exclude easy faith army artwork pencil tortoise fashion vague interest hair");
    walletImp = TWHDWalletCreateWithMnemonic(secretMnemonic, TWStringCreateWithUTF8Bytes(""));
    TWStringDelete(secretMnemonic);
    
    const TWCoinType coinType = (TWCoinType) coins.at(argv[1]);
    
    string coinName  = TWStringUTF8Bytes(TWCoinTypeConfigurationGetName(coinType));
    string coinsymbl = TWStringUTF8Bytes(TWCoinTypeConfigurationGetSymbol(coinType));
    cout << coinName <<  (int) argv[2] << endl;
    TWPrivateKey* privateKey = TWHDWalletGetKeyBIP44(walletImp, coinType, 0, 0, (int) argv[2]);
    string address = TWStringUTF8Bytes(TWCoinTypeDeriveAddress(coinType, privateKey));
    cout << "address: '" << address << "'" << endl;


    // cout << "Default derivation path:  " << TWStringUTF8Bytes(TWCoinTypeDerivationPath(coinType)) << endl;
    // TWPrivateKey* secretPrivateKeyDefault = TWHDWalletGetKeyForCoin(walletImp, coinType);
    // string addressDefault = TWStringUTF8Bytes(TWCoinTypeDeriveAddress(coinType, secretPrivateKeyDefault));
    // cout << "Address from default key: '" << addressDefault << "'" << endl;

    // // Alternative: Derive address using custom derivation path.  Done in 2 steps: derive private key, then address.
    // auto customDerivationPath = TWStringCreateWithUTF8Bytes("m/44'/60'/1'/0/0");
    // TWPrivateKey* secretPrivateKeyCustom = TWHDWalletGetKey(walletImp, coinType, customDerivationPath);
    // TWStringDelete(customDerivationPath);
    // string addressCustom = TWStringUTF8Bytes(TWCoinTypeDeriveAddress(coinType, secretPrivateKeyCustom));
    // cout << "Custom-derived address:   '" << addressCustom << "'" << endl;
    // cout << endl;

    TWHDWalletDelete(walletImp);
}
