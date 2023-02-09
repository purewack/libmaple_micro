import json
import os
from common import *

file = f"{root}/../{config['firmware']}"
print("Uploading to hardware:")
print(file)
os.system(f"stm32flash -w {file} -v -g 0x0 {config['port']}")