
coins=('btc' 'eth')
for coin in "${coins[@]}"
do
    for (( c=1; c<=2; c++ ))
    do  
    /wallet-core/build/walletconsole/walletconsole
    coin "${coin}"
    done
done