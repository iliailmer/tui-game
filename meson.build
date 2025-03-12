project('space_invaders', 'c', version: '0.1', default_options: ['warning_level=3'])
ncurses_dep = dependency('ncurses', required: true, fallback: ['ncurses', 'ncurses_dep'])

executable('game', 'src/main.c', install: true, dependencies: [ncurses_dep])
