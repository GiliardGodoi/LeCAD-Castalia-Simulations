#! /usr/bin/awk -f
BEGIN{

}
{
    if($3 == "NO"){
        tempo = $1
        potencia = $8
        taxaMAC = $11
        no = $4
        # print no"    "tempo"    "potencia"    "taxaMAC
        if (no == 1){
            if((potencia,taxaMAC) in contador){
                contador[potencia, taxaMAC] = contador[potencia, taxaMAC] + 1
            } else {
                contador[potencia, taxaMAC] = 1
            }
        }
    }
}
END{
    for( indice in contador){
        print indice" - "contador[indice]
    }
}