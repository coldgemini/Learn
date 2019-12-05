import yaml
import munch


class AttrDict():
    def __init__(self, init_dict=None):
        if init_dict == None:
            init_dict = {}
        super().__init__()
        for k, v in init_dict.items():
            self.__setattr__(k, v)

    def __setattr__(self, name, value):
        print(name, value)
        if isinstance(value, dict):
            att = AttrDict(init_dict=value)
            self.__setattr__(name, att)


with open('./tree.yml') as f:
    # use safe_load instead load
    dataMap0 = yaml.safe_load(f)

print(dataMap0)

# att = AttrDict(init_dict=dataMap0)
undefined = object()
att = munch.DefaultMunch(undefined, dataMap0)
# print(att.fromDict(dataMap0, undefined))
print(att.treeroot)
print(att.treeroot.branch1)
