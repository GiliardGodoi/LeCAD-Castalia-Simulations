# -*- coding: utf-8 -*-
"""
Created on Thu Feb 14 11:06:56 2019

@author: Giliard A Godoi
"""
import pandas as pd

def read_to_array(filename):
    file = open(filename,'r')
    array = file.read().replace(" | ","|").strip().split('\n')
    
    return array

def interpret_line(line):
        
    if len(line) == 0 or line.isspace():
        return 'IGNORE'
    
    elif "|" in line:
        return 'TABLE'
    
    elif ":" in line and line.count(',') is 0:
#    atribuir ao objeto a funcao que monta a tabela para "Total"
        if 'all values' in line:
            return 'BEGIN_ALL'
        else:
            return 'BEGIN'
#    atribuir ao objeto main a funcao que monta a tabela "All"
    
    elif 'CastaliaResults' in line:
        return 'COMMAND'
    
    else:
        return 'IGNORE'


def extract_main_table(data):
    reachMainTable = False
    hasHeader = False
    
    result = list()
    
    for line in data:
        _type = interpret_line(line)
        
        if reachMainTable and _type == "TABLE":
            if not hasHeader :
                line = line.strip("|")
                hasHeader = True
                
            else:
                line = line = line.strip().replace(',','|').replace('-','0')
            
            result.append(line)
            
        elif _type == "BEGIN":
            reachMainTable = True
            
        elif _type == "BEGIN_ALL":
            break
        
        
    return result

def extract_all_table(data):
    reachAllTable = False
    
    hasHeader = False
    
    result = list()
    
    for line in data:
        _type = interpret_line(line)
        
        if reachAllTable and (_type == 'TABLE'):
            # collect data
            line = line.strip()
            if not hasHeader:
                line = line.strip('|')
                hasHeader = True
            else :
                line = line.strip()
                line = line.replace(',','|').replace(' ','|').replace('-','0')
            
            result.append(line)
            
        elif _type == "BEGIN_ALL":
            reachAllTable = True
            
    return result

def define_better_header(data,compHeader=None):
    header = data[0]
    body = data[1:]
    
    diff = body[0].count('|') - header.count('|')
    
    if compHeader:
        if len(compHeader) == diff:
            header = "|".join(compHeader) + "|" + header    
            return header
        
    h_c = ['info_{0}'.format(i) for i in range(0,diff)]
    h = "|".join(h_c)
    
    return h + "|" + header
        
        
def parser_main_table(filename):
    
    _list = read_to_array(filename)
    _data = extract_main_table(_list)
    _header = define_better_header(_data)
    
    _data[0] = _header
    _data = [ item.split("|") for item in _data ]
    
    df = pd.DataFrame(data=_data[1:],columns=_data[0])
    
    return df
        
    
def parser_allvalues_table(filename):
    
    _list = read_to_array(filename)
    _data = extract_all_table(_list)
    _header = define_better_header(_data)
    
    _data[0] = _header
    _data = [ item.split("|") for item in _data ]
    
    df = pd.DataFrame(data=_data[1:],columns=_data[0])
    
    return df
    

