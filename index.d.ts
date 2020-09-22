export declare type RandomxFlag = 'mine' | 'verify' | 'jit' | 'secure' | 'largePages' | 'softAes' | 'ssse3' | 'avx2';
export interface RandomxVMReference {
    readonly vmRef: Object;
}
export declare const RandomxCreateVM: (key: Uint8Array, flags: RandomxFlag[]) => RandomxVMReference;
export declare const RandomxHash: (vm: RandomxVMReference, data: Uint8Array) => Uint8Array;
