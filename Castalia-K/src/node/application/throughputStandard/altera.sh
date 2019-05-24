#mkdir throughputPriority
#cd throughputPriority

cat ThroughputTest2.cc | sed -e 's/ThroughputTest2/ThroughputStandard/g' > ThroughputStandard.cc
cat ThroughputTest2.h | sed -e 's/ThroughputTest2/ThroughputStandard/g' > ThroughputStandard.h
cat ThroughputTest2.ned | sed -e 's/ThroughputTest2/ThroughputStandard/g' > ThroughputStandart.ned

# Não mudou "node.application.throughputBufferAware" no arquivo ThroughputBufferAware.ned
# pode ser que de certo isso aqui
# cat ThroughputBufferAware.ned | sed -e 's/throughputPriority/throughputBufferAware/g' > ThroughputBufferAware.ned