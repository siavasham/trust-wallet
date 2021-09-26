coins=('btc' 'eth')
for coin in "${coins[@]}"
do
    for (( c=1; c<=5; c++ ))
    do  
    echo "Welcome $c times $coin"
    done
done