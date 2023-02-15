import os
import json

root = os.path.dirname(os.path.realpath(__file__))
config_file = f"{root}/../config.json"

if not os.path.exists(config_file):
    print("Missing config.json")
    exit(-1)

with open(config_file,'r') as f:
    config = json.load(f)

def config_save():
    with open(config_file, "w") as f:
        js = json.dumps(config, indent=4)
        f.write(js)