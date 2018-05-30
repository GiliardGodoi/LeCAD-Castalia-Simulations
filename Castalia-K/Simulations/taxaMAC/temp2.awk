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

	if($3 == "ModelCollision"){ 
		print $4		 
	}

	if($3 == "Pacotesrecebidos"){
		print $4" Recebidos "$7" Transmitidos "$5" Taxa "$9
	}

	if($3 == "SpentEnergy"){
		print tStr" Energia "$4" nJ/bit "$6
	}
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

# MAC
	if(tStr == "1" && $3 == "Failedbusychannel"){
		Fbc1=Fbc1+$4
	}
	if(tStr == "1" && $3 == "Failednoack"){
		Fna1=Fna1+$4
	}
	if(tStr == "1" && $3 == "Successnotfirsttry"){
		Snft1=Snft1+$4
	}
	if(tStr == "1" && $3 == "Successfirsttry"){
		Sft1=Sft1+$4
	}


	if(tStr == "2" && $3 == "Failedbusychannel"){
		Fbc2=Fbc2+$4
	}
	if(tStr == "2" && $3 == "Failednoack"){
		Fna2=Fna2+$4
	}
	if(tStr == "2" && $3 == "Successnotfirsttry"){
		Snft2=Snft2+$4
	}
	if(tStr == "2" && $3 == "Successfirsttry"){
		Sft2=Sft2+$4
	}


	if(tStr == "3" && $3 == "Failedbusychannel"){
		Fbc3=Fbc3+$4
	}
	if(tStr == "3" && $3 == "Failednoack"){
		Fna3=Fna3+$4
	}
	if(tStr == "3" && $3 == "Successnotfirsttry"){
		Snft3=Snft3+$4
	}
	if(tStr == "3" && $3 == "Successfirsttry"){
		Sft3=Sft3+$4
	}

	if(tStr == "4" && $3 == "Failedbusychannel"){
		Fbc4=Fbc4+$4
	}
	if(tStr == "4" && $3 == "Failednoack"){
		Fna4=Fna4+$4
	}
	if(tStr == "4" && $3 == "Successnotfirsttry"){
		Snft4=Snft4+$4
	}
	if(tStr == "4" && $3 == "Successfirsttry"){
		Sft4=Sft4+$4
	}


	if(tStr == "5" && $3 == "Failedbusychannel"){
		Fbc5=Fbc5+$4
	}
	if(tStr == "5" && $3 == "Failednoack"){
		Fna5=Fna5+$4
	}
	if(tStr == "5" && $3 == "Successnotfirsttry"){
		Snft5=Snft5+$4
	}
	if(tStr == "5" && $3 == "Successfirsttry"){
		Sft5=Sft5+$4
	}

}
END{
	print "1 "" FailedBusy "Fbc1
	print "1 "" FailedNoAck "Fna1
	print "1 "" SucessNotFirstTry "Snft1
	print "1 "" SucessFirstTry "Sft1

	print "2 "" FailedBusy "Fbc2
	print "2 "" FailedNoAck "Fna2
	print "2 "" SucessNotFirstTry "Snft2
	print "2 "" SucessFirstTry "Sft2

	print "3 "" FailedBusy "Fbc3
	print "3 "" FailedNoAck "Fna3
	print "3 "" SucessNotFirstTry "Snft3
	print "3 "" SucessFirstTry "Sft3

	print "4 "" FailedBusy "Fbc4
	print "4 "" FailedNoAck "Fna4
	print "4 "" SucessNotFirstTry "Snft4
	print "4 "" SucessFirstTry "Sft4

	print "5 "" FailedBusy "Fbc5
	print "5 "" FailedNoAck "Fna5
	print "5 "" SucessNotFirstTry "Snft5
	print "5 "" SucessFirstTry "Sft5

} 




# csplit -k -f simula Castalia-Trace.teste "/Not sending/" {15}
# separar arquivos com base no critério
# for i in $(ls simula*); do awk -f temp2.awk $i; done
