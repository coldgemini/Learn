# import yaml

# from parse_yaml import parse_yaml

CONFIG = '/home/xiang/Workspace/Learn/yaml/config.yml'
# with open(CONFIG, 'r') as ymlfile:
#     cfg = yaml.safe_load(ymlfile)
# cfg = parse_yaml(cfg, print_cfg=False)
# print(cfg)

from pathlib import Path
import ruamel.yaml

in_file = Path(CONFIG)
yaml = ruamel.yaml.YAML()
data = yaml.load(CONFIG)
print(type(data))


def lookup(sk, d, path=[]):
    # lookup the values for key(s) sk return as list the tuple (path to the value, value)
    if isinstance(d, dict):
        for k, v in d.items():
            if k == sk:
                yield (path + [k], v)
            for res in lookup(sk, v, path + [k]):
                yield res
    elif isinstance(d, list):
        for item in d:
            for res in lookup(sk, item, path + [item]):
                yield res


for path, value in lookup("NUM_GPUS", data):
    print(path, '->', value)
