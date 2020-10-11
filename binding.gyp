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
          ['OS=="linux" and target_arch=="x64"', {
            "libraries": [
              "../binaries/librandomx.a"
            ],
          }],
          ['OS=="linux" and target_arch=="arm64"', {
            "libraries": [
              "../binaries/librandomx.pi4.a"
            ],
          }],
          ['OS=="win"', {
            "libraries": [
              "../binaries/randomx.lib"
            ],
          }],
       ],
      "sources": [  
        "./src-cpp/addon.cc",
        "./src-cpp/vm.cc"
      ],      
    }
  ]
}