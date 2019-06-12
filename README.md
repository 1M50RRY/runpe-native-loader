# RunPE native loader
## Consists of three parts:
- Encoder - uses the byte offset to encode payload
- Loader - downloads the file using urlmon (not the best practise, it's only for example)
- Memory executor - runs file in the memory of self-process using RunPE
