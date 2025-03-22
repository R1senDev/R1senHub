from zipfile import ZipFile
from shutil  import copyfile, rmtree
from json    import load
import os


INSTALLATION_DIR = 'C:/R1senTools/'

print('\nChecking privileges')
if os.system('net session >nul 2>&1') != 0:
    print('Please run this script as Administrator')
    exit(1)

reinstall = False
while True:
    try:
        os.makedirs(INSTALLATION_DIR)
        print(f'Creating path: {INSTALLATION_DIR}')
        break
    except FileExistsError:
        reinstall = True
        print(f'Removing existing installation: {INSTALLATION_DIR}')
        try:
            rmtree(INSTALLATION_DIR)
        except Exception as e:
            os.system(f'rmdir /S /Q "{INSTALLATION_DIR}"')

print(f'Unpacking: ./package.zip -> {INSTALLATION_DIR}')
with ZipFile('package.zip', 'r') as zip_ref:
    zip_ref.extractall(INSTALLATION_DIR)

print('Generating aliases...')
with open('aliases.json', 'r') as file:
    aliases_table = load(file) # type: dict[str, list[str]]
for path, aliases in aliases_table.items():
    for alias in aliases:
        print(f'\t- {alias} ==> {path}')
        with open(INSTALLATION_DIR + alias + '.bat', 'w') as file:
            file.write(f'@echo off\n{path} %*')

if not reinstall:
    print(f'Adding {INSTALLATION_DIR} to PATH')
    os.system(f'setx PATH "%PATH%;{INSTALLATION_DIR}"')

print('\nDone!\nTry running "risenhub" to see available tools. May need to reboot your PC to apply PATH changes.')