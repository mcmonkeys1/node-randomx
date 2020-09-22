const arandx = require('node-gyp-build')(__dirname)


export type RandomxFlag = 
	  'mine'        // mining mode: 2080 MiB
	| 'verify'      // verification mode: 256 MiB
	| 'jit'         // JIT compiled mode (default: interpreter)
	| 'secure'      // W^X policy for JIT pages (default: off)
	| 'largePages'  // use large pages (default: small pages)
	| 'softAes'     // use software AES (default: hardware AES)
	| 'ssse3'       // use optimized Argon2 for SSSE3 CPUs
	| 'avx2'        // use optimized Argon2 for AVX2 CPUs

export interface RandomxVMReference {
	readonly vmRef: Object
}

export const RandomxCreateVM = (key: Uint8Array, flags: RandomxFlag[] ) => {
	let vm = arandx.RandomxVM(key.buffer, flags)
	return { vmRef: vm } as RandomxVMReference
}

export const RandomxHash = (vm: RandomxVMReference, data: Uint8Array) => {
	let hash = arandx.hash(vm.vmRef, data.buffer)
	return new Uint8Array(hash)
}