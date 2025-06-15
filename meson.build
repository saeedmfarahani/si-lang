project('si-lang', 'c',
  version: '0.0.0',
  default_options: ['warning_level=3', 'c_std=c23']
)

srcs = run_command('find', './src', '-type', 'f', '-name', '*[.c]', check : false).stdout().strip().split('\n')
incs = include_directories('inc')

executable('si-lang', srcs,
  include_directories: incs,
  install: true
)
