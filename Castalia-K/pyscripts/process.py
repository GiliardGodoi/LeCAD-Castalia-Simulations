import pandas as pd
from pandas.compat import StringIO

def read_file_data(file_path):

    with open(file_path,'r') as file:
        content = file.read()

    content = [ line.strip('[ |]') for line in content.split('\n') if "|" in line ]

    if len(content) < 1:
        raise AttributeError('Arquivo possivelmente vazio')
  
    content[0] = 'Info |' + content[0]

    content = '\n'.join(content)

    df = pd.read_csv(StringIO(content),sep='|')
    df.columns = [ s.strip() for s in df.columns ]

    return df

def expand_info_column(data_frame):
    data_frame.Info = data_frame.Info.str.replace(',','=')
    tmp = data_frame.Info.str.split('=',expand=True)

    for i in range(0,len(tmp.columns),2):
        j = i + 1
        header = tmp[i].unique()
        if len(header) == 1 :
            header = ''.join(header)
        else:
            header = ' '.join(header)
        
        data_frame[header] = tmp[j]

    return data_frame.drop(columns=['Info'])