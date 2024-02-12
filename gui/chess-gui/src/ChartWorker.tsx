
self.onmessage = (event : MessageEvent<string>) =>
{
    const data = event.data;

    self.postMessage(true);
}

export {};