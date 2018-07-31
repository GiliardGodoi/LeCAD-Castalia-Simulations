#! /usr/bin/awk -f

BEGIN { }
{ 
	tStr = $2
	gsub(/[^0-9]/,"",tStr)
	if ($3 == "ALTERADO" && tStr == 4 ){
		# NO | TEMPO | POTENCIA | TAXA MAC
		print tStr"|"$1"|"$6"|"$9
	}	
}
END { }
