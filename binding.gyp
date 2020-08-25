{
  "targets": [
    { 
      'cflags!': [ '-fno-exceptions' ],
        'cflags_cc!': [ '-fno-exceptions' ],
        'xcode_settings': {
          'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
          'CLANG_CXX_LIBRARY': 'libc++',
          'MACOSX_DEPLOYMENT_TARGET': '10.7',
        },
        'msvs_settings': {
          'VCCLCompilerTool': { 'ExceptionHandling': 1 },
        },
      "include_dirs" : [
        "<!@(node -p \"require('node-addon-api').include\")",
      ],
      'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],
      "target_name": "addon",
      'conditions': [
          ['OS=="linux"', {
            "libraries": [
              "../binaries/librandomx.a"
            ],
          }],
          ['OS=="win"', {
            "libraries": [
              # "../../RandomX/build-mingw/librandomx.a"
              "../binaries/randomx.lib"
            ],
          }],
       ],
      "sources": [  
        "./src/addon.cc",
        "./src/vm.cc"
      ],      
    }
  ]
}