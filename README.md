# ar node randomx
NodeJS addon for RandomX (https://github.com/ArweaveTeam/RandomX)

RandomX is a blockchain PoW consensus algorithm developed for CPU mining.
This library helps you to use RandomX C++ library in your Nodejs Arweave projects. 

This fork differs from the orinal code by prudanoff in the following ways:

- added i/o support for UInt8Arrays instead of Strings
- comes with RandomX compiled against Arweave compatible version
- compiles to an importable JS library with Typescript bindings
- prebuilt library for Windows 10 included
- should compile automatically against your linux system

## How to install
~~Build RandomX from sources:~~

~~Clone this repo:~~

~~Install node-gyp:~~

~~Build addon:~~

Now just run
```
npm install mcmonkeys1/node-randomx
```
That's it :-)

## Example usage
```
import { RandomxCreateVM, RandomxHash, RandomxVMReference } from 'ar-node-randomx'

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
	let hash = RandomxHash(vm, blob)
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

## Troubleshooting

If you are having trouble installing on any version of Windows apart from Windows 10 x64, you may need to install node-gyp for compiling the node-randomx library first:

```
npm install --global --production windows-build-tools
```
For all other OSes take a look at the rest of the [node-gyp installion instructions](https://github.com/nodejs/node-gyp#installation) for node-gyp for prerequisites.
