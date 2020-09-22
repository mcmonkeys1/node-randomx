## node randomx
NodeJS addon for Arweave's RandomX https://github.com/tevador/RandomX

RandomX is a blockchain PoW consensus algorithm developed for CPU mining.
This simple code helps you tu use RandomX C++ library in your Nodejs projects. 

## How to use
~~Build RandomX from sources:~~

~~Clone this repo:~~

~~Install node-gyp:~~

~~Build addon:~~
```
npm install mcmonkeys1/node-randomx
```
That's it :-)

## Example usage
```
import { RandomxCreateVM, RandomxHash, RandomxVMReference } from 'arweave-nodejs-randomx'

async function main(){
	let key = Buffer.from("0410591dc8b3bba89f949212982f05deeb4a1947e939c62679dfc7610c62")
	let blob = Buffer.from("58249adafb690683a800ee8d6556e2a7d25864d577afbf709ceff9e3bdd5ebae")

	let vm: RandomxVMReference
	console.log("Starting RandomX virtual machine...")
	try{
		vm = RandomxCreateVM(key, ["jit", "ssse3"])
	}
	catch(e){
		console.log(e)
		return 0
	}

	console.log("Start hashing...")
	let	hash = RandomxHash(vm, blob)
	console.log("hash: " + hash)
}
main();

```

### Flag Reference

```
export type RandomxFlag = 
	  'mine'        // mining mode: 2080 MiB
	| 'verify'      // verification mode: 256 MiB
	| 'jit'         // JIT compiled mode (default: interpreter)
	| 'secure'      // W^X policy for JIT pages (default: off)
	| 'largePages'  // use large pages (default: small pages)
	| 'softAes'     // use software AES (default: hardware AES)
	| 'ssse3'       // use optimized Argon2 for SSSE3 CPUs
	| 'avx2'        // use optimized Argon2 for AVX2 CPUs
```

