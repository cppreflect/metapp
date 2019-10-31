project('printable_test', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++17'])

metareflect = find_program('mpp')

gen = generator(
  metareflect,
  output: '@BASENAME@_gen.hpp',
  arguments: ['--template', '@SOURCE_DIR@/def.inja', '--output', '@OUTPUT@', '@INPUT@'])

gen_src = gen.process('complex.hpp')

exe = executable('printable', sources: ['main.cpp', gen_src], cpp_args: '-Wno-attributes')
test('basic', exe)
