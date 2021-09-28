package main
// #cgo CFLAGS: -I/wallet-core/include
// #cgo LDFLAGS: -L/wallet-core/build -L/wallet-core/build/trezor-crypto -lTrustWalletCore -lprotobuf -lTrezorCrypto -lc++ -lm
// #include <TrustWalletCore/TWHash.h>
// #include <TrustWalletCore/TWHDWallet.h>
// #include <TrustWalletCore/TWString.h>
// #include <TrustWalletCore/TWData.h>
// #include <TrustWalletCore/TWPrivateKey.h>
// #include <TrustWalletCore/TWPublicKey.h>
// #include <TrustWalletCore/TWMnemonic.h>
// #include <TrustWalletCore/TWBase58.h>
// #include <TrustWalletCore/TWCoinType.h>

// #include <TrustWalletCore/TWFoundationData.h>
// #include <TrustWalletCore/TWFoundationString.h>
// #include <TrustWalletCore/TWBitcoin.h>
// #include <TrustWalletCore/TWBitcoinOpCodes.h>
// #include <TrustWalletCore/TWAES.h>
// #include <TrustWalletCore/TWAccount.h>
// #include <TrustWalletCore/TWAionAddress.h>
// #include <TrustWalletCore/TWAionSigner.h>
// #include <TrustWalletCore/TWBech32Address.h>
// #include <TrustWalletCore/TWBinanceSigner.h>
// #include <TrustWalletCore/TWBitcoinAddress.h>
// #include <TrustWalletCore/TWBitcoinCashAddress.h>
// #include <TrustWalletCore/TWBitcoinScript.h>
// #include <TrustWalletCore/TWBitcoinTransactionSigner.h>
// #include <TrustWalletCore/TWCoinTypeConfiguration.h>
// #include <TrustWalletCore/TWCosmosAddress.h>
// #include <TrustWalletCore/TWCosmosSigner.h>
// #include <TrustWalletCore/TWCurve.h>
// #include <TrustWalletCore/TWDecredAddress.h>
// #include <TrustWalletCore/TWDecredSigner.h>
// #include <TrustWalletCore/TWEthereumAddress.h>
// #include <TrustWalletCore/TWEthereumChainID.h>
// #include <TrustWalletCore/TWEthereumSigner.h>
// #include <TrustWalletCore/TWGroestlcoinAddress.h>
// #include <TrustWalletCore/TWGroestlcoinTransactionSigner.h>
// #include <TrustWalletCore/TWHDVersion.h>
// #include <TrustWalletCore/TWHDWallet.h>
// #include <TrustWalletCore/TWHRP.h>
// #include <TrustWalletCore/TWHash.h>
// #include <TrustWalletCore/TWIOSTAccount.h>
// #include <TrustWalletCore/TWIOSTSigner.h>
// #include <TrustWalletCore/TWIconAddress.h>
// #include <TrustWalletCore/TWIconAddressType.h>
// #include <TrustWalletCore/TWIconSigner.h>
// #include <TrustWalletCore/TWIocoinAddress.h>
// #include <TrustWalletCore/TWKeyDerivation.h>
// #include <TrustWalletCore/TWNEOAddress.h>
// #include <TrustWalletCore/TWNimiqAddress.h>
// #include <TrustWalletCore/TWNimiqSigner.h>
// #include <TrustWalletCore/TWOntologyAddress.h>
// #include <TrustWalletCore/TWOntologySigner.h>
// #include <TrustWalletCore/TWP2PKHPrefix.h>
// #include <TrustWalletCore/TWP2SHPrefix.h>
// #include <TrustWalletCore/TWPrivateKey.h>
// #include <TrustWalletCore/TWPublicKey.h>
// #include <TrustWalletCore/TWPurpose.h>
// #include <TrustWalletCore/TWRippleAddress.h>
// #include <TrustWalletCore/TWRippleSigner.h>
// #include <TrustWalletCore/TWStellarAddress.h>
// #include <TrustWalletCore/TWStellarMemoType.h>
// #include <TrustWalletCore/TWStellarPassphrase.h>
// #include <TrustWalletCore/TWStellarSigner.h>
// #include <TrustWalletCore/TWStellarVersionByte.h>
// #include <TrustWalletCore/TWStoredKey.h>
// #include <TrustWalletCore/TWTezosAddress.h>
// #include <TrustWalletCore/TWTezosSigner.h>
// #include <TrustWalletCore/TWThetaSigner.h>
// #include <TrustWalletCore/TWTronAddress.h>
// #include <TrustWalletCore/TWTronSigner.h>
// #include <TrustWalletCore/TWVeChainSigner.h>
// #include <TrustWalletCore/TWWanchainAddress.h>
// #include <TrustWalletCore/TWWanchainSigner.h>
// #include <TrustWalletCore/TWZcashTAddress.h>
// #include <TrustWalletCore/TWZcashTransactionSigner.h>
import "C"
import "fmt"
import "unsafe"
import "encoding/hex"
import "os"

// C.TWString -> Go string
func TWStringGoString(s unsafe.Pointer) string {
    return C.GoString(C.TWStringUTF8Bytes(s))
}

// Go string -> C.TWString
func TWStringCreateWithGoString(s string) unsafe.Pointer {
    cStr := C.CString(s)
    defer C.free(unsafe.Pointer(cStr))
    str := C.TWStringCreateWithUTF8Bytes(cStr)
    return str
}

