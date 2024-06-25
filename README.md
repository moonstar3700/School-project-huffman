# File Encoder Program with Huffman Encoding

This program is written in C++ and implements Huffman encoding to encode and decode text files efficiently.

## Overview

The File Encoder program allows you to encode and decode text files using Huffman encoding. Huffman encoding is a popular algorithm used for lossless data compression, where each character is assigned a variable-length code based on its frequency of occurrence in the input text. This method ensures that frequently occurring characters are assigned shorter codes, optimizing the overall file size.

## Features

- Huffman encoding to compress text files.
- Huffman decoding to decompress encoded files back to their original form.
- Command-line interface for compression and decompression operations.

## Running the Program

To run the File Encoder program, follow these steps:

1. **Open the Project in Visual Studio Code:**
   - Open Visual Studio Code.
   - Navigate to the project folder.

2. **Build the Release Version:**
   - Build the project in Release mode to generate the executable.
   - This will create a `Release` folder in the path `src\huffman\x64\Release`.

3. **Prepare Input File:**
   - Place a text file (`file.txt`) containing the message you want to encode in the `Release` folder.

4. **Compression:**
   - Open a shell (Bash) in the `Release` folder.
   - Run the following command to compress `file.txt` and save the results to `file.hf`:
     ```bash
     huffman compress file.txt file.hf
     ```

5. **Decompression:**
   - To decompress `file.hf` back to `file2.txt`, use the following command:
     ```bash
     huffman decompress file.hf file2.txt
     ```

6. **View Results:**
   - Check the `Release` folder for the compressed (`file.hf`) and decompressed (`file2.txt`) files.

## Example

Suppose `file.txt` contains the message "Hello, Huffman Encoding!". After compression and decompression using the program:

- `file.hf` will contain the compressed binary data.
- `file2.txt` will contain the original message "Hello, Huffman Encoding!" after decompression.

## Notes

- Ensure that you have Visual Studio Code installed and configured with C++ development tools.
- The program assumes that the input text file (`file.txt`) is in the `Release` folder.
- Adjust paths accordingly if your setup differs.
