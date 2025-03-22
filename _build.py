from shutil import rmtree
from time   import time
from sys    import argv
from os     import system, listdir
from re     import match

IGNORED = [r'_.*']

OUTPUT_DIR = 'build'
T_PYTHON = 'py -m nuitka --standalone --onefile --no-pyi-file --output-dir={output_dir} --jobs=4 {src}'.replace('{output_dir}', OUTPUT_DIR)
T_C = 'gcc {src} -o {output_dir}/{dst}.exe'.replace('{output_dir}', OUTPUT_DIR)

if '--all' == argv[1]:
    files = [file for file in listdir() if (not any([match(pattern, file) for pattern in IGNORED])) and (file.endswith(('.py', '.pyw')) or file.endswith('.c'))]
elif '--c' == argv[1]:
    files = [file for file in listdir() if (not any([match(pattern, file) for pattern in IGNORED])) and file.endswith('.c')]
elif '--python' == argv[1]:
    files = [file for file in listdir() if (not any([match(pattern, file) for pattern in IGNORED])) and file.endswith(('.py', '.pyw'))]
else:
    files = argv[1:]

start_time = time()

if not '--just-gc' in argv:
    for file in files:
        template = ''
        if file.endswith(('.py', '.pyw')):
            template = T_PYTHON
        elif file.endswith('.c'):
            template = T_C
        fname = file.replace('\\', '/').rsplit('/')[-1]
        print(template.format(
            src = fname,
            dst = fname.split('.')[0]
        ))
        system(template.format(
            src = fname,
            dst = fname.split('.')[0]
        ))

if '--run-gc' in argv or '--just-gc' in argv:
    print('\nGC payload in progress...')
    for child in listdir(OUTPUT_DIR):
        if any(match(regex, child) for regex in {r'.+\.dist', r'.+\.build', r'.+\.onefile-build'}):
            rmtree(f'{OUTPUT_DIR}/{child}')

print(f'\n\nBuild done in {round(time() - start_time)} s')