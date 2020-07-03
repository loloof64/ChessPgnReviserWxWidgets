project('ChessPgnReviser', 'cpp')
conf_data = configuration_data()
conf_data.set('version', '0.1.0')

wx_dep = dependency('wxwidgets', version : '>=3.0.0', required : true)
if build_machine.system() == 'windows'
    executable('ChessPgnReviser.exe', ['src/main.cpp'], dependencies : [wx_dep])
else
    executable('ChessPgnReviser', ['src/main.cpp'], dependencies : [wx_dep])
endif    