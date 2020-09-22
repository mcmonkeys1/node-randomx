"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.RandomxHash = exports.RandomxCreateVM = void 0;
var arandx = require('node-gyp-build')(__dirname);
exports.RandomxCreateVM = function (key, flags) {
    var vm = arandx.RandomxVM(key.buffer, flags);
    return { vmRef: vm };
};
exports.RandomxHash = function (vm, data) {
    var hash = arandx.hash(vm.vmRef, data.buffer);
    return new Uint8Array(hash);
};
