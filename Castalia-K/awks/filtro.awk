#!/usr/bin/awk −f

# Analisa o log do arquivo Castalia-Trace.txt. 
# 'Filtra' todos os registros (linhas) e mantém somente a linha do Nó sensor de interesse (nodeTarget)

BEGIN{
    nodeTarget = 5
}
{
    node = $2
    gsub(/[^0-9]/,"",node)
    if(node == nodeTarget){
        print $0
    }
}
END{

}