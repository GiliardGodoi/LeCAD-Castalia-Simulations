import pandas as pd
import numpy as np

from pandas import DataFrame, Series

import matplotlib.pyplot as plt
import seaborn as sns

def save_fig(fig, filename='./img/img.png'):
    '''
    Salva uma figura de acordo com o nome especificado.
    O nome já deve conter o diretório  destino da imagem e o tipo de arquivo - png ou jpg.
    O diretorio já deve existir, caso contrário lançará uma exceção de diretório não existente.
    '''
    fig.get_figure().savefig(filename)

def plot_taxaMAC(dataFrame, repeticao = 0, axis = None,style='--',label='taxa mac'):
    '''
        Gráfico que mostra a variação da taxaMAC ao longo do tempo.

        Parâmetros:
            dataFrame: dados a serem plotados;
            repeticao: relacionado ao parametro 'repeticao' do dataFrame que sinaliza qual repetição estamos interessados
            axis: utilizado para plotar mais de uma série temporal no mesmo gráfico.
            outfile: Se especificado o gráfico em uma imagem de acordo com o nome e caminho especificado.
    '''
    if repeticao != 0: 
        dataFrame = dataFrame[dataFrame["repeticao"] == repeticao]
    # plt.figure()
    fig = dataFrame.plot(x='tempo',
                    y='taxaMAC',
                    figsize=(40,5),
                    marker='.',
                    style=style,
                    ax=axis,
                    label=label
                   )
    
    return fig

def plot_MMtaxaMAC(dataFrame, repeticao = None, axis = None,style='r--',label='media móvel'):
    '''Calcula a media móvel da taxaMAC e plota o gráfico correspondente.'''
    if repeticao != 0 :
        dataFrame = dataFrame[dataFrame["repeticao"] == repeticao]
    dataFrame = dataFrame.rolling(window=5).mean()
    fig = dataFrame.plot(x='tempo',
                    y='taxaMAC',
                    figsize=(40,5),
                    marker='.',
                    style=style,
                    ax=axis,
                    label=label
                   )
   
    return fig

def plot_potencia(dataFrame,repeticao = None,
                  size=(40,5),
                  marker='.',
                  style='c--',
                  label='potencia',
                  vetorPotencia=[-10, -12, -15, -20, -25]):
    
    if repeticao :
        dataFrame = dataFrame[dataFrame['repeticao'] == repeticao]
    
    fig = dataFrame.plot(x='tempo', y='potencia',figsize=size,marker=marker, style=style,label=label,yticks=vetorPotencia)
    
    return fig
    

def compare_MM_and_taxaMAC_chart(dataFrame, repeticao = 0):
    '''Sobrepõe o gráfico da variação da taxaMAC e a sua Média Móvel.'''
    fig = plot_taxaMAC(dataFrame,repeticao=repeticao,style="g--")
    fig = plot_MMtaxaMAC(dataFrame,repeticao=repeticao,axis=fig,style="r--")
    return fig

def barchart_taxaMAC(dataFrame,ylim=(0,2500),xlim=(0,100),imgsize=(15,10)):
    '''Plota gráfico de barras com a contagem das ocorrências dos valores da taxaMAC.'''
    plt.figure(figsize=imgsize)
    plt.title('Ocorrencias das TaxaMAC')
    plt.xlabel('Taxa MAC')
    fig = sns.countplot(x='taxaMAC', data=dataFrame)

    return fig

def calcula_porcentagem_taxaMAC(dados, repeticao = 0):
    if repeticao != 0:
        dados = dados[dados["repeticao"] == repeticao]
    df = dados.groupby(by="taxaMAC",as_index=False).count()
    total = df["no"].sum()
    resultado = DataFrame()
    resultado["freq_absoluta"] = df["no"]
    resultado["freq_relativa"] = df["no"] / total
    return resultado

