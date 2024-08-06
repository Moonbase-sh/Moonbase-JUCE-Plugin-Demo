import * as Juce from 'juce-framework-frontend';

async function callJuceNative(fnName, result, ...args) {
    const nativeFunction = Juce.getNativeFunction(fnName);
    const r = await nativeFunction(...args);
    result.value = r;
}

async function callJuceNativeReturn(fnName, ...args) {
    const nativeFunction = Juce.getNativeFunction(fnName);
    return await nativeFunction(...args);
}

const JuceHelpers = {
    callJuceNative,
    callJuceNativeReturn,
}

export { JuceHelpers };
