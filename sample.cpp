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

#include <nlohmann/json.hpp>
  
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>

using namespace std;
using json = nlohmann::json;

int main(int argc,char* argv[]) {
    json j;
    const std::map<std::string, int> coins
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
        {"smartchain",TWCoinType::TWCoinTypeSmartChain},
        {"bsc" , TWCoinType::TWCoinTypeSmartChainLegacy}
    };
    TWHDWallet* walletImp = nullptr;
    auto secretMnemonic = TWStringCreateWithUTF8Bytes("prefer exclude easy faith army artwork pencil tortoise fashion vague interest hair");
    walletImp = TWHDWalletCreateWithMnemonic(secretMnemonic, TWStringCreateWithUTF8Bytes(""));
    TWStringDelete(secretMnemonic);
    
    int size = atoi(argv[1]);
    for ( const pair<std::string, int> &p : coins ) {
        const TWCoinType coinType = (TWCoinType) p.second;
       json JsonObjects = json::array();
        for(int i=0;i<size;i++){
            string coinName  = TWStringUTF8Bytes(TWCoinTypeConfigurationGetName(coinType));
            string coinsymbl = TWStringUTF8Bytes(TWCoinTypeConfigurationGetSymbol(coinType));
            TWPrivateKey* privateKey = TWHDWalletGetKeyBIP44(walletImp, coinType, 0, 0,i);
            string address = TWStringUTF8Bytes(TWCoinTypeDeriveAddress(coinType, privateKey));
            JsonObjects.push_back(address);
        }
        j[p.first] = JsonObjects;
    }
    ofstream MyFile("address.json");
    MyFile << j.dump();
    MyFile.close();
 

    TWHDWalletDelete(walletImp);
}
