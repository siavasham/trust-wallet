// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.
#include "json.hpp"

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

using json = nlohmann::json;
using namespace std;

int main(int argc,char* argv[]) {
   
    const map<string, int> coins
    {
        {"ae",TWCoinType::TWCoinTypeAeternity },
        {"aion" , TWCoinType::TWCoinTypeAion },
        {"bnb" , TWCoinType::TWCoinTypeBinance },
        {"btc" , TWCoinType::TWCoinTypeBitcoin },
        {"bch" , TWCoinType::TWCoinTypeBitcoinCash },
        {"btg" , TWCoinType::TWCoinTypeBitcoinGold },
        {"clo" , TWCoinType::TWCoinTypeCallisto },
        {"ada" , TWCoinType::TWCoinTypeCardano ,} ,
        {"atom" , TWCoinType::TWCoinTypeCosmos },
        {"dash" , TWCoinType::TWCoinTypeDash },
        {"dcr" , TWCoinType::TWCoinTypeDecred },
        {"dgb" ,  TWCoinType::TWCoinTypeDigiByte },
        {"doge" , TWCoinType::TWCoinTypeDogecoin },
        {"eos" , TWCoinType::TWCoinTypeEOS },
        {"eth" , TWCoinType::TWCoinTypeEthereum },
        {"etc" , TWCoinType::TWCoinTypeEthereumClassic },
        {"fio" , TWCoinType::TWCoinTypeFIO },
        {"go" , TWCoinType::TWCoinTypeGoChain },
        {"grs" , TWCoinType::TWCoinTypeGroestlcoin },
        {"icx" , TWCoinType::TWCoinTypeICON },
        {"iotx" , TWCoinType::TWCoinTypeIoTeX },
        {"kava" , TWCoinType::TWCoinTypeKava },
        {"kin" , TWCoinType::TWCoinTypeKin },
        {"ltc" , TWCoinType::TWCoinTypeLitecoin },
        {"mona" , TWCoinType::TWCoinTypeMonacoin },
        {"nas" , TWCoinType::TWCoinTypeNebulas },
        {"nuls" , TWCoinType::TWCoinTypeNULS },
        {"nano" , TWCoinType::TWCoinTypeNano },
        {"near" , TWCoinType::TWCoinTypeNEAR },
        {"nim" , TWCoinType::TWCoinTypeNimiq },
        {"ont" , TWCoinType::TWCoinTypeOntology },
        {"poa" , TWCoinType::TWCoinTypePOANetwork },
        {"qtum" , TWCoinType::TWCoinTypeQtum },
        {"xrp" , TWCoinType::TWCoinTypeXRP },
        {"sol" , TWCoinType::TWCoinTypeSolana },
        {"xlm" , TWCoinType::TWCoinTypeStellar },
        {"xtz" , TWCoinType::TWCoinTypeTezos },
        {"theta" , TWCoinType::TWCoinTypeTheta },
        {"tt" , TWCoinType::TWCoinTypeThunderToken },
        {"neo" , TWCoinType::TWCoinTypeNEO },
        {"tomo" , TWCoinType::TWCoinTypeTomoChain },
        {"trx" , TWCoinType::TWCoinTypeTron },
        {"vet" , TWCoinType::TWCoinTypeVeChain },
        {"via" , TWCoinType::TWCoinTypeViacoin },
        {"wan" , TWCoinType::TWCoinTypeWanchain },
        {"zec" , TWCoinType::TWCoinTypeZcash },
        {"firo" , TWCoinType::TWCoinTypeZcoin },
        {"zil" , TWCoinType::TWCoinTypeZilliqa },
        {"zel" , TWCoinType::TWCoinTypeZelcash },
        {"rvn" , TWCoinType::TWCoinTypeRavencoin },
        {"waves" , TWCoinType::TWCoinTypeWaves },
        {"luna" , TWCoinType::TWCoinTypeTerra },
        {"one" , TWCoinType::TWCoinTypeHarmony },
        {"algo" , TWCoinType::TWCoinTypeAlgorand },
        {"ksm" , TWCoinType::TWCoinTypeKusama },
        {"dot" , TWCoinType::TWCoinTypePolkadot },
        {"fil" , TWCoinType::TWCoinTypeFilecoin },
        {"egld" , TWCoinType::TWCoinTypeElrond },
        {"band" , TWCoinType::TWCoinTypeBandChain },
        {"bsc",TWCoinType::TWCoinTypeSmartChain},
        {"bep20" , TWCoinType::TWCoinTypeSmartChainLegacy}
    };
    TWHDWallet* walletImp = nullptr;
    string menomic =  argv[3];
    auto pos = 0;
    string from  = "-";
    string to = " ";
    while(true)
    {
        size_t startPosition = menomic.find(from, pos);
        if(startPosition == string::npos)
            break;
        menomic.replace(startPosition, from.length(), to);
        pos += to.length();
    }
    auto secretMnemonic = TWStringCreateWithUTF8Bytes(menomic+"");
    // walletImp = TWHDWalletCreateWithMnemonic(secretMnemonic, TWStringCreateWithUTF8Bytes(""));
    // TWStringDelete(secretMnemonic);
    
    // const TWCoinType coinType = (TWCoinType) coins.at(argv[1]);
    // int userId = atoi(argv[2]);
    // string coinName  = TWStringUTF8Bytes(TWCoinTypeConfigurationGetName(coinType));
    // string coinsymbl = TWStringUTF8Bytes(TWCoinTypeConfigurationGetSymbol(coinType));
    // TWPrivateKey* privateKey = TWHDWalletGetKeyBIP44(walletImp, coinType, 0, 0,userId);
    // string address = TWStringUTF8Bytes(TWCoinTypeDeriveAddress(coinType, privateKey));

    // const map<string, string> out {{"address", address}};
    // json j = out;
    // cout << j << endl;

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

    // TWHDWalletDelete(walletImp);
}