// C.TWData -> Go byte[]
func TWDataGoBytes(d unsafe.Pointer) []byte {
    cBytes := C.TWDataBytes(d)
    cSize := C.TWDataSize(d)
    return C.GoBytes(unsafe.Pointer(cBytes), C.int(cSize))
}

// Go byte[] -> C.TWData
func TWDataCreateWithGoBytes(d []byte) unsafe.Pointer {
    cBytes := C.CBytes(d)
    defer C.free(unsafe.Pointer(cBytes))
    data := C.TWDataCreateWithBytes((*C.uchar)(cBytes), C.ulong(len(d)))
    return data
}

func main() {
    coin := os.Args[1]
    // index := os.Args[2]

    types := map[string]uint32{
    "ae":C.TWCoinTypeAeternity ,
    "aion" : C.TWCoinTypeAion ,
    "bnb" : C.TWCoinTypeBinance ,
    "btc" : C.TWCoinTypeBitcoin ,
    "bch" : C.TWCoinTypeBitcoinCash ,
    "btg" : C.TWCoinTypeBitcoinGold ,
    "clo" : C.TWCoinTypeCallisto ,
    "ada" : C.TWCoinTypeCardano , 
    "atom" : C.TWCoinTypeCosmos ,
    "dash" : C.TWCoinTypeDash ,
    "dcr" : C.TWCoinTypeDecred ,
    "dgb" :  C.TWCoinTypeDigiByte ,
    "doge" : C.TWCoinTypeDogecoin ,
    "eos" : C.TWCoinTypeEOS ,
    "eth" : C.TWCoinTypeEthereum ,
    "etc" : C.TWCoinTypeEthereumClassic ,
    "fio" : C.TWCoinTypeFIO ,
    "go" : C.TWCoinTypeGoChain ,
    "grs" : C.TWCoinTypeGroestlcoin ,
    "icx" : C.TWCoinTypeICON ,
    "iotx" : C.TWCoinTypeIoTeX ,
    "kava" : C.TWCoinTypeKava ,
    "kin" : C.TWCoinTypeKin ,
    "ltc" : C.TWCoinTypeLitecoin ,
    "mona" : C.TWCoinTypeMonacoin ,
    "nas" : C.TWCoinTypeNebulas ,
    "nuls" : C.TWCoinTypeNULS ,
    "nano" : C.TWCoinTypeNano ,
    "near" : C.TWCoinTypeNEAR ,
    "nim" : C.TWCoinTypeNimiq ,
    "ont" : C.TWCoinTypeOntology ,
    "poa" : C.TWCoinTypePOANetwork ,
    "qtum" : C.TWCoinTypeQtum ,
    "xrp" : C.TWCoinTypeXRP ,
    "sol" : C.TWCoinTypeSolana ,
    "xlm" : C.TWCoinTypeStellar ,
    "xtz" : C.TWCoinTypeTezos ,
    "theta" : C.TWCoinTypeTheta ,
    "tt" : C.TWCoinTypeThunderToken ,
    "neo" : C.TWCoinTypeNEO ,
    "tomo" : C.TWCoinTypeTomoChain ,
    "trx" : C.TWCoinTypeTron ,
    "vet" : C.TWCoinTypeVeChain ,
    "via" : C.TWCoinTypeViacoin ,
    "wan" : C.TWCoinTypeWanchain ,
    "zec" : C.TWCoinTypeZcash ,
    "firo" : C.TWCoinTypeZcoin ,
    "zil" : C.TWCoinTypeZilliqa ,
    "zel" : C.TWCoinTypeZelcash ,
    "rvn" : C.TWCoinTypeRavencoin ,
    "waves" : C.TWCoinTypeWaves ,
    "luna" : C.TWCoinTypeTerra ,
    "one" : C.TWCoinTypeHarmony ,
    "algo" : C.TWCoinTypeAlgorand ,
    "ksm" : C.TWCoinTypeKusama ,
    "dot" : C.TWCoinTypePolkadot ,
    "fil" : C.TWCoinTypeFilecoin ,
    "egld" : C.TWCoinTypeElrond ,
    "band" : C.TWCoinTypeBandChain ,
    "smartchain":C.TWCoinTypeSmartChain,
    "bsc" : C.TWCoinTypeSmartChainLegacy };

    str := TWStringCreateWithGoString("prefer exclude easy faith army artwork pencil tortoise fashion vague interest hair")
    emtpy := TWStringCreateWithGoString("")
    defer C.TWStringDelete(str)
    defer C.TWStringDelete(emtpy)

    wallet := C.TWHDWalletCreateWithMnemonic(str, emtpy)
    defer C.TWHDWalletDelete(wallet)

    key = C.TWHDWalletGetDerivedKey(wallet, types[coin], 0, 0 ,0 )
    defer C.free(unsafe.Pointer(key))
    keyData := C.TWPrivateKeyData(key)
    keyHex := hex.EncodeToString(TWDataGoBytes(keyData))
    fmt.Println("private key: ", keyHex)

    // address := C.TWStringUTF8Bytes(C.TWCoinTypeDeriveAddress(types[coin], keyHex));
    // fmt.Println("address:", TWStringGoString(address))


    address := C.TWHDWalletGetAddressForCoin(wallet, types[coin])
    fmt.Println("<== bitcoin address: ", TWStringGoString(address))
}