import pprint
import os
import ruamel.yaml


def flatten_dict(d):
    def items():
        for key, value in d.items():
            if isinstance(value, dict):
                for subkey, subvalue in flatten_dict(value).items():
                    yield subkey, subvalue
            else:
                yield key, value

    return dict(items())


def parse_yaml(yml_dict, print_cfg=False):
    # print("in parse_yaml")
    if print_cfg:
        pp = pprint.PrettyPrinter(width=12, compact=True)
        pp.pprint(yml_dict)
    yml_dict = flatten_dict(yml_dict)

    dir_list = ['SNAPSHOT_DIR', 'LOG_DIR', 'INF_OUTPUT_DIR', 'INF_OUTPUT_DIR_3D', 'EXPORT_DIR']
    for dir in dir_list:
        if dir in yml_dict.keys():
            if not (os.path.exists(yml_dict[dir]) or os.path.islink(yml_dict[dir])):
                # print(os.path.exists(yml_dict[dir]))
                # print(os.path.isdir(yml_dict[dir]))
                # print(os.path.islink(yml_dict[dir]))
                # print(os.path.isfile(yml_dict[dir]))
                # print("creating: " + yml_dict[dir])
                os.makedirs(yml_dict[dir], exist_ok=True)
                # print(os.path.exists(yml_dict[dir]))
                # print(os.path.isdir(yml_dict[dir]))
                # print(os.path.islink(yml_dict[dir]))
                # print(os.path.isfile(yml_dict[dir]))

    return yml_dict
