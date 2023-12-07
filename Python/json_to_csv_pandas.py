import json
import pandas as pd

IN_JSON = r"inf_file.json"
OUT_CSVe = r"out_file.csv"

def flatten_json(data):
    flatten_data = {}

    def flatten(value, name=''):
        if type(value) is dict:
            for val in value:
                flatten(value[val], name + val + '_')
        elif type(value) is list:
            i = 0
            for a in value:
                flatten(a, name)
                i += 1
        else:
            flatten_data[name[:-1]] = value

    flatten(data)
    return flatten_data

with open(IN_JSON, "r") as inputFile:
    json_data = json.loads(inputFile.read())

columns_to_drop = []
final_data = flatten_json(json_data)
final_data = pd.json_normalize(final_data)
final_data.drop(columns_to_drop, axis=1, inplace=True, )
final_data.to_csv(OUT_CSV, encoding='utf8', index=False)
