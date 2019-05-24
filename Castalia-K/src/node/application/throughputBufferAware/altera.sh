#mkdir throughputPriority
#cd throughputPriority

cat ThroughputPriority.cc | sed -e 's/ThroughputPriority/ThroughputBufferAware/g' > ThroughputBufferAware.cc
cat ThroughputPriority.h | sed -e 's/ThroughputPriority/ThroughputBufferAware/g' > ThroughputBufferAware.h
cat ThroughputPriority.ned | sed -e 's/ThroughputPriority/ThroughputBufferAware/g' > ThroughputBufferAware.ned

# Não mudou "node.application.throughputBufferAware" no arquivo ThroughputBufferAware.ned
# pode ser que de certo isso aqui
# cat ThroughputBufferAware.ned | sed -e 's/throughputPriority/throughputBufferAware/g' > ThroughputBufferAware.ned