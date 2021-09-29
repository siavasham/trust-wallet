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

using namespace std;

class Coins {       
  public:             
    int btc = TWCoinType::TWCoinTypeBitcoin;        
    int etc = TWCoinType::TWCoinTypeEthereum;        
};
int main(int argc,char* argv[]) {
    Coins coins ;
    TWHDWallet* walletImp = nullptr;
    auto secretMnemonic = TWStringCreateWithUTF8Bytes("prefer exclude easy faith army artwork pencil tortoise fashion vague interest hair");
    walletImp = TWHDWalletCreateWithMnemonic(secretMnemonic, TWStringCreateWithUTF8Bytes(""));
    TWStringDelete(secretMnemonic);
    
    cout << "Default address:          '" << argv[0] << "'" << endl;

    const TWCoinType coinType = coins[argv[0]];
    cout << "Working with coin: " <<
        TWStringUTF8Bytes(TWCoinTypeConfigurationGetName(coinType)) << " " <<
        TWStringUTF8Bytes(TWCoinTypeConfigurationGetSymbol(coinType)) << endl;

    // Derive default address.
    cout << "Obtaining default address ... ";
    string address = TWStringUTF8Bytes(TWHDWalletGetAddressForCoin(walletImp, coinType));
    cout << " done." << endl;
    cout << "Default address:          '" << address << "'" << endl;

    // Alternative: Derive address using default derivation path.
    // Done in 2 steps: derive private key, then address from private key.
    // Note that private key is passed around between the two calls by the wallet -- be always cautious when handling secrets, avoid the risk of leaking secrets.
    cout << "Default derivation path:  " << TWStringUTF8Bytes(TWCoinTypeDerivationPath(coinType)) << endl;
    TWPrivateKey* secretPrivateKeyDefault = TWHDWalletGetKeyForCoin(walletImp, coinType);
    string addressDefault = TWStringUTF8Bytes(TWCoinTypeDeriveAddress(coinType, secretPrivateKeyDefault));
    cout << "Address from default key: '" << addressDefault << "'" << endl;

    // Alternative: Derive address using custom derivation path.  Done in 2 steps: derive private key, then address.
    auto customDerivationPath = TWStringCreateWithUTF8Bytes("m/44'/60'/1'/0/0");
    TWPrivateKey* secretPrivateKeyCustom = TWHDWalletGetKey(walletImp, coinType, customDerivationPath);
    TWStringDelete(customDerivationPath);
    string addressCustom = TWStringUTF8Bytes(TWCoinTypeDeriveAddress(coinType, secretPrivateKeyCustom));
    cout << "Custom-derived address:   '" << addressCustom << "'" << endl;
    cout << endl;

    cout << "RECEIVE funds: Perform send from somewehere else to this address:   " << address << " ." << endl;
    cout << endl;

    TWHDWalletDelete(walletImp);
}
