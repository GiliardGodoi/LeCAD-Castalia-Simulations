#!/usr/bin/awk −f
BEGIN{ 
Fbc1 = 0
Fna1 = 0
Sft1 = 0
Snft1 = 0

Fbc2 = 0
Fna2 = 0
Sft2 = 0
Snft2 = 0

Fbc3 = 0
Fna3 = 0
Sft3 = 0
Snft3 = 0

Fbc4 = 0
Fna4 = 0
Sft4 = 0
Snft4 = 0

Fbc5 = 0
Fna5 = 0
Sft5 = 0
Snft5 = 0


} 

{ 
#	tStr = $5

#	sub("#","",tStr)

	tStr = $2
	gsub(/[^0-9]/,"",tStr)	

# radio
	if($3 == "ReceivedwithNOinterference:"){
		print tStr" ReceivedWithNOinterference "$4
	}

	if($3 == "Receiveddespiteinterference:"){
		print tStr" ReceivedDespiteInterference "$4
	}
	if($3 == "FailedwithNOinterference:"){
		print tStr" FailedWithNOinterference "$4
	}
	if($3 == "Failedwithinterference:"){
		print tStr" FailedWithInterference "$4
	}
	if($3 == "Failed,nonRXstate:"){
		print tStr" FailedNonRXstate "$4
	}
	if($3 == "Failed,belowsensitivity:"){
		print tStr" FailedBelowSensitivity "$4
	}
	if($3 == "Failed,wrongmodulation:"){
		print tStr" FailedWrongModulation "$4
	}
	if($3 == "Bufferoverflow:"){
		print tStr" BufferOverflow "$4
	}

# resource
	if($3 == "Estimatednetworklifetimedays"){
		print tStr" EstimatednetworklifetimeDays "$4
	}
}

END{

} 




# csplit -k -f simula Castalia-Trace.teste "/Not sending/" {15}
# separar arquivos com base no critério
# for i in $(ls simula*); do awk -f temp2.awk $i; done
