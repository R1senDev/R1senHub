from psutil import net_if_addrs
from socket import AF_INET
from sys    import argv

space = '-oL' in argv
if not space:
    print()
for iface, addrs in net_if_addrs().items():
    for addr in addrs:
        if addr.family == AF_INET:
            print(addr.address, end = ' ' if space else '\n')