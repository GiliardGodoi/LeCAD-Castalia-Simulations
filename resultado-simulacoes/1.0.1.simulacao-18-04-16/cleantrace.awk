#! /usr/bin/awk -f
BEGIN{

}
{
    if($3 == "NO"){
        tempo = $1
        potencia = $8
        taxaMAC = $11
        no = $4
        print no"    "tempo"    "potencia"    "taxaMAC
    }
}
END{

}