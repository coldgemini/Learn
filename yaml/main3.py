import yaml
from my_collections import AttrDict
from config import _merge_a_into_b

with open('./tree.yml') as f:
    # use safe_load instead load
    dataMap0 = yaml.safe_load(f)

attr_dict0 = AttrDict(dataMap0)
print(type(attr_dict0))
print(type(attr_dict0.treeroot.branch1))

with open('./tree1.yml') as f:
    # use safe_load instead load
    dataMap1 = yaml.safe_load(f)

attr_dict1 = AttrDict(dataMap1)
# print(attr_dict1)
print(type(attr_dict1.treeroot))

_merge_a_into_b(attr_dict0, attr_dict1)

print(attr_dict1)
