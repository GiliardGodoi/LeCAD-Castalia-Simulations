#mkdir throughputPriority
#cd throughputPriority
cp ../throughputTest/* .

cat ThroughputTest.cc | sed -e 's/ThroughputTest/ThroughputPolicies/g' > ThroughputPriority.cc
cat ThroughputTest.h | sed -e 's/ThroughputTest/ThroughputPriority/g' > ThroughputPriority.h
cat ThroughputTest.ned | sed -e 's/ThroughputTest/ThroughputPriority/g' > ThroughputPriority.ned

# Não mudou "node.application.throughputPriority" no arquivo ThroughputPriority.ned
# pode ser que de certo isso aqui
cat ThroughputPriority.ned | sed -e 's/throughputTest/throughputPriority/g' > ThroughputPriority.ned