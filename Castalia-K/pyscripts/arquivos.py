import pandas as pd
import os
from os import path

def read_csv(
        file,
        columnlabel = None,
        delimiter = '|'
    ):

    if (file == '') or (type(file) != str):
        raise Exception('Argumento file é inválido')
    
    dfData = pd.read_csv(file,delimiter=delimiter,names=columnlabel)

    return dfData



def read(file, folders = None, columnlabel = None):
    if folders == None:
        return read_csv(file,columnlabel=columnlabel)
    
    if type(folders) == str:
        folders = [folders]

    dfData = pd.DataFrame()

    for folder in filter(lambda x: path.isdir(x),folders):
        dataFile = path.join(folder,file)
        if path.isfile(dataFile):
            df = read_csv(dataFile,columnlabel=columnlabel)
            df['folder'] = folder
            dfData = dfData.append(df,ignore_index=True)
            print(folder)
    
    return dfData

def read_taxaMAC(file, folders = None):

    columns = ['Tempo', 'Nó Sensor', 'taxaMAC', 'Repeticao']

    return read(file,folders=folders,columnlabel=columns)

def read_packet_breakdown(folders):
    file = 'packet_breakdown.txt' 
    columns = ['InterfModel,node',
           'Falha, estouro de buffer',
           'Falha, canal ocupado',
           'Falha, sem ACK',
           'Sucesso, primeira tentativa',
           'Sucesso, mais de uma tentativa']
    
    dfData = read(file,folders=folders,columnlabel=columns)

    return dfData

def read_PRR(folders):
    file = 'PRR.txt'
    columns = ['Modelo de colisao', 'nó 1', 'nó 2', 'nó 3', 'nó 4', 'nó 5']
    dfData = read(file,folders=folders,columnlabel=columns)

    return dfData