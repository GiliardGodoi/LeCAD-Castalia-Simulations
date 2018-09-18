import pandas as pd
from matplotlib import pyplot as plt
import seaborn as sns

def read(arquivo='bufferData.csv'):
    df = pd.read_csv(arquivo,delimiter="|")
    return df

def serieTemporal(dfData,output='taxaBufferVsTempo.png'):
    # axes = dfData.plot(x="Tempo",y="Taxa Buffer",hue="Nó Sensor",style="--",marker=".",figsize=(40,10))
    axes = plt.figure(figsize=(40,5))
    axes = sns.lineplot(x="Tempo",y="Taxa Buffer",hue="Nó Sensor",data=dfData)
    fig = axes.get_figure()
    fig.savefig(output)
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
    # distribuicao(df)