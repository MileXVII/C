# BinTranslator

A lightweight command-line utility that converts binary files (.bin) into readable text files (.txt).

## Description

BinTranslator reads binary files and converts them to text format, making the content readable while preserving the file structure. Non-printable characters (except newlines and tabs) are replaced with dots to maintain readability.

## Features

- Fast and memory-efficient binary-to-text conversion
- Preserves newlines and tabs for better formatting
- Handles large files using buffered I/O (4KB buffer)
- Automatic output file naming (replaces .bin with .txt)
- Input validation and error handling

## Compilation
```bash
gcc -o BinTranslator BinTranslator.c
```

## Usage
```bash
./BinTranslator <file.bin>
```

### Example
```bash
./BinTranslator data.bin
```

This will create `data.txt` in the same directory.

## How It Works

1. Validates that the input file has a `.bin` extension
2. Checks if the file is not empty
3. Reads the binary file in 4KB chunks for efficiency
4. Converts each byte:
   - Printable ASCII characters → kept as-is
   - Newlines and tabs → preserved
   - Non-printable bytes → replaced with `.`
5. Outputs to a `.txt` file with the same name

## Requirements

- C compiler (gcc, clang, etc.)
- Standard C library

## License

MIT License - See the main repository LICENSE file for details.

## Author

MileXVII - January 2026
