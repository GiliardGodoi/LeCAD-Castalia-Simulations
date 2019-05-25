import pandas as pd
from matplotlib import pyplot as plt
import seaborn as sns

def read(arquivo='bufferData.csv'):
    df = pd.read_csv(arquivo,delimiter="|")
    return df

def serieTemporal(dfData,output='taxaBufferVsTempo.png'):
    
    df = dfData[['Tempo','Nó Sensor', 'Taxa Buffer']]
    df = df.pivot(index='Tempo',columns='Nó Sensor',values='Taxa Buffer')
    df.fillna(value=0,inplace=True)
    axes = df.plot(subplots=True, figsize=(25, 10),legend=True,ylim=(0,75),style='-')
    plt.tight_layout()
    plt.savefig(output)
    return axes

def distribuicao(dfData,output='distribuicao-taxabuffer.png'):
    plt.figure(figsize=(15,10))
    plt.title("Distribuição da Taxa Buffer")
    plt.xlabel("Taxa Buffer")
    fig = sns.countplot(x="Taxa Buffer",data=dfData,color='steelblue')
    fig.get_figure().savefig(output)
    return fig


if __name__ == "__main__":
    df = read()
    serieTemporal(df)
    distribuicao(df)