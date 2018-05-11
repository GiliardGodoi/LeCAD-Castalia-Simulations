#mkdir throughputPolicies
#cd throughputPolicies
cp ../throughputTest/* .

cat ThroughputTest.cc | sed -e 's/ThroughputTest/ThroughputPolicies/g' > ThroughputPolicies.cc
cat ThroughputTest.h | sed -e 's/ThroughputTest/ThroughputPolicies/g' > ThroughputPolicies.h
cat ThroughputTest.ned | sed -e 's/ThroughputTest/ThroughputPolicies/g' > ThroughputPolicies.ned

# Não mudou "node.application.throughputPolicies" no arquivo ThroughputPolicies.ned
# pode ser que de certo isso aqui
cat ThroughputPolicies.ned | sed -e 's/throughputTest/throughputPolicies/g' > ThroughputPolicies.ned