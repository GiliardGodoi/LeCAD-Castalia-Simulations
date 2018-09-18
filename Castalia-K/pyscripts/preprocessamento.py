import pandas as pd

def change_simulation_name(folder_name):
    '''
        Infere um indentificador (nome) para simulação a partir do nome do diretório.
        O diretório deve conter um identificador para a simulação com o seguinte padrão.
        XXXX_NomeSimulacao
    '''
    index = folder_name.rfind("_")
    index += 1
    simulation_name = folder_name[index:]

    return simulation_name

def inferir_modoColisao_apartir_repeticao(nro_repeticao, quant_repeticoes = 100):
    if nro_repeticao <= (1 * quant_repeticoes):
        return 0
    elif nro_repeticao <= (2 * quant_repeticoes):
        return 1 
    elif nro_repeticao <= (3 * quant_repeticoes):
        return 3
    else:
        raise Exception('Parâmetro não esperado!')

def obter_interfmodel(item):
    interfModel = item[12]
    return interfModel

def obter_node(item):
    node = item[19]
    return node

# col = ['Falha, estouro de buffer',
#        'Falha, canal ocupado',
#        'Falha, sem ACK',
#        'Sucesso, primeira tentativa',
#        'Sucesso, mais de uma tentativa']

# DATA['total de pacotes'] = DATA[col].sum(axis=1)
# DATA['Estouro de buffer'] = (DATA['Falha, estouro de buffer'] / DATA['total de pacotes']) * 100
# DATA['Canal ocupado'] = (DATA['Falha, canal ocupado'] / DATA['total de pacotes']) * 100
# DATA['Sem recebimento ACK'] = (DATA['Falha, sem ACK'] / DATA['total de pacotes']) * 100

# DATA['PRR, primeira tentativa'] = (DATA['Sucesso, primeira tentativa'] / DATA['total de pacotes']) * 100
# DATA['PRR, mais de uma tentativa'] = (DATA['Sucesso, mais de uma tentativa'] / DATA['total de pacotes']) * 100
