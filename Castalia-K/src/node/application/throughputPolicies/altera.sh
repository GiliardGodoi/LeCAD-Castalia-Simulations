#mkdir throughputPriority
#cd throughputPriority

cat ThroughputTest.cc | sed -e 's/ThroughputTest/ThroughputPolicies/g' > ThroughputPolicies.cc
cat ThroughputTest.h | sed -e 's/ThroughputTest/ThroughputPolicies/g' > ThroughputPolicies.h
cat ThroughputTest.ned | sed -e 's/ThroughputTest/ThroughputPolicies/g' > ThroughputPolicies.ned

# Não mudou "node.application.throughputBufferAware" no arquivo ThroughputBufferAware.ned
# pode ser que de certo isso aqui
# cat ThroughputBufferAware.ned | sed -e 's/throughputPriority/throughputBufferAware/g' > ThroughputBufferAware.ned