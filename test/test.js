const rx = require('node-gyp-build')(__dirname + '/..')


let key = new Uint8Array(Buffer.from("0410591dc8b3bba89f949212982f05deeb4a1947e939c62679dfc7610c62"))
let key2 = new Uint8Array(Buffer.from("9529408ea783bba89f949212982f05deeb4a1945e939c55679dfc7123456"))
let blob = new Uint8Array(Buffer.from("58249adafb690683a800ee8d6556e2a7d25864d577afbf709ceff9e3bdd5ebae"))

function main(key) {
	let vm
	console.log("Starting RandomX virtual machine...")
	try{
		vm = rx.RandomxVM(key.buffer, ["jit"])
	}
	catch(e){
		console.log(e)
		return 0
	}

	console.log("Start hashing...")
	let	hash = rx.hash(vm, blob.buffer)
	let view = new Uint8Array(hash)
	console.log("hash: " + view)
}
main(key)
main(key2)

let bigmem1 = new Uint8Array(1024**3)
let bigmem2 = new Uint8Array(1024**3)
let bigmem3 = new Uint8Array(1024**3)
let bigmem4 = new Uint8Array(1024**3)

for (let i = 0; i < bigmem1.length; i++) {
	bigmem1[i] = i * 4
	bigmem2[i] = i / 2 + i
	bigmem3[i] = i ^ 0xff
	bigmem4[i] = i * 2
}
