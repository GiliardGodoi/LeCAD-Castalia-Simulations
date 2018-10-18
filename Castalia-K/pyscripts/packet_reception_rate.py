import pandas as pd

def read(file='packet_reception_rate.txt'):
    f = open(file,'r')
    line = f.readline()
    while(line.find('|') < 0):
        line = f.readline()

    colunas = line.strip('\n').split('|')
    colunas[0] = 'Info'

    df = pd.read_csv(f,delimiter='|',names=colunas)
    
    return df

