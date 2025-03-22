MAGIC = b'RHPkgData'
VERSION = '0.0.1'
BINARY_NAME = 'build/package.bin'
PACKAGE_NAME = 'build/package.zip'
WRAPPED_NAME = f'build/R1senHub-v{VERSION}.zip'
INSTALLER_NAME = 'build/install.exe'
IGNORED_FNAMES = [r'_.*', r'install\.py']

from zipfile import ZipFile, ZIP_DEFLATED
from os.path import exists
from sys     import argv
from os      import listdir, remove
from re      import match

if not exists(INSTALLER_NAME):
    print(f'Cannot generate package without {INSTALLER_NAME.rsplit("/")[-1]}')
    exit(1)

version_bin_repr = b''.join([int(i).to_bytes() for i in VERSION.split('.')])

packages = [i.rsplit('.', 1)[0] for i in listdir('./build/') if not any(match(j, i) for j in IGNORED_FNAMES) and i.endswith('.exe')]
packages.sort()
print('Packages:\n\t- ', '\n\t- '.join(packages))
packages_bin_repr = b''
for package in packages:
    packages_bin_repr += package.encode('ascii') + b'\x00'
packages_bin_repr += b'\x00'

print(f'Generating file {BINARY_NAME} with {len(packages)} packages')
with open(BINARY_NAME, 'wb') as file:
    file.write(MAGIC)
    file.write(version_bin_repr)
    file.write(packages_bin_repr)

print(f'\nPacking stuff -> {PACKAGE_NAME}')
with ZipFile(PACKAGE_NAME, 'w', ZIP_DEFLATED) as zfile:
    for file in listdir('build/'):
        if not file.endswith(('.exe', '.bin')) or file == INSTALLER_NAME.rstrip('/')[-1]:
            print(f'\tSkipping: {file}')
            continue
        print(f'\tAdding:   {file}')
        zfile.write(f'build/{file}', file)

print(f'\nPacking stuff -> {WRAPPED_NAME}')
with ZipFile(WRAPPED_NAME, 'w', ZIP_DEFLATED) as zfile:
    for file in {PACKAGE_NAME, INSTALLER_NAME}:
        shortname = file.rsplit('/')[-1]
        print(f'\tAdding: {shortname}')
        zfile.write(file, shortname)

if not '--no-gc' in argv:
    print('\nCleaning up')
    for file in listdir('build/') + [PACKAGE_NAME]:
        if not file.endswith(('.exe', '.bin')):
            continue
        print(f'\tRemoving: {file}')
        try:
            remove(f'build/{file}')
        except FileNotFoundError:
            continue

print('\nDone!')