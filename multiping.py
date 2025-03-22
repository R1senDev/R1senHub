from sys import argv
import subprocess

def is_ip_available(ip):
    try:
        output = subprocess.check_output(['ping', '-n', '5', '-w', '1000', ip], stderr=subprocess.STDOUT, universal_newlines=True)
        if 'TTL=' in output:
            return True
        else:
            return False
    except subprocess.CalledProcessError:
        return False

up = 0

print()
for ip in argv[1:]:
    if is_ip_available(ip):
        print(f'{ip}\tOK')
        up += 1
    else:
        print(f'{ip}\tFAIL')

print(f'\nDone.\nChecked: {len(argv[1:])}, reachable: {up}.')