def barchart_porcentagem_taxaMAC(dataFrame,repeticao=0,ylim=(0,50),xlim=(0,100),imgsize=(15,10)):
    '''Plota gráfico com as frequencias relativas da taxa MAC (porcentagens)'''
    plt.figure(figsize=imgsize)
    plt.title('Frequencia Relativa / TaxaMAC')
    df = dataFrame.groupby(by="taxaMAC",as_index=False).count()
    total = df["no"].sum()
    df["porcentagem"] = 100 * (df["no"] / total)
    fig = sns.barplot(x="taxaMAC", y="porcentagem",data=df)

    return fig

def barchart_frequencia_potencia(dados,ylim=(0,2500)):
    '''Plota gráfico de barras com a contagem das ocorrências dos valores assumidos pela potencia.'''
    plt.figure(figsize=(12,8))
    plt.title('Frequência Absoluta - Potência')
    plt.xlabel('potência')
    fig = sns.countplot(x='potencia', data=dados)
    fig.set(ylim=ylim)

    return fig

def calcula_porcentagem_potencia(dados, repeticao = 0):
    if repeticao != 0:
        dados = dados[dados["repeticao"] == repeticao]
    df = dados.groupby(by="potencia",as_index=False).count()
    total = df["no"].sum()
    resultado = DataFrame()
    resultado["freq_absoluta"] = df["no"]
    resultado["freq_relativa"] = 100 * (df["no"] / total)
    return resultado

def barchart_porcentagem_potencia(dataFrame,repeticao=0):
    df = dataFrame.groupby(by="potencia",as_index=False).count()
    total = df["no"].sum()
    df["porcentagem"] = 100 * (df["no"] / total)
    plt.figure(figsize=(12,8))
    plt.title('Frequência Relativa - Potência')
    plt.xlabel('potência')
    fig = sns.barplot(x="potencia", y="porcentagem",data=df)

    return fig

def stripplot_taxaMAC_potencia(dataFrame,jitter=True):
    plt.figure()
    fig = sns.stripplot(x='potencia', y='taxaMAC',data=dataFrame,jitter=jitter)
        
    return fig
        
def boxplot_taxaMAC_potencia(dataFrame):
    plt.figure()
    fig = sns.boxplot(x='potencia',y='taxaMAC',data=dataFrame)
    return fig


def heatmap_potencia_taxaMAC(dataFrame,imgsize=(15,10),fmt=".2g"):
    tmp = dataFrame.copy()
    tmp['potencia'] = tmp['potencia'].shift(1)
    
    plt.figure(figsize=(15,10))
    dfNo = tmp.pivot_table(index='taxaMAC',columns='potencia',aggfunc=np.count_nonzero)['no']
    fig = sns.heatmap(dfNo,cmap="YlGnBu", fmt=fmt,annot=True)
    return fig

def calcula_distribuicao_condicional(dataFrame,index='taxaMAC', col='potencia',col_get='no'):
    tmp = dataFrame.copy()
    tmp['potencia'] = tmp['potencia'].shift(1)
    dfPivoted = tmp.pivot_table(index=index,columns=col,aggfunc=np.count_nonzero)[col_get].fillna(0)
    
    total_geral = dataFrame.count()[col_get]
    P_txMacAndW = dfPivoted.applymap(lambda x: x/total_geral)
    P_W = P_txMacAndW.sum(axis=0)
    
    def prop_cond(x):
        w = x.name
        p_w = P_W[w]
        return x / p_w
    
    P_condicional = P_txMacAndW.apply(prop_cond, axis=0)
    
    return P_condicional
    
def heatmap_dist_condicional(dataFrame):
    p_condicional = calcula_distribuicao_condicional(dataFrame)
    fig = sns.heatmap(p_condicional,cmap="YlGnBu",annot=True)
    return fig
    
    
def plot_rssi(data,repeticao = 1, node = None):
    
    if node != None and type(node) == int:
        select = (data['Repeticao'] == repeticao) & (data['Nó sensor'] == node)
    else:
        select = data['Repeticao'] == repeticao
        
    df = data[select]
    fig = df.plot(x='Tempo',y='RSSI',figsize=(40,5))
    return fig